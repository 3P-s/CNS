import random
from sympy import isprime, mod_inverse

def generate_keypair(p, q):
    if not (isprime(p) and isprime(q)):
        raise ValueError('Both numbers must be prime.')
    elif p == q:
        raise ValueError('p and q cannot be equal')
    
    n = p * q
    phi = (p-1) * (q-1)
    
    e = random.randrange(1, phi)
    
    g = gcd(e, phi)
    while g != 1:
        e = random.randrange(1, phi)
        g = gcd(e, phi)
    
    d = mod_inverse(e, phi)
    
    return ((e, n), (d, n))

def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

def encrypt(pk, plaintext):
    key, n = pk
    cipher = [(ord(char) ** key) % n for char in plaintext]
    return cipher

def decrypt(pk, ciphertext):
    key, n = pk
    plain = [chr((char ** key) % n) for char in ciphertext]
    return ''.join(plain)

if __name__ == '__main__':
    p = 61
    q = 53
    public, private = generate_keypair(p, q)
    print("Public Key: ", public)
    print("Private Key: ", private)
    
    message = "Hello"
    encrypted_msg = encrypt(public, message)
    print("Encrypted Message: ", encrypted_msg)
    
    decrypted_msg = decrypt(private, encrypted_msg)
    print("Decrypted Message: ", decrypted_msg)