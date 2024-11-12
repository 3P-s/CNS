def encrypt(text, s):
    result=""
    for i in range(len(text)):
        if text[i].isupper():
            result+=chr((ord(text[i]) + s - 65) % 26 + 65)
        else:
            result+=chr((ord(text[i]) + s - 97) % 26 + 97)
    return result

text="ATTACKATONCE"
s=4
print("Text:",text)
print("Shift:",s)
print("Cipher:",encrypt(text,s))