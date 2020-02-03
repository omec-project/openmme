/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef SGWSOVERLOADCONTROLINFORMATIONINDOWNLINKDATANOTIFICATION_H_
#define SGWSOVERLOADCONTROLINFORMATIONINDOWNLINKDATANOTIFICATION_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class SgwsOverloadControlInformationInDownlinkDataNotification:public GtpV2GroupedIe
{
public:
    SgwsOverloadControlInformationInDownlinkDataNotification();
    virtual ~SgwsOverloadControlInformationInDownlinkDataNotification();
    bool encodeSgwsOverloadControlInformationInDownlinkDataNotification(MsgBuffer &buffer,
                             SgwsOverloadControlInformationInDownlinkDataNotificationData
                              const &data);

    bool decodeSgwsOverloadControlInformationInDownlinkDataNotification (MsgBuffer &buffer,
                             SgwsOverloadControlInformationInDownlinkDataNotificationData 
                             & data, Uint16 length);

    void displaySgwsOverloadControlInformationInDownlinkDataNotificationData_v
    (SgwsOverloadControlInformationInDownlinkDataNotificationData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif