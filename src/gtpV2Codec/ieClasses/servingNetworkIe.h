/*
 * servingNetworkIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef SERVINGNETWORKIE_H_
#define SERVINGNETWORKIE_H_

#include "manual/gtpV2Ie.h"



class ServingNetworkIe: public GtpV2Ie {
public:
    ServingNetworkIe();
    virtual ~ServingNetworkIe();

    bool encodeServingNetworkIe(MsgBuffer &buffer,
                 ServingNetworkIeData const &data);
    bool decodeServingNetworkIe(MsgBuffer &buffer,
                 ServingNetworkIeData &data, Uint16 length);
    void displayServingNetworkIe_v(ServingNetworkIeData const &data,
                 Debug &stream);
};

#endif /* SERVINGNETWORKIE_H_ */