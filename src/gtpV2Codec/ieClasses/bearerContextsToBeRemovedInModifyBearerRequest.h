/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef BEARERCONTEXTSTOBEREMOVEDINMODIFYBEARERREQUEST_H_
#define BEARERCONTEXTSTOBEREMOVEDINMODIFYBEARERREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class BearerContextsToBeRemovedInModifyBearerRequest:public GtpV2GroupedIe
{
public:
    BearerContextsToBeRemovedInModifyBearerRequest();
    virtual ~BearerContextsToBeRemovedInModifyBearerRequest();
    bool encodeBearerContextsToBeRemovedInModifyBearerRequest(MsgBuffer &buffer,
                             BearerContextsToBeRemovedInModifyBearerRequestData
                              const &data);

    bool decodeBearerContextsToBeRemovedInModifyBearerRequest (MsgBuffer &buffer,
                             BearerContextsToBeRemovedInModifyBearerRequestData 
                             & data, Uint16 length);

    void displayBearerContextsToBeRemovedInModifyBearerRequestData_v
    (BearerContextsToBeRemovedInModifyBearerRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif