/*
 * createBearerRequestMsg.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */
#include "createBearerRequestMsg.h"
#include "../ieClasses/manual/gtpV2Ie.h"
#include "../ieClasses/gtpV2IeFactory.h"
#include "../ieClasses/ptiIe.h"
#include "../ieClasses/ebiIe.h"
#include "../ieClasses/pcoIe.h"
#include "../ieClasses/bearerContextIe.h"
#include "../ieClasses/bearerContextsInCreateBearerRequest.h"
#include "../ieClasses/fqCsidIe.h"
#include "../ieClasses/fqCsidIe.h"
#include "../ieClasses/changeReportingActionIe.h"
#include "../ieClasses/csgInformationReportingActionIe.h"
#include "../ieClasses/henbInformationReportingIe.h"
#include "../ieClasses/presenceReportingAreaActionIe.h"
#include "../ieClasses/indicationIe.h"
#include "../ieClasses/loadControlInformationIe.h"
#include "../ieClasses/pgwsNodeLevelLoadControlInformationInCreateBearerRequest.h"
#include "../ieClasses/loadControlInformationIe.h"
#include "../ieClasses/pgwsApnLevelLoadControlInformationInCreateBearerRequest.h"
#include "../ieClasses/loadControlInformationIe.h"
#include "../ieClasses/sgwsNodeLevelLoadControlInformationInCreateBearerRequest.h"
#include "../ieClasses/overloadControlInformationIe.h"
#include "../ieClasses/pgwsOverloadControlInformationInCreateBearerRequest.h"
#include "../ieClasses/overloadControlInformationIe.h"
#include "../ieClasses/sgwsOverloadControlInformationInCreateBearerRequest.h"
#include "../ieClasses/fContainerIe.h"

CreateBearerRequestMsg::CreateBearerRequestMsg()
{
    msgType = CreateBearerRequestMsgType;
    Uint16 mandIe;
    mandIe = EbiIeType;
    mandIe = (mandIe << 8) | 0; // linkedEpsBearerId
    mandatoryIeSet.insert(mandIe);    mandIe = BearerContextIeType;
    mandIe = (mandIe << 8) | 0; // bearerContexts
    mandatoryIeSet.insert(mandIe);
}

CreateBearerRequestMsg::~CreateBearerRequestMsg()
{

}

bool CreateBearerRequestMsg::encodeCreateBearerRequestMsg(MsgBuffer &buffer,
                        CreateBearerRequestMsgData
							const &data)
{
    bool rc = false;
    GtpV2IeHeader header;
    Uint16 startIndex = 0;
    Uint16 endIndex = 0;
    Uint16 length = 0;

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
        PgwsNodeLevelLoadControlInformationInCreateBearerRequest groupedIeInstance =
        dynamic_cast<
         PgwsNodeLevelLoadControlInformationInCreateBearerRequest&>(loadControlInformation.getGroupedIe(msgType, 0));
        rc = groupedIeInstance.encodePgwsNodeLevelLoadControlInformationInCreateBearerRequest(buffer, data.pgwsNodeLevelLoadControlInformation);
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
        PgwsApnLevelLoadControlInformationInCreateBearerRequest groupedIeInstance =
        dynamic_cast<
         PgwsApnLevelLoadControlInformationInCreateBearerRequest&>(loadControlInformation.getGroupedIe(msgType, 1));
        rc = groupedIeInstance.encodePgwsApnLevelLoadControlInformationInCreateBearerRequest(buffer, data.pgwsApnLevelLoadControlInformation);
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
        SgwsNodeLevelLoadControlInformationInCreateBearerRequest groupedIeInstance =
        dynamic_cast<
         SgwsNodeLevelLoadControlInformationInCreateBearerRequest&>(loadControlInformation.getGroupedIe(msgType, 2));
        rc = groupedIeInstance.encodeSgwsNodeLevelLoadControlInformationInCreateBearerRequest(buffer, data.sgwsNodeLevelLoadControlInformation);
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
        PgwsOverloadControlInformationInCreateBearerRequest groupedIeInstance =
        dynamic_cast<
         PgwsOverloadControlInformationInCreateBearerRequest&>(overloadControlInformation.getGroupedIe(msgType, 0));
        rc = groupedIeInstance.encodePgwsOverloadControlInformationInCreateBearerRequest(buffer, data.pgwsOverloadControlInformation);
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
        SgwsOverloadControlInformationInCreateBearerRequest groupedIeInstance =
        dynamic_cast<
         SgwsOverloadControlInformationInCreateBearerRequest&>(overloadControlInformation.getGroupedIe(msgType, 1));
        rc = groupedIeInstance.encodeSgwsOverloadControlInformationInCreateBearerRequest(buffer, data.sgwsOverloadControlInformation);
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
    return rc;

}

bool CreateBearerRequestMsg::decodeCreateBearerRequestMsg(MsgBuffer &buffer,
 CreateBearerRequestMsgData 
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
     
            case EbiIeType:
            {
                EbiIe ieObject =
                dynamic_cast<
                EbiIe&>(GtpV2IeFactory::getInstance().getIeObject(EbiIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeEbiIe(buffer, data.linkedEpsBearerId, ieHeader.length);

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
                    if (data.bearerContextsCount == 11)
                    {
                        errorStream.add("More than 11 instances of bearerContexts received\n");
                        return false;
                    }
                    BearerContextsInCreateBearerRequest groupedIeInstance =
                    dynamic_cast<
                    BearerContextsInCreateBearerRequest&>(ieObject.getGroupedIe(msgType, 0));
                    rc = groupedIeInstance.decodeBearerContextsInCreateBearerRequest(buffer,
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
					PgwsNodeLevelLoadControlInformationInCreateBearerRequest groupedIeInstance =
					dynamic_cast<
					PgwsNodeLevelLoadControlInformationInCreateBearerRequest&>(ieObject.getGroupedIe(msgType, 0));
					rc = groupedIeInstance.decodePgwsNodeLevelLoadControlInformationInCreateBearerRequest(buffer, data.pgwsNodeLevelLoadControlInformation, ieHeader.length);

                    data.pgwsNodeLevelLoadControlInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: pgwsNodeLevelLoadControlInformation\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 1)
                {
					PgwsApnLevelLoadControlInformationInCreateBearerRequest groupedIeInstance =
					dynamic_cast<
					PgwsApnLevelLoadControlInformationInCreateBearerRequest&>(ieObject.getGroupedIe(msgType, 1));
					rc = groupedIeInstance.decodePgwsApnLevelLoadControlInformationInCreateBearerRequest(buffer, data.pgwsApnLevelLoadControlInformation, ieHeader.length);

                    data.pgwsApnLevelLoadControlInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: pgwsApnLevelLoadControlInformation\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 2)
                {
					SgwsNodeLevelLoadControlInformationInCreateBearerRequest groupedIeInstance =
					dynamic_cast<
					SgwsNodeLevelLoadControlInformationInCreateBearerRequest&>(ieObject.getGroupedIe(msgType, 2));
					rc = groupedIeInstance.decodeSgwsNodeLevelLoadControlInformationInCreateBearerRequest(buffer, data.sgwsNodeLevelLoadControlInformation, ieHeader.length);

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
					PgwsOverloadControlInformationInCreateBearerRequest groupedIeInstance =
					dynamic_cast<
					PgwsOverloadControlInformationInCreateBearerRequest&>(ieObject.getGroupedIe(msgType, 0));
					rc = groupedIeInstance.decodePgwsOverloadControlInformationInCreateBearerRequest(buffer, data.pgwsOverloadControlInformation, ieHeader.length);

                    data.pgwsOverloadControlInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: pgwsOverloadControlInformation\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 1)
                {
					SgwsOverloadControlInformationInCreateBearerRequest groupedIeInstance =
					dynamic_cast<
					SgwsOverloadControlInformationInCreateBearerRequest&>(ieObject.getGroupedIe(msgType, 1));
					rc = groupedIeInstance.decodeSgwsOverloadControlInformationInCreateBearerRequest(buffer, data.sgwsOverloadControlInformation, ieHeader.length);

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

void CreateBearerRequestMsg::
displayCreateBearerRequestMsgData_v(CreateBearerRequestMsgData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("CreateBearerRequestMsg:");
    stream.endOfLine();
    Uint8 displayCount;
    stream.incrIndent();
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
    if (data.hNbInformationReportingIePresent)
    {
        stream.add("IE - hNbInformationReporting:");
        stream.endOfLine();
        HenbInformationReportingIe henbInformationReporting=
        dynamic_cast<
        HenbInformationReportingIe&>(GtpV2IeFactory::getInstance().getIeObject(HenbInformationReportingIeType));
        henbInformationReporting.displayHenbInformationReportingIe_v(data.hNbInformationReporting, stream);

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
            PgwsNodeLevelLoadControlInformationInCreateBearerRequest groupedIeInstance =
        dynamic_cast<
        PgwsNodeLevelLoadControlInformationInCreateBearerRequest&>(loadControlInformation.getGroupedIe(msgType, 0));
        groupedIeInstance.displayPgwsNodeLevelLoadControlInformationInCreateBearerRequestData_v(data.pgwsNodeLevelLoadControlInformation, stream);

    }
    if (data.pgwsApnLevelLoadControlInformationIePresent)
    {
        stream.add("IE - pgwsApnLevelLoadControlInformation:");
        stream.endOfLine();
        LoadControlInformationIe loadControlInformation=
        dynamic_cast<
        LoadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(LoadControlInformationIeType));
            PgwsApnLevelLoadControlInformationInCreateBearerRequest groupedIeInstance =
        dynamic_cast<
        PgwsApnLevelLoadControlInformationInCreateBearerRequest&>(loadControlInformation.getGroupedIe(msgType, 1));
        groupedIeInstance.displayPgwsApnLevelLoadControlInformationInCreateBearerRequestData_v(data.pgwsApnLevelLoadControlInformation, stream);

    }
    if (data.sgwsNodeLevelLoadControlInformationIePresent)
    {
        stream.add("IE - sgwsNodeLevelLoadControlInformation:");
        stream.endOfLine();
        LoadControlInformationIe loadControlInformation=
        dynamic_cast<
        LoadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(LoadControlInformationIeType));
            SgwsNodeLevelLoadControlInformationInCreateBearerRequest groupedIeInstance =
        dynamic_cast<
        SgwsNodeLevelLoadControlInformationInCreateBearerRequest&>(loadControlInformation.getGroupedIe(msgType, 2));
        groupedIeInstance.displaySgwsNodeLevelLoadControlInformationInCreateBearerRequestData_v(data.sgwsNodeLevelLoadControlInformation, stream);

    }
    if (data.pgwsOverloadControlInformationIePresent)
    {
        stream.add("IE - pgwsOverloadControlInformation:");
        stream.endOfLine();
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
            PgwsOverloadControlInformationInCreateBearerRequest groupedIeInstance =
        dynamic_cast<
        PgwsOverloadControlInformationInCreateBearerRequest&>(overloadControlInformation.getGroupedIe(msgType, 0));
        groupedIeInstance.displayPgwsOverloadControlInformationInCreateBearerRequestData_v(data.pgwsOverloadControlInformation, stream);

    }
    if (data.sgwsOverloadControlInformationIePresent)
    {
        stream.add("IE - sgwsOverloadControlInformation:");
        stream.endOfLine();
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
            SgwsOverloadControlInformationInCreateBearerRequest groupedIeInstance =
        dynamic_cast<
        SgwsOverloadControlInformationInCreateBearerRequest&>(overloadControlInformation.getGroupedIe(msgType, 1));
        groupedIeInstance.displaySgwsOverloadControlInformationInCreateBearerRequestData_v(data.sgwsOverloadControlInformation, stream);

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
    stream.decrIndent();
    stream.decrIndent();
}


