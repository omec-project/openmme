/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 


#ifndef DATATYPECODECUTILS_H_
#define DATATYPECODECUTILS_H_

#include <sstream>
#include <msgBuffer.h>
#include "gtpV2IeDataTypes.h"
#include "gtpV2DataTypes.h"
#include "manual/gtpV2DataTypes_Manual.h"

//TODO Includes

class DataTypeCodecUtils {
public:
    DataTypeCodecUtils();
    virtual ~DataTypeCodecUtils();


    static bool encodeCgiField(MsgBuffer &buffer, CgiField const &data);
    static bool decodeCgiField(MsgBuffer &buffer, CgiField &data,
                 Uint16 length);
    static void displayCgiField_v(CgiField const &data, Debug &stream);

    static bool encodeOffendingIeData(MsgBuffer &buffer, OffendingIeData const &data);
    static bool decodeOffendingIeData(MsgBuffer &buffer, OffendingIeData &data,
                 Uint16 length);
    static void displayOffendingIeData_v(OffendingIeData const &data, Debug &stream);

    static bool encodeSaiField(MsgBuffer &buffer, SaiField const &data);
    static bool decodeSaiField(MsgBuffer &buffer, SaiField &data,
                 Uint16 length);
    static void displaySaiField_v(SaiField const &data, Debug &stream);

    static bool encodeRaiField(MsgBuffer &buffer, RaiField const &data);
    static bool decodeRaiField(MsgBuffer &buffer, RaiField &data,
                 Uint16 length);
    static void displayRaiField_v(RaiField const &data, Debug &stream);

    static bool encodeTaiField(MsgBuffer &buffer, TaiField const &data);
    static bool decodeTaiField(MsgBuffer &buffer, TaiField &data,
                 Uint16 length);
    static void displayTaiField_v(TaiField const &data, Debug &stream);

    static bool encodeEcgiField(MsgBuffer &buffer, EcgiField const &data);
    static bool decodeEcgiField(MsgBuffer &buffer, EcgiField &data,
                 Uint16 length);
    static void displayEcgiField_v(EcgiField const &data, Debug &stream);

    static bool encodeLaiField(MsgBuffer &buffer, LaiField const &data);
    static bool decodeLaiField(MsgBuffer &buffer, LaiField &data,
                 Uint16 length);
    static void displayLaiField_v(LaiField const &data, Debug &stream);

    static bool encodeIpAddressV4(MsgBuffer &buffer, IpAddressV4 const &data);
    static bool decodeIpAddressV4(MsgBuffer &buffer, IpAddressV4 &data,
                 Uint16 length);
    static void displayIpAddressV4_v(IpAddressV4 const &data, Debug &stream);

    static bool encodeIpAddressV6(MsgBuffer &buffer, IpAddressV6 const &data);
    static bool decodeIpAddressV6(MsgBuffer &buffer, IpAddressV6 &data,
                 Uint16 length);
    static void displayIpAddressV6_v(IpAddressV6 const &data, Debug &stream);


    // The following methods are generated to encode, decode and display array types

    static bool encodeUint16Array16(MsgBuffer &buffer, Uint16Array16 const &data);
    static bool decodeUint16Array16(MsgBuffer &buffer, Uint16Array16 &data,
                 Uint16 length, Uint16 count);
    static void displayUint16Array16_v(Uint16Array16 const &data, Debug &stream);


    static bool encodeUint8Array16(MsgBuffer &buffer, Uint8Array16 const &data);
    static bool decodeUint8Array16(MsgBuffer &buffer, Uint8Array16 &data,
                 Uint16 length, Uint16 count);
    static void displayUint8Array16_v(Uint8Array16 const &data, Debug &stream);


    static bool encodeUint8Array32(MsgBuffer &buffer, Uint8Array32 const &data);
    static bool decodeUint8Array32(MsgBuffer &buffer, Uint8Array32 &data,
                 Uint16 length, Uint16 count);
    static void displayUint8Array32_v(Uint8Array32 const &data, Debug &stream);


    static bool encodeUint8Array5(MsgBuffer &buffer, Uint8Array5 const &data);
    static bool decodeUint8Array5(MsgBuffer &buffer, Uint8Array5 &data,
                 Uint16 length, Uint16 count);
    static void displayUint8Array5_v(Uint8Array5 const &data, Debug &stream);


    static bool encodeUint8Array4(MsgBuffer &buffer, Uint8Array4 const &data);
    static bool decodeUint8Array4(MsgBuffer &buffer, Uint8Array4 &data,
                 Uint16 length, Uint16 count);
    static void displayUint8Array4_v(Uint8Array4 const &data, Debug &stream);


    static bool encodeUint8Array512(MsgBuffer &buffer, Uint8Array512 const &data);
    static bool decodeUint8Array512(MsgBuffer &buffer, Uint8Array512 &data,
                 Uint16 length, Uint16 count);
    static void displayUint8Array512_v(Uint8Array512 const &data, Debug &stream);


    static bool encodeUint8Array255(MsgBuffer &buffer, Uint8Array255 const &data);
    static bool decodeUint8Array255(MsgBuffer &buffer, Uint8Array255 &data,
                 Uint16 length, Uint16 count);
    static void displayUint8Array255_v(Uint8Array255 const &data, Debug &stream);


    static bool encodeCgiFieldArray64(MsgBuffer &buffer, CgiFieldArray64 const &data);
    static bool decodeCgiFieldArray64(MsgBuffer &buffer, CgiFieldArray64 &data,
                 Uint16 length, Uint16 count);
    static void displayCgiFieldArray64_v(CgiFieldArray64 const &data, Debug &stream);


    static bool encodeSaiFieldArray64(MsgBuffer &buffer, SaiFieldArray64 const &data);
    static bool decodeSaiFieldArray64(MsgBuffer &buffer, SaiFieldArray64 &data,
                 Uint16 length, Uint16 count);
    static void displaySaiFieldArray64_v(SaiFieldArray64 const &data, Debug &stream);


    static bool encodeEcgiFieldArray64(MsgBuffer &buffer, EcgiFieldArray64 const &data);
    static bool decodeEcgiFieldArray64(MsgBuffer &buffer, EcgiFieldArray64 &data,
                 Uint16 length, Uint16 count);
    static void displayEcgiFieldArray64_v(EcgiFieldArray64 const &data, Debug &stream);


    static bool encodeTaiFieldArray15(MsgBuffer &buffer, TaiFieldArray15 const &data);
    static bool decodeTaiFieldArray15(MsgBuffer &buffer, TaiFieldArray15 &data,
                 Uint16 length, Uint16 count);
    static void displayTaiFieldArray15_v(TaiFieldArray15 const &data, Debug &stream);


    static bool encodeRaiFieldArray15(MsgBuffer &buffer, RaiFieldArray15 const &data);
    static bool decodeRaiFieldArray15(MsgBuffer &buffer, RaiFieldArray15 &data,
                 Uint16 length, Uint16 count);
    static void displayRaiFieldArray15_v(RaiFieldArray15 const &data, Debug &stream);


    // The following methods are to be written manually
    // See DataTypeCodecUtils_Manual.cc for implementation

    static bool encodeDigitRegister(MsgBuffer &buffer, DigitRegister const &data);
    static bool decodeDigitRegister(MsgBuffer &buffer, DigitRegister &data,
                 Uint16 length);
    static void displayDigitRegister_v(DigitRegister const &data, Debug &stream);

         
};

#endif /*DATATYPECODECUTILS_H_*/