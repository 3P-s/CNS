def row_column_encrypt(text, rows, cols):
    grid = [['X' for _ in range(cols)] for _ in range(rows)]  
    k = 0
    
    for i in range(rows):
        for j in range(cols):
            if k < len(text):
                grid[i][j] = text[k]
                k += 1
            else:
                grid[i][j] = 'X'  
    encrypted = ""
    for j in range(cols):
        for i in range(rows):
            encrypted += grid[i][j]

    return encrypted

def row_column_decrypt(text, rows, cols):
    grid = [['' for _ in range(cols)] for _ in range(rows)]
    k = 0
    for j in range(cols):
        for i in range(rows):
            grid[i][j] = text[k]
            k += 1

    decrypted = ""
    for i in range(rows):
        for j in range(cols):
            decrypted += grid[i][j]

    return decrypted

if __name__ == "__main__":
    text = "HELLOTHISISROWCOLUMN"
    rows = 4
    cols = 5

    encrypted = row_column_encrypt(text, rows, cols)
    print(f"Row-Column Encrypted: {encrypted}")

    decrypted = row_column_decrypt(encrypted, rows, cols)
    print(f"Row-Column Decrypted: {decrypted}")
