/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#include "downlinkDataNotificationFailureIndicationMsg.h"
#include "../ieClasses/manual/gtpV2Ie.h"
#include "../ieClasses/gtpV2IeFactory.h"
#include "../ieClasses/causeIe.h"
#include "../ieClasses/nodeTypeIe.h"
#include "../ieClasses/imsiIe.h"

DownlinkDataNotificationFailureIndicationMsg::DownlinkDataNotificationFailureIndicationMsg()
{
    msgType = DownlinkDataNotificationFailureIndicationMsgType;
    Uint16 mandIe;
    mandIe = CauseIeType;
    mandIe = (mandIe << 8) | 0; // cause
    mandatoryIeSet.insert(mandIe);
}

DownlinkDataNotificationFailureIndicationMsg::~DownlinkDataNotificationFailureIndicationMsg()
{

}

bool DownlinkDataNotificationFailureIndicationMsg::encodeDownlinkDataNotificationFailureIndicationMsg(MsgBuffer &buffer,
                        DownlinkDataNotificationFailureIndicationMsgData
							const &data)
{
    bool rc = false;
    GtpV2IeHeader header;
    Uint16 startIndex = 0;
    Uint16 endIndex = 0;
    Uint16 length = 0;

    
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
        errorStream.add((char *)"Failed to encode IE: cause\n");
        return false;
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
            errorStream.add((char *)"Failed to encode IE: originatingNode\n");
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
            errorStream.add((char *)"Failed to encode IE: imsi\n");
            return false;
        }
    }
    return rc;

}

bool DownlinkDataNotificationFailureIndicationMsg::decodeDownlinkDataNotificationFailureIndicationMsg(MsgBuffer &buffer,
 DownlinkDataNotificationFailureIndicationMsgData 
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
            errorStream.add((char *)"IE Length exceeds beyond message boundary\n");
            errorStream.add((char *)"  Offending IE Type: ");
            errorStream.add(ieHeader.ieType);
            errorStream.add((char *)"\n  Ie Length in Header: ");
            errorStream.add(ieHeader.length);
            errorStream.add((char *)"\n  Bytes left in message: ");
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
                        errorStream.add((char *)"Failed to decode IE: cause\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add((char *)"Unknown IE Type: ");
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
                        errorStream.add((char *)"Failed to decode IE: originatingNode\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add((char *)"Unknown IE Type: ");
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
                        errorStream.add((char *)"Failed to decode IE: imsi\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add((char *)"Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }

            default:
            {
                // Unknown IE print error
                errorStream.add((char *)"Unknown IE Type: ");
                errorStream.add(ieHeader.ieType);
                errorStream.endOfLine();
                buffer.skipBytes(ieHeader.length);
            }
        }
    }
    return rc; // TODO validations
}

void DownlinkDataNotificationFailureIndicationMsg::
displayDownlinkDataNotificationFailureIndicationMsgData_v(DownlinkDataNotificationFailureIndicationMsgData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"DownlinkDataNotificationFailureIndicationMsg:");
    stream.endOfLine();
    stream.incrIndent();
        
    
        stream.add((char *)"IE - cause:");
        stream.endOfLine();
        CauseIe cause=
        dynamic_cast<
        CauseIe&>(GtpV2IeFactory::getInstance().getIeObject(CauseIeType));
        cause.displayCauseIe_v(data.cause, stream);

    if (data.originatingNodeIePresent)
    {


        stream.add((char *)"IE - originatingNode:");
        stream.endOfLine();
        NodeTypeIe nodeType=
        dynamic_cast<
        NodeTypeIe&>(GtpV2IeFactory::getInstance().getIeObject(NodeTypeIeType));
        nodeType.displayNodeTypeIe_v(data.originatingNode, stream);

    }
    if (data.imsiIePresent)
    {


        stream.add((char *)"IE - imsi:");
        stream.endOfLine();
        ImsiIe imsi=
        dynamic_cast<
        ImsiIe&>(GtpV2IeFactory::getInstance().getIeObject(ImsiIeType));
        imsi.displayImsiIe_v(data.imsi, stream);

    }

    stream.decrIndent();
    stream.decrIndent();
}


