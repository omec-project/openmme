/*
 * additionalProtocolConfigurationOptionsIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef ADDITIONALPROTOCOLCONFIGURATIONOPTIONSIE_H_
#define ADDITIONALPROTOCOLCONFIGURATIONOPTIONSIE_H_

#include "manual/gtpV2Ie.h"



class AdditionalProtocolConfigurationOptionsIe: public GtpV2Ie {
public:
    AdditionalProtocolConfigurationOptionsIe();
    virtual ~AdditionalProtocolConfigurationOptionsIe();

    bool encodeAdditionalProtocolConfigurationOptionsIe(MsgBuffer &buffer,
                 AdditionalProtocolConfigurationOptionsIeData const &data);
    bool decodeAdditionalProtocolConfigurationOptionsIe(MsgBuffer &buffer,
                 AdditionalProtocolConfigurationOptionsIeData &data, Uint16 length);
    void displayAdditionalProtocolConfigurationOptionsIe_v(AdditionalProtocolConfigurationOptionsIeData const &data,
                 Debug &stream);
};

#endif /* ADDITIONALPROTOCOLCONFIGURATIONOPTIONSIE_H_ */