/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef BEARERCONTEXTSINCREATEBEARERRESPONSE_H_
#define BEARERCONTEXTSINCREATEBEARERRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class BearerContextsInCreateBearerResponse:public GtpV2GroupedIe
{
public:
    BearerContextsInCreateBearerResponse();
    virtual ~BearerContextsInCreateBearerResponse();
    bool encodeBearerContextsInCreateBearerResponse(MsgBuffer &buffer,
                             BearerContextsInCreateBearerResponseData
                              const &data);

    bool decodeBearerContextsInCreateBearerResponse (MsgBuffer &buffer,
                             BearerContextsInCreateBearerResponseData 
                             & data, Uint16 length);

    void displayBearerContextsInCreateBearerResponseData_v
    (BearerContextsInCreateBearerResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif