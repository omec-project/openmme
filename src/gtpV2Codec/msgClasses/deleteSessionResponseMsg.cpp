/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#include "deleteSessionResponseMsg.h"
#include "../ieClasses/manual/gtpV2Ie.h"
#include "../ieClasses/gtpV2IeFactory.h"
#include "../ieClasses/causeIe.h"
#include "../ieClasses/recoveryIe.h"
#include "../ieClasses/pcoIe.h"
#include "../ieClasses/indicationIe.h"
#include "../ieClasses/loadControlInformationIe.h"
#include "../ieClasses/pgwsNodeLevelLoadControlInformationInDeleteSessionResponse.h"
#include "../ieClasses/loadControlInformationIe.h"
#include "../ieClasses/pgwsApnLevelLoadControlInformationInDeleteSessionResponse.h"
#include "../ieClasses/loadControlInformationIe.h"
#include "../ieClasses/sgwsNodeLevelLoadControlInformationInDeleteSessionResponse.h"
#include "../ieClasses/overloadControlInformationIe.h"
#include "../ieClasses/pgwsOverloadControlInformationInDeleteSessionResponse.h"
#include "../ieClasses/overloadControlInformationIe.h"
#include "../ieClasses/sgwsOverloadControlInformationInDeleteSessionResponse.h"
#include "../ieClasses/epcoIe.h"

DeleteSessionResponseMsg::DeleteSessionResponseMsg()
{
    msgType = DeleteSessionResponseMsgType;
    Uint16 mandIe;
    mandIe = CauseIeType;
    mandIe = (mandIe << 8) | 0; // cause
    mandatoryIeSet.insert(mandIe);
}

DeleteSessionResponseMsg::~DeleteSessionResponseMsg()
{

}

bool DeleteSessionResponseMsg::encodeDeleteSessionResponseMsg(MsgBuffer &buffer,
                        DeleteSessionResponseMsgData
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
            errorStream.add((char *)"Failed to encode IE: protocolConfigurationOptions\n");
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
        PgwsNodeLevelLoadControlInformationInDeleteSessionResponse groupedIeInstance =
        dynamic_cast<
         PgwsNodeLevelLoadControlInformationInDeleteSessionResponse&>(loadControlInformation.getGroupedIe(msgType, 0));
        rc = groupedIeInstance.encodePgwsNodeLevelLoadControlInformationInDeleteSessionResponse(buffer, data.pgwsNodeLevelLoadControlInformation);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: pgwsNodeLevelLoadControlInformation\n");
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
        PgwsApnLevelLoadControlInformationInDeleteSessionResponse groupedIeInstance =
        dynamic_cast<
         PgwsApnLevelLoadControlInformationInDeleteSessionResponse&>(loadControlInformation.getGroupedIe(msgType, 1));
        rc = groupedIeInstance.encodePgwsApnLevelLoadControlInformationInDeleteSessionResponse(buffer, data.pgwsApnLevelLoadControlInformation);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: pgwsApnLevelLoadControlInformation\n");
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
        SgwsNodeLevelLoadControlInformationInDeleteSessionResponse groupedIeInstance =
        dynamic_cast<
         SgwsNodeLevelLoadControlInformationInDeleteSessionResponse&>(loadControlInformation.getGroupedIe(msgType, 2));
        rc = groupedIeInstance.encodeSgwsNodeLevelLoadControlInformationInDeleteSessionResponse(buffer, data.sgwsNodeLevelLoadControlInformation);
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
        PgwsOverloadControlInformationInDeleteSessionResponse groupedIeInstance =
        dynamic_cast<
         PgwsOverloadControlInformationInDeleteSessionResponse&>(overloadControlInformation.getGroupedIe(msgType, 0));
        rc = groupedIeInstance.encodePgwsOverloadControlInformationInDeleteSessionResponse(buffer, data.pgwsOverloadControlInformation);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: pgwsOverloadControlInformation\n");
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
        SgwsOverloadControlInformationInDeleteSessionResponse groupedIeInstance =
        dynamic_cast<
         SgwsOverloadControlInformationInDeleteSessionResponse&>(overloadControlInformation.getGroupedIe(msgType, 1));
        rc = groupedIeInstance.encodeSgwsOverloadControlInformationInDeleteSessionResponse(buffer, data.sgwsOverloadControlInformation);
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
            errorStream.add((char *)"Failed to encode IE: extendedProtocolConfigurationOptions\n");
            return false;
        }
    }
    return rc;

}

bool DeleteSessionResponseMsg::decodeDeleteSessionResponseMsg(MsgBuffer &buffer,
 DeleteSessionResponseMsgData 
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
                        errorStream.add((char *)"Failed to decode IE: protocolConfigurationOptions\n");
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
					PgwsNodeLevelLoadControlInformationInDeleteSessionResponse groupedIeInstance =
					dynamic_cast<
					PgwsNodeLevelLoadControlInformationInDeleteSessionResponse&>(ieObject.getGroupedIe(msgType, 0));
					rc = groupedIeInstance.decodePgwsNodeLevelLoadControlInformationInDeleteSessionResponse(buffer, data.pgwsNodeLevelLoadControlInformation, ieHeader.length);

                    data.pgwsNodeLevelLoadControlInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: pgwsNodeLevelLoadControlInformation\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 1)
                {
					PgwsApnLevelLoadControlInformationInDeleteSessionResponse groupedIeInstance =
					dynamic_cast<
					PgwsApnLevelLoadControlInformationInDeleteSessionResponse&>(ieObject.getGroupedIe(msgType, 1));
					rc = groupedIeInstance.decodePgwsApnLevelLoadControlInformationInDeleteSessionResponse(buffer, data.pgwsApnLevelLoadControlInformation, ieHeader.length);

                    data.pgwsApnLevelLoadControlInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: pgwsApnLevelLoadControlInformation\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 2)
                {
					SgwsNodeLevelLoadControlInformationInDeleteSessionResponse groupedIeInstance =
					dynamic_cast<
					SgwsNodeLevelLoadControlInformationInDeleteSessionResponse&>(ieObject.getGroupedIe(msgType, 2));
					rc = groupedIeInstance.decodeSgwsNodeLevelLoadControlInformationInDeleteSessionResponse(buffer, data.sgwsNodeLevelLoadControlInformation, ieHeader.length);

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
					PgwsOverloadControlInformationInDeleteSessionResponse groupedIeInstance =
					dynamic_cast<
					PgwsOverloadControlInformationInDeleteSessionResponse&>(ieObject.getGroupedIe(msgType, 0));
					rc = groupedIeInstance.decodePgwsOverloadControlInformationInDeleteSessionResponse(buffer, data.pgwsOverloadControlInformation, ieHeader.length);

                    data.pgwsOverloadControlInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: pgwsOverloadControlInformation\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 1)
                {
					SgwsOverloadControlInformationInDeleteSessionResponse groupedIeInstance =
					dynamic_cast<
					SgwsOverloadControlInformationInDeleteSessionResponse&>(ieObject.getGroupedIe(msgType, 1));
					rc = groupedIeInstance.decodeSgwsOverloadControlInformationInDeleteSessionResponse(buffer, data.sgwsOverloadControlInformation, ieHeader.length);

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
                        errorStream.add((char *)"Failed to decode IE: extendedProtocolConfigurationOptions\n");
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

void DeleteSessionResponseMsg::
displayDeleteSessionResponseMsgData_v(DeleteSessionResponseMsgData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"DeleteSessionResponseMsg:");
    stream.endOfLine();
    stream.incrIndent();
        
    
        stream.add((char *)"IE - cause:");
        stream.endOfLine();
        CauseIe cause=
        dynamic_cast<
        CauseIe&>(GtpV2IeFactory::getInstance().getIeObject(CauseIeType));
        cause.displayCauseIe_v(data.cause, stream);

    if (data.recoveryIePresent)
    {


        stream.add((char *)"IE - recovery:");
        stream.endOfLine();
        RecoveryIe recovery=
        dynamic_cast<
        RecoveryIe&>(GtpV2IeFactory::getInstance().getIeObject(RecoveryIeType));
        recovery.displayRecoveryIe_v(data.recovery, stream);

    }
    if (data.protocolConfigurationOptionsIePresent)
    {


        stream.add((char *)"IE - protocolConfigurationOptions:");
        stream.endOfLine();
        PcoIe pco=
        dynamic_cast<
        PcoIe&>(GtpV2IeFactory::getInstance().getIeObject(PcoIeType));
        pco.displayPcoIe_v(data.protocolConfigurationOptions, stream);

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
    if (data.pgwsNodeLevelLoadControlInformationIePresent)
    {


        stream.add((char *)"IE - pgwsNodeLevelLoadControlInformation:");
        stream.endOfLine();
        LoadControlInformationIe loadControlInformation=
        dynamic_cast<
        LoadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(LoadControlInformationIeType));
            PgwsNodeLevelLoadControlInformationInDeleteSessionResponse groupedIeInstance =
        dynamic_cast<
        PgwsNodeLevelLoadControlInformationInDeleteSessionResponse&>(loadControlInformation.getGroupedIe(msgType, 0));
        groupedIeInstance.displayPgwsNodeLevelLoadControlInformationInDeleteSessionResponseData_v(data.pgwsNodeLevelLoadControlInformation, stream);

    }
    if (data.pgwsApnLevelLoadControlInformationIePresent)
    {


        stream.add((char *)"IE - pgwsApnLevelLoadControlInformation:");
        stream.endOfLine();
        LoadControlInformationIe loadControlInformation=
        dynamic_cast<
        LoadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(LoadControlInformationIeType));
            PgwsApnLevelLoadControlInformationInDeleteSessionResponse groupedIeInstance =
        dynamic_cast<
        PgwsApnLevelLoadControlInformationInDeleteSessionResponse&>(loadControlInformation.getGroupedIe(msgType, 1));
        groupedIeInstance.displayPgwsApnLevelLoadControlInformationInDeleteSessionResponseData_v(data.pgwsApnLevelLoadControlInformation, stream);

    }
    if (data.sgwsNodeLevelLoadControlInformationIePresent)
    {


        stream.add((char *)"IE - sgwsNodeLevelLoadControlInformation:");
        stream.endOfLine();
        LoadControlInformationIe loadControlInformation=
        dynamic_cast<
        LoadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(LoadControlInformationIeType));
            SgwsNodeLevelLoadControlInformationInDeleteSessionResponse groupedIeInstance =
        dynamic_cast<
        SgwsNodeLevelLoadControlInformationInDeleteSessionResponse&>(loadControlInformation.getGroupedIe(msgType, 2));
        groupedIeInstance.displaySgwsNodeLevelLoadControlInformationInDeleteSessionResponseData_v(data.sgwsNodeLevelLoadControlInformation, stream);

    }
    if (data.pgwsOverloadControlInformationIePresent)
    {


        stream.add((char *)"IE - pgwsOverloadControlInformation:");
        stream.endOfLine();
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
            PgwsOverloadControlInformationInDeleteSessionResponse groupedIeInstance =
        dynamic_cast<
        PgwsOverloadControlInformationInDeleteSessionResponse&>(overloadControlInformation.getGroupedIe(msgType, 0));
        groupedIeInstance.displayPgwsOverloadControlInformationInDeleteSessionResponseData_v(data.pgwsOverloadControlInformation, stream);

    }
    if (data.sgwsOverloadControlInformationIePresent)
    {


        stream.add((char *)"IE - sgwsOverloadControlInformation:");
        stream.endOfLine();
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
            SgwsOverloadControlInformationInDeleteSessionResponse groupedIeInstance =
        dynamic_cast<
        SgwsOverloadControlInformationInDeleteSessionResponse&>(overloadControlInformation.getGroupedIe(msgType, 1));
        groupedIeInstance.displaySgwsOverloadControlInformationInDeleteSessionResponseData_v(data.sgwsOverloadControlInformation, stream);

    }
    if (data.extendedProtocolConfigurationOptionsIePresent)
    {


        stream.add((char *)"IE - extendedProtocolConfigurationOptions:");
        stream.endOfLine();
        EpcoIe epco=
        dynamic_cast<
        EpcoIe&>(GtpV2IeFactory::getInstance().getIeObject(EpcoIeType));
        epco.displayEpcoIe_v(data.extendedProtocolConfigurationOptions, stream);

    }

    stream.decrIndent();
    stream.decrIndent();
}


