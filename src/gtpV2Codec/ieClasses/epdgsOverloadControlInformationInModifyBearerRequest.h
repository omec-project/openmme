/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef EPDGSOVERLOADCONTROLINFORMATIONINMODIFYBEARERREQUEST_H_
#define EPDGSOVERLOADCONTROLINFORMATIONINMODIFYBEARERREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class EpdgsOverloadControlInformationInModifyBearerRequest:public GtpV2GroupedIe
{
public:
    EpdgsOverloadControlInformationInModifyBearerRequest();
    virtual ~EpdgsOverloadControlInformationInModifyBearerRequest();
    bool encodeEpdgsOverloadControlInformationInModifyBearerRequest(MsgBuffer &buffer,
                             EpdgsOverloadControlInformationInModifyBearerRequestData
                              const &data);

    bool decodeEpdgsOverloadControlInformationInModifyBearerRequest (MsgBuffer &buffer,
                             EpdgsOverloadControlInformationInModifyBearerRequestData 
                             & data, Uint16 length);

    void displayEpdgsOverloadControlInformationInModifyBearerRequestData_v
    (EpdgsOverloadControlInformationInModifyBearerRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif