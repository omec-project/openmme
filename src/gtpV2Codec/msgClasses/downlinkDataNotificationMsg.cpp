/*
 * downlinkDataNotificationMsg.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */
#include "downlinkDataNotificationMsg.h"
#include "../ieClasses/manual/gtpV2Ie.h"
#include "../ieClasses/gtpV2IeFactory.h"
#include "../ieClasses/causeIe.h"
#include "../ieClasses/ebiIe.h"
#include "../ieClasses/arpIe.h"
#include "../ieClasses/imsiIe.h"
#include "../ieClasses/fTeidIe.h"
#include "../ieClasses/indicationIe.h"
#include "../ieClasses/loadControlInformationIe.h"
#include "../ieClasses/sgwsNodeLevelLoadControlInformationInDownlinkDataNotification.h"
#include "../ieClasses/overloadControlInformationIe.h"
#include "../ieClasses/sgwsOverloadControlInformationInDownlinkDataNotification.h"
#include "../ieClasses/pagingAndServiceInformationIe.h"

DownlinkDataNotificationMsg::DownlinkDataNotificationMsg()
{
    msgType = DownlinkDataNotificationMsgType;

}

DownlinkDataNotificationMsg::~DownlinkDataNotificationMsg()
{

}

bool DownlinkDataNotificationMsg::encodeDownlinkDataNotificationMsg(MsgBuffer &buffer,
                        DownlinkDataNotificationMsgData
							const &data)
{
    bool rc = false;
    GtpV2IeHeader header;
    Uint16 startIndex = 0;
    Uint16 endIndex = 0;
    Uint16 length = 0;

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

    if (data.epsBearerIdIePresent)
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
        rc = ebi.encodeEbiIe(buffer, data.epsBearerId);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: epsBearerId\n");
            return false;
        }
    }

    if (data.allocationRetentionPriorityIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = ArpIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        ArpIe arp=
        dynamic_cast<
        ArpIe&>(GtpV2IeFactory::getInstance().getIeObject(ArpIeType));
        rc = arp.encodeArpIe(buffer, data.allocationRetentionPriority);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: allocationRetentionPriority\n");
            return false;
        }
    }

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

    if (data.sgwsNodeLevelLoadControlInformationIePresent)
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
        SgwsNodeLevelLoadControlInformationInDownlinkDataNotification groupedIeInstance =
        dynamic_cast<
         SgwsNodeLevelLoadControlInformationInDownlinkDataNotification&>(loadControlInformation.getGroupedIe(msgType, 0));
        rc = groupedIeInstance.encodeSgwsNodeLevelLoadControlInformationInDownlinkDataNotification(buffer, data.sgwsNodeLevelLoadControlInformation);
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

    if (data.sgwsOverloadControlInformationIePresent)
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
        SgwsOverloadControlInformationInDownlinkDataNotification groupedIeInstance =
        dynamic_cast<
         SgwsOverloadControlInformationInDownlinkDataNotification&>(overloadControlInformation.getGroupedIe(msgType, 0));
        rc = groupedIeInstance.encodeSgwsOverloadControlInformationInDownlinkDataNotification(buffer, data.sgwsOverloadControlInformation);
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

    if (data.pagingAndServiceInformationIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = PagingAndServiceInformationIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        PagingAndServiceInformationIe pagingAndServiceInformation=
        dynamic_cast<
        PagingAndServiceInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(PagingAndServiceInformationIeType));
        rc = pagingAndServiceInformation.encodePagingAndServiceInformationIe(buffer, data.pagingAndServiceInformation);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: pagingAndServiceInformation\n");
            return false;
        }
    }
    return rc;

}

bool DownlinkDataNotificationMsg::decodeDownlinkDataNotificationMsg(MsgBuffer &buffer,
 DownlinkDataNotificationMsgData 
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
     
            case EbiIeType:
            {
                EbiIe ieObject =
                dynamic_cast<
                EbiIe&>(GtpV2IeFactory::getInstance().getIeObject(EbiIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeEbiIe(buffer, data.epsBearerId, ieHeader.length);

                    data.epsBearerIdIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: epsBearerId\n");
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
     
            case ArpIeType:
            {
                ArpIe ieObject =
                dynamic_cast<
                ArpIe&>(GtpV2IeFactory::getInstance().getIeObject(ArpIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeArpIe(buffer, data.allocationRetentionPriority, ieHeader.length);

                    data.allocationRetentionPriorityIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: allocationRetentionPriority\n");
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
     
            case LoadControlInformationIeType:
            {
                LoadControlInformationIe ieObject =
                dynamic_cast<
                LoadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(LoadControlInformationIeType));

                if(ieHeader.instance == 0)
                {
					SgwsNodeLevelLoadControlInformationInDownlinkDataNotification groupedIeInstance =
					dynamic_cast<
					SgwsNodeLevelLoadControlInformationInDownlinkDataNotification&>(ieObject.getGroupedIe(msgType, 0));
					rc = groupedIeInstance.decodeSgwsNodeLevelLoadControlInformationInDownlinkDataNotification(buffer, data.sgwsNodeLevelLoadControlInformation, ieHeader.length);

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
					SgwsOverloadControlInformationInDownlinkDataNotification groupedIeInstance =
					dynamic_cast<
					SgwsOverloadControlInformationInDownlinkDataNotification&>(ieObject.getGroupedIe(msgType, 0));
					rc = groupedIeInstance.decodeSgwsOverloadControlInformationInDownlinkDataNotification(buffer, data.sgwsOverloadControlInformation, ieHeader.length);

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
     
            case PagingAndServiceInformationIeType:
            {
                PagingAndServiceInformationIe ieObject =
                dynamic_cast<
                PagingAndServiceInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(PagingAndServiceInformationIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodePagingAndServiceInformationIe(buffer, data.pagingAndServiceInformation, ieHeader.length);

                    data.pagingAndServiceInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: pagingAndServiceInformation\n");
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

void DownlinkDataNotificationMsg::
displayDownlinkDataNotificationMsgData_v(DownlinkDataNotificationMsgData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("DownlinkDataNotificationMsg:");
    stream.endOfLine();
    Uint8 displayCount;
    stream.incrIndent();
    if (data.causeIePresent)
    {
        stream.add("IE - cause:");
        stream.endOfLine();
        CauseIe cause=
        dynamic_cast<
        CauseIe&>(GtpV2IeFactory::getInstance().getIeObject(CauseIeType));
        cause.displayCauseIe_v(data.cause, stream);

    }
    if (data.epsBearerIdIePresent)
    {
        stream.add("IE - epsBearerId:");
        stream.endOfLine();
        EbiIe ebi=
        dynamic_cast<
        EbiIe&>(GtpV2IeFactory::getInstance().getIeObject(EbiIeType));
        ebi.displayEbiIe_v(data.epsBearerId, stream);

    }
    if (data.allocationRetentionPriorityIePresent)
    {
        stream.add("IE - allocationRetentionPriority:");
        stream.endOfLine();
        ArpIe arp=
        dynamic_cast<
        ArpIe&>(GtpV2IeFactory::getInstance().getIeObject(ArpIeType));
        arp.displayArpIe_v(data.allocationRetentionPriority, stream);

    }
    if (data.imsiIePresent)
    {
        stream.add("IE - imsi:");
        stream.endOfLine();
        ImsiIe imsi=
        dynamic_cast<
        ImsiIe&>(GtpV2IeFactory::getInstance().getIeObject(ImsiIeType));
        imsi.displayImsiIe_v(data.imsi, stream);

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
    if (data.indicationFlagsIePresent)
    {
        stream.add("IE - indicationFlags:");
        stream.endOfLine();
        IndicationIe indication=
        dynamic_cast<
        IndicationIe&>(GtpV2IeFactory::getInstance().getIeObject(IndicationIeType));
        indication.displayIndicationIe_v(data.indicationFlags, stream);

    }
    if (data.sgwsNodeLevelLoadControlInformationIePresent)
    {
        stream.add("IE - sgwsNodeLevelLoadControlInformation:");
        stream.endOfLine();
        LoadControlInformationIe loadControlInformation=
        dynamic_cast<
        LoadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(LoadControlInformationIeType));
            SgwsNodeLevelLoadControlInformationInDownlinkDataNotification groupedIeInstance =
        dynamic_cast<
        SgwsNodeLevelLoadControlInformationInDownlinkDataNotification&>(loadControlInformation.getGroupedIe(msgType, 0));
        groupedIeInstance.displaySgwsNodeLevelLoadControlInformationInDownlinkDataNotificationData_v(data.sgwsNodeLevelLoadControlInformation, stream);

    }
    if (data.sgwsOverloadControlInformationIePresent)
    {
        stream.add("IE - sgwsOverloadControlInformation:");
        stream.endOfLine();
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
            SgwsOverloadControlInformationInDownlinkDataNotification groupedIeInstance =
        dynamic_cast<
        SgwsOverloadControlInformationInDownlinkDataNotification&>(overloadControlInformation.getGroupedIe(msgType, 0));
        groupedIeInstance.displaySgwsOverloadControlInformationInDownlinkDataNotificationData_v(data.sgwsOverloadControlInformation, stream);

    }
    if (data.pagingAndServiceInformationIePresent)
    {
        stream.add("IE - pagingAndServiceInformation:");
        stream.endOfLine();
        PagingAndServiceInformationIe pagingAndServiceInformation=
        dynamic_cast<
        PagingAndServiceInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(PagingAndServiceInformationIeType));
        pagingAndServiceInformation.displayPagingAndServiceInformationIe_v(data.pagingAndServiceInformation, stream);

    }
    stream.decrIndent();
    stream.decrIndent();
}


