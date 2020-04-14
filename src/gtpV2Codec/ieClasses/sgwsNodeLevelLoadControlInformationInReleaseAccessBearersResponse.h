/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef SGWSNODELEVELLOADCONTROLINFORMATIONINRELEASEACCESSBEARERSRESPONSE_H_
#define SGWSNODELEVELLOADCONTROLINFORMATIONINRELEASEACCESSBEARERSRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class SgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponse:public GtpV2GroupedIe
{
public:
    SgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponse();
    virtual ~SgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponse();
    bool encodeSgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponse(MsgBuffer &buffer,
                             SgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponseData
                              const &data);

    bool decodeSgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponse (MsgBuffer &buffer,
                             SgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponseData 
                             & data, Uint16 length);

    void displaySgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponseData_v
    (SgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif