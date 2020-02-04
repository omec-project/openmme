/*
 * remoteUserIdIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef REMOTEUSERIDIE_H_
#define REMOTEUSERIDIE_H_

#include "manual/gtpV2Ie.h"



class RemoteUserIdIe: public GtpV2Ie {
public:
    RemoteUserIdIe();
    virtual ~RemoteUserIdIe();

    bool encodeRemoteUserIdIe(MsgBuffer &buffer,
                 RemoteUserIdIeData const &data);
    bool decodeRemoteUserIdIe(MsgBuffer &buffer,
                 RemoteUserIdIeData &data, Uint16 length);
    void displayRemoteUserIdIe_v(RemoteUserIdIeData const &data,
                 Debug &stream);
};

#endif /* REMOTEUSERIDIE_H_ */