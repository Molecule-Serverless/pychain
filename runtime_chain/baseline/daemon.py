# This python file is the runtime for directly startup from `runc run` and call code in /code/index.py
import traceback
import json
import os
import time

import importlib.util
import sys
import base64 

func = None

def start_faas_server():
    global func
    sys.path.append("/code")
    # load code
    if func is None:
        func = importlib.import_module('index')      
    
    param = {"message" : "hello world"}
    ####### driver hard code ######
    # invoke the function   
    retVal = func.handler(param)
    # TODO: judge the type of the retVal. Now it is a string by default
    print(retVal)

def main():
    start_faas_server()

if __name__ == '__main__':
    main()
    