/*
 * Copyright (c) 2019, Infosys Ltd.
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

#include "releaseAccessBearersResponseMsg.h"
#include "../ieClasses/manual/gtpV2Ie.h"
#include "../ieClasses/gtpV2IeFactory.h"
#include "../ieClasses/causeIe.h"
#include "../ieClasses/recoveryIe.h"
#include "../ieClasses/indicationIe.h"
#include "../ieClasses/loadControlInformationIe.h"
#include "../ieClasses/sgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponse.h"
#include "../ieClasses/overloadControlInformationIe.h"
#include "../ieClasses/sgwsOverloadControlInformationInReleaseAccessBearersResponse.h"

ReleaseAccessBearersResponseMsg::ReleaseAccessBearersResponseMsg()
{
    msgType = ReleaseAccessBearersResponseMsgType;
    Uint16 mandIe;
    mandIe = CauseIeType;
    mandIe = (mandIe << 8) | 0; // cause
    mandatoryIeSet.insert(mandIe);
}

ReleaseAccessBearersResponseMsg::~ReleaseAccessBearersResponseMsg()
{

}

bool ReleaseAccessBearersResponseMsg::encodeReleaseAccessBearersResponseMsg(MsgBuffer &buffer,
                        ReleaseAccessBearersResponseMsgData
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
            errorStream.add((char *)"Failed to encode IE: indicationFlags\n");
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
        SgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponse groupedIeInstance =
        dynamic_cast<
         SgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponse&>(loadControlInformation.getGroupedIe(msgType, 0));
        rc = groupedIeInstance.encodeSgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponse(buffer, data.sgwsNodeLevelLoadControlInformation);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: sgwsNodeLevelLoadControlInformation\n");
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
        SgwsOverloadControlInformationInReleaseAccessBearersResponse groupedIeInstance =
        dynamic_cast<
         SgwsOverloadControlInformationInReleaseAccessBearersResponse&>(overloadControlInformation.getGroupedIe(msgType, 0));
        rc = groupedIeInstance.encodeSgwsOverloadControlInformationInReleaseAccessBearersResponse(buffer, data.sgwsOverloadControlInformation);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: sgwsOverloadControlInformation\n");
            return false;
        }
    }
    return rc;

}

bool ReleaseAccessBearersResponseMsg::decodeReleaseAccessBearersResponseMsg(MsgBuffer &buffer,
 ReleaseAccessBearersResponseMsgData 
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
                        errorStream.add((char *)"Failed to decode IE: indicationFlags\n");
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
     
            case LoadControlInformationIeType:
            {
                LoadControlInformationIe ieObject =
                dynamic_cast<
                LoadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(LoadControlInformationIeType));

                if(ieHeader.instance == 0)
                {
					SgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponse groupedIeInstance =
					dynamic_cast<
					SgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponse&>(ieObject.getGroupedIe(msgType, 0));
					rc = groupedIeInstance.decodeSgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponse(buffer, data.sgwsNodeLevelLoadControlInformation, ieHeader.length);

                    data.sgwsNodeLevelLoadControlInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: sgwsNodeLevelLoadControlInformation\n");
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
     
            case OverloadControlInformationIeType:
            {
                OverloadControlInformationIe ieObject =
                dynamic_cast<
                OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));

                if(ieHeader.instance == 0)
                {
					SgwsOverloadControlInformationInReleaseAccessBearersResponse groupedIeInstance =
					dynamic_cast<
					SgwsOverloadControlInformationInReleaseAccessBearersResponse&>(ieObject.getGroupedIe(msgType, 0));
					rc = groupedIeInstance.decodeSgwsOverloadControlInformationInReleaseAccessBearersResponse(buffer, data.sgwsOverloadControlInformation, ieHeader.length);

                    data.sgwsOverloadControlInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: sgwsOverloadControlInformation\n");
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

void ReleaseAccessBearersResponseMsg::
displayReleaseAccessBearersResponseMsgData_v(ReleaseAccessBearersResponseMsgData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"ReleaseAccessBearersResponseMsg:");
    stream.endOfLine();
    Uint8 displayCount;
    stream.incrIndent();
    if (data.recoveryIePresent)
    {
        stream.add((char *)"IE - recovery:");
        stream.endOfLine();
        RecoveryIe recovery=
        dynamic_cast<
        RecoveryIe&>(GtpV2IeFactory::getInstance().getIeObject(RecoveryIeType));
        recovery.displayRecoveryIe_v(data.recovery, stream);

    }
    if (data.indicationFlagsIePresent)
    {
        stream.add((char *)"IE - indicationFlags:");
        stream.endOfLine();
        IndicationIe indication=
        dynamic_cast<
        IndicationIe&>(GtpV2IeFactory::getInstance().getIeObject(IndicationIeType));
        indication.displayIndicationIe_v(data.indicationFlags, stream);

    }
    if (data.sgwsNodeLevelLoadControlInformationIePresent)
    {
        stream.add((char *)"IE - sgwsNodeLevelLoadControlInformation:");
        stream.endOfLine();
        LoadControlInformationIe loadControlInformation=
        dynamic_cast<
        LoadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(LoadControlInformationIeType));
            SgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponse groupedIeInstance =
        dynamic_cast<
        SgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponse&>(loadControlInformation.getGroupedIe(msgType, 0));
        groupedIeInstance.displaySgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponseData_v(data.sgwsNodeLevelLoadControlInformation, stream);

    }
    if (data.sgwsOverloadControlInformationIePresent)
    {
        stream.add((char *)"IE - sgwsOverloadControlInformation:");
        stream.endOfLine();
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
            SgwsOverloadControlInformationInReleaseAccessBearersResponse groupedIeInstance =
        dynamic_cast<
        SgwsOverloadControlInformationInReleaseAccessBearersResponse&>(overloadControlInformation.getGroupedIe(msgType, 0));
        groupedIeInstance.displaySgwsOverloadControlInformationInReleaseAccessBearersResponseData_v(data.sgwsOverloadControlInformation, stream);

    }
    stream.decrIndent();
    stream.decrIndent();
}


