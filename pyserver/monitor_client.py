from flask import Flask, render_template, request, jsonify, Response
import prometheus_client
from prometheus_client import Summary, Counter, Histogram, Gauge
from prometheus_client import CONTENT_TYPE_LATEST
import socket
import random
import json
import sys
import ipaddress
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
                ("paa", c_int),
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
              imsiBytes = IMSI_STRUCT.from_buffer_copy(buff)
              imsiS = bytes_to_str(imsiBytes.imsi)
              #data = {'imsi': imsiS}
              account.append(imsiS)
              imsiCnt += 1
               
        except:
           print ("exception")
           sock.close()
           sys.exit(1)

        sock.close()
        return account
#        return render_template('monitor_tool.html', accts=account)
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
           payload_in = struct.unpack("II16sc3shII", buff)
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
        print ("PAA = {}".format(parsed_data.paa))
        account = {'IMSI': imsi}
        account['Result'] = parsed_data.result
        account['PAA'] = str(ipaddress.ip_address(parsed_data.paa))
        #account['PAA'] = str(ipaddress.ip_address(123456789))
        account['BearerId'] = bytes_to_int(parsed_data.bearer_id)
        account['MaxDL'] = parsed_data.ambr.max_req_dl
        account['MaxUL'] = parsed_data.ambr.max_req_ul
        #account['TAC'] = bytes_to_int(parsed_data.tai.tac)
        account['TAC'] = int.from_bytes(parsed_data.tai.tac, byteorder='big',signed=False)
        if account['TAC'] == 202:
          account['EDGE'] = 'edge-onf-menlo'
        elif account['TAC'] == 101:
          account['EDGE'] = 'edge-intel'
        elif account['TAC'] == 17:
          account['EDGE'] = 'edge-onf-menlo'
        else:
          account['EDGE'] = 'edge-barcelona'

        account['MCC'] = bytes_to_mcc(parsed_data.tai.plmn_id.idx)
        account['MNC'] = bytes_to_mnc(parsed_data.tai.plmn_id.idx)

        return account

@app.route("/metrics")
def exportMetrics():
    results = []
    imsis = getImsiList()
    imsiIndex = 0
    for imsi in imsis:
        # Get subscriber info from IMSI
        ueInfo = getInfo(imsi)
#        uePrintDataBearerId = "BearerId{IMSI=\"" + imsi + "\"} " + str(ueInfo['BearerId']) + "\n"
#        results.append(uePrintDataBearerId)
#        uePrintDataMaxDL = "MaxDL{IMSI=\"" + imsi + "\"} " + str(ueInfo['MaxDL']) + "\n"
#        results.append(uePrintDataMaxDL)
#        uePrintDataMaxUL = "MaxUL{IMSI=\"" + imsi + "\"} " + str(ueInfo['MaxUL']) + "\n"
#        results.append(uePrintDataMaxUL)
#        uePrintDataTAC = "TAC{IMSI=\"" + imsi + "\"} " + str(ueInfo['TAC']) + "\n"
#        results.append(uePrintDataTAC)
#        uePrintDataMCC = "MCC{IMSI=\"" + imsi + "\"} " + str(ueInfo['MCC']) + "\n"
#        results.append(uePrintDataMCC)
#        uePrintDataMNC = "MNC{IMSI=\"" + imsi + "\"} " + str(ueInfo['MNC']) + "\n"
#        results.append(uePrintDataMNC)
        
        ueInfoPrint = "ue_info{IMSI=\"" + imsi + "\",PAA=\"" + ueInfo['PAA'] +  "\",EDGE=\"" + ueInfo['EDGE'] + "\",BearerId=\"" + str(ueInfo['BearerId']) + "\",MaxDL=\"" + str(ueInfo['MaxDL']) + "\",MaxUL=\"" + str(ueInfo['MaxUL']) + "\",TAC=\"" + str(ueInfo['TAC']) + "\",MCC=\"" + str(ueInfo['MCC']) + "\",MNC=\"" + str(ueInfo['MNC']) + "\"} " + imsi + "\n"
        results.append(ueInfoPrint)

    return Response(results, mimetype="text/plain")




#    results = "imsi{server=\"dns://169.254.25.10:53\",zone=\".\",le=\"0.0005\"} 1"
#    return Response(results, mimetype="text/plain")
#    return Response(result, mimetype=CONTENT_TYPE_LATEST)
#    return Response(result, mimetype="application/json")


if __name__ == '__main__':
    app.run(host='0.0.0.0',port=3081)
