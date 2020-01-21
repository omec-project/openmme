/*
 * gtpV2Stack.cpp
 *
 *  Created on: Jul 11, 2014
 *      Author: hariharanb
 */
#include <cstring>
#include <stdint.h>
#include "gtpV2Stack.h"
#include "msgClasses/gtpV2MsgFactory.h"
#include "msgClasses/manual/gtpV2Message.h"
#include "msgClasses/createSessionRequestMsg.h"
#include "msgClasses/createSessionResponseMsg.h"
#include "msgClasses/modifyBearerRequestMsg.h"
#include "msgClasses/modifyBearerResponseMsg.h"
#include "msgClasses/deleteSessionRequestMsg.h"
#include "msgClasses/deleteSessionResponseMsg.h"
#include "msgClasses/releaseAccessBearersRequestMsg.h"
#include "msgClasses/releaseAccessBearersResponseMsg.h"
#include "msgClasses/downlinkDataNotificationMsg.h"
#include "msgClasses/downlinkDataNotificationAcknowledgeMsg.h"
#include "msgClasses/downlinkDataNotificationFailureIndicationMsg.h"


GtpV2Stack::GtpV2Stack ()
{
    // TODO Auto-generated constructor stub

}

GtpV2Stack::~GtpV2Stack ()
{
    // TODO Auto-generated destructor stub
}

bool
GtpV2Stack::encodeMessage (GtpV2MessageHeader & msgHeader, 
			   MsgBuffer & buffer, void *data_p)
{

    //Clear the global errorStream
    errorStream.clearStream ();
    bool rc = false;
    GtpV2Message & msg =
    GtpV2MsgFactory::getInstance ().getMsgObject (msgHeader.msgType);

    uint16_t gtpHeaderStartIdx = buffer.getCurrentIndex();

    // Encode the header
    GtpV2Message::encodeHeader (buffer, msgHeader);

    Uint16 startIndex = buffer.getCurrentIndex();

    switch (msgHeader.msgType)
    {
        case CreateSessionRequestMsgType:
        {
            if (data_p != NULL)
            {
                rc =
               dynamic_cast<
               CreateSessionRequestMsg & >(msg).
               encodeCreateSessionRequestMsg(buffer,
    			     *((CreateSessionRequestMsgData *)
        			     data_p));
            }
            else
            { 
                // Application has filled the data structure provided by the stack
                rc = 
                dynamic_cast<
                CreateSessionRequestMsg & >(msg).
                encodeCreateSessionRequestMsg (buffer,
                            createSessionRequestStackData);
            }
            break;
        }
        case CreateSessionResponseMsgType:
        {
            if (data_p != NULL)
            {
                rc =
               dynamic_cast<
               CreateSessionResponseMsg & >(msg).
               encodeCreateSessionResponseMsg(buffer,
    			     *((CreateSessionResponseMsgData *)
        			     data_p));
            }
            else
            { 
                // Application has filled the data structure provided by the stack
                rc = 
                dynamic_cast<
                CreateSessionResponseMsg & >(msg).
                encodeCreateSessionResponseMsg (buffer,
                            createSessionResponseStackData);
            }
            break;
        }
        case ModifyBearerRequestMsgType:
        {
            if (data_p != NULL)
            {
                rc =
               dynamic_cast<
               ModifyBearerRequestMsg & >(msg).
               encodeModifyBearerRequestMsg(buffer,
    			     *((ModifyBearerRequestMsgData *)
        			     data_p));
            }
            else
            { 
                // Application has filled the data structure provided by the stack
                rc = 
                dynamic_cast<
                ModifyBearerRequestMsg & >(msg).
                encodeModifyBearerRequestMsg (buffer,
                            modifyBearerRequestStackData);
            }
            break;
        }
        case ModifyBearerResponseMsgType:
        {
            if (data_p != NULL)
            {
                rc =
               dynamic_cast<
               ModifyBearerResponseMsg & >(msg).
               encodeModifyBearerResponseMsg(buffer,
    			     *((ModifyBearerResponseMsgData *)
        			     data_p));
            }
            else
            { 
                // Application has filled the data structure provided by the stack
                rc = 
                dynamic_cast<
                ModifyBearerResponseMsg & >(msg).
                encodeModifyBearerResponseMsg (buffer,
                            modifyBearerResponseStackData);
            }
            break;
        }
        case DeleteSessionRequestMsgType:
        {
            if (data_p != NULL)
            {
                rc =
               dynamic_cast<
               DeleteSessionRequestMsg & >(msg).
               encodeDeleteSessionRequestMsg(buffer,
    			     *((DeleteSessionRequestMsgData *)
        			     data_p));
            }
            else
            { 
                // Application has filled the data structure provided by the stack
                rc = 
                dynamic_cast<
                DeleteSessionRequestMsg & >(msg).
                encodeDeleteSessionRequestMsg (buffer,
                            deleteSessionRequestStackData);
            }
            break;
        }
        case DeleteSessionResponseMsgType:
        {
            if (data_p != NULL)
            {
                rc =
               dynamic_cast<
               DeleteSessionResponseMsg & >(msg).
               encodeDeleteSessionResponseMsg(buffer,
    			     *((DeleteSessionResponseMsgData *)
        			     data_p));
            }
            else
            { 
                // Application has filled the data structure provided by the stack
                rc = 
                dynamic_cast<
                DeleteSessionResponseMsg & >(msg).
                encodeDeleteSessionResponseMsg (buffer,
                            deleteSessionResponseStackData);
            }
            break;
        }
        case ReleaseAccessBearersRequestMsgType:
        {
            if (data_p != NULL)
            {
                rc =
               dynamic_cast<
               ReleaseAccessBearersRequestMsg & >(msg).
               encodeReleaseAccessBearersRequestMsg(buffer,
    			     *((ReleaseAccessBearersRequestMsgData *)
        			     data_p));
            }
            else
            { 
                // Application has filled the data structure provided by the stack
                rc = 
                dynamic_cast<
                ReleaseAccessBearersRequestMsg & >(msg).
                encodeReleaseAccessBearersRequestMsg (buffer,
                            releaseAccessBearersRequestStackData);
            }
            break;
        }
        case ReleaseAccessBearersResponseMsgType:
        {
            if (data_p != NULL)
            {
                rc =
               dynamic_cast<
               ReleaseAccessBearersResponseMsg & >(msg).
               encodeReleaseAccessBearersResponseMsg(buffer,
    			     *((ReleaseAccessBearersResponseMsgData *)
        			     data_p));
            }
            else
            { 
                // Application has filled the data structure provided by the stack
                rc = 
                dynamic_cast<
                ReleaseAccessBearersResponseMsg & >(msg).
                encodeReleaseAccessBearersResponseMsg (buffer,
                            releaseAccessBearersResponseStackData);
            }
            break;
        }
        case DownlinkDataNotificationMsgType:
        {
            if (data_p != NULL)
            {
                rc =
               dynamic_cast<
               DownlinkDataNotificationMsg & >(msg).
               encodeDownlinkDataNotificationMsg(buffer,
    			     *((DownlinkDataNotificationMsgData *)
        			     data_p));
            }
            else
            { 
                // Application has filled the data structure provided by the stack
                rc = 
                dynamic_cast<
                DownlinkDataNotificationMsg & >(msg).
                encodeDownlinkDataNotificationMsg (buffer,
                            downlinkDataNotificationStackData);
            }
            break;
        }
        case DownlinkDataNotificationAcknowledgeMsgType:
        {
            if (data_p != NULL)
            {
                rc =
               dynamic_cast<
               DownlinkDataNotificationAcknowledgeMsg & >(msg).
               encodeDownlinkDataNotificationAcknowledgeMsg(buffer,
    			     *((DownlinkDataNotificationAcknowledgeMsgData *)
        			     data_p));
            }
            else
            { 
                // Application has filled the data structure provided by the stack
                rc = 
                dynamic_cast<
                DownlinkDataNotificationAcknowledgeMsg & >(msg).
                encodeDownlinkDataNotificationAcknowledgeMsg (buffer,
                            downlinkDataNotificationAcknowledgeStackData);
            }
            break;
        }
        case DownlinkDataNotificationFailureIndicationMsgType:
        {
            if (data_p != NULL)
            {
                rc =
               dynamic_cast<
               DownlinkDataNotificationFailureIndicationMsg & >(msg).
               encodeDownlinkDataNotificationFailureIndicationMsg(buffer,
    			     *((DownlinkDataNotificationFailureIndicationMsgData *)
        			     data_p));
            }
            else
            { 
                // Application has filled the data structure provided by the stack
                rc = 
                dynamic_cast<
                DownlinkDataNotificationFailureIndicationMsg & >(msg).
                encodeDownlinkDataNotificationFailureIndicationMsg (buffer,
                            downlinkDataNotificationFailureIndicationStackData);
            }
            break;
        }
    }

    Uint16 endIndex = buffer.getCurrentIndex ();

    Uint16 messageLength = (endIndex - startIndex) + 8;


    buffer.goToIndex (gtpHeaderStartIdx + 2); // 2 is where length is encoded in a gtp message TODO remove hardcoding
    buffer.writeUint16 (messageLength, false);
    buffer.goToIndex (endIndex);
    return rc;
}

bool
GtpV2Stack::decodeGtpMessageHeader(GtpV2MessageHeader& msgHeader, MsgBuffer& buffer)
{
	 return GtpV2Message::decodeHeader (buffer, msgHeader);
}


bool
GtpV2Stack::decodeMessage (GtpV2MessageHeader& msgHeader, 
                MsgBuffer& buffer,void* data_p)
{
    errorStream.clearStream();
    // First decode the message header
    bool rc = false;
    
    Uint16 msgDataLength = msgHeader.msgLength;
    
    if (msgHeader.teidPresent)
    {
        msgDataLength = msgDataLength - 8; //teid and sequence number
    }
    else
    {
        msgDataLength = msgDataLength - 4; //only sequence number
    }
  
    // Validate the length before proceeding
    if (msgDataLength != buffer.lengthLeft() )
    {
        // Encoded message length does not match the number of bytes left in the message
        errorStream.add ((char*)"Message length does not match bytes in buffer\n");
        errorStream.add ((char*)"Computed Message length: ");
        errorStream.add (msgDataLength);
        errorStream.add ((char*)"  Bytes Left in buffer: ");
        errorStream.add (buffer.lengthLeft());
        errorStream.endOfLine ();
        return false;
    }

    GtpV2Message& msg = 
    GtpV2MsgFactory::getInstance ().getMsgObject (msgHeader.msgType);

    switch (msgHeader.msgType){
        case CreateSessionRequestMsgType:
        {
            if (data_p != NULL)
            {
                rc =
                dynamic_cast<
                CreateSessionRequestMsg & >(msg).
                decodeCreateSessionRequestMsg(buffer,
                            *(CreateSessionRequestMsgData*)
                             data_p, msgDataLength);
            }
            else
            { 
                // Application wants to use the data structure provided by the stack
                // let us first clear any data present in the internal data structure
                memset (&createSessionRequestStackData, 0,
                sizeof (CreateSessionRequestMsgData));
                rc =
                dynamic_cast<
                CreateSessionRequestMsg & >(msg).
                decodeCreateSessionRequestMsg(buffer,
                            createSessionRequestStackData,
                            msgDataLength);
            }
            break;
        }
        case CreateSessionResponseMsgType:
        {
            if (data_p != NULL)
            {
                rc =
                dynamic_cast<
                CreateSessionResponseMsg & >(msg).
                decodeCreateSessionResponseMsg(buffer,
                            *(CreateSessionResponseMsgData*)
                             data_p, msgDataLength);
            }
            else
            { 
                // Application wants to use the data structure provided by the stack
                // let us first clear any data present in the internal data structure
                memset (&createSessionResponseStackData, 0,
                sizeof (CreateSessionResponseMsgData));
                rc =
                dynamic_cast<
                CreateSessionResponseMsg & >(msg).
                decodeCreateSessionResponseMsg(buffer,
                            createSessionResponseStackData,
                            msgDataLength);
            }
            break;
        }
        case ModifyBearerRequestMsgType:
        {
            if (data_p != NULL)
            {
                rc =
                dynamic_cast<
                ModifyBearerRequestMsg & >(msg).
                decodeModifyBearerRequestMsg(buffer,
                            *(ModifyBearerRequestMsgData*)
                             data_p, msgDataLength);
            }
            else
            { 
                // Application wants to use the data structure provided by the stack
                // let us first clear any data present in the internal data structure
                memset (&modifyBearerRequestStackData, 0,
                sizeof (ModifyBearerRequestMsgData));
                rc =
                dynamic_cast<
                ModifyBearerRequestMsg & >(msg).
                decodeModifyBearerRequestMsg(buffer,
                            modifyBearerRequestStackData,
                            msgDataLength);
            }
            break;
        }
        case ModifyBearerResponseMsgType:
        {
            if (data_p != NULL)
            {
                rc =
                dynamic_cast<
                ModifyBearerResponseMsg & >(msg).
                decodeModifyBearerResponseMsg(buffer,
                            *(ModifyBearerResponseMsgData*)
                             data_p, msgDataLength);
            }
            else
            { 
                // Application wants to use the data structure provided by the stack
                // let us first clear any data present in the internal data structure
                memset (&modifyBearerResponseStackData, 0,
                sizeof (ModifyBearerResponseMsgData));
                rc =
                dynamic_cast<
                ModifyBearerResponseMsg & >(msg).
                decodeModifyBearerResponseMsg(buffer,
                            modifyBearerResponseStackData,
                            msgDataLength);
            }
            break;
        }
        case DeleteSessionRequestMsgType:
        {
            if (data_p != NULL)
            {
                rc =
                dynamic_cast<
                DeleteSessionRequestMsg & >(msg).
                decodeDeleteSessionRequestMsg(buffer,
                            *(DeleteSessionRequestMsgData*)
                             data_p, msgDataLength);
            }
            else
            { 
                // Application wants to use the data structure provided by the stack
                // let us first clear any data present in the internal data structure
                memset (&deleteSessionRequestStackData, 0,
                sizeof (DeleteSessionRequestMsgData));
                rc =
                dynamic_cast<
                DeleteSessionRequestMsg & >(msg).
                decodeDeleteSessionRequestMsg(buffer,
                            deleteSessionRequestStackData,
                            msgDataLength);
            }
            break;
        }
        case DeleteSessionResponseMsgType:
        {
            if (data_p != NULL)
            {
                rc =
                dynamic_cast<
                DeleteSessionResponseMsg & >(msg).
                decodeDeleteSessionResponseMsg(buffer,
                            *(DeleteSessionResponseMsgData*)
                             data_p, msgDataLength);
            }
            else
            { 
                // Application wants to use the data structure provided by the stack
                // let us first clear any data present in the internal data structure
                memset (&deleteSessionResponseStackData, 0,
                sizeof (DeleteSessionResponseMsgData));
                rc =
                dynamic_cast<
                DeleteSessionResponseMsg & >(msg).
                decodeDeleteSessionResponseMsg(buffer,
                            deleteSessionResponseStackData,
                            msgDataLength);
            }
            break;
        }
        case ReleaseAccessBearersRequestMsgType:
        {
            if (data_p != NULL)
            {
                rc =
                dynamic_cast<
                ReleaseAccessBearersRequestMsg & >(msg).
                decodeReleaseAccessBearersRequestMsg(buffer,
                            *(ReleaseAccessBearersRequestMsgData*)
                             data_p, msgDataLength);
            }
            else
            { 
                // Application wants to use the data structure provided by the stack
                // let us first clear any data present in the internal data structure
                memset (&releaseAccessBearersRequestStackData, 0,
                sizeof (ReleaseAccessBearersRequestMsgData));
                rc =
                dynamic_cast<
                ReleaseAccessBearersRequestMsg & >(msg).
                decodeReleaseAccessBearersRequestMsg(buffer,
                            releaseAccessBearersRequestStackData,
                            msgDataLength);
            }
            break;
        }
        case ReleaseAccessBearersResponseMsgType:
        {
            if (data_p != NULL)
            {
                rc =
                dynamic_cast<
                ReleaseAccessBearersResponseMsg & >(msg).
                decodeReleaseAccessBearersResponseMsg(buffer,
                            *(ReleaseAccessBearersResponseMsgData*)
                             data_p, msgDataLength);
            }
            else
            { 
                // Application wants to use the data structure provided by the stack
                // let us first clear any data present in the internal data structure
                memset (&releaseAccessBearersResponseStackData, 0,
                sizeof (ReleaseAccessBearersResponseMsgData));
                rc =
                dynamic_cast<
                ReleaseAccessBearersResponseMsg & >(msg).
                decodeReleaseAccessBearersResponseMsg(buffer,
                            releaseAccessBearersResponseStackData,
                            msgDataLength);
            }
            break;
        }
        case DownlinkDataNotificationMsgType:
        {
            if (data_p != NULL)
            {
                rc =
                dynamic_cast<
                DownlinkDataNotificationMsg & >(msg).
                decodeDownlinkDataNotificationMsg(buffer,
                            *(DownlinkDataNotificationMsgData*)
                             data_p, msgDataLength);
            }
            else
            { 
                // Application wants to use the data structure provided by the stack
                // let us first clear any data present in the internal data structure
                memset (&downlinkDataNotificationStackData, 0,
                sizeof (DownlinkDataNotificationMsgData));
                rc =
                dynamic_cast<
                DownlinkDataNotificationMsg & >(msg).
                decodeDownlinkDataNotificationMsg(buffer,
                            downlinkDataNotificationStackData,
                            msgDataLength);
            }
            break;
        }
        case DownlinkDataNotificationAcknowledgeMsgType:
        {
            if (data_p != NULL)
            {
                rc =
                dynamic_cast<
                DownlinkDataNotificationAcknowledgeMsg & >(msg).
                decodeDownlinkDataNotificationAcknowledgeMsg(buffer,
                            *(DownlinkDataNotificationAcknowledgeMsgData*)
                             data_p, msgDataLength);
            }
            else
            { 
                // Application wants to use the data structure provided by the stack
                // let us first clear any data present in the internal data structure
                memset (&downlinkDataNotificationAcknowledgeStackData, 0,
                sizeof (DownlinkDataNotificationAcknowledgeMsgData));
                rc =
                dynamic_cast<
                DownlinkDataNotificationAcknowledgeMsg & >(msg).
                decodeDownlinkDataNotificationAcknowledgeMsg(buffer,
                            downlinkDataNotificationAcknowledgeStackData,
                            msgDataLength);
            }
            break;
        }
        case DownlinkDataNotificationFailureIndicationMsgType:
        {
            if (data_p != NULL)
            {
                rc =
                dynamic_cast<
                DownlinkDataNotificationFailureIndicationMsg & >(msg).
                decodeDownlinkDataNotificationFailureIndicationMsg(buffer,
                            *(DownlinkDataNotificationFailureIndicationMsgData*)
                             data_p, msgDataLength);
            }
            else
            { 
                // Application wants to use the data structure provided by the stack
                // let us first clear any data present in the internal data structure
                memset (&downlinkDataNotificationFailureIndicationStackData, 0,
                sizeof (DownlinkDataNotificationFailureIndicationMsgData));
                rc =
                dynamic_cast<
                DownlinkDataNotificationFailureIndicationMsg & >(msg).
                decodeDownlinkDataNotificationFailureIndicationMsg(buffer,
                            downlinkDataNotificationFailureIndicationStackData,
                            msgDataLength);
            }
            break;
        }
    }
    return rc;
}

void 
GtpV2Stack::display_v(Uint8 msgType, Debug& stream, void* data_p)
{
    // Display the messageType
    stream.add ("MessageType: ");
    stream.add (msgType);
    stream.endOfLine ();
      
    GtpV2Message& msg = GtpV2MsgFactory::getInstance ().getMsgObject (msgType);

    switch (msgType){
        case CreateSessionRequestMsgType:
        {
            stream.add ("Message: CreateSessionRequestMsg");
            stream.endOfLine ();
            if (data_p != NULL)
            {
            dynamic_cast<
            CreateSessionRequestMsg & >(msg).
            displayCreateSessionRequestMsgData_v (*
                        ((CreateSessionRequestMsgData*) data_p), stream);
            }
            else
            {
            // Application wants to use the data structure provided by the stack
            dynamic_cast<
            CreateSessionRequestMsg & >(msg).
            displayCreateSessionRequestMsgData_v
                        (createSessionRequestStackData, stream);
            }
           break;
        }
        case CreateSessionResponseMsgType:
        {
            stream.add ("Message: CreateSessionResponseMsg");
            stream.endOfLine ();
            if (data_p != NULL)
            {
            dynamic_cast<
            CreateSessionResponseMsg & >(msg).
            displayCreateSessionResponseMsgData_v (*
                        ((CreateSessionResponseMsgData*) data_p), stream);
            }
            else
            {
            // Application wants to use the data structure provided by the stack
            dynamic_cast<
            CreateSessionResponseMsg & >(msg).
            displayCreateSessionResponseMsgData_v
                        (createSessionResponseStackData, stream);
            }
           break;
        }
        case ModifyBearerRequestMsgType:
        {
            stream.add ("Message: ModifyBearerRequestMsg");
            stream.endOfLine ();
            if (data_p != NULL)
            {
            dynamic_cast<
            ModifyBearerRequestMsg & >(msg).
            displayModifyBearerRequestMsgData_v (*
                        ((ModifyBearerRequestMsgData*) data_p), stream);
            }
            else
            {
            // Application wants to use the data structure provided by the stack
            dynamic_cast<
            ModifyBearerRequestMsg & >(msg).
            displayModifyBearerRequestMsgData_v
                        (modifyBearerRequestStackData, stream);
            }
           break;
        }
        case ModifyBearerResponseMsgType:
        {
            stream.add ("Message: ModifyBearerResponseMsg");
            stream.endOfLine ();
            if (data_p != NULL)
            {
            dynamic_cast<
            ModifyBearerResponseMsg & >(msg).
            displayModifyBearerResponseMsgData_v (*
                        ((ModifyBearerResponseMsgData*) data_p), stream);
            }
            else
            {
            // Application wants to use the data structure provided by the stack
            dynamic_cast<
            ModifyBearerResponseMsg & >(msg).
            displayModifyBearerResponseMsgData_v
                        (modifyBearerResponseStackData, stream);
            }
           break;
        }
        case DeleteSessionRequestMsgType:
        {
            stream.add ("Message: DeleteSessionRequestMsg");
            stream.endOfLine ();
            if (data_p != NULL)
            {
            dynamic_cast<
            DeleteSessionRequestMsg & >(msg).
            displayDeleteSessionRequestMsgData_v (*
                        ((DeleteSessionRequestMsgData*) data_p), stream);
            }
            else
            {
            // Application wants to use the data structure provided by the stack
            dynamic_cast<
            DeleteSessionRequestMsg & >(msg).
            displayDeleteSessionRequestMsgData_v
                        (deleteSessionRequestStackData, stream);
            }
           break;
        }
        case DeleteSessionResponseMsgType:
        {
            stream.add ("Message: DeleteSessionResponseMsg");
            stream.endOfLine ();
            if (data_p != NULL)
            {
            dynamic_cast<
            DeleteSessionResponseMsg & >(msg).
            displayDeleteSessionResponseMsgData_v (*
                        ((DeleteSessionResponseMsgData*) data_p), stream);
            }
            else
            {
            // Application wants to use the data structure provided by the stack
            dynamic_cast<
            DeleteSessionResponseMsg & >(msg).
            displayDeleteSessionResponseMsgData_v
                        (deleteSessionResponseStackData, stream);
            }
           break;
        }
        case ReleaseAccessBearersRequestMsgType:
        {
            stream.add ("Message: ReleaseAccessBearersRequestMsg");
            stream.endOfLine ();
            if (data_p != NULL)
            {
            dynamic_cast<
            ReleaseAccessBearersRequestMsg & >(msg).
            displayReleaseAccessBearersRequestMsgData_v (*
                        ((ReleaseAccessBearersRequestMsgData*) data_p), stream);
            }
            else
            {
            // Application wants to use the data structure provided by the stack
            dynamic_cast<
            ReleaseAccessBearersRequestMsg & >(msg).
            displayReleaseAccessBearersRequestMsgData_v
                        (releaseAccessBearersRequestStackData, stream);
            }
           break;
        }
        case ReleaseAccessBearersResponseMsgType:
        {
            stream.add ("Message: ReleaseAccessBearersResponseMsg");
            stream.endOfLine ();
            if (data_p != NULL)
            {
            dynamic_cast<
            ReleaseAccessBearersResponseMsg & >(msg).
            displayReleaseAccessBearersResponseMsgData_v (*
                        ((ReleaseAccessBearersResponseMsgData*) data_p), stream);
            }
            else
            {
            // Application wants to use the data structure provided by the stack
            dynamic_cast<
            ReleaseAccessBearersResponseMsg & >(msg).
            displayReleaseAccessBearersResponseMsgData_v
                        (releaseAccessBearersResponseStackData, stream);
            }
           break;
        }
        case DownlinkDataNotificationMsgType:
        {
            stream.add ("Message: DownlinkDataNotificationMsg");
            stream.endOfLine ();
            if (data_p != NULL)
            {
            dynamic_cast<
            DownlinkDataNotificationMsg & >(msg).
            displayDownlinkDataNotificationMsgData_v (*
                        ((DownlinkDataNotificationMsgData*) data_p), stream);
            }
            else
            {
            // Application wants to use the data structure provided by the stack
            dynamic_cast<
            DownlinkDataNotificationMsg & >(msg).
            displayDownlinkDataNotificationMsgData_v
                        (downlinkDataNotificationStackData, stream);
            }
           break;
        }
        case DownlinkDataNotificationAcknowledgeMsgType:
        {
            stream.add ("Message: DownlinkDataNotificationAcknowledgeMsg");
            stream.endOfLine ();
            if (data_p != NULL)
            {
            dynamic_cast<
            DownlinkDataNotificationAcknowledgeMsg & >(msg).
            displayDownlinkDataNotificationAcknowledgeMsgData_v (*
                        ((DownlinkDataNotificationAcknowledgeMsgData*) data_p), stream);
            }
            else
            {
            // Application wants to use the data structure provided by the stack
            dynamic_cast<
            DownlinkDataNotificationAcknowledgeMsg & >(msg).
            displayDownlinkDataNotificationAcknowledgeMsgData_v
                        (downlinkDataNotificationAcknowledgeStackData, stream);
            }
           break;
        }
        case DownlinkDataNotificationFailureIndicationMsgType:
        {
            stream.add ("Message: DownlinkDataNotificationFailureIndicationMsg");
            stream.endOfLine ();
            if (data_p != NULL)
            {
            dynamic_cast<
            DownlinkDataNotificationFailureIndicationMsg & >(msg).
            displayDownlinkDataNotificationFailureIndicationMsgData_v (*
                        ((DownlinkDataNotificationFailureIndicationMsgData*) data_p), stream);
            }
            else
            {
            // Application wants to use the data structure provided by the stack
            dynamic_cast<
            DownlinkDataNotificationFailureIndicationMsg & >(msg).
            displayDownlinkDataNotificationFailureIndicationMsgData_v
                        (downlinkDataNotificationFailureIndicationStackData, stream);
            }
           break;
        }
    }
}
