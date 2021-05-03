# This python file is the runtime for directly startup from `runc run` and call code in /code/index.py
import json
import os
import time

import importlib.util
import sys
import base64 
import moleculeIPC

func = None
funcName = os.environ.get("FUNC_NAME")
uuid = int(os.environ.get("IPC_UUID"), 16)
nextid_str = os.environ.get("NEXT_UUID")
connect_next = None
def load_code():
    global func
    sys.path.append("/code")
    # load code
    if func is None:
        func = importlib.import_module('index')      

    
if __name__ == '__main__':
    load_code()
    fifo_self, global_fifo = moleculeIPC.init_server(uuid)

    while(True):
        # 1. receive messages and get uuid of the prev_function
        raw_message = moleculeIPC.receive_from_client(fifo_self, global_fifo)
        print("raw_message: %s\n" %raw_message, flush = True)
        message = eval(raw_message)
        previd = message["uuid"]
        # print("receive from client:\n%s" %message, flush = True)
        
        # 2. get param and pass the param to func.handler
        retVal = func.handler(message) # The retVal must be a dict
        
        # 3. connect to the next function and send the param
        # If no next function, directly return the result to the caller
        if nextid_str == None:
            connect_prev = moleculeIPC.global_fifo_connect(previd) #TODO
            moleculeIPC.send_to_server(connect_prev, str(retVal))
            continue
        nextid = int(nextid_str, 16)
        # print("function %s with uuid %ld ready to send message to next function" %(funcName, uuid), flush = True)
        # Else, attach uuid to the message and send it to the next function
        retVal['uuid'] = uuid            
        # Delay the connection to the next function, 
        # because we assume that the next function is ready only when the first invocation has come,
        if connect_next == None:
            connect_next = moleculeIPC.global_fifo_connect(nextid)
        moleculeIPC.send_to_server(connect_next, str(retVal))

        # 4. get the return value of the next function and send to the param
        raw_message_return = moleculeIPC.receive_from_client(fifo_self, global_fifo)
        message_return = eval(raw_message_return)
        # previd = 1111
        connect_prev = moleculeIPC.global_fifo_connect(previd)
        moleculeIPC.send_to_server(connect_prev, str(message_return))
        
        # print("send response: %s" %retVal, flush = True)

    