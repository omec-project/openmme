/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef BEARERCONTEXTSTOBEMODIFIEDINMODIFYBEARERREQUEST_H_
#define BEARERCONTEXTSTOBEMODIFIEDINMODIFYBEARERREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class BearerContextsToBeModifiedInModifyBearerRequest:public GtpV2GroupedIe
{
public:
    BearerContextsToBeModifiedInModifyBearerRequest();
    virtual ~BearerContextsToBeModifiedInModifyBearerRequest();
    bool encodeBearerContextsToBeModifiedInModifyBearerRequest(MsgBuffer &buffer,
                             BearerContextsToBeModifiedInModifyBearerRequestData
                              const &data);

    bool decodeBearerContextsToBeModifiedInModifyBearerRequest (MsgBuffer &buffer,
                             BearerContextsToBeModifiedInModifyBearerRequestData 
                             & data, Uint16 length);

    void displayBearerContextsToBeModifiedInModifyBearerRequestData_v
    (BearerContextsToBeModifiedInModifyBearerRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif