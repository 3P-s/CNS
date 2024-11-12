# SHA-1 
import hashlib
import sys

def sha1_hash(data):
    sha1 = hashlib.sha1()
    sha1.update(data)
    return sha1.hexdigest()

data = sys.argv[1].encode()
print(sha1_hash(data))

