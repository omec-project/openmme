from flask import Flask, render_template, request, jsonify
import socket
import random
import json
import sys
import functools 
import operator
from ctypes import *
import struct
import time

""" This class defines a C-like struct """
class IMSI_REQ(Structure):
    _fields_ = [("req_type", c_int),
                ("imsi", c_byte*16)]

class IMSI_STRUCT(Structure):
    _fields_ = [("imsi", c_byte*16)]

class PLMN(Structure):
    _fields_ = [("idx", c_byte*3)]

class TAI(Structure):
    _fields_ = [("plmn_id", PLMN),
                ("tac", c_byte*2)]

class AMBR(Structure):
    _fields_ = [("max_req_dl", c_int),
                ("max_req_ul", c_int)]

class IMSI_RSP(Structure):
    _fields_ = [("result", c_int), 
                ("imsi", c_byte*16),
                ("bearer_id", c_char),
                ("tai", TAI),
                ("ambr", AMBR)]

class MyEncoder(json.JSONEncoder):
    def default(self, o):
        if type(o) is bytes:
            return o.decode("ISO-8859-1")
        return super(MyEncoder, self).default(o)

app = Flask(__name__)

@app.route("/")

def helloWorld():
    return "Hello World\n"

def bytes_to_int(bytes):
    result = 0
    for b in bytes:
        result = result * 256 + int(b)
    return result

def bytes_to_str(bytes):
    result = ""
    for b in bytes:
       c = chr(b)
       if c != '\0':
          result += c
    return result

def bytes_to_mcc(plmn):
    b = bytes(plmn)
    a1 = (b[0]) & 0x0F
    a2 = ((b[0]) & 0xF0) >> 4
    a3 = (b[1] & 0x0F)
    result = "" + str(a1) + str(a2) + str(a3)
    return result

def bytes_to_mnc(plmn):
    b = bytes(plmn)
    a1 = (b[2]) & 0x0F
    a2 = ((b[2]) & 0xF0) >> 4
    a3 = (b[1] & 0xF0) >> 4
    if(int(a3) == 15):
        result = "" + str(a1) + str(a2)
    else:
        result = "" + str(a1) + str(a2) + str(a3)
    return result

def tuple_to_str(tup): 
    str =  b''.join(tup) 
    return str

@app.route("/imsiInfo/", methods=["GET"])
def getImsiList():
        # Create a UDS socket
        sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)

        # Connect the socket to the port where the server is listening
        server_address = '/tmp/unix_socket'
        print ('connecting to %s' % server_address, file=sys.stderr)
        try:
               sock.connect(server_address)
        except socket.error:
               print (msg, file=sys.stderr)
               sys.exit(1)

        try:
           #payload_out = IMSI_REQ(bytes(imsival,'utf-8'))
           imsival = ""
           req_type = 1
           payload_out = struct.pack("i16s",req_type,bytes(imsival,'utf-8'))
           nsent = sock.send(payload_out)
           print ("sent %d bytes out" % nsent)
           print ("struct {}".format(payload_out))
           account = []
           amount_received = 0
           amount_expected = 4
           while amount_received < amount_expected:
              buff = sock.recv(4)
              amount_received += len(buff)
              print ('received "%s"' % buff, file=sys.stderr)
           no_of_ue = struct.unpack("i", buff)
           noUe = bytes(no_of_ue)
           intNoUe = bytes_to_int(noUe) 
           imsiCnt = 0
           while imsiCnt < intNoUe:
              buff = sock.recv(16)
#imsiBytes = (struct.unpack("16s", buff))
              imsiBytes = IMSI_STRUCT.from_buffer_copy(buff)
#imsiStr = bytes_to_str(imsiBytes)
#imsiS = ''.join(imsiStr) 
              imsiS = bytes_to_str(imsiBytes.imsi)
              data = {'imsi': imsiS}
              account.append(data)
              imsiCnt += 1
               
        except:
           print ("exception")
           sock.close()
           sys.exit(1)

        sock.close()
        return render_template('monitor_tool.html', accts=account)
#return jsonify(account)

@app.route("/imsiInfo/<imsi>", methods=["GET"])
def getInfo(imsi):
        imsival = str(imsi)
        print ("%s" % imsival)
        # Create a UDS socket
        sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)

        # Connect the socket to the port where the server is listening
        server_address = '/tmp/unix_socket'
        print ('connecting to %s' % server_address, file=sys.stderr)
        try:
           sock.connect(server_address)
        except socket.error:
           print (msg, file=sys.stderr)
           sys.exit(1)

        try:
           #payload_out = IMSI_REQ(bytes(imsival,'utf-8'))
           req_type = 0;
           payload_out = struct.pack("i16s",req_type,bytes(imsival,'utf-8'))
           nsent = sock.send(payload_out)
           print ("sent %d bytes out" % nsent)
           print ("struct {}".format(payload_out))
           amount_received = 0
           amount_expected = sizeof(IMSI_RSP)
           #while 1:
           #    time.sleep(10)
           while amount_received < amount_expected:
              buff = sock.recv(sizeof(IMSI_RSP))
              amount_received += len(buff)
              print ('received "%s"' % buff, file=sys.stderr)
           #buff = sock.recv(sizeof(IMSI_RSP))
           #payload_in = IMSI_RSP.from_buffer_copy(buff)
           payload_in = struct.unpack("i16sc3shii", buff)
           parsed_data = IMSI_RSP.from_buffer_copy(buff)
           #bearerid, plmn, tac, maxdl, maxul = struct.unpack("c3shii", buff)
           print ("struct {}".format(payload_in))
           print ("struct {}".format(parsed_data))
           #print ("Received id=%d, max_dl=%d, max_ul=%d" % payload_in.bearer_id, payload_in.ambr.max_req_dl
           #, payload_in.ambr.max_req_ul)
        except:
           print ("exception")
           sock.close()
           sys.exit(1)

        sock.close()
        account = []
        data = {'name' : 'Result', 'value': parsed_data.result}
        account.append(data)
        data = {'name' : 'BearerId', 'value': bytes_to_int(parsed_data.bearer_id)}
        account.append(data)
        data = {'name' : 'Max DL', 'value': (parsed_data.ambr.max_req_dl)}
        account.append(data)
        data = {'name' : 'Max UL', 'value': (parsed_data.ambr.max_req_ul)}
        account.append(data)
        data = {'name' : 'TAC', 'value': (bytes_to_int(parsed_data.tai.tac))}
        account.append(data)
        data = {'name' : 'MCC', 'value':
            (bytes_to_mcc(parsed_data.tai.plmn_id.idx))}
        account.append(data)
        data = {'name' : 'MNC', 'value':
            (bytes_to_mnc(parsed_data.tai.plmn_id.idx))}
        account.append(data)
        print(json.dumps(payload_in, cls=MyEncoder))
        output = (json.dumps(payload_in, cls=MyEncoder))
        output1 = json.dumps(parsed_data.__dict__)

        return jsonify(account)


if __name__ == '__main__':
    app.run(host='0.0.0.0',port=3081)
