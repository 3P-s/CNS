import numpy as np
def char_to_int(c):
    return ord(c.upper())-ord('A')
def int_to_char(n):
    return chr(n%26+ord('A'))
def hill_encrypt(p_text,key_matrix):
    p_text=p_text.upper().replace(" ","")
    if len(p_text)%2!=0:
        p_text+='X'
    encrypted_text=""
    for i in range(0,len(p_text),2):
        pair=[char_to_int(p_text[i]),char_to_int(p_text[i+1])]
        result=np.dot(key_matrix,pair)%26
        encrypted_text+=int_to_char(result[0])+int_to_char(result[1])
    return encrypted_text


key_matrix=np.array([[3,3],[2,5]])
p_text="HELLO"
encrypted_message=hill_encrypt(p_text,key_matrix)
print("Encrypted message:",encrypted_message)
