def generate_matrix(key):
    key = key.upper().replace("J", "I")
    matrix = []
    used_chars = set()
    
    for char in key:
        if char not in used_chars and char.isalpha():
            matrix.append(char)
            used_chars.add(char)
    
    alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"
    for char in alphabet:
        if char not in used_chars:
            matrix.append(char)
            used_chars.add(char)
    print('Matrix:')
    intial=0
    for i in range(5):
        for j in range(5):
            print(matrix[intial],end=" ")
            intial+=1
        print()
    print()

    return [matrix[i:i+5] for i in range(0, 25, 5)]

def find_position(matrix, char):
    for row in range(5):
        for col in range(5):
            if matrix[row][col] == char:
                return row, col
    return None

def prepare_text(text):
    text = text.upper().replace("J", "I")
    prepared_text = ""
    
    i = 0
    while i < len(text):
        char1 = text[i]
        char2 = text[i+1] if i+1 < len(text) else 'X'
        
        if char1 == char2:
            prepared_text += char1 + 'X'
            i += 1
        else:
            prepared_text += char1 + char2
            i += 2
    
    if len(prepared_text) % 2 != 0:
        prepared_text += 'X'
    
    return prepared_text

def encrypt_pair(pair, matrix):
    row1, col1 = find_position(matrix, pair[0])
    row2, col2 = find_position(matrix, pair[1])
    
    if row1 == row2:
        return matrix[row1][(col1 + 1) % 5] + matrix[row2][(col2 + 1) % 5]
    elif col1 == col2:
        return matrix[(row1 + 1) % 5][col1] + matrix[(row2 + 1) % 5][col2]
    else:
        return matrix[row1][col2] + matrix[row2][col1]

def playfair_encrypt(text, key):
    matrix = generate_matrix(key)
    prepared_text = prepare_text(text)
    
    encrypted_text = ""
    for i in range(0, len(prepared_text), 2):
        encrypted_text += encrypt_pair(prepared_text[i:i+2], matrix)
    
    return encrypted_text

text = input('Enter Text: ')
key = input('Enter Key: ')
encrypted_text = playfair_encrypt(text, key)
print("Encrypted text:", encrypted_text)




