/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef PGWSOVERLOADCONTROLINFORMATIONINCREATEBEARERREQUEST_H_
#define PGWSOVERLOADCONTROLINFORMATIONINCREATEBEARERREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class PgwsOverloadControlInformationInCreateBearerRequest:public GtpV2GroupedIe
{
public:
    PgwsOverloadControlInformationInCreateBearerRequest();
    virtual ~PgwsOverloadControlInformationInCreateBearerRequest();
    bool encodePgwsOverloadControlInformationInCreateBearerRequest(MsgBuffer &buffer,
                             PgwsOverloadControlInformationInCreateBearerRequestData
                              const &data);

    bool decodePgwsOverloadControlInformationInCreateBearerRequest (MsgBuffer &buffer,
                             PgwsOverloadControlInformationInCreateBearerRequestData 
                             & data, Uint16 length);

    void displayPgwsOverloadControlInformationInCreateBearerRequestData_v
    (PgwsOverloadControlInformationInCreateBearerRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif