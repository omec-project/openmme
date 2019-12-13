/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef SGWSNODELEVELLOADCONTROLINFORMATIONINDOWNLINKDATANOTIFICATION_H_
#define SGWSNODELEVELLOADCONTROLINFORMATIONINDOWNLINKDATANOTIFICATION_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class SgwsNodeLevelLoadControlInformationInDownlinkDataNotification:public GtpV2GroupedIe
{
public:
    SgwsNodeLevelLoadControlInformationInDownlinkDataNotification();
    virtual ~SgwsNodeLevelLoadControlInformationInDownlinkDataNotification();
    bool encodeSgwsNodeLevelLoadControlInformationInDownlinkDataNotification(MsgBuffer &buffer,
                             SgwsNodeLevelLoadControlInformationInDownlinkDataNotificationData
                              const &data);

    bool decodeSgwsNodeLevelLoadControlInformationInDownlinkDataNotification (MsgBuffer &buffer,
                             SgwsNodeLevelLoadControlInformationInDownlinkDataNotificationData 
                             & data, Uint16 length);

    void displaySgwsNodeLevelLoadControlInformationInDownlinkDataNotificationData_v
    (SgwsNodeLevelLoadControlInformationInDownlinkDataNotificationData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif