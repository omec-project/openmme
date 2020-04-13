/*
 * Copyright 2019-present Infosys Limited  
 *   
 * SPDX-License-Identifier: Apache-2.0    
 */

#ifndef MSGBUFFER_H_
#define MSGBUFFER_H_

#include <sstream>
#include <debug.h>

#include <stdint.h>

#define DEFAULT_BUFF_SIZE 1024

using namespace std;
extern cmn::utils::Debug errorStream;
namespace cmn
{
namespace utils
{
class MsgBuffer
{
public:

	MsgBuffer();
	MsgBuffer(uint16_t size);

	~MsgBuffer();


	bool writeBits(uint8_t data, uint8_t size, bool append = true);
	bool writeBytes(uint8_t* data, uint16_t size, bool append = true);
	bool writeUint8(uint8_t data,  bool append = true);
	bool writeUint16(uint16_t data, bool append = true);
	bool writeUint32(uint32_t data, bool append = true);
	bool writeUint64(uint64_t data, bool append = true);

	void display (Debug &stream);

	uint8_t readBits(uint16_t size);
	bool readBytes(uint8_t* data, uint16_t size);

	bool readBit();
	void readUint8(uint8_t &data);
	bool readUint16(uint16_t &data);
	bool readUint32(uint32_t &data);
	bool readUint64(uint64_t &data);
	void reset();
	void rewind();
	void goToEnd();
	void skipBits(uint8_t size);
	void skipBytes(uint16_t size);
    	uint16_t getLength();
	uint16_t getBufferSize();
    	uint16_t getCurrentIndex();
    	void goToIndex(uint16_t idx);

    	uint8_t charToHex(uint8_t x);
    	uint16_t lengthLeft();
    	uint16_t sizeLeft();

    	void* getDataPointer();
    	void setLength(uint16_t bufLen);

private:

	uint8_t* data_mp;
	uint16_t bufSize;
	uint16_t length;
	uint16_t bitLength;
	uint16_t byteIndex;
	uint16_t bitIndex;

	void initialize(uint16_t size);
	bool incrBitIndex(uint8_t size);
	bool incrByteIndex(uint16_t size);
	void nextByte();
};
};
};

using namespace cmn::utils;

#endif /* MSGBUFFER_H_ */

