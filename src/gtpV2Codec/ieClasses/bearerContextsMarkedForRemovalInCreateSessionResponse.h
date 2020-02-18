/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef BEARERCONTEXTSMARKEDFORREMOVALINCREATESESSIONRESPONSE_H_
#define BEARERCONTEXTSMARKEDFORREMOVALINCREATESESSIONRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class BearerContextsMarkedForRemovalInCreateSessionResponse:public GtpV2GroupedIe
{
public:
    BearerContextsMarkedForRemovalInCreateSessionResponse();
    virtual ~BearerContextsMarkedForRemovalInCreateSessionResponse();
    bool encodeBearerContextsMarkedForRemovalInCreateSessionResponse(MsgBuffer &buffer,
                             BearerContextsMarkedForRemovalInCreateSessionResponseData
                              const &data);

    bool decodeBearerContextsMarkedForRemovalInCreateSessionResponse (MsgBuffer &buffer,
                             BearerContextsMarkedForRemovalInCreateSessionResponseData 
                             & data, Uint16 length);

    void displayBearerContextsMarkedForRemovalInCreateSessionResponseData_v
    (BearerContextsMarkedForRemovalInCreateSessionResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif