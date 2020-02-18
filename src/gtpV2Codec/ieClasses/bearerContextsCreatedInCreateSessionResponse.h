/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef BEARERCONTEXTSCREATEDINCREATESESSIONRESPONSE_H_
#define BEARERCONTEXTSCREATEDINCREATESESSIONRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class BearerContextsCreatedInCreateSessionResponse:public GtpV2GroupedIe
{
public:
    BearerContextsCreatedInCreateSessionResponse();
    virtual ~BearerContextsCreatedInCreateSessionResponse();
    bool encodeBearerContextsCreatedInCreateSessionResponse(MsgBuffer &buffer,
                             BearerContextsCreatedInCreateSessionResponseData
                              const &data);

    bool decodeBearerContextsCreatedInCreateSessionResponse (MsgBuffer &buffer,
                             BearerContextsCreatedInCreateSessionResponseData 
                             & data, Uint16 length);

    void displayBearerContextsCreatedInCreateSessionResponseData_v
    (BearerContextsCreatedInCreateSessionResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif