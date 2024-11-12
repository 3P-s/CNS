def generate_key(text,key):
    key=key.upper()
    if len(text)==len(key):
        return key
    else:
        key=(key*(len(text)//len(key)))+key[:len(text)%len(key)]
    return key
def vigenere_encrypt(text,key):
    text=text.upper().replace(" ","")
    key=generate_key(text,key)
    ans_text=""
    for i in range(len(text)):
        ans_text+=chr(((ord(text[i])+ord(key[i]))%26)+65)
    return ans_text



text="HELLO"
key="KEY"
encrypted_message=vigenere_encrypt(text,key)
print("Encrypted message:",encrypted_message)
