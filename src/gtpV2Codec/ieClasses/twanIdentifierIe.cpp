/*
 * twanIdentifierIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "twanIdentifierIe.h"
#include "dataTypeCodecUtils.h"

TwanIdentifierIe::TwanIdentifierIe() 
{
    ieType = 169;
    // TODO

}

TwanIdentifierIe::~TwanIdentifierIe() {
    // TODO Auto-generated destructor stub
}

bool TwanIdentifierIe::encodeTwanIdentifierIe(MsgBuffer &buffer, TwanIdentifierIeData const &data)
{
    buffer.skipBits(2);

    if(!(buffer.writeBits(data.laiipresent, 1)))
    {
        errorStream.add("Encoding of laiipresent failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.opnaipresent, 1)))
    {
        errorStream.add("Encoding of opnaipresent failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.plmnipresent, 1)))
    {
        errorStream.add("Encoding of plmnipresent failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.civaipresent, 1)))
    {
        errorStream.add("Encoding of civaipresent failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.bssidipresent, 2)))
    {
        errorStream.add("Encoding of bssidipresent failed\n");
        return false;
    }
    if (!(buffer.writeUint64(data.ssidLength)))
    {
        errorStream.add("Encoding of ssidLength failed\n");
        return false;
    }
    if ( data.ssidLength <=32)
    {
        if (!(buffer.writeUint8(data.ssid)))
        {
    errorStream.add("Encoding of ssid failed\n");
    return false;
        }
    }
    if (data.bssidipresent)
    {
        if (!(buffer.writeUint8(data.bssid)))
        {
    errorStream.add("Encoding of bssid failed\n");
    return false;
        }
    }
    if (data.civaipresent)
    {
        if (!(buffer.writeUint8(data.civicAddressLength)))
        {
    errorStream.add("Encoding of civicAddressLength failed\n");
    return false;
        }
    }
    if (data.civaipresent)
    {
        if (!(buffer.writeUint8(data.civicAddressInformation)))
        {
    errorStream.add("Encoding of civicAddressInformation failed\n");
    return false;
        }
    }
    if (data.plmnipresent)
    {
        if (!(buffer.writeUint8(data.twanplmnid)))
        {
    errorStream.add("Encoding of twanplmnid failed\n");
    return false;
        }
    }
    if (data.opnaipresent)
    {
        if (!(buffer.writeUint8(data.twanOperatorNameLength)))
        {
    errorStream.add("Encoding of twanOperatorNameLength failed\n");
    return false;
        }
    }
    if (data.opnaipresent)
    {
        if (!(buffer.writeUint8(data.twanOperatorName)))
        {
    errorStream.add("Encoding of twanOperatorName failed\n");
    return false;
        }
    }
    if (data.laiipresent)
    {
        if (!(buffer.writeUint8(data.relayIdentityType)))
        {
    errorStream.add("Encoding of relayIdentityType failed\n");
    return false;
        }
    }
    if (data.laiipresent)
    {
        if (!(buffer.writeUint8(data.relayIdentityLength)))
        {
    errorStream.add("Encoding of relayIdentityLength failed\n");
    return false;
        }
    }
    if (data.laiipresent)
    {
        if (!(buffer.writeUint8(data.relayIdentity)))
        {
    errorStream.add("Encoding of relayIdentity failed\n");
    return false;
        }
    }
    if (data.laiipresent)
    {
        if (!(buffer.writeUint8(data.circuitIDLength)))
        {
    errorStream.add("Encoding of circuitIDLength failed\n");
    return false;
        }
    }
    if (data.laiipresent)
    {
        if (!(buffer.writeUint8(data.circuitID)))
        {
    errorStream.add("Encoding of circuitID failed\n");
    return false;
        }
    }

    return true;
}

bool TwanIdentifierIe::decodeTwanIdentifierIe(MsgBuffer &buffer, TwanIdentifierIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    buffer.skipBits(2);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.laiipresent = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: laiipresent\n");
        return false;
    }
    data.opnaipresent = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: opnaipresent\n");
        return false;
    }
    data.plmnipresent = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: plmnipresent\n");
        return false;
    }
    data.civaipresent = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: civaipresent\n");
        return false;
    }
    data.bssidipresent = buffer.readBits(2);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: bssidipresent\n");
        return false;
    }

    buffer.readUint64(data.ssidLength);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: ssidLength\n");
        return false;
    }

    buffer.readUint8(data.ssid);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: ssid\n");
        return false;
    }

    buffer.readUint8(data.bssid);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: bssid\n");
        return false;
    }

    buffer.readUint8(data.civicAddressLength);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: civicAddressLength\n");
        return false;
    }

    buffer.readUint8(data.civicAddressInformation);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: civicAddressInformation\n");
        return false;
    }

    buffer.readUint8(data.twanplmnid);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: twanplmnid\n");
        return false;
    }

    buffer.readUint8(data.twanOperatorNameLength);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: twanOperatorNameLength\n");
        return false;
    }

    buffer.readUint8(data.twanOperatorName);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: twanOperatorName\n");
        return false;
    }

    buffer.readUint8(data.relayIdentityType);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: relayIdentityType\n");
        return false;
    }

    buffer.readUint8(data.relayIdentityLength);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: relayIdentityLength\n");
        return false;
    }

    buffer.readUint8(data.relayIdentity);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: relayIdentity\n");
        return false;
    }

    buffer.readUint8(data.circuitIDLength);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: circuitIDLength\n");
        return false;
    }

    buffer.readUint8(data.circuitID);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: circuitID\n");
        return false;
    }

    // The IE is decoded now. The buffer index should be pointing to the 
    // IE Boundary. If not, we have some more data left for the IE which we don't know
    // how to decode
    if (ieBoundary == buffer.getCurrentIndex())
    {
        return true;
    }
    else
    {
        errorStream.add("Unable to decode IE TwanIdentifierIe\n");
        return false;
    }
}
void TwanIdentifierIe::displayTwanIdentifierIe_v(TwanIdentifierIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("TwanIdentifierIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( "laiipresent: "); 
    stream.add((Uint8)data.laiipresent);
    stream.endOfLine();
  
    stream.add( "opnaipresent: "); 
    stream.add((Uint8)data.opnaipresent);
    stream.endOfLine();
  
    stream.add( "plmnipresent: "); 
    stream.add((Uint8)data.plmnipresent);
    stream.endOfLine();
  
    stream.add( "civaipresent: "); 
    stream.add((Uint8)data.civaipresent);
    stream.endOfLine();
  
    stream.add( "bssidipresent: "); 
    stream.add((Uint8)data.bssidipresent);
    stream.endOfLine();
  
    stream.add("ssidLength: ");
    stream.add(data.ssidLength);
    stream.endOfLine();
  
    if ( data.ssidLength <=32)
    {
        stream.add("ssid: ");
        stream.add(data.ssid);
        stream.endOfLine();
    }
  
    if (data.bssidipresent)
    {
        stream.add("bssid: ");
        stream.add(data.bssid);
        stream.endOfLine();
    }
  
    if (data.civaipresent)
    {
        stream.add("civicAddressLength: ");
        stream.add(data.civicAddressLength);
        stream.endOfLine();
    }
  
    if (data.civaipresent)
    {
        stream.add("civicAddressInformation: ");
        stream.add(data.civicAddressInformation);
        stream.endOfLine();
    }
  
    if (data.plmnipresent)
    {
        stream.add("twanplmnid: ");
        stream.add(data.twanplmnid);
        stream.endOfLine();
    }
  
    if (data.opnaipresent)
    {
        stream.add("twanOperatorNameLength: ");
        stream.add(data.twanOperatorNameLength);
        stream.endOfLine();
    }
  
    if (data.opnaipresent)
    {
        stream.add("twanOperatorName: ");
        stream.add(data.twanOperatorName);
        stream.endOfLine();
    }
  
    if (data.laiipresent)
    {
        stream.add("relayIdentityType: ");
        stream.add(data.relayIdentityType);
        stream.endOfLine();
    }
  
    if (data.laiipresent)
    {
        stream.add("relayIdentityLength: ");
        stream.add(data.relayIdentityLength);
        stream.endOfLine();
    }
  
    if (data.laiipresent)
    {
        stream.add("relayIdentity: ");
        stream.add(data.relayIdentity);
        stream.endOfLine();
    }
  
    if (data.laiipresent)
    {
        stream.add("circuitIDLength: ");
        stream.add(data.circuitIDLength);
        stream.endOfLine();
    }
  
    if (data.laiipresent)
    {
        stream.add("circuitID: ");
        stream.add(data.circuitID);
        stream.endOfLine();
    }
    stream.decrIndent();
    stream.decrIndent();
}
