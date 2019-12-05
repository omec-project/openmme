#ifndef __GtpStackWrappers_H
#define __GtpStackWrappers_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include "msgClasses/gtpV2MsgDataTypes.h"

	typedef struct GtpV2Stack GtpV2Stack;
	typedef struct MsgBuffer MsgBuffer;

	GtpV2Stack* createGtpV2Stack();
	MsgBuffer* createMsgBuffer(uint16_t size);

	void* MsgBuffer_getDataPointer(MsgBuffer* buf_p);

	uint16_t MsgBuffer_getBufLen(MsgBuffer* buf_p);

	void MsgBuffer_reset(MsgBuffer* buf_p);

	bool MsgBuffer_writeBytes(MsgBuffer* msgBuf_p, Uint8* data, Uint16 size, bool append);

	void MsgBuffer_rewind(MsgBuffer* msgBuf_p);

	void MsgBuffer_free(MsgBuffer* buf_p);

	bool GtpV2Stack_decodeMessageHeader(GtpV2Stack* stack_p,
			GtpV2MessageHeader* hdr_p,
			MsgBuffer* msgBuf_p);

	bool GtpV2Stack_decodeMessage(GtpV2Stack* stack_p,
			GtpV2MessageHeader* msgHeader_p,
			MsgBuffer* buffer_p,
            void* data_p);

	bool GtpV2Stack_buildGtpV2Message(GtpV2Stack* stack_p,
						MsgBuffer* buf_p,
						GtpV2MessageHeader* hdr_p,
						void* data_p);

#ifdef __cplusplus
}
#endif
#endif
