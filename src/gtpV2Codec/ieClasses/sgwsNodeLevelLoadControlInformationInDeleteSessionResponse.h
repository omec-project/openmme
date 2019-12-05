/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef SGWSNODELEVELLOADCONTROLINFORMATIONINDELETESESSIONRESPONSE_H_
#define SGWSNODELEVELLOADCONTROLINFORMATIONINDELETESESSIONRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class SgwsNodeLevelLoadControlInformationInDeleteSessionResponse:public GtpV2GroupedIe
{
public:
    SgwsNodeLevelLoadControlInformationInDeleteSessionResponse();
    virtual ~SgwsNodeLevelLoadControlInformationInDeleteSessionResponse();
    bool encodeSgwsNodeLevelLoadControlInformationInDeleteSessionResponse(MsgBuffer &buffer,
                             SgwsNodeLevelLoadControlInformationInDeleteSessionResponseData
                              const &data);

    bool decodeSgwsNodeLevelLoadControlInformationInDeleteSessionResponse (MsgBuffer &buffer,
                             SgwsNodeLevelLoadControlInformationInDeleteSessionResponseData 
                             & data, Uint16 length);

    void displaySgwsNodeLevelLoadControlInformationInDeleteSessionResponseData_v
    (SgwsNodeLevelLoadControlInformationInDeleteSessionResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif