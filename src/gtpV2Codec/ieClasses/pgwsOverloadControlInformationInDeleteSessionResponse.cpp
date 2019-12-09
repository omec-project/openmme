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

#include "pgwsOverloadControlInformationInDeleteSessionResponse.h"
#include "manual/gtpV2Ie.h"
#include "gtpV2IeFactory.h"
#include "sequenceNumberIe.h"
#include "metricIe.h"
#include "epcTimerIe.h"
#include "apnIe.h"

PgwsOverloadControlInformationInDeleteSessionResponse::
PgwsOverloadControlInformationInDeleteSessionResponse()
{
    Uint16 mandIe;
    mandIe = SequenceNumberIeType;
    mandIe = (mandIe << 8) | 0; // overloadControlSequenceNumber
    mandatoryIeSet.insert(mandIe);
    mandIe = MetricIeType;
    mandIe = (mandIe << 8) | 0; // overloadReductionMetric
    mandatoryIeSet.insert(mandIe);
    mandIe = EpcTimerIeType;
    mandIe = (mandIe << 8) | 0; // periodOfValidity
    mandatoryIeSet.insert(mandIe);

}

PgwsOverloadControlInformationInDeleteSessionResponse::
~PgwsOverloadControlInformationInDeleteSessionResponse()
{

}
bool PgwsOverloadControlInformationInDeleteSessionResponse::
encodePgwsOverloadControlInformationInDeleteSessionResponse(MsgBuffer &buffer,
                         PgwsOverloadControlInformationInDeleteSessionResponseData
                          const &data)
{
    bool rc = false;
    GtpV2IeHeader header;
    Uint16 startIndex = 0;
    Uint16 endIndex = 0;
    Uint16 length = 0;


    
    // Encode the Ie Header
    header.ieType = SequenceNumberIeType;
    header.instance = 0;
    header.length = 0; // We will encode the IE first and then update the length
    GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
    startIndex = buffer.getCurrentIndex(); 
    SequenceNumberIe sequenceNumber=
    dynamic_cast<
    SequenceNumberIe&>(GtpV2IeFactory::getInstance().getIeObject(SequenceNumberIeType));
    rc = sequenceNumber.encodeSequenceNumberIe(buffer, data.overloadControlSequenceNumber);
    endIndex = buffer.getCurrentIndex();
    length = endIndex - startIndex;

    // encode the length value now
    buffer.goToIndex(startIndex - 3);
    buffer.writeUint16(length, false);
    buffer.goToIndex(endIndex);
    if (!(rc))
    {
        errorStream.add((char *)"Failed to encode IE: overloadControlSequenceNumber\n");
        return false;
    }


    
    // Encode the Ie Header
    header.ieType = MetricIeType;
    header.instance = 0;
    header.length = 0; // We will encode the IE first and then update the length
    GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
    startIndex = buffer.getCurrentIndex(); 
    MetricIe metric=
    dynamic_cast<
    MetricIe&>(GtpV2IeFactory::getInstance().getIeObject(MetricIeType));
    rc = metric.encodeMetricIe(buffer, data.overloadReductionMetric);
    endIndex = buffer.getCurrentIndex();
    length = endIndex - startIndex;

    // encode the length value now
    buffer.goToIndex(startIndex - 3);
    buffer.writeUint16(length, false);
    buffer.goToIndex(endIndex);
    if (!(rc))
    {
        errorStream.add((char *)"Failed to encode IE: overloadReductionMetric\n");
        return false;
    }


    
    // Encode the Ie Header
    header.ieType = EpcTimerIeType;
    header.instance = 0;
    header.length = 0; // We will encode the IE first and then update the length
    GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
    startIndex = buffer.getCurrentIndex(); 
    EpcTimerIe epcTimer=
    dynamic_cast<
    EpcTimerIe&>(GtpV2IeFactory::getInstance().getIeObject(EpcTimerIeType));
    rc = epcTimer.encodeEpcTimerIe(buffer, data.periodOfValidity);
    endIndex = buffer.getCurrentIndex();
    length = endIndex - startIndex;

    // encode the length value now
    buffer.goToIndex(startIndex - 3);
    buffer.writeUint16(length, false);
    buffer.goToIndex(endIndex);
    if (!(rc))
    {
        errorStream.add((char *)"Failed to encode IE: periodOfValidity\n");
        return false;
    }

    if (data.listOfAccessPointNameIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = ApnIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        ApnIe apn=
        dynamic_cast<
        ApnIe&>(GtpV2IeFactory::getInstance().getIeObject(ApnIeType));
        rc = apn.encodeApnIe(buffer, data.listOfAccessPointName);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        {
          errorStream.add((char *)"Failed to encode IE: listOfAccessPointName\n");
          return false;
        }
    }
    return rc;
}

bool PgwsOverloadControlInformationInDeleteSessionResponse::
decodePgwsOverloadControlInformationInDeleteSessionResponse(MsgBuffer &buffer,
                         PgwsOverloadControlInformationInDeleteSessionResponseData 
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
            case SequenceNumberIeType:
            {
                SequenceNumberIe ieObject =
                dynamic_cast<
                SequenceNumberIe&>(GtpV2IeFactory::getInstance().
                         getIeObject(SequenceNumberIeType));


                if(ieHeader.instance == 0)
                {

                					rc = ieObject.decodeSequenceNumberIe(buffer, data.overloadControlSequenceNumber, ieHeader.length);

                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: overloadControlSequenceNumber\n");
                        return false;
                    }
                    Uint16 mandIe = SequenceNumberIeType;
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
            case MetricIeType:
            {
                MetricIe ieObject =
                dynamic_cast<
                MetricIe&>(GtpV2IeFactory::getInstance().
                         getIeObject(MetricIeType));


                if(ieHeader.instance == 0)
                {

                					rc = ieObject.decodeMetricIe(buffer, data.overloadReductionMetric, ieHeader.length);

                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: overloadReductionMetric\n");
                        return false;
                    }
                    Uint16 mandIe = MetricIeType;
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
            case EpcTimerIeType:
            {
                EpcTimerIe ieObject =
                dynamic_cast<
                EpcTimerIe&>(GtpV2IeFactory::getInstance().
                         getIeObject(EpcTimerIeType));


                if(ieHeader.instance == 0)
                {

                					rc = ieObject.decodeEpcTimerIe(buffer, data.periodOfValidity, ieHeader.length);

                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: periodOfValidity\n");
                        return false;
                    }
                    Uint16 mandIe = EpcTimerIeType;
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
            case ApnIeType:
            {
                ApnIe ieObject =
                dynamic_cast<
                ApnIe&>(GtpV2IeFactory::getInstance().
                         getIeObject(ApnIeType));


                if(ieHeader.instance == 0)
                {

                					rc = ieObject.decodeApnIe(buffer, data.listOfAccessPointName, ieHeader.length);

                    data.listOfAccessPointNameIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: listOfAccessPointName\n");
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

void PgwsOverloadControlInformationInDeleteSessionResponse::
displayPgwsOverloadControlInformationInDeleteSessionResponseData_v
(PgwsOverloadControlInformationInDeleteSessionResponseData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"PgwsOverloadControlInformationInDeleteSessionResponse:");
    stream.endOfLine();
    stream.incrIndent();




    if (data.listOfAccessPointNameIePresent)
    {

        stream.add((char *)"listOfAccessPointName:");
        stream.endOfLine();
        ApnIe apn=
        dynamic_cast<
        ApnIe&>(GtpV2IeFactory::getInstance().getIeObject(ApnIeType));
        apn.displayApnIe_v(data.listOfAccessPointName, stream);

    }

    stream.decrIndent();
    stream.decrIndent();
}





