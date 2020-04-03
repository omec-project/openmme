/*
 * Copyright 2019-present Infosys Limited  
 *   
 * SPDX-License-Identifier: Apache-2.0    
 */

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <basicTypes.h>
#include <msgBuffer.h>

using namespace std;

using namespace cmn::utils;

MsgBuffer::MsgBuffer()
{
	initialize(DEFAULT_BUFF_SIZE);
}

MsgBuffer::MsgBuffer(uint16_t size)
{
	initialize(size);
}

MsgBuffer::~MsgBuffer()
{
	delete data_mp;
}

void MsgBuffer::initialize(uint16_t size)
{
	bufSize = size;
	data_mp = new uint8_t[size];
	memset(data_mp, 0, size);
	bitIndex = 0;
	byteIndex = 0;
	length = 0;
	bitLength = 0;
}

bool MsgBuffer::writeBits(uint8_t data, uint8_t size, bool append)
{

    uint8_t mask = (0xFF >> (8 - size));
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

bool MsgBuffer::writeBytes(uint8_t* data, uint16_t size, bool append)
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

bool MsgBuffer::writeUint8(uint8_t data,  bool append)
{
	return writeBytes(&data, sizeof(uint8_t), append);
}

bool MsgBuffer::writeUint16(uint16_t data,  bool append)
{
	uint16_t localData = htons(data);
	return writeBytes((uint8_t*)&localData, sizeof(uint16_t), append);
}

bool MsgBuffer::writeUint32(uint32_t data,  bool append)
{
	uint32_t localData = htonl(data);
	return writeBytes((uint8_t*)&localData, sizeof(uint32_t), append);
}

bool MsgBuffer::writeUint64(uint64_t data, bool append)
{
	uint64_t localData = htonl(data);
	return writeBytes((uint8_t*)&localData, sizeof(uint64_t), append);
}

bool MsgBuffer::readBit()
{
	uint8_t byteValue = data_mp[byteIndex];
	uint8_t bitMask = 0x80;
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

void MsgBuffer::readUint8(uint8_t &data)
{
	data = data_mp[byteIndex];
	nextByte();
}

bool MsgBuffer::readUint16(uint16_t &data)
{
	if ((byteIndex + sizeof(uint16_t)) <= length)
	{
		memcpy(&data, &data_mp[byteIndex], sizeof(uint16_t));
		data = ntohs(data);
		incrByteIndex(sizeof(uint16_t));
		return true;
	}
	else
	{
		return false;
	}
}

bool MsgBuffer::readUint32(uint32_t &data)
{
	if ((byteIndex + sizeof(uint32_t)) <= length)
	{
		memcpy(&data, &data_mp[byteIndex], sizeof(uint32_t));
		data = ntohl(data);
		incrByteIndex(sizeof(uint32_t));
		return true;
	}
	else
	{
		return false;
	}
}

bool MsgBuffer::readUint64(uint64_t &data)
{
	if ((byteIndex + sizeof(uint64_t)) <= length)
	{
		memcpy(&data, &data_mp[byteIndex], sizeof(uint64_t));
		data = ntohl(data);
		incrByteIndex(sizeof(uint64_t));
		return true;
	}
	else
	{
		return false;
	}
}

uint8_t MsgBuffer::readBits(uint16_t size)
{
	uint8_t data = 0;

	if ((bitIndex + size) > 8)
	{
		cout << "Attempt to read beyond byte boundary";
		return 0;
	}

	uint16_t i;
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


bool MsgBuffer::readBytes(uint8_t* data, uint16_t size)
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

void MsgBuffer::skipBits(uint8_t size)
{
	incrBitIndex(size);
}

void MsgBuffer::skipBytes(uint16_t size)
{
	incrByteIndex(size);
}

void MsgBuffer::display(Debug &stream)
{

}

bool MsgBuffer::incrBitIndex(uint8_t size)
{
    bool rc = false;
    if ((bitIndex + size) <= 8)
    {
    	uint16_t savedBitIndex = bitIndex;
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

bool MsgBuffer::incrByteIndex(uint16_t size)
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

uint16_t MsgBuffer::getLength()
{
       if (bitIndex == 0)
           return length;
       else
           return (length + 1);
}

uint16_t MsgBuffer::getBufferSize()
{
  return bufSize;
}

uint16_t MsgBuffer::getCurrentIndex()
{
       return byteIndex;
}

void MsgBuffer::goToIndex(uint16_t idx)
{
       byteIndex = idx;
}

uint16_t MsgBuffer::lengthLeft()
{
  return (length - byteIndex);
}

uint16_t MsgBuffer::sizeLeft()
{
  return (bufSize - byteIndex);
}

void* MsgBuffer::getDataPointer() 
{
  return data_mp;
}

void MsgBuffer::setLength(uint16_t bufLen)
{
  length = bufLen;
}

uint8_t MsgBuffer::charToHex (uint8_t x)
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

