/*
 * ADSpinnaker.cpp
 *
 * This is a driver for FLIR (PointGrey) GigE, 10GigE, and USB3 cameras using their Spinnaker SDK
 *
 * Author: Mark Rivers
 *         University of Chicago
 *
 * Created: February 3, 2018
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <set>

#include <epicsEvent.h>
#include <epicsTime.h>
#include <epicsThread.h>
#include <epicsMessageQueue.h>
#include <iocsh.h>
#include <cantProceed.h>
#include <epicsString.h>
#include <epicsExit.h>

#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"

using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;
using namespace std;

#include <ADGenICam.h>

#include <epicsExport.h>
#include "SPFeature.h"
#include "ADSpinnaker.h"

#define DRIVER_VERSION      1
#define DRIVER_REVISION     0
#define DRIVER_MODIFICATION 0

static const char *driverName = "ADSpinnaker";

/*
#define PGPacketSizeString            "PG_PACKET_SIZE"
#define PGPacketSizeActualString      "PG_PACKET_SIZE_ACTUAL"
#define PGMaxPacketSizeString         "PG_MAX_PACKET_SIZE"
#define PGPacketDelayString           "PG_PACKET_DELAY"
#define PGPacketDelayActualString     "PG_PACKET_DELAY_ACTUAL"
#define PGBandwidthString             "PG_BANDWIDTH"
*/

// Default packet delay in microseconds
#define DEFAULT_PACKET_DELAY 400

// Size of message queue for callback function
#define CALLBACK_MESSAGE_QUEUE_SIZE 10

typedef enum {
    SPPixelConvertNone,
    SPPixelConvertMono8,
    SPPixelConvertMono16,
    SPPixelConvertRaw16,
    SPPixelConvertRGB8,
    SPPixelConvertRGB16
} SPPixelConvert_t;


/*
static const char *gigEPropertyTypeStrings[NUM_GIGE_PROPERTIES] = {
    "Heartbeat",
    "HeartbeatTimeout",
    "PacketSize",
    "PacketDelay"
};
*/

typedef enum {
    TimeStampCamera,
    TimeStampEPICS
} SPTimeStamp_t;

typedef enum {
    UniqueIdCamera,
    UniqueIdDriver
} SPUniqueId_t;



/** Configuration function to configure one camera.
 *
 * This function need to be called once for each camera to be used by the IOC. A call to this
 * function instanciates one object from the ADSpinnaker class.
 * \param[in] portName asyn port name to assign to the camera.
 * \param[in] cameraId The camera index or serial number; <1000 is assumed to be index, >=1000 is assumed to be serial number.
 * \param[in] traceMask The initial value of the asynTraceMask.  
 *            If set to 0 or 1 then asynTraceMask will be set to ASYN_TRACE_ERROR.
 *            If set to 0x21 (ASYN_TRACE_WARNING | ASYN_TRACE_ERROR) then each call to the
 *            FlyCap2 library will be traced including during initialization.
 * \param[in] memoryChannel  The camera memory channel (non-volatile memory containing camera parameters) 
 *            to load during initialization.  If 0 no memory channel is loaded.
 *            If >=1 thenRestoreFromMemoryChannel(memoryChannel-1) is called.  
 *            Set memoryChannel to 1 to work around a bug in the Linux GigE driver in R2.0.
 * \param[in] maxMemory Maximum memory (in bytes) that this driver is allowed to allocate. So if max. size = 1024x768 (8bpp)
 *            and maxBuffers is, say 14. maxMemory = 1024x768x14 = 11010048 bytes (~11MB). 0=unlimited.
 * \param[in] priority The EPICS thread priority for this driver.  0=use asyn default.
 * \param[in] stackSize The size of the stack for the EPICS port thread. 0=use asyn default.
 */
extern "C" int ADSpinnakerConfig(const char *portName, int cameraId, int traceMask, int memoryChannel, 
                                 size_t maxMemory, int priority, int stackSize)
{
    new ADSpinnaker( portName, cameraId, traceMask, memoryChannel, maxMemory, priority, stackSize);
    return asynSuccess;
}


static void c_shutdown(void *arg)
{
   ADSpinnaker *p = (ADSpinnaker *)arg;
   p->shutdown();
}


