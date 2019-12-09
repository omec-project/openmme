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

#include "bearerContextsInCreateBearerRequest.h"
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
#include "bearerQosIe.h"
#include "chargingIdIe.h"
#include "bearerFlagsIe.h"
#include "pcoIe.h"
#include "epcoIe.h"
#include "maximumPacketLossRateIe.h"

BearerContextsInCreateBearerRequest::
BearerContextsInCreateBearerRequest()
{
    Uint16 mandIe;
    mandIe = EbiIeType;
    mandIe = (mandIe << 8) | 0; // epsBearerId
    mandatoryIeSet.insert(mandIe);
    mandIe = BearerTftIeType;
    mandIe = (mandIe << 8) | 0; // tft
    mandatoryIeSet.insert(mandIe);
    mandIe = BearerQosIeType;
    mandIe = (mandIe << 8) | 0; // bearerLevelQos
    mandatoryIeSet.insert(mandIe);

}

BearerContextsInCreateBearerRequest::
~BearerContextsInCreateBearerRequest()
{

}
bool BearerContextsInCreateBearerRequest::
encodeBearerContextsInCreateBearerRequest(MsgBuffer &buffer,
                         BearerContextsInCreateBearerRequestData
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
          errorStream.add((char *)"Failed to encode IE: s1USgwFTeid\n");
          return false;
        }
    }

    if (data.s58UPgwFTeidIePresent)
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
        rc = fTeid.encodeFTeidIe(buffer, data.s58UPgwFTeid);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        {
          errorStream.add((char *)"Failed to encode IE: s58UPgwFTeid\n");
          return false;
        }
    }

    if (data.s12SgwFTeidIePresent)
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
        rc = fTeid.encodeFTeidIe(buffer, data.s12SgwFTeid);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        {
          errorStream.add((char *)"Failed to encode IE: s12SgwFTeid\n");
          return false;
        }
    }

    if (data.s4USgwFTeidIePresent)
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
        rc = fTeid.encodeFTeidIe(buffer, data.s4USgwFTeid);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        {
          errorStream.add((char *)"Failed to encode IE: s4USgwFTeid\n");
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
          errorStream.add((char *)"Failed to encode IE: s2bUPgwFTeid\n");
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
          errorStream.add((char *)"Failed to encode IE: s2aUPgwFTeid\n");
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
          errorStream.add((char *)"Failed to encode IE: chargingId\n");
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
          errorStream.add((char *)"Failed to encode IE: bearerFlags\n");
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

    if (data.maximumPacketLossRateIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = MaximumPacketLossRateIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        MaximumPacketLossRateIe maximumPacketLossRate=
        dynamic_cast<
        MaximumPacketLossRateIe&>(GtpV2IeFactory::getInstance().getIeObject(MaximumPacketLossRateIeType));
        rc = maximumPacketLossRate.encodeMaximumPacketLossRateIe(buffer, data.maximumPacketLossRate);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        {
          errorStream.add((char *)"Failed to encode IE: maximumPacketLossRate\n");
          return false;
        }
    }
    return rc;
}

