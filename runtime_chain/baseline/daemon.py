# This python file is the runtime for directly startup from `runc run` and call code in /code/index.py
import traceback
import json
import os
import time
import requests

import importlib.util
import sys
import base64 
from flask import Flask, request

func = None
funcName = os.environ.get("FUNC_NAME")
app = Flask(__name__)

@app.route('/invoke', methods = ["POST"])
def start_faas_server():
    startTime = int(round(time.time() * 1000))
    getParam = request.get_json()
    # TODO: add error handling for param and handler
    retVal = func.handler(getParam)
    # TODO: judge the type of the retVal. Now it is a dict by default
    next_func = os.environ.get("NEXT_FUNC")
    if next_func == None:
        endTime = int(round(time.time() * 1000))
        retVal["end2end_%s" %funcName] = endTime - startTime
        return retVal

    url = "http://%s:5000/invoke" %next_func

    resp = requests.post(url, json = retVal)
    retVal = eval(resp.content)
    
    endTime = int(round(time.time() * 1000))
    retVal["end2end_%s" %funcName] = endTime - startTime
    print(retVal, flush= True)
    return retVal

def load_code():
    global func
    sys.path.append("/code")
    # load code
    if func is None:
        func = importlib.import_module('index')      

    
if __name__ == '__main__':
    load_code()
    FLASK_PORT = os.environ.get('FLASK_PORT')
    if FLASK_PORT == None:
        FLASK_PORT = 5000
    app.run(host='0.0.0.0', port=FLASK_PORT)

# def main():
#     start_faas_server()

# if __name__ == '__main__':
#     main()
    