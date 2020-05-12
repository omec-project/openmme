/*
 * createBearerResponseMsg.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */
#include "createBearerResponseMsg.h"
#include "../ieClasses/manual/gtpV2Ie.h"
#include "../ieClasses/gtpV2IeFactory.h"
#include "../ieClasses/causeIe.h"
#include "../ieClasses/bearerContextIe.h"
#include "../ieClasses/bearerContextsInCreateBearerResponse.h"
#include "../ieClasses/recoveryIe.h"
#include "../ieClasses/fqCsidIe.h"
#include "../ieClasses/fqCsidIe.h"
#include "../ieClasses/fqCsidIe.h"
#include "../ieClasses/fqCsidIe.h"
#include "../ieClasses/pcoIe.h"
#include "../ieClasses/ueTimeZoneIe.h"
#include "../ieClasses/uliIe.h"
#include "../ieClasses/twanIdentifierIe.h"
#include "../ieClasses/overloadControlInformationIe.h"
#include "../ieClasses/mmeS4SgsnsOverloadControlInformationInCreateBearerResponse.h"
#include "../ieClasses/overloadControlInformationIe.h"
#include "../ieClasses/sgwsOverloadControlInformationInCreateBearerResponse.h"
#include "../ieClasses/ipAddressIe.h"
#include "../ieClasses/overloadControlInformationIe.h"
#include "../ieClasses/twanEpdgsOverloadControlInformationInCreateBearerResponse.h"
#include "../ieClasses/twanIdentifierIe.h"
#include "../ieClasses/twanIdentifierTimestampIe.h"
#include "../ieClasses/ipAddressIe.h"
#include "../ieClasses/portNumberIe.h"
#include "../ieClasses/fContainerIe.h"
#include "../ieClasses/portNumberIe.h"

CreateBearerResponseMsg::CreateBearerResponseMsg()
{
    msgType = CreateBearerResponseMsgType;
    Uint16 mandIe;
    mandIe = CauseIeType;
    mandIe = (mandIe << 8) | 0; // cause
    mandatoryIeSet.insert(mandIe);    mandIe = BearerContextIeType;
    mandIe = (mandIe << 8) | 0; // bearerContexts
    mandatoryIeSet.insert(mandIe);
}

CreateBearerResponseMsg::~CreateBearerResponseMsg()
{

}

bool CreateBearerResponseMsg::encodeCreateBearerResponseMsg(MsgBuffer &buffer,
                        CreateBearerResponseMsgData
							const &data)
{
    bool rc = false;
    GtpV2IeHeader header;
    Uint16 startIndex = 0;
    Uint16 endIndex = 0;
    Uint16 length = 0;



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
        MmeS4SgsnsOverloadControlInformationInCreateBearerResponse groupedIeInstance =
        dynamic_cast<
         MmeS4SgsnsOverloadControlInformationInCreateBearerResponse&>(overloadControlInformation.getGroupedIe(msgType, 0));
        rc = groupedIeInstance.encodeMmeS4SgsnsOverloadControlInformationInCreateBearerResponse(buffer, data.mmeS4SgsnsOverloadControlInformation);
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
        SgwsOverloadControlInformationInCreateBearerResponse groupedIeInstance =
        dynamic_cast<
         SgwsOverloadControlInformationInCreateBearerResponse&>(overloadControlInformation.getGroupedIe(msgType, 1));
        rc = groupedIeInstance.encodeSgwsOverloadControlInformationInCreateBearerResponse(buffer, data.sgwsOverloadControlInformation);
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

    if (data.mmeS4SgsnIdentifierIePresent)
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
        TwanEpdgsOverloadControlInformationInCreateBearerResponse groupedIeInstance =
        dynamic_cast<
         TwanEpdgsOverloadControlInformationInCreateBearerResponse&>(overloadControlInformation.getGroupedIe(msgType, 2));
        rc = groupedIeInstance.encodeTwanEpdgsOverloadControlInformationInCreateBearerResponse(buffer, data.twanEpdgsOverloadControlInformation);
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
    return rc;

}

bool CreateBearerResponseMsg::decodeCreateBearerResponseMsg(MsgBuffer &buffer,
 CreateBearerResponseMsgData 
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
     
            case BearerContextIeType:
            {
                BearerContextIe ieObject =
                dynamic_cast<
                BearerContextIe&>(GtpV2IeFactory::getInstance().getIeObject(BearerContextIeType));

                if(ieHeader.instance == 0)
                {
					// First check if we have enough space left to decode and store this instance
                    if (data.bearerContextsCount == 11)
                    {
                        errorStream.add("More than 11 instances of bearerContexts received\n");
                        return false;
                    }
                    BearerContextsInCreateBearerResponse groupedIeInstance =
                    dynamic_cast<
                    BearerContextsInCreateBearerResponse&>(ieObject.getGroupedIe(msgType, 0));
                    rc = groupedIeInstance.decodeBearerContextsInCreateBearerResponse(buffer,
                    data.bearerContexts[data.bearerContextsCount], ieHeader.length);
                    data.bearerContextsCount++; // TODO Count validation

                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: bearerContexts\n");
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
     
            case OverloadControlInformationIeType:
            {
                OverloadControlInformationIe ieObject =
                dynamic_cast<
                OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));

                if(ieHeader.instance == 0)
                {
					MmeS4SgsnsOverloadControlInformationInCreateBearerResponse groupedIeInstance =
					dynamic_cast<
					MmeS4SgsnsOverloadControlInformationInCreateBearerResponse&>(ieObject.getGroupedIe(msgType, 0));
					rc = groupedIeInstance.decodeMmeS4SgsnsOverloadControlInformationInCreateBearerResponse(buffer, data.mmeS4SgsnsOverloadControlInformation, ieHeader.length);

                    data.mmeS4SgsnsOverloadControlInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: mmeS4SgsnsOverloadControlInformation\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 1)
                {
					SgwsOverloadControlInformationInCreateBearerResponse groupedIeInstance =
					dynamic_cast<
					SgwsOverloadControlInformationInCreateBearerResponse&>(ieObject.getGroupedIe(msgType, 1));
					rc = groupedIeInstance.decodeSgwsOverloadControlInformationInCreateBearerResponse(buffer, data.sgwsOverloadControlInformation, ieHeader.length);

                    data.sgwsOverloadControlInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: sgwsOverloadControlInformation\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 2)
                {
					TwanEpdgsOverloadControlInformationInCreateBearerResponse groupedIeInstance =
					dynamic_cast<
					TwanEpdgsOverloadControlInformationInCreateBearerResponse&>(ieObject.getGroupedIe(msgType, 2));
					rc = groupedIeInstance.decodeTwanEpdgsOverloadControlInformationInCreateBearerResponse(buffer, data.twanEpdgsOverloadControlInformation, ieHeader.length);

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
					rc = ieObject.decodeIpAddressIe(buffer, data.mmeS4SgsnIdentifier, ieHeader.length);

                    data.mmeS4SgsnIdentifierIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: mmeS4SgsnIdentifier\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 0)
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
     
            case TwanIdentifierTimestampIeType:
            {
                TwanIdentifierTimestampIe ieObject =
                dynamic_cast<
                TwanIdentifierTimestampIe&>(GtpV2IeFactory::getInstance().getIeObject(TwanIdentifierTimestampIeType));

                if(ieHeader.instance == 1)
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

void CreateBearerResponseMsg::
displayCreateBearerResponseMsgData_v(CreateBearerResponseMsgData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("CreateBearerResponseMsg:");
    stream.endOfLine();
    Uint8 displayCount;
    stream.incrIndent();
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
    if (data.protocolConfigurationOptionsIePresent)
    {
        stream.add("IE - protocolConfigurationOptions:");
        stream.endOfLine();
        PcoIe pco=
        dynamic_cast<
        PcoIe&>(GtpV2IeFactory::getInstance().getIeObject(PcoIeType));
        pco.displayPcoIe_v(data.protocolConfigurationOptions, stream);

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
    if (data.userLocationInformationIePresent)
    {
        stream.add("IE - userLocationInformation:");
        stream.endOfLine();
        UliIe uli=
        dynamic_cast<
        UliIe&>(GtpV2IeFactory::getInstance().getIeObject(UliIeType));
        uli.displayUliIe_v(data.userLocationInformation, stream);

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
    if (data.mmeS4SgsnsOverloadControlInformationIePresent)
    {
        stream.add("IE - mmeS4SgsnsOverloadControlInformation:");
        stream.endOfLine();
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
            MmeS4SgsnsOverloadControlInformationInCreateBearerResponse groupedIeInstance =
        dynamic_cast<
        MmeS4SgsnsOverloadControlInformationInCreateBearerResponse&>(overloadControlInformation.getGroupedIe(msgType, 0));
        groupedIeInstance.displayMmeS4SgsnsOverloadControlInformationInCreateBearerResponseData_v(data.mmeS4SgsnsOverloadControlInformation, stream);

    }
    if (data.sgwsOverloadControlInformationIePresent)
    {
        stream.add("IE - sgwsOverloadControlInformation:");
        stream.endOfLine();
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
            SgwsOverloadControlInformationInCreateBearerResponse groupedIeInstance =
        dynamic_cast<
        SgwsOverloadControlInformationInCreateBearerResponse&>(overloadControlInformation.getGroupedIe(msgType, 1));
        groupedIeInstance.displaySgwsOverloadControlInformationInCreateBearerResponseData_v(data.sgwsOverloadControlInformation, stream);

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
    if (data.twanEpdgsOverloadControlInformationIePresent)
    {
        stream.add("IE - twanEpdgsOverloadControlInformation:");
        stream.endOfLine();
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
            TwanEpdgsOverloadControlInformationInCreateBearerResponse groupedIeInstance =
        dynamic_cast<
        TwanEpdgsOverloadControlInformationInCreateBearerResponse&>(overloadControlInformation.getGroupedIe(msgType, 2));
        groupedIeInstance.displayTwanEpdgsOverloadControlInformationInCreateBearerResponseData_v(data.twanEpdgsOverloadControlInformation, stream);

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
    if (data.nbifomContainerIePresent)
    {
        stream.add("IE - nbifomContainer:");
        stream.endOfLine();
        FContainerIe fContainer=
        dynamic_cast<
        FContainerIe&>(GtpV2IeFactory::getInstance().getIeObject(FContainerIeType));
        fContainer.displayFContainerIe_v(data.nbifomContainer, stream);

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
    stream.decrIndent();
    stream.decrIndent();
}