bool BearerContextsInCreateBearerRequest::
decodeBearerContextsInCreateBearerRequest(MsgBuffer &buffer,
                         BearerContextsInCreateBearerRequestData 
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

                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: tft\n");
                        return false;
                    }
                    Uint16 mandIe = BearerTftIeType;
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

                					rc = ieObject.decodeFTeidIe(buffer, data.s1USgwFTeid, ieHeader.length);

                    data.s1USgwFTeidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: s1USgwFTeid\n");
                        return false;
                    }
                }

                else if(ieHeader.instance == 1)
                {

                					rc = ieObject.decodeFTeidIe(buffer, data.s58UPgwFTeid, ieHeader.length);

                    data.s58UPgwFTeidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: s58UPgwFTeid\n");
                        return false;
                    }
                }

                else if(ieHeader.instance == 2)
                {

                					rc = ieObject.decodeFTeidIe(buffer, data.s12SgwFTeid, ieHeader.length);

                    data.s12SgwFTeidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: s12SgwFTeid\n");
                        return false;
                    }
                }

                else if(ieHeader.instance == 3)
                {

                					rc = ieObject.decodeFTeidIe(buffer, data.s4USgwFTeid, ieHeader.length);

                    data.s4USgwFTeidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: s4USgwFTeid\n");
                        return false;
                    }
                }

                else if(ieHeader.instance == 4)
                {

                					rc = ieObject.decodeFTeidIe(buffer, data.s2bUPgwFTeid, ieHeader.length);

                    data.s2bUPgwFTeidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: s2bUPgwFTeid\n");
                        return false;
                    }
                }

                else if(ieHeader.instance == 5)
                {

                					rc = ieObject.decodeFTeidIe(buffer, data.s2aUPgwFTeid, ieHeader.length);

                    data.s2aUPgwFTeidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: s2aUPgwFTeid\n");
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
                        errorStream.add((char *)"Failed to decode IE: chargingId\n");
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
                        errorStream.add((char *)"Failed to decode IE: bearerFlags\n");
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
            case PcoIeType:
            {
                PcoIe ieObject =
                dynamic_cast<
                PcoIe&>(GtpV2IeFactory::getInstance().
                         getIeObject(PcoIeType));


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
                    // Unknown IE instance print error TODO
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
                EpcoIe&>(GtpV2IeFactory::getInstance().
                         getIeObject(EpcoIeType));


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
                    // Unknown IE instance print error TODO
                    errorStream.add((char *)"Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
            case MaximumPacketLossRateIeType:
            {
                MaximumPacketLossRateIe ieObject =
                dynamic_cast<
                MaximumPacketLossRateIe&>(GtpV2IeFactory::getInstance().
                         getIeObject(MaximumPacketLossRateIeType));


                if(ieHeader.instance == 0)
                {

                					rc = ieObject.decodeMaximumPacketLossRateIe(buffer, data.maximumPacketLossRate, ieHeader.length);

                    data.maximumPacketLossRateIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: maximumPacketLossRate\n");
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

void BearerContextsInCreateBearerRequest::
displayBearerContextsInCreateBearerRequestData_v
(BearerContextsInCreateBearerRequestData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"BearerContextsInCreateBearerRequest:");
    stream.endOfLine();
    stream.incrIndent();



    if (data.s1USgwFTeidIePresent)
    {

        stream.add((char *)"s1USgwFTeid:");
        stream.endOfLine();
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        fTeid.displayFTeidIe_v(data.s1USgwFTeid, stream);

    }

    if (data.s58UPgwFTeidIePresent)
    {

        stream.add((char *)"s58UPgwFTeid:");
        stream.endOfLine();
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        fTeid.displayFTeidIe_v(data.s58UPgwFTeid, stream);

    }

    if (data.s12SgwFTeidIePresent)
    {

        stream.add((char *)"s12SgwFTeid:");
        stream.endOfLine();
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        fTeid.displayFTeidIe_v(data.s12SgwFTeid, stream);

    }

    if (data.s4USgwFTeidIePresent)
    {

        stream.add((char *)"s4USgwFTeid:");
        stream.endOfLine();
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        fTeid.displayFTeidIe_v(data.s4USgwFTeid, stream);

    }

    if (data.s2bUPgwFTeidIePresent)
    {

        stream.add((char *)"s2bUPgwFTeid:");
        stream.endOfLine();
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        fTeid.displayFTeidIe_v(data.s2bUPgwFTeid, stream);

    }

    if (data.s2aUPgwFTeidIePresent)
    {

        stream.add((char *)"s2aUPgwFTeid:");
        stream.endOfLine();
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        fTeid.displayFTeidIe_v(data.s2aUPgwFTeid, stream);

    }


    if (data.chargingIdIePresent)
    {

        stream.add((char *)"chargingId:");
        stream.endOfLine();
        ChargingIdIe chargingId=
        dynamic_cast<
        ChargingIdIe&>(GtpV2IeFactory::getInstance().getIeObject(ChargingIdIeType));
        chargingId.displayChargingIdIe_v(data.chargingId, stream);

    }

    if (data.bearerFlagsIePresent)
    {

        stream.add((char *)"bearerFlags:");
        stream.endOfLine();
        BearerFlagsIe bearerFlags=
        dynamic_cast<
        BearerFlagsIe&>(GtpV2IeFactory::getInstance().getIeObject(BearerFlagsIeType));
        bearerFlags.displayBearerFlagsIe_v(data.bearerFlags, stream);

    }

    if (data.protocolConfigurationOptionsIePresent)
    {

        stream.add((char *)"protocolConfigurationOptions:");
        stream.endOfLine();
        PcoIe pco=
        dynamic_cast<
        PcoIe&>(GtpV2IeFactory::getInstance().getIeObject(PcoIeType));
        pco.displayPcoIe_v(data.protocolConfigurationOptions, stream);

    }

    if (data.extendedProtocolConfigurationOptionsIePresent)
    {

        stream.add((char *)"extendedProtocolConfigurationOptions:");
        stream.endOfLine();
        EpcoIe epco=
        dynamic_cast<
        EpcoIe&>(GtpV2IeFactory::getInstance().getIeObject(EpcoIeType));
        epco.displayEpcoIe_v(data.extendedProtocolConfigurationOptions, stream);

    }

    if (data.maximumPacketLossRateIePresent)
    {

        stream.add((char *)"maximumPacketLossRate:");
        stream.endOfLine();
        MaximumPacketLossRateIe maximumPacketLossRate=
        dynamic_cast<
        MaximumPacketLossRateIe&>(GtpV2IeFactory::getInstance().getIeObject(MaximumPacketLossRateIeType));
        maximumPacketLossRate.displayMaximumPacketLossRateIe_v(data.maximumPacketLossRate, stream);

    }

    stream.decrIndent();
    stream.decrIndent();
}