static void imageGrabTaskC(void *drvPvt)
{
    ADSpinnaker *pPvt = (ADSpinnaker *)drvPvt;

    pPvt->imageGrabTask();
}

/** Constructor for the ADSpinnaker class
 * \param[in] portName asyn port name to assign to the camera.
 * \param[in] cameraId The camera index or serial number; <1000 is assumed to be index, >=1000 is assumed to be serial number.
 * \param[in] traceMask The initial value of the asynTraceMask.  
 *            If set to 0 or 1 then asynTraceMask will be set to ASYN_TRACE_ERROR.
 *            If set to 0x21 (ASYN_TRACE_WARNING | ASYN_TRACE_ERROR) then each call to the
 *            FlyCap2 library will be traced including during initialization.
 * \param[in] memoryChannel  The camera memory channel (non-volatile memory containing camera parameters) 
 *            to load during initialization.  If 0 no memory channel is loaded.
 *            If >=1 thenRestoreFromMemoryChannel(memoryChannel-1) is called.  
 *            Set memoryChannel to 1 to work around a bug in the Linux GigE driver in R2.0.
 * \param[in] maxMemory Maximum memory (in bytes) that this driver is allowed to allocate. So if max. size = 1024x768 (8bpp)
 *            and maxBuffers is, say 14. maxMemory = 1024x768x14 = 11010048 bytes (~11MB). 0=unlimited.
 * \param[in] priority The EPICS thread priority for this driver.  0=use asyn default.
 * \param[in] stackSize The size of the stack for the EPICS port thread. 0=use asyn default.
 */
ADSpinnaker::ADSpinnaker(const char *portName, int cameraId, int traceMask, int memoryChannel,
                         size_t maxMemory, int priority, int stackSize )
    : ADGenICam(portName, maxMemory, priority, stackSize),
    cameraId_(cameraId), memoryChannel_(memoryChannel), exiting_(0), pRaw_(NULL), uniqueId_(0)
{
    static const char *functionName = "ADSpinnaker";
    asynStatus status;
    
    if (traceMask == 0) traceMask = ASYN_TRACE_ERROR;
    pasynTrace->setTraceMask(pasynUserSelf, traceMask);


/*
    createParam(PGPacketSizeString,             asynParamInt32,   &PGPacketSize);
    createParam(PGPacketSizeActualString,       asynParamInt32,   &PGPacketSizeActual);
    createParam(PGMaxPacketSizeString,          asynParamInt32,   &PGMaxPacketSize);
    createParam(PGPacketDelayString,            asynParamInt32,   &PGPacketDelay);
    createParam(PGPacketDelayActualString,      asynParamInt32,   &PGPacketDelayActual);
    createParam(PGBandwidthString,              asynParamFloat64, &PGBandwidth);
*/
    // Retrieve singleton reference to system object
    system_ = System::GetInstance();

    status = connectCamera();
    if (status) {
        asynPrint(pasynUserSelf, ASYN_TRACE_ERROR,
            "%s:%s:  camera connection failed (%d)\n",
            driverName, functionName, status);
        // Call report() to get a list of available cameras
        report(stdout, 1);
        return;
    }

    createParam("SP_CONVERT_PIXEL_FORMAT",     asynParamInt32,   &SPConvertPixelFormat);

    createParam("SP_BUFFER_UNDERRUN_COUNT",    asynParamInt32,   &SPBufferUnderrunCount);
    createParam("SP_FAILED_BUFFER_COUNT",      asynParamInt32,   &SPFailedBufferCount);
    createParam("SP_FAILED_PACKET_COUNT",      asynParamInt32,   &SPFailedPacketCount);
    createParam("SP_TIME_STAMP_MODE",          asynParamInt32,   &SPTimeStampMode);
    createParam("SP_UNIQUE_ID_MODE",           asynParamInt32,   &SPUniqueIdMode);

    /* Set initial values of some parameters */
    setIntegerParam(NDDataType, NDUInt8);
    setIntegerParam(NDColorMode, NDColorModeMono);
    setIntegerParam(NDArraySizeZ, 0);
    setIntegerParam(ADMinX, 0);
    setIntegerParam(ADMinY, 0);
    setStringParam(ADStringToServer, "<not used by driver>");
    setStringParam(ADStringFromServer, "<not used by driver>");
//    setIntegerParam(SPTriggerSource, 0);
//    setSPProperty(SPColorProcessEnabled, 0);
    
//    getSPProperty(ADMaxSizeX, &iValue);
//    setIntegerParam(ADSizeX, iValue);
//    getSPProperty(ADMaxSizeY, &iValue);
//    setIntegerParam(ADSizeY, iValue);

    // Create the message queue to pass images from the callback class
    pCallbackMsgQ_ = new epicsMessageQueue(CALLBACK_MESSAGE_QUEUE_SIZE, sizeof(ImagePtr));
    if (!pCallbackMsgQ_) {
        cantProceed("ADSpinnaker::ADSpinnaker epicsMessageQueueCreate failure\n");
    }

    pImageEventHandler_ = new ImageEventHandler(pCallbackMsgQ_);
    pCamera_->RegisterEvent(*pImageEventHandler_);

    startEventId_ = epicsEventCreate(epicsEventEmpty);

    // launch image read task
    epicsThreadCreate("PointGreyImageTask", 
                      epicsThreadPriorityMedium,
                      epicsThreadGetStackSize(epicsThreadStackMedium),
                      imageGrabTaskC, this);

    // shutdown on exit
    epicsAtExit(c_shutdown, this);

    return;
}


void ADSpinnaker::shutdown(void)
{
    static const char *functionName = "shutdown";
    
    lock();
    exiting_ = 1;
    try {
        pCamera_->UnregisterEvent(*pImageEventHandler_);
        delete pImageEventHandler_;
        pNodeMap_ = 0;
        pCamera_->DeInit();
        pCamera_ = 0;
        camList_.Clear();
        system_->ReleaseInstance();
    }
    catch (Spinnaker::Exception &e) {
      asynPrint(pasynUserSelf, ASYN_TRACE_ERROR, 
          "%s::%s exception %s\n",
          driverName, functionName, e.what());
    }
    unlock();
}

GenICamFeature *ADSpinnaker::createFeature(GenICamFeatureSet *set, 
                                           std::string const & asynName, asynParamType asynType, 
                                           std::string const & featureName, GCFeatureType_t featureType) {
    return new SPFeature(set, asynName, asynType, featureName, featureType);
}

INodeMap *ADSpinnaker::getNodeMap() {
    return pNodeMap_;
}


asynStatus ADSpinnaker::connectCamera(void)
{
    unsigned int numCameras;
    char tempString[100];
    static const char *functionName = "connectCamera";

    try {
        // Retrieve list of cameras from the system
        camList_ = system_->GetCameras();
    
        numCameras = camList_.GetSize();
    
        asynPrint(pasynUserSelf, ASYN_TRACE_WARNING,
            "%s::%s called camList_.GetSize, camList_=%p, numCameras=%d\n",
            driverName, functionName, &camList_, numCameras);
        
        if (numCameras <= 0) {
            asynPrint(pasynUserSelf, ASYN_TRACE_ERROR, 
                "%s:%s: no cameras found\n",
                driverName, functionName);
     
            // Clear camera list before releasing system
            camList_.Clear();
            return asynError;
        }
    
        if (cameraId_ < 1000) {
            asynPrint(pasynUserSelf, ASYN_TRACE_WARNING,
                "%s::%s calling camList_.GetByIndex, camList_=%p\n",
                driverName, functionName, &camList_);
            pCamera_ = camList_.GetByIndex(cameraId_);
        } else { 
            asynPrint(pasynUserSelf, ASYN_TRACE_WARNING,
                "%s::%s calling camList_.GetBySerial, camList_=%p, cameraId_=%d\n",
                driverName, functionName, &camList_, cameraId_);
            char tempString[100];
            sprintf(tempString, "%d", cameraId_);
            std::string tempStdString(tempString);
            pCamera_ = camList_.GetBySerial(tempStdString);
        }
    
        // Initialize camera
        pCamera_->Init();
        
        // Retrieve GenICam nodemap
        pNodeMap_ = &pCamera_->GetNodeMap();
    }

    catch (Spinnaker::Exception &e) {
      asynPrint(pasynUserSelf, ASYN_TRACE_ERROR, 
          "%s::%s exception %s\n",
          driverName, functionName, e.what());
      return asynError;
    }

    epicsSnprintf(tempString, sizeof(tempString), "%d.%d.%d", 
                  DRIVER_VERSION, DRIVER_REVISION, DRIVER_MODIFICATION);
    setStringParam(NDDriverVersion,tempString);
 
/*   
    Utilities::GetLibraryVersion(&version);
    epicsSnprintf(tempString, sizeof(tempString), "%d.%d.%d", version.major, version.minor, version.type);
    asynPrint(pasynUserSelf, ASYN_TRACE_WARNING,
        "%s::%s called Utilities::GetLibraryVersion, version=%s\n",
        driverName, functionName, tempString);
    setStringParam(ADSDKVersion, tempString);


    // Get and set the embedded image info
    asynPrint(pasynUserSelf, ASYN_TRACE_WARNING,
        "%s::%s calling CameraBase::GetEmbeddedImageInfo, &embeddedInfo=%p\n",
        driverName, functionName, &embeddedInfo);
    error = pCameraBase_->GetEmbeddedImageInfo(&embeddedInfo);
    if (checkError(error, functionName, "GetEmbeddedImageInfo")) return asynError;
    // Force the timestamp and frame counter information to be on
    embeddedInfo.timestamp.onOff = true;
    embeddedInfo.frameCounter.onOff = true;
    asynPrint(pasynUserSelf, ASYN_TRACE_WARNING,
        "%s::%s calling CameraBase::SetEmbeddedImageInfo, &embeddedInfo=%p\n",
        driverName, functionName, &embeddedInfo);
    error = pCameraBase_->SetEmbeddedImageInfo(&embeddedInfo);
    if (checkError(error, functionName, "SetEmbeddedImageInfo")) return asynError;
*/    
    return asynSuccess;
}


/** Task to grab images off the camera and send them up to areaDetector
 *
 */

void ADSpinnaker::imageGrabTask()
{
    asynStatus status = asynSuccess;
    int imageCounter;
    int numImages, numImagesCounter;
    int imageMode;
    int arrayCallbacks;
    epicsTimeStamp startTime;
    int acquire;
    static const char *functionName = "imageGrabTask";

    lock();

    while (1) {
        // Is acquisition active? 
        getIntegerParam(ADAcquire, &acquire);
        // If we are not acquiring then wait for a semaphore that is given when acquisition is started 
        if (!acquire) {
            setIntegerParam(ADStatus, ADStatusIdle);
            callParamCallbacks();

            // Wait for a signal that tells this thread that the transmission
            // has started and we can start asking for image buffers...
            asynPrint(pasynUserSelf, ASYN_TRACE_FLOW,
                "%s::%s waiting for acquire to start\n", 
                driverName, functionName);
            // Release the lock while we wait for an event that says acquire has started, then lock again
            unlock();
            epicsEventWait(startEventId_);
            lock();
            asynPrint(pasynUserSelf, ASYN_TRACE_FLOW,
                "%s::%s started!\n", 
                driverName, functionName);
            setIntegerParam(ADNumImagesCounter, 0);
            setIntegerParam(ADAcquire, 1);
        }

        // Get the current time 
        epicsTimeGetCurrent(&startTime);
        // We are now waiting for an image
        setIntegerParam(ADStatus, ADStatusWaiting);
        // Call the callbacks to update any changes
        callParamCallbacks();

        status = grabImage();
        if (status == asynError) {
            // remember to release the NDArray back to the pool now
            // that we are not using it (we didn't get an image...)
            if (pRaw_) pRaw_->release();
            pRaw_ = NULL;
            continue;
        }

        getIntegerParam(NDArrayCounter, &imageCounter);
        getIntegerParam(ADNumImages, &numImages);
        getIntegerParam(ADNumImagesCounter, &numImagesCounter);
        getIntegerParam(ADImageMode, &imageMode);
        getIntegerParam(NDArrayCallbacks, &arrayCallbacks);
        imageCounter++;
        numImagesCounter++;
        setIntegerParam(NDArrayCounter, imageCounter);
        setIntegerParam(ADNumImagesCounter, numImagesCounter);

        if (arrayCallbacks) {
            // Call the NDArray callback
            doCallbacksGenericPointer(pRaw_, NDArrayData, 0);
        }
        // Release the NDArray buffer now that we are done with it.
        // After the callback just above we don't need it anymore
        pRaw_->release();
        pRaw_ = NULL;

        // See if acquisition is done if we are in single or multiple mode
        if ((imageMode == ADImageSingle) || ((imageMode == ADImageMultiple) && (numImagesCounter >= numImages))) {
            setIntegerParam(ADStatus, ADStatusIdle);
            status = stopCapture();
        }
        callParamCallbacks();
    }
}

asynStatus ADSpinnaker::grabImage()
{
    asynStatus status = asynSuccess;
    size_t nRows, nCols;
    NDDataType_t dataType;
    NDColorMode_t colorMode;
    int timeStampMode;
    int uniqueIdMode;
    int convertPixelFormat;
    int numColors;
    size_t dims[3];
    ImageStatus imageStatus;
    PixelFormatEnums pixelFormat;
    int pixelSize;
    size_t dataSize, dataSizePG;
    void *pData;
    int nDims;
    ImagePtr pImage;
    ImagePtr *imagePtrAddr=0;
    static const char *functionName = "grabImage";

    try {
        while(1) {
            unlock();
            int recvSize = pCallbackMsgQ_->receive(&imagePtrAddr, sizeof(imagePtrAddr), 0.1);
            lock();
            if (recvSize == sizeof(imagePtrAddr)) {
                break;
            } else if (recvSize == -1) {
                // Timeout
                int acquire;
                getIntegerParam(ADAcquire, &acquire);
                if (acquire == 0) {
                    return asynError;
                } else {
                    continue;
                }
            } else {
                asynPrint(pasynUserSelf, ASYN_TRACE_ERROR,
                        "%s::%s error receiving from message queue\n",
                        driverName, functionName);
                return asynError;
            }
        }
        pImage = *imagePtrAddr;
        // Delete the ImagePtr that was passed to us
        delete imagePtrAddr;
        imageStatus = pImage->GetImageStatus();
        if (imageStatus != IMAGE_NO_ERROR) {
            asynPrint(pasynUserSelf, ASYN_TRACE_ERROR,
                "%s::%s error GetImageStatus returned %d\n",
                driverName, functionName, imageStatus);
            pImage->Release();
            return asynError;
        } 
        nCols = pImage->GetWidth();
        nRows = pImage->GetHeight();
     
        // Convert the pixel format if requested
        getIntegerParam(SPConvertPixelFormat, &convertPixelFormat);
        if (convertPixelFormat != SPPixelConvertNone) {
            PixelFormatEnums convertedFormat;
            switch (convertPixelFormat) {
                case SPPixelConvertMono8:
                    convertedFormat = PixelFormat_Mono8;
                    break;
                case SPPixelConvertMono16:
                    convertedFormat = PixelFormat_Mono16;
                    break;
                case SPPixelConvertRaw16:
                    convertedFormat = PixelFormat_Raw16;
                    break;
                case SPPixelConvertRGB8:
                    convertedFormat = PixelFormat_RGB8;
                    break;
                case SPPixelConvertRGB16:
                    convertedFormat = PixelFormat_RGB16;
                    break;
                default:
                    asynPrint(pasynUserSelf, ASYN_TRACE_ERROR,
                        "%s::%s Error: Unknown pixel conversion format %d\n",
                        driverName, functionName, convertPixelFormat);
                    convertedFormat = PixelFormat_Mono8;
                    break;
            }
    
            pixelFormat = pImage->GetPixelFormat();
printf("Converting image from format 0x%x to format 0x%x\n", pixelFormat, convertedFormat);
            try {
                ImagePtr pConvertedImage = pImage->Convert(convertedFormat);
                pImage->Release();
                pImage = pConvertedImage;
            }
            catch (Spinnaker::Exception &e) {
                 asynPrint(pasynUserSelf, ASYN_TRACE_ERROR, 
                     "%s::%s exception %s\n",
                 driverName, functionName, e.what());
            }
        }
    
        pixelFormat = pImage->GetPixelFormat();
        switch (pixelFormat) {
            case PixelFormat_Mono8:
            case PixelFormat_Raw8:
                dataType = NDUInt8;
                colorMode = NDColorModeMono;
                numColors = 1;
                pixelSize = 1;
                break;
    
            case PixelFormat_RGB8:
                dataType = NDUInt8;
                colorMode = NDColorModeRGB1;
                numColors = 3;
                pixelSize = 1;
                break;
    
            case PixelFormat_Mono16:
            case PixelFormat_Raw16:
                dataType = NDUInt16;
                colorMode = NDColorModeMono;
                numColors = 1;
                pixelSize = 2;
                break;
    
            case PixelFormat_RGB16:
                dataType = NDUInt16;
                colorMode = NDColorModeRGB1;
                numColors = 3;
                pixelSize = 2;
                break;
    
            default:
                asynPrint(pasynUserSelf, ASYN_TRACE_ERROR,
                    "%s:%s: unsupported pixel format=0x%x\n",
                    driverName, functionName, pixelFormat);
                return asynError;
        }
    
        if (numColors == 1) {
            nDims = 2;
            dims[0] = nCols;
            dims[1] = nRows;
        } else {
            nDims = 3;
            dims[0] = 3;
            dims[1] = nCols;
            dims[2] = nRows;
        }
        dataSize = dims[0] * dims[1] * pixelSize;
        if (nDims == 3) dataSize *= dims[2];
        dataSizePG = pImage->GetBufferSize();
        // Note, we should be testing for equality here.  However, there appears to be a bug in the
        // SDK when images are converted.  When converting from raw8 to mono8, for example, the
        // size returned by GetDataSize is the size of an RGB8 image, not a mono8 image.
        if (dataSize > dataSizePG) {
            asynPrint(pasynUserSelf, ASYN_TRACE_ERROR,
                "%s:%s: data size mismatch: calculated=%lu, reported=%lu\n",
                driverName, functionName, (long)dataSize, (long)dataSizePG);
            //return asynError;
        }
        setIntegerParam(NDArraySizeX, (int)nCols);
        setIntegerParam(NDArraySizeY, (int)nRows);
        setIntegerParam(NDArraySize, (int)dataSize);
        setIntegerParam(NDDataType,dataType);
        if (nDims == 3) {
            colorMode = NDColorModeRGB1;
        } else {
            // If the color mode is currently set to Bayer leave it alone
            getIntegerParam(NDColorMode, (int *)&colorMode);
            if (colorMode != NDColorModeBayer) colorMode = NDColorModeMono;
        }
        setIntegerParam(NDColorMode, colorMode);
    
        pRaw_ = pNDArrayPool->alloc(nDims, dims, dataType, 0, NULL);
        if (!pRaw_) {
            // If we didn't get a valid buffer from the NDArrayPool we must abort
            // the acquisition as we have nowhere to dump the data...
            setIntegerParam(ADStatus, ADStatusAborting);
            callParamCallbacks();
            asynPrint(pasynUserSelf, ASYN_TRACE_ERROR, 
                "%s::%s [%s] ERROR: Serious problem: not enough buffers left! Aborting acquisition!\n",
                driverName, functionName, portName);
            setIntegerParam(ADAcquire, 0);
            return(asynError);
        }
        pData = pImage->GetData();
        if (pData) {
            memcpy(pRaw_->pData, pData, dataSize);
        } else {
            asynPrint(pasynUserSelf, ASYN_TRACE_ERROR, 
                "%s::%s [%s] ERROR: pData is NULL!\n",
                driverName, functionName, portName);
            return asynError;
        }
    
        // Put the frame number into the buffer
        getIntegerParam(SPUniqueIdMode, &uniqueIdMode);
        if (uniqueIdMode == UniqueIdCamera) {
            pRaw_->uniqueId = (int)pImage->GetFrameID();
        } else {
            pRaw_->uniqueId = uniqueId_;
        }
        uniqueId_++;
        updateTimeStamp(&pRaw_->epicsTS);
        getIntegerParam(SPTimeStampMode, &timeStampMode);
        // Set the timestamps in the buffer
        if (timeStampMode == TimeStampCamera) {
            long long timeStamp = pImage->GetTimeStamp();
            pRaw_->timeStamp = timeStamp / 1e9;
        } else {
            pRaw_->timeStamp = pRaw_->epicsTS.secPastEpoch + pRaw_->epicsTS.nsec/1e9;
        }
        try {
            pImage->Release();
        }
        catch (Spinnaker::Exception &e) {
            asynPrint(pasynUserSelf, ASYN_TRACE_ERROR, 
                "%s::%s exception %s\n",
                driverName, functionName, e.what());
        }
        // Get any attributes that have been defined for this driver        
        getAttributes(pRaw_->pAttributeList);
        
        // Change the status to be readout...
        setIntegerParam(ADStatus, ADStatusReadout);
        callParamCallbacks();
    
        pRaw_->pAttributeList->add("ColorMode", "Color mode", NDAttrInt32, &colorMode);
        return status;
    }
    catch (Spinnaker::Exception &e) {
        asynPrint(pasynUserSelf, ASYN_TRACE_ERROR, 
            "%s::%s exception %s\n",
            driverName, functionName, e.what());
        return asynError;
    }
}

asynStatus ADSpinnaker::readEnum(asynUser *pasynUser, char *strings[], int values[], int severities[], 
                               size_t nElements, size_t *nIn)
{
    int function = pasynUser->reason;
    //static const char *functionName = "readEnum";

    // There are a few enums we don't want to autogenerate the values
    if (function == SPConvertPixelFormat) {
        return asynError;
    }
    
    return ADGenICam::readEnum(pasynUser, strings, values, severities, nElements, nIn);
}

asynStatus ADSpinnaker::startCapture()
{
    static const char *functionName = "startCapture";

    // Start the camera transmission...
    setIntegerParam(ADNumImagesCounter, 0);
    setShutter(1);
    try {
        pCamera_->BeginAcquisition();
        epicsEventSignal(startEventId_);
    }
    catch (Spinnaker::Exception &e) {
      asynPrint(pasynUserSelf, ASYN_TRACE_ERROR, 
          "%s::%s exception %s\n",
          driverName, functionName, e.what());
      return asynError;
    }
    return asynSuccess;
}


asynStatus ADSpinnaker::stopCapture()
{
    int status;
    static const char *functionName = "stopCapture";

    setIntegerParam(ADAcquire, 0);
    setShutter(0);
    // Need to wait for the task to set the status to idle
    while (1) {
        getIntegerParam(ADStatus, &status);
        if (status == ADStatusIdle) break;
        unlock();
        epicsThreadSleep(.1);
        lock();
    }
    try {
        pCamera_->EndAcquisition();
        ImagePtr pImage;
        // Need to empty the message queue it could have some images in it
        while(pCallbackMsgQ_->tryReceive(&pImage, sizeof(pImage)) != -1) {
        }
    }
    catch (Spinnaker::Exception &e) {
      asynPrint(pasynUserSelf, ASYN_TRACE_ERROR, 
          "%s::%s exception %s\n",
          driverName, functionName, e.what());
      return asynError;
    }
    return asynSuccess;
}


asynStatus ADSpinnaker::readStatus()
{
    static const char *functionName = "readStatus";

    try {
        const TransportLayerStream& camInfo = pCamera_->TLStream;
//  		  cout << "Stream ID: " << camInfo.StreamID.ToString() << endl;
//	  	  cout << "Stream Type: " << camInfo.StreamType.ToString() << endl;
//		    cout << "Stream Buffer Count: " << camInfo.StreamDefaultBufferCount.ToString() << endl;
//		    cout << "Stream Buffer Handling Mode: " << camInfo.StreamBufferHandlingMode.ToString() << endl;
//        cout << "Stream Packets Received: " << camInfo.GevTotalPacketCount.ToString() << endl;
//        getSPProperty(ADTemperatureActual);
//printf("StreamBufferUnderrunCount = %d\n", (int)camInfo.StreamBufferUnderrunCount.GetValue());
        setIntegerParam(SPBufferUnderrunCount, (int)camInfo.StreamBufferUnderrunCount.GetValue());
        setIntegerParam(SPFailedBufferCount,   (int)camInfo.StreamFailedBufferCount.GetValue());
        if (camInfo.StreamType.GetIntValue() == StreamType_GEV) {
//printf("GeVFailedPacketCount = %d\n", (int)camInfo.GevFailedPacketCount.GetValue());
            setIntegerParam(SPFailedPacketCount,   (int)camInfo.GevFailedPacketCount.GetValue());
//printf("GeVTotalPacketCount = %d\n", (int)camInfo.GevTotalPacketCount.GetValue());
        }
    }
    catch (Spinnaker::Exception &e) {
        asynPrint(pasynUserSelf, ASYN_TRACE_ERROR, 
            "%s::%s exception %s\n",
            driverName, functionName, e.what());
        return asynError;
    }
    callParamCallbacks();
    return asynSuccess;
}

void ADSpinnaker::reportNode(FILE *fp, INodeMap *pNodeMap, gcstring nodeName, int level)
{
    gcstring displayName;
    gcstring value;
    CNodePtr pBase = (CNodePtr)pNodeMap->GetNode(nodeName);
    if (IsAvailable(pBase) && IsReadable(pBase)) {
        displayName = pBase->GetDisplayName();
        switch (pBase->GetPrincipalInterfaceType()) {
            case intfIString: {
                CStringPtr pNode = static_cast<CStringPtr>(pBase);
                value = pNode->GetValue();
                break;
            }
            case intfIInteger: {
                CIntegerPtr pNode = static_cast<CIntegerPtr>(pBase);
                value = pNode->ToString();
                break;
            }
            case intfIFloat: {
                CFloatPtr pNode = static_cast<CFloatPtr>(pBase);
                value = pNode->ToString();
                break;
                }
            case intfIBoolean: {
                CBooleanPtr pNode = static_cast<CBooleanPtr>(pBase);
                value = pNode->ToString();
                break;
                }
            case intfICommand: {
                CCommandPtr pNode = static_cast<CCommandPtr>(pBase);
                value = pNode->GetToolTip();
                break;
                }
            case intfIEnumeration: {
                CEnumerationPtr pNode = static_cast<CEnumerationPtr>(pBase);
                CEnumEntryPtr pEntry = pNode->GetCurrentEntry();
                value = pEntry->GetSymbolic();
                break;
               }
            default:
                value = "Unhandled data type";
                break;
        }
    }
    fprintf(fp, "%s (%s):%s\n", displayName.c_str(), nodeName.c_str(), value.c_str());
}


/** Print out a report; calls ADGenICam::report to get base class report as well.
  * \param[in] fp File pointer to write output to
  * \param[in] details Level of detail desired.  If >1 prints information about 
               supported video formats and modes, etc.
 */

void ADSpinnaker::report(FILE *fp, int details)
{
    int numCameras;
    int i;
    static const char *functionName = "report";

    try {    
        numCameras = camList_.GetSize();
        fprintf(fp, "\nNumber of cameras detected: %d\n", numCameras);
        if (details <1) return;
        for (i=0; i<numCameras; i++) {
            CameraPtr pCamera;
            pCamera = camList_.GetByIndex(i);
            INodeMap *pNodeMap = &pCamera->GetTLDeviceNodeMap();
    
            fprintf(fp, "Camera %d\n", i);
            reportNode(fp, pNodeMap, "DeviceVendorName", 1);
            reportNode(fp, pNodeMap, "DeviceModelName", 1);
            reportNode(fp, pNodeMap, "DeviceSerialNumber", 1);
            reportNode(fp, pNodeMap, "DeviceVersion", 1);
            reportNode(fp, pNodeMap, "DeviceType", 1);
        }
    }
    catch (Spinnaker::Exception &e) {
      asynPrint(pasynUserSelf, ASYN_TRACE_ERROR, 
          "%s::%s exception %s\n",
          driverName, functionName, e.what());
    }
    
    ADGenICam::report(fp, details);
    return;
}

static const iocshArg configArg0 = {"Port name", iocshArgString};
static const iocshArg configArg1 = {"cameraId", iocshArgInt};
static const iocshArg configArg2 = {"traceMask", iocshArgInt};
static const iocshArg configArg3 = {"memoryChannel", iocshArgInt};
static const iocshArg configArg4 = {"maxMemory", iocshArgInt};
static const iocshArg configArg5 = {"priority", iocshArgInt};
static const iocshArg configArg6 = {"stackSize", iocshArgInt};
static const iocshArg * const configArgs[] = {&configArg0,
                                              &configArg1,
                                              &configArg2,
                                              &configArg3,
                                              &configArg4,
                                              &configArg5,
                                              &configArg6};
static const iocshFuncDef configADSpinnaker = {"ADSpinnakerConfig", 7, configArgs};
static void configCallFunc(const iocshArgBuf *args)
{
    ADSpinnakerConfig(args[0].sval, args[1].ival, args[2].ival, 
                      args[3].ival, args[4].ival, args[5].ival,
                      args[6].ival);
}


static void ADSpinnakerRegister(void)
{
    iocshRegister(&configADSpinnaker, configCallFunc);
}

extern "C" {
epicsExportRegistrar(ADSpinnakerRegister);
}

