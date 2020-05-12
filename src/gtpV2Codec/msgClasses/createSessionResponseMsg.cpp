/*
 * createSessionResponseMsg.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */
#include "assert.h"
#include "createSessionResponseMsg.h"
#include "../ieClasses/manual/gtpV2Ie.h"
#include "../ieClasses/gtpV2IeFactory.h"
#include "../ieClasses/causeIe.h"
#include "../ieClasses/changeReportingActionIe.h"
#include "../ieClasses/csgInformationReportingActionIe.h"
#include "../ieClasses/fTeidIe.h"
#include "../ieClasses/apnRestrictionIe.h"
#include "../ieClasses/ambrIe.h"
#include "../ieClasses/ebiIe.h"
#include "../ieClasses/bearerContextIe.h"
#include "../ieClasses/bearerContextsCreatedInCreateSessionResponse.h"
#include "../ieClasses/bearerContextIe.h"
#include "../ieClasses/bearerContextsMarkedForRemovalInCreateSessionResponse.h"
#include "../ieClasses/recoveryIe.h"
#include "../ieClasses/fqdnIe.h"
#include "../ieClasses/ipAddressIe.h"
#include "../ieClasses/fqCsidIe.h"
#include "../ieClasses/fqCsidIe.h"
#include "../ieClasses/localDistinguishedNameIe.h"
#include "../ieClasses/localDistinguishedNameIe.h"
#include "../ieClasses/epcTimerIe.h"
#include "../ieClasses/henbInformationReportingIe.h"
#include "../ieClasses/fTeidIe.h"
#include "../ieClasses/paaIe.h"
#include "../ieClasses/pcoIe.h"
#include "../ieClasses/additionalProtocolConfigurationOptionsIe.h"
#include "../ieClasses/ip4cpIe.h"
#include "../ieClasses/indicationIe.h"
#include "../ieClasses/presenceReportingAreaActionIe.h"
#include "../ieClasses/loadControlInformationIe.h"
#include "../ieClasses/pgwsNodeLevelLoadControlInformationInCreateSessionResponse.h"
#include "../ieClasses/loadControlInformationIe.h"
#include "../ieClasses/pgwsApnLevelLoadControlInformationInCreateSessionResponse.h"
#include "../ieClasses/loadControlInformationIe.h"
#include "../ieClasses/sgwsNodeLevelLoadControlInformationInCreateSessionResponse.h"
#include "../ieClasses/overloadControlInformationIe.h"
#include "../ieClasses/pgwsOverloadControlInformationInCreateSessionResponse.h"
#include "../ieClasses/overloadControlInformationIe.h"
#include "../ieClasses/sgwsOverloadControlInformationInCreateSessionResponse.h"
#include "../ieClasses/fContainerIe.h"
#include "../ieClasses/chargingIdIe.h"
#include "../ieClasses/epcoIe.h"
#include "stdio.h"

CreateSessionResponseMsg::CreateSessionResponseMsg()
{
    msgType = CreateSessionResponseMsgType;
    Uint16 mandIe;
    mandIe = CauseIeType;
    mandIe = (mandIe << 8) | 0; // cause
    mandatoryIeSet.insert(mandIe);    mandIe = BearerContextIeType;
    mandIe = (mandIe << 8) | 0; // bearerContextsCreated
    mandatoryIeSet.insert(mandIe);
}

CreateSessionResponseMsg::~CreateSessionResponseMsg()
{

}

bool CreateSessionResponseMsg::encodeCreateSessionResponseMsg(MsgBuffer &buffer,
                        CreateSessionResponseMsgData
							const &data)
{
    bool rc = false;
    GtpV2IeHeader header;
    Uint16 startIndex = 0;
    Uint16 endIndex = 0;
    Uint16 length = 0;


    if (data.changeReportingActionIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = ChangeReportingActionIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        ChangeReportingActionIe changeReportingAction=
        dynamic_cast<
        ChangeReportingActionIe&>(GtpV2IeFactory::getInstance().getIeObject(ChangeReportingActionIeType));
        rc = changeReportingAction.encodeChangeReportingActionIe(buffer, data.changeReportingAction);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: changeReportingAction\n");
            return false;
        }
    }

    if (data.csgInformationReportingActionIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = CsgInformationReportingActionIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        CsgInformationReportingActionIe csgInformationReportingAction=
        dynamic_cast<
        CsgInformationReportingActionIe&>(GtpV2IeFactory::getInstance().getIeObject(CsgInformationReportingActionIeType));
        rc = csgInformationReportingAction.encodeCsgInformationReportingActionIe(buffer, data.csgInformationReportingAction);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: csgInformationReportingAction\n");
            return false;
        }
    }

    if (data.senderFTeidForControlPlaneIePresent)
    {
            
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
    }

    if (data.apnRestrictionIePresent)
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
        rc = apnRestriction.encodeApnRestrictionIe(buffer, data.apnRestriction);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: apnRestriction\n");
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


        // First validate if the applicatoin provided more than the expected cardinality
    if (data.bearerContextsMarkedForRemovalCount > 11)
    {
        errorStream.add("Number of entries of bearerContextsMarkedForRemoval exceeded\n");
        errorStream.add("Expected count: 11 Received count: ");
        errorStream.add("data.bearerContextsMarkedForRemovalCount");
        errorStream.endOfLine();
        return false;
    }
    for (Uint8 i = 0; i < data.bearerContextsMarkedForRemovalCount; i++)
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
        BearerContextsMarkedForRemovalInCreateSessionResponse groupedIeInstance = dynamic_cast<BearerContextsMarkedForRemovalInCreateSessionResponse&>(bearerContext.getGroupedIe(msgType, 1));
        rc = groupedIeInstance.encodeBearerContextsMarkedForRemovalInCreateSessionResponse(buffer, data.bearerContextsMarkedForRemoval[i]);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;

        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);
    }

    if (!(rc))
    { 
        errorStream.add("Failed to encode IE: bearerContextsMarkedForRemoval\n");
        return false;
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

    if (data.chargingGatewayNameIePresent)
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
        rc = fqdn.encodeFqdnIe(buffer, data.chargingGatewayName);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: chargingGatewayName\n");
            return false;
        }
    }

    if (data.chargingGatewayAddressIePresent)
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
        rc = ipAddress.encodeIpAddressIe(buffer, data.chargingGatewayAddress);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: chargingGatewayAddress\n");
            return false;
        }
    }

    if (data.pgwFqCsidIePresent)
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
        rc = fqCsid.encodeFqCsidIe(buffer, data.pgwFqCsid);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: pgwFqCsid\n");
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

    if (data.sgwLdnIePresent)
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

    if (data.pgwLdnIePresent)
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
        rc = localDistinguishedName.encodeLocalDistinguishedNameIe(buffer, data.pgwLdn);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: pgwLdn\n");
            return false;
        }
    }

    if (data.pgwBackOffTimeIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = EpcTimerIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        EpcTimerIe epcTimer=
        dynamic_cast<
        EpcTimerIe&>(GtpV2IeFactory::getInstance().getIeObject(EpcTimerIeType));
        rc = epcTimer.encodeEpcTimerIe(buffer, data.pgwBackOffTime);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: pgwBackOffTime\n");
            return false;
        }
    }

    if (data.hNbInformationReportingIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = HenbInformationReportingIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        HenbInformationReportingIe henbInformationReporting=
        dynamic_cast<
        HenbInformationReportingIe&>(GtpV2IeFactory::getInstance().getIeObject(HenbInformationReportingIeType));
        rc = henbInformationReporting.encodeHenbInformationReportingIe(buffer, data.hNbInformationReporting);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: hNbInformationReporting\n");
            return false;
        }
    }

    if (data.pgwS5S8S2aS2bFTeidForPmipBasedInterfaceOrForGtpBasedControlPlaneInterfaceIePresent)
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
        rc = fTeid.encodeFTeidIe(buffer, data.pgwS5S8S2aS2bFTeidForPmipBasedInterfaceOrForGtpBasedControlPlaneInterface);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: pgwS5S8S2aS2bFTeidForPmipBasedInterfaceOrForGtpBasedControlPlaneInterface\n");
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

    if (data.trustedWlanIpv4ParametersIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = Ip4cpIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        Ip4cpIe ip4cp=
        dynamic_cast<
        Ip4cpIe&>(GtpV2IeFactory::getInstance().getIeObject(Ip4cpIeType));
        rc = ip4cp.encodeIp4cpIe(buffer, data.trustedWlanIpv4Parameters);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: trustedWlanIpv4Parameters\n");
            return false;
        }
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

    if (data.presenceReportingAreaActionIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = PresenceReportingAreaActionIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        PresenceReportingAreaActionIe presenceReportingAreaAction=
        dynamic_cast<
        PresenceReportingAreaActionIe&>(GtpV2IeFactory::getInstance().getIeObject(PresenceReportingAreaActionIeType));
        rc = presenceReportingAreaAction.encodePresenceReportingAreaActionIe(buffer, data.presenceReportingAreaAction);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: presenceReportingAreaAction\n");
            return false;
        }
    }

    if (data.pgwsNodeLevelLoadControlInformationIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = LoadControlInformationIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        LoadControlInformationIe loadControlInformation=
        dynamic_cast<
        LoadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(LoadControlInformationIeType));
        PgwsNodeLevelLoadControlInformationInCreateSessionResponse groupedIeInstance =
        dynamic_cast<
         PgwsNodeLevelLoadControlInformationInCreateSessionResponse&>(loadControlInformation.getGroupedIe(msgType, 0));
        rc = groupedIeInstance.encodePgwsNodeLevelLoadControlInformationInCreateSessionResponse(buffer, data.pgwsNodeLevelLoadControlInformation);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: pgwsNodeLevelLoadControlInformation\n");
            return false;
        }
    }

    if (data.pgwsApnLevelLoadControlInformationIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = LoadControlInformationIeType;
        header.instance = 1;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        LoadControlInformationIe loadControlInformation=
        dynamic_cast<
        LoadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(LoadControlInformationIeType));
        PgwsApnLevelLoadControlInformationInCreateSessionResponse groupedIeInstance =
        dynamic_cast<
         PgwsApnLevelLoadControlInformationInCreateSessionResponse&>(loadControlInformation.getGroupedIe(msgType, 1));
        rc = groupedIeInstance.encodePgwsApnLevelLoadControlInformationInCreateSessionResponse(buffer, data.pgwsApnLevelLoadControlInformation);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: pgwsApnLevelLoadControlInformation\n");
            return false;
        }
    }

    if (data.sgwsNodeLevelLoadControlInformationIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = LoadControlInformationIeType;
        header.instance = 2;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        LoadControlInformationIe loadControlInformation=
        dynamic_cast<
        LoadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(LoadControlInformationIeType));
        SgwsNodeLevelLoadControlInformationInCreateSessionResponse groupedIeInstance =
        dynamic_cast<
         SgwsNodeLevelLoadControlInformationInCreateSessionResponse&>(loadControlInformation.getGroupedIe(msgType, 2));
        rc = groupedIeInstance.encodeSgwsNodeLevelLoadControlInformationInCreateSessionResponse(buffer, data.sgwsNodeLevelLoadControlInformation);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: sgwsNodeLevelLoadControlInformation\n");
            return false;
        }
    }

    if (data.pgwsOverloadControlInformationIePresent)
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
        PgwsOverloadControlInformationInCreateSessionResponse groupedIeInstance =
        dynamic_cast<
         PgwsOverloadControlInformationInCreateSessionResponse&>(overloadControlInformation.getGroupedIe(msgType, 0));
        rc = groupedIeInstance.encodePgwsOverloadControlInformationInCreateSessionResponse(buffer, data.pgwsOverloadControlInformation);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: pgwsOverloadControlInformation\n");
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
        SgwsOverloadControlInformationInCreateSessionResponse groupedIeInstance =
        dynamic_cast<
         SgwsOverloadControlInformationInCreateSessionResponse&>(overloadControlInformation.getGroupedIe(msgType, 1));
        rc = groupedIeInstance.encodeSgwsOverloadControlInformationInCreateSessionResponse(buffer, data.sgwsOverloadControlInformation);
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

    if (data.pdnConnectionChargingIdIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = ChargingIdIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        ChargingIdIe chargingId=
        dynamic_cast<
        ChargingIdIe&>(GtpV2IeFactory::getInstance().getIeObject(ChargingIdIeType));
        rc = chargingId.encodeChargingIdIe(buffer, data.pdnConnectionChargingId);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: pdnConnectionChargingId\n");
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
    return rc;

}

bool CreateSessionResponseMsg::decodeCreateSessionResponseMsg(MsgBuffer &buffer,
 CreateSessionResponseMsgData 
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
     
            case CauseIeType:
            {
                CauseIe ieObject =
                dynamic_cast<
                CauseIe&>(GtpV2IeFactory::getInstance().getIeObject(CauseIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeCauseIe(buffer, data.cause, ieHeader.length);

                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: cause\n");
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
     
            case ChangeReportingActionIeType:
            {
                ChangeReportingActionIe ieObject =
                dynamic_cast<
                ChangeReportingActionIe&>(GtpV2IeFactory::getInstance().getIeObject(ChangeReportingActionIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeChangeReportingActionIe(buffer, data.changeReportingAction, ieHeader.length);

                    data.changeReportingActionIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: changeReportingAction\n");
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
     
            case CsgInformationReportingActionIeType:
            {
                CsgInformationReportingActionIe ieObject =
                dynamic_cast<
                CsgInformationReportingActionIe&>(GtpV2IeFactory::getInstance().getIeObject(CsgInformationReportingActionIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeCsgInformationReportingActionIe(buffer, data.csgInformationReportingAction, ieHeader.length);

                    data.csgInformationReportingActionIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: csgInformationReportingAction\n");
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

                    data.senderFTeidForControlPlaneIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: senderFTeidForControlPlane\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 1)
                {
					rc = ieObject.decodeFTeidIe(buffer, data.pgwS5S8S2aS2bFTeidForPmipBasedInterfaceOrForGtpBasedControlPlaneInterface, ieHeader.length);

                    data.pgwS5S8S2aS2bFTeidForPmipBasedInterfaceOrForGtpBasedControlPlaneInterfaceIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: pgwS5S8S2aS2bFTeidForPmipBasedInterfaceOrForGtpBasedControlPlaneInterface\n");
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
					rc = ieObject.decodeApnRestrictionIe(buffer, data.apnRestriction, ieHeader.length);

                    data.apnRestrictionIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: apnRestriction\n");
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
     
            case BearerContextIeType:
            {
                BearerContextIe ieObject =
                dynamic_cast<
                BearerContextIe&>(GtpV2IeFactory::getInstance().getIeObject(BearerContextIeType));

                if(ieHeader.instance == 0)
                {
					// First check if we have enough space left to decode and store this instance
                    if (data.bearerContextsCreatedCount == 11)
                    {
                        errorStream.add("More than 11 instances of bearerContextsCreated received\n");
                        return false;
                    }
                    BearerContextsCreatedInCreateSessionResponse groupedIeInstance =
                    dynamic_cast<
                    BearerContextsCreatedInCreateSessionResponse&>(ieObject.getGroupedIe(msgType, 0));
                    rc = groupedIeInstance.decodeBearerContextsCreatedInCreateSessionResponse(buffer,
                    data.bearerContextsCreated[data.bearerContextsCreatedCount], ieHeader.length);
                    data.bearerContextsCreatedCount++; // TODO Count validation

                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: bearerContextsCreated\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 1)
                {
					// First check if we have enough space left to decode and store this instance
                    if (data.bearerContextsMarkedForRemovalCount == 11)
                    {
                        errorStream.add("More than 11 instances of bearerContextsMarkedForRemoval received\n");
                        return false;
                    }
                    BearerContextsMarkedForRemovalInCreateSessionResponse groupedIeInstance =
                    dynamic_cast<
                    BearerContextsMarkedForRemovalInCreateSessionResponse&>(ieObject.getGroupedIe(msgType, 1));
                    rc = groupedIeInstance.decodeBearerContextsMarkedForRemovalInCreateSessionResponse(buffer,
                    data.bearerContextsMarkedForRemoval[data.bearerContextsMarkedForRemovalCount], ieHeader.length);
                    data.bearerContextsMarkedForRemovalCount++; // TODO Count validation

                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: bearerContextsMarkedForRemoval\n");
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
     
            case FqdnIeType:
            {
                FqdnIe ieObject =
                dynamic_cast<
                FqdnIe&>(GtpV2IeFactory::getInstance().getIeObject(FqdnIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeFqdnIe(buffer, data.chargingGatewayName, ieHeader.length);

                    data.chargingGatewayNameIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: chargingGatewayName\n");
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
					rc = ieObject.decodeIpAddressIe(buffer, data.chargingGatewayAddress, ieHeader.length);

                    data.chargingGatewayAddressIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: chargingGatewayAddress\n");
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
					rc = ieObject.decodeFqCsidIe(buffer, data.pgwFqCsid, ieHeader.length);

                    data.pgwFqCsidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: pgwFqCsid\n");
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
					rc = ieObject.decodeLocalDistinguishedNameIe(buffer, data.sgwLdn, ieHeader.length);

                    data.sgwLdnIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: sgwLdn\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 1)
                {
					rc = ieObject.decodeLocalDistinguishedNameIe(buffer, data.pgwLdn, ieHeader.length);

                    data.pgwLdnIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: pgwLdn\n");
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
     
            case EpcTimerIeType:
            {
                EpcTimerIe ieObject =
                dynamic_cast<
                EpcTimerIe&>(GtpV2IeFactory::getInstance().getIeObject(EpcTimerIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeEpcTimerIe(buffer, data.pgwBackOffTime, ieHeader.length);

                    data.pgwBackOffTimeIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: pgwBackOffTime\n");
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
     
            case HenbInformationReportingIeType:
            {
                HenbInformationReportingIe ieObject =
                dynamic_cast<
                HenbInformationReportingIe&>(GtpV2IeFactory::getInstance().getIeObject(HenbInformationReportingIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeHenbInformationReportingIe(buffer, data.hNbInformationReporting, ieHeader.length);

                    data.hNbInformationReportingIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: hNbInformationReporting\n");
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
     
            case Ip4cpIeType:
            {
                Ip4cpIe ieObject =
                dynamic_cast<
                Ip4cpIe&>(GtpV2IeFactory::getInstance().getIeObject(Ip4cpIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeIp4cpIe(buffer, data.trustedWlanIpv4Parameters, ieHeader.length);

                    data.trustedWlanIpv4ParametersIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: trustedWlanIpv4Parameters\n");
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
     
            case PresenceReportingAreaActionIeType:
            {
                PresenceReportingAreaActionIe ieObject =
                dynamic_cast<
                PresenceReportingAreaActionIe&>(GtpV2IeFactory::getInstance().getIeObject(PresenceReportingAreaActionIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodePresenceReportingAreaActionIe(buffer, data.presenceReportingAreaAction, ieHeader.length);

                    data.presenceReportingAreaActionIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: presenceReportingAreaAction\n");
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
     
            case LoadControlInformationIeType:
            {
                LoadControlInformationIe ieObject =
                dynamic_cast<
                LoadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(LoadControlInformationIeType));

                if(ieHeader.instance == 0)
                {
					PgwsNodeLevelLoadControlInformationInCreateSessionResponse groupedIeInstance =
					dynamic_cast<
					PgwsNodeLevelLoadControlInformationInCreateSessionResponse&>(ieObject.getGroupedIe(msgType, 0));
					rc = groupedIeInstance.decodePgwsNodeLevelLoadControlInformationInCreateSessionResponse(buffer, data.pgwsNodeLevelLoadControlInformation, ieHeader.length);

                    data.pgwsNodeLevelLoadControlInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: pgwsNodeLevelLoadControlInformation\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 1)
                {
					PgwsApnLevelLoadControlInformationInCreateSessionResponse groupedIeInstance =
					dynamic_cast<
					PgwsApnLevelLoadControlInformationInCreateSessionResponse&>(ieObject.getGroupedIe(msgType, 1));
					rc = groupedIeInstance.decodePgwsApnLevelLoadControlInformationInCreateSessionResponse(buffer, data.pgwsApnLevelLoadControlInformation, ieHeader.length);

                    data.pgwsApnLevelLoadControlInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: pgwsApnLevelLoadControlInformation\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 2)
                {
					SgwsNodeLevelLoadControlInformationInCreateSessionResponse groupedIeInstance =
					dynamic_cast<
					SgwsNodeLevelLoadControlInformationInCreateSessionResponse&>(ieObject.getGroupedIe(msgType, 2));
					rc = groupedIeInstance.decodeSgwsNodeLevelLoadControlInformationInCreateSessionResponse(buffer, data.sgwsNodeLevelLoadControlInformation, ieHeader.length);

                    data.sgwsNodeLevelLoadControlInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: sgwsNodeLevelLoadControlInformation\n");
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
					PgwsOverloadControlInformationInCreateSessionResponse groupedIeInstance =
					dynamic_cast<
					PgwsOverloadControlInformationInCreateSessionResponse&>(ieObject.getGroupedIe(msgType, 0));
					rc = groupedIeInstance.decodePgwsOverloadControlInformationInCreateSessionResponse(buffer, data.pgwsOverloadControlInformation, ieHeader.length);

                    data.pgwsOverloadControlInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: pgwsOverloadControlInformation\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 1)
                {
					SgwsOverloadControlInformationInCreateSessionResponse groupedIeInstance =
					dynamic_cast<
					SgwsOverloadControlInformationInCreateSessionResponse&>(ieObject.getGroupedIe(msgType, 1));
					rc = groupedIeInstance.decodeSgwsOverloadControlInformationInCreateSessionResponse(buffer, data.sgwsOverloadControlInformation, ieHeader.length);

                    data.sgwsOverloadControlInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: sgwsOverloadControlInformation\n");
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
     
            case ChargingIdIeType:
            {
                ChargingIdIe ieObject =
                dynamic_cast<
                ChargingIdIe&>(GtpV2IeFactory::getInstance().getIeObject(ChargingIdIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeChargingIdIe(buffer, data.pdnConnectionChargingId, ieHeader.length);

                    data.pdnConnectionChargingIdIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: pdnConnectionChargingId\n");
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

void CreateSessionResponseMsg::
displayCreateSessionResponseMsgData_v(CreateSessionResponseMsgData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("CreateSessionResponseMsg:");
    stream.endOfLine();
    Uint8 displayCount;
    stream.incrIndent();
    if (data.changeReportingActionIePresent)
    {
        stream.add("IE - changeReportingAction:");
        stream.endOfLine();
        ChangeReportingActionIe changeReportingAction=
        dynamic_cast<
        ChangeReportingActionIe&>(GtpV2IeFactory::getInstance().getIeObject(ChangeReportingActionIeType));
        changeReportingAction.displayChangeReportingActionIe_v(data.changeReportingAction, stream);

    }
    if (data.csgInformationReportingActionIePresent)
    {
        stream.add("IE - csgInformationReportingAction:");
        stream.endOfLine();
        CsgInformationReportingActionIe csgInformationReportingAction=
        dynamic_cast<
        CsgInformationReportingActionIe&>(GtpV2IeFactory::getInstance().getIeObject(CsgInformationReportingActionIeType));
        csgInformationReportingAction.displayCsgInformationReportingActionIe_v(data.csgInformationReportingAction, stream);

    }
    if (data.senderFTeidForControlPlaneIePresent)
    {
        stream.add("IE - senderFTeidForControlPlane:");
        stream.endOfLine();
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        fTeid.displayFTeidIe_v(data.senderFTeidForControlPlane, stream);

    }
    if (data.apnRestrictionIePresent)
    {
        stream.add("IE - apnRestriction:");
        stream.endOfLine();
        ApnRestrictionIe apnRestriction=
        dynamic_cast<
        ApnRestrictionIe&>(GtpV2IeFactory::getInstance().getIeObject(ApnRestrictionIeType));
        apnRestriction.displayApnRestrictionIe_v(data.apnRestriction, stream);

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
    displayCount = data.bearerContextsMarkedForRemovalCount;
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
        stream.add("IE -  bearerContextsMarkedForRemoval:");
        stream.endOfLine();
        BearerContextIe bearerContext=
        dynamic_cast<
        BearerContextIe&>(GtpV2IeFactory::getInstance().getIeObject(BearerContextIeType));
        BearerContextsMarkedForRemovalInCreateSessionResponse groupedIeInstance =
        dynamic_cast<
        BearerContextsMarkedForRemovalInCreateSessionResponse&>(bearerContext.getGroupedIe(msgType, 1));
        groupedIeInstance.displayBearerContextsMarkedForRemovalInCreateSessionResponseData_v(data.bearerContextsMarkedForRemoval[i], stream);

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
    if (data.chargingGatewayNameIePresent)
    {
        stream.add("IE - chargingGatewayName:");
        stream.endOfLine();
        FqdnIe fqdn=
        dynamic_cast<
        FqdnIe&>(GtpV2IeFactory::getInstance().getIeObject(FqdnIeType));
        fqdn.displayFqdnIe_v(data.chargingGatewayName, stream);

    }
    if (data.chargingGatewayAddressIePresent)
    {
        stream.add("IE - chargingGatewayAddress:");
        stream.endOfLine();
        IpAddressIe ipAddress=
        dynamic_cast<
        IpAddressIe&>(GtpV2IeFactory::getInstance().getIeObject(IpAddressIeType));
        ipAddress.displayIpAddressIe_v(data.chargingGatewayAddress, stream);

    }
    if (data.pgwFqCsidIePresent)
    {
        stream.add("IE - pgwFqCsid:");
        stream.endOfLine();
        FqCsidIe fqCsid=
        dynamic_cast<
        FqCsidIe&>(GtpV2IeFactory::getInstance().getIeObject(FqCsidIeType));
        fqCsid.displayFqCsidIe_v(data.pgwFqCsid, stream);

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
    if (data.sgwLdnIePresent)
    {
        stream.add("IE - sgwLdn:");
        stream.endOfLine();
        LocalDistinguishedNameIe localDistinguishedName=
        dynamic_cast<
        LocalDistinguishedNameIe&>(GtpV2IeFactory::getInstance().getIeObject(LocalDistinguishedNameIeType));
        localDistinguishedName.displayLocalDistinguishedNameIe_v(data.sgwLdn, stream);

    }
    if (data.pgwLdnIePresent)
    {
        stream.add("IE - pgwLdn:");
        stream.endOfLine();
        LocalDistinguishedNameIe localDistinguishedName=
        dynamic_cast<
        LocalDistinguishedNameIe&>(GtpV2IeFactory::getInstance().getIeObject(LocalDistinguishedNameIeType));
        localDistinguishedName.displayLocalDistinguishedNameIe_v(data.pgwLdn, stream);

    }
    if (data.pgwBackOffTimeIePresent)
    {
        stream.add("IE - pgwBackOffTime:");
        stream.endOfLine();
        EpcTimerIe epcTimer=
        dynamic_cast<
        EpcTimerIe&>(GtpV2IeFactory::getInstance().getIeObject(EpcTimerIeType));
        epcTimer.displayEpcTimerIe_v(data.pgwBackOffTime, stream);

    }
    if (data.hNbInformationReportingIePresent)
    {
        stream.add("IE - hNbInformationReporting:");
        stream.endOfLine();
        HenbInformationReportingIe henbInformationReporting=
        dynamic_cast<
        HenbInformationReportingIe&>(GtpV2IeFactory::getInstance().getIeObject(HenbInformationReportingIeType));
        henbInformationReporting.displayHenbInformationReportingIe_v(data.hNbInformationReporting, stream);

    }
    if (data.pgwS5S8S2aS2bFTeidForPmipBasedInterfaceOrForGtpBasedControlPlaneInterfaceIePresent)
    {
        stream.add("IE - pgwS5S8S2aS2bFTeidForPmipBasedInterfaceOrForGtpBasedControlPlaneInterface:");
        stream.endOfLine();
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        fTeid.displayFTeidIe_v(data.pgwS5S8S2aS2bFTeidForPmipBasedInterfaceOrForGtpBasedControlPlaneInterface, stream);

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
    if (data.protocolConfigurationOptionsIePresent)
    {
        stream.add("IE - protocolConfigurationOptions:");
        stream.endOfLine();
        PcoIe pco=
        dynamic_cast<
        PcoIe&>(GtpV2IeFactory::getInstance().getIeObject(PcoIeType));
        pco.displayPcoIe_v(data.protocolConfigurationOptions, stream);

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
    if (data.trustedWlanIpv4ParametersIePresent)
    {
        stream.add("IE - trustedWlanIpv4Parameters:");
        stream.endOfLine();
        Ip4cpIe ip4cp=
        dynamic_cast<
        Ip4cpIe&>(GtpV2IeFactory::getInstance().getIeObject(Ip4cpIeType));
        ip4cp.displayIp4cpIe_v(data.trustedWlanIpv4Parameters, stream);

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
    if (data.presenceReportingAreaActionIePresent)
    {
        stream.add("IE - presenceReportingAreaAction:");
        stream.endOfLine();
        PresenceReportingAreaActionIe presenceReportingAreaAction=
        dynamic_cast<
        PresenceReportingAreaActionIe&>(GtpV2IeFactory::getInstance().getIeObject(PresenceReportingAreaActionIeType));
        presenceReportingAreaAction.displayPresenceReportingAreaActionIe_v(data.presenceReportingAreaAction, stream);

    }
    if (data.pgwsNodeLevelLoadControlInformationIePresent)
    {
        stream.add("IE - pgwsNodeLevelLoadControlInformation:");
        stream.endOfLine();
        LoadControlInformationIe loadControlInformation=
        dynamic_cast<
        LoadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(LoadControlInformationIeType));
            PgwsNodeLevelLoadControlInformationInCreateSessionResponse groupedIeInstance =
        dynamic_cast<
        PgwsNodeLevelLoadControlInformationInCreateSessionResponse&>(loadControlInformation.getGroupedIe(msgType, 0));
        groupedIeInstance.displayPgwsNodeLevelLoadControlInformationInCreateSessionResponseData_v(data.pgwsNodeLevelLoadControlInformation, stream);

    }
    if (data.pgwsApnLevelLoadControlInformationIePresent)
    {
        stream.add("IE - pgwsApnLevelLoadControlInformation:");
        stream.endOfLine();
        LoadControlInformationIe loadControlInformation=
        dynamic_cast<
        LoadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(LoadControlInformationIeType));
            PgwsApnLevelLoadControlInformationInCreateSessionResponse groupedIeInstance =
        dynamic_cast<
        PgwsApnLevelLoadControlInformationInCreateSessionResponse&>(loadControlInformation.getGroupedIe(msgType, 1));
        groupedIeInstance.displayPgwsApnLevelLoadControlInformationInCreateSessionResponseData_v(data.pgwsApnLevelLoadControlInformation, stream);

    }
    if (data.sgwsNodeLevelLoadControlInformationIePresent)
    {
        stream.add("IE - sgwsNodeLevelLoadControlInformation:");
        stream.endOfLine();
        LoadControlInformationIe loadControlInformation=
        dynamic_cast<
        LoadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(LoadControlInformationIeType));
            SgwsNodeLevelLoadControlInformationInCreateSessionResponse groupedIeInstance =
        dynamic_cast<
        SgwsNodeLevelLoadControlInformationInCreateSessionResponse&>(loadControlInformation.getGroupedIe(msgType, 2));
        groupedIeInstance.displaySgwsNodeLevelLoadControlInformationInCreateSessionResponseData_v(data.sgwsNodeLevelLoadControlInformation, stream);

    }
    if (data.pgwsOverloadControlInformationIePresent)
    {
        stream.add("IE - pgwsOverloadControlInformation:");
        stream.endOfLine();
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
            PgwsOverloadControlInformationInCreateSessionResponse groupedIeInstance =
        dynamic_cast<
        PgwsOverloadControlInformationInCreateSessionResponse&>(overloadControlInformation.getGroupedIe(msgType, 0));
        groupedIeInstance.displayPgwsOverloadControlInformationInCreateSessionResponseData_v(data.pgwsOverloadControlInformation, stream);

    }
    if (data.sgwsOverloadControlInformationIePresent)
    {
        stream.add("IE - sgwsOverloadControlInformation:");
        stream.endOfLine();
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
            SgwsOverloadControlInformationInCreateSessionResponse groupedIeInstance =
        dynamic_cast<
        SgwsOverloadControlInformationInCreateSessionResponse&>(overloadControlInformation.getGroupedIe(msgType, 1));
        groupedIeInstance.displaySgwsOverloadControlInformationInCreateSessionResponseData_v(data.sgwsOverloadControlInformation, stream);

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
    if (data.pdnConnectionChargingIdIePresent)
    {
        stream.add("IE - pdnConnectionChargingId:");
        stream.endOfLine();
        ChargingIdIe chargingId=
        dynamic_cast<
        ChargingIdIe&>(GtpV2IeFactory::getInstance().getIeObject(ChargingIdIeType));
        chargingId.displayChargingIdIe_v(data.pdnConnectionChargingId, stream);

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
    stream.decrIndent();
    stream.decrIndent();
}


