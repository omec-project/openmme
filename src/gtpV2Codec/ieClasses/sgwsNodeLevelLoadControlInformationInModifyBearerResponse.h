/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef SGWSNODELEVELLOADCONTROLINFORMATIONINMODIFYBEARERRESPONSE_H_
#define SGWSNODELEVELLOADCONTROLINFORMATIONINMODIFYBEARERRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class SgwsNodeLevelLoadControlInformationInModifyBearerResponse:public GtpV2GroupedIe
{
public:
    SgwsNodeLevelLoadControlInformationInModifyBearerResponse();
    virtual ~SgwsNodeLevelLoadControlInformationInModifyBearerResponse();
    bool encodeSgwsNodeLevelLoadControlInformationInModifyBearerResponse(MsgBuffer &buffer,
                             SgwsNodeLevelLoadControlInformationInModifyBearerResponseData
                              const &data);

    bool decodeSgwsNodeLevelLoadControlInformationInModifyBearerResponse (MsgBuffer &buffer,
                             SgwsNodeLevelLoadControlInformationInModifyBearerResponseData 
                             & data, Uint16 length);

    void displaySgwsNodeLevelLoadControlInformationInModifyBearerResponseData_v
    (SgwsNodeLevelLoadControlInformationInModifyBearerResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif