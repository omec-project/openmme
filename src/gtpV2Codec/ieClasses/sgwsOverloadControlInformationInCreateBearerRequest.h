/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef SGWSOVERLOADCONTROLINFORMATIONINCREATEBEARERREQUEST_H_
#define SGWSOVERLOADCONTROLINFORMATIONINCREATEBEARERREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class SgwsOverloadControlInformationInCreateBearerRequest:public GtpV2GroupedIe
{
public:
    SgwsOverloadControlInformationInCreateBearerRequest();
    virtual ~SgwsOverloadControlInformationInCreateBearerRequest();
    bool encodeSgwsOverloadControlInformationInCreateBearerRequest(MsgBuffer &buffer,
                             SgwsOverloadControlInformationInCreateBearerRequestData
                              const &data);

    bool decodeSgwsOverloadControlInformationInCreateBearerRequest (MsgBuffer &buffer,
                             SgwsOverloadControlInformationInCreateBearerRequestData 
                             & data, Uint16 length);

    void displaySgwsOverloadControlInformationInCreateBearerRequestData_v
    (SgwsOverloadControlInformationInCreateBearerRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif