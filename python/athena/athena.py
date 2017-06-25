#! /usr/bin/python
import struct
from threading import Thread
import sys
import os
import socket
import urllib
import time
import json

# Athena Protobuf import
sys.path.insert(0, '/opt/intel/athena/utils/include/protobuf/')
import queryMessage_pb2 # protobuf struct autogenerated

# Recieves a json struct as a string
def query(query_JSON):
    quer = queryMessage_pb2.queryMessage()
    # quer has .json_query and .blob
    quer.json_query = query_JSON

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(("localhost",55555))

    # Serialize with protobuf and send
    data = quer.SerializeToString();
    sent_len = struct.pack('@I', len(data)) # send size first
    s.send( sent_len )
    s.send(data)

    # time.sleep(1)

    # Recieve response
    recv_len = s.recv(4)
    recv_len = struct.unpack('@I', recv_len)[0]
    response = s.recv(recv_len)

    querRes = queryMessage_pb2.queryMessage()
    querRes.ParseFromString(response)

    return querRes.json_query

# Recieves json object
def queryJSONObj(json_obj):

    parsed = json.loads(json_obj)
    str_query = json.dumps(parsed, indent=4, sort_keys=False)
    return query(str_query)