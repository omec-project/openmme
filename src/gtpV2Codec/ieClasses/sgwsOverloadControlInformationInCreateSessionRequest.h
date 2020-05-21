/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef SGWSOVERLOADCONTROLINFORMATIONINCREATESESSIONREQUEST_H_
#define SGWSOVERLOADCONTROLINFORMATIONINCREATESESSIONREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class SgwsOverloadControlInformationInCreateSessionRequest:public GtpV2GroupedIe
{
public:
    SgwsOverloadControlInformationInCreateSessionRequest();
    virtual ~SgwsOverloadControlInformationInCreateSessionRequest();
    bool encodeSgwsOverloadControlInformationInCreateSessionRequest(MsgBuffer &buffer,
                             SgwsOverloadControlInformationInCreateSessionRequestData
                              const &data);

    bool decodeSgwsOverloadControlInformationInCreateSessionRequest (MsgBuffer &buffer,
                             SgwsOverloadControlInformationInCreateSessionRequestData 
                             & data, Uint16 length);

    void displaySgwsOverloadControlInformationInCreateSessionRequestData_v
    (SgwsOverloadControlInformationInCreateSessionRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif