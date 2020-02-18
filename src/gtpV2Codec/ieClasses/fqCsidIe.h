/*
 * fqCsidIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef FQCSIDIE_H_
#define FQCSIDIE_H_

#include "manual/gtpV2Ie.h"



class FqCsidIe: public GtpV2Ie {
public:
    FqCsidIe();
    virtual ~FqCsidIe();

    bool encodeFqCsidIe(MsgBuffer &buffer,
                 FqCsidIeData const &data);
    bool decodeFqCsidIe(MsgBuffer &buffer,
                 FqCsidIeData &data, Uint16 length);
    void displayFqCsidIe_v(FqCsidIeData const &data,
                 Debug &stream);
};

#endif /* FQCSIDIE_H_ */