/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef GTPV2IEDATATYPES_H_
#define GTPV2IEDATATYPES_H_

#include "gtpV2DataTypes.h"
#include "manual/gtpV2DataTypes_Manual.h"

typedef struct
{
    DigitRegister imsiValue;    

}ImsiIeData;

typedef struct
{
    Uint8 causeValue;    
    bool pce;    
    bool pbe;    
    bool cs;    
    bool offendingIeDataPresent;
    OffendingIeData offendingIeData;    

}CauseIeData;

typedef struct
{
    DigitRegister msisdnValue;    

}MsisdnIeData;

typedef struct
{
    DigitRegister imeiSvValue;    

}MeiIeData;

typedef struct
{
    bool laipresent;    
    bool ecgipresent;    
    bool taipresent;    
    bool raipresent;    
    bool saipresent;    
    bool cgipresent;    
    CgiField cgi;    
    SaiField sai;    
    RaiField rai;    
    TaiField tai;    
    EcgiField ecgi;    
    LaiField lai;    

}UliIeData;

typedef struct
{
    Uint8 mccDigit2;    
    Uint8 mccDigit1;    
    Uint8 mncDigit3;    
    Uint8 mccDigit3;    
    Uint8 mncDigit2;    
    Uint8 mncDigit1;    

}ServingNetworkIeData;

typedef struct
{
    Uint8 ratType;    

}RatTypeIeData;

typedef struct
{
    bool iDAF;    
    bool iDTF;    
    bool iHI;    
    bool iDFI;    
    bool iOI;    
    bool iISRSI;    
    bool iISRAI;    
    bool iSGWCI;    
    bool iSQCI;    
    bool iUIMSI;    
    bool iCFSI;    
    bool iCRSI;    
    bool iP;    
    bool iPT;    
    bool iSI;    
    bool iMSV;    
    bool iS6AF;    
    bool iS4AF;    
    bool iMBMDT;    
    bool iISRAU;    
    bool iCCRSI;    

}IndicationIeData;

typedef struct
{
    bool ipv4present;    
    bool ipv6present;    
    Uint8 interfaceType;    
    Uint32 teidGreKey;    
    IpAddressV4 ipV4Address;    
    IpAddressV6 ipV6Address;    

}FTeidIeData;

typedef struct
{
    Uint8Array32 apnValue;    

}ApnIeData;

typedef struct
{
    Uint8 selectionMode;    

}SelectionModeIeData;

typedef struct
{
    Uint8 pdnType;    

}PdnTypeIeData;

typedef struct
{
    Uint8 pdnType;    
    Uint8 ipv6PrefixLength;    
    IpAddressV6 ipV6Address;    
    IpAddressV4 ipV4Address;    

}PaaIeData;

typedef struct
{
    Uint8 restrictionValue;    

}ApnRestrictionIeData;

typedef struct
{
    Uint32 maxMbrUplink;    
    Uint32 maxMbrDownlink;    

}AmbrMmbrIeData;

typedef struct
{
    Uint32 maxMbrUplink;    
    Uint32 maxMbrDownlink;    

}AmbrIeData;

typedef struct
{
    Uint8 epsBearerId;    

}EbiIeData;

typedef struct
{
  Uint8Array512 pcoValue;

}PcoIeData;

typedef struct
{
    Uint8 mccDigit2;    
    Uint8 mccDigit1;    
    Uint8 mncDigit3;    
    Uint8 mccDigit3;    
    Uint8 mncDigit2;    
    Uint8 mncDigit1;    
    Uint8Array4 traceId;    
    Uint8Array16 triggeringEvents;    
    Uint16 listOfNeTypes;    
    Uint8 sessionTraceDepth;    
    Uint8Array16 listOfInterfaces;    
    IpAddressV4 ipAddressOfTce;    

}TraceInformationIeData;

typedef struct
{
    Uint8 restartCounter;    

}RecoveryIeData;

typedef struct
{
    Uint8 daylightSavingTime;    

}UeTimeZoneIeData;

typedef struct
{
    Uint8 mccDigit2;    
    Uint8 mccDigit1;    
    Uint8 mncDigit3;    
    Uint8 mccDigit3;    
    Uint8 mncDigit2;    
    Uint8 mncDigit1;    
    Uint32 csgId;    
    Uint8 accessMode;    
    Uint8 lcsg;    
    Uint8 cmi;    

}UciIeData;

typedef struct
{
    Uint16 value;    

}ChargingCharacteristicsIeData;

typedef struct
{
    Uint8Array512 ldn;    

}LocalDistinguishedNameIeData;

typedef struct
{

}SignallingPriorityIndicationIeData;

typedef struct
{
    Uint8Array16 apco;    

}AdditionalProtocolConfigurationOptionsIeData;

typedef struct
{
    Uint8 nodeIdType;    
    Uint8 numberOfCsids;    
    IpAddressV4 nodeIdIpv4;    
    IpAddressV6 nodeIdIpv6;    
    Uint32 nodeIdUint32;    
    Uint16Array16 csidList;    

}FqCsidIeData;

typedef struct
{
    Uint8Array16 tft;    

}BearerTftIeData;

typedef struct
{
    Uint8 pci;    
    Uint8 pl;    
    Uint8 pvi;    
    Uint8 qci;    
    Uint8Array5 maxBitRateUl;    
    Uint8Array5 maxBitRateDl;    
    Uint8Array5 guraranteedBitRateUl;    
    Uint8Array5 guaranteedBitRateDl;    

}BearerQosIeData;

typedef struct
{
    Uint8 action;    

}ChangeReportingActionIeData;

typedef struct
{
    bool uciuhc;    
    bool ucishc;    
    bool ucicsg;    

}CsgInformationReportingActionIeData;

typedef struct
{
    Uint8Array32 fqdn;    

}FqdnIeData;

typedef struct
{
    Uint8 timerUnit;    
    Uint8 timerValue;    

}EpcTimerIeData;

typedef struct
{
    Uint32 chargingIdValue;    

}ChargingIdIeData;

typedef struct
{
    bool vb;    
    bool ppc;    

}BearerFlagsIeData;

typedef struct
{
    bool ipAddressV4Present;
    IpAddressV4 ipAddressV4;    
    bool ipAddressV6Present;
    IpAddressV6 ipAddressV6;    

}IpAddressIeData;

typedef struct
{
    Uint8 delayValue;    

}DelayValueIeData;

typedef struct
{
    Uint16 portNumber;    

}PortNumberIeData;

typedef struct
{
    Uint8 cnOpselectionEntity;    

}CnOperatorSelectionEntityIeData;

typedef struct
{
    Uint16 uplinkRateLimit;    
    Uint16 downlinkRateLimit;    

}ServingPlmnRateControlIeData;

typedef struct
{
    Uint32 timeStampValue;    
    Uint8 counterValue;    

}CounterIeData;

typedef struct
{
    bool laiipresent;    
    bool opnaipresent;    
    bool plmnipresent;    
    bool civaipresent;    
    bool bssidipresent;    
    Uint64 ssidLength;    
    Uint8 ssid;    
    Uint8 bssid;    
    Uint8 civicAddressLength;    
    Uint8 civicAddressInformation;    
    Uint8 twanplmnid;    
    Uint8 twanOperatorNameLength;    
    Uint8 twanOperatorName;    
    Uint8 relayIdentityType;    
    Uint8 relayIdentityLength;    
    Uint8 relayIdentity;    
    Uint8 circuitIDLength;    
    Uint8 circuitID;    

}TwanIdentifierIeData;

typedef struct
{
    Uint32 twanIdentifierTimestampvalue;    

}TwanIdentifierTimestampIeData;

typedef struct
{
    bool irsgw;    
    bool irpgw;    
    Uint8 secondaryRatType;    
    Uint8 epsBearerId;    
    Uint32 starttimestamp;    
    Uint32 endtimestamp;    
    Uint64 usageDataDL;    
    Uint64 usageDataUL;    

}SecondaryRatUsageDataReportIeData;

typedef struct
{
    Uint8 protocolType;    
    Uint8 causeType;    
    Uint8 causeValue;    

}RanNasCauseIeData;

typedef struct
{
    Uint8Array16 epco;    

}EpcoIeData;

typedef struct
{
    Uint8 dl;    
    Uint8 ul;    
    Uint16 ulValue;    
    Uint16 dlValue;    

}MaximumPacketLossRateIeData;

typedef struct
{
    Uint8 containerType;    
    Uint8 fContainerField;    

}FContainerIeData;

typedef struct
{
    Uint8 lengthOfNodeName;    
    Uint8 nodeName;    
    Uint8 lengthOfNodeRealm;    
    Uint8 nodeRealm;    

}NodeIdentifierIeData;

typedef struct
{
    bool dcnr;    

}UpFunctionSelectionIndicationFlagsIeData;

typedef struct
{
    bool fti;    

}HenbInformationReportingIeData;

typedef struct
{
    Uint8 subnetPrefixLength;    
    IpAddressV4 iPv4DefaultRouterAddress;    

}Ip4cpIeData;

typedef struct
{
    bool inapra;    
    Uint8 action;    
    Uint32 presenceReportingAreaIdentifier;    
    Uint8 numberOfTAI;    
    Uint8 numberOfRAI;    
    Uint8 numberOfMacroeNodeB;    
    Uint8 numberOfHomeeNodeB;    
    Uint8 numberOfECGI;    
    Uint8 numberOfSAI;    
    Uint8 numberOfCGI;    
    TaiFieldArray15 tais;    
    Uint8 macroeNBIds;    
    Uint8 homeeNBIds;    
    EcgiFieldArray64 ecgis;    
    RaiFieldArray15 raiss;    
    SaiFieldArray64 saiss;    
    CgiFieldArray64 cgiss;    
    Uint8 numberOfExtendedMacroeNodeB;    
    Uint8 extendedMacroeNBIds;    

}PresenceReportingAreaActionIeData;

typedef struct
{
    Uint8 nodeType;    

}NodeTypeIeData;

typedef struct
{
    Uint8 procedureTransactionId;    

}PtiIeData;

typedef struct
{
    bool mcm;    
    bool scm;    

}TwmiIeData;

typedef struct
{
    Uint64 millisecondTimeStampValue;    

}MillisecondTimeStampIeData;

typedef struct
{
    Uint64 integerNumberValue;    

}IntegerNumberIeData;

typedef struct
{
    Uint16 mappedUEUsageType;    

}MappedUeUsageTypeIeData;

typedef struct
{
    Uint32 uliTimestampvalue;    

}UliTimestampIeData;

typedef struct
{
    Uint8 metric;    

}MetricIeData;

typedef struct
{
    bool imeifpresent;    
    bool msisdnfpresent;    
    Uint8 lengthofIMSI;    
    DigitRegister imsi;    
    Uint8 lengthOfMSISDN;    
    DigitRegister msisdn;    
    Uint8 lengthOfIMEI;    
    DigitRegister imei;    

}RemoteUserIdIeData;

typedef struct
{
    Uint64 remoteUeIpInformation;    

}RemoteUeIpInformationIeData;

typedef struct
{
    Uint32 sequenceNumber;    

}SequenceNumberIeData;

typedef struct
{
    Uint8 relativeCapacity;    
    Uint8 apnLength;    
    Uint8Array32 apn;    

}ApnAndRelativeCapacityIeData;

typedef struct
{
    Uint8 pci;    
    Uint8 pl;    
    Uint8 pvi;    

}ArpIeData;

typedef struct
{
    Uint8 throttlingDelayUnit;    
    Uint8 throttlingDelayValue;    
    Uint8 throttlingFactor;    

}ThrottlingIeData;

typedef struct
{
    Uint8 epsBearerId;    
    Uint8 ppi;    
    Uint8 ppiValue;    

}PagingAndServiceInformationIeData;


