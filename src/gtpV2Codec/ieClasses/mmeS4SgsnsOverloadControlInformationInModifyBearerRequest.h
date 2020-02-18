/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef MMES4SGSNSOVERLOADCONTROLINFORMATIONINMODIFYBEARERREQUEST_H_
#define MMES4SGSNSOVERLOADCONTROLINFORMATIONINMODIFYBEARERREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class MmeS4SgsnsOverloadControlInformationInModifyBearerRequest:public GtpV2GroupedIe
{
public:
    MmeS4SgsnsOverloadControlInformationInModifyBearerRequest();
    virtual ~MmeS4SgsnsOverloadControlInformationInModifyBearerRequest();
    bool encodeMmeS4SgsnsOverloadControlInformationInModifyBearerRequest(MsgBuffer &buffer,
                             MmeS4SgsnsOverloadControlInformationInModifyBearerRequestData
                              const &data);

    bool decodeMmeS4SgsnsOverloadControlInformationInModifyBearerRequest (MsgBuffer &buffer,
                             MmeS4SgsnsOverloadControlInformationInModifyBearerRequestData 
                             & data, Uint16 length);

    void displayMmeS4SgsnsOverloadControlInformationInModifyBearerRequestData_v
    (MmeS4SgsnsOverloadControlInformationInModifyBearerRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif