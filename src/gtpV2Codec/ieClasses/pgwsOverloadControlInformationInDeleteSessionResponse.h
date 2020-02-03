/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef PGWSOVERLOADCONTROLINFORMATIONINDELETESESSIONRESPONSE_H_
#define PGWSOVERLOADCONTROLINFORMATIONINDELETESESSIONRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class PgwsOverloadControlInformationInDeleteSessionResponse:public GtpV2GroupedIe
{
public:
    PgwsOverloadControlInformationInDeleteSessionResponse();
    virtual ~PgwsOverloadControlInformationInDeleteSessionResponse();
    bool encodePgwsOverloadControlInformationInDeleteSessionResponse(MsgBuffer &buffer,
                             PgwsOverloadControlInformationInDeleteSessionResponseData
                              const &data);

    bool decodePgwsOverloadControlInformationInDeleteSessionResponse (MsgBuffer &buffer,
                             PgwsOverloadControlInformationInDeleteSessionResponseData 
                             & data, Uint16 length);

    void displayPgwsOverloadControlInformationInDeleteSessionResponseData_v
    (PgwsOverloadControlInformationInDeleteSessionResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif