keywords = ["lions", "fish", "old"]

def handler(event):
    output = {}

    for keyword in keywords:
        output[keyword] = 0
    
    all_keys = []
    print("param: %s\n" %event, flush=True)
    contents = eval(event['output'])
    for obj in list(contents.keys()):
        all_keys.append(obj)
    
    for key in all_keys:
        output[key] = contents[key]
    
    payload = {
        'output': output
    }

    return payload