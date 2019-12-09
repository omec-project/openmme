/*
* Copyright (c) 2019 Infosys Limited
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <map>
#include "gtpV2IeFactory.h"
#include "manual/gtpV2Ie.h"
#include "gtpV2GrpIeDataTypes.h"
#include "imsiIe.h"
#include "causeIe.h"
#include "msisdnIe.h"
#include "meiIe.h"
#include "uliIe.h"
#include "servingNetworkIe.h"
#include "ratTypeIe.h"
#include "indicationIe.h"
#include "fTeidIe.h"
#include "apnIe.h"
#include "selectionModeIe.h"
#include "pdnTypeIe.h"
#include "paaIe.h"
#include "apnRestrictionIe.h"
#include "ambrMmbrIe.h"
#include "ambrIe.h"
#include "ebiIe.h"
#include "pcoIe.h"
#include "traceInformationIe.h"
#include "recoveryIe.h"
#include "ueTimeZoneIe.h"
#include "uciIe.h"
#include "chargingCharacteristicsIe.h"
#include "localDistinguishedNameIe.h"
#include "signallingPriorityIndicationIe.h"
#include "additionalProtocolConfigurationOptionsIe.h"
#include "fqCsidIe.h"
#include "bearerTftIe.h"
#include "bearerQosIe.h"
#include "changeReportingActionIe.h"
#include "csgInformationReportingActionIe.h"
#include "fqdnIe.h"
#include "epcTimerIe.h"
#include "chargingIdIe.h"
#include "bearerFlagsIe.h"
#include "ipAddressIe.h"
#include "delayValueIe.h"
#include "portNumberIe.h"
#include "cnOperatorSelectionEntityIe.h"
#include "servingPlmnRateControlIe.h"
#include "counterIe.h"
#include "twanIdentifierIe.h"
#include "twanIdentifierTimestampIe.h"
#include "secondaryRatUsageDataReportIe.h"
#include "ranNasCauseIe.h"
#include "epcoIe.h"
#include "maximumPacketLossRateIe.h"
#include "fContainerIe.h"
#include "nodeIdentifierIe.h"
#include "upFunctionSelectionIndicationFlagsIe.h"
#include "henbInformationReportingIe.h"
#include "ip4cpIe.h"
#include "presenceReportingAreaActionIe.h"
#include "nodeTypeIe.h"
#include "ptiIe.h"
#include "twmiIe.h"
#include "millisecondTimeStampIe.h"
#include "integerNumberIe.h"
#include "mappedUeUsageTypeIe.h"
#include "uliTimestampIe.h"
#include "metricIe.h"
#include "remoteUserIdIe.h"
#include "remoteUeIpInformationIe.h"
#include "sequenceNumberIe.h"
#include "apnAndRelativeCapacityIe.h"
#include "arpIe.h"
#include "throttlingIe.h"
#include "pagingAndServiceInformationIe.h"
#include "bearerContextIe.h"
#include "overloadControlInformationIe.h"
#include "loadControlInformationIe.h"
#include "remoteUeContextIe.h"

GtpV2IeFactory::GtpV2IeFactory() 
{
    //Create Message Objects    
    ImsiIe* imsiIe_p = new (ImsiIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(ImsiIeType, imsiIe_p));

    CauseIe* causeIe_p = new (CauseIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(CauseIeType, causeIe_p));

    MsisdnIe* msisdnIe_p = new (MsisdnIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(MsisdnIeType, msisdnIe_p));

    MeiIe* meiIe_p = new (MeiIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(MeiIeType, meiIe_p));

    UliIe* uliIe_p = new (UliIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(UliIeType, uliIe_p));

    ServingNetworkIe* servingNetworkIe_p = new (ServingNetworkIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(ServingNetworkIeType, servingNetworkIe_p));

    RatTypeIe* ratTypeIe_p = new (RatTypeIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(RatTypeIeType, ratTypeIe_p));

    IndicationIe* indicationIe_p = new (IndicationIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(IndicationIeType, indicationIe_p));

    FTeidIe* fTeidIe_p = new (FTeidIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(FTeidIeType, fTeidIe_p));

    ApnIe* apnIe_p = new (ApnIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(ApnIeType, apnIe_p));

    SelectionModeIe* selectionModeIe_p = new (SelectionModeIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(SelectionModeIeType, selectionModeIe_p));

    PdnTypeIe* pdnTypeIe_p = new (PdnTypeIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(PdnTypeIeType, pdnTypeIe_p));

    PaaIe* paaIe_p = new (PaaIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(PaaIeType, paaIe_p));

    ApnRestrictionIe* apnRestrictionIe_p = new (ApnRestrictionIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(ApnRestrictionIeType, apnRestrictionIe_p));

    AmbrMmbrIe* ambrMmbrIe_p = new (AmbrMmbrIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(AmbrMmbrIeType, ambrMmbrIe_p));

    AmbrIe* ambrIe_p = new (AmbrIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(AmbrIeType, ambrIe_p));

    EbiIe* ebiIe_p = new (EbiIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(EbiIeType, ebiIe_p));

    PcoIe* pcoIe_p = new (PcoIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(PcoIeType, pcoIe_p));

    TraceInformationIe* traceInformationIe_p = new (TraceInformationIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(TraceInformationIeType, traceInformationIe_p));

    RecoveryIe* recoveryIe_p = new (RecoveryIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(RecoveryIeType, recoveryIe_p));

    UeTimeZoneIe* ueTimeZoneIe_p = new (UeTimeZoneIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(UeTimeZoneIeType, ueTimeZoneIe_p));

    UciIe* uciIe_p = new (UciIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(UciIeType, uciIe_p));

    ChargingCharacteristicsIe* chargingCharacteristicsIe_p = new (ChargingCharacteristicsIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(ChargingCharacteristicsIeType, chargingCharacteristicsIe_p));

    LocalDistinguishedNameIe* localDistinguishedNameIe_p = new (LocalDistinguishedNameIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(LocalDistinguishedNameIeType, localDistinguishedNameIe_p));

    SignallingPriorityIndicationIe* signallingPriorityIndicationIe_p = new (SignallingPriorityIndicationIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(SignallingPriorityIndicationIeType, signallingPriorityIndicationIe_p));

    AdditionalProtocolConfigurationOptionsIe* additionalProtocolConfigurationOptionsIe_p = new (AdditionalProtocolConfigurationOptionsIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(AdditionalProtocolConfigurationOptionsIeType, additionalProtocolConfigurationOptionsIe_p));

    FqCsidIe* fqCsidIe_p = new (FqCsidIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(FqCsidIeType, fqCsidIe_p));

    BearerTftIe* bearerTftIe_p = new (BearerTftIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(BearerTftIeType, bearerTftIe_p));

    BearerQosIe* bearerQosIe_p = new (BearerQosIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(BearerQosIeType, bearerQosIe_p));

    ChangeReportingActionIe* changeReportingActionIe_p = new (ChangeReportingActionIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(ChangeReportingActionIeType, changeReportingActionIe_p));

    CsgInformationReportingActionIe* csgInformationReportingActionIe_p = new (CsgInformationReportingActionIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(CsgInformationReportingActionIeType, csgInformationReportingActionIe_p));

    FqdnIe* fqdnIe_p = new (FqdnIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(FqdnIeType, fqdnIe_p));

    EpcTimerIe* epcTimerIe_p = new (EpcTimerIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(EpcTimerIeType, epcTimerIe_p));

    ChargingIdIe* chargingIdIe_p = new (ChargingIdIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(ChargingIdIeType, chargingIdIe_p));

    BearerFlagsIe* bearerFlagsIe_p = new (BearerFlagsIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(BearerFlagsIeType, bearerFlagsIe_p));

    IpAddressIe* ipAddressIe_p = new (IpAddressIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(IpAddressIeType, ipAddressIe_p));

    DelayValueIe* delayValueIe_p = new (DelayValueIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(DelayValueIeType, delayValueIe_p));

    PortNumberIe* portNumberIe_p = new (PortNumberIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(PortNumberIeType, portNumberIe_p));

    CnOperatorSelectionEntityIe* cnOperatorSelectionEntityIe_p = new (CnOperatorSelectionEntityIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(CnOperatorSelectionEntityIeType, cnOperatorSelectionEntityIe_p));

    ServingPlmnRateControlIe* servingPlmnRateControlIe_p = new (ServingPlmnRateControlIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(ServingPlmnRateControlIeType, servingPlmnRateControlIe_p));

    CounterIe* counterIe_p = new (CounterIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(CounterIeType, counterIe_p));

    TwanIdentifierIe* twanIdentifierIe_p = new (TwanIdentifierIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(TwanIdentifierIeType, twanIdentifierIe_p));

    TwanIdentifierTimestampIe* twanIdentifierTimestampIe_p = new (TwanIdentifierTimestampIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(TwanIdentifierTimestampIeType, twanIdentifierTimestampIe_p));

    SecondaryRatUsageDataReportIe* secondaryRatUsageDataReportIe_p = new (SecondaryRatUsageDataReportIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(SecondaryRatUsageDataReportIeType, secondaryRatUsageDataReportIe_p));

    RanNasCauseIe* ranNasCauseIe_p = new (RanNasCauseIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(RanNasCauseIeType, ranNasCauseIe_p));

    EpcoIe* epcoIe_p = new (EpcoIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(EpcoIeType, epcoIe_p));

    MaximumPacketLossRateIe* maximumPacketLossRateIe_p = new (MaximumPacketLossRateIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(MaximumPacketLossRateIeType, maximumPacketLossRateIe_p));

    FContainerIe* fContainerIe_p = new (FContainerIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(FContainerIeType, fContainerIe_p));

    NodeIdentifierIe* nodeIdentifierIe_p = new (NodeIdentifierIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(NodeIdentifierIeType, nodeIdentifierIe_p));

    UpFunctionSelectionIndicationFlagsIe* upFunctionSelectionIndicationFlagsIe_p = new (UpFunctionSelectionIndicationFlagsIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(UpFunctionSelectionIndicationFlagsIeType, upFunctionSelectionIndicationFlagsIe_p));

    HenbInformationReportingIe* henbInformationReportingIe_p = new (HenbInformationReportingIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(HenbInformationReportingIeType, henbInformationReportingIe_p));

    Ip4cpIe* ip4cpIe_p = new (Ip4cpIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(Ip4cpIeType, ip4cpIe_p));

    PresenceReportingAreaActionIe* presenceReportingAreaActionIe_p = new (PresenceReportingAreaActionIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(PresenceReportingAreaActionIeType, presenceReportingAreaActionIe_p));

    NodeTypeIe* nodeTypeIe_p = new (NodeTypeIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(NodeTypeIeType, nodeTypeIe_p));

    PtiIe* ptiIe_p = new (PtiIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(PtiIeType, ptiIe_p));

    TwmiIe* twmiIe_p = new (TwmiIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(TwmiIeType, twmiIe_p));

    MillisecondTimeStampIe* millisecondTimeStampIe_p = new (MillisecondTimeStampIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(MillisecondTimeStampIeType, millisecondTimeStampIe_p));

    IntegerNumberIe* integerNumberIe_p = new (IntegerNumberIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(IntegerNumberIeType, integerNumberIe_p));

    MappedUeUsageTypeIe* mappedUeUsageTypeIe_p = new (MappedUeUsageTypeIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(MappedUeUsageTypeIeType, mappedUeUsageTypeIe_p));

    UliTimestampIe* uliTimestampIe_p = new (UliTimestampIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(UliTimestampIeType, uliTimestampIe_p));

    MetricIe* metricIe_p = new (MetricIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(MetricIeType, metricIe_p));

    RemoteUserIdIe* remoteUserIdIe_p = new (RemoteUserIdIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(RemoteUserIdIeType, remoteUserIdIe_p));

    RemoteUeIpInformationIe* remoteUeIpInformationIe_p = new (RemoteUeIpInformationIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(RemoteUeIpInformationIeType, remoteUeIpInformationIe_p));

    SequenceNumberIe* sequenceNumberIe_p = new (SequenceNumberIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(SequenceNumberIeType, sequenceNumberIe_p));

    ApnAndRelativeCapacityIe* apnAndRelativeCapacityIe_p = new (ApnAndRelativeCapacityIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(ApnAndRelativeCapacityIeType, apnAndRelativeCapacityIe_p));

    ArpIe* arpIe_p = new (ArpIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(ArpIeType, arpIe_p));

    ThrottlingIe* throttlingIe_p = new (ThrottlingIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(ThrottlingIeType, throttlingIe_p));

    PagingAndServiceInformationIe* pagingAndServiceInformationIe_p = new (PagingAndServiceInformationIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(PagingAndServiceInformationIeType, pagingAndServiceInformationIe_p));

    BearerContextIe* bearerContextIe_p = new (BearerContextIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(BearerContextIeType, bearerContextIe_p));

    OverloadControlInformationIe* overloadControlInformationIe_p = new (OverloadControlInformationIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(OverloadControlInformationIeType, overloadControlInformationIe_p));

    LoadControlInformationIe* loadControlInformationIe_p = new (LoadControlInformationIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(LoadControlInformationIeType, loadControlInformationIe_p));

    RemoteUeContextIe* remoteUeContextIe_p = new (RemoteUeContextIe);
    ieObjectContainer.insert(std::pair<Uint8, GtpV2Ie*>(RemoteUeContextIeType, remoteUeContextIe_p));


}

GtpV2IeFactory::~GtpV2IeFactory() {
    // TODO clean up the allocated memory for message objects
}

GtpV2IeFactory& GtpV2IeFactory::getInstance()
{
    static GtpV2IeFactory gtpV2IeFactory;
    return gtpV2IeFactory;
}

GtpV2Ie& GtpV2IeFactory::getIeObject(Uint8 ieType)
{
    std::map<Uint8, GtpV2Ie*>::iterator it;
    it = ieObjectContainer.find(ieType);
    return *(it->second);
}