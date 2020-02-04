/*
 * bearerContextsCreatedInCreateSessionResponse.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */
#include "bearerContextsCreatedInCreateSessionResponse.h"
#include "manual/gtpV2Ie.h"
#include "gtpV2IeFactory.h"
#include "ebiIe.h"
#include "causeIe.h"
#include "fTeidIe.h"
#include "fTeidIe.h"
#include "fTeidIe.h"
#include "fTeidIe.h"
#include "fTeidIe.h"
#include "fTeidIe.h"
#include "bearerQosIe.h"
#include "chargingIdIe.h"
#include "bearerFlagsIe.h"
#include "fTeidIe.h"

BearerContextsCreatedInCreateSessionResponse::
BearerContextsCreatedInCreateSessionResponse()
{
    Uint16 mandIe;
    mandIe = EbiIeType;
    mandIe = (mandIe << 8) | 0; // epsBearerId
    mandatoryIeSet.insert(mandIe);
    mandIe = CauseIeType;
    mandIe = (mandIe << 8) | 0; // cause
    mandatoryIeSet.insert(mandIe);

}

BearerContextsCreatedInCreateSessionResponse::
~BearerContextsCreatedInCreateSessionResponse()
{

}
bool BearerContextsCreatedInCreateSessionResponse::
encodeBearerContextsCreatedInCreateSessionResponse(MsgBuffer &buffer,
                         BearerContextsCreatedInCreateSessionResponseData
                          const &data)
{
    bool rc = false;
    GtpV2IeHeader header;
    Uint16 startIndex = 0;
    Uint16 endIndex = 0;
    Uint16 length = 0;


    
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

    if (data.s1USgwFTeidIePresent)
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
        rc = fTeid.encodeFTeidIe(buffer, data.s1USgwFTeid);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        {
          errorStream.add("Failed to encode IE: s1USgwFTeid\n");
          return false;
        }
    }

    if (data.s4USgwFTeidIePresent)
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
        rc = fTeid.encodeFTeidIe(buffer, data.s4USgwFTeid);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        {
          errorStream.add("Failed to encode IE: s4USgwFTeid\n");
          return false;
        }
    }

    if (data.s5S8UPgwFTeidIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = FTeidIeType;
        header.instance = 2;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        rc = fTeid.encodeFTeidIe(buffer, data.s5S8UPgwFTeid);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        {
          errorStream.add("Failed to encode IE: s5S8UPgwFTeid\n");
          return false;
        }
    }

    if (data.s12SgwFTeidIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = FTeidIeType;
        header.instance = 3;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        rc = fTeid.encodeFTeidIe(buffer, data.s12SgwFTeid);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        {
          errorStream.add("Failed to encode IE: s12SgwFTeid\n");
          return false;
        }
    }

    if (data.s2bUPgwFTeidIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = FTeidIeType;
        header.instance = 4;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        rc = fTeid.encodeFTeidIe(buffer, data.s2bUPgwFTeid);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        {
          errorStream.add("Failed to encode IE: s2bUPgwFTeid\n");
          return false;
        }
    }

    if (data.s2aUPgwFTeidIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = FTeidIeType;
        header.instance = 5;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        rc = fTeid.encodeFTeidIe(buffer, data.s2aUPgwFTeid);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        {
          errorStream.add("Failed to encode IE: s2aUPgwFTeid\n");
          return false;
        }
    }

    if (data.bearerLevelQosIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = BearerQosIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        BearerQosIe bearerQos=
        dynamic_cast<
        BearerQosIe&>(GtpV2IeFactory::getInstance().getIeObject(BearerQosIeType));
        rc = bearerQos.encodeBearerQosIe(buffer, data.bearerLevelQos);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        {
          errorStream.add("Failed to encode IE: bearerLevelQos\n");
          return false;
        }
    }

    if (data.chargingIdIePresent)
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
        rc = chargingId.encodeChargingIdIe(buffer, data.chargingId);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        {
          errorStream.add("Failed to encode IE: chargingId\n");
          return false;
        }
    }

    if (data.bearerFlagsIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = BearerFlagsIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        BearerFlagsIe bearerFlags=
        dynamic_cast<
        BearerFlagsIe&>(GtpV2IeFactory::getInstance().getIeObject(BearerFlagsIeType));
        rc = bearerFlags.encodeBearerFlagsIe(buffer, data.bearerFlags);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        {
          errorStream.add("Failed to encode IE: bearerFlags\n");
          return false;
        }
    }

    if (data.s11USgwFTeidIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = FTeidIeType;
        header.instance = 6;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        rc = fTeid.encodeFTeidIe(buffer, data.s11USgwFTeid);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        {
          errorStream.add("Failed to encode IE: s11USgwFTeid\n");
          return false;
        }
    }
    return rc;
}

bool BearerContextsCreatedInCreateSessionResponse::
decodeBearerContextsCreatedInCreateSessionResponse(MsgBuffer &buffer,
                         BearerContextsCreatedInCreateSessionResponseData 
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
                EbiIe&>(GtpV2IeFactory::getInstance().
                         getIeObject(EbiIeType));


                if(ieHeader.instance == 0)
                {

                					rc = ieObject.decodeEbiIe(buffer, data.epsBearerId, ieHeader.length);

                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: epsBearerId\n");
                        return false;
                    }
                    Uint16 mandIe = EbiIeType;
                    mandIe = (mandIe << 8) | 0;
                    mandatoryIeLocalList.erase(mandIe);
                }
                else
                {
                    // Unknown IE instance print error TODO
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
                CauseIe&>(GtpV2IeFactory::getInstance().
                         getIeObject(CauseIeType));


                if(ieHeader.instance == 0)
                {

                					rc = ieObject.decodeCauseIe(buffer, data.cause, ieHeader.length);

                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: cause\n");
                        return false;
                    }
                    Uint16 mandIe = CauseIeType;
                    mandIe = (mandIe << 8) | 0;
                    mandatoryIeLocalList.erase(mandIe);
                }
                else
                {
                    // Unknown IE instance print error TODO
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
                FTeidIe&>(GtpV2IeFactory::getInstance().
                         getIeObject(FTeidIeType));


                if(ieHeader.instance == 0)
                {

                					rc = ieObject.decodeFTeidIe(buffer, data.s1USgwFTeid, ieHeader.length);

                    data.s1USgwFTeidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: s1USgwFTeid\n");
                        return false;
                    }
                }

                else if(ieHeader.instance == 1)
                {

                					rc = ieObject.decodeFTeidIe(buffer, data.s4USgwFTeid, ieHeader.length);

                    data.s4USgwFTeidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: s4USgwFTeid\n");
                        return false;
                    }
                }

                else if(ieHeader.instance == 2)
                {

                					rc = ieObject.decodeFTeidIe(buffer, data.s5S8UPgwFTeid, ieHeader.length);

                    data.s5S8UPgwFTeidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: s5S8UPgwFTeid\n");
                        return false;
                    }
                }

                else if(ieHeader.instance == 3)
                {

                					rc = ieObject.decodeFTeidIe(buffer, data.s12SgwFTeid, ieHeader.length);

                    data.s12SgwFTeidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: s12SgwFTeid\n");
                        return false;
                    }
                }

                else if(ieHeader.instance == 4)
                {

                					rc = ieObject.decodeFTeidIe(buffer, data.s2bUPgwFTeid, ieHeader.length);

                    data.s2bUPgwFTeidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: s2bUPgwFTeid\n");
                        return false;
                    }
                }

                else if(ieHeader.instance == 5)
                {

                					rc = ieObject.decodeFTeidIe(buffer, data.s2aUPgwFTeid, ieHeader.length);

                    data.s2aUPgwFTeidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: s2aUPgwFTeid\n");
                        return false;
                    }
                }

                else if(ieHeader.instance == 6)
                {

                					rc = ieObject.decodeFTeidIe(buffer, data.s11USgwFTeid, ieHeader.length);

                    data.s11USgwFTeidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: s11USgwFTeid\n");
                        return false;
                    }
                }
                else
                {
                    // Unknown IE instance print error TODO
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
            case BearerQosIeType:
            {
                BearerQosIe ieObject =
                dynamic_cast<
                BearerQosIe&>(GtpV2IeFactory::getInstance().
                         getIeObject(BearerQosIeType));


                if(ieHeader.instance == 0)
                {

                					rc = ieObject.decodeBearerQosIe(buffer, data.bearerLevelQos, ieHeader.length);

                    data.bearerLevelQosIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: bearerLevelQos\n");
                        return false;
                    }
                }
                else
                {
                    // Unknown IE instance print error TODO
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
                ChargingIdIe&>(GtpV2IeFactory::getInstance().
                         getIeObject(ChargingIdIeType));


                if(ieHeader.instance == 0)
                {

                					rc = ieObject.decodeChargingIdIe(buffer, data.chargingId, ieHeader.length);

                    data.chargingIdIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: chargingId\n");
                        return false;
                    }
                }
                else
                {
                    // Unknown IE instance print error TODO
                    errorStream.add("Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
            case BearerFlagsIeType:
            {
                BearerFlagsIe ieObject =
                dynamic_cast<
                BearerFlagsIe&>(GtpV2IeFactory::getInstance().
                         getIeObject(BearerFlagsIeType));


                if(ieHeader.instance == 0)
                {

                					rc = ieObject.decodeBearerFlagsIe(buffer, data.bearerFlags, ieHeader.length);

                    data.bearerFlagsIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: bearerFlags\n");
                        return false;
                    }
                }
                else
                {
                    // Unknown IE instance print error TODO
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
    if (!mandatoryIeLocalList.empty())
    {
        // some mandatory IEs are missing
        errorStream.add("Missing Mandatory IEs:");
        errorStream.endOfLine();
        while (!mandatoryIeLocalList.empty())
        {
            Uint16 missingMandIe = *mandatoryIeLocalList.begin ();
            mandatoryIeLocalList.erase (mandatoryIeLocalList.begin ());
            Uint16 missingInstance = missingMandIe & 0x00FF;
            Uint16 missingIeType = (missingMandIe >> 8);
            errorStream.add ("Missing Ie type: ");
            errorStream.add (missingIeType);
            errorStream.add ("  Instance: ");
            errorStream.add (missingInstance);
            errorStream.endOfLine();
        }
        rc = false;
    
    }
    return rc; 
}

void BearerContextsCreatedInCreateSessionResponse::
displayBearerContextsCreatedInCreateSessionResponseData_v
(BearerContextsCreatedInCreateSessionResponseData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("BearerContextsCreatedInCreateSessionResponse:");
    stream.endOfLine();
    stream.incrIndent();



    if (data.s1USgwFTeidIePresent)
    {

        stream.add("s1USgwFTeid:");
        stream.endOfLine();
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        fTeid.displayFTeidIe_v(data.s1USgwFTeid, stream);

    }

    if (data.s4USgwFTeidIePresent)
    {

        stream.add("s4USgwFTeid:");
        stream.endOfLine();
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        fTeid.displayFTeidIe_v(data.s4USgwFTeid, stream);

    }

    if (data.s5S8UPgwFTeidIePresent)
    {

        stream.add("s5S8UPgwFTeid:");
        stream.endOfLine();
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        fTeid.displayFTeidIe_v(data.s5S8UPgwFTeid, stream);

    }

    if (data.s12SgwFTeidIePresent)
    {

        stream.add("s12SgwFTeid:");
        stream.endOfLine();
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        fTeid.displayFTeidIe_v(data.s12SgwFTeid, stream);

    }

    if (data.s2bUPgwFTeidIePresent)
    {

        stream.add("s2bUPgwFTeid:");
        stream.endOfLine();
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        fTeid.displayFTeidIe_v(data.s2bUPgwFTeid, stream);

    }

    if (data.s2aUPgwFTeidIePresent)
    {

        stream.add("s2aUPgwFTeid:");
        stream.endOfLine();
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        fTeid.displayFTeidIe_v(data.s2aUPgwFTeid, stream);

    }

    if (data.bearerLevelQosIePresent)
    {

        stream.add("bearerLevelQos:");
        stream.endOfLine();
        BearerQosIe bearerQos=
        dynamic_cast<
        BearerQosIe&>(GtpV2IeFactory::getInstance().getIeObject(BearerQosIeType));
        bearerQos.displayBearerQosIe_v(data.bearerLevelQos, stream);

    }

    if (data.chargingIdIePresent)
    {

        stream.add("chargingId:");
        stream.endOfLine();
        ChargingIdIe chargingId=
        dynamic_cast<
        ChargingIdIe&>(GtpV2IeFactory::getInstance().getIeObject(ChargingIdIeType));
        chargingId.displayChargingIdIe_v(data.chargingId, stream);

    }

    if (data.bearerFlagsIePresent)
    {

        stream.add("bearerFlags:");
        stream.endOfLine();
        BearerFlagsIe bearerFlags=
        dynamic_cast<
        BearerFlagsIe&>(GtpV2IeFactory::getInstance().getIeObject(BearerFlagsIeType));
        bearerFlags.displayBearerFlagsIe_v(data.bearerFlags, stream);

    }

    if (data.s11USgwFTeidIePresent)
    {

        stream.add("s11USgwFTeid:");
        stream.endOfLine();
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        fTeid.displayFTeidIe_v(data.s11USgwFTeid, stream);

    }

    stream.decrIndent();
    stream.decrIndent();
}





