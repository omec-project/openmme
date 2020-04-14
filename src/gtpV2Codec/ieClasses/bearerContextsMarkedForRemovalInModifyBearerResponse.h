/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef BEARERCONTEXTSMARKEDFORREMOVALINMODIFYBEARERRESPONSE_H_
#define BEARERCONTEXTSMARKEDFORREMOVALINMODIFYBEARERRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class BearerContextsMarkedForRemovalInModifyBearerResponse:public GtpV2GroupedIe
{
public:
    BearerContextsMarkedForRemovalInModifyBearerResponse();
    virtual ~BearerContextsMarkedForRemovalInModifyBearerResponse();
    bool encodeBearerContextsMarkedForRemovalInModifyBearerResponse(MsgBuffer &buffer,
                             BearerContextsMarkedForRemovalInModifyBearerResponseData
                              const &data);

    bool decodeBearerContextsMarkedForRemovalInModifyBearerResponse (MsgBuffer &buffer,
                             BearerContextsMarkedForRemovalInModifyBearerResponseData 
                             & data, Uint16 length);

    void displayBearerContextsMarkedForRemovalInModifyBearerResponseData_v
    (BearerContextsMarkedForRemovalInModifyBearerResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif