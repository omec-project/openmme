/*
* Copyright (c) 2019 Infosys Limited
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

#include "bearerContextsToBeCreatedInCreateSessionRequest.h"
#include "manual/gtpV2Ie.h"
#include "gtpV2IeFactory.h"
#include "ebiIe.h"
#include "bearerTftIe.h"
#include "fTeidIe.h"
#include "fTeidIe.h"
#include "fTeidIe.h"
#include "fTeidIe.h"
#include "fTeidIe.h"
#include "fTeidIe.h"
#include "fTeidIe.h"
#include "bearerQosIe.h"
#include "fTeidIe.h"

BearerContextsToBeCreatedInCreateSessionRequest::
BearerContextsToBeCreatedInCreateSessionRequest()
{
    Uint16 mandIe;
    mandIe = EbiIeType;
    mandIe = (mandIe << 8) | 0; // epsBearerId
    mandatoryIeSet.insert(mandIe);
    mandIe = BearerQosIeType;
    mandIe = (mandIe << 8) | 0; // bearerLevelQos
    mandatoryIeSet.insert(mandIe);

}

BearerContextsToBeCreatedInCreateSessionRequest::
~BearerContextsToBeCreatedInCreateSessionRequest()
{

}
bool BearerContextsToBeCreatedInCreateSessionRequest::
encodeBearerContextsToBeCreatedInCreateSessionRequest(MsgBuffer &buffer,
                         BearerContextsToBeCreatedInCreateSessionRequestData
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

    if (data.tftIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = BearerTftIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        BearerTftIe bearerTft=
        dynamic_cast<
        BearerTftIe&>(GtpV2IeFactory::getInstance().getIeObject(BearerTftIeType));
        rc = bearerTft.encodeBearerTftIe(buffer, data.tft);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        {
          errorStream.add((char *)"Failed to encode IE: tft\n");
          return false;
        }
    }

    if (data.s1UEnodebFTeidIePresent)
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
        rc = fTeid.encodeFTeidIe(buffer, data.s1UEnodebFTeid);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        {
          errorStream.add((char *)"Failed to encode IE: s1UEnodebFTeid\n");
          return false;
        }
    }

    if (data.s4USgsnFTeidIePresent)
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

    if (data.s5S8USgwFTeidIePresent)
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
        rc = fTeid.encodeFTeidIe(buffer, data.s5S8USgwFTeid);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        {
          errorStream.add((char *)"Failed to encode IE: s5S8USgwFTeid\n");
          return false;
        }
    }

    if (data.s5S8UPgwFTeidIePresent)
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
        rc = fTeid.encodeFTeidIe(buffer, data.s5S8UPgwFTeid);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        {
          errorStream.add((char *)"Failed to encode IE: s5S8UPgwFTeid\n");
          return false;
        }
    }

    if (data.s12RncFTeidIePresent)
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

    if (data.s2bUEpdgFTeidIePresent)
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
        rc = fTeid.encodeFTeidIe(buffer, data.s2bUEpdgFTeid);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        {
          errorStream.add((char *)"Failed to encode IE: s2bUEpdgFTeid\n");
          return false;
        }
    }

    if (data.s2aUTwanFTeidIePresent)
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
        rc = fTeid.encodeFTeidIe(buffer, data.s2aUTwanFTeid);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        {
          errorStream.add((char *)"Failed to encode IE: s2aUTwanFTeid\n");
          return false;
        }
    }


    
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
        errorStream.add((char *)"Failed to encode IE: bearerLevelQos\n");
        return false;
    }

    if (data.s11UMmeFTeidIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = FTeidIeType;
        header.instance = 7;
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

bool BearerContextsToBeCreatedInCreateSessionRequest::
decodeBearerContextsToBeCreatedInCreateSessionRequest(MsgBuffer &buffer,
                         BearerContextsToBeCreatedInCreateSessionRequestData 
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
            case BearerTftIeType:
            {
                BearerTftIe ieObject =
                dynamic_cast<
                BearerTftIe&>(GtpV2IeFactory::getInstance().
                         getIeObject(BearerTftIeType));


                if(ieHeader.instance == 0)
                {

                					rc = ieObject.decodeBearerTftIe(buffer, data.tft, ieHeader.length);

                    data.tftIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: tft\n");
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
            case FTeidIeType:
            {
                FTeidIe ieObject =
                dynamic_cast<
                FTeidIe&>(GtpV2IeFactory::getInstance().
                         getIeObject(FTeidIeType));


                if(ieHeader.instance == 0)
                {

                					rc = ieObject.decodeFTeidIe(buffer, data.s1UEnodebFTeid, ieHeader.length);

                    data.s1UEnodebFTeidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: s1UEnodebFTeid\n");
                        return false;
                    }
                }

                else if(ieHeader.instance == 1)
                {

                					rc = ieObject.decodeFTeidIe(buffer, data.s4USgsnFTeid, ieHeader.length);

                    data.s4USgsnFTeidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: s4USgsnFTeid\n");
                        return false;
                    }
                }

                else if(ieHeader.instance == 2)
                {

                					rc = ieObject.decodeFTeidIe(buffer, data.s5S8USgwFTeid, ieHeader.length);

                    data.s5S8USgwFTeidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: s5S8USgwFTeid\n");
                        return false;
                    }
                }

                else if(ieHeader.instance == 3)
                {

                					rc = ieObject.decodeFTeidIe(buffer, data.s5S8UPgwFTeid, ieHeader.length);

                    data.s5S8UPgwFTeidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: s5S8UPgwFTeid\n");
                        return false;
                    }
                }

                else if(ieHeader.instance == 4)
                {

                					rc = ieObject.decodeFTeidIe(buffer, data.s12RncFTeid, ieHeader.length);

                    data.s12RncFTeidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: s12RncFTeid\n");
                        return false;
                    }
                }

                else if(ieHeader.instance == 5)
                {

                					rc = ieObject.decodeFTeidIe(buffer, data.s2bUEpdgFTeid, ieHeader.length);

                    data.s2bUEpdgFTeidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: s2bUEpdgFTeid\n");
                        return false;
                    }
                }

                else if(ieHeader.instance == 6)
                {

                					rc = ieObject.decodeFTeidIe(buffer, data.s2aUTwanFTeid, ieHeader.length);

                    data.s2aUTwanFTeidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: s2aUTwanFTeid\n");
                        return false;
                    }
                }

                else if(ieHeader.instance == 7)
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
            case BearerQosIeType:
            {
                BearerQosIe ieObject =
                dynamic_cast<
                BearerQosIe&>(GtpV2IeFactory::getInstance().
                         getIeObject(BearerQosIeType));


                if(ieHeader.instance == 0)
                {

                					rc = ieObject.decodeBearerQosIe(buffer, data.bearerLevelQos, ieHeader.length);

                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: bearerLevelQos\n");
                        return false;
                    }
                    Uint16 mandIe = BearerQosIeType;
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

void BearerContextsToBeCreatedInCreateSessionRequest::
displayBearerContextsToBeCreatedInCreateSessionRequestData_v
(BearerContextsToBeCreatedInCreateSessionRequestData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"BearerContextsToBeCreatedInCreateSessionRequest:");
    stream.endOfLine();
    stream.incrIndent();


    if (data.tftIePresent)
    {

        stream.add((char *)"tft:");
        stream.endOfLine();
        BearerTftIe bearerTft=
        dynamic_cast<
        BearerTftIe&>(GtpV2IeFactory::getInstance().getIeObject(BearerTftIeType));
        bearerTft.displayBearerTftIe_v(data.tft, stream);

    }

    if (data.s1UEnodebFTeidIePresent)
    {

        stream.add((char *)"s1UEnodebFTeid:");
        stream.endOfLine();
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        fTeid.displayFTeidIe_v(data.s1UEnodebFTeid, stream);

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

    if (data.s5S8USgwFTeidIePresent)
    {

        stream.add((char *)"s5S8USgwFTeid:");
        stream.endOfLine();
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        fTeid.displayFTeidIe_v(data.s5S8USgwFTeid, stream);

    }

    if (data.s5S8UPgwFTeidIePresent)
    {

        stream.add((char *)"s5S8UPgwFTeid:");
        stream.endOfLine();
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        fTeid.displayFTeidIe_v(data.s5S8UPgwFTeid, stream);

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

    if (data.s2bUEpdgFTeidIePresent)
    {

        stream.add((char *)"s2bUEpdgFTeid:");
        stream.endOfLine();
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        fTeid.displayFTeidIe_v(data.s2bUEpdgFTeid, stream);

    }

    if (data.s2aUTwanFTeidIePresent)
    {

        stream.add((char *)"s2aUTwanFTeid:");
        stream.endOfLine();
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        fTeid.displayFTeidIe_v(data.s2aUTwanFTeid, stream);

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





