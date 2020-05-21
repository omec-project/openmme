#include "gtpV2Stack.h"
#include "msgBuffer.h"
#include "gtpV2StackWrappers.h"

extern "C" 
{
        GtpV2Stack* createGtpV2Stack() 
        {
        	return new GtpV2Stack();
        }

        MsgBuffer* createMsgBuffer(uint16_t size)
        {
        	return new MsgBuffer();
        }
        
        void MsgBuffer_free(MsgBuffer* buf_p)
        {
        	delete  buf_p;
        }

        void* MsgBuffer_getDataPointer(MsgBuffer* buf_p)
        {
        	return buf_p->getDataPointer();
        }

        uint16_t MsgBuffer_getBufLen(MsgBuffer* buf_p)
        {
        	return buf_p->getLength();
        }

        void MsgBuffer_reset(MsgBuffer* buf_p)
        {
        	return buf_p->reset();
        }

        bool MsgBuffer_writeBytes(MsgBuffer* msgBuf_p, Uint8* data, Uint16 size, bool append)
        {
        	return msgBuf_p->writeBytes(data, size, append);
        }

        void MsgBuffer_rewind(MsgBuffer* msgBuf_p)
        {
        	return msgBuf_p->rewind();
        }

        bool GtpV2Stack_buildGtpV2Message(
            GtpV2Stack* stack_p,
            MsgBuffer* buf_p,
            GtpV2MessageHeader* msgHeader_p,
            void* data_p)
        {
        	bool rc = stack_p->encodeMessage(*msgHeader_p, *buf_p, data_p);
        	if (rc == false)
        	{
        		errorStream.printDebugStream();
        	} else
        	{
        		cout << "GTP Encode Success" << endl;
        	}
        	return rc;
        }

        bool GtpV2Stack_decodeMessageHeader(GtpV2Stack* stack_p, GtpV2MessageHeader* hdr_p, MsgBuffer* msgBuf_p)
        {
        	return stack_p->decodeGtpMessageHeader(*hdr_p, *msgBuf_p);
        }

    	bool GtpV2Stack_decodeMessage(GtpV2Stack* stack_p,
    			GtpV2MessageHeader* msgHeader,
    			MsgBuffer* buffer,
                void* data_p)
    	{
        	bool rc = stack_p->decodeMessage(*msgHeader, *buffer, data_p);
        	if (rc == false)
        	{
        		errorStream.printDebugStream();
        	} else
        	{
        		cout << "GTP Decode Success" << endl;
        	}
        	return rc;
    	}

}
