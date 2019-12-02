/*
 * servingPlmnRateControlIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef SERVINGPLMNRATECONTROLIE_H_
#define SERVINGPLMNRATECONTROLIE_H_

#include "manual/gtpV2Ie.h"



class ServingPlmnRateControlIe: public GtpV2Ie {
public:
    ServingPlmnRateControlIe();
    virtual ~ServingPlmnRateControlIe();

    bool encodeServingPlmnRateControlIe(MsgBuffer &buffer,
                 ServingPlmnRateControlIeData const &data);
    bool decodeServingPlmnRateControlIe(MsgBuffer &buffer,
                 ServingPlmnRateControlIeData &data, Uint16 length);
    void displayServingPlmnRateControlIe_v(ServingPlmnRateControlIeData const &data,
                 Debug &stream);
};

#endif /* SERVINGPLMNRATECONTROLIE_H_ */