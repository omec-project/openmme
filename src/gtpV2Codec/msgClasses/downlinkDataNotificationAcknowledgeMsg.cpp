/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#include "downlinkDataNotificationAcknowledgeMsg.h"
#include "../ieClasses/manual/gtpV2Ie.h"
#include "../ieClasses/gtpV2IeFactory.h"
#include "../ieClasses/causeIe.h"
#include "../ieClasses/delayValueIe.h"
#include "../ieClasses/recoveryIe.h"
#include "../ieClasses/throttlingIe.h"
#include "../ieClasses/imsiIe.h"
#include "../ieClasses/epcTimerIe.h"
#include "../ieClasses/integerNumberIe.h"

DownlinkDataNotificationAcknowledgeMsg::DownlinkDataNotificationAcknowledgeMsg()
{
    msgType = DownlinkDataNotificationAcknowledgeMsgType;
    Uint16 mandIe;
    mandIe = CauseIeType;
    mandIe = (mandIe << 8) | 0; // cause
    mandatoryIeSet.insert(mandIe);
}

DownlinkDataNotificationAcknowledgeMsg::~DownlinkDataNotificationAcknowledgeMsg()
{

}

bool DownlinkDataNotificationAcknowledgeMsg::encodeDownlinkDataNotificationAcknowledgeMsg(MsgBuffer &buffer,
                        DownlinkDataNotificationAcknowledgeMsgData
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

    if (data.dataNotificationDelayIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = DelayValueIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        DelayValueIe delayValue=
        dynamic_cast<
        DelayValueIe&>(GtpV2IeFactory::getInstance().getIeObject(DelayValueIeType));
        rc = delayValue.encodeDelayValueIe(buffer, data.dataNotificationDelay);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: dataNotificationDelay\n");
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
            errorStream.add((char *)"Failed to encode IE: recovery\n");
            return false;
        }
    }

    if (data.dlLowPriorityTrafficThrottlingIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = ThrottlingIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        ThrottlingIe throttling=
        dynamic_cast<
        ThrottlingIe&>(GtpV2IeFactory::getInstance().getIeObject(ThrottlingIeType));
        rc = throttling.encodeThrottlingIe(buffer, data.dlLowPriorityTrafficThrottling);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: dlLowPriorityTrafficThrottling\n");
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

    if (data.dlBufferingDurationIePresent)
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
        rc = epcTimer.encodeEpcTimerIe(buffer, data.dlBufferingDuration);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: dlBufferingDuration\n");
            return false;
        }
    }

    if (data.dlBufferingSuggestedPacketCountIePresent)
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
        rc = integerNumber.encodeIntegerNumberIe(buffer, data.dlBufferingSuggestedPacketCount);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: dlBufferingSuggestedPacketCount\n");
            return false;
        }
    }
    return rc;

}

bool DownlinkDataNotificationAcknowledgeMsg::decodeDownlinkDataNotificationAcknowledgeMsg(MsgBuffer &buffer,
 DownlinkDataNotificationAcknowledgeMsgData 
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
     
            case DelayValueIeType:
            {
                DelayValueIe ieObject =
                dynamic_cast<
                DelayValueIe&>(GtpV2IeFactory::getInstance().getIeObject(DelayValueIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeDelayValueIe(buffer, data.dataNotificationDelay, ieHeader.length);

                    data.dataNotificationDelayIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: dataNotificationDelay\n");
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
                        errorStream.add((char *)"Failed to decode IE: recovery\n");
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
     
            case ThrottlingIeType:
            {
                ThrottlingIe ieObject =
                dynamic_cast<
                ThrottlingIe&>(GtpV2IeFactory::getInstance().getIeObject(ThrottlingIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeThrottlingIe(buffer, data.dlLowPriorityTrafficThrottling, ieHeader.length);

                    data.dlLowPriorityTrafficThrottlingIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: dlLowPriorityTrafficThrottling\n");
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
     
            case EpcTimerIeType:
            {
                EpcTimerIe ieObject =
                dynamic_cast<
                EpcTimerIe&>(GtpV2IeFactory::getInstance().getIeObject(EpcTimerIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeEpcTimerIe(buffer, data.dlBufferingDuration, ieHeader.length);

                    data.dlBufferingDurationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: dlBufferingDuration\n");
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
     
            case IntegerNumberIeType:
            {
                IntegerNumberIe ieObject =
                dynamic_cast<
                IntegerNumberIe&>(GtpV2IeFactory::getInstance().getIeObject(IntegerNumberIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeIntegerNumberIe(buffer, data.dlBufferingSuggestedPacketCount, ieHeader.length);

                    data.dlBufferingSuggestedPacketCountIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: dlBufferingSuggestedPacketCount\n");
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

void DownlinkDataNotificationAcknowledgeMsg::
displayDownlinkDataNotificationAcknowledgeMsgData_v(DownlinkDataNotificationAcknowledgeMsgData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"DownlinkDataNotificationAcknowledgeMsg:");
    stream.endOfLine();
    stream.incrIndent();
        
    
        stream.add((char *)"IE - cause:");
        stream.endOfLine();
        CauseIe cause=
        dynamic_cast<
        CauseIe&>(GtpV2IeFactory::getInstance().getIeObject(CauseIeType));
        cause.displayCauseIe_v(data.cause, stream);

    if (data.dataNotificationDelayIePresent)
    {


        stream.add((char *)"IE - dataNotificationDelay:");
        stream.endOfLine();
        DelayValueIe delayValue=
        dynamic_cast<
        DelayValueIe&>(GtpV2IeFactory::getInstance().getIeObject(DelayValueIeType));
        delayValue.displayDelayValueIe_v(data.dataNotificationDelay, stream);

    }
    if (data.recoveryIePresent)
    {


        stream.add((char *)"IE - recovery:");
        stream.endOfLine();
        RecoveryIe recovery=
        dynamic_cast<
        RecoveryIe&>(GtpV2IeFactory::getInstance().getIeObject(RecoveryIeType));
        recovery.displayRecoveryIe_v(data.recovery, stream);

    }
    if (data.dlLowPriorityTrafficThrottlingIePresent)
    {


        stream.add((char *)"IE - dlLowPriorityTrafficThrottling:");
        stream.endOfLine();
        ThrottlingIe throttling=
        dynamic_cast<
        ThrottlingIe&>(GtpV2IeFactory::getInstance().getIeObject(ThrottlingIeType));
        throttling.displayThrottlingIe_v(data.dlLowPriorityTrafficThrottling, stream);

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
    if (data.dlBufferingDurationIePresent)
    {


        stream.add((char *)"IE - dlBufferingDuration:");
        stream.endOfLine();
        EpcTimerIe epcTimer=
        dynamic_cast<
        EpcTimerIe&>(GtpV2IeFactory::getInstance().getIeObject(EpcTimerIeType));
        epcTimer.displayEpcTimerIe_v(data.dlBufferingDuration, stream);

    }
    if (data.dlBufferingSuggestedPacketCountIePresent)
    {


        stream.add((char *)"IE - dlBufferingSuggestedPacketCount:");
        stream.endOfLine();
        IntegerNumberIe integerNumber=
        dynamic_cast<
        IntegerNumberIe&>(GtpV2IeFactory::getInstance().getIeObject(IntegerNumberIeType));
        integerNumber.displayIntegerNumberIe_v(data.dlBufferingSuggestedPacketCount, stream);

    }

    stream.decrIndent();
    stream.decrIndent();
}