//Ie Type Constants
static const  Uint8  ImsiIeType = 1;    
static const  Uint8  CauseIeType = 2;    
static const  Uint8  MsisdnIeType = 76;    
static const  Uint8  MeiIeType = 75;    
static const  Uint8  UliIeType = 86;    
static const  Uint8  ServingNetworkIeType = 83;    
static const  Uint8  RatTypeIeType = 82;    
static const  Uint8  IndicationIeType = 77;    
static const  Uint8  FTeidIeType = 87;    
static const  Uint8  ApnIeType = 71;    
static const  Uint8  SelectionModeIeType = 128;    
static const  Uint8  PdnTypeIeType = 99;    
static const  Uint8  PaaIeType = 79;    
static const  Uint8  ApnRestrictionIeType = 127;    
static const  Uint8  AmbrMmbrIeType = 161;    
static const  Uint8  AmbrIeType = 72;    
static const  Uint8  EbiIeType = 73;    
static const  Uint8  PcoIeType = 78;    
static const  Uint8  TraceInformationIeType = 96;    
static const  Uint8  RecoveryIeType = 3;    
static const  Uint8  UeTimeZoneIeType = 114;    
static const  Uint8  UciIeType = 145;    
static const  Uint8  ChargingCharacteristicsIeType = 95;    
static const  Uint8  LocalDistinguishedNameIeType = 151;    
static const  Uint8  SignallingPriorityIndicationIeType = 157;    
static const  Uint8  AdditionalProtocolConfigurationOptionsIeType = 163;    
static const  Uint8  FqCsidIeType = 132;    
static const  Uint8  BearerTftIeType = 84;    
static const  Uint8  BearerQosIeType = 80;    
static const  Uint8  ChangeReportingActionIeType = 131;    
static const  Uint8  CsgInformationReportingActionIeType = 146;    
static const  Uint8  FqdnIeType = 136;    
static const  Uint8  EpcTimerIeType = 156;    
static const  Uint8  ChargingIdIeType = 94;    
static const  Uint8  BearerFlagsIeType = 97;    
static const  Uint8  IpAddressIeType = 74;    
static const  Uint8  DelayValueIeType = 92;    
static const  Uint8  PortNumberIeType = 126;    
static const  Uint8  CnOperatorSelectionEntityIeType = 173;    
static const  Uint8  ServingPlmnRateControlIeType = 198;    
static const  Uint8  CounterIeType = 199;    
static const  Uint8  TwanIdentifierIeType = 169;    
static const  Uint8  TwanIdentifierTimestampIeType = 179;    
static const  Uint8  SecondaryRatUsageDataReportIeType = 201;    
static const  Uint8  RanNasCauseIeType = 172;    
static const  Uint8  EpcoIeType = 197;    
static const  Uint8  MaximumPacketLossRateIeType = 203;    
static const  Uint8  FContainerIeType = 118;    
static const  Uint8  NodeIdentifierIeType = 176;    
static const  Uint8  UpFunctionSelectionIndicationFlagsIeType = 202;    
static const  Uint8  HenbInformationReportingIeType = 165;    
static const  Uint8  Ip4cpIeType = 166;    
static const  Uint8  PresenceReportingAreaActionIeType = 177;    
static const  Uint8  NodeTypeIeType = 135;    
static const  Uint8  PtiIeType = 100;    
static const  Uint8  TwmiIeType = 174;    
static const  Uint8  MillisecondTimeStampIeType = 188;    
static const  Uint8  IntegerNumberIeType = 187;    
static const  Uint8  MappedUeUsageTypeIeType = 200;    
static const  Uint8  UliTimestampIeType = 170;    
static const  Uint8  MetricIeType = 182;    
static const  Uint8  RemoteUserIdIeType = 192;    
static const  Uint8  RemoteUeIpInformationIeType = 193;    
static const  Uint8  SequenceNumberIeType = 183;    
static const  Uint8  ApnAndRelativeCapacityIeType = 184;    
static const  Uint8  ArpIeType = 155;    
static const  Uint8  ThrottlingIeType = 154;    
static const  Uint8  PagingAndServiceInformationIeType = 186;    


#endif 
