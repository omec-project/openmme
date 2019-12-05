/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef SGWSAPNLEVELLOADCONTROLINFORMATIONINDELETEBEARERREQUEST_H_
#define SGWSAPNLEVELLOADCONTROLINFORMATIONINDELETEBEARERREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class SgwsApnLevelLoadControlInformationInDeleteBearerRequest:public GtpV2GroupedIe
{
public:
    SgwsApnLevelLoadControlInformationInDeleteBearerRequest();
    virtual ~SgwsApnLevelLoadControlInformationInDeleteBearerRequest();
    bool encodeSgwsApnLevelLoadControlInformationInDeleteBearerRequest(MsgBuffer &buffer,
                             SgwsApnLevelLoadControlInformationInDeleteBearerRequestData
                              const &data);

    bool decodeSgwsApnLevelLoadControlInformationInDeleteBearerRequest (MsgBuffer &buffer,
                             SgwsApnLevelLoadControlInformationInDeleteBearerRequestData 
                             & data, Uint16 length);

    void displaySgwsApnLevelLoadControlInformationInDeleteBearerRequestData_v
    (SgwsApnLevelLoadControlInformationInDeleteBearerRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif