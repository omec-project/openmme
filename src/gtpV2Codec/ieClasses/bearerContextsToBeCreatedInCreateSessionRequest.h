/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef BEARERCONTEXTSTOBECREATEDINCREATESESSIONREQUEST_H_
#define BEARERCONTEXTSTOBECREATEDINCREATESESSIONREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class BearerContextsToBeCreatedInCreateSessionRequest:public GtpV2GroupedIe
{
public:
    BearerContextsToBeCreatedInCreateSessionRequest();
    virtual ~BearerContextsToBeCreatedInCreateSessionRequest();
    bool encodeBearerContextsToBeCreatedInCreateSessionRequest(MsgBuffer &buffer,
                             BearerContextsToBeCreatedInCreateSessionRequestData
                              const &data);

    bool decodeBearerContextsToBeCreatedInCreateSessionRequest (MsgBuffer &buffer,
                             BearerContextsToBeCreatedInCreateSessionRequestData 
                             & data, Uint16 length);

    void displayBearerContextsToBeCreatedInCreateSessionRequestData_v
    (BearerContextsToBeCreatedInCreateSessionRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif