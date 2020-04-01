/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef GTPV2MSGDATATYPES_H_
#define GTPV2MSGDATATYPES_H_

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
    bool trustedWlanModeIndicationIePresent;   
    bool protocolConfigurationOptionsIePresent;   
    bool traceInformationIePresent;   
    bool recoveryIePresent;   
    bool mmeFqCsidIePresent;   
    bool sgwFqCsidIePresent;   
    bool epdgFqCsidIePresent;   
    bool twanFqCsidIePresent;   
    bool ueTimeZoneIePresent;   
    bool userCsgInformationIePresent;   
    bool chargingCharacteristicsIePresent;   
    bool mmeS4SgsnLdnIePresent;   
    bool sgwLdnIePresent;   
    bool epdgLdnIePresent;   
    bool twanLdnIePresent;   
    bool signallingPriorityIndicationIePresent;   
    bool ueLocalIpAddressIePresent;   
    bool ueUdpPortIePresent;   
    bool additionalProtocolConfigurationOptionsIePresent;   
    bool hNbLocalIpAddressIePresent;   
    bool hNbUdpPortIePresent;   
    bool mmeS4SgsnIdentifierIePresent;   
    bool twanIdentifierIePresent;   
    bool epdgIpAddressIePresent;   
    bool cnOperatorSelectionEntityIePresent;   
    bool mmeS4SgsnsOverloadControlInformationIePresent;   
    bool sgwsOverloadControlInformationIePresent;   
    bool twanEpdgsOverloadControlInformationIePresent;   
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
    AdditionalProtocolConfigurationOptionsIeData additionalProtocolConfigurationOptions;
    IpAddressIeData hNbLocalIpAddress;
    PortNumberIeData hNbUdpPort;
    IpAddressIeData mmeS4SgsnIdentifier;
    TwanIdentifierIeData twanIdentifier;
    IpAddressIeData epdgIpAddress;
    CnOperatorSelectionEntityIeData cnOperatorSelectionEntity;
    MmeS4SgsnsOverloadControlInformationInCreateSessionRequestData mmeS4SgsnsOverloadControlInformation;
    SgwsOverloadControlInformationInCreateSessionRequestData sgwsOverloadControlInformation;
    TwanEpdgsOverloadControlInformationInCreateSessionRequestData twanEpdgsOverloadControlInformation;
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
}CreateSessionRequestMsgData;

typedef struct
{
    bool changeReportingActionIePresent;   
    bool csgInformationReportingActionIePresent;   
    bool senderFTeidForControlPlaneIePresent;   
    bool apnRestrictionIePresent;   
    bool aggregateMaximumBitRateIePresent;   
    bool linkedEpsBearerIdIePresent;   
    bool recoveryIePresent;   
    bool chargingGatewayNameIePresent;   
    bool chargingGatewayAddressIePresent;   
    bool pgwFqCsidIePresent;   
    bool sgwFqCsidIePresent;   
    bool sgwLdnIePresent;   
    bool pgwLdnIePresent;   
    bool pgwBackOffTimeIePresent;   
    bool hNbInformationReportingIePresent;   
    bool pgwS5S8S2bFTeidIePresent;   
    bool pdnAddressAllocationIePresent;   
    bool protocolConfigurationOptionsIePresent;   
    bool additionalProtocolConfigurationOptionsIePresent;   
    bool trustedWlanIpv4ParametersIePresent;   
    bool indicationFlagsIePresent;   
    bool presenceReportingAreaActionIePresent;   
    bool pgwsNodeLevelLoadControlInformationIePresent;   
    bool pgwsApnLevelLoadControlInformationIePresent;   
    bool sgwsNodeLevelLoadControlInformationIePresent;   
    bool pgwsOverloadControlInformationIePresent;   
    bool sgwsOverloadControlInformationIePresent;   
    bool nbifomContainerIePresent;   
    bool pdnConnectionChargingIdIePresent;   
    bool extendedProtocolConfigurationOptionsIePresent;   


    CauseIeData cause;
    ChangeReportingActionIeData changeReportingAction;
    CsgInformationReportingActionIeData csgInformationReportingAction;
    FTeidIeData senderFTeidForControlPlane;
    ApnRestrictionIeData apnRestriction;
    AmbrIeData aggregateMaximumBitRate;
    EbiIeData linkedEpsBearerId;

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
    HenbInformationReportingIeData hNbInformationReporting;
    FTeidIeData pgwS5S8S2bFTeid;
    PaaIeData pdnAddressAllocation;
    PcoIeData protocolConfigurationOptions;
    AdditionalProtocolConfigurationOptionsIeData additionalProtocolConfigurationOptions;
    Ip4cpIeData trustedWlanIpv4Parameters;
    IndicationIeData indicationFlags;
    PresenceReportingAreaActionIeData presenceReportingAreaAction;
    PgwsNodeLevelLoadControlInformationInCreateSessionResponseData pgwsNodeLevelLoadControlInformation;
    PgwsApnLevelLoadControlInformationInCreateSessionResponseData pgwsApnLevelLoadControlInformation;
    SgwsNodeLevelLoadControlInformationInCreateSessionResponseData sgwsNodeLevelLoadControlInformation;
    PgwsOverloadControlInformationInCreateSessionResponseData pgwsOverloadControlInformation;
    SgwsOverloadControlInformationInCreateSessionResponseData sgwsOverloadControlInformation;
    FContainerIeData nbifomContainer;
    ChargingIdIeData pdnConnectionChargingId;
    EpcoIeData extendedProtocolConfigurationOptions;
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
    bool ueLocalIpAddressIePresent;   
    bool ueUdpPortIePresent;   
    bool mmeS4SgsnLdnIePresent;   
    bool sgwLdnIePresent;   
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
    IpAddressIeData ueLocalIpAddress;
    PortNumberIeData ueUdpPort;
    LocalDistinguishedNameIeData mmeS4SgsnLdn;
    LocalDistinguishedNameIeData sgwLdn;
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
    bool linkedEpsBearerIdIePresent;   
    bool indicationFlagsIePresent;   
    bool apnRestrictionIePresent;   
    bool protocolConfigurationOptionsIePresent;   
    bool changeReportingActionIePresent;   
    bool csgInformationReportingActionIePresent;   
    bool hNbInformationReportingIePresent;   
    bool chargingGatewayNameIePresent;   
    bool chargingGatewayAddressIePresent;   
    bool pgwFqCsidIePresent;   
    bool sgwFqCsidIePresent;   
    bool recoveryIePresent;   
    bool sgwLdnIePresent;   
    bool pgwLdnIePresent;   
    bool presenceReportingAreaActionIePresent;   
    bool pgwsNodeLevelLoadControlInformationIePresent;   
    bool pgwsApnLevelLoadControlInformationIePresent;   
    bool sgwsNodeLevelLoadControlInformationIePresent;   
    bool pgwsOverloadControlInformationIePresent;   
    bool sgwsOverloadControlInformationIePresent;   
    bool pdnConnectionChargingIdIePresent;   
    bool msisdnIePresent;   


    EbiIeData linkedEpsBearerId;

    Uint16 bearerContextsModifiedCount;
    BearerContextsModifiedInModifyBearerResponseData bearerContextsModified[11];

    Uint16 bearerContextsMarkedForRemovalCount;
    BearerContextsMarkedForRemovalInModifyBearerResponseData bearerContextsMarkedForRemoval[11];
    IndicationIeData indicationFlags;
    CauseIeData cause;
    ApnRestrictionIeData apnRestriction;
    PcoIeData protocolConfigurationOptions;
    ChangeReportingActionIeData changeReportingAction;
    CsgInformationReportingActionIeData csgInformationReportingAction;
    HenbInformationReportingIeData hNbInformationReporting;
    FqdnIeData chargingGatewayName;
    IpAddressIeData chargingGatewayAddress;
    FqCsidIeData pgwFqCsid;
    FqCsidIeData sgwFqCsid;
    RecoveryIeData recovery;
    LocalDistinguishedNameIeData sgwLdn;
    LocalDistinguishedNameIeData pgwLdn;
    PresenceReportingAreaActionIeData presenceReportingAreaAction;
    PgwsNodeLevelLoadControlInformationInModifyBearerResponseData pgwsNodeLevelLoadControlInformation;
    PgwsApnLevelLoadControlInformationInModifyBearerResponseData pgwsApnLevelLoadControlInformation;
    SgwsNodeLevelLoadControlInformationInModifyBearerResponseData sgwsNodeLevelLoadControlInformation;
    PgwsOverloadControlInformationInModifyBearerResponseData pgwsOverloadControlInformation;
    SgwsOverloadControlInformationInModifyBearerResponseData sgwsOverloadControlInformation;
    ChargingIdIeData pdnConnectionChargingId;
    MsisdnIeData msisdn;
}ModifyBearerResponseMsgData;

typedef struct
{
    bool linkedEpsBearerIdIePresent;   
    bool indicationFlagsIePresent;   
    bool causeIePresent;   
    bool senderFTeidForControlPlaneIePresent;   
    bool userLocationInformationIePresent;   
    bool protocolConfigurationOptionsIePresent;   
    bool originatingNodeIePresent;   
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


    EbiIeData linkedEpsBearerId;
    IndicationIeData indicationFlags;
    CauseIeData cause;
    FTeidIeData senderFTeidForControlPlane;
    UliIeData userLocationInformation;
    PcoIeData protocolConfigurationOptions;
    NodeTypeIeData originatingNode;
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
    bool recoveryIePresent;   
    bool protocolConfigurationOptionsIePresent;   
    bool indicationFlagsIePresent;   
    bool pgwsNodeLevelLoadControlInformationIePresent;   
    bool pgwsApnLevelLoadControlInformationIePresent;   
    bool sgwsNodeLevelLoadControlInformationIePresent;   
    bool pgwsOverloadControlInformationIePresent;   
    bool sgwsOverloadControlInformationIePresent;   
    bool extendedProtocolConfigurationOptionsIePresent;   


    CauseIeData cause;
    RecoveryIeData recovery;
    PcoIeData protocolConfigurationOptions;
    IndicationIeData indicationFlags;
    PgwsNodeLevelLoadControlInformationInDeleteSessionResponseData pgwsNodeLevelLoadControlInformation;
    PgwsApnLevelLoadControlInformationInDeleteSessionResponseData pgwsApnLevelLoadControlInformation;
    SgwsNodeLevelLoadControlInformationInDeleteSessionResponseData sgwsNodeLevelLoadControlInformation;
    PgwsOverloadControlInformationInDeleteSessionResponseData pgwsOverloadControlInformation;
    SgwsOverloadControlInformationInDeleteSessionResponseData sgwsOverloadControlInformation;
    EpcoIeData extendedProtocolConfigurationOptions;
}DeleteSessionResponseMsgData;

typedef struct
{
    bool listOfRabsIePresent;   
    bool originatingNodeIePresent;   
    bool indicationFlagsIePresent;   
    bool secondaryRatUsageDataReportIePresent;   


    EbiIeData listOfRabs;
    NodeTypeIeData originatingNode;
    IndicationIeData indicationFlags;
    SecondaryRatUsageDataReportIeData secondaryRatUsageDataReport;
}ReleaseAccessBearersRequestMsgData;

typedef struct
{
    bool recoveryIePresent;   
    bool indicationFlagsIePresent;   
    bool sgwsNodeLevelLoadControlInformationIePresent;   
    bool sgwsOverloadControlInformationIePresent;   


    CauseIeData cause;
    RecoveryIeData recovery;
    IndicationIeData indicationFlags;
    SgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponseData sgwsNodeLevelLoadControlInformation;
    SgwsOverloadControlInformationInReleaseAccessBearersResponseData sgwsOverloadControlInformation;
}ReleaseAccessBearersResponseMsgData;

