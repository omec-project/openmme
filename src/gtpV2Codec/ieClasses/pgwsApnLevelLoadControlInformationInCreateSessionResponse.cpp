/*
 * pgwsApnLevelLoadControlInformationInCreateSessionResponse.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */
#include "pgwsApnLevelLoadControlInformationInCreateSessionResponse.h"
#include "manual/gtpV2Ie.h"
#include "gtpV2IeFactory.h"
#include "sequenceNumberIe.h"
#include "metricIe.h"
#include "apnAndRelativeCapacityIe.h"

PgwsApnLevelLoadControlInformationInCreateSessionResponse::
PgwsApnLevelLoadControlInformationInCreateSessionResponse()
{
    Uint16 mandIe;
    mandIe = SequenceNumberIeType;
    mandIe = (mandIe << 8) | 0; // loadControlSequenceNumber
    mandatoryIeSet.insert(mandIe);
    mandIe = MetricIeType;
    mandIe = (mandIe << 8) | 0; // loadMetric
    mandatoryIeSet.insert(mandIe);
    mandIe = ApnAndRelativeCapacityIeType;
    mandIe = (mandIe << 8) | 0; // listOfApnAndRelativeCapacity
    mandatoryIeSet.insert(mandIe);

}

PgwsApnLevelLoadControlInformationInCreateSessionResponse::
~PgwsApnLevelLoadControlInformationInCreateSessionResponse()
{

}
bool PgwsApnLevelLoadControlInformationInCreateSessionResponse::
encodePgwsApnLevelLoadControlInformationInCreateSessionResponse(MsgBuffer &buffer,
                         PgwsApnLevelLoadControlInformationInCreateSessionResponseData
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
    rc = sequenceNumber.encodeSequenceNumberIe(buffer, data.loadControlSequenceNumber);
    endIndex = buffer.getCurrentIndex();
    length = endIndex - startIndex;

    // encode the length value now
    buffer.goToIndex(startIndex - 3);
    buffer.writeUint16(length, false);
    buffer.goToIndex(endIndex);
    if (!(rc))
    {
        errorStream.add("Failed to encode IE: loadControlSequenceNumber\n");
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
    rc = metric.encodeMetricIe(buffer, data.loadMetric);
    endIndex = buffer.getCurrentIndex();
    length = endIndex - startIndex;

    // encode the length value now
    buffer.goToIndex(startIndex - 3);
    buffer.writeUint16(length, false);
    buffer.goToIndex(endIndex);
    if (!(rc))
    {
        errorStream.add("Failed to encode IE: loadMetric\n");
        return false;
    }


    
    // Encode the Ie Header
    header.ieType = ApnAndRelativeCapacityIeType;
    header.instance = 0;
    header.length = 0; // We will encode the IE first and then update the length
    GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
    startIndex = buffer.getCurrentIndex(); 
    ApnAndRelativeCapacityIe apnAndRelativeCapacity=
    dynamic_cast<
    ApnAndRelativeCapacityIe&>(GtpV2IeFactory::getInstance().getIeObject(ApnAndRelativeCapacityIeType));
    rc = apnAndRelativeCapacity.encodeApnAndRelativeCapacityIe(buffer, data.listOfApnAndRelativeCapacity);
    endIndex = buffer.getCurrentIndex();
    length = endIndex - startIndex;

    // encode the length value now
    buffer.goToIndex(startIndex - 3);
    buffer.writeUint16(length, false);
    buffer.goToIndex(endIndex);
    if (!(rc))
    {
        errorStream.add("Failed to encode IE: listOfApnAndRelativeCapacity\n");
        return false;
    }
    return rc;
}

bool PgwsApnLevelLoadControlInformationInCreateSessionResponse::
decodePgwsApnLevelLoadControlInformationInCreateSessionResponse(MsgBuffer &buffer,
                         PgwsApnLevelLoadControlInformationInCreateSessionResponseData 
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
            case SequenceNumberIeType:
            {
                SequenceNumberIe ieObject =
                dynamic_cast<
                SequenceNumberIe&>(GtpV2IeFactory::getInstance().
                         getIeObject(SequenceNumberIeType));


                if(ieHeader.instance == 0)
                {

                					rc = ieObject.decodeSequenceNumberIe(buffer, data.loadControlSequenceNumber, ieHeader.length);

                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: loadControlSequenceNumber\n");
                        return false;
                    }
                    Uint16 mandIe = SequenceNumberIeType;
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
            case MetricIeType:
            {
                MetricIe ieObject =
                dynamic_cast<
                MetricIe&>(GtpV2IeFactory::getInstance().
                         getIeObject(MetricIeType));


                if(ieHeader.instance == 0)
                {

                					rc = ieObject.decodeMetricIe(buffer, data.loadMetric, ieHeader.length);

                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: loadMetric\n");
                        return false;
                    }
                    Uint16 mandIe = MetricIeType;
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
            case ApnAndRelativeCapacityIeType:
            {
                ApnAndRelativeCapacityIe ieObject =
                dynamic_cast<
                ApnAndRelativeCapacityIe&>(GtpV2IeFactory::getInstance().
                         getIeObject(ApnAndRelativeCapacityIeType));


                if(ieHeader.instance == 0)
                {

                					rc = ieObject.decodeApnAndRelativeCapacityIe(buffer, data.listOfApnAndRelativeCapacity, ieHeader.length);

                    if (!(rc))
                    {
                        errorStream.add("Failed to decode IE: listOfApnAndRelativeCapacity\n");
                        return false;
                    }
                    Uint16 mandIe = ApnAndRelativeCapacityIeType;
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

void PgwsApnLevelLoadControlInformationInCreateSessionResponse::
displayPgwsApnLevelLoadControlInformationInCreateSessionResponseData_v
(PgwsApnLevelLoadControlInformationInCreateSessionResponseData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("PgwsApnLevelLoadControlInformationInCreateSessionResponse:");
    stream.endOfLine();
    stream.incrIndent();




    stream.decrIndent();
    stream.decrIndent();
}





