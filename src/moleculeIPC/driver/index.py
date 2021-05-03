import os

def getKeys():
    keys = []
    files = os.listdir("/code")
    for f in files:
        fileSplit = f.split(".")
        # find "f*.txt"
        if fileSplit[0][0] == "f" and fileSplit[-1] == "txt":
            keys.append(f)
    return keys

def prepare_mapper_payload(all_keys, batch_size, mapper_id):
    keys = all_keys[mapper_id * batch_size: (mapper_id + 1) * batch_size]
    key = ""
    for item in keys:
        key += item + '/'
    key = key[:-1]
    payload = {
        "keys": key,
        "mapper_id": mapper_id
    }
    return payload

def handler(event):
    n_mapper = 1

    # Fetch all the keys
    all_keys = getKeys()
    
    #TODO
    total_size = len(all_keys)
    batch_size = 0

    if total_size % n_mapper == 0:
        batch_size = total_size / n_mapper
    else:
        batch_size = total_size // n_mapper + 1
    
    payload = prepare_mapper_payload(all_keys, int(batch_size), 0)

    return payload