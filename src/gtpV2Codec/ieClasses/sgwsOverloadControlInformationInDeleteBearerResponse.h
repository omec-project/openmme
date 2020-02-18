/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef SGWSOVERLOADCONTROLINFORMATIONINDELETEBEARERRESPONSE_H_
#define SGWSOVERLOADCONTROLINFORMATIONINDELETEBEARERRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class SgwsOverloadControlInformationInDeleteBearerResponse:public GtpV2GroupedIe
{
public:
    SgwsOverloadControlInformationInDeleteBearerResponse();
    virtual ~SgwsOverloadControlInformationInDeleteBearerResponse();
    bool encodeSgwsOverloadControlInformationInDeleteBearerResponse(MsgBuffer &buffer,
                             SgwsOverloadControlInformationInDeleteBearerResponseData
                              const &data);

    bool decodeSgwsOverloadControlInformationInDeleteBearerResponse (MsgBuffer &buffer,
                             SgwsOverloadControlInformationInDeleteBearerResponseData 
                             & data, Uint16 length);

    void displaySgwsOverloadControlInformationInDeleteBearerResponseData_v
    (SgwsOverloadControlInformationInDeleteBearerResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif