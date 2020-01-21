/*
 * createSessionRequestMsg.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */
#include "createSessionRequestMsg.h"
#include "../ieClasses/manual/gtpV2Ie.h"
#include "../ieClasses/gtpV2IeFactory.h"
#include "../ieClasses/imsiIe.h"
#include "../ieClasses/msisdnIe.h"
#include "../ieClasses/meiIe.h"
#include "../ieClasses/uliIe.h"
#include "../ieClasses/servingNetworkIe.h"
#include "../ieClasses/ratTypeIe.h"
#include "../ieClasses/indicationIe.h"
#include "../ieClasses/fTeidIe.h"
#include "../ieClasses/fTeidIe.h"
#include "../ieClasses/apnIe.h"
#include "../ieClasses/selectionModeIe.h"
#include "../ieClasses/pdnTypeIe.h"
#include "../ieClasses/paaIe.h"
#include "../ieClasses/apnRestrictionIe.h"
#include "../ieClasses/ambrIe.h"
#include "../ieClasses/ebiIe.h"
#include "../ieClasses/twmiIe.h"
#include "../ieClasses/pcoIe.h"
#include "../ieClasses/bearerContextIe.h"
#include "../ieClasses/bearerContextsToBeCreatedInCreateSessionRequest.h"
#include "../ieClasses/bearerContextIe.h"
#include "../ieClasses/bearerContextsToBeRemovedInCreateSessionRequest.h"
#include "../ieClasses/traceInformationIe.h"
#include "../ieClasses/recoveryIe.h"
#include "../ieClasses/fqCsidIe.h"
#include "../ieClasses/fqCsidIe.h"
#include "../ieClasses/fqCsidIe.h"
#include "../ieClasses/fqCsidIe.h"
#include "../ieClasses/ueTimeZoneIe.h"
#include "../ieClasses/uciIe.h"
#include "../ieClasses/chargingCharacteristicsIe.h"
#include "../ieClasses/localDistinguishedNameIe.h"
#include "../ieClasses/localDistinguishedNameIe.h"
#include "../ieClasses/localDistinguishedNameIe.h"
#include "../ieClasses/localDistinguishedNameIe.h"
#include "../ieClasses/signallingPriorityIndicationIe.h"
#include "../ieClasses/ipAddressIe.h"
#include "../ieClasses/portNumberIe.h"
#include "../ieClasses/additionalProtocolConfigurationOptionsIe.h"
#include "../ieClasses/ipAddressIe.h"
#include "../ieClasses/portNumberIe.h"
#include "../ieClasses/ipAddressIe.h"
#include "../ieClasses/twanIdentifierIe.h"
#include "../ieClasses/ipAddressIe.h"
#include "../ieClasses/cnOperatorSelectionEntityIe.h"
#include "../ieClasses/overloadControlInformationIe.h"
#include "../ieClasses/mmeS4SgsnsOverloadControlInformationInCreateSessionRequest.h"
#include "../ieClasses/overloadControlInformationIe.h"
#include "../ieClasses/sgwsOverloadControlInformationInCreateSessionRequest.h"
#include "../ieClasses/overloadControlInformationIe.h"
#include "../ieClasses/twanEpdgsOverloadControlInformationInCreateSessionRequest.h"
#include "../ieClasses/millisecondTimeStampIe.h"
#include "../ieClasses/integerNumberIe.h"
#include "../ieClasses/twanIdentifierIe.h"
#include "../ieClasses/twanIdentifierTimestampIe.h"
#include "../ieClasses/fContainerIe.h"
#include "../ieClasses/remoteUeContextIe.h"
#include "../ieClasses/remoteUeContextConnectedInCreateSessionRequest.h"
#include "../ieClasses/nodeIdentifierIe.h"
#include "../ieClasses/epcoIe.h"
#include "../ieClasses/servingPlmnRateControlIe.h"
#include "../ieClasses/counterIe.h"
#include "../ieClasses/portNumberIe.h"
#include "../ieClasses/mappedUeUsageTypeIe.h"
#include "../ieClasses/uliIe.h"
#include "../ieClasses/fqdnIe.h"
#include "../ieClasses/secondaryRatUsageDataReportIe.h"
#include "../ieClasses/upFunctionSelectionIndicationFlagsIe.h"

CreateSessionRequestMsg::CreateSessionRequestMsg()
{
    msgType = CreateSessionRequestMsgType;
    Uint16 mandIe;
    mandIe = RatTypeIeType;
    mandIe = (mandIe << 8) | 0; // ratType
    mandatoryIeSet.insert(mandIe);    mandIe = FTeidIeType;
    mandIe = (mandIe << 8) | 0; // senderFTeidForControlPlane
    mandatoryIeSet.insert(mandIe);    mandIe = ApnIeType;
    mandIe = (mandIe << 8) | 0; // accessPointName
    mandatoryIeSet.insert(mandIe);    mandIe = BearerContextIeType;
    mandIe = (mandIe << 8) | 0; // bearerContextsToBeCreated
    mandatoryIeSet.insert(mandIe);
}

CreateSessionRequestMsg::~CreateSessionRequestMsg()
{

}

