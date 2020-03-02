#
# Copyright 2020-present Open Networking Foundation
#
# SPDX-License-Identifier: Apache-2.0
#

from flask import Flask, Response
import prometheus_client
import sys
import socket
import json
import ipaddress
from ctypes import *
import struct

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
                ("state", c_int),
                ("paa", c_int),
                ("imsi", c_byte*16),
                ("bearer_id", c_char),
                ("tai", TAI),
                ("ambr", AMBR)]


app = Flask(__name__)

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

def getTacEdgeNames(loc):
    results = {}
    with open(loc) as f:
        data = json.load(f)
    edges = data["edges"]
    for e in edges:
        tac = e['tac']
        results[tac] = e['edgeName']

    return results

def getPhoneTypes(loc):
    results = {}
    with open(loc) as f:
        data = json.load(f)
    phoneTypes = data["phoneTypes"]
    for e in phoneTypes:
        imsi = e['imsi']
        results[imsi] = e['phoneType']

    return results

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
        intNoUe = int.from_bytes(noUe, byteorder='big',signed=False)
        imsiCnt = 0
        while imsiCnt < intNoUe:
            buff = sock.recv(16)
            imsiBytes = IMSI_STRUCT.from_buffer_copy(buff)
            imsiS = bytes_to_str(imsiBytes.imsi)
            account.append(imsiS)
            imsiCnt += 1
    except:
        print ("exception")
        sock.close()
        sys.exit(1)

    sock.close()
    return account

def getInfo(imsi):
    imsival = str(imsi)
    print ("%s" % imsival)
    # Create a UDS socket
    sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)

    server_address = '/tmp/unix_socket'
    print ('connecting to %s' % server_address, file=sys.stderr)
    try:
        sock.connect(server_address)
    except socket.error:
        print (msg, file=sys.stderr)
        sys.exit(1)

    try:
        req_type = 0;
        payload_out = struct.pack("i16s",req_type,bytes(imsival,'utf-8'))
        nsent = sock.send(payload_out)
        print ("sent %d bytes out" % nsent)
        print ("struct {}".format(payload_out))
        amount_received = 0
        amount_expected = sizeof(IMSI_RSP)
        while amount_received < amount_expected:
            buff = sock.recv(sizeof(IMSI_RSP))
            amount_received += len(buff)
            print ('received "%s"' % buff, file=sys.stderr)

        payload_in = struct.unpack("III16sc3shII", buff)
        parsed_data = IMSI_RSP.from_buffer_copy(buff)
        print ("struct {}".format(payload_in))
        print ("struct {}".format(parsed_data))
    except:
        print ("exception")
        sock.close()
        sys.exit(1)

    sock.close()

    tacRef = getTacEdgeNames('./conf/mme_exporter.json')
    phoneTypeRef = getPhoneTypes('./conf/mme_exporter.json')

    account = {'IMSI': imsi}
    account['Result'] = parsed_data.result
    account['PAA'] = str(ipaddress.ip_address(parsed_data.paa))
    if parsed_data.state == 1:
        account['State'] = "Idle"
    elif parsed_data.state == 2:
        account['State'] = "Active"
    else:
        account['State'] = "Unknown"
    account['BearerId'] = int.from_bytes(parsed_data.bearer_id, byteorder='big',signed=False)
    account['MaxDL'] = parsed_data.ambr.max_req_dl
    account['MaxUL'] = parsed_data.ambr.max_req_ul
    account['TAC'] = int.from_bytes(parsed_data.tai.tac, byteorder='big',signed=False)
    if account['TAC'] in tacRef:
        account['EDGE'] = tacRef[account['TAC']]
    else:
        account['EDGE'] = ""
    account['MCC'] = bytes_to_mcc(parsed_data.tai.plmn_id.idx)
    account['MNC'] = bytes_to_mnc(parsed_data.tai.plmn_id.idx)
    if int(account['IMSI']) in phoneTypeRef:
        account['PhoneType'] = phoneTypeRef[int(account['IMSI'])]
    else:
        account['PhoneType'] = "Unknown"

    return account

@app.route("/metrics")
def exportMetrics():
    results = []
    imsis = getImsiList()
    imsiIndex = 0
    for imsi in imsis:
        # Get subscriber info from IMSI
        ueInfo = getInfo(imsi)
        ueInfoPrint = "ue_info{IMSI=\"" + imsi + "\",State=\"" + ueInfo['State'] + "\",PhoneType=\"" + ueInfo['PhoneType'] + "\",PAA=\"" + ueInfo['PAA'] +  "\",EDGE=\"" + ueInfo['EDGE'] + "\",BearerId=\"" + str(ueInfo['BearerId']) + "\",MaxDL=\"" + str(ueInfo['MaxDL']) + "\",MaxUL=\"" + str(ueInfo['MaxUL']) + "\",TAC=\"" + str(ueInfo['TAC']) + "\",MCC=\"" + str(ueInfo['MCC']) + "\",MNC=\"" + str(ueInfo['MNC']) + "\"} " + imsi + "\n"
        results.append(ueInfoPrint)
    return Response(results, mimetype="text/plain")

if __name__ == '__main__':
    app.run(host='0.0.0.0',port=3081)
