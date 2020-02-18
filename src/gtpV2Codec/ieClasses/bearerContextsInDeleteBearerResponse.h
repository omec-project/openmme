/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef BEARERCONTEXTSINDELETEBEARERRESPONSE_H_
#define BEARERCONTEXTSINDELETEBEARERRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class BearerContextsInDeleteBearerResponse:public GtpV2GroupedIe
{
public:
    BearerContextsInDeleteBearerResponse();
    virtual ~BearerContextsInDeleteBearerResponse();
    bool encodeBearerContextsInDeleteBearerResponse(MsgBuffer &buffer,
                             BearerContextsInDeleteBearerResponseData
                              const &data);

    bool decodeBearerContextsInDeleteBearerResponse (MsgBuffer &buffer,
                             BearerContextsInDeleteBearerResponseData 
                             & data, Uint16 length);

    void displayBearerContextsInDeleteBearerResponseData_v
    (BearerContextsInDeleteBearerResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif