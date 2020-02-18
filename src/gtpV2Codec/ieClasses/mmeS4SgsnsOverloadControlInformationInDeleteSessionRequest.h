/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef MMES4SGSNSOVERLOADCONTROLINFORMATIONINDELETESESSIONREQUEST_H_
#define MMES4SGSNSOVERLOADCONTROLINFORMATIONINDELETESESSIONREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class MmeS4SgsnsOverloadControlInformationInDeleteSessionRequest:public GtpV2GroupedIe
{
public:
    MmeS4SgsnsOverloadControlInformationInDeleteSessionRequest();
    virtual ~MmeS4SgsnsOverloadControlInformationInDeleteSessionRequest();
    bool encodeMmeS4SgsnsOverloadControlInformationInDeleteSessionRequest(MsgBuffer &buffer,
                             MmeS4SgsnsOverloadControlInformationInDeleteSessionRequestData
                              const &data);

    bool decodeMmeS4SgsnsOverloadControlInformationInDeleteSessionRequest (MsgBuffer &buffer,
                             MmeS4SgsnsOverloadControlInformationInDeleteSessionRequestData 
                             & data, Uint16 length);

    void displayMmeS4SgsnsOverloadControlInformationInDeleteSessionRequestData_v
    (MmeS4SgsnsOverloadControlInformationInDeleteSessionRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif