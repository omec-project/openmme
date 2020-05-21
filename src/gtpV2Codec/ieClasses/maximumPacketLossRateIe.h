/*
 * maximumPacketLossRateIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef MAXIMUMPACKETLOSSRATEIE_H_
#define MAXIMUMPACKETLOSSRATEIE_H_

#include "manual/gtpV2Ie.h"



class MaximumPacketLossRateIe: public GtpV2Ie {
public:
    MaximumPacketLossRateIe();
    virtual ~MaximumPacketLossRateIe();

    bool encodeMaximumPacketLossRateIe(MsgBuffer &buffer,
                 MaximumPacketLossRateIeData const &data);
    bool decodeMaximumPacketLossRateIe(MsgBuffer &buffer,
                 MaximumPacketLossRateIeData &data, Uint16 length);
    void displayMaximumPacketLossRateIe_v(MaximumPacketLossRateIeData const &data,
                 Debug &stream);
};

#endif /* MAXIMUMPACKETLOSSRATEIE_H_ */