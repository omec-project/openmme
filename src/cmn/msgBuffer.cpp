/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#include <arpa/inet.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

#include "basicTypes.h"
#include "msgBuffer.h"

using namespace std;

Debug errorStream; // Need a better place to put this

MsgBuffer::MsgBuffer()
{
	initialize(DEFAULT_BUFF_SIZE);
}



MsgBuffer::MsgBuffer(Uint16 size)
{
	initialize(size);
}


MsgBuffer::~MsgBuffer()
{
	delete data_mp;
}

void MsgBuffer::initialize(Uint16 size)
{
	bufSize = size;
	data_mp = new Uint8[size];
	memset(data_mp, 0, size);
	bitIndex = 0;
	byteIndex = 0;
	length = 0;
	bitLength = 0;
}

bool MsgBuffer::writeBits(Uint8 data, Uint8 size, bool append)
{

        Uint8 mask = (0xFF >> (8 - size));
        data = data & mask;

	if ((bitIndex + size) <= 8)
	{
		if (append)
		{
			goToEnd();
		}

		data_mp[byteIndex] = data_mp[byteIndex] | (data << (8-(bitIndex+size)));
		incrBitIndex(size);

		return true;

	}
	else
	{
		// Attempt to write beyond byte boundary
		return false;
	}
}

bool MsgBuffer::writeBytes(Uint8* data, Uint16 size, bool append)
{
	bool rc = false;
	if (bitIndex == 0)
	{
		if (append)
		{
			goToEnd();
		}

		if ((byteIndex + size) <= bufSize)
		{
			memcpy(&data_mp[byteIndex], data, size);
			rc = incrByteIndex(size);
			if (byteIndex > length)
			{
				length = byteIndex;
			}
		}
	}
	return rc;
}

bool MsgBuffer::writeUint8(Uint8 data,  bool append)
{
	return writeBytes(&data, sizeof(Uint8), append);
}

bool MsgBuffer::writeUint16(Uint16 data,  bool append)
{
	Uint16 localData = htons(data);
	return writeBytes((Uint8*)&localData, sizeof(Uint16), append);
}

bool MsgBuffer::writeUint32(Uint32 data,  bool append)
{
	Uint32 localData = htonl(data);
	return writeBytes((Uint8*)&localData, sizeof(Uint32), append);
}

bool MsgBuffer::writeUint64(Uint64 data, bool append)
{
	Uint64 localData = htonl(data);
	return writeBytes((Uint8*)&localData, sizeof(Uint64), append);
}



bool MsgBuffer::readBit()
{
	Uint8 byteValue = data_mp[byteIndex];
	Uint8 bitMask = 0x80;
	bitMask = bitMask >> bitIndex;

	// Adjust the indices
	incrBitIndex(1);

	if (byteValue & bitMask)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void MsgBuffer::readUint8(Uint8 &data)
{
	data = data_mp[byteIndex];
	nextByte();
}

bool MsgBuffer::readUint16(Uint16 &data)
{
	if ((byteIndex + sizeof(Uint16)) <= length)
	{
		memcpy(&data, &data_mp[byteIndex], sizeof(Uint16));
		data = ntohs(data);
		incrByteIndex(sizeof(Uint16));
		return true;
	}
	else
	{
		return false;
	}
}

bool MsgBuffer::readUint32(Uint32 &data)
{
	if ((byteIndex + sizeof(Uint32)) <= length)
	{
		memcpy(&data, &data_mp[byteIndex], sizeof(Uint32));
		data = ntohl(data);
		incrByteIndex(sizeof(Uint32));
		return true;
	}
	else
	{
		return false;
	}
}

bool MsgBuffer::readUint64(Uint64 &data)
{
	if ((byteIndex + sizeof(Uint64)) <= length)
	{
		memcpy(&data, &data_mp[byteIndex], sizeof(Uint64));
		data = ntohl(data);
		incrByteIndex(sizeof(Uint64));
		return true;
	}
	else
	{
		return false;
	}
}

Uint8 MsgBuffer::readBits(Uint16 size)
{
	Uint8 data = 0;

	if ((bitIndex + size) > 8)
	{
		cout << "Attempt to read beyond byte boundary";
		return 0;
	}

	Uint16 i;
	for (i = 0; i <size; i++)
	{
		data = data << 1;
		if (readBit())
		{
			data = data | 0x0001;
		}
	}
	return data;
}


bool MsgBuffer::readBytes(Uint8* data, Uint16 size)
{
	if ((byteIndex + size) <= length)
	{
		memcpy(data, &data_mp[byteIndex], size);
		byteIndex += size;
		bitIndex   = 0;
		return true;
	}
	else
	{
		return false;
	}


}

void MsgBuffer::rewind()
{
	bitIndex = 0;
	byteIndex = 0;
}

void MsgBuffer::reset()
{
	memset(data_mp, 0, length);
	rewind();
        length = 0;
        bitLength = 0;
}

void MsgBuffer::skipBits(Uint8 size)
{
	incrBitIndex(size);
}

void MsgBuffer::skipBytes(Uint16 size)
{
	incrByteIndex(size);
}

void MsgBuffer::display(Debug &stream)
{

        Uint16 bufLength = getLength();

	// Displays current buffer contents
	stream.add((char *)"Buffer Size: ");
        stream.add(bufLength);
        stream.endOfLine();
	stream.add((char *)"Current Index: ");
        stream.add(byteIndex);
        stream.add((char *)".");
        stream.add(bitIndex);
        stream.endOfLine();
	stream.add((char *)"Data:");
        stream.endOfLine();
        stream.setHexOutput();

        for (Uint16 i = 0; i < bufLength; i++)
        {
    	  stream.add(data_mp[i]);
	  stream.add((char *)" ");
          if (((i+1) % 16) == 0)
          {
            stream.endOfLine();
          }
        }
        stream.unsetHexOutput();
        stream.endOfLine();
}


bool MsgBuffer::incrBitIndex(Uint8 size)
{
    bool rc = false;
    if ((bitIndex + size) <= 8)
    {
    	Uint16 savedBitIndex = bitIndex;
    	bitIndex += size;
        rc = true;
    	if (bitIndex == 8)
    	{
    	  rc = incrByteIndex(1);
          bitIndex = 0;
    	}

    	if (!rc)
    	{
    		bitIndex = savedBitIndex;
    	}
    }
    // adjust the length now
    if ((byteIndex == length)&&(bitIndex > bitLength))
    {
      bitLength = bitIndex;
    }
    else if (byteIndex > length)
    {
      length = byteIndex;
      bitLength = bitIndex;
    }
    return rc;
}




bool MsgBuffer::incrByteIndex(Uint16 size)
{
	if ((byteIndex + size) <= bufSize)
	{
		byteIndex += size;
		return true;
	}
	else
	{
		return false;
	}
}

void MsgBuffer::nextByte()
{
	byteIndex++;
	if (byteIndex > length)
	{
		byteIndex = 0;
	}
	bitIndex = 0;
}

void MsgBuffer::goToEnd()
{
	byteIndex = length;
	bitIndex = bitLength;
}

Uint16 MsgBuffer::getLength()
{
       if (bitIndex == 0)
           return length;
       else
           return (length + 1);
}

Uint16 MsgBuffer::getBufferSize()
{
  return bufSize;
}

Uint16 MsgBuffer::getCurrentIndex()
{
       return byteIndex;
}

void MsgBuffer::goToIndex(Uint16 idx)
{
       byteIndex = idx;
}

Uint16 MsgBuffer::lengthLeft()
{
  return (length - byteIndex);
}

Uint16 MsgBuffer::sizeLeft()
{
  return (bufSize - byteIndex);
}

void* MsgBuffer::getDataPointer()
{
  return data_mp;
}

void MsgBuffer::setLength(Uint16 bufLen)
{
  length = bufLen;
}

Uint8 MsgBuffer::charToHex (Uint8 x)
{
  if ((x >= '0') && (x <= '9'))
  {
    return (x - '0');
  }
  else if ((x >= 'a') && (x <= 'f'))
  {
    return (x - 'a' + 10);
  }
  else if ((x >= 'A') && (x <= 'F'))
  {
    return (x - 'A' + 10);
  }
  else
  {
    return 0;
  }
}





