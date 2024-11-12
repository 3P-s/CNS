from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes


def aes_encrypt(plain_text, key):
    cipher = AES.new(key, AES.MODE_CBC)
    iv = cipher.iv  
    padded_text = pad(plain_text.encode(), AES.block_size)
    encrypted_text = cipher.encrypt(padded_text)
    return iv, encrypted_text


def aes_decrypt(iv, cipher_text, key):
    cipher = AES.new(key, AES.MODE_CBC, iv)
    #print all
    decrypted_text = unpad(cipher.decrypt(cipher_text), AES.block_size)
    return decrypted_text.decode()


def main():
    print("\nAES Encryption and Decryption")
    
    key_input = input("Enter a 32-byte key (in hexadecimal): ")
    key = bytes.fromhex(key_input)
    choice = int(input("Enter choice: 1. Encrypt 2. Decrypt"))
    print()
    
    if choice == 1:
        plain_text = input("\nEnter the plain text to encrypt: ")
        iv, encrypted_text = aes_encrypt(plain_text, key)
        print(f"\nInitialization Vector (IV) (in hexadecimal): {iv.hex()}")
        print(f"\nEncrypted Text (in hexadecimal): {encrypted_text.hex()}")
    
    else:
        iv = bytes.fromhex(input("Enter IV: "))
        encrypted_text = bytes.fromhex(input("Enter Encrypted Text: "))
        decrypted_text = aes_decrypt(iv, encrypted_text, key)
        print(f"\nDecrypted Text: {decrypted_text}")

    decrypted_text = aes_decrypt(iv, encrypted_text, key)
    print(f"\nDecrypted Text: {decrypted_text}")


main()


# ECB (Electronic Codebook):
# Each block of plaintext is encrypted independently.
# Weakness: Identical plaintext blocks produce identical ciphertext blocks, making it vulnerable to pattern recognition.
# Not recommended for secure communication.



# CBC (Cipher Block Chaining):
# Each plaintext block is XORed with the previous ciphertext block before being encrypted.
# Requires an Initialization Vector (IV) for the first block to ensure that identical plaintexts produce different ciphertexts.
# More secure than ECB, as it introduces randomness with the IV and makes patterns less recognizable.
# The mode used in your code.


# CFB (Cipher Feedback):
# Converts a block cipher into a self-synchronizing stream cipher.
# Useful for encrypting data of unknown or variable length.


# OFB (Output Feedback):
# Also converts a block cipher into a stream cipher, but in a simpler way than CFB.
# Errors in transmission do not propagate, unlike in CBC.


# CTR (Counter):
# Works like a stream cipher.
# Each block of plaintext is XORed with an encrypted counter value.
# The counter increases for each subsequent block.


# GCM (Galois/Counter Mode):
# Provides both encryption and integrity/authentication.
# Often used in secure communication protocols like TLS.