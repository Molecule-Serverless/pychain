keywords = ["lions", "fish", "old"]

def handler(event):
    src_keys = event['keys']
    mapper_id = event['mapper_id']

    output = {}

    for keyword in keywords:
        output[keyword] = 0

    keys = src_keys.split('/')
    for key in keys:
        f = open("/code/%s" %key, "r")
        contents = f.read()

        for line in contents.split('\n')[:-1]:
            for keyword in keywords:
                if keyword in line:
                    output[keyword] += 1
    payload = {
        'output': str(output)
    }
    return payload

