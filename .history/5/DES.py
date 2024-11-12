from Crypto.Cipher import DES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes


def des_encrypt(plain_text, key):
    cipher = DES.new(key, DES.MODE_ECB)
    padded_text = pad(plain_text.encode(), DES.block_size)
    encrypted_text = cipher.encrypt(padded_text)
    return encrypted_text


def des_decrypt(cipher_text, key):
    cipher = DES.new(key, DES.MODE_ECB)
    decrypted_text = unpad(cipher.decrypt(cipher_text), DES.block_size)
    return decrypted_text.decode()


def main():
    print("\nDES Encryption and Decryption")
    key = get_random_bytes(8)
    print(f"\nGenerated Key (in hexadecimal): {key.hex()}")
    
    plain_text = input("Enter the plain text to encrypt: ")
    encrypted_text = des_encrypt(plain_text, key)

    print(f"\nEncrypted Text (in hexadecimal): {encrypted_text.hex()}")
    decrypted_text = des_decrypt(encrypted_text, key)
    print(f"\nDecrypted Text: {decrypted_text}")
    

main()
