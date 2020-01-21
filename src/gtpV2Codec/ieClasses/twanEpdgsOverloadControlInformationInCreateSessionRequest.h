/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef TWANEPDGSOVERLOADCONTROLINFORMATIONINCREATESESSIONREQUEST_H_
#define TWANEPDGSOVERLOADCONTROLINFORMATIONINCREATESESSIONREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class TwanEpdgsOverloadControlInformationInCreateSessionRequest:public GtpV2GroupedIe
{
public:
    TwanEpdgsOverloadControlInformationInCreateSessionRequest();
    virtual ~TwanEpdgsOverloadControlInformationInCreateSessionRequest();
    bool encodeTwanEpdgsOverloadControlInformationInCreateSessionRequest(MsgBuffer &buffer,
                             TwanEpdgsOverloadControlInformationInCreateSessionRequestData
                              const &data);

    bool decodeTwanEpdgsOverloadControlInformationInCreateSessionRequest (MsgBuffer &buffer,
                             TwanEpdgsOverloadControlInformationInCreateSessionRequestData 
                             & data, Uint16 length);

    void displayTwanEpdgsOverloadControlInformationInCreateSessionRequestData_v
    (TwanEpdgsOverloadControlInformationInCreateSessionRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif