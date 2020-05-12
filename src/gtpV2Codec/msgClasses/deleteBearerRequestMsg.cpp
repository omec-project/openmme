/*
 * deleteBearerRequestMsg.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */
#include "deleteBearerRequestMsg.h"
#include "../ieClasses/manual/gtpV2Ie.h"
#include "../ieClasses/gtpV2IeFactory.h"
#include "../ieClasses/ebiIe.h"
#include "../ieClasses/ebiIe.h"
#include "../ieClasses/bearerContextIe.h"
#include "../ieClasses/failedBearerContextsInDeleteBearerRequest.h"
#include "../ieClasses/ptiIe.h"
#include "../ieClasses/pcoIe.h"
#include "../ieClasses/fqCsidIe.h"
#include "../ieClasses/fqCsidIe.h"
#include "../ieClasses/causeIe.h"
#include "../ieClasses/indicationIe.h"
#include "../ieClasses/loadControlInformationIe.h"
#include "../ieClasses/pgwsNodeLevelLoadControlInformationInDeleteBearerRequest.h"
#include "../ieClasses/loadControlInformationIe.h"
#include "../ieClasses/pgwsApnLevelLoadControlInformationInDeleteBearerRequest.h"
#include "../ieClasses/loadControlInformationIe.h"
#include "../ieClasses/sgwsNodeLevelLoadControlInformationInDeleteBearerRequest.h"
#include "../ieClasses/overloadControlInformationIe.h"
#include "../ieClasses/pgwsOverloadControlInformationInDeleteBearerRequest.h"
#include "../ieClasses/overloadControlInformationIe.h"
#include "../ieClasses/sgwsOverloadControlInformationInDeleteBearerRequest.h"
#include "../ieClasses/fContainerIe.h"
#include "../ieClasses/epcoIe.h"

DeleteBearerRequestMsg::DeleteBearerRequestMsg()
{
    msgType = DeleteBearerRequestMsgType;

}

DeleteBearerRequestMsg::~DeleteBearerRequestMsg()
{

}

bool DeleteBearerRequestMsg::encodeDeleteBearerRequestMsg(MsgBuffer &buffer,
                        DeleteBearerRequestMsgData
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

    if (data.epsBearerIdsIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = EbiIeType;
        header.instance = 1;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        EbiIe ebi=
        dynamic_cast<
        EbiIe&>(GtpV2IeFactory::getInstance().getIeObject(EbiIeType));
        rc = ebi.encodeEbiIe(buffer, data.epsBearerIds);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: epsBearerIds\n");
            return false;
        }
    }

        // First validate if the applicatoin provided more than the expected cardinality
    if (data.failedBearerContextsCount > 11)
    {
        errorStream.add("Number of entries of failedBearerContexts exceeded\n");
        errorStream.add("Expected count: 11 Received count: ");
        errorStream.add("data.failedBearerContextsCount");
        errorStream.endOfLine();
        return false;
    }
    for (Uint8 i = 0; i < data.failedBearerContextsCount; i++)
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
        FailedBearerContextsInDeleteBearerRequest groupedIeInstance = dynamic_cast<FailedBearerContextsInDeleteBearerRequest&>(bearerContext.getGroupedIe(msgType, 0));
        rc = groupedIeInstance.encodeFailedBearerContextsInDeleteBearerRequest(buffer, data.failedBearerContexts[i]);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;

        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);
    }

    if (!(rc))
    { 
        errorStream.add("Failed to encode IE: failedBearerContexts\n");
        return false;
    }

    if (data.procedureTransactionIdIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = PtiIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        PtiIe pti=
        dynamic_cast<
        PtiIe&>(GtpV2IeFactory::getInstance().getIeObject(PtiIeType));
        rc = pti.encodePtiIe(buffer, data.procedureTransactionId);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add("Failed to encode IE: procedureTransactionId\n");
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
        PgwsNodeLevelLoadControlInformationInDeleteBearerRequest groupedIeInstance =
        dynamic_cast<
         PgwsNodeLevelLoadControlInformationInDeleteBearerRequest&>(loadControlInformation.getGroupedIe(msgType, 0));
        rc = groupedIeInstance.encodePgwsNodeLevelLoadControlInformationInDeleteBearerRequest(buffer, data.pgwsNodeLevelLoadControlInformation);
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
        PgwsApnLevelLoadControlInformationInDeleteBearerRequest groupedIeInstance =
        dynamic_cast<
         PgwsApnLevelLoadControlInformationInDeleteBearerRequest&>(loadControlInformation.getGroupedIe(msgType, 1));
        rc = groupedIeInstance.encodePgwsApnLevelLoadControlInformationInDeleteBearerRequest(buffer, data.pgwsApnLevelLoadControlInformation);
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
        SgwsNodeLevelLoadControlInformationInDeleteBearerRequest groupedIeInstance =
        dynamic_cast<
         SgwsNodeLevelLoadControlInformationInDeleteBearerRequest&>(loadControlInformation.getGroupedIe(msgType, 2));
        rc = groupedIeInstance.encodeSgwsNodeLevelLoadControlInformationInDeleteBearerRequest(buffer, data.sgwsNodeLevelLoadControlInformation);
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
        PgwsOverloadControlInformationInDeleteBearerRequest groupedIeInstance =
        dynamic_cast<
         PgwsOverloadControlInformationInDeleteBearerRequest&>(overloadControlInformation.getGroupedIe(msgType, 0));
        rc = groupedIeInstance.encodePgwsOverloadControlInformationInDeleteBearerRequest(buffer, data.pgwsOverloadControlInformation);
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
        SgwsOverloadControlInformationInDeleteBearerRequest groupedIeInstance =
        dynamic_cast<
         SgwsOverloadControlInformationInDeleteBearerRequest&>(overloadControlInformation.getGroupedIe(msgType, 1));
        rc = groupedIeInstance.encodeSgwsOverloadControlInformationInDeleteBearerRequest(buffer, data.sgwsOverloadControlInformation);
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

bool DeleteBearerRequestMsg::decodeDeleteBearerRequestMsg(MsgBuffer &buffer,
 DeleteBearerRequestMsgData 
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
                else if(ieHeader.instance == 1)
                {
					rc = ieObject.decodeEbiIe(buffer, data.epsBearerIds, ieHeader.length);

                    data.epsBearerIdsIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: epsBearerIds\n");
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
                    if (data.failedBearerContextsCount == 11)
                    {
                        errorStream.add("More than 11 instances of failedBearerContexts received\n");
                        return false;
                    }
                    FailedBearerContextsInDeleteBearerRequest groupedIeInstance =
                    dynamic_cast<
                    FailedBearerContextsInDeleteBearerRequest&>(ieObject.getGroupedIe(msgType, 0));
                    rc = groupedIeInstance.decodeFailedBearerContextsInDeleteBearerRequest(buffer,
                    data.failedBearerContexts[data.failedBearerContextsCount], ieHeader.length);
                    data.failedBearerContextsCount++; // TODO Count validation

                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: failedBearerContexts\n");
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
     
            case PtiIeType:
            {
                PtiIe ieObject =
                dynamic_cast<
                PtiIe&>(GtpV2IeFactory::getInstance().getIeObject(PtiIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodePtiIe(buffer, data.procedureTransactionId, ieHeader.length);

                    data.procedureTransactionIdIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: procedureTransactionId\n");
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
					PgwsNodeLevelLoadControlInformationInDeleteBearerRequest groupedIeInstance =
					dynamic_cast<
					PgwsNodeLevelLoadControlInformationInDeleteBearerRequest&>(ieObject.getGroupedIe(msgType, 0));
					rc = groupedIeInstance.decodePgwsNodeLevelLoadControlInformationInDeleteBearerRequest(buffer, data.pgwsNodeLevelLoadControlInformation, ieHeader.length);

                    data.pgwsNodeLevelLoadControlInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: pgwsNodeLevelLoadControlInformation\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 1)
                {
					PgwsApnLevelLoadControlInformationInDeleteBearerRequest groupedIeInstance =
					dynamic_cast<
					PgwsApnLevelLoadControlInformationInDeleteBearerRequest&>(ieObject.getGroupedIe(msgType, 1));
					rc = groupedIeInstance.decodePgwsApnLevelLoadControlInformationInDeleteBearerRequest(buffer, data.pgwsApnLevelLoadControlInformation, ieHeader.length);

                    data.pgwsApnLevelLoadControlInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: pgwsApnLevelLoadControlInformation\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 2)
                {
					SgwsNodeLevelLoadControlInformationInDeleteBearerRequest groupedIeInstance =
					dynamic_cast<
					SgwsNodeLevelLoadControlInformationInDeleteBearerRequest&>(ieObject.getGroupedIe(msgType, 2));
					rc = groupedIeInstance.decodeSgwsNodeLevelLoadControlInformationInDeleteBearerRequest(buffer, data.sgwsNodeLevelLoadControlInformation, ieHeader.length);

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
					PgwsOverloadControlInformationInDeleteBearerRequest groupedIeInstance =
					dynamic_cast<
					PgwsOverloadControlInformationInDeleteBearerRequest&>(ieObject.getGroupedIe(msgType, 0));
					rc = groupedIeInstance.decodePgwsOverloadControlInformationInDeleteBearerRequest(buffer, data.pgwsOverloadControlInformation, ieHeader.length);

                    data.pgwsOverloadControlInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: pgwsOverloadControlInformation\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 1)
                {
					SgwsOverloadControlInformationInDeleteBearerRequest groupedIeInstance =
					dynamic_cast<
					SgwsOverloadControlInformationInDeleteBearerRequest&>(ieObject.getGroupedIe(msgType, 1));
					rc = groupedIeInstance.decodeSgwsOverloadControlInformationInDeleteBearerRequest(buffer, data.sgwsOverloadControlInformation, ieHeader.length);

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

void DeleteBearerRequestMsg::
displayDeleteBearerRequestMsgData_v(DeleteBearerRequestMsgData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("DeleteBearerRequestMsg:");
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
    if (data.epsBearerIdsIePresent)
    {
        stream.add("IE - epsBearerIds:");
        stream.endOfLine();
        EbiIe ebi=
        dynamic_cast<
        EbiIe&>(GtpV2IeFactory::getInstance().getIeObject(EbiIeType));
        ebi.displayEbiIe_v(data.epsBearerIds, stream);

    }
    displayCount = data.failedBearerContextsCount;
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
        stream.add("IE -  failedBearerContexts:");
        stream.endOfLine();
        BearerContextIe bearerContext=
        dynamic_cast<
        BearerContextIe&>(GtpV2IeFactory::getInstance().getIeObject(BearerContextIeType));
        FailedBearerContextsInDeleteBearerRequest groupedIeInstance =
        dynamic_cast<
        FailedBearerContextsInDeleteBearerRequest&>(bearerContext.getGroupedIe(msgType, 0));
        groupedIeInstance.displayFailedBearerContextsInDeleteBearerRequestData_v(data.failedBearerContexts[i], stream);

    }
    if (data.procedureTransactionIdIePresent)
    {
        stream.add("IE - procedureTransactionId:");
        stream.endOfLine();
        PtiIe pti=
        dynamic_cast<
        PtiIe&>(GtpV2IeFactory::getInstance().getIeObject(PtiIeType));
        pti.displayPtiIe_v(data.procedureTransactionId, stream);

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
    if (data.causeIePresent)
    {
        stream.add("IE - cause:");
        stream.endOfLine();
        CauseIe cause=
        dynamic_cast<
        CauseIe&>(GtpV2IeFactory::getInstance().getIeObject(CauseIeType));
        cause.displayCauseIe_v(data.cause, stream);

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
    if (data.pgwsNodeLevelLoadControlInformationIePresent)
    {
        stream.add("IE - pgwsNodeLevelLoadControlInformation:");
        stream.endOfLine();
        LoadControlInformationIe loadControlInformation=
        dynamic_cast<
        LoadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(LoadControlInformationIeType));
            PgwsNodeLevelLoadControlInformationInDeleteBearerRequest groupedIeInstance =
        dynamic_cast<
        PgwsNodeLevelLoadControlInformationInDeleteBearerRequest&>(loadControlInformation.getGroupedIe(msgType, 0));
        groupedIeInstance.displayPgwsNodeLevelLoadControlInformationInDeleteBearerRequestData_v(data.pgwsNodeLevelLoadControlInformation, stream);

    }
    if (data.pgwsApnLevelLoadControlInformationIePresent)
    {
        stream.add("IE - pgwsApnLevelLoadControlInformation:");
        stream.endOfLine();
        LoadControlInformationIe loadControlInformation=
        dynamic_cast<
        LoadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(LoadControlInformationIeType));
            PgwsApnLevelLoadControlInformationInDeleteBearerRequest groupedIeInstance =
        dynamic_cast<
        PgwsApnLevelLoadControlInformationInDeleteBearerRequest&>(loadControlInformation.getGroupedIe(msgType, 1));
        groupedIeInstance.displayPgwsApnLevelLoadControlInformationInDeleteBearerRequestData_v(data.pgwsApnLevelLoadControlInformation, stream);

    }
    if (data.sgwsNodeLevelLoadControlInformationIePresent)
    {
        stream.add("IE - sgwsNodeLevelLoadControlInformation:");
        stream.endOfLine();
        LoadControlInformationIe loadControlInformation=
        dynamic_cast<
        LoadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(LoadControlInformationIeType));
            SgwsNodeLevelLoadControlInformationInDeleteBearerRequest groupedIeInstance =
        dynamic_cast<
        SgwsNodeLevelLoadControlInformationInDeleteBearerRequest&>(loadControlInformation.getGroupedIe(msgType, 2));
        groupedIeInstance.displaySgwsNodeLevelLoadControlInformationInDeleteBearerRequestData_v(data.sgwsNodeLevelLoadControlInformation, stream);

    }
    if (data.pgwsOverloadControlInformationIePresent)
    {
        stream.add("IE - pgwsOverloadControlInformation:");
        stream.endOfLine();
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
            PgwsOverloadControlInformationInDeleteBearerRequest groupedIeInstance =
        dynamic_cast<
        PgwsOverloadControlInformationInDeleteBearerRequest&>(overloadControlInformation.getGroupedIe(msgType, 0));
        groupedIeInstance.displayPgwsOverloadControlInformationInDeleteBearerRequestData_v(data.pgwsOverloadControlInformation, stream);

    }
    if (data.sgwsOverloadControlInformationIePresent)
    {
        stream.add("IE - sgwsOverloadControlInformation:");
        stream.endOfLine();
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
            SgwsOverloadControlInformationInDeleteBearerRequest groupedIeInstance =
        dynamic_cast<
        SgwsOverloadControlInformationInDeleteBearerRequest&>(overloadControlInformation.getGroupedIe(msgType, 1));
        groupedIeInstance.displaySgwsOverloadControlInformationInDeleteBearerRequestData_v(data.sgwsOverloadControlInformation, stream);

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