bool CreateSessionRequestMsg::encodeCreateSessionRequestMsg(MsgBuffer &buffer,
                        CreateSessionRequestMsgData
							const &data)
{
    bool rc = false;
    GtpV2IeHeader header;
    Uint16 startIndex = 0;
    Uint16 endIndex = 0;
    Uint16 length = 0;

    if (data.imsiIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = ImsiIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        ImsiIe imsi=
        dynamic_cast<
        ImsiIe&>(GtpV2IeFactory::getInstance().getIeObject(ImsiIeType));
        rc = imsi.encodeImsiIe(buffer, data.imsi);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: imsi\n");
            return false;
        }
    }

    if (data.msisdnIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = MsisdnIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        MsisdnIe msisdn=
        dynamic_cast<
        MsisdnIe&>(GtpV2IeFactory::getInstance().getIeObject(MsisdnIeType));
        rc = msisdn.encodeMsisdnIe(buffer, data.msisdn);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: msisdn\n");
            return false;
        }
    }

    if (data.meIdentityIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = MeiIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        MeiIe mei=
        dynamic_cast<
        MeiIe&>(GtpV2IeFactory::getInstance().getIeObject(MeiIeType));
        rc = mei.encodeMeiIe(buffer, data.meIdentity);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: meIdentity\n");
            return false;
        }
    }

    if (data.userLocationInformationIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = UliIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        UliIe uli=
        dynamic_cast<
        UliIe&>(GtpV2IeFactory::getInstance().getIeObject(UliIeType));
        rc = uli.encodeUliIe(buffer, data.userLocationInformation);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: userLocationInformation\n");
            return false;
        }
    }

    if (data.servingNetworkIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = ServingNetworkIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        ServingNetworkIe servingNetwork=
        dynamic_cast<
        ServingNetworkIe&>(GtpV2IeFactory::getInstance().getIeObject(ServingNetworkIeType));
        rc = servingNetwork.encodeServingNetworkIe(buffer, data.servingNetwork);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: servingNetwork\n");
            return false;
        }
    }

    // Encode the Ie Header
    header.ieType = RatTypeIeType;
    header.instance = 0;
    header.length = 0; // We will encode the IE first and then update the length
    GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
    startIndex = buffer.getCurrentIndex(); 
    RatTypeIe ratType=
     dynamic_cast<
	 RatTypeIe&>(GtpV2IeFactory::getInstance().getIeObject(RatTypeIeType));
	 rc = ratType.encodeRatTypeIe(buffer, data.ratType);
    endIndex = buffer.getCurrentIndex();
    length = endIndex - startIndex;

    // encode the length value now
    buffer.goToIndex(startIndex - 3);
    buffer.writeUint16(length, false);
    buffer.goToIndex(endIndex);

    if (!(rc))
    { 
      errorStream.add("Failed to encode IE: ratType\n");
      return false;
    }

    if (data.indicationFlagsIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = IndicationIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        IndicationIe indication=
        dynamic_cast<
        IndicationIe&>(GtpV2IeFactory::getInstance().getIeObject(IndicationIeType));
        rc = indication.encodeIndicationIe(buffer, data.indicationFlags);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: indicationFlags\n");
            return false;
        }
    }

    // Encode the Ie Header
    header.ieType = FTeidIeType;
    header.instance = 0;
    header.length = 0; // We will encode the IE first and then update the length
    GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
    startIndex = buffer.getCurrentIndex(); 
    FTeidIe fTeid=
     dynamic_cast<
		 FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
    rc = fTeid.encodeFTeidIe(buffer, data.senderFTeidForControlPlane);
    endIndex = buffer.getCurrentIndex();
    length = endIndex - startIndex;

    // encode the length value now
    buffer.goToIndex(startIndex - 3);
    buffer.writeUint16(length, false);
    buffer.goToIndex(endIndex);

    if (!(rc))
    { 
      errorStream.add("Failed to encode IE: senderFTeidForControlPlane\n");
      return false;
    }
    

    if (data.pgwS5S8AddressForControlPlaneOrPmipIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = FTeidIeType;
        header.instance = 1;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        rc = fTeid.encodeFTeidIe(buffer, data.pgwS5S8AddressForControlPlaneOrPmip);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: pgwS5S8AddressForControlPlaneOrPmip\n");
            return false;
        }
    }


    if (data.selectionModeIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = SelectionModeIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        SelectionModeIe selectionMode=
        dynamic_cast<
        SelectionModeIe&>(GtpV2IeFactory::getInstance().getIeObject(SelectionModeIeType));
        rc = selectionMode.encodeSelectionModeIe(buffer, data.selectionMode);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: selectionMode\n");
            return false;
        }
    }

    // Encode the Ie Header
    header.ieType = ApnIeType;
    header.instance = 0;
    header.length = 0; // We will encode the IE first and then update the length
    GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
    startIndex = buffer.getCurrentIndex(); 
    ApnIe apn=
     dynamic_cast<
	 ApnIe&>(GtpV2IeFactory::getInstance().getIeObject(ApnIeType));
    rc = apn.encodeApnIe(buffer, data.accessPointName);
    endIndex = buffer.getCurrentIndex();
    length = endIndex - startIndex;

    // encode the length value now
    buffer.goToIndex(startIndex - 3);
    buffer.writeUint16(length, false);
    buffer.goToIndex(endIndex);

    if (!(rc))
    { 
      errorStream.add("Failed to encode IE: accessPointName\n");
      return false;
    }


    if (data.pdnTypeIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = PdnTypeIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        PdnTypeIe pdnType=
        dynamic_cast<
        PdnTypeIe&>(GtpV2IeFactory::getInstance().getIeObject(PdnTypeIeType));
        rc = pdnType.encodePdnTypeIe(buffer, data.pdnType);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: pdnType\n");
            return false;
        }
    }

    if (data.pdnAddressAllocationIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = PaaIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        PaaIe paa=
        dynamic_cast<
        PaaIe&>(GtpV2IeFactory::getInstance().getIeObject(PaaIeType));
        rc = paa.encodePaaIe(buffer, data.pdnAddressAllocation);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: pdnAddressAllocation\n");
            return false;
        }
    }

    if (data.maximumApnRestrictionIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = ApnRestrictionIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        ApnRestrictionIe apnRestriction=
        dynamic_cast<
        ApnRestrictionIe&>(GtpV2IeFactory::getInstance().getIeObject(ApnRestrictionIeType));
        rc = apnRestriction.encodeApnRestrictionIe(buffer, data.maximumApnRestriction);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: maximumApnRestriction\n");
            return false;
        }
    }

    if (data.aggregateMaximumBitRateIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = AmbrIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        AmbrIe ambr=
        dynamic_cast<
        AmbrIe&>(GtpV2IeFactory::getInstance().getIeObject(AmbrIeType));
        rc = ambr.encodeAmbrIe(buffer, data.aggregateMaximumBitRate);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: aggregateMaximumBitRate\n");
            return false;
        }
    }


    if (data.linkedEpsBearerIdIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = EbiIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        EbiIe ebi=
        dynamic_cast<
        EbiIe&>(GtpV2IeFactory::getInstance().getIeObject(EbiIeType));
        rc = ebi.encodeEbiIe(buffer, data.linkedEpsBearerId);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: linkedEpsBearerId\n");
            return false;
        }
    }

    if (data.trustedWlanModeIndicationIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = TwmiIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        TwmiIe twmi=
        dynamic_cast<
        TwmiIe&>(GtpV2IeFactory::getInstance().getIeObject(TwmiIeType));
        rc = twmi.encodeTwmiIe(buffer, data.trustedWlanModeIndication);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: trustedWlanModeIndication\n");
            return false;
        }
    }

    if (data.protocolConfigurationOptionsIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = PcoIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        PcoIe pco=
        dynamic_cast<
        PcoIe&>(GtpV2IeFactory::getInstance().getIeObject(PcoIeType));
        rc = pco.encodePcoIe(buffer, data.protocolConfigurationOptions);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: protocolConfigurationOptions\n");
            return false;
        }
    }

 // First validate if the applicatoin provided more than the expected cardinality
 if (data.bearerContextsToBeCreatedCount > 11)
 {
     errorStream.add("Number of entries of bearerContextsToBeCreated exceeded\n");
     errorStream.add("Expected count: 11 Received count: ");
     errorStream.add("data.bearerContextsToBeCreatedCount");
     errorStream.endOfLine();
     return false;
 }
 for (Uint8 i = 0; i < data.bearerContextsToBeCreatedCount; i++)
 {
     // Encode the Ie Header
      header.ieType = BearerContextIeType;
      header.instance = 0;
      header.length = 0; // We will encode the IE first and then update the length
      GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
      startIndex = buffer.getCurrentIndex(); 
      BearerContextIe bearerContext=
      dynamic_cast<
      BearerContextIe&>(GtpV2IeFactory::getInstance().
      getIeObject(BearerContextIeType));
      BearerContextsToBeCreatedInCreateSessionRequest groupedIeInstance = dynamic_cast<BearerContextsToBeCreatedInCreateSessionRequest&>(bearerContext.getGroupedIe(msgType, 0));
      rc = groupedIeInstance.encodeBearerContextsToBeCreatedInCreateSessionRequest(buffer, data.bearerContextsToBeCreated[i]);
     endIndex = buffer.getCurrentIndex();
     length = endIndex - startIndex;

     // encode the length value now
     buffer.goToIndex(startIndex - 3);
     buffer.writeUint16(length, false);
     buffer.goToIndex(endIndex);
  }

    if (!(rc))
    { 
      errorStream.add("Failed to encode IE: bearerContextsToBeCreated\n");
      return false;
    }


        // First validate if the applicatoin provided more than the expected cardinality
    if (data.bearerContextsToBeRemovedCount > 11)
    {
        errorStream.add("Number of entries of bearerContextsToBeRemoved exceeded\n");
        errorStream.add("Expected count: 11 Received count: ");
        errorStream.add("data.bearerContextsToBeRemovedCount");
        errorStream.endOfLine();
        return false;
    }
    for (Uint8 i = 0; i < data.bearerContextsToBeRemovedCount; i++)
    {
        // Encode the Ie Header
        header.ieType = BearerContextIeType;
        header.instance = 1;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        BearerContextIe bearerContext=
        dynamic_cast<
        BearerContextIe&>(GtpV2IeFactory::getInstance().
        getIeObject(BearerContextIeType));
        BearerContextsToBeRemovedInCreateSessionRequest groupedIeInstance = dynamic_cast<BearerContextsToBeRemovedInCreateSessionRequest&>(bearerContext.getGroupedIe(msgType, 1));
        rc = groupedIeInstance.encodeBearerContextsToBeRemovedInCreateSessionRequest(buffer, data.bearerContextsToBeRemoved[i]);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;

        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);
    }

    if (!(rc))
    { 
        errorStream.add("Failed to encode IE: bearerContextsToBeRemoved\n");
        return false;
    }

    if (data.traceInformationIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = TraceInformationIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        TraceInformationIe traceInformation=
        dynamic_cast<
        TraceInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(TraceInformationIeType));
        rc = traceInformation.encodeTraceInformationIe(buffer, data.traceInformation);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: traceInformation\n");
            return false;
        }
    }

    if (data.recoveryIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = RecoveryIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        RecoveryIe recovery=
        dynamic_cast<
        RecoveryIe&>(GtpV2IeFactory::getInstance().getIeObject(RecoveryIeType));
        rc = recovery.encodeRecoveryIe(buffer, data.recovery);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: recovery\n");
            return false;
        }
    }

    if (data.mmeFqCsidIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = FqCsidIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        FqCsidIe fqCsid=
        dynamic_cast<
        FqCsidIe&>(GtpV2IeFactory::getInstance().getIeObject(FqCsidIeType));
        rc = fqCsid.encodeFqCsidIe(buffer, data.mmeFqCsid);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: mmeFqCsid\n");
            return false;
        }
    }

    if (data.sgwFqCsidIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = FqCsidIeType;
        header.instance = 1;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        FqCsidIe fqCsid=
        dynamic_cast<
        FqCsidIe&>(GtpV2IeFactory::getInstance().getIeObject(FqCsidIeType));
        rc = fqCsid.encodeFqCsidIe(buffer, data.sgwFqCsid);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: sgwFqCsid\n");
            return false;
        }
    }

    if (data.epdgFqCsidIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = FqCsidIeType;
        header.instance = 2;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        FqCsidIe fqCsid=
        dynamic_cast<
        FqCsidIe&>(GtpV2IeFactory::getInstance().getIeObject(FqCsidIeType));
        rc = fqCsid.encodeFqCsidIe(buffer, data.epdgFqCsid);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: epdgFqCsid\n");
            return false;
        }
    }

    if (data.twanFqCsidIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = FqCsidIeType;
        header.instance = 3;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        FqCsidIe fqCsid=
        dynamic_cast<
        FqCsidIe&>(GtpV2IeFactory::getInstance().getIeObject(FqCsidIeType));
        rc = fqCsid.encodeFqCsidIe(buffer, data.twanFqCsid);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: twanFqCsid\n");
            return false;
        }
    }

    if (data.ueTimeZoneIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = UeTimeZoneIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        UeTimeZoneIe ueTimeZone=
        dynamic_cast<
        UeTimeZoneIe&>(GtpV2IeFactory::getInstance().getIeObject(UeTimeZoneIeType));
        rc = ueTimeZone.encodeUeTimeZoneIe(buffer, data.ueTimeZone);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: ueTimeZone\n");
            return false;
        }
    }

    if (data.userCsgInformationIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = UciIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        UciIe uci=
        dynamic_cast<
        UciIe&>(GtpV2IeFactory::getInstance().getIeObject(UciIeType));
        rc = uci.encodeUciIe(buffer, data.userCsgInformation);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: userCsgInformation\n");
            return false;
        }
    }

    if (data.chargingCharacteristicsIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = ChargingCharacteristicsIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        ChargingCharacteristicsIe chargingCharacteristics=
        dynamic_cast<
        ChargingCharacteristicsIe&>(GtpV2IeFactory::getInstance().getIeObject(ChargingCharacteristicsIeType));
        rc = chargingCharacteristics.encodeChargingCharacteristicsIe(buffer, data.chargingCharacteristics);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: chargingCharacteristics\n");
            return false;
        }
    }

    if (data.mmeS4SgsnLdnIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = LocalDistinguishedNameIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        LocalDistinguishedNameIe localDistinguishedName=
        dynamic_cast<
        LocalDistinguishedNameIe&>(GtpV2IeFactory::getInstance().getIeObject(LocalDistinguishedNameIeType));
        rc = localDistinguishedName.encodeLocalDistinguishedNameIe(buffer, data.mmeS4SgsnLdn);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: mmeS4SgsnLdn\n");
            return false;
        }
    }

    if (data.sgwLdnIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = LocalDistinguishedNameIeType;
        header.instance = 1;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        LocalDistinguishedNameIe localDistinguishedName=
        dynamic_cast<
        LocalDistinguishedNameIe&>(GtpV2IeFactory::getInstance().getIeObject(LocalDistinguishedNameIeType));
        rc = localDistinguishedName.encodeLocalDistinguishedNameIe(buffer, data.sgwLdn);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: sgwLdn\n");
            return false;
        }
    }

    if (data.epdgLdnIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = LocalDistinguishedNameIeType;
        header.instance = 2;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        LocalDistinguishedNameIe localDistinguishedName=
        dynamic_cast<
        LocalDistinguishedNameIe&>(GtpV2IeFactory::getInstance().getIeObject(LocalDistinguishedNameIeType));
        rc = localDistinguishedName.encodeLocalDistinguishedNameIe(buffer, data.epdgLdn);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: epdgLdn\n");
            return false;
        }
    }

    if (data.twanLdnIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = LocalDistinguishedNameIeType;
        header.instance = 3;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        LocalDistinguishedNameIe localDistinguishedName=
        dynamic_cast<
        LocalDistinguishedNameIe&>(GtpV2IeFactory::getInstance().getIeObject(LocalDistinguishedNameIeType));
        rc = localDistinguishedName.encodeLocalDistinguishedNameIe(buffer, data.twanLdn);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: twanLdn\n");
            return false;
        }
    }

    if (data.signallingPriorityIndicationIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = SignallingPriorityIndicationIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        SignallingPriorityIndicationIe signallingPriorityIndication=
        dynamic_cast<
        SignallingPriorityIndicationIe&>(GtpV2IeFactory::getInstance().getIeObject(SignallingPriorityIndicationIeType));
        rc = signallingPriorityIndication.encodeSignallingPriorityIndicationIe(buffer, data.signallingPriorityIndication);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: signallingPriorityIndication\n");
            return false;
        }
    }

    if (data.ueLocalIpAddressIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = IpAddressIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        IpAddressIe ipAddress=
        dynamic_cast<
        IpAddressIe&>(GtpV2IeFactory::getInstance().getIeObject(IpAddressIeType));
        rc = ipAddress.encodeIpAddressIe(buffer, data.ueLocalIpAddress);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: ueLocalIpAddress\n");
            return false;
        }
    }

    if (data.ueUdpPortIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = PortNumberIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        PortNumberIe portNumber=
        dynamic_cast<
        PortNumberIe&>(GtpV2IeFactory::getInstance().getIeObject(PortNumberIeType));
        rc = portNumber.encodePortNumberIe(buffer, data.ueUdpPort);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: ueUdpPort\n");
            return false;
        }
    }

    if (data.additionalProtocolConfigurationOptionsIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = AdditionalProtocolConfigurationOptionsIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        AdditionalProtocolConfigurationOptionsIe additionalProtocolConfigurationOptions=
        dynamic_cast<
        AdditionalProtocolConfigurationOptionsIe&>(GtpV2IeFactory::getInstance().getIeObject(AdditionalProtocolConfigurationOptionsIeType));
        rc = additionalProtocolConfigurationOptions.encodeAdditionalProtocolConfigurationOptionsIe(buffer, data.additionalProtocolConfigurationOptions);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: additionalProtocolConfigurationOptions\n");
            return false;
        }
    }

    if (data.hNbLocalIpAddressIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = IpAddressIeType;
        header.instance = 1;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        IpAddressIe ipAddress=
        dynamic_cast<
        IpAddressIe&>(GtpV2IeFactory::getInstance().getIeObject(IpAddressIeType));
        rc = ipAddress.encodeIpAddressIe(buffer, data.hNbLocalIpAddress);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: hNbLocalIpAddress\n");
            return false;
        }
    }

    if (data.hNbUdpPortIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = PortNumberIeType;
        header.instance = 1;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        PortNumberIe portNumber=
        dynamic_cast<
        PortNumberIe&>(GtpV2IeFactory::getInstance().getIeObject(PortNumberIeType));
        rc = portNumber.encodePortNumberIe(buffer, data.hNbUdpPort);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: hNbUdpPort\n");
            return false;
        }
    }

    if (data.mmeS4SgsnIdentifierIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = IpAddressIeType;
        header.instance = 2;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        IpAddressIe ipAddress=
        dynamic_cast<
        IpAddressIe&>(GtpV2IeFactory::getInstance().getIeObject(IpAddressIeType));
        rc = ipAddress.encodeIpAddressIe(buffer, data.mmeS4SgsnIdentifier);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: mmeS4SgsnIdentifier\n");
            return false;
        }
    }

    if (data.twanIdentifierIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = TwanIdentifierIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        TwanIdentifierIe twanIdentifier=
        dynamic_cast<
        TwanIdentifierIe&>(GtpV2IeFactory::getInstance().getIeObject(TwanIdentifierIeType));
        rc = twanIdentifier.encodeTwanIdentifierIe(buffer, data.twanIdentifier);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: twanIdentifier\n");
            return false;
        }
    }

    if (data.epdgIpAddressIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = IpAddressIeType;
        header.instance = 3;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        IpAddressIe ipAddress=
        dynamic_cast<
        IpAddressIe&>(GtpV2IeFactory::getInstance().getIeObject(IpAddressIeType));
        rc = ipAddress.encodeIpAddressIe(buffer, data.epdgIpAddress);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: epdgIpAddress\n");
            return false;
        }
    }

    if (data.cnOperatorSelectionEntityIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = CnOperatorSelectionEntityIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        CnOperatorSelectionEntityIe cnOperatorSelectionEntity=
        dynamic_cast<
        CnOperatorSelectionEntityIe&>(GtpV2IeFactory::getInstance().getIeObject(CnOperatorSelectionEntityIeType));
        rc = cnOperatorSelectionEntity.encodeCnOperatorSelectionEntityIe(buffer, data.cnOperatorSelectionEntity);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: cnOperatorSelectionEntity\n");
            return false;
        }
    }

    if (data.mmeS4SgsnsOverloadControlInformationIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = OverloadControlInformationIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
        MmeS4SgsnsOverloadControlInformationInCreateSessionRequest groupedIeInstance =
        dynamic_cast<
         MmeS4SgsnsOverloadControlInformationInCreateSessionRequest&>(overloadControlInformation.getGroupedIe(msgType, 0));
        rc = groupedIeInstance.encodeMmeS4SgsnsOverloadControlInformationInCreateSessionRequest(buffer, data.mmeS4SgsnsOverloadControlInformation);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: mmeS4SgsnsOverloadControlInformation\n");
            return false;
        }
    }

    if (data.sgwsOverloadControlInformationIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = OverloadControlInformationIeType;
        header.instance = 1;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
        SgwsOverloadControlInformationInCreateSessionRequest groupedIeInstance =
        dynamic_cast<
         SgwsOverloadControlInformationInCreateSessionRequest&>(overloadControlInformation.getGroupedIe(msgType, 1));
        rc = groupedIeInstance.encodeSgwsOverloadControlInformationInCreateSessionRequest(buffer, data.sgwsOverloadControlInformation);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: sgwsOverloadControlInformation\n");
            return false;
        }
    }

    if (data.twanEpdgsOverloadControlInformationIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = OverloadControlInformationIeType;
        header.instance = 2;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
        TwanEpdgsOverloadControlInformationInCreateSessionRequest groupedIeInstance =
        dynamic_cast<
         TwanEpdgsOverloadControlInformationInCreateSessionRequest&>(overloadControlInformation.getGroupedIe(msgType, 2));
        rc = groupedIeInstance.encodeTwanEpdgsOverloadControlInformationInCreateSessionRequest(buffer, data.twanEpdgsOverloadControlInformation);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: twanEpdgsOverloadControlInformation\n");
            return false;
        }
    }

    if (data.originationTimeStampIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = MillisecondTimeStampIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        MillisecondTimeStampIe millisecondTimeStamp=
        dynamic_cast<
        MillisecondTimeStampIe&>(GtpV2IeFactory::getInstance().getIeObject(MillisecondTimeStampIeType));
        rc = millisecondTimeStamp.encodeMillisecondTimeStampIe(buffer, data.originationTimeStamp);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: originationTimeStamp\n");
            return false;
        }
    }

    if (data.maximumWaitTimeIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = IntegerNumberIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        IntegerNumberIe integerNumber=
        dynamic_cast<
        IntegerNumberIe&>(GtpV2IeFactory::getInstance().getIeObject(IntegerNumberIeType));
        rc = integerNumber.encodeIntegerNumberIe(buffer, data.maximumWaitTime);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: maximumWaitTime\n");
            return false;
        }
    }

    if (data.wlanLocationInformationIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = TwanIdentifierIeType;
        header.instance = 1;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        TwanIdentifierIe twanIdentifier=
        dynamic_cast<
        TwanIdentifierIe&>(GtpV2IeFactory::getInstance().getIeObject(TwanIdentifierIeType));
        rc = twanIdentifier.encodeTwanIdentifierIe(buffer, data.wlanLocationInformation);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: wlanLocationInformation\n");
            return false;
        }
    }

    if (data.wlanLocationTimestampIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = TwanIdentifierTimestampIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        TwanIdentifierTimestampIe twanIdentifierTimestamp=
        dynamic_cast<
        TwanIdentifierTimestampIe&>(GtpV2IeFactory::getInstance().getIeObject(TwanIdentifierTimestampIeType));
        rc = twanIdentifierTimestamp.encodeTwanIdentifierTimestampIe(buffer, data.wlanLocationTimestamp);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: wlanLocationTimestamp\n");
            return false;
        }
    }

    if (data.nbifomContainerIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = FContainerIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        FContainerIe fContainer=
        dynamic_cast<
        FContainerIe&>(GtpV2IeFactory::getInstance().getIeObject(FContainerIeType));
        rc = fContainer.encodeFContainerIe(buffer, data.nbifomContainer);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: nbifomContainer\n");
            return false;
        }
    }

    if (data.remoteUeContextConnectedIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = RemoteUeContextIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        RemoteUeContextIe remoteUeContext=
        dynamic_cast<
        RemoteUeContextIe&>(GtpV2IeFactory::getInstance().getIeObject(RemoteUeContextIeType));
        RemoteUeContextConnectedInCreateSessionRequest groupedIeInstance =
        dynamic_cast<
         RemoteUeContextConnectedInCreateSessionRequest&>(remoteUeContext.getGroupedIe(msgType, 0));
        rc = groupedIeInstance.encodeRemoteUeContextConnectedInCreateSessionRequest(buffer, data.remoteUeContextConnected);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: remoteUeContextConnected\n");
            return false;
        }
    }

    if (data.a3gppAaaServerIdentifierIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = NodeIdentifierIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        NodeIdentifierIe nodeIdentifier=
        dynamic_cast<
        NodeIdentifierIe&>(GtpV2IeFactory::getInstance().getIeObject(NodeIdentifierIeType));
        rc = nodeIdentifier.encodeNodeIdentifierIe(buffer, data.a3gppAaaServerIdentifier);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: a3gppAaaServerIdentifier\n");
            return false;
        }
    }

    if (data.extendedProtocolConfigurationOptionsIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = EpcoIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        EpcoIe epco=
        dynamic_cast<
        EpcoIe&>(GtpV2IeFactory::getInstance().getIeObject(EpcoIeType));
        rc = epco.encodeEpcoIe(buffer, data.extendedProtocolConfigurationOptions);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: extendedProtocolConfigurationOptions\n");
            return false;
        }
    }

    if (data.servingPlmnRateControlIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = ServingPlmnRateControlIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        ServingPlmnRateControlIe servingPlmnRateControl=
        dynamic_cast<
        ServingPlmnRateControlIe&>(GtpV2IeFactory::getInstance().getIeObject(ServingPlmnRateControlIeType));
        rc = servingPlmnRateControl.encodeServingPlmnRateControlIe(buffer, data.servingPlmnRateControl);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: servingPlmnRateControl\n");
            return false;
        }
    }

    if (data.moExceptionDataCounterIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = CounterIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        CounterIe counter=
        dynamic_cast<
        CounterIe&>(GtpV2IeFactory::getInstance().getIeObject(CounterIeType));
        rc = counter.encodeCounterIe(buffer, data.moExceptionDataCounter);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: moExceptionDataCounter\n");
            return false;
        }
    }

    if (data.ueTcpPortIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = PortNumberIeType;
        header.instance = 2;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        PortNumberIe portNumber=
        dynamic_cast<
        PortNumberIe&>(GtpV2IeFactory::getInstance().getIeObject(PortNumberIeType));
        rc = portNumber.encodePortNumberIe(buffer, data.ueTcpPort);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: ueTcpPort\n");
            return false;
        }
    }

    if (data.mappedUeUsageTypeIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = MappedUeUsageTypeIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        MappedUeUsageTypeIe mappedUeUsageType=
        dynamic_cast<
        MappedUeUsageTypeIe&>(GtpV2IeFactory::getInstance().getIeObject(MappedUeUsageTypeIeType));
        rc = mappedUeUsageType.encodeMappedUeUsageTypeIe(buffer, data.mappedUeUsageType);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: mappedUeUsageType\n");
            return false;
        }
    }

    if (data.userLocationInformationForSgwIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = UliIeType;
        header.instance = 1;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        UliIe uli=
        dynamic_cast<
        UliIe&>(GtpV2IeFactory::getInstance().getIeObject(UliIeType));
        rc = uli.encodeUliIe(buffer, data.userLocationInformationForSgw);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: userLocationInformationForSgw\n");
            return false;
        }
    }

    if (data.sgwUNodeNameIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = FqdnIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        FqdnIe fqdn=
        dynamic_cast<
        FqdnIe&>(GtpV2IeFactory::getInstance().getIeObject(FqdnIeType));
        rc = fqdn.encodeFqdnIe(buffer, data.sgwUNodeName);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: sgwUNodeName\n");
            return false;
        }
    }

    if (data.secondaryRatUsageDataReportIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = SecondaryRatUsageDataReportIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        SecondaryRatUsageDataReportIe secondaryRatUsageDataReport=
        dynamic_cast<
        SecondaryRatUsageDataReportIe&>(GtpV2IeFactory::getInstance().getIeObject(SecondaryRatUsageDataReportIeType));
        rc = secondaryRatUsageDataReport.encodeSecondaryRatUsageDataReportIe(buffer, data.secondaryRatUsageDataReport);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: secondaryRatUsageDataReport\n");
            return false;
        }
    }

    if (data.upFunctionSelectionIndicationFlagsIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = UpFunctionSelectionIndicationFlagsIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        UpFunctionSelectionIndicationFlagsIe upFunctionSelectionIndicationFlags=
        dynamic_cast<
        UpFunctionSelectionIndicationFlagsIe&>(GtpV2IeFactory::getInstance().getIeObject(UpFunctionSelectionIndicationFlagsIeType));
        rc = upFunctionSelectionIndicationFlags.encodeUpFunctionSelectionIndicationFlagsIe(buffer, data.upFunctionSelectionIndicationFlags);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: upFunctionSelectionIndicationFlags\n");
            return false;
        }
    }
    return rc;

}