typedef struct
{
    bool procedureTransactionIdIePresent;   
    bool protocolConfigurationOptionsIePresent;   
    bool pgwFqCsidIePresent;   
    bool sgwFqCsidIePresent;   
    bool changeReportingActionIePresent;   
    bool csgInformationReportingActionIePresent;   
    bool hNbInformationReportingIePresent;   
    bool presenceReportingAreaActionIePresent;   
    bool indicationFlagsIePresent;   
    bool pgwsNodeLevelLoadControlInformationIePresent;   
    bool pgwsApnLevelLoadControlInformationIePresent;   
    bool sgwsNodeLevelLoadControlInformationIePresent;   
    bool pgwsOverloadControlInformationIePresent;   
    bool sgwsOverloadControlInformationIePresent;   
    bool nbifomContainerIePresent;   


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
    PgwsNodeLevelLoadControlInformationInCreateBearerRequestData pgwsNodeLevelLoadControlInformation;
    PgwsApnLevelLoadControlInformationInCreateBearerRequestData pgwsApnLevelLoadControlInformation;
    SgwsNodeLevelLoadControlInformationInCreateBearerRequestData sgwsNodeLevelLoadControlInformation;
    PgwsOverloadControlInformationInCreateBearerRequestData pgwsOverloadControlInformation;
    SgwsOverloadControlInformationInCreateBearerRequestData sgwsOverloadControlInformation;
    FContainerIeData nbifomContainer;
}CreateBearerRequestMsgData;

typedef struct
{
    bool recoveryIePresent;   
    bool mmeFqCsidIePresent;   
    bool sgwFqCsidIePresent;   
    bool epdgFqCsidIePresent;   
    bool twanFqCsidIePresent;   
    bool protocolConfigurationOptionsIePresent;   
    bool ueTimeZoneIePresent;   
    bool userLocationInformationIePresent;   
    bool twanIdentifierIePresent;   
    bool mmeS4SgsnsOverloadControlInformationIePresent;   
    bool sgwsOverloadControlInformationIePresent;   
    bool mmeS4SgsnIdentifierIePresent;   
    bool twanEpdgsOverloadControlInformationIePresent;   
    bool wlanLocationInformationIePresent;   
    bool wlanLocationTimestampIePresent;   
    bool ueLocalIpAddressIePresent;   
    bool ueUdpPortIePresent;   
    bool nbifomContainerIePresent;   
    bool ueTcpPortIePresent;   


    CauseIeData cause;

    Uint16 bearerContextsCount;
    BearerContextsInCreateBearerResponseData bearerContexts[11];
    RecoveryIeData recovery;
    FqCsidIeData mmeFqCsid;
    FqCsidIeData sgwFqCsid;
    FqCsidIeData epdgFqCsid;
    FqCsidIeData twanFqCsid;
    PcoIeData protocolConfigurationOptions;
    UeTimeZoneIeData ueTimeZone;
    UliIeData userLocationInformation;
    TwanIdentifierIeData twanIdentifier;
    MmeS4SgsnsOverloadControlInformationInCreateBearerResponseData mmeS4SgsnsOverloadControlInformation;
    SgwsOverloadControlInformationInCreateBearerResponseData sgwsOverloadControlInformation;
    IpAddressIeData mmeS4SgsnIdentifier;
    TwanEpdgsOverloadControlInformationInCreateBearerResponseData twanEpdgsOverloadControlInformation;
    TwanIdentifierIeData wlanLocationInformation;
    TwanIdentifierTimestampIeData wlanLocationTimestamp;
    IpAddressIeData ueLocalIpAddress;
    PortNumberIeData ueUdpPort;
    FContainerIeData nbifomContainer;
    PortNumberIeData ueTcpPort;
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
    bool pgwsNodeLevelLoadControlInformationIePresent;   
    bool pgwsApnLevelLoadControlInformationIePresent;   
    bool sgwsNodeLevelLoadControlInformationIePresent;   
    bool pgwsOverloadControlInformationIePresent;   
    bool sgwsOverloadControlInformationIePresent;   
    bool nbifomContainerIePresent;   
    bool extendedProtocolConfigurationOptionsIePresent;   


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
    PgwsNodeLevelLoadControlInformationInDeleteBearerRequestData pgwsNodeLevelLoadControlInformation;
    PgwsApnLevelLoadControlInformationInDeleteBearerRequestData pgwsApnLevelLoadControlInformation;
    SgwsNodeLevelLoadControlInformationInDeleteBearerRequestData sgwsNodeLevelLoadControlInformation;
    PgwsOverloadControlInformationInDeleteBearerRequestData pgwsOverloadControlInformation;
    SgwsOverloadControlInformationInDeleteBearerRequestData sgwsOverloadControlInformation;
    FContainerIeData nbifomContainer;
    EpcoIeData extendedProtocolConfigurationOptions;
}DeleteBearerRequestMsgData;

typedef struct
{
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
    bool mmeS4SgsnsOverloadControlInformationIePresent;   
    bool sgwsOverloadControlInformationIePresent;   
    bool mmeS4SgsnIdentifierIePresent;   
    bool twanEpdgsOverloadControlInformationIePresent;   
    bool wlanLocationInformationIePresent;   
    bool wlanLocationTimestampIePresent;   
    bool ueLocalIpAddressIePresent;   
    bool ueUdpPortIePresent;   
    bool nbifomContainerIePresent;   
    bool ueTcpPortIePresent;   
    bool secondaryRatUsageDataReportIePresent;   


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
    MmeS4SgsnsOverloadControlInformationInDeleteBearerResponseData mmeS4SgsnsOverloadControlInformation;
    SgwsOverloadControlInformationInDeleteBearerResponseData sgwsOverloadControlInformation;
    IpAddressIeData mmeS4SgsnIdentifier;
    TwanEpdgsOverloadControlInformationInDeleteBearerResponseData twanEpdgsOverloadControlInformation;
    TwanIdentifierIeData wlanLocationInformation;
    TwanIdentifierTimestampIeData wlanLocationTimestamp;
    IpAddressIeData ueLocalIpAddress;
    PortNumberIeData ueUdpPort;
    FContainerIeData nbifomContainer;
    PortNumberIeData ueTcpPort;
    SecondaryRatUsageDataReportIeData secondaryRatUsageDataReport;
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
    bool originatingNodeIePresent;   
    bool imsiIePresent;   


    CauseIeData cause;
    NodeTypeIeData originatingNode;
    ImsiIeData imsi;
}DownlinkDataNotificationFailureIndicationMsgData;


//Ie Type Constants
static const  Uint8  CreateSessionRequestMsgType = 32;    
static const  Uint8  CreateSessionResponseMsgType = 33;    
static const  Uint8  ModifyBearerRequestMsgType = 34;    
static const  Uint8  ModifyBearerResponseMsgType = 35;    
static const  Uint8  DeleteSessionRequestMsgType = 36;    
static const  Uint8  DeleteSessionResponseMsgType = 37;    
static const  Uint8  ReleaseAccessBearersRequestMsgType = 170;    
static const  Uint8  ReleaseAccessBearersResponseMsgType = 171;    
static const  Uint8  CreateBearerRequestMsgType = 95;    
static const  Uint8  CreateBearerResponseMsgType = 96;    
static const  Uint8  DeleteBearerRequestMsgType = 99;    
static const  Uint8  DeleteBearerResponseMsgType = 100;    
static const  Uint8  DownlinkDataNotificationMsgType = 176;    
static const  Uint8  DownlinkDataNotificationAcknowledgeMsgType = 177;    
static const  Uint8  DownlinkDataNotificationFailureIndicationMsgType = 70;    


#endif 