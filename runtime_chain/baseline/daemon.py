# This python file is the runtime for directly startup from `runc run` and call code in /code/index.py
import traceback
import json
import os
import time

import importlib.util
import sys
import base64 
from flask import Flask, request

func = None
app = Flask(__name__)

@app.route('/invoke', methods = ["POST"])
def start_faas_server():
    getParam = request.get_json()
    # TODO: add error handling for param and handler
    retVal = func.handler(getParam)
    # TODO: judge the type of the retVal. Now it is a string by default
    print("retVal in flask: %s" %retVal)
    return retVal


def load_code():
    global func
    sys.path.append("/code")
    # load code
    if func is None:
        func = importlib.import_module('index')      

    
if __name__ == '__main__':
    load_code()
    FLASK_PORT = os.environ['FLASK_PORT']
    app.run(host='0.0.0.0', port=FLASK_PORT)

# def main():
#     start_faas_server()

# if __name__ == '__main__':
#     main()
    