/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef PGWSAPNLEVELLOADCONTROLINFORMATIONINDELETESESSIONRESPONSE_H_
#define PGWSAPNLEVELLOADCONTROLINFORMATIONINDELETESESSIONRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class PgwsApnLevelLoadControlInformationInDeleteSessionResponse:public GtpV2GroupedIe
{
public:
    PgwsApnLevelLoadControlInformationInDeleteSessionResponse();
    virtual ~PgwsApnLevelLoadControlInformationInDeleteSessionResponse();
    bool encodePgwsApnLevelLoadControlInformationInDeleteSessionResponse(MsgBuffer &buffer,
                             PgwsApnLevelLoadControlInformationInDeleteSessionResponseData
                              const &data);

    bool decodePgwsApnLevelLoadControlInformationInDeleteSessionResponse (MsgBuffer &buffer,
                             PgwsApnLevelLoadControlInformationInDeleteSessionResponseData 
                             & data, Uint16 length);

    void displayPgwsApnLevelLoadControlInformationInDeleteSessionResponseData_v
    (PgwsApnLevelLoadControlInformationInDeleteSessionResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif