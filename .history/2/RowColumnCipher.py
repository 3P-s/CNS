def create_matrix(text, key):
    rows, cols = len(key), len(text) // len(key) + (len(text) % len(key) != 0)
    matrix = [['' for _ in range(cols)] for _ in range(rows)]
    k = 0
    for i in range(cols):
        for j in range(rows):
            if k < len(text):
                matrix[j][i] = text[k]
                k += 1
    return matrix

def encrypt(text, key):
    matrix = create_matrix(text, key)
    sorted_key = sorted(list(key))
    encrypted_text = ''
    for k in sorted_key:
        col = key.index(k)
        for row in matrix:
            if row[col] != '':
                encrypted_text += row[col]
    return encrypted_text

def decrypt(encrypted_text, key):
    rows, cols = len(key), len(encrypted_text) // len(key) + (len(encrypted_text) % len(key) != 0)
    matrix = [['' for _ in range(cols)] for _ in range(rows)]
    sorted_key = sorted(list(key))
    k = 0
    for k_char in sorted_key:
        col = key.index(k_char)
        for row in range(rows):
            if k < len(encrypted_text):
                matrix[row][col] = encrypted_text[k]
                k += 1
    decrypted_text = ''
    for i in range(cols):
        for j in range(rows):
            if matrix[j][i] != '':
                decrypted_text += matrix[j][i]
    return decrypted_text

if __name__ == "__main__":
    choice = input("Enter 'e' to encrypt or 'd' to decrypt: ").lower()
    key = input("Enter the key: ")
    text = input("Enter the text: ")

    if choice == 'e':
        encrypted = encrypt(text, key)
        print(f"Encrypted text: {encrypted}")
    elif choice == 'd':
        decrypted = decrypt(text, key)
        print(f"Decrypted text: {decrypted}")
    else:
        print("Invalid choice")