bool CreateSessionRequestMsg::decodeCreateSessionRequestMsg(MsgBuffer &buffer,
 CreateSessionRequestMsgData 
 &data, Uint16 length)
{

    bool rc = false;
    GtpV2IeHeader ieHeader;
  
    set<Uint16> mandatoryIeLocalList = mandatoryIeSet;
    while (buffer.lengthLeft() > IE_HEADER_SIZE)
    {
        GtpV2Ie::decodeGtpV2IeHeader(buffer, ieHeader);
        if (ieHeader.length > buffer.lengthLeft())
        {
            // We do not have enough bytes left in the message for this IE
            errorStream.add("IE Length exceeds beyond message boundary\n");
            errorStream.add("  Offending IE Type: ");
            errorStream.add(ieHeader.ieType);
            errorStream.add("\n  Ie Length in Header: ");
            errorStream.add(ieHeader.length);
            errorStream.add("\n  Bytes left in message: ");
            errorStream.add(buffer.lengthLeft());
            errorStream.endOfLine();
            return false;
        }

        switch (ieHeader.ieType){
     
            case ImsiIeType:
            {
                ImsiIe ieObject =
                dynamic_cast<
                ImsiIe&>(GtpV2IeFactory::getInstance().getIeObject(ImsiIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeImsiIe(buffer, data.imsi, ieHeader.length);

                    data.imsiIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: imsi\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case MsisdnIeType:
            {
                MsisdnIe ieObject =
                dynamic_cast<
                MsisdnIe&>(GtpV2IeFactory::getInstance().getIeObject(MsisdnIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeMsisdnIe(buffer, data.msisdn, ieHeader.length);

                    data.msisdnIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: msisdn\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case MeiIeType:
            {
                MeiIe ieObject =
                dynamic_cast<
                MeiIe&>(GtpV2IeFactory::getInstance().getIeObject(MeiIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeMeiIe(buffer, data.meIdentity, ieHeader.length);

                    data.meIdentityIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: meIdentity\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case UliIeType:
            {
                UliIe ieObject =
                dynamic_cast<
                UliIe&>(GtpV2IeFactory::getInstance().getIeObject(UliIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeUliIe(buffer, data.userLocationInformation, ieHeader.length);

                    data.userLocationInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: userLocationInformation\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 1)
                {
					rc = ieObject.decodeUliIe(buffer, data.userLocationInformationForSgw, ieHeader.length);

                    data.userLocationInformationForSgwIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: userLocationInformationForSgw\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case ServingNetworkIeType:
            {
                ServingNetworkIe ieObject =
                dynamic_cast<
                ServingNetworkIe&>(GtpV2IeFactory::getInstance().getIeObject(ServingNetworkIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeServingNetworkIe(buffer, data.servingNetwork, ieHeader.length);

                    data.servingNetworkIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: servingNetwork\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case RatTypeIeType:
            {
                RatTypeIe ieObject =
                dynamic_cast<
                RatTypeIe&>(GtpV2IeFactory::getInstance().getIeObject(RatTypeIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeRatTypeIe(buffer, data.ratType, ieHeader.length);

                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: ratType\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case IndicationIeType:
            {
                IndicationIe ieObject =
                dynamic_cast<
                IndicationIe&>(GtpV2IeFactory::getInstance().getIeObject(IndicationIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeIndicationIe(buffer, data.indicationFlags, ieHeader.length);

                    data.indicationFlagsIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: indicationFlags\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case FTeidIeType:
            {
                FTeidIe ieObject =
                dynamic_cast<
                FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeFTeidIe(buffer, data.senderFTeidForControlPlane, ieHeader.length);

                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: senderFTeidForControlPlane\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 1)
                {
					rc = ieObject.decodeFTeidIe(buffer, data.pgwS5S8AddressForControlPlaneOrPmip, ieHeader.length);

                    data.pgwS5S8AddressForControlPlaneOrPmipIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: pgwS5S8AddressForControlPlaneOrPmip\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case ApnIeType:
            {
                ApnIe ieObject =
                dynamic_cast<
                ApnIe&>(GtpV2IeFactory::getInstance().getIeObject(ApnIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeApnIe(buffer, data.accessPointName, ieHeader.length);

                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: accessPointName\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case SelectionModeIeType:
            {
                SelectionModeIe ieObject =
                dynamic_cast<
                SelectionModeIe&>(GtpV2IeFactory::getInstance().getIeObject(SelectionModeIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeSelectionModeIe(buffer, data.selectionMode, ieHeader.length);

                    data.selectionModeIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: selectionMode\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case PdnTypeIeType:
            {
                PdnTypeIe ieObject =
                dynamic_cast<
                PdnTypeIe&>(GtpV2IeFactory::getInstance().getIeObject(PdnTypeIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodePdnTypeIe(buffer, data.pdnType, ieHeader.length);

                    data.pdnTypeIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: pdnType\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case PaaIeType:
            {
                PaaIe ieObject =
                dynamic_cast<
                PaaIe&>(GtpV2IeFactory::getInstance().getIeObject(PaaIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodePaaIe(buffer, data.pdnAddressAllocation, ieHeader.length);

                    data.pdnAddressAllocationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: pdnAddressAllocation\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case ApnRestrictionIeType:
            {
                ApnRestrictionIe ieObject =
                dynamic_cast<
                ApnRestrictionIe&>(GtpV2IeFactory::getInstance().getIeObject(ApnRestrictionIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeApnRestrictionIe(buffer, data.maximumApnRestriction, ieHeader.length);

                    data.maximumApnRestrictionIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: maximumApnRestriction\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case AmbrIeType:
            {
                AmbrIe ieObject =
                dynamic_cast<
                AmbrIe&>(GtpV2IeFactory::getInstance().getIeObject(AmbrIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeAmbrIe(buffer, data.aggregateMaximumBitRate, ieHeader.length);

                    data.aggregateMaximumBitRateIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: aggregateMaximumBitRate\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case EbiIeType:
            {
                EbiIe ieObject =
                dynamic_cast<
                EbiIe&>(GtpV2IeFactory::getInstance().getIeObject(EbiIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeEbiIe(buffer, data.linkedEpsBearerId, ieHeader.length);

                    data.linkedEpsBearerIdIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: linkedEpsBearerId\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case TwmiIeType:
            {
                TwmiIe ieObject =
                dynamic_cast<
                TwmiIe&>(GtpV2IeFactory::getInstance().getIeObject(TwmiIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeTwmiIe(buffer, data.trustedWlanModeIndication, ieHeader.length);

                    data.trustedWlanModeIndicationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: trustedWlanModeIndication\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case PcoIeType:
            {
                PcoIe ieObject =
                dynamic_cast<
                PcoIe&>(GtpV2IeFactory::getInstance().getIeObject(PcoIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodePcoIe(buffer, data.protocolConfigurationOptions, ieHeader.length);

                    data.protocolConfigurationOptionsIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: protocolConfigurationOptions\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case BearerContextIeType:
            {
                BearerContextIe ieObject =
                dynamic_cast<
                BearerContextIe&>(GtpV2IeFactory::getInstance().getIeObject(BearerContextIeType));

                if(ieHeader.instance == 0)
                {
					// First check if we have enough space left to decode and store this instance
                    if (data.bearerContextsToBeCreatedCount == 11)
                    {
                        errorStream.add("More than 11 instances of bearerContextsToBeCreated received\n");
                        return false;
                    }
                    BearerContextsToBeCreatedInCreateSessionRequest groupedIeInstance =
                    dynamic_cast<
                    BearerContextsToBeCreatedInCreateSessionRequest&>(ieObject.getGroupedIe(msgType, 0));
                    rc = groupedIeInstance.decodeBearerContextsToBeCreatedInCreateSessionRequest(buffer,
                    data.bearerContextsToBeCreated[data.bearerContextsToBeCreatedCount], ieHeader.length);
                    data.bearerContextsToBeCreatedCount++; // TODO Count validation

                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: bearerContextsToBeCreated\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 1)
                {
					// First check if we have enough space left to decode and store this instance
                    if (data.bearerContextsToBeRemovedCount == 11)
                    {
                        errorStream.add("More than 11 instances of bearerContextsToBeRemoved received\n");
                        return false;
                    }
                    BearerContextsToBeRemovedInCreateSessionRequest groupedIeInstance =
                    dynamic_cast<
                    BearerContextsToBeRemovedInCreateSessionRequest&>(ieObject.getGroupedIe(msgType, 1));
                    rc = groupedIeInstance.decodeBearerContextsToBeRemovedInCreateSessionRequest(buffer,
                    data.bearerContextsToBeRemoved[data.bearerContextsToBeRemovedCount], ieHeader.length);
                    data.bearerContextsToBeRemovedCount++; // TODO Count validation

                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: bearerContextsToBeRemoved\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case TraceInformationIeType:
            {
                TraceInformationIe ieObject =
                dynamic_cast<
                TraceInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(TraceInformationIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeTraceInformationIe(buffer, data.traceInformation, ieHeader.length);

                    data.traceInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: traceInformation\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case RecoveryIeType:
            {
                RecoveryIe ieObject =
                dynamic_cast<
                RecoveryIe&>(GtpV2IeFactory::getInstance().getIeObject(RecoveryIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeRecoveryIe(buffer, data.recovery, ieHeader.length);

                    data.recoveryIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: recovery\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case FqCsidIeType:
            {
                FqCsidIe ieObject =
                dynamic_cast<
                FqCsidIe&>(GtpV2IeFactory::getInstance().getIeObject(FqCsidIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeFqCsidIe(buffer, data.mmeFqCsid, ieHeader.length);

                    data.mmeFqCsidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: mmeFqCsid\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 1)
                {
					rc = ieObject.decodeFqCsidIe(buffer, data.sgwFqCsid, ieHeader.length);

                    data.sgwFqCsidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: sgwFqCsid\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 2)
                {
					rc = ieObject.decodeFqCsidIe(buffer, data.epdgFqCsid, ieHeader.length);

                    data.epdgFqCsidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: epdgFqCsid\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 3)
                {
					rc = ieObject.decodeFqCsidIe(buffer, data.twanFqCsid, ieHeader.length);

                    data.twanFqCsidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: twanFqCsid\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case UeTimeZoneIeType:
            {
                UeTimeZoneIe ieObject =
                dynamic_cast<
                UeTimeZoneIe&>(GtpV2IeFactory::getInstance().getIeObject(UeTimeZoneIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeUeTimeZoneIe(buffer, data.ueTimeZone, ieHeader.length);

                    data.ueTimeZoneIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: ueTimeZone\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case UciIeType:
            {
                UciIe ieObject =
                dynamic_cast<
                UciIe&>(GtpV2IeFactory::getInstance().getIeObject(UciIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeUciIe(buffer, data.userCsgInformation, ieHeader.length);

                    data.userCsgInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: userCsgInformation\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case ChargingCharacteristicsIeType:
            {
                ChargingCharacteristicsIe ieObject =
                dynamic_cast<
                ChargingCharacteristicsIe&>(GtpV2IeFactory::getInstance().getIeObject(ChargingCharacteristicsIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeChargingCharacteristicsIe(buffer, data.chargingCharacteristics, ieHeader.length);

                    data.chargingCharacteristicsIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: chargingCharacteristics\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case LocalDistinguishedNameIeType:
            {
                LocalDistinguishedNameIe ieObject =
                dynamic_cast<
                LocalDistinguishedNameIe&>(GtpV2IeFactory::getInstance().getIeObject(LocalDistinguishedNameIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeLocalDistinguishedNameIe(buffer, data.mmeS4SgsnLdn, ieHeader.length);

                    data.mmeS4SgsnLdnIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: mmeS4SgsnLdn\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 1)
                {
					rc = ieObject.decodeLocalDistinguishedNameIe(buffer, data.sgwLdn, ieHeader.length);

                    data.sgwLdnIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: sgwLdn\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 2)
                {
					rc = ieObject.decodeLocalDistinguishedNameIe(buffer, data.epdgLdn, ieHeader.length);

                    data.epdgLdnIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: epdgLdn\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 3)
                {
					rc = ieObject.decodeLocalDistinguishedNameIe(buffer, data.twanLdn, ieHeader.length);

                    data.twanLdnIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: twanLdn\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case SignallingPriorityIndicationIeType:
            {
                SignallingPriorityIndicationIe ieObject =
                dynamic_cast<
                SignallingPriorityIndicationIe&>(GtpV2IeFactory::getInstance().getIeObject(SignallingPriorityIndicationIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeSignallingPriorityIndicationIe(buffer, data.signallingPriorityIndication, ieHeader.length);

                    data.signallingPriorityIndicationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: signallingPriorityIndication\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case IpAddressIeType:
            {
                IpAddressIe ieObject =
                dynamic_cast<
                IpAddressIe&>(GtpV2IeFactory::getInstance().getIeObject(IpAddressIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeIpAddressIe(buffer, data.ueLocalIpAddress, ieHeader.length);

                    data.ueLocalIpAddressIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: ueLocalIpAddress\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 1)
                {
					rc = ieObject.decodeIpAddressIe(buffer, data.hNbLocalIpAddress, ieHeader.length);

                    data.hNbLocalIpAddressIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: hNbLocalIpAddress\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 2)
                {
					rc = ieObject.decodeIpAddressIe(buffer, data.mmeS4SgsnIdentifier, ieHeader.length);

                    data.mmeS4SgsnIdentifierIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: mmeS4SgsnIdentifier\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 3)
                {
					rc = ieObject.decodeIpAddressIe(buffer, data.epdgIpAddress, ieHeader.length);

                    data.epdgIpAddressIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: epdgIpAddress\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case PortNumberIeType:
            {
                PortNumberIe ieObject =
                dynamic_cast<
                PortNumberIe&>(GtpV2IeFactory::getInstance().getIeObject(PortNumberIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodePortNumberIe(buffer, data.ueUdpPort, ieHeader.length);

                    data.ueUdpPortIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: ueUdpPort\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 1)
                {
					rc = ieObject.decodePortNumberIe(buffer, data.hNbUdpPort, ieHeader.length);

                    data.hNbUdpPortIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: hNbUdpPort\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 2)
                {
					rc = ieObject.decodePortNumberIe(buffer, data.ueTcpPort, ieHeader.length);

                    data.ueTcpPortIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: ueTcpPort\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case AdditionalProtocolConfigurationOptionsIeType:
            {
                AdditionalProtocolConfigurationOptionsIe ieObject =
                dynamic_cast<
                AdditionalProtocolConfigurationOptionsIe&>(GtpV2IeFactory::getInstance().getIeObject(AdditionalProtocolConfigurationOptionsIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeAdditionalProtocolConfigurationOptionsIe(buffer, data.additionalProtocolConfigurationOptions, ieHeader.length);

                    data.additionalProtocolConfigurationOptionsIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: additionalProtocolConfigurationOptions\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case TwanIdentifierIeType:
            {
                TwanIdentifierIe ieObject =
                dynamic_cast<
                TwanIdentifierIe&>(GtpV2IeFactory::getInstance().getIeObject(TwanIdentifierIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeTwanIdentifierIe(buffer, data.twanIdentifier, ieHeader.length);

                    data.twanIdentifierIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: twanIdentifier\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 1)
                {
					rc = ieObject.decodeTwanIdentifierIe(buffer, data.wlanLocationInformation, ieHeader.length);

                    data.wlanLocationInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: wlanLocationInformation\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case CnOperatorSelectionEntityIeType:
            {
                CnOperatorSelectionEntityIe ieObject =
                dynamic_cast<
                CnOperatorSelectionEntityIe&>(GtpV2IeFactory::getInstance().getIeObject(CnOperatorSelectionEntityIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeCnOperatorSelectionEntityIe(buffer, data.cnOperatorSelectionEntity, ieHeader.length);

                    data.cnOperatorSelectionEntityIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: cnOperatorSelectionEntity\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case OverloadControlInformationIeType:
            {
                OverloadControlInformationIe ieObject =
                dynamic_cast<
                OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));

                if(ieHeader.instance == 0)
                {
					MmeS4SgsnsOverloadControlInformationInCreateSessionRequest groupedIeInstance =
					dynamic_cast<
					MmeS4SgsnsOverloadControlInformationInCreateSessionRequest&>(ieObject.getGroupedIe(msgType, 0));
					rc = groupedIeInstance.decodeMmeS4SgsnsOverloadControlInformationInCreateSessionRequest(buffer, data.mmeS4SgsnsOverloadControlInformation, ieHeader.length);

                    data.mmeS4SgsnsOverloadControlInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: mmeS4SgsnsOverloadControlInformation\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 1)
                {
					SgwsOverloadControlInformationInCreateSessionRequest groupedIeInstance =
					dynamic_cast<
					SgwsOverloadControlInformationInCreateSessionRequest&>(ieObject.getGroupedIe(msgType, 1));
					rc = groupedIeInstance.decodeSgwsOverloadControlInformationInCreateSessionRequest(buffer, data.sgwsOverloadControlInformation, ieHeader.length);

                    data.sgwsOverloadControlInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: sgwsOverloadControlInformation\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 2)
                {
					TwanEpdgsOverloadControlInformationInCreateSessionRequest groupedIeInstance =
					dynamic_cast<
					TwanEpdgsOverloadControlInformationInCreateSessionRequest&>(ieObject.getGroupedIe(msgType, 2));
					rc = groupedIeInstance.decodeTwanEpdgsOverloadControlInformationInCreateSessionRequest(buffer, data.twanEpdgsOverloadControlInformation, ieHeader.length);

                    data.twanEpdgsOverloadControlInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: twanEpdgsOverloadControlInformation\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case MillisecondTimeStampIeType:
            {
                MillisecondTimeStampIe ieObject =
                dynamic_cast<
                MillisecondTimeStampIe&>(GtpV2IeFactory::getInstance().getIeObject(MillisecondTimeStampIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeMillisecondTimeStampIe(buffer, data.originationTimeStamp, ieHeader.length);

                    data.originationTimeStampIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: originationTimeStamp\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case IntegerNumberIeType:
            {
                IntegerNumberIe ieObject =
                dynamic_cast<
                IntegerNumberIe&>(GtpV2IeFactory::getInstance().getIeObject(IntegerNumberIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeIntegerNumberIe(buffer, data.maximumWaitTime, ieHeader.length);

                    data.maximumWaitTimeIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: maximumWaitTime\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case TwanIdentifierTimestampIeType:
            {
                TwanIdentifierTimestampIe ieObject =
                dynamic_cast<
                TwanIdentifierTimestampIe&>(GtpV2IeFactory::getInstance().getIeObject(TwanIdentifierTimestampIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeTwanIdentifierTimestampIe(buffer, data.wlanLocationTimestamp, ieHeader.length);

                    data.wlanLocationTimestampIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: wlanLocationTimestamp\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case FContainerIeType:
            {
                FContainerIe ieObject =
                dynamic_cast<
                FContainerIe&>(GtpV2IeFactory::getInstance().getIeObject(FContainerIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeFContainerIe(buffer, data.nbifomContainer, ieHeader.length);

                    data.nbifomContainerIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: nbifomContainer\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case RemoteUeContextIeType:
            {
                RemoteUeContextIe ieObject =
                dynamic_cast<
                RemoteUeContextIe&>(GtpV2IeFactory::getInstance().getIeObject(RemoteUeContextIeType));

                if(ieHeader.instance == 0)
                {
					RemoteUeContextConnectedInCreateSessionRequest groupedIeInstance =
					dynamic_cast<
					RemoteUeContextConnectedInCreateSessionRequest&>(ieObject.getGroupedIe(msgType, 0));
					rc = groupedIeInstance.decodeRemoteUeContextConnectedInCreateSessionRequest(buffer, data.remoteUeContextConnected, ieHeader.length);

                    data.remoteUeContextConnectedIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: remoteUeContextConnected\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case NodeIdentifierIeType:
            {
                NodeIdentifierIe ieObject =
                dynamic_cast<
                NodeIdentifierIe&>(GtpV2IeFactory::getInstance().getIeObject(NodeIdentifierIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeNodeIdentifierIe(buffer, data.a3gppAaaServerIdentifier, ieHeader.length);

                    data.a3gppAaaServerIdentifierIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: a3gppAaaServerIdentifier\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case EpcoIeType:
            {
                EpcoIe ieObject =
                dynamic_cast<
                EpcoIe&>(GtpV2IeFactory::getInstance().getIeObject(EpcoIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeEpcoIe(buffer, data.extendedProtocolConfigurationOptions, ieHeader.length);

                    data.extendedProtocolConfigurationOptionsIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: extendedProtocolConfigurationOptions\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case ServingPlmnRateControlIeType:
            {
                ServingPlmnRateControlIe ieObject =
                dynamic_cast<
                ServingPlmnRateControlIe&>(GtpV2IeFactory::getInstance().getIeObject(ServingPlmnRateControlIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeServingPlmnRateControlIe(buffer, data.servingPlmnRateControl, ieHeader.length);

                    data.servingPlmnRateControlIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: servingPlmnRateControl\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case CounterIeType:
            {
                CounterIe ieObject =
                dynamic_cast<
                CounterIe&>(GtpV2IeFactory::getInstance().getIeObject(CounterIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeCounterIe(buffer, data.moExceptionDataCounter, ieHeader.length);

                    data.moExceptionDataCounterIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: moExceptionDataCounter\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case MappedUeUsageTypeIeType:
            {
                MappedUeUsageTypeIe ieObject =
                dynamic_cast<
                MappedUeUsageTypeIe&>(GtpV2IeFactory::getInstance().getIeObject(MappedUeUsageTypeIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeMappedUeUsageTypeIe(buffer, data.mappedUeUsageType, ieHeader.length);

                    data.mappedUeUsageTypeIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: mappedUeUsageType\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case FqdnIeType:
            {
                FqdnIe ieObject =
                dynamic_cast<
                FqdnIe&>(GtpV2IeFactory::getInstance().getIeObject(FqdnIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeFqdnIe(buffer, data.sgwUNodeName, ieHeader.length);

                    data.sgwUNodeNameIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: sgwUNodeName\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case SecondaryRatUsageDataReportIeType:
            {
                SecondaryRatUsageDataReportIe ieObject =
                dynamic_cast<
                SecondaryRatUsageDataReportIe&>(GtpV2IeFactory::getInstance().getIeObject(SecondaryRatUsageDataReportIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeSecondaryRatUsageDataReportIe(buffer, data.secondaryRatUsageDataReport, ieHeader.length);

                    data.secondaryRatUsageDataReportIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: secondaryRatUsageDataReport\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case UpFunctionSelectionIndicationFlagsIeType:
            {
                UpFunctionSelectionIndicationFlagsIe ieObject =
                dynamic_cast<
                UpFunctionSelectionIndicationFlagsIe&>(GtpV2IeFactory::getInstance().getIeObject(UpFunctionSelectionIndicationFlagsIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeUpFunctionSelectionIndicationFlagsIe(buffer, data.upFunctionSelectionIndicationFlags, ieHeader.length);

                    data.upFunctionSelectionIndicationFlagsIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: upFunctionSelectionIndicationFlags\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }

            default:
            {
                // Unknown IE print error
                errorStream.add("Unknown IE Type: ");
                errorStream.add(ieHeader.ieType);
                errorStream.endOfLine();
                buffer.skipBytes(ieHeader.length);
            }
        }
    }
    return rc; // TODO validations
}

void CreateSessionRequestMsg::
displayCreateSessionRequestMsgData_v(CreateSessionRequestMsgData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("CreateSessionRequestMsg:");
    stream.endOfLine();
    Uint8 displayCount;
    stream.incrIndent();
    if (data.imsiIePresent)
    {
        stream.add("IE - imsi:");
        stream.endOfLine();
        ImsiIe imsi=
        dynamic_cast<
        ImsiIe&>(GtpV2IeFactory::getInstance().getIeObject(ImsiIeType));
        imsi.displayImsiIe_v(data.imsi, stream);

    }
    if (data.msisdnIePresent)
    {
        stream.add("IE - msisdn:");
        stream.endOfLine();
        MsisdnIe msisdn=
        dynamic_cast<
        MsisdnIe&>(GtpV2IeFactory::getInstance().getIeObject(MsisdnIeType));
        msisdn.displayMsisdnIe_v(data.msisdn, stream);

    }
    if (data.meIdentityIePresent)
    {
        stream.add("IE - meIdentity:");
        stream.endOfLine();
        MeiIe mei=
        dynamic_cast<
        MeiIe&>(GtpV2IeFactory::getInstance().getIeObject(MeiIeType));
        mei.displayMeiIe_v(data.meIdentity, stream);

    }
    if (data.userLocationInformationIePresent)
    {
        stream.add("IE - userLocationInformation:");
        stream.endOfLine();
        UliIe uli=
        dynamic_cast<
        UliIe&>(GtpV2IeFactory::getInstance().getIeObject(UliIeType));
        uli.displayUliIe_v(data.userLocationInformation, stream);

    }
    if (data.servingNetworkIePresent)
    {
        stream.add("IE - servingNetwork:");
        stream.endOfLine();
        ServingNetworkIe servingNetwork=
        dynamic_cast<
        ServingNetworkIe&>(GtpV2IeFactory::getInstance().getIeObject(ServingNetworkIeType));
        servingNetwork.displayServingNetworkIe_v(data.servingNetwork, stream);

    }
    if (data.indicationFlagsIePresent)
    {
        stream.add("IE - indicationFlags:");
        stream.endOfLine();
        IndicationIe indication=
        dynamic_cast<
        IndicationIe&>(GtpV2IeFactory::getInstance().getIeObject(IndicationIeType));
        indication.displayIndicationIe_v(data.indicationFlags, stream);

    }
    if (data.pgwS5S8AddressForControlPlaneOrPmipIePresent)
    {
        stream.add("IE - pgwS5S8AddressForControlPlaneOrPmip:");
        stream.endOfLine();
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        fTeid.displayFTeidIe_v(data.pgwS5S8AddressForControlPlaneOrPmip, stream);

    }
    if (data.selectionModeIePresent)
    {
        stream.add("IE - selectionMode:");
        stream.endOfLine();
        SelectionModeIe selectionMode=
        dynamic_cast<
        SelectionModeIe&>(GtpV2IeFactory::getInstance().getIeObject(SelectionModeIeType));
        selectionMode.displaySelectionModeIe_v(data.selectionMode, stream);

    }
    if (data.pdnTypeIePresent)
    {
        stream.add("IE - pdnType:");
        stream.endOfLine();
        PdnTypeIe pdnType=
        dynamic_cast<
        PdnTypeIe&>(GtpV2IeFactory::getInstance().getIeObject(PdnTypeIeType));
        pdnType.displayPdnTypeIe_v(data.pdnType, stream);

    }
    if (data.pdnAddressAllocationIePresent)
    {
        stream.add("IE - pdnAddressAllocation:");
        stream.endOfLine();
        PaaIe paa=
        dynamic_cast<
        PaaIe&>(GtpV2IeFactory::getInstance().getIeObject(PaaIeType));
        paa.displayPaaIe_v(data.pdnAddressAllocation, stream);

    }
    if (data.maximumApnRestrictionIePresent)
    {
        stream.add("IE - maximumApnRestriction:");
        stream.endOfLine();
        ApnRestrictionIe apnRestriction=
        dynamic_cast<
        ApnRestrictionIe&>(GtpV2IeFactory::getInstance().getIeObject(ApnRestrictionIeType));
        apnRestriction.displayApnRestrictionIe_v(data.maximumApnRestriction, stream);

    }
    if (data.aggregateMaximumBitRateIePresent)
    {
        stream.add("IE - aggregateMaximumBitRate:");
        stream.endOfLine();
        AmbrIe ambr=
        dynamic_cast<
        AmbrIe&>(GtpV2IeFactory::getInstance().getIeObject(AmbrIeType));
        ambr.displayAmbrIe_v(data.aggregateMaximumBitRate, stream);

    }
    if (data.linkedEpsBearerIdIePresent)
    {
        stream.add("IE - linkedEpsBearerId:");
        stream.endOfLine();
        EbiIe ebi=
        dynamic_cast<
        EbiIe&>(GtpV2IeFactory::getInstance().getIeObject(EbiIeType));
        ebi.displayEbiIe_v(data.linkedEpsBearerId, stream);

    }
    if (data.trustedWlanModeIndicationIePresent)
    {
        stream.add("IE - trustedWlanModeIndication:");
        stream.endOfLine();
        TwmiIe twmi=
        dynamic_cast<
        TwmiIe&>(GtpV2IeFactory::getInstance().getIeObject(TwmiIeType));
        twmi.displayTwmiIe_v(data.trustedWlanModeIndication, stream);

    }
    if (data.protocolConfigurationOptionsIePresent)
    {
        stream.add("IE - protocolConfigurationOptions:");
        stream.endOfLine();
        PcoIe pco=
        dynamic_cast<
        PcoIe&>(GtpV2IeFactory::getInstance().getIeObject(PcoIeType));
        pco.displayPcoIe_v(data.protocolConfigurationOptions, stream);

    }
    displayCount = data.bearerContextsToBeRemovedCount;
    if (displayCount > 11)
    {
        stream.add("Invalid data more than 11 instances");
        stream.endOfLine();
        stream.add("Displaying only 11");
        stream.endOfLine();
        displayCount = 11;
    }
    for (Uint8 i = 0; i < displayCount; i++)
    {
        stream.add("IE -  bearerContextsToBeRemoved:");
        stream.endOfLine();
        BearerContextIe bearerContext=
        dynamic_cast<
        BearerContextIe&>(GtpV2IeFactory::getInstance().getIeObject(BearerContextIeType));
        BearerContextsToBeRemovedInCreateSessionRequest groupedIeInstance =
        dynamic_cast<
        BearerContextsToBeRemovedInCreateSessionRequest&>(bearerContext.getGroupedIe(msgType, 1));
        groupedIeInstance.displayBearerContextsToBeRemovedInCreateSessionRequestData_v(data.bearerContextsToBeRemoved[i], stream);

    }
    if (data.traceInformationIePresent)
    {
        stream.add("IE - traceInformation:");
        stream.endOfLine();
        TraceInformationIe traceInformation=
        dynamic_cast<
        TraceInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(TraceInformationIeType));
        traceInformation.displayTraceInformationIe_v(data.traceInformation, stream);

    }
    if (data.recoveryIePresent)
    {
        stream.add("IE - recovery:");
        stream.endOfLine();
        RecoveryIe recovery=
        dynamic_cast<
        RecoveryIe&>(GtpV2IeFactory::getInstance().getIeObject(RecoveryIeType));
        recovery.displayRecoveryIe_v(data.recovery, stream);

    }
    if (data.mmeFqCsidIePresent)
    {
        stream.add("IE - mmeFqCsid:");
        stream.endOfLine();
        FqCsidIe fqCsid=
        dynamic_cast<
        FqCsidIe&>(GtpV2IeFactory::getInstance().getIeObject(FqCsidIeType));
        fqCsid.displayFqCsidIe_v(data.mmeFqCsid, stream);

    }
    if (data.sgwFqCsidIePresent)
    {
        stream.add("IE - sgwFqCsid:");
        stream.endOfLine();
        FqCsidIe fqCsid=
        dynamic_cast<
        FqCsidIe&>(GtpV2IeFactory::getInstance().getIeObject(FqCsidIeType));
        fqCsid.displayFqCsidIe_v(data.sgwFqCsid, stream);

    }
    if (data.epdgFqCsidIePresent)
    {
        stream.add("IE - epdgFqCsid:");
        stream.endOfLine();
        FqCsidIe fqCsid=
        dynamic_cast<
        FqCsidIe&>(GtpV2IeFactory::getInstance().getIeObject(FqCsidIeType));
        fqCsid.displayFqCsidIe_v(data.epdgFqCsid, stream);

    }
    if (data.twanFqCsidIePresent)
    {
        stream.add("IE - twanFqCsid:");
        stream.endOfLine();
        FqCsidIe fqCsid=
        dynamic_cast<
        FqCsidIe&>(GtpV2IeFactory::getInstance().getIeObject(FqCsidIeType));
        fqCsid.displayFqCsidIe_v(data.twanFqCsid, stream);

    }
    if (data.ueTimeZoneIePresent)
    {
        stream.add("IE - ueTimeZone:");
        stream.endOfLine();
        UeTimeZoneIe ueTimeZone=
        dynamic_cast<
        UeTimeZoneIe&>(GtpV2IeFactory::getInstance().getIeObject(UeTimeZoneIeType));
        ueTimeZone.displayUeTimeZoneIe_v(data.ueTimeZone, stream);

    }
    if (data.userCsgInformationIePresent)
    {
        stream.add("IE - userCsgInformation:");
        stream.endOfLine();
        UciIe uci=
        dynamic_cast<
        UciIe&>(GtpV2IeFactory::getInstance().getIeObject(UciIeType));
        uci.displayUciIe_v(data.userCsgInformation, stream);

    }
    if (data.chargingCharacteristicsIePresent)
    {
        stream.add("IE - chargingCharacteristics:");
        stream.endOfLine();
        ChargingCharacteristicsIe chargingCharacteristics=
        dynamic_cast<
        ChargingCharacteristicsIe&>(GtpV2IeFactory::getInstance().getIeObject(ChargingCharacteristicsIeType));
        chargingCharacteristics.displayChargingCharacteristicsIe_v(data.chargingCharacteristics, stream);

    }
    if (data.mmeS4SgsnLdnIePresent)
    {
        stream.add("IE - mmeS4SgsnLdn:");
        stream.endOfLine();
        LocalDistinguishedNameIe localDistinguishedName=
        dynamic_cast<
        LocalDistinguishedNameIe&>(GtpV2IeFactory::getInstance().getIeObject(LocalDistinguishedNameIeType));
        localDistinguishedName.displayLocalDistinguishedNameIe_v(data.mmeS4SgsnLdn, stream);

    }
    if (data.sgwLdnIePresent)
    {
        stream.add("IE - sgwLdn:");
        stream.endOfLine();
        LocalDistinguishedNameIe localDistinguishedName=
        dynamic_cast<
        LocalDistinguishedNameIe&>(GtpV2IeFactory::getInstance().getIeObject(LocalDistinguishedNameIeType));
        localDistinguishedName.displayLocalDistinguishedNameIe_v(data.sgwLdn, stream);

    }
    if (data.epdgLdnIePresent)
    {
        stream.add("IE - epdgLdn:");
        stream.endOfLine();
        LocalDistinguishedNameIe localDistinguishedName=
        dynamic_cast<
        LocalDistinguishedNameIe&>(GtpV2IeFactory::getInstance().getIeObject(LocalDistinguishedNameIeType));
        localDistinguishedName.displayLocalDistinguishedNameIe_v(data.epdgLdn, stream);

    }
    if (data.twanLdnIePresent)
    {
        stream.add("IE - twanLdn:");
        stream.endOfLine();
        LocalDistinguishedNameIe localDistinguishedName=
        dynamic_cast<
        LocalDistinguishedNameIe&>(GtpV2IeFactory::getInstance().getIeObject(LocalDistinguishedNameIeType));
        localDistinguishedName.displayLocalDistinguishedNameIe_v(data.twanLdn, stream);

    }
    if (data.signallingPriorityIndicationIePresent)
    {
        stream.add("IE - signallingPriorityIndication:");
        stream.endOfLine();
        SignallingPriorityIndicationIe signallingPriorityIndication=
        dynamic_cast<
        SignallingPriorityIndicationIe&>(GtpV2IeFactory::getInstance().getIeObject(SignallingPriorityIndicationIeType));
        signallingPriorityIndication.displaySignallingPriorityIndicationIe_v(data.signallingPriorityIndication, stream);

    }
    if (data.ueLocalIpAddressIePresent)
    {
        stream.add("IE - ueLocalIpAddress:");
        stream.endOfLine();
        IpAddressIe ipAddress=
        dynamic_cast<
        IpAddressIe&>(GtpV2IeFactory::getInstance().getIeObject(IpAddressIeType));
        ipAddress.displayIpAddressIe_v(data.ueLocalIpAddress, stream);

    }
    if (data.ueUdpPortIePresent)
    {
        stream.add("IE - ueUdpPort:");
        stream.endOfLine();
        PortNumberIe portNumber=
        dynamic_cast<
        PortNumberIe&>(GtpV2IeFactory::getInstance().getIeObject(PortNumberIeType));
        portNumber.displayPortNumberIe_v(data.ueUdpPort, stream);

    }
    if (data.additionalProtocolConfigurationOptionsIePresent)
    {
        stream.add("IE - additionalProtocolConfigurationOptions:");
        stream.endOfLine();
        AdditionalProtocolConfigurationOptionsIe additionalProtocolConfigurationOptions=
        dynamic_cast<
        AdditionalProtocolConfigurationOptionsIe&>(GtpV2IeFactory::getInstance().getIeObject(AdditionalProtocolConfigurationOptionsIeType));
        additionalProtocolConfigurationOptions.displayAdditionalProtocolConfigurationOptionsIe_v(data.additionalProtocolConfigurationOptions, stream);

    }
    if (data.hNbLocalIpAddressIePresent)
    {
        stream.add("IE - hNbLocalIpAddress:");
        stream.endOfLine();
        IpAddressIe ipAddress=
        dynamic_cast<
        IpAddressIe&>(GtpV2IeFactory::getInstance().getIeObject(IpAddressIeType));
        ipAddress.displayIpAddressIe_v(data.hNbLocalIpAddress, stream);

    }
    if (data.hNbUdpPortIePresent)
    {
        stream.add("IE - hNbUdpPort:");
        stream.endOfLine();
        PortNumberIe portNumber=
        dynamic_cast<
        PortNumberIe&>(GtpV2IeFactory::getInstance().getIeObject(PortNumberIeType));
        portNumber.displayPortNumberIe_v(data.hNbUdpPort, stream);

    }
    if (data.mmeS4SgsnIdentifierIePresent)
    {
        stream.add("IE - mmeS4SgsnIdentifier:");
        stream.endOfLine();
        IpAddressIe ipAddress=
        dynamic_cast<
        IpAddressIe&>(GtpV2IeFactory::getInstance().getIeObject(IpAddressIeType));
        ipAddress.displayIpAddressIe_v(data.mmeS4SgsnIdentifier, stream);

    }
    if (data.twanIdentifierIePresent)
    {
        stream.add("IE - twanIdentifier:");
        stream.endOfLine();
        TwanIdentifierIe twanIdentifier=
        dynamic_cast<
        TwanIdentifierIe&>(GtpV2IeFactory::getInstance().getIeObject(TwanIdentifierIeType));
        twanIdentifier.displayTwanIdentifierIe_v(data.twanIdentifier, stream);

    }
    if (data.epdgIpAddressIePresent)
    {
        stream.add("IE - epdgIpAddress:");
        stream.endOfLine();
        IpAddressIe ipAddress=
        dynamic_cast<
        IpAddressIe&>(GtpV2IeFactory::getInstance().getIeObject(IpAddressIeType));
        ipAddress.displayIpAddressIe_v(data.epdgIpAddress, stream);

    }
    if (data.cnOperatorSelectionEntityIePresent)
    {
        stream.add("IE - cnOperatorSelectionEntity:");
        stream.endOfLine();
        CnOperatorSelectionEntityIe cnOperatorSelectionEntity=
        dynamic_cast<
        CnOperatorSelectionEntityIe&>(GtpV2IeFactory::getInstance().getIeObject(CnOperatorSelectionEntityIeType));
        cnOperatorSelectionEntity.displayCnOperatorSelectionEntityIe_v(data.cnOperatorSelectionEntity, stream);

    }
    if (data.mmeS4SgsnsOverloadControlInformationIePresent)
    {
        stream.add("IE - mmeS4SgsnsOverloadControlInformation:");
        stream.endOfLine();
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
            MmeS4SgsnsOverloadControlInformationInCreateSessionRequest groupedIeInstance =
        dynamic_cast<
        MmeS4SgsnsOverloadControlInformationInCreateSessionRequest&>(overloadControlInformation.getGroupedIe(msgType, 0));
        groupedIeInstance.displayMmeS4SgsnsOverloadControlInformationInCreateSessionRequestData_v(data.mmeS4SgsnsOverloadControlInformation, stream);

    }
    if (data.sgwsOverloadControlInformationIePresent)
    {
        stream.add("IE - sgwsOverloadControlInformation:");
        stream.endOfLine();
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
            SgwsOverloadControlInformationInCreateSessionRequest groupedIeInstance =
        dynamic_cast<
        SgwsOverloadControlInformationInCreateSessionRequest&>(overloadControlInformation.getGroupedIe(msgType, 1));
        groupedIeInstance.displaySgwsOverloadControlInformationInCreateSessionRequestData_v(data.sgwsOverloadControlInformation, stream);

    }
    if (data.twanEpdgsOverloadControlInformationIePresent)
    {
        stream.add("IE - twanEpdgsOverloadControlInformation:");
        stream.endOfLine();
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
            TwanEpdgsOverloadControlInformationInCreateSessionRequest groupedIeInstance =
        dynamic_cast<
        TwanEpdgsOverloadControlInformationInCreateSessionRequest&>(overloadControlInformation.getGroupedIe(msgType, 2));
        groupedIeInstance.displayTwanEpdgsOverloadControlInformationInCreateSessionRequestData_v(data.twanEpdgsOverloadControlInformation, stream);

    }
    if (data.originationTimeStampIePresent)
    {
        stream.add("IE - originationTimeStamp:");
        stream.endOfLine();
        MillisecondTimeStampIe millisecondTimeStamp=
        dynamic_cast<
        MillisecondTimeStampIe&>(GtpV2IeFactory::getInstance().getIeObject(MillisecondTimeStampIeType));
        millisecondTimeStamp.displayMillisecondTimeStampIe_v(data.originationTimeStamp, stream);

    }
    if (data.maximumWaitTimeIePresent)
    {
        stream.add("IE - maximumWaitTime:");
        stream.endOfLine();
        IntegerNumberIe integerNumber=
        dynamic_cast<
        IntegerNumberIe&>(GtpV2IeFactory::getInstance().getIeObject(IntegerNumberIeType));
        integerNumber.displayIntegerNumberIe_v(data.maximumWaitTime, stream);

    }
    if (data.wlanLocationInformationIePresent)
    {
        stream.add("IE - wlanLocationInformation:");
        stream.endOfLine();
        TwanIdentifierIe twanIdentifier=
        dynamic_cast<
        TwanIdentifierIe&>(GtpV2IeFactory::getInstance().getIeObject(TwanIdentifierIeType));
        twanIdentifier.displayTwanIdentifierIe_v(data.wlanLocationInformation, stream);

    }
    if (data.wlanLocationTimestampIePresent)
    {
        stream.add("IE - wlanLocationTimestamp:");
        stream.endOfLine();
        TwanIdentifierTimestampIe twanIdentifierTimestamp=
        dynamic_cast<
        TwanIdentifierTimestampIe&>(GtpV2IeFactory::getInstance().getIeObject(TwanIdentifierTimestampIeType));
        twanIdentifierTimestamp.displayTwanIdentifierTimestampIe_v(data.wlanLocationTimestamp, stream);

    }
    if (data.nbifomContainerIePresent)
    {
        stream.add("IE - nbifomContainer:");
        stream.endOfLine();
        FContainerIe fContainer=
        dynamic_cast<
        FContainerIe&>(GtpV2IeFactory::getInstance().getIeObject(FContainerIeType));
        fContainer.displayFContainerIe_v(data.nbifomContainer, stream);

    }
    if (data.remoteUeContextConnectedIePresent)
    {
        stream.add("IE - remoteUeContextConnected:");
        stream.endOfLine();
        RemoteUeContextIe remoteUeContext=
        dynamic_cast<
        RemoteUeContextIe&>(GtpV2IeFactory::getInstance().getIeObject(RemoteUeContextIeType));
            RemoteUeContextConnectedInCreateSessionRequest groupedIeInstance =
        dynamic_cast<
        RemoteUeContextConnectedInCreateSessionRequest&>(remoteUeContext.getGroupedIe(msgType, 0));
        groupedIeInstance.displayRemoteUeContextConnectedInCreateSessionRequestData_v(data.remoteUeContextConnected, stream);

    }
    if (data.a3gppAaaServerIdentifierIePresent)
    {
        stream.add("IE - a3gppAaaServerIdentifier:");
        stream.endOfLine();
        NodeIdentifierIe nodeIdentifier=
        dynamic_cast<
        NodeIdentifierIe&>(GtpV2IeFactory::getInstance().getIeObject(NodeIdentifierIeType));
        nodeIdentifier.displayNodeIdentifierIe_v(data.a3gppAaaServerIdentifier, stream);

    }
    if (data.extendedProtocolConfigurationOptionsIePresent)
    {
        stream.add("IE - extendedProtocolConfigurationOptions:");
        stream.endOfLine();
        EpcoIe epco=
        dynamic_cast<
        EpcoIe&>(GtpV2IeFactory::getInstance().getIeObject(EpcoIeType));
        epco.displayEpcoIe_v(data.extendedProtocolConfigurationOptions, stream);

    }
    if (data.servingPlmnRateControlIePresent)
    {
        stream.add("IE - servingPlmnRateControl:");
        stream.endOfLine();
        ServingPlmnRateControlIe servingPlmnRateControl=
        dynamic_cast<
        ServingPlmnRateControlIe&>(GtpV2IeFactory::getInstance().getIeObject(ServingPlmnRateControlIeType));
        servingPlmnRateControl.displayServingPlmnRateControlIe_v(data.servingPlmnRateControl, stream);

    }
    if (data.moExceptionDataCounterIePresent)
    {
        stream.add("IE - moExceptionDataCounter:");
        stream.endOfLine();
        CounterIe counter=
        dynamic_cast<
        CounterIe&>(GtpV2IeFactory::getInstance().getIeObject(CounterIeType));
        counter.displayCounterIe_v(data.moExceptionDataCounter, stream);

    }
    if (data.ueTcpPortIePresent)
    {
        stream.add("IE - ueTcpPort:");
        stream.endOfLine();
        PortNumberIe portNumber=
        dynamic_cast<
        PortNumberIe&>(GtpV2IeFactory::getInstance().getIeObject(PortNumberIeType));
        portNumber.displayPortNumberIe_v(data.ueTcpPort, stream);

    }
    if (data.mappedUeUsageTypeIePresent)
    {
        stream.add("IE - mappedUeUsageType:");
        stream.endOfLine();
        MappedUeUsageTypeIe mappedUeUsageType=
        dynamic_cast<
        MappedUeUsageTypeIe&>(GtpV2IeFactory::getInstance().getIeObject(MappedUeUsageTypeIeType));
        mappedUeUsageType.displayMappedUeUsageTypeIe_v(data.mappedUeUsageType, stream);

    }
    if (data.userLocationInformationForSgwIePresent)
    {
        stream.add("IE - userLocationInformationForSgw:");
        stream.endOfLine();
        UliIe uli=
        dynamic_cast<
        UliIe&>(GtpV2IeFactory::getInstance().getIeObject(UliIeType));
        uli.displayUliIe_v(data.userLocationInformationForSgw, stream);

    }
    if (data.sgwUNodeNameIePresent)
    {
        stream.add("IE - sgwUNodeName:");
        stream.endOfLine();
        FqdnIe fqdn=
        dynamic_cast<
        FqdnIe&>(GtpV2IeFactory::getInstance().getIeObject(FqdnIeType));
        fqdn.displayFqdnIe_v(data.sgwUNodeName, stream);

    }
    if (data.secondaryRatUsageDataReportIePresent)
    {
        stream.add("IE - secondaryRatUsageDataReport:");
        stream.endOfLine();
        SecondaryRatUsageDataReportIe secondaryRatUsageDataReport=
        dynamic_cast<
        SecondaryRatUsageDataReportIe&>(GtpV2IeFactory::getInstance().getIeObject(SecondaryRatUsageDataReportIeType));
        secondaryRatUsageDataReport.displaySecondaryRatUsageDataReportIe_v(data.secondaryRatUsageDataReport, stream);

    }
    if (data.upFunctionSelectionIndicationFlagsIePresent)
    {
        stream.add("IE - upFunctionSelectionIndicationFlags:");
        stream.endOfLine();
        UpFunctionSelectionIndicationFlagsIe upFunctionSelectionIndicationFlags=
        dynamic_cast<
        UpFunctionSelectionIndicationFlagsIe&>(GtpV2IeFactory::getInstance().getIeObject(UpFunctionSelectionIndicationFlagsIeType));
        upFunctionSelectionIndicationFlags.displayUpFunctionSelectionIndicationFlagsIe_v(data.upFunctionSelectionIndicationFlags, stream);

    }
    stream.decrIndent();
    stream.decrIndent();
}


