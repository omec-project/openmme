/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef PGWSNODELEVELLOADCONTROLINFORMATIONINCREATESESSIONRESPONSE_H_
#define PGWSNODELEVELLOADCONTROLINFORMATIONINCREATESESSIONRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class PgwsNodeLevelLoadControlInformationInCreateSessionResponse:public GtpV2GroupedIe
{
public:
    PgwsNodeLevelLoadControlInformationInCreateSessionResponse();
    virtual ~PgwsNodeLevelLoadControlInformationInCreateSessionResponse();
    bool encodePgwsNodeLevelLoadControlInformationInCreateSessionResponse(MsgBuffer &buffer,
                             PgwsNodeLevelLoadControlInformationInCreateSessionResponseData
                              const &data);

    bool decodePgwsNodeLevelLoadControlInformationInCreateSessionResponse (MsgBuffer &buffer,
                             PgwsNodeLevelLoadControlInformationInCreateSessionResponseData 
                             & data, Uint16 length);

    void displayPgwsNodeLevelLoadControlInformationInCreateSessionResponseData_v
    (PgwsNodeLevelLoadControlInformationInCreateSessionResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif