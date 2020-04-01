/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#include "bearerContextsToBeModifiedInModifyBearerRequest.h"
#include "manual/gtpV2Ie.h"
#include "gtpV2IeFactory.h"
#include "ebiIe.h"
#include "fTeidIe.h"
#include "fTeidIe.h"
#include "fTeidIe.h"
#include "fTeidIe.h"
#include "fTeidIe.h"

BearerContextsToBeModifiedInModifyBearerRequest::
BearerContextsToBeModifiedInModifyBearerRequest()
{
    Uint16 mandIe;
    mandIe = EbiIeType;
    mandIe = (mandIe << 8) | 0; // epsBearerId
    mandatoryIeSet.insert(mandIe);

}

BearerContextsToBeModifiedInModifyBearerRequest::
~BearerContextsToBeModifiedInModifyBearerRequest()
{

}
bool BearerContextsToBeModifiedInModifyBearerRequest::
encodeBearerContextsToBeModifiedInModifyBearerRequest(MsgBuffer &buffer,
                         BearerContextsToBeModifiedInModifyBearerRequestData
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
        errorStream.add((char *)"Failed to encode IE: epsBearerId\n");
        return false;
    }

    if (data.s1EnodebFTeidIePresent)
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
        rc = fTeid.encodeFTeidIe(buffer, data.s1EnodebFTeid);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        {
          errorStream.add((char *)"Failed to encode IE: s1EnodebFTeid\n");
          return false;
        }
    }

    if (data.s58USgwFTeidIePresent)
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
        rc = fTeid.encodeFTeidIe(buffer, data.s58USgwFTeid);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        {
          errorStream.add((char *)"Failed to encode IE: s58USgwFTeid\n");
          return false;
        }
    }

    if (data.s12RncFTeidIePresent)
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
        rc = fTeid.encodeFTeidIe(buffer, data.s12RncFTeid);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        {
          errorStream.add((char *)"Failed to encode IE: s12RncFTeid\n");
          return false;
        }
    }

    if (data.s4USgsnFTeidIePresent)
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
        rc = fTeid.encodeFTeidIe(buffer, data.s4USgsnFTeid);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        {
          errorStream.add((char *)"Failed to encode IE: s4USgsnFTeid\n");
          return false;
        }
    }

    if (data.s11UMmeFTeidIePresent)
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
        rc = fTeid.encodeFTeidIe(buffer, data.s11UMmeFTeid);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        {
          errorStream.add((char *)"Failed to encode IE: s11UMmeFTeid\n");
          return false;
        }
    }
    return rc;
}

bool BearerContextsToBeModifiedInModifyBearerRequest::
decodeBearerContextsToBeModifiedInModifyBearerRequest(MsgBuffer &buffer,
                         BearerContextsToBeModifiedInModifyBearerRequestData 
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
                        errorStream.add((char *)"Failed to decode IE: epsBearerId\n");
                        return false;
                    }
                    Uint16 mandIe = EbiIeType;
                    mandIe = (mandIe << 8) | 0;
                    mandatoryIeLocalList.erase(mandIe);
                }
                else
                {
                    // Unknown IE instance print error TODO
                    errorStream.add((char *)"Unknown IE Type: ");
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

                					rc = ieObject.decodeFTeidIe(buffer, data.s1EnodebFTeid, ieHeader.length);

                    data.s1EnodebFTeidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: s1EnodebFTeid\n");
                        return false;
                    }
                }

                else if(ieHeader.instance == 1)
                {

                					rc = ieObject.decodeFTeidIe(buffer, data.s58USgwFTeid, ieHeader.length);

                    data.s58USgwFTeidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: s58USgwFTeid\n");
                        return false;
                    }
                }

                else if(ieHeader.instance == 2)
                {

                					rc = ieObject.decodeFTeidIe(buffer, data.s12RncFTeid, ieHeader.length);

                    data.s12RncFTeidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: s12RncFTeid\n");
                        return false;
                    }
                }

                else if(ieHeader.instance == 3)
                {

                					rc = ieObject.decodeFTeidIe(buffer, data.s4USgsnFTeid, ieHeader.length);

                    data.s4USgsnFTeidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: s4USgsnFTeid\n");
                        return false;
                    }
                }

                else if(ieHeader.instance == 4)
                {

                					rc = ieObject.decodeFTeidIe(buffer, data.s11UMmeFTeid, ieHeader.length);

                    data.s11UMmeFTeidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: s11UMmeFTeid\n");
                        return false;
                    }
                }
                else
                {
                    // Unknown IE instance print error TODO
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
    if (!mandatoryIeLocalList.empty())
    {
        // some mandatory IEs are missing
        errorStream.add((char *)"Missing Mandatory IEs:");
        errorStream.endOfLine();
        while (!mandatoryIeLocalList.empty())
        {
            Uint16 missingMandIe = *mandatoryIeLocalList.begin ();
            mandatoryIeLocalList.erase (mandatoryIeLocalList.begin ());
            Uint16 missingInstance = missingMandIe & 0x00FF;
            Uint16 missingIeType = (missingMandIe >> 8);
            errorStream.add ((char *)"Missing Ie type: ");
            errorStream.add (missingIeType);
            errorStream.add ((char *)"  Instance: ");
            errorStream.add (missingInstance);
            errorStream.endOfLine();
        }
        rc = false;
    
    }
    return rc; 
}

void BearerContextsToBeModifiedInModifyBearerRequest::
displayBearerContextsToBeModifiedInModifyBearerRequestData_v
(BearerContextsToBeModifiedInModifyBearerRequestData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"BearerContextsToBeModifiedInModifyBearerRequest:");
    stream.endOfLine();
    stream.incrIndent();


    if (data.s1EnodebFTeidIePresent)
    {

        stream.add((char *)"s1EnodebFTeid:");
        stream.endOfLine();
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        fTeid.displayFTeidIe_v(data.s1EnodebFTeid, stream);

    }

    if (data.s58USgwFTeidIePresent)
    {

        stream.add((char *)"s58USgwFTeid:");
        stream.endOfLine();
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        fTeid.displayFTeidIe_v(data.s58USgwFTeid, stream);

    }

    if (data.s12RncFTeidIePresent)
    {

        stream.add((char *)"s12RncFTeid:");
        stream.endOfLine();
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        fTeid.displayFTeidIe_v(data.s12RncFTeid, stream);

    }

    if (data.s4USgsnFTeidIePresent)
    {

        stream.add((char *)"s4USgsnFTeid:");
        stream.endOfLine();
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        fTeid.displayFTeidIe_v(data.s4USgsnFTeid, stream);

    }

    if (data.s11UMmeFTeidIePresent)
    {

        stream.add((char *)"s11UMmeFTeid:");
        stream.endOfLine();
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        fTeid.displayFTeidIe_v(data.s11UMmeFTeid, stream);

    }

    stream.decrIndent();
    stream.decrIndent();
}





