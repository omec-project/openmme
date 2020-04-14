/*
 * deleteSessionRequestMsg.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */
#include "deleteSessionRequestMsg.h"
#include "../ieClasses/manual/gtpV2Ie.h"
#include "../ieClasses/gtpV2IeFactory.h"
#include "../ieClasses/ebiIe.h"
#include "../ieClasses/indicationIe.h"
#include "../ieClasses/causeIe.h"
#include "../ieClasses/fTeidIe.h"
#include "../ieClasses/uliIe.h"
#include "../ieClasses/pcoIe.h"
#include "../ieClasses/nodeTypeIe.h"
#include "../ieClasses/ueTimeZoneIe.h"
#include "../ieClasses/uliTimestampIe.h"
#include "../ieClasses/ranNasCauseIe.h"
#include "../ieClasses/twanIdentifierIe.h"
#include "../ieClasses/twanIdentifierTimestampIe.h"
#include "../ieClasses/overloadControlInformationIe.h"
#include "../ieClasses/mmeS4SgsnsOverloadControlInformationInDeleteSessionRequest.h"
#include "../ieClasses/overloadControlInformationIe.h"
#include "../ieClasses/sgwsOverloadControlInformationInDeleteSessionRequest.h"
#include "../ieClasses/overloadControlInformationIe.h"
#include "../ieClasses/twanEpdgsOverloadControlInformationInDeleteSessionRequest.h"
#include "../ieClasses/twanIdentifierIe.h"
#include "../ieClasses/twanIdentifierTimestampIe.h"
#include "../ieClasses/ipAddressIe.h"
#include "../ieClasses/portNumberIe.h"
#include "../ieClasses/epcoIe.h"
#include "../ieClasses/portNumberIe.h"
#include "../ieClasses/secondaryRatUsageDataReportIe.h"

DeleteSessionRequestMsg::DeleteSessionRequestMsg()
{
    msgType = DeleteSessionRequestMsgType;

}

DeleteSessionRequestMsg::~DeleteSessionRequestMsg()
{

}

bool DeleteSessionRequestMsg::encodeDeleteSessionRequestMsg(MsgBuffer &buffer,
                        DeleteSessionRequestMsgData
							const &data)
{
    bool rc = false;
    GtpV2IeHeader header;
    Uint16 startIndex = 0;
    Uint16 endIndex = 0;
    Uint16 length = 0;

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

    if (data.causeIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = CauseIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        CauseIe cause=
        dynamic_cast<
        CauseIe&>(GtpV2IeFactory::getInstance().getIeObject(CauseIeType));
        rc = cause.encodeCauseIe(buffer, data.cause);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: cause\n");
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

    if (data.originatingNodeIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = NodeTypeIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        NodeTypeIe nodeType=
        dynamic_cast<
        NodeTypeIe&>(GtpV2IeFactory::getInstance().getIeObject(NodeTypeIeType));
        rc = nodeType.encodeNodeTypeIe(buffer, data.originatingNode);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: originatingNode\n");
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

    if (data.uliTimestampIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = UliTimestampIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        UliTimestampIe uliTimestamp=
        dynamic_cast<
        UliTimestampIe&>(GtpV2IeFactory::getInstance().getIeObject(UliTimestampIeType));
        rc = uliTimestamp.encodeUliTimestampIe(buffer, data.uliTimestamp);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: uliTimestamp\n");
            return false;
        }
    }

    if (data.ranNasReleaseCauseIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = RanNasCauseIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        RanNasCauseIe ranNasCause=
        dynamic_cast<
        RanNasCauseIe&>(GtpV2IeFactory::getInstance().getIeObject(RanNasCauseIeType));
        rc = ranNasCause.encodeRanNasCauseIe(buffer, data.ranNasReleaseCause);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: ranNasReleaseCause\n");
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

    if (data.twanIdentifierTimestampIePresent)
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
        rc = twanIdentifierTimestamp.encodeTwanIdentifierTimestampIe(buffer, data.twanIdentifierTimestamp);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: twanIdentifierTimestamp\n");
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
        MmeS4SgsnsOverloadControlInformationInDeleteSessionRequest groupedIeInstance =
        dynamic_cast<
         MmeS4SgsnsOverloadControlInformationInDeleteSessionRequest&>(overloadControlInformation.getGroupedIe(msgType, 0));
        rc = groupedIeInstance.encodeMmeS4SgsnsOverloadControlInformationInDeleteSessionRequest(buffer, data.mmeS4SgsnsOverloadControlInformation);
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
        SgwsOverloadControlInformationInDeleteSessionRequest groupedIeInstance =
        dynamic_cast<
         SgwsOverloadControlInformationInDeleteSessionRequest&>(overloadControlInformation.getGroupedIe(msgType, 1));
        rc = groupedIeInstance.encodeSgwsOverloadControlInformationInDeleteSessionRequest(buffer, data.sgwsOverloadControlInformation);
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
        TwanEpdgsOverloadControlInformationInDeleteSessionRequest groupedIeInstance =
        dynamic_cast<
         TwanEpdgsOverloadControlInformationInDeleteSessionRequest&>(overloadControlInformation.getGroupedIe(msgType, 2));
        rc = groupedIeInstance.encodeTwanEpdgsOverloadControlInformationInDeleteSessionRequest(buffer, data.twanEpdgsOverloadControlInformation);
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
        header.instance = 1;
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

    if (data.ueTcpPortIePresent)
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
    return rc;

}

bool DeleteSessionRequestMsg::decodeDeleteSessionRequestMsg(MsgBuffer &buffer,
 DeleteSessionRequestMsgData 
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
     
            case CauseIeType:
            {
                CauseIe ieObject =
                dynamic_cast<
                CauseIe&>(GtpV2IeFactory::getInstance().getIeObject(CauseIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeCauseIe(buffer, data.cause, ieHeader.length);

                    data.causeIePresent = true;
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
     
            case NodeTypeIeType:
            {
                NodeTypeIe ieObject =
                dynamic_cast<
                NodeTypeIe&>(GtpV2IeFactory::getInstance().getIeObject(NodeTypeIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeNodeTypeIe(buffer, data.originatingNode, ieHeader.length);

                    data.originatingNodeIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: originatingNode\n");
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
     
            case UliTimestampIeType:
            {
                UliTimestampIe ieObject =
                dynamic_cast<
                UliTimestampIe&>(GtpV2IeFactory::getInstance().getIeObject(UliTimestampIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeUliTimestampIe(buffer, data.uliTimestamp, ieHeader.length);

                    data.uliTimestampIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: uliTimestamp\n");
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
     
            case RanNasCauseIeType:
            {
                RanNasCauseIe ieObject =
                dynamic_cast<
                RanNasCauseIe&>(GtpV2IeFactory::getInstance().getIeObject(RanNasCauseIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeRanNasCauseIe(buffer, data.ranNasReleaseCause, ieHeader.length);

                    data.ranNasReleaseCauseIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: ranNasReleaseCause\n");
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
     
            case TwanIdentifierTimestampIeType:
            {
                TwanIdentifierTimestampIe ieObject =
                dynamic_cast<
                TwanIdentifierTimestampIe&>(GtpV2IeFactory::getInstance().getIeObject(TwanIdentifierTimestampIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeTwanIdentifierTimestampIe(buffer, data.twanIdentifierTimestamp, ieHeader.length);

                    data.twanIdentifierTimestampIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: twanIdentifierTimestamp\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 1)
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
     
            case OverloadControlInformationIeType:
            {
                OverloadControlInformationIe ieObject =
                dynamic_cast<
                OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));

                if(ieHeader.instance == 0)
                {
					MmeS4SgsnsOverloadControlInformationInDeleteSessionRequest groupedIeInstance =
					dynamic_cast<
					MmeS4SgsnsOverloadControlInformationInDeleteSessionRequest&>(ieObject.getGroupedIe(msgType, 0));
					rc = groupedIeInstance.decodeMmeS4SgsnsOverloadControlInformationInDeleteSessionRequest(buffer, data.mmeS4SgsnsOverloadControlInformation, ieHeader.length);

                    data.mmeS4SgsnsOverloadControlInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: mmeS4SgsnsOverloadControlInformation\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 1)
                {
					SgwsOverloadControlInformationInDeleteSessionRequest groupedIeInstance =
					dynamic_cast<
					SgwsOverloadControlInformationInDeleteSessionRequest&>(ieObject.getGroupedIe(msgType, 1));
					rc = groupedIeInstance.decodeSgwsOverloadControlInformationInDeleteSessionRequest(buffer, data.sgwsOverloadControlInformation, ieHeader.length);

                    data.sgwsOverloadControlInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: sgwsOverloadControlInformation\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 2)
                {
					TwanEpdgsOverloadControlInformationInDeleteSessionRequest groupedIeInstance =
					dynamic_cast<
					TwanEpdgsOverloadControlInformationInDeleteSessionRequest&>(ieObject.getGroupedIe(msgType, 2));
					rc = groupedIeInstance.decodeTwanEpdgsOverloadControlInformationInDeleteSessionRequest(buffer, data.twanEpdgsOverloadControlInformation, ieHeader.length);

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

void DeleteSessionRequestMsg::
displayDeleteSessionRequestMsgData_v(DeleteSessionRequestMsgData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("DeleteSessionRequestMsg:");
    stream.endOfLine();
    Uint8 displayCount;
    stream.incrIndent();
    if (data.linkedEpsBearerIdIePresent)
    {
        stream.add("IE - linkedEpsBearerId:");
        stream.endOfLine();
        EbiIe ebi=
        dynamic_cast<
        EbiIe&>(GtpV2IeFactory::getInstance().getIeObject(EbiIeType));
        ebi.displayEbiIe_v(data.linkedEpsBearerId, stream);

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
    if (data.causeIePresent)
    {
        stream.add("IE - cause:");
        stream.endOfLine();
        CauseIe cause=
        dynamic_cast<
        CauseIe&>(GtpV2IeFactory::getInstance().getIeObject(CauseIeType));
        cause.displayCauseIe_v(data.cause, stream);

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
    if (data.userLocationInformationIePresent)
    {
        stream.add("IE - userLocationInformation:");
        stream.endOfLine();
        UliIe uli=
        dynamic_cast<
        UliIe&>(GtpV2IeFactory::getInstance().getIeObject(UliIeType));
        uli.displayUliIe_v(data.userLocationInformation, stream);

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
    if (data.originatingNodeIePresent)
    {
        stream.add("IE - originatingNode:");
        stream.endOfLine();
        NodeTypeIe nodeType=
        dynamic_cast<
        NodeTypeIe&>(GtpV2IeFactory::getInstance().getIeObject(NodeTypeIeType));
        nodeType.displayNodeTypeIe_v(data.originatingNode, stream);

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
    if (data.uliTimestampIePresent)
    {
        stream.add("IE - uliTimestamp:");
        stream.endOfLine();
        UliTimestampIe uliTimestamp=
        dynamic_cast<
        UliTimestampIe&>(GtpV2IeFactory::getInstance().getIeObject(UliTimestampIeType));
        uliTimestamp.displayUliTimestampIe_v(data.uliTimestamp, stream);

    }
    if (data.ranNasReleaseCauseIePresent)
    {
        stream.add("IE - ranNasReleaseCause:");
        stream.endOfLine();
        RanNasCauseIe ranNasCause=
        dynamic_cast<
        RanNasCauseIe&>(GtpV2IeFactory::getInstance().getIeObject(RanNasCauseIeType));
        ranNasCause.displayRanNasCauseIe_v(data.ranNasReleaseCause, stream);

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
    if (data.twanIdentifierTimestampIePresent)
    {
        stream.add("IE - twanIdentifierTimestamp:");
        stream.endOfLine();
        TwanIdentifierTimestampIe twanIdentifierTimestamp=
        dynamic_cast<
        TwanIdentifierTimestampIe&>(GtpV2IeFactory::getInstance().getIeObject(TwanIdentifierTimestampIeType));
        twanIdentifierTimestamp.displayTwanIdentifierTimestampIe_v(data.twanIdentifierTimestamp, stream);

    }
    if (data.mmeS4SgsnsOverloadControlInformationIePresent)
    {
        stream.add("IE - mmeS4SgsnsOverloadControlInformation:");
        stream.endOfLine();
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
            MmeS4SgsnsOverloadControlInformationInDeleteSessionRequest groupedIeInstance =
        dynamic_cast<
        MmeS4SgsnsOverloadControlInformationInDeleteSessionRequest&>(overloadControlInformation.getGroupedIe(msgType, 0));
        groupedIeInstance.displayMmeS4SgsnsOverloadControlInformationInDeleteSessionRequestData_v(data.mmeS4SgsnsOverloadControlInformation, stream);

    }
    if (data.sgwsOverloadControlInformationIePresent)
    {
        stream.add("IE - sgwsOverloadControlInformation:");
        stream.endOfLine();
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
            SgwsOverloadControlInformationInDeleteSessionRequest groupedIeInstance =
        dynamic_cast<
        SgwsOverloadControlInformationInDeleteSessionRequest&>(overloadControlInformation.getGroupedIe(msgType, 1));
        groupedIeInstance.displaySgwsOverloadControlInformationInDeleteSessionRequestData_v(data.sgwsOverloadControlInformation, stream);

    }
    if (data.twanEpdgsOverloadControlInformationIePresent)
    {
        stream.add("IE - twanEpdgsOverloadControlInformation:");
        stream.endOfLine();
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
            TwanEpdgsOverloadControlInformationInDeleteSessionRequest groupedIeInstance =
        dynamic_cast<
        TwanEpdgsOverloadControlInformationInDeleteSessionRequest&>(overloadControlInformation.getGroupedIe(msgType, 2));
        groupedIeInstance.displayTwanEpdgsOverloadControlInformationInDeleteSessionRequestData_v(data.twanEpdgsOverloadControlInformation, stream);

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
    if (data.extendedProtocolConfigurationOptionsIePresent)
    {
        stream.add("IE - extendedProtocolConfigurationOptions:");
        stream.endOfLine();
        EpcoIe epco=
        dynamic_cast<
        EpcoIe&>(GtpV2IeFactory::getInstance().getIeObject(EpcoIeType));
        epco.displayEpcoIe_v(data.extendedProtocolConfigurationOptions, stream);

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
    if (data.secondaryRatUsageDataReportIePresent)
    {
        stream.add("IE - secondaryRatUsageDataReport:");
        stream.endOfLine();
        SecondaryRatUsageDataReportIe secondaryRatUsageDataReport=
        dynamic_cast<
        SecondaryRatUsageDataReportIe&>(GtpV2IeFactory::getInstance().getIeObject(SecondaryRatUsageDataReportIeType));
        secondaryRatUsageDataReport.displaySecondaryRatUsageDataReportIe_v(data.secondaryRatUsageDataReport, stream);

    }
    stream.decrIndent();
    stream.decrIndent();
}


