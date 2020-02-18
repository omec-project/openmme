/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef MMES4SGSNSOVERLOADCONTROLINFORMATIONINCREATESESSIONREQUEST_H_
#define MMES4SGSNSOVERLOADCONTROLINFORMATIONINCREATESESSIONREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class MmeS4SgsnsOverloadControlInformationInCreateSessionRequest:public GtpV2GroupedIe
{
public:
    MmeS4SgsnsOverloadControlInformationInCreateSessionRequest();
    virtual ~MmeS4SgsnsOverloadControlInformationInCreateSessionRequest();
    bool encodeMmeS4SgsnsOverloadControlInformationInCreateSessionRequest(MsgBuffer &buffer,
                             MmeS4SgsnsOverloadControlInformationInCreateSessionRequestData
                              const &data);

    bool decodeMmeS4SgsnsOverloadControlInformationInCreateSessionRequest (MsgBuffer &buffer,
                             MmeS4SgsnsOverloadControlInformationInCreateSessionRequestData 
                             & data, Uint16 length);

    void displayMmeS4SgsnsOverloadControlInformationInCreateSessionRequestData_v
    (MmeS4SgsnsOverloadControlInformationInCreateSessionRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif