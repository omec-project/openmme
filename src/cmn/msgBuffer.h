/*
* Copyright (c) 2019 Infosys Limited
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef MSGBUFFER_H_
#define MSGBUFFER_H_

#include <sstream>
#include "basicTypes.h"
#include "debug.h"

#define DEFAULT_BUFF_SIZE 1024

using namespace std;

extern Debug errorStream;

class MsgBuffer {
public:
	MsgBuffer();
	MsgBuffer(Uint16 size);

	~MsgBuffer();


	bool writeBits(Uint8 data, Uint8 size, bool append = true);
	bool writeBytes(Uint8* data, Uint16 size, bool append = true);
	bool writeUint8(Uint8 data,  bool append = true);
	bool writeUint16(Uint16 data, bool append = true);
	bool writeUint32(Uint32 data, bool append = true);
	bool writeUint64(Uint64 data, bool append = true);

	void display (Debug &stream);

	Uint8 readBits(Uint16 size);
	bool readBytes(Uint8* data, Uint16 size);

	bool readBit();
	void readUint8(Uint8 &data);
	bool readUint16(Uint16 &data);
	bool readUint32(Uint32 &data);
	bool readUint64(Uint64 &data);
	void reset();
	void rewind();
	void goToEnd();
	void skipBits(Uint8 size);
	void skipBytes(Uint16 size);
        Uint16 getLength();
        Uint16 getBufferSize();
        Uint16 getCurrentIndex();
        void goToIndex(Uint16 idx);

        Uint8 charToHex(Uint8 x); // TODO move this out
        Uint16 lengthLeft();
        Uint16 sizeLeft();

        void* getDataPointer();  // TODO make it a friend of socket
        void setLength(Uint16 bufLen); // TODO make it a friend of socket

private:
	Uint8* data_mp;
	Uint16 bufSize;
	Uint16 length;
	Uint16 bitLength;
	Uint16 byteIndex;
	Uint16 bitIndex;

	void initialize(Uint16 size);
	bool incrBitIndex(Uint8 size);
	bool incrByteIndex(Uint16 size);
	void nextByte();

};

#endif /* MSGBUFFER_H_ */
