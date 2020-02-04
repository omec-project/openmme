/*
 * gtpV2MsgDataTypes.h 
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef GTPV2MSGDATATYPES_H_
#define GTPV2MSGDATATYPES_H_

#include "stdbool.h"
#include "../../gtpV2Codec/ieClasses/gtpV2GrpIeDataTypes.h"
#include "../../gtpV2Codec/ieClasses/gtpV2IeDataTypes.h"

typedef struct
{
  Uint8 msgType;
  Uint16 msgLength;
  bool teidPresent;
  Uint32 teid;
  Uint32 sequenceNumber;
}GtpV2MessageHeader;

typedef struct
{
  bool imsiIePresent;
  bool msisdnIePresent;
  bool meIdentityIePresent;
  bool userLocationInformationIePresent;
  bool servingNetworkIePresent;
  bool indicationFlagsIePresent;
  bool pgwS5S8AddressForControlPlaneOrPmipIePresent;
  bool selectionModeIePresent;
  bool pdnTypeIePresent;
  bool pdnAddressAllocationIePresent;
  bool maximumApnRestrictionIePresent;
  bool aggregateMaximumBitRateIePresent;
  bool linkedEpsBearerIdIePresent;
  bool protocolConfigurationOptionsIePresent;
  bool traceInformationIePresent;
  bool recoveryIePresent;
  bool mmeFqCsidIePresent;
  bool sgwFqCsidIePresent;
  bool epdgFqCsidIePresent;
  bool ueTimeZoneIePresent;
  bool userCsgInformationIePresent;
  bool chargingCharacteristicsIePresent;
  bool mmeS4SgsnLdnIePresent;
  bool sgwLdnIePresent;
  bool epdgLdnIePresent;
  bool signallingPriorityIndicationIePresent;
  bool maxMbrApnAmbrIePresent;
  bool additionalProtocolConfigurationOptionsIePresent;
  bool twanFqCsidIePresent;
  bool twanLdnIePresent;
  bool ueLocalIpAddressIePresent;
  bool ueUdpPortIePresent;
  bool hNbLocalIpAddressIePresent;
  bool hNbUdpPortIePresent;
  bool mmeS4SgsnIdentifierIePresent;
  bool twanIdentifierIePresent;
  bool epdgIpAddressIePresent;
  bool cnOperatorSelectionEntityIePresent;
  bool originationTimeStampIePresent;
  bool maximumWaitTimeIePresent;
  bool wlanLocationInformationIePresent;
  bool wlanLocationTimestampIePresent;
  bool nbifomContainerIePresent;
  bool remoteUeContextConnectedIePresent;
  bool a3gppAaaServerIdentifierIePresent;
  bool extendedProtocolConfigurationOptionsIePresent;
  bool servingPlmnRateControlIePresent;
  bool moExceptionDataCounterIePresent;
  bool ueTcpPortIePresent;
  bool mappedUeUsageTypeIePresent;
  bool userLocationInformationForSgwIePresent;
  bool sgwUNodeNameIePresent;
  bool secondaryRatUsageDataReportIePresent;
  bool upFunctionSelectionIndicationFlagsIePresent;
  bool sgwsOverloadControlInformationIePresent;
  bool twanEpdgsOverloadControlInformationIePresent;
  bool mmeS4SgsnsOverloadControlInformationIePresent;
  bool trustedWlanModeIndicationIePresent;

  ImsiIeData imsi;
  MsisdnIeData msisdn;
  MeiIeData meIdentity;
  UliIeData userLocationInformation;
  ServingNetworkIeData servingNetwork;
  RatTypeIeData ratType;
  IndicationIeData indicationFlags;
  FTeidIeData senderFTeidForControlPlane;
  FTeidIeData pgwS5S8AddressForControlPlaneOrPmip;
  ApnIeData accessPointName;
  SelectionModeIeData selectionMode;
  PdnTypeIeData pdnType;
  PaaIeData pdnAddressAllocation;
  ApnRestrictionIeData maximumApnRestriction;
  AmbrIeData aggregateMaximumBitRate;
  EbiIeData linkedEpsBearerId;
  TwmiIeData trustedWlanModeIndication;
  PcoIeData protocolConfigurationOptions;

  Uint16 bearerContextsToBeCreatedCount;
  BearerContextsToBeCreatedInCreateSessionRequestData bearerContextsToBeCreated[11];

  Uint16 bearerContextsToBeRemovedCount;
  BearerContextsToBeRemovedInCreateSessionRequestData bearerContextsToBeRemoved[11];
  TraceInformationIeData traceInformation;
  RecoveryIeData recovery;
  FqCsidIeData mmeFqCsid;
  FqCsidIeData sgwFqCsid;
  FqCsidIeData epdgFqCsid;
  FqCsidIeData twanFqCsid;
  UeTimeZoneIeData ueTimeZone;
  UciIeData userCsgInformation;
  ChargingCharacteristicsIeData chargingCharacteristics;
  LocalDistinguishedNameIeData mmeS4SgsnLdn;
  LocalDistinguishedNameIeData sgwLdn;
  LocalDistinguishedNameIeData epdgLdn;
  LocalDistinguishedNameIeData twanLdn;
  SignallingPriorityIndicationIeData signallingPriorityIndication;
  IpAddressIeData ueLocalIpAddress;
  PortNumberIeData ueUdpPort;
  AmbrMmbrIeData maxMbrApnAmbr;
  AdditionalProtocolConfigurationOptionsIeData additionalProtocolConfigurationOptions;
  IpAddressIeData hNbLocalIpAddress;
  PortNumberIeData hNbUdpPort;
  IpAddressIeData mmeS4SgsnIdentifier;
  TwanIdentifierIeData twanIdentifier;
  IpAddressIeData epdgIpAddress;
  CnOperatorSelectionEntityIeData cnOperatorSelectionEntity;
  MillisecondTimeStampIeData originationTimeStamp;
  IntegerNumberIeData maximumWaitTime;
  TwanIdentifierIeData wlanLocationInformation;
  TwanIdentifierTimestampIeData wlanLocationTimestamp;
  FContainerIeData nbifomContainer;
  RemoteUeContextConnectedInCreateSessionRequestData remoteUeContextConnected;
  NodeIdentifierIeData a3gppAaaServerIdentifier;
  EpcoIeData extendedProtocolConfigurationOptions;
  ServingPlmnRateControlIeData servingPlmnRateControl;
  CounterIeData moExceptionDataCounter;
  PortNumberIeData ueTcpPort;
  MappedUeUsageTypeIeData mappedUeUsageType;
  UliIeData userLocationInformationForSgw;
  FqdnIeData sgwUNodeName;
  SecondaryRatUsageDataReportIeData secondaryRatUsageDataReport;
  UpFunctionSelectionIndicationFlagsIeData upFunctionSelectionIndicationFlags;
  SgwsOverloadControlInformationInCreateSessionRequestData sgwsOverloadControlInformation;
  TwanEpdgsOverloadControlInformationInCreateSessionRequestData twanEpdgsOverloadControlInformation;
  MmeS4SgsnsOverloadControlInformationInCreateSessionRequestData mmeS4SgsnsOverloadControlInformation;
}CreateSessionRequestMsgData;

typedef struct
{
  bool rejectedResponseMessage;
  bool changeReportingActionIePresent;
  bool csgInformationReportingActionIePresent;
  bool senderFTeidForControlPlaneIePresent;
  bool pgwS5S8S2bFTeidIePresent;
  bool pdnAddressAllocationIePresent;
  bool apnRestrictionIePresent;
  bool aggregateMaximumBitRateIePresent;
  bool linkedEpsBearerIdIePresent;
  bool protocolConfigurationOptionsIePresent;
  bool recoveryIePresent;
  bool chargingGatewayNameIePresent;
  bool chargingGatewayAddressIePresent;
  bool pgwFqCsidIePresent;
  bool sgwFqCsidIePresent;
  bool sgwLdnIePresent;
  bool pgwLdnIePresent;
  bool pgwBackOffTimeIePresent;
  bool additionalProtocolConfigurationOptionsIePresent;
  bool hNbInformationReportingIePresent;
  bool pgwS5S8S2aS2bFTeidForPmipBasedInterfaceOrForGtpBasedControlPlaneInterfaceIePresent;
  bool trustedWlanIpv4ParametersIePresent;
  bool indicationFlagsIePresent;
  bool presenceReportingAreaActionIePresent;
  bool nbifomContainerIePresent;
  bool pdnConnectionChargingIdIePresent;
  bool extendedProtocolConfigurationOptionsIePresent;
  bool pgwsNodeLevelLoadControlInformationIePresent;
  bool pgwsApnLevelLoadControlInformationIePresent;
  bool sgwsNodeLevelLoadControlInformationIePresent;
  bool pgwsOverloadControlInformationIePresent;
  bool sgwsOverloadControlInformationIePresent;
  
  CauseIeData cause;
  ChangeReportingActionIeData changeReportingAction;
  CsgInformationReportingActionIeData csgInformationReportingAction;
  FTeidIeData senderFTeidForControlPlane;
  FTeidIeData pgwS5S8S2bFTeid;
  PaaIeData pdnAddressAllocation;
  ApnRestrictionIeData apnRestriction;
  AmbrIeData aggregateMaximumBitRate;
  EbiIeData linkedEpsBearerId;
  PcoIeData protocolConfigurationOptions;

  Uint16 bearerContextsCreatedCount;
  BearerContextsCreatedInCreateSessionResponseData bearerContextsCreated[11];

  Uint16 bearerContextsMarkedForRemovalCount;
  BearerContextsMarkedForRemovalInCreateSessionResponseData bearerContextsMarkedForRemoval[11];
  RecoveryIeData recovery;
  FqdnIeData chargingGatewayName;
  IpAddressIeData chargingGatewayAddress;
  FqCsidIeData pgwFqCsid;
  FqCsidIeData sgwFqCsid;
  LocalDistinguishedNameIeData sgwLdn;
  LocalDistinguishedNameIeData pgwLdn;
  EpcTimerIeData pgwBackOffTime;
  AdditionalProtocolConfigurationOptionsIeData additionalProtocolConfigurationOptions;
  HenbInformationReportingIeData hNbInformationReporting;
  FTeidIeData pgwS5S8S2aS2bFTeidForPmipBasedInterfaceOrForGtpBasedControlPlaneInterface;
  Ip4cpIeData trustedWlanIpv4Parameters;
  IndicationIeData indicationFlags;
  PresenceReportingAreaActionIeData presenceReportingAreaAction;
  FContainerIeData nbifomContainer;
  ChargingIdIeData pdnConnectionChargingId;
  EpcoIeData extendedProtocolConfigurationOptions;
  PgwsNodeLevelLoadControlInformationInCreateSessionResponseData pgwsNodeLevelLoadControlInformation;
  PgwsApnLevelLoadControlInformationInCreateSessionResponseData pgwsApnLevelLoadControlInformation;
  SgwsNodeLevelLoadControlInformationInCreateSessionResponseData sgwsNodeLevelLoadControlInformation;
  PgwsOverloadControlInformationInCreateSessionResponseData pgwsOverloadControlInformation;
  SgwsOverloadControlInformationInCreateSessionResponseData sgwsOverloadControlInformation;
}CreateSessionResponseMsgData;

typedef struct
{
  bool meIdentityIePresent;
  bool userLocationInformationIePresent;
  bool servingNetworkIePresent;
  bool ratTypeIePresent;
  bool indicationFlagsIePresent;
  bool senderFTeidForControlPlaneIePresent;
  bool aggregateMaximumBitRateIePresent;
  bool delayDownlinkPacketNotificationRequestIePresent;
  bool recoveryIePresent;
  bool ueTimeZoneIePresent;
  bool mmeFqCsidIePresent;
  bool sgwFqCsidIePresent;
  bool userCsgInformationIePresent;
  bool mmeS4SgsnLdnIePresent;
  bool sgwLdnIePresent;
  bool maxMbrApnAmbrIePresent;
  bool ueLocalIpAddressIePresent;
  bool ueUdpPortIePresent;
  bool hNbLocalIpAddressIePresent;
  bool hNbUdpPortIePresent;
  bool mmeS4SgsnIdentifierIePresent;
  bool cnOperatorSelectionEntityIePresent;
  bool mmeS4SgsnsOverloadControlInformationIePresent;
  bool sgwsOverloadControlInformationIePresent;
  bool epdgsOverloadControlInformationIePresent;
  bool servingPlmnRateControlIePresent;
  bool moExceptionDataCounterIePresent;
  bool imsiIePresent;
  bool userLocationInformationForSgwIePresent;
  bool wlanLocationInformationIePresent;
  bool wlanLocationTimestampIePresent;
  bool secondaryRatUsageDataReportIePresent;
  
  

  MeiIeData meIdentity;
  UliIeData userLocationInformation;
  ServingNetworkIeData servingNetwork;
  RatTypeIeData ratType;
  IndicationIeData indicationFlags;
  FTeidIeData senderFTeidForControlPlane;
  AmbrIeData aggregateMaximumBitRate;
  DelayValueIeData delayDownlinkPacketNotificationRequest;

  Uint16 bearerContextsToBeModifiedCount;
  BearerContextsToBeModifiedInModifyBearerRequestData bearerContextsToBeModified[11];

  Uint16 bearerContextsToBeRemovedCount;
  BearerContextsToBeRemovedInModifyBearerRequestData bearerContextsToBeRemoved[11];
  RecoveryIeData recovery;
  UeTimeZoneIeData ueTimeZone;
  FqCsidIeData mmeFqCsid;
  FqCsidIeData sgwFqCsid;
  UciIeData userCsgInformation;
  LocalDistinguishedNameIeData mmeS4SgsnLdn;
  LocalDistinguishedNameIeData sgwLdn;
  AmbrMmbrIeData maxMbrApnAmbr;
  IpAddressIeData ueLocalIpAddress;
  PortNumberIeData ueUdpPort;
  IpAddressIeData hNbLocalIpAddress;
  PortNumberIeData hNbUdpPort;
  IpAddressIeData mmeS4SgsnIdentifier;
  CnOperatorSelectionEntityIeData cnOperatorSelectionEntity;
  MmeS4SgsnsOverloadControlInformationInModifyBearerRequestData mmeS4SgsnsOverloadControlInformation;
  SgwsOverloadControlInformationInModifyBearerRequestData sgwsOverloadControlInformation;
  EpdgsOverloadControlInformationInModifyBearerRequestData epdgsOverloadControlInformation;
  ServingPlmnRateControlIeData servingPlmnRateControl;
  CounterIeData moExceptionDataCounter;
  ImsiIeData imsi;
  UliIeData userLocationInformationForSgw;
  TwanIdentifierIeData wlanLocationInformation;
  TwanIdentifierTimestampIeData wlanLocationTimestamp;
  SecondaryRatUsageDataReportIeData secondaryRatUsageDataReport;
  
  
}ModifyBearerRequestMsgData;

typedef struct
{
  bool rejectedResponseMessage;
  bool msisdnIePresent;
  bool linkedEpsBearerIdIePresent;
  bool aggregateMaximumBitRateIePresent;
  bool apnRestrictionIePresent;
  bool protocolConfigurationOptionsIePresent;
  bool changeReportingActionIePresent;
  bool csgInformationReportingActionIePresent;
  bool chargingGatewayNameIePresent;
  bool chargingGatewayAddressIePresent;
  bool pgwFqCsidIePresent;
  bool sgwFqCsidIePresent;
  bool recoveryIePresent;
  bool sgwLdnIePresent;
  bool pgwLdnIePresent;
  bool indicationFlagsIePresent;
  bool hNbInformationReportingIePresent;
  bool presenceReportingAreaActionIePresent;
  bool pgwsNodeLevelLoadControlInformationIePresent;
  bool pgwsApnLevelLoadControlInformationIePresent;
  bool sgwsNodeLevelLoadControlInformationIePresent;
  bool pgwsOverloadControlInformationIePresent;
  bool sgwsOverloadControlInformationIePresent;
  bool pdnConnectionChargingIdIePresent;
  
  CauseIeData cause;
  MsisdnIeData msisdn;
  EbiIeData linkedEpsBearerId;
  AmbrIeData aggregateMaximumBitRate;
  ApnRestrictionIeData apnRestriction;
  PcoIeData protocolConfigurationOptions;

  Uint16 bearerContextsModifiedCount;
  BearerContextsModifiedInModifyBearerResponseData bearerContextsModified[11];

  Uint16 bearerContextsMarkedForRemovalCount;
  BearerContextsMarkedForRemovalInModifyBearerResponseData bearerContextsMarkedForRemoval[11];
  ChangeReportingActionIeData changeReportingAction;
  CsgInformationReportingActionIeData csgInformationReportingAction;
  FqdnIeData chargingGatewayName;
  IpAddressIeData chargingGatewayAddress;
  FqCsidIeData pgwFqCsid;
  FqCsidIeData sgwFqCsid;
  RecoveryIeData recovery;
  LocalDistinguishedNameIeData sgwLdn;
  LocalDistinguishedNameIeData pgwLdn;
  IndicationIeData indicationFlags;
  HenbInformationReportingIeData hNbInformationReporting;
  PresenceReportingAreaActionIeData presenceReportingAreaAction;
  PgwsNodeLevelLoadControlInformationInModifyBearerResponseData pgwsNodeLevelLoadControlInformation;
  PgwsApnLevelLoadControlInformationInModifyBearerResponseData pgwsApnLevelLoadControlInformation;
  SgwsNodeLevelLoadControlInformationInModifyBearerResponseData sgwsNodeLevelLoadControlInformation;
  PgwsOverloadControlInformationInModifyBearerResponseData pgwsOverloadControlInformation;
  SgwsOverloadControlInformationInModifyBearerResponseData sgwsOverloadControlInformation;
  ChargingIdIeData pdnConnectionChargingId;
}ModifyBearerResponseMsgData;

typedef struct
{
  bool causeIePresent;
  bool linkedEpsBearerIdIePresent;
  bool userLocationInformationIePresent;
  bool indicationFlagsIePresent;
  bool protocolConfigurationOptionsIePresent;
  bool originatingNodeIePresent;
  bool senderFTeidForControlPlaneIePresent;
  bool ueTimeZoneIePresent;
  bool uliTimestampIePresent;
  bool ranNasReleaseCauseIePresent;
  bool twanIdentifierIePresent;
  bool twanIdentifierTimestampIePresent;
  bool mmeS4SgsnsOverloadControlInformationIePresent;
  bool sgwsOverloadControlInformationIePresent;
  bool twanEpdgsOverloadControlInformationIePresent;
  bool wlanLocationInformationIePresent;
  bool wlanLocationTimestampIePresent;
  bool ueLocalIpAddressIePresent;
  bool ueUdpPortIePresent;
  bool extendedProtocolConfigurationOptionsIePresent;
  bool ueTcpPortIePresent;
  bool secondaryRatUsageDataReportIePresent;

  CauseIeData cause;
  EbiIeData linkedEpsBearerId;
  UliIeData userLocationInformation;
  IndicationIeData indicationFlags;
  PcoIeData protocolConfigurationOptions;
  NodeTypeIeData originatingNode;
  FTeidIeData senderFTeidForControlPlane;
  UeTimeZoneIeData ueTimeZone;
  UliTimestampIeData uliTimestamp;
  RanNasCauseIeData ranNasReleaseCause;
  TwanIdentifierIeData twanIdentifier;
  TwanIdentifierTimestampIeData twanIdentifierTimestamp;
  MmeS4SgsnsOverloadControlInformationInDeleteSessionRequestData mmeS4SgsnsOverloadControlInformation;
  SgwsOverloadControlInformationInDeleteSessionRequestData sgwsOverloadControlInformation;
  TwanEpdgsOverloadControlInformationInDeleteSessionRequestData twanEpdgsOverloadControlInformation;
  TwanIdentifierIeData wlanLocationInformation;
  TwanIdentifierTimestampIeData wlanLocationTimestamp;
  IpAddressIeData ueLocalIpAddress;
  PortNumberIeData ueUdpPort;
  EpcoIeData extendedProtocolConfigurationOptions;
  PortNumberIeData ueTcpPort;
  SecondaryRatUsageDataReportIeData secondaryRatUsageDataReport;
   
}DeleteSessionRequestMsgData;

typedef struct
{
  bool rejectedResponseMessage;
  bool recoveryIePresent;
  bool protocolConfigurationOptionsIePresent;
  bool indicationFlagsIePresent;
  bool pgwsNodeLevelLoadControlInformationIePresent;
  bool pgwsApnLevelLoadControlInformationIePresent;
  bool sgwsNodeLevelLoadControlInformationIePresent;
  bool pgwsOverloadControlInformationIePresent;
  bool sgwsOverloadControlInformationIePresent;
  bool extendedProtocolConfigurationOptionsIePresent;
  
  IndicationIeData indicationFlags;
  CauseIeData cause;
  RecoveryIeData recovery;
  PcoIeData protocolConfigurationOptions;
  PgwsNodeLevelLoadControlInformationInDeleteSessionResponseData pgwsNodeLevelLoadControlInformation;
  PgwsApnLevelLoadControlInformationInDeleteSessionResponseData pgwsApnLevelLoadControlInformation;
  SgwsNodeLevelLoadControlInformationInDeleteSessionResponseData sgwsNodeLevelLoadControlInformation;
  PgwsOverloadControlInformationInDeleteSessionResponseData pgwsOverloadControlInformation;
  SgwsOverloadControlInformationInDeleteSessionResponseData sgwsOverloadControlInformation;
  EpcoIeData extendedProtocolConfigurationOptions;
}DeleteSessionResponseMsgData;

typedef struct
{
  
  bool indicationFlagsIePresent;
  bool listOfRabsIePresent;
  bool originatingNodeIePresent;
  bool secondaryRatUsageDataReportIePresent;
  
  EbiIeData listOfRabs;
  NodeTypeIeData originatingNode;
  IndicationIeData indicationFlags;
  SecondaryRatUsageDataReportIeData secondaryRatUsageDataReport;
}ReleaseAccessBearersRequestMsgData;

typedef struct
{

  bool indicationFlagsIePresent;
  bool sgwsOverloadControlInformationIePresent;
  bool sgwsNodeLevelLoadControlInformationIePresent;
  bool recoveryIePresent;
  
  IndicationIeData indicationFlags;
  CauseIeData cause;
  SgwsOverloadControlInformationInReleaseAccessBearersResponseData sgwsOverloadControlInformation;
  SgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponseData sgwsNodeLevelLoadControlInformation;
  RecoveryIeData recovery;
}ReleaseAccessBearersResponseMsgData;






typedef struct
{
  bool procedureTransactionIdIePresent;
  bool linkedEPSBearerIdIePresent;
  bool protocolConfigurationOptionsIePresent;
  bool pgwFqCsidIePresent;
  bool sgwFqCsidIePresent;
  bool changeReportingActionIePresent;
  bool csgInformationReportingActionIePresent;
  bool hNbInformationReportingIePresent;
  bool presenceReportingAreaActionIePresent;
  bool indicationFlagsIePresent;
  bool nbifomContainerIePresent;
  bool pgwsNodeLevelLoadControlInformationIePresent;
  bool pgwsApnLevelLoadControlInformationIePresent;
  bool sgwsNodeLevelLoadControlInformationIePresent;
  bool pgwsOverloadControlInformationIePresent;
  bool sgwsOverloadControlInformationIePresent;
    
  
  
  PtiIeData procedureTransactionId;
  EbiIeData linkedEpsBearerId;
  PcoIeData protocolConfigurationOptions;
  
  Uint16 bearerContextsCount;
  BearerContextsInCreateBearerRequestData bearerContexts[11];
  
  FqCsidIeData pgwFqCsid;
  FqCsidIeData sgwFqCsid;
  ChangeReportingActionIeData changeReportingAction;
  CsgInformationReportingActionIeData csgInformationReportingAction;
  HenbInformationReportingIeData hNbInformationReporting;
  PresenceReportingAreaActionIeData presenceReportingAreaAction;
  IndicationIeData indicationFlags;
  FContainerIeData nbifomContainer;
  PgwsNodeLevelLoadControlInformationInCreateBearerRequestData pgwsNodeLevelLoadControlInformation;
  PgwsApnLevelLoadControlInformationInCreateBearerRequestData pgwsApnLevelLoadControlInformation;
  SgwsNodeLevelLoadControlInformationInCreateBearerRequestData sgwsNodeLevelLoadControlInformation;
  PgwsOverloadControlInformationInCreateBearerRequestData pgwsOverloadControlInformation;
  SgwsOverloadControlInformationInCreateBearerRequestData sgwsOverloadControlInformation;
}CreateBearerRequestMsgData;


typedef struct
{
  bool causeIePresent;
  
  Uint16 bearerContextsCount;
  BearerContextsInCreateBearerResponseData bearerContexts[11];
  
  bool recoveryIePresent;
  bool mmeFqCsidIePresent;
  bool sgwFqCsidIePresent;
  bool epdgFqCsidIePresent;
  bool twanFqCsidIePresent;
  bool protocolConfigurationOptionsIePresent;
  bool ueTimeZoneIePresent;
  bool userLocationInformationIePresent;
  bool mmeS4SgsnIdentifierIePresent;
  bool twanIdentifierIePresent;
  bool wlanLocationInformationIePresent;
  bool wlanLocationTimestampIePresent;
  bool ueLocalIpAddressIePresent;
  bool ueUdpPortIePresent;
  bool nbifomContainerIePresent;
  bool ueTcpPortIePresent;
  bool mmeS4SgsnsOverloadControlInformationIePresent;
  bool sgwsOverloadControlInformationIePresent;
  bool twanEpdgsOverloadControlInformationIePresent;
       
  
  CauseIeData cause;
  RecoveryIeData recovery;
  FqCsidIeData mmeFqCsid;
  FqCsidIeData sgwFqCsid;
  FqCsidIeData epdgFqCsid;
  FqCsidIeData twanFqCsid;
  PcoIeData protocolConfigurationOptions;
  UeTimeZoneIeData ueTimeZone;
  UliIeData userLocationInformation;
  TwanIdentifierIeData twanIdentifier;
  IpAddressIeData mmeS4SgsnIdentifier;
  TwanIdentifierIeData wlanLocationInformation;
  TwanIdentifierTimestampIeData wlanLocationTimestamp;
  IpAddressIeData ueLocalIpAddress;
  PortNumberIeData ueUdpPort;
  FContainerIeData nbifomContainer;
  PortNumberIeData ueTcpPort;
  MmeS4SgsnsOverloadControlInformationInCreateBearerResponseData mmeS4SgsnsOverloadControlInformation;
  SgwsOverloadControlInformationInCreateBearerResponseData sgwsOverloadControlInformation;
  TwanEpdgsOverloadControlInformationInCreateBearerResponseData twanEpdgsOverloadControlInformation;
}CreateBearerResponseMsgData;

typedef struct
{
  bool linkedEpsBearerIdIePresent;
  bool epsBearerIdsIePresent;
  bool procedureTransactionIdIePresent;
  bool protocolConfigurationOptionsIePresent;
  bool pgwFqCsidIePresent;
  bool sgwFqCsidIePresent;
  bool causeIePresent;
  bool indicationFlagsIePresent;
  bool nbifomContainerIePresent;
  bool extendedProtocolConfigurationOptionsIePresent;
  bool pgwsNodeLevelLoadControlInformationIePresent;
  bool pgwsApnLevelLoadControlInformationIePresent;
  bool sgwsNodeLevelLoadControlInformationIePresent;
  bool pgwsOverloadControlInformationIePresent;
  bool sgwsOverloadControlInformationIePresent;
  
  
  
  
  EbiIeData linkedEpsBearerId;
  EbiIeData epsBearerIds;
  
  Uint16 failedBearerContextsCount;
  FailedBearerContextsInDeleteBearerRequestData failedBearerContexts[11];
  
  PtiIeData procedureTransactionId;
  PcoIeData protocolConfigurationOptions;
  FqCsidIeData pgwFqCsid;
  FqCsidIeData sgwFqCsid;
  CauseIeData cause;
  IndicationIeData indicationFlags;
  FContainerIeData nbifomContainer;
  EpcoIeData extendedProtocolConfigurationOptions;
  PgwsNodeLevelLoadControlInformationInDeleteBearerRequestData pgwsNodeLevelLoadControlInformation;
  PgwsApnLevelLoadControlInformationInDeleteBearerRequestData pgwsApnLevelLoadControlInformation;
  SgwsNodeLevelLoadControlInformationInDeleteBearerRequestData sgwsNodeLevelLoadControlInformation;
  PgwsOverloadControlInformationInDeleteBearerRequestData pgwsOverloadControlInformation;
  SgwsOverloadControlInformationInDeleteBearerRequestData sgwsOverloadControlInformation;  
    
}DeleteBearerRequestMsgData;

typedef struct
{ 
	bool causeIePresent;
	bool linkedEpsBearerIdIePresent;
	bool recoveryIePresent;
	bool mmeFqCsidIePresent;
	bool sgwFqCsidIePresent;
	bool epdgFqCsidIePresent;
	bool twanFqCsidIePresent;
	bool protocolConfigurationOptionsIePresent;
	bool ueTimeZoneIePresent;
	bool userLocationInformationIePresent;
	bool uliTimestampIePresent;
	bool twanIdentifierIePresent;
	bool twanIdentifierTimestampIePresent;
	bool mmeS4SgsnIdentifierIePresent;
	bool wlanLocationInformationIePresent;
	bool wlanLocationTimestampIePresent;
	bool ueLocalIpAddressIePresent;
	bool ueUdpPortIePresent;
	bool nbifomContainerIePresent;
	bool ueTcpPortIePresent;
	bool secondaryRatUsageDataReportIePresent;
	bool mmeS4SgsnsOverloadControlInformationIePresent;
	bool sgwsOverloadControlInformationIePresent;
	bool twanEpdgsOverloadControlInformationIePresent;
	
	CauseIeData cause;
	EbiIeData linkedEpsBearerId;
	
	Uint16 bearerContextsCount;
    BearerContextsInDeleteBearerResponseData bearerContexts[11];
	
	RecoveryIeData recovery;
	FqCsidIeData mmeFqCsid;
	FqCsidIeData sgwFqCsid;
	FqCsidIeData epdgFqCsid;
	FqCsidIeData twanFqCsid;
	PcoIeData protocolConfigurationOptions;
	UeTimeZoneIeData ueTimeZone;
	UliIeData userLocationInformation;
	UliTimestampIeData uliTimestamp;
	TwanIdentifierIeData twanIdentifier;
	TwanIdentifierTimestampIeData twanIdentifierTimestamp;
	IpAddressIeData mmeS4SgsnIdentifier;
	TwanIdentifierIeData wlanLocationInformation;
	TwanIdentifierTimestampIeData wlanLocationTimestamp;
	IpAddressIeData ueLocalIpAddress;
	PortNumberIeData ueUdpPort;
	FContainerIeData nbifomContainer;
	PortNumberIeData ueTcpPort;
	SecondaryRatUsageDataReportIeData secondaryRatUsageDataReport;
	MmeS4SgsnsOverloadControlInformationInDeleteBearerResponseData mmeS4SgsnsOverloadControlInformation;
	SgwsOverloadControlInformationInDeleteBearerResponseData sgwsOverloadControlInformation;
	TwanEpdgsOverloadControlInformationInDeleteBearerResponseData twanEpdgsOverloadControlInformation;
		
}DeleteBearerResponseMsgData; 


typedef struct
{ 
	bool causeIePresent;
	bool epsBearerIdIePresent;
	bool allocationRetentionPriorityIePresent;
	bool imsiIePresent;
	bool senderFTeidForControlPlaneIePresent;
	bool indicationFlagsIePresent;
	bool sgwsNodeLevelLoadControlInformationIePresent;
	bool sgwsOverloadControlInformationIePresent;
	bool pagingAndServiceInformationIePresent;
	
	CauseIeData cause;
	EbiIeData epsBearerId;
	ArpIeData allocationRetentionPriority;
	ImsiIeData imsi;
	FTeidIeData senderFTeidForControlPlane;
	IndicationIeData indicationFlags;
	SgwsNodeLevelLoadControlInformationInDownlinkDataNotificationData sgwsNodeLevelLoadControlInformation;
	SgwsOverloadControlInformationInDownlinkDataNotificationData sgwsOverloadControlInformation;
	PagingAndServiceInformationIeData pagingAndServiceInformation;
	
}DownlinkDataNotificationMsgData;


typedef struct
{ 
	bool causeIePresent;
	bool dataNotificationDelayIePresent;
	bool recoveryIePresent;
	bool dlLowPriorityTrafficThrottlingIePresent;
	bool imsiIePresent;
	bool dlBufferingDurationIePresent;
	bool dlBufferingSuggestedPacketCountIePresent;
	
	CauseIeData cause;
	DelayValueIeData dataNotificationDelay;
	RecoveryIeData recovery;
	ThrottlingIeData dlLowPriorityTrafficThrottling;
	ImsiIeData imsi;
	EpcTimerIeData dlBufferingDuration;
	IntegerNumberIeData dlBufferingSuggestedPacketCount;
	
}DownlinkDataNotificationAcknowledgeMsgData;

typedef struct
{ 

	bool causeIePresent;
	bool originatingNodeIePresent;
	bool imsiIePresent;
	
	CauseIeData cause;
	NodeTypeIeData originatingNode;
	ImsiIeData imsi;
	
}DownlinkDataNotificationFailureIndicationMsgData;

//Message Type Constants
static const Uint8 CreateSessionRequestMsgType = 32;
static const Uint8 CreateSessionResponseMsgType = 33;
static const Uint8 ModifyBearerRequestMsgType = 34;
static const Uint8 ModifyBearerResponseMsgType = 35;
static const Uint8 DeleteSessionRequestMsgType = 36;
static const Uint8 DeleteSessionResponseMsgType = 37;
static const Uint8 ReleaseAccessBearersRequestMsgType = 170;
static const Uint8 ReleaseAccessBearersResponseMsgType=171;
static const Uint8 CreateBearerRequestMsgType = 95;
static const Uint8 CreateBearerResponseMsgType = 96;
static const Uint8 DeleteBearerRequestMsgType = 99;
static const Uint8 DeleteBearerResponseMsgType = 100;
static const Uint8 DownlinkDataNotificationMsgType = 176;
static const Uint8 DownlinkDataNotificationAcknowledgeMsgType = 177;
static const Uint8 DownlinkDataNotificationFailureIndicationMsgType = 70;

#endif
