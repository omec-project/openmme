/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef PGWSAPNLEVELLOADCONTROLINFORMATIONINMODIFYBEARERRESPONSE_H_
#define PGWSAPNLEVELLOADCONTROLINFORMATIONINMODIFYBEARERRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class PgwsApnLevelLoadControlInformationInModifyBearerResponse:public GtpV2GroupedIe
{
public:
    PgwsApnLevelLoadControlInformationInModifyBearerResponse();
    virtual ~PgwsApnLevelLoadControlInformationInModifyBearerResponse();
    bool encodePgwsApnLevelLoadControlInformationInModifyBearerResponse(MsgBuffer &buffer,
                             PgwsApnLevelLoadControlInformationInModifyBearerResponseData
                              const &data);

    bool decodePgwsApnLevelLoadControlInformationInModifyBearerResponse (MsgBuffer &buffer,
                             PgwsApnLevelLoadControlInformationInModifyBearerResponseData 
                             & data, Uint16 length);

    void displayPgwsApnLevelLoadControlInformationInModifyBearerResponseData_v
    (PgwsApnLevelLoadControlInformationInModifyBearerResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif