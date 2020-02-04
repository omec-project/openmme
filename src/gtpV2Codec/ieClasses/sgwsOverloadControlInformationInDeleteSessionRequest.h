/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef SGWSOVERLOADCONTROLINFORMATIONINDELETESESSIONREQUEST_H_
#define SGWSOVERLOADCONTROLINFORMATIONINDELETESESSIONREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class SgwsOverloadControlInformationInDeleteSessionRequest:public GtpV2GroupedIe
{
public:
    SgwsOverloadControlInformationInDeleteSessionRequest();
    virtual ~SgwsOverloadControlInformationInDeleteSessionRequest();
    bool encodeSgwsOverloadControlInformationInDeleteSessionRequest(MsgBuffer &buffer,
                             SgwsOverloadControlInformationInDeleteSessionRequestData
                              const &data);

    bool decodeSgwsOverloadControlInformationInDeleteSessionRequest (MsgBuffer &buffer,
                             SgwsOverloadControlInformationInDeleteSessionRequestData 
                             & data, Uint16 length);

    void displaySgwsOverloadControlInformationInDeleteSessionRequestData_v
    (SgwsOverloadControlInformationInDeleteSessionRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif