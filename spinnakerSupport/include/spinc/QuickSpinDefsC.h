//=============================================================================
// Copyright (c) 2001-2020 FLIR Systems, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of FLIR
// Integrated Imaging Solutions, Inc. ("Confidential Information"). You
// shall not disclose such Confidential Information and shall use it only in
// accordance with the terms of the license agreement you entered into
// with FLIR Integrated Imaging Solutions, Inc. (FLIR).
//
// FLIR MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT. FLIR SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================
   
/* Auto-generated file. Do not modify. */

#ifndef FLIR_SPINNAKER_QUICKSPINDEFS_C_H
#define FLIR_SPINNAKER_QUICKSPINDEFS_C_H

#include "SpinnakerGenApiDefsC.h"

typedef spinNodeHandle quickSpinStringNode;
typedef spinNodeHandle quickSpinIntegerNode;
typedef spinNodeHandle quickSpinFloatNode;
typedef spinNodeHandle quickSpinBooleanNode;
typedef spinNodeHandle quickSpinEnumerationNode;
typedef spinNodeHandle quickSpinCommandNode;
typedef spinNodeHandle quickSpinRegisterNode;

typedef struct _quickSpin
{
    quickSpinIntegerNode LUTIndex;
    quickSpinBooleanNode LUTEnable;
    quickSpinIntegerNode LUTValue;
    quickSpinEnumerationNode LUTSelector;
    quickSpinFloatNode ExposureTime;
    quickSpinCommandNode AcquisitionStop;
    quickSpinFloatNode AcquisitionResultingFrameRate;
    quickSpinFloatNode AcquisitionLineRate;
    quickSpinCommandNode AcquisitionStart;
    quickSpinCommandNode TriggerSoftware;
    quickSpinEnumerationNode ExposureMode;
    quickSpinEnumerationNode AcquisitionMode;
    quickSpinIntegerNode AcquisitionFrameCount;
    quickSpinEnumerationNode TriggerSource;
    quickSpinEnumerationNode TriggerActivation;
    quickSpinEnumerationNode SensorShutterMode;
    quickSpinFloatNode TriggerDelay;
    quickSpinEnumerationNode TriggerMode;
    quickSpinFloatNode AcquisitionFrameRate;
    quickSpinEnumerationNode TriggerOverlap;
    quickSpinEnumerationNode TriggerSelector;
    quickSpinBooleanNode AcquisitionFrameRateEnable;
    quickSpinEnumerationNode ExposureAuto;
    quickSpinIntegerNode AcquisitionBurstFrameCount;
    quickSpinIntegerNode EventTest;
    quickSpinIntegerNode EventTestTimestamp;
    quickSpinIntegerNode EventExposureEndFrameID;
    quickSpinIntegerNode EventExposureEnd;
    quickSpinIntegerNode EventExposureEndTimestamp;
    quickSpinIntegerNode EventError;
    quickSpinIntegerNode EventErrorTimestamp;
    quickSpinIntegerNode EventErrorCode;
    quickSpinIntegerNode EventErrorFrameID;
    quickSpinEnumerationNode EventSelector;
    quickSpinBooleanNode EventSerialReceiveOverflow;
    quickSpinIntegerNode EventSerialPortReceive;
    quickSpinIntegerNode EventSerialPortReceiveTimestamp;
    quickSpinStringNode EventSerialData;
    quickSpinIntegerNode EventSerialDataLength;
    quickSpinEnumerationNode EventNotification;
    quickSpinIntegerNode LogicBlockLUTRowIndex;
    quickSpinEnumerationNode LogicBlockSelector;
    quickSpinEnumerationNode LogicBlockLUTInputActivation;
    quickSpinEnumerationNode LogicBlockLUTInputSelector;
    quickSpinEnumerationNode LogicBlockLUTInputSource;
    quickSpinBooleanNode LogicBlockLUTOutputValue;
    quickSpinIntegerNode LogicBlockLUTOutputValueAll;
    quickSpinEnumerationNode LogicBlockLUTSelector;
    quickSpinFloatNode ColorTransformationValue;
    quickSpinBooleanNode ColorTransformationEnable;
    quickSpinEnumerationNode ColorTransformationSelector;
    quickSpinEnumerationNode RgbTransformLightSource;
    quickSpinFloatNode Saturation;
    quickSpinBooleanNode SaturationEnable;
    quickSpinEnumerationNode ColorTransformationValueSelector;
    quickSpinIntegerNode TimestampLatchValue;
    quickSpinCommandNode TimestampReset;
    quickSpinStringNode DeviceUserID;
    quickSpinFloatNode DeviceTemperature;
    quickSpinIntegerNode MaxDeviceResetTime;
    quickSpinIntegerNode DeviceTLVersionMinor;
    quickSpinStringNode DeviceSerialNumber;
    quickSpinStringNode DeviceVendorName;
    quickSpinEnumerationNode DeviceRegistersEndianness;
    quickSpinStringNode DeviceManufacturerInfo;
    quickSpinIntegerNode DeviceLinkSpeed;
    quickSpinIntegerNode LinkUptime;
    quickSpinIntegerNode DeviceEventChannelCount;
    quickSpinCommandNode TimestampLatch;
    quickSpinEnumerationNode DeviceScanType;
    quickSpinCommandNode DeviceReset;
    quickSpinEnumerationNode DeviceCharacterSet;
    quickSpinIntegerNode DeviceLinkThroughputLimit;
    quickSpinStringNode DeviceFirmwareVersion;
    quickSpinIntegerNode DeviceStreamChannelCount;
    quickSpinEnumerationNode DeviceTLType;
    quickSpinStringNode DeviceVersion;
    quickSpinEnumerationNode DevicePowerSupplySelector;
    quickSpinStringNode SensorDescription;
    quickSpinStringNode DeviceModelName;
    quickSpinIntegerNode DeviceTLVersionMajor;
    quickSpinEnumerationNode DeviceTemperatureSelector;
    quickSpinIntegerNode EnumerationCount;
    quickSpinFloatNode PowerSupplyCurrent;
    quickSpinStringNode DeviceID;
    quickSpinIntegerNode DeviceUptime;
    quickSpinIntegerNode DeviceLinkCurrentThroughput;
    quickSpinIntegerNode DeviceMaxThroughput;
    quickSpinCommandNode FactoryReset;
    quickSpinFloatNode PowerSupplyVoltage;
    quickSpinEnumerationNode DeviceIndicatorMode;
    quickSpinFloatNode DeviceLinkBandwidthReserve;
    quickSpinIntegerNode AasRoiOffsetY;
    quickSpinIntegerNode AasRoiOffsetX;
    quickSpinEnumerationNode AutoExposureControlPriority;
    quickSpinFloatNode BalanceWhiteAutoLowerLimit;
    quickSpinFloatNode BalanceWhiteAutoDamping;
    quickSpinIntegerNode AasRoiHeight;
    quickSpinFloatNode AutoExposureGreyValueUpperLimit;
    quickSpinFloatNode AutoExposureTargetGreyValue;
    quickSpinFloatNode AutoExposureGainLowerLimit;
    quickSpinFloatNode AutoExposureGreyValueLowerLimit;
    quickSpinEnumerationNode AutoExposureMeteringMode;
    quickSpinFloatNode AutoExposureExposureTimeUpperLimit;
    quickSpinFloatNode AutoExposureGainUpperLimit;
    quickSpinFloatNode AutoExposureControlLoopDamping;
    quickSpinFloatNode AutoExposureEVCompensation;
    quickSpinFloatNode AutoExposureExposureTimeLowerLimit;
    quickSpinEnumerationNode BalanceWhiteAutoProfile;
    quickSpinEnumerationNode AutoAlgorithmSelector;
    quickSpinEnumerationNode AutoExposureTargetGreyValueAuto;
    quickSpinBooleanNode AasRoiEnable;
    quickSpinEnumerationNode AutoExposureLightingMode;
    quickSpinIntegerNode AasRoiWidth;
    quickSpinFloatNode BalanceWhiteAutoUpperLimit;
    quickSpinIntegerNode LinkErrorCount;
    quickSpinBooleanNode GevCurrentIPConfigurationDHCP;
    quickSpinIntegerNode GevInterfaceSelector;
    quickSpinIntegerNode GevSCPD;
    quickSpinIntegerNode GevTimestampTickFrequency;
    quickSpinIntegerNode GevSCPSPacketSize;
    quickSpinIntegerNode GevCurrentDefaultGateway;
    quickSpinBooleanNode GevSCCFGUnconditionalStreaming;
    quickSpinIntegerNode GevMCTT;
    quickSpinBooleanNode GevSCPSDoNotFragment;
    quickSpinIntegerNode GevCurrentSubnetMask;
    quickSpinIntegerNode GevStreamChannelSelector;
    quickSpinIntegerNode GevCurrentIPAddress;
    quickSpinIntegerNode GevMCSP;
    quickSpinIntegerNode GevGVCPPendingTimeout;
    quickSpinEnumerationNode GevIEEE1588Status;
    quickSpinStringNode GevFirstURL;
    quickSpinIntegerNode GevMACAddress;
    quickSpinIntegerNode GevPersistentSubnetMask;
    quickSpinIntegerNode GevMCPHostPort;
    quickSpinIntegerNode GevSCPHostPort;
    quickSpinBooleanNode GevGVCPPendingAck;
    quickSpinIntegerNode GevSCPInterfaceIndex;
    quickSpinBooleanNode GevSupportedOption;
    quickSpinEnumerationNode GevIEEE1588Mode;
    quickSpinBooleanNode GevCurrentIPConfigurationLLA;
    quickSpinIntegerNode GevSCSP;
    quickSpinBooleanNode GevIEEE1588;
    quickSpinBooleanNode GevSCCFGExtendedChunkData;
    quickSpinIntegerNode GevPersistentIPAddress;
    quickSpinBooleanNode GevCurrentIPConfigurationPersistentIP;
    quickSpinEnumerationNode GevIEEE1588ClockAccuracy;
    quickSpinIntegerNode GevHeartbeatTimeout;
    quickSpinIntegerNode GevPersistentDefaultGateway;
    quickSpinEnumerationNode GevCCP;
    quickSpinIntegerNode GevMCDA;
    quickSpinIntegerNode GevSCDA;
    quickSpinIntegerNode GevSCPDirection;
    quickSpinBooleanNode GevSCPSFireTestPacket;
    quickSpinStringNode GevSecondURL;
    quickSpinEnumerationNode GevSupportedOptionSelector;
    quickSpinBooleanNode GevGVCPHeartbeatDisable;
    quickSpinIntegerNode GevMCRC;
    quickSpinBooleanNode GevSCPSBigEndian;
    quickSpinIntegerNode GevNumberOfInterfaces;
    quickSpinIntegerNode TLParamsLocked;
    quickSpinIntegerNode PayloadSize;
    quickSpinIntegerNode PacketResendRequestCount;
    quickSpinBooleanNode SharpeningEnable;
    quickSpinEnumerationNode BlackLevelSelector;
    quickSpinBooleanNode GammaEnable;
    quickSpinBooleanNode SharpeningAuto;
    quickSpinBooleanNode BlackLevelClampingEnable;
    quickSpinFloatNode BalanceRatio;
    quickSpinEnumerationNode BalanceWhiteAuto;
    quickSpinFloatNode SharpeningThreshold;
    quickSpinEnumerationNode GainAuto;
    quickSpinFloatNode Sharpening;
    quickSpinFloatNode Gain;
    quickSpinEnumerationNode BalanceRatioSelector;
    quickSpinEnumerationNode GainSelector;
    quickSpinFloatNode BlackLevel;
    quickSpinIntegerNode BlackLevelRaw;
    quickSpinFloatNode Gamma;
    quickSpinIntegerNode DefectTableIndex;
    quickSpinCommandNode DefectTableFactoryRestore;
    quickSpinIntegerNode DefectTableCoordinateY;
    quickSpinCommandNode DefectTableSave;
    quickSpinEnumerationNode DefectCorrectionMode;
    quickSpinIntegerNode DefectTableCoordinateX;
    quickSpinIntegerNode DefectTablePixelCount;
    quickSpinBooleanNode DefectCorrectStaticEnable;
    quickSpinCommandNode DefectTableApply;
    quickSpinBooleanNode UserSetFeatureEnable;
    quickSpinCommandNode UserSetSave;
    quickSpinEnumerationNode UserSetSelector;
    quickSpinCommandNode UserSetLoad;
    quickSpinEnumerationNode UserSetDefault;
    quickSpinEnumerationNode SerialPortBaudRate;
    quickSpinIntegerNode SerialPortDataBits;
    quickSpinEnumerationNode SerialPortParity;
    quickSpinIntegerNode SerialTransmitQueueMaxCharacterCount;
    quickSpinIntegerNode SerialReceiveQueueCurrentCharacterCount;
    quickSpinEnumerationNode SerialPortSelector;
    quickSpinEnumerationNode SerialPortStopBits;
    quickSpinCommandNode SerialReceiveQueueClear;
    quickSpinIntegerNode SerialReceiveFramingErrorCount;
    quickSpinIntegerNode SerialTransmitQueueCurrentCharacterCount;
    quickSpinIntegerNode SerialReceiveParityErrorCount;
    quickSpinEnumerationNode SerialPortSource;
    quickSpinIntegerNode SerialReceiveQueueMaxCharacterCount;
    quickSpinIntegerNode SequencerSetStart;
    quickSpinEnumerationNode SequencerMode;
    quickSpinEnumerationNode SequencerConfigurationValid;
    quickSpinEnumerationNode SequencerSetValid;
    quickSpinIntegerNode SequencerSetSelector;
    quickSpinEnumerationNode SequencerTriggerActivation;
    quickSpinEnumerationNode SequencerConfigurationMode;
    quickSpinCommandNode SequencerSetSave;
    quickSpinEnumerationNode SequencerTriggerSource;
    quickSpinIntegerNode SequencerSetActive;
    quickSpinIntegerNode SequencerSetNext;
    quickSpinCommandNode SequencerSetLoad;
    quickSpinIntegerNode SequencerPathSelector;
    quickSpinBooleanNode SequencerFeatureEnable;
    quickSpinIntegerNode TransferBlockCount;
    quickSpinCommandNode TransferStart;
    quickSpinIntegerNode TransferQueueMaxBlockCount;
    quickSpinIntegerNode TransferQueueCurrentBlockCount;
    quickSpinEnumerationNode TransferQueueMode;
    quickSpinEnumerationNode TransferOperationMode;
    quickSpinCommandNode TransferStop;
    quickSpinIntegerNode TransferQueueOverflowCount;
    quickSpinEnumerationNode TransferControlMode;
    quickSpinFloatNode ChunkBlackLevel;
    quickSpinIntegerNode ChunkFrameID;
    quickSpinStringNode ChunkSerialData;
    quickSpinFloatNode ChunkExposureTime;
    quickSpinBooleanNode ChunkSerialReceiveOverflow;
    quickSpinIntegerNode ChunkTimestamp;
    quickSpinBooleanNode ChunkModeActive;
    quickSpinIntegerNode ChunkExposureEndLineStatusAll;
    quickSpinEnumerationNode ChunkGainSelector;
    quickSpinEnumerationNode ChunkSelector;
    quickSpinEnumerationNode ChunkBlackLevelSelector;
    quickSpinIntegerNode ChunkWidth;
    quickSpinIntegerNode ChunkImage;
    quickSpinIntegerNode ChunkHeight;
    quickSpinEnumerationNode ChunkPixelFormat;
    quickSpinFloatNode ChunkGain;
    quickSpinIntegerNode ChunkSequencerSetActive;
    quickSpinIntegerNode ChunkCRC;
    quickSpinIntegerNode ChunkOffsetX;
    quickSpinIntegerNode ChunkOffsetY;
    quickSpinBooleanNode ChunkEnable;
    quickSpinIntegerNode ChunkSerialDataLength;
    quickSpinIntegerNode FileAccessOffset;
    quickSpinIntegerNode FileAccessLength;
    quickSpinEnumerationNode FileOperationStatus;
    quickSpinCommandNode FileOperationExecute;
    quickSpinEnumerationNode FileOpenMode;
    quickSpinIntegerNode FileOperationResult;
    quickSpinEnumerationNode FileOperationSelector;
    quickSpinEnumerationNode FileSelector;
    quickSpinIntegerNode FileSize;
    quickSpinEnumerationNode BinningSelector;
    quickSpinIntegerNode PixelDynamicRangeMin;
    quickSpinIntegerNode PixelDynamicRangeMax;
    quickSpinIntegerNode OffsetY;
    quickSpinIntegerNode BinningHorizontal;
    quickSpinIntegerNode Width;
    quickSpinEnumerationNode TestPatternGeneratorSelector;
    quickSpinFloatNode CompressionRatio;
    quickSpinBooleanNode ReverseX;
    quickSpinBooleanNode ReverseY;
    quickSpinEnumerationNode TestPattern;
    quickSpinEnumerationNode PixelColorFilter;
    quickSpinIntegerNode WidthMax;
    quickSpinEnumerationNode AdcBitDepth;
    quickSpinIntegerNode BinningVertical;
    quickSpinEnumerationNode DecimationHorizontalMode;
    quickSpinEnumerationNode BinningVerticalMode;
    quickSpinIntegerNode OffsetX;
    quickSpinIntegerNode HeightMax;
    quickSpinIntegerNode DecimationHorizontal;
    quickSpinEnumerationNode PixelSize;
    quickSpinIntegerNode SensorHeight;
    quickSpinEnumerationNode DecimationSelector;
    quickSpinBooleanNode IspEnable;
    quickSpinBooleanNode AdaptiveCompressionEnable;
    quickSpinEnumerationNode ImageCompressionMode;
    quickSpinIntegerNode DecimationVertical;
    quickSpinIntegerNode Height;
    quickSpinEnumerationNode BinningHorizontalMode;
    quickSpinEnumerationNode PixelFormat;
    quickSpinIntegerNode SensorWidth;
    quickSpinEnumerationNode DecimationVerticalMode;
    quickSpinCommandNode TestEventGenerate;
    quickSpinCommandNode TriggerEventTest;
    quickSpinIntegerNode GuiXmlManifestAddress;
    quickSpinIntegerNode Test0001;
    quickSpinBooleanNode V3_3Enable;
    quickSpinEnumerationNode LineMode;
    quickSpinEnumerationNode LineSource;
    quickSpinEnumerationNode LineInputFilterSelector;
    quickSpinBooleanNode UserOutputValue;
    quickSpinIntegerNode UserOutputValueAll;
    quickSpinEnumerationNode UserOutputSelector;
    quickSpinBooleanNode LineStatus;
    quickSpinEnumerationNode LineFormat;
    quickSpinIntegerNode LineStatusAll;
    quickSpinEnumerationNode LineSelector;
    quickSpinEnumerationNode ExposureActiveMode;
    quickSpinBooleanNode LineInverter;
    quickSpinFloatNode LineFilterWidth;
    quickSpinEnumerationNode CounterTriggerActivation;
    quickSpinIntegerNode CounterValue;
    quickSpinEnumerationNode CounterSelector;
    quickSpinIntegerNode CounterValueAtReset;
    quickSpinEnumerationNode CounterStatus;
    quickSpinEnumerationNode CounterTriggerSource;
    quickSpinIntegerNode CounterDelay;
    quickSpinEnumerationNode CounterResetSource;
    quickSpinEnumerationNode CounterEventSource;
    quickSpinEnumerationNode CounterEventActivation;
    quickSpinIntegerNode CounterDuration;
    quickSpinEnumerationNode CounterResetActivation;
    quickSpinEnumerationNode DeviceType;
    quickSpinStringNode DeviceFamilyName;
    quickSpinIntegerNode DeviceSFNCVersionMajor;
    quickSpinIntegerNode DeviceSFNCVersionMinor;
    quickSpinIntegerNode DeviceSFNCVersionSubMinor;
    quickSpinIntegerNode DeviceManifestEntrySelector;
    quickSpinIntegerNode DeviceManifestXMLMajorVersion;
    quickSpinIntegerNode DeviceManifestXMLMinorVersion;
    quickSpinIntegerNode DeviceManifestXMLSubMinorVersion;
    quickSpinIntegerNode DeviceManifestSchemaMajorVersion;
    quickSpinIntegerNode DeviceManifestSchemaMinorVersion;
    quickSpinStringNode DeviceManifestPrimaryURL;
    quickSpinStringNode DeviceManifestSecondaryURL;
    quickSpinIntegerNode DeviceTLVersionSubMinor;
    quickSpinIntegerNode DeviceGenCPVersionMajor;
    quickSpinIntegerNode DeviceGenCPVersionMinor;
    quickSpinIntegerNode DeviceConnectionSelector;
    quickSpinIntegerNode DeviceConnectionSpeed;
    quickSpinEnumerationNode DeviceConnectionStatus;
    quickSpinIntegerNode DeviceLinkSelector;
    quickSpinEnumerationNode DeviceLinkThroughputLimitMode;
    quickSpinIntegerNode DeviceLinkConnectionCount;
    quickSpinEnumerationNode DeviceLinkHeartbeatMode;
    quickSpinFloatNode DeviceLinkHeartbeatTimeout;
    quickSpinFloatNode DeviceLinkCommandTimeout;
    quickSpinIntegerNode DeviceStreamChannelSelector;
    quickSpinEnumerationNode DeviceStreamChannelType;
    quickSpinIntegerNode DeviceStreamChannelLink;
    quickSpinEnumerationNode DeviceStreamChannelEndianness;
    quickSpinIntegerNode DeviceStreamChannelPacketSize;
    quickSpinCommandNode DeviceFeaturePersistenceStart;
    quickSpinCommandNode DeviceFeaturePersistenceEnd;
    quickSpinCommandNode DeviceRegistersStreamingStart;
    quickSpinCommandNode DeviceRegistersStreamingEnd;
    quickSpinCommandNode DeviceRegistersCheck;
    quickSpinBooleanNode DeviceRegistersValid;
    quickSpinEnumerationNode DeviceClockSelector;
    quickSpinFloatNode DeviceClockFrequency;
    quickSpinEnumerationNode DeviceSerialPortSelector;
    quickSpinEnumerationNode DeviceSerialPortBaudRate;
    quickSpinIntegerNode Timestamp;
    quickSpinEnumerationNode SensorTaps;
    quickSpinEnumerationNode SensorDigitizationTaps;
    quickSpinEnumerationNode RegionSelector;
    quickSpinEnumerationNode RegionMode;
    quickSpinEnumerationNode RegionDestination;
    quickSpinEnumerationNode ImageComponentSelector;
    quickSpinBooleanNode ImageComponentEnable;
    quickSpinIntegerNode LinePitch;
    quickSpinEnumerationNode PixelFormatInfoSelector;
    quickSpinIntegerNode PixelFormatInfoID;
    quickSpinEnumerationNode Deinterlacing;
    quickSpinEnumerationNode ImageCompressionRateOption;
    quickSpinIntegerNode ImageCompressionQuality;
    quickSpinFloatNode ImageCompressionBitrate;
    quickSpinEnumerationNode ImageCompressionJPEGFormatOption;
    quickSpinCommandNode AcquisitionAbort;
    quickSpinCommandNode AcquisitionArm;
    quickSpinEnumerationNode AcquisitionStatusSelector;
    quickSpinBooleanNode AcquisitionStatus;
    quickSpinIntegerNode TriggerDivider;
    quickSpinIntegerNode TriggerMultiplier;
    quickSpinEnumerationNode ExposureTimeMode;
    quickSpinEnumerationNode ExposureTimeSelector;
    quickSpinEnumerationNode GainAutoBalance;
    quickSpinEnumerationNode BlackLevelAuto;
    quickSpinEnumerationNode BlackLevelAutoBalance;
    quickSpinEnumerationNode WhiteClipSelector;
    quickSpinFloatNode WhiteClip;
    quickSpinRegisterNode LUTValueAll;
    quickSpinIntegerNode UserOutputValueAllMask;
    quickSpinCommandNode CounterReset;
    quickSpinEnumerationNode TimerSelector;
    quickSpinFloatNode TimerDuration;
    quickSpinFloatNode TimerDelay;
    quickSpinCommandNode TimerReset;
    quickSpinFloatNode TimerValue;
    quickSpinEnumerationNode TimerStatus;
    quickSpinEnumerationNode TimerTriggerSource;
    quickSpinEnumerationNode TimerTriggerActivation;
    quickSpinEnumerationNode EncoderSelector;
    quickSpinEnumerationNode EncoderSourceA;
    quickSpinEnumerationNode EncoderSourceB;
    quickSpinEnumerationNode EncoderMode;
    quickSpinIntegerNode EncoderDivider;
    quickSpinEnumerationNode EncoderOutputMode;
    quickSpinEnumerationNode EncoderStatus;
    quickSpinFloatNode EncoderTimeout;
    quickSpinEnumerationNode EncoderResetSource;
    quickSpinEnumerationNode EncoderResetActivation;
    quickSpinCommandNode EncoderReset;
    quickSpinIntegerNode EncoderValue;
    quickSpinIntegerNode EncoderValueAtReset;
    quickSpinEnumerationNode SoftwareSignalSelector;
    quickSpinCommandNode SoftwareSignalPulse;
    quickSpinEnumerationNode ActionUnconditionalMode;
    quickSpinIntegerNode ActionDeviceKey;
    quickSpinIntegerNode ActionQueueSize;
    quickSpinIntegerNode ActionSelector;
    quickSpinIntegerNode ActionGroupMask;
    quickSpinIntegerNode ActionGroupKey;
    quickSpinIntegerNode EventAcquisitionTrigger;
    quickSpinIntegerNode EventAcquisitionTriggerTimestamp;
    quickSpinIntegerNode EventAcquisitionTriggerFrameID;
    quickSpinIntegerNode EventAcquisitionStart;
    quickSpinIntegerNode EventAcquisitionStartTimestamp;
    quickSpinIntegerNode EventAcquisitionStartFrameID;
    quickSpinIntegerNode EventAcquisitionEnd;
    quickSpinIntegerNode EventAcquisitionEndTimestamp;
    quickSpinIntegerNode EventAcquisitionEndFrameID;
    quickSpinIntegerNode EventAcquisitionTransferStart;
    quickSpinIntegerNode EventAcquisitionTransferStartTimestamp;
    quickSpinIntegerNode EventAcquisitionTransferStartFrameID;
    quickSpinIntegerNode EventAcquisitionTransferEnd;
    quickSpinIntegerNode EventAcquisitionTransferEndTimestamp;
    quickSpinIntegerNode EventAcquisitionTransferEndFrameID;
    quickSpinIntegerNode EventAcquisitionError;
    quickSpinIntegerNode EventAcquisitionErrorTimestamp;
    quickSpinIntegerNode EventAcquisitionErrorFrameID;
    quickSpinIntegerNode EventFrameTrigger;
    quickSpinIntegerNode EventFrameTriggerTimestamp;
    quickSpinIntegerNode EventFrameTriggerFrameID;
    quickSpinIntegerNode EventFrameStart;
    quickSpinIntegerNode EventFrameStartTimestamp;
    quickSpinIntegerNode EventFrameStartFrameID;
    quickSpinIntegerNode EventFrameEnd;
    quickSpinIntegerNode EventFrameEndTimestamp;
    quickSpinIntegerNode EventFrameEndFrameID;
    quickSpinIntegerNode EventFrameBurstStart;
    quickSpinIntegerNode EventFrameBurstStartTimestamp;
    quickSpinIntegerNode EventFrameBurstStartFrameID;
    quickSpinIntegerNode EventFrameBurstEnd;
    quickSpinIntegerNode EventFrameBurstEndTimestamp;
    quickSpinIntegerNode EventFrameBurstEndFrameID;
    quickSpinIntegerNode EventFrameTransferStart;
    quickSpinIntegerNode EventFrameTransferStartTimestamp;
    quickSpinIntegerNode EventFrameTransferStartFrameID;
    quickSpinIntegerNode EventFrameTransferEnd;
    quickSpinIntegerNode EventFrameTransferEndTimestamp;
    quickSpinIntegerNode EventFrameTransferEndFrameID;
    quickSpinIntegerNode EventExposureStart;
    quickSpinIntegerNode EventExposureStartTimestamp;
    quickSpinIntegerNode EventExposureStartFrameID;
    quickSpinIntegerNode EventStream0TransferStart;
    quickSpinIntegerNode EventStream0TransferStartTimestamp;
    quickSpinIntegerNode EventStream0TransferStartFrameID;
    quickSpinIntegerNode EventStream0TransferEnd;
    quickSpinIntegerNode EventStream0TransferEndTimestamp;
    quickSpinIntegerNode EventStream0TransferEndFrameID;
    quickSpinIntegerNode EventStream0TransferPause;
    quickSpinIntegerNode EventStream0TransferPauseTimestamp;
    quickSpinIntegerNode EventStream0TransferPauseFrameID;
    quickSpinIntegerNode EventStream0TransferResume;
    quickSpinIntegerNode EventStream0TransferResumeTimestamp;
    quickSpinIntegerNode EventStream0TransferResumeFrameID;
    quickSpinIntegerNode EventStream0TransferBlockStart;
    quickSpinIntegerNode EventStream0TransferBlockStartTimestamp;
    quickSpinIntegerNode EventStream0TransferBlockStartFrameID;
    quickSpinIntegerNode EventStream0TransferBlockEnd;
    quickSpinIntegerNode EventStream0TransferBlockEndTimestamp;
    quickSpinIntegerNode EventStream0TransferBlockEndFrameID;
    quickSpinIntegerNode EventStream0TransferBlockTrigger;
    quickSpinIntegerNode EventStream0TransferBlockTriggerTimestamp;
    quickSpinIntegerNode EventStream0TransferBlockTriggerFrameID;
    quickSpinIntegerNode EventStream0TransferBurstStart;
    quickSpinIntegerNode EventStream0TransferBurstStartTimestamp;
    quickSpinIntegerNode EventStream0TransferBurstStartFrameID;
    quickSpinIntegerNode EventStream0TransferBurstEnd;
    quickSpinIntegerNode EventStream0TransferBurstEndTimestamp;
    quickSpinIntegerNode EventStream0TransferBurstEndFrameID;
    quickSpinIntegerNode EventStream0TransferOverflow;
    quickSpinIntegerNode EventStream0TransferOverflowTimestamp;
    quickSpinIntegerNode EventStream0TransferOverflowFrameID;
    quickSpinIntegerNode EventSequencerSetChange;
    quickSpinIntegerNode EventSequencerSetChangeTimestamp;
    quickSpinIntegerNode EventSequencerSetChangeFrameID;
    quickSpinIntegerNode EventCounter0Start;
    quickSpinIntegerNode EventCounter0StartTimestamp;
    quickSpinIntegerNode EventCounter0StartFrameID;
    quickSpinIntegerNode EventCounter1Start;
    quickSpinIntegerNode EventCounter1StartTimestamp;
    quickSpinIntegerNode EventCounter1StartFrameID;
    quickSpinIntegerNode EventCounter0End;
    quickSpinIntegerNode EventCounter0EndTimestamp;
    quickSpinIntegerNode EventCounter0EndFrameID;
    quickSpinIntegerNode EventCounter1End;
    quickSpinIntegerNode EventCounter1EndTimestamp;
    quickSpinIntegerNode EventCounter1EndFrameID;
    quickSpinIntegerNode EventTimer0Start;
    quickSpinIntegerNode EventTimer0StartTimestamp;
    quickSpinIntegerNode EventTimer0StartFrameID;
    quickSpinIntegerNode EventTimer1Start;
    quickSpinIntegerNode EventTimer1StartTimestamp;
    quickSpinIntegerNode EventTimer1StartFrameID;
    quickSpinIntegerNode EventTimer0End;
    quickSpinIntegerNode EventTimer0EndTimestamp;
    quickSpinIntegerNode EventTimer0EndFrameID;
    quickSpinIntegerNode EventTimer1End;
    quickSpinIntegerNode EventTimer1EndTimestamp;
    quickSpinIntegerNode EventTimer1EndFrameID;
    quickSpinIntegerNode EventEncoder0Stopped;
    quickSpinIntegerNode EventEncoder0StoppedTimestamp;
    quickSpinIntegerNode EventEncoder0StoppedFrameID;
    quickSpinIntegerNode EventEncoder1Stopped;
    quickSpinIntegerNode EventEncoder1StoppedTimestamp;
    quickSpinIntegerNode EventEncoder1StoppedFrameID;
    quickSpinIntegerNode EventEncoder0Restarted;
    quickSpinIntegerNode EventEncoder0RestartedTimestamp;
    quickSpinIntegerNode EventEncoder0RestartedFrameID;
    quickSpinIntegerNode EventEncoder1Restarted;
    quickSpinIntegerNode EventEncoder1RestartedTimestamp;
    quickSpinIntegerNode EventEncoder1RestartedFrameID;
    quickSpinIntegerNode EventLine0RisingEdge;
    quickSpinIntegerNode EventLine0RisingEdgeTimestamp;
    quickSpinIntegerNode EventLine0RisingEdgeFrameID;
    quickSpinIntegerNode EventLine1RisingEdge;
    quickSpinIntegerNode EventLine1RisingEdgeTimestamp;
    quickSpinIntegerNode EventLine1RisingEdgeFrameID;
    quickSpinIntegerNode EventLine0FallingEdge;
    quickSpinIntegerNode EventLine0FallingEdgeTimestamp;
    quickSpinIntegerNode EventLine0FallingEdgeFrameID;
    quickSpinIntegerNode EventLine1FallingEdge;
    quickSpinIntegerNode EventLine1FallingEdgeTimestamp;
    quickSpinIntegerNode EventLine1FallingEdgeFrameID;
    quickSpinIntegerNode EventLine0AnyEdge;
    quickSpinIntegerNode EventLine0AnyEdgeTimestamp;
    quickSpinIntegerNode EventLine0AnyEdgeFrameID;
    quickSpinIntegerNode EventLine1AnyEdge;
    quickSpinIntegerNode EventLine1AnyEdgeTimestamp;
    quickSpinIntegerNode EventLine1AnyEdgeFrameID;
    quickSpinIntegerNode EventLinkTrigger0;
    quickSpinIntegerNode EventLinkTrigger0Timestamp;
    quickSpinIntegerNode EventLinkTrigger0FrameID;
    quickSpinIntegerNode EventLinkTrigger1;
    quickSpinIntegerNode EventLinkTrigger1Timestamp;
    quickSpinIntegerNode EventLinkTrigger1FrameID;
    quickSpinIntegerNode EventActionLate;
    quickSpinIntegerNode EventActionLateTimestamp;
    quickSpinIntegerNode EventActionLateFrameID;
    quickSpinIntegerNode EventLinkSpeedChange;
    quickSpinIntegerNode EventLinkSpeedChangeTimestamp;
    quickSpinIntegerNode EventLinkSpeedChangeFrameID;
    quickSpinRegisterNode FileAccessBuffer;
    quickSpinIntegerNode SourceCount;
    quickSpinEnumerationNode SourceSelector;
    quickSpinEnumerationNode TransferSelector;
    quickSpinIntegerNode TransferBurstCount;
    quickSpinCommandNode TransferAbort;
    quickSpinCommandNode TransferPause;
    quickSpinCommandNode TransferResume;
    quickSpinEnumerationNode TransferTriggerSelector;
    quickSpinEnumerationNode TransferTriggerMode;
    quickSpinEnumerationNode TransferTriggerSource;
    quickSpinEnumerationNode TransferTriggerActivation;
    quickSpinEnumerationNode TransferStatusSelector;
    quickSpinBooleanNode TransferStatus;
    quickSpinEnumerationNode TransferComponentSelector;
    quickSpinIntegerNode TransferStreamChannel;
    quickSpinEnumerationNode Scan3dDistanceUnit;
    quickSpinEnumerationNode Scan3dCoordinateSystem;
    quickSpinEnumerationNode Scan3dOutputMode;
    quickSpinEnumerationNode Scan3dCoordinateSystemReference;
    quickSpinEnumerationNode Scan3dCoordinateSelector;
    quickSpinFloatNode Scan3dCoordinateScale;
    quickSpinFloatNode Scan3dCoordinateOffset;
    quickSpinBooleanNode Scan3dInvalidDataFlag;
    quickSpinFloatNode Scan3dInvalidDataValue;
    quickSpinFloatNode Scan3dAxisMin;
    quickSpinFloatNode Scan3dAxisMax;
    quickSpinEnumerationNode Scan3dCoordinateTransformSelector;
    quickSpinFloatNode Scan3dTransformValue;
    quickSpinEnumerationNode Scan3dCoordinateReferenceSelector;
    quickSpinFloatNode Scan3dCoordinateReferenceValue;
    quickSpinIntegerNode ChunkPartSelector;
    quickSpinEnumerationNode ChunkImageComponent;
    quickSpinIntegerNode ChunkPixelDynamicRangeMin;
    quickSpinIntegerNode ChunkPixelDynamicRangeMax;
    quickSpinIntegerNode ChunkTimestampLatchValue;
    quickSpinIntegerNode ChunkLineStatusAll;
    quickSpinEnumerationNode ChunkCounterSelector;
    quickSpinIntegerNode ChunkCounterValue;
    quickSpinEnumerationNode ChunkTimerSelector;
    quickSpinFloatNode ChunkTimerValue;
    quickSpinEnumerationNode ChunkEncoderSelector;
    quickSpinIntegerNode ChunkScanLineSelector;
    quickSpinIntegerNode ChunkEncoderValue;
    quickSpinEnumerationNode ChunkEncoderStatus;
    quickSpinEnumerationNode ChunkExposureTimeSelector;
    quickSpinIntegerNode ChunkLinePitch;
    quickSpinEnumerationNode ChunkSourceID;
    quickSpinEnumerationNode ChunkRegionID;
    quickSpinIntegerNode ChunkTransferBlockID;
    quickSpinEnumerationNode ChunkTransferStreamID;
    quickSpinIntegerNode ChunkTransferQueueCurrentBlockCount;
    quickSpinIntegerNode ChunkStreamChannelID;
    quickSpinEnumerationNode ChunkScan3dDistanceUnit;
    quickSpinEnumerationNode ChunkScan3dOutputMode;
    quickSpinEnumerationNode ChunkScan3dCoordinateSystem;
    quickSpinEnumerationNode ChunkScan3dCoordinateSystemReference;
    quickSpinEnumerationNode ChunkScan3dCoordinateSelector;
    quickSpinFloatNode ChunkScan3dCoordinateScale;
    quickSpinFloatNode ChunkScan3dCoordinateOffset;
    quickSpinBooleanNode ChunkScan3dInvalidDataFlag;
    quickSpinFloatNode ChunkScan3dInvalidDataValue;
    quickSpinFloatNode ChunkScan3dAxisMin;
    quickSpinFloatNode ChunkScan3dAxisMax;
    quickSpinEnumerationNode ChunkScan3dCoordinateTransformSelector;
    quickSpinFloatNode ChunkScan3dTransformValue;
    quickSpinEnumerationNode ChunkScan3dCoordinateReferenceSelector;
    quickSpinFloatNode ChunkScan3dCoordinateReferenceValue;
    quickSpinIntegerNode TestPendingAck;
    quickSpinEnumerationNode DeviceTapGeometry;
    quickSpinEnumerationNode GevPhysicalLinkConfiguration;
    quickSpinEnumerationNode GevCurrentPhysicalLinkConfiguration;
    quickSpinIntegerNode GevActiveLinkCount;
    quickSpinBooleanNode GevPAUSEFrameReception;
    quickSpinBooleanNode GevPAUSEFrameTransmission;
    quickSpinEnumerationNode GevIPConfigurationStatus;
    quickSpinIntegerNode GevDiscoveryAckDelay;
    quickSpinEnumerationNode GevGVCPExtendedStatusCodesSelector;
    quickSpinBooleanNode GevGVCPExtendedStatusCodes;
    quickSpinIntegerNode GevPrimaryApplicationSwitchoverKey;
    quickSpinEnumerationNode GevGVSPExtendedIDMode;
    quickSpinIntegerNode GevPrimaryApplicationSocket;
    quickSpinIntegerNode GevPrimaryApplicationIPAddress;
    quickSpinBooleanNode GevSCCFGPacketResendDestination;
    quickSpinBooleanNode GevSCCFGAllInTransmission;
    quickSpinIntegerNode GevSCZoneCount;
    quickSpinIntegerNode GevSCZoneDirectionAll;
    quickSpinBooleanNode GevSCZoneConfigurationLock;
    quickSpinIntegerNode aPAUSEMACCtrlFramesTransmitted;
    quickSpinIntegerNode aPAUSEMACCtrlFramesReceived;
    quickSpinEnumerationNode ClConfiguration;
    quickSpinEnumerationNode ClTimeSlotsCount;
    quickSpinEnumerationNode CxpLinkConfigurationStatus;
    quickSpinEnumerationNode CxpLinkConfigurationPreferred;
    quickSpinEnumerationNode CxpLinkConfiguration;
    quickSpinIntegerNode CxpConnectionSelector;
    quickSpinEnumerationNode CxpConnectionTestMode;
    quickSpinIntegerNode CxpConnectionTestErrorCount;
    quickSpinIntegerNode CxpConnectionTestPacketCount;
    quickSpinCommandNode CxpPoCxpAuto;
    quickSpinCommandNode CxpPoCxpTurnOff;
    quickSpinCommandNode CxpPoCxpTripReset;
    quickSpinEnumerationNode CxpPoCxpStatus;
    quickSpinIntegerNode ChunkInferenceFrameId;
    quickSpinIntegerNode ChunkInferenceResult;
    quickSpinFloatNode ChunkInferenceConfidence;
    quickSpinRegisterNode ChunkInferenceBoundingBoxResult;
} quickSpin;

#endif // FLIR_SPINNAKER_QUICKSPINDEFS_C_H
