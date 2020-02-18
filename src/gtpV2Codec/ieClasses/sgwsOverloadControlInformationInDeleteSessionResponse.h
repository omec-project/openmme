/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef SGWSOVERLOADCONTROLINFORMATIONINDELETESESSIONRESPONSE_H_
#define SGWSOVERLOADCONTROLINFORMATIONINDELETESESSIONRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class SgwsOverloadControlInformationInDeleteSessionResponse:public GtpV2GroupedIe
{
public:
    SgwsOverloadControlInformationInDeleteSessionResponse();
    virtual ~SgwsOverloadControlInformationInDeleteSessionResponse();
    bool encodeSgwsOverloadControlInformationInDeleteSessionResponse(MsgBuffer &buffer,
                             SgwsOverloadControlInformationInDeleteSessionResponseData
                              const &data);

    bool decodeSgwsOverloadControlInformationInDeleteSessionResponse (MsgBuffer &buffer,
                             SgwsOverloadControlInformationInDeleteSessionResponseData 
                             & data, Uint16 length);

    void displaySgwsOverloadControlInformationInDeleteSessionResponseData_v
    (SgwsOverloadControlInformationInDeleteSessionResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif