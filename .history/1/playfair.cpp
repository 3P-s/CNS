#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

char keyMatrix[5][5];

// Function to remove duplicates from a string
string removeDuplicates(string str) {
    string result;
    bool used[26] = {false};
    for (char c : str) {
        if (!used[c - 'a']) {
            used[c - 'a'] = true;
            result += c;
        }
    }
    return result;
}

// Function to create the Playfair key matrix
void generateKeyMatrix(string key) {
    key = removeDuplicates(key);
    key.erase(remove(key.begin(), key.end(), 'j'), key.end()); // Remove 'j'

    bool used[26] = {false};
    int k = 0;
    for (char c : key) {
        used[c - 'a'] = true;
    }
    key += "abcdefghiklmnopqrstuvwxyz"; // All letters except 'j'

    int index = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            while (used[key[index] - 'a']) index++;
            keyMatrix[i][j] = key[index];
            used[key[index] - 'a'] = true;
        }
    }
}

// Function to find the position of a character in the key matrix
void findPosition(char c, int &row, int &col) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (keyMatrix[i][j] == c) {
                row = i;
                col = j;
                return;
            }
        }
    }
}

// Function to preprocess the plaintext (handle repeated characters, make pairs)
string preprocessPlaintext(string text) {
    text.erase(remove(text.begin(), text.end(), ' '), text.end()); // Remove spaces
    for (int i = 0; i < text.length(); i += 2) {
        if (i + 1 == text.length()) {
            text += 'x'; // Append 'x' if the length of text is odd
        } else if (text[i] == text[i + 1]) {
            text.insert(i + 1, 1, 'x'); // Insert 'x' between repeated letters
        }
    }
    return text;
}

// Function to encrypt plaintext using Playfair Cipher
string playfairEncrypt(string plaintext, string key) {
    generateKeyMatrix(key);
    plaintext = preprocessPlaintext(plaintext);
    string encrypted = "";

    for (int i = 0; i < plaintext.length(); i += 2) {
        int r1, c1, r2, c2;
        findPosition(plaintext[i], r1, c1);
        findPosition(plaintext[i + 1], r2, c2);

        if (r1 == r2) { // Same row
            encrypted += keyMatrix[r1][(c1 + 1) % 5];
            encrypted += keyMatrix[r2][(c2 + 1) % 5];
        } else if (c1 == c2) { // Same column
            encrypted += keyMatrix[(r1 + 1) % 5][c1];
            encrypted += keyMatrix[(r2 + 1) % 5][c2];
        } else { // Rectangle swap
            encrypted += keyMatrix[r1][c2];
            encrypted += keyMatrix[r2][c1];
        }
    }
    return encrypted;
}

// Function to decrypt ciphertext using Playfair Cipher
string playfairDecrypt(string ciphertext, string key) {
    generateKeyMatrix(key);
    string decrypted = "";

    for (int i = 0; i < ciphertext.length(); i += 2) {
        int r1, c1, r2, c2;
        findPosition(ciphertext[i], r1, c1);
        findPosition(ciphertext[i + 1], r2, c2);

        if (r1 == r2) { // Same row
            decrypted += keyMatrix[r1][(c1 + 4) % 5];
            decrypted += keyMatrix[r2][(c2 + 4) % 5];
        } else if (c1 == c2) { // Same column
            decrypted += keyMatrix[(r1 + 4) % 5][c1];
            decrypted += keyMatrix[(r2 + 4) % 5][c2];
        } else { // Rectangle swap
            decrypted += keyMatrix[r1][c2];
            decrypted += keyMatrix[r2][c1];
        }
    }
    return decrypted;
}

int main() {
    cout<<"Enter the single word key: ";
    string key;
    cin>>key;

    cout<<"Enter the plaintext: ";
    string plaintext;
    getline(cin>>ws, plaintext);

    cout << "Original Text: " << plaintext << endl;

    string encrypted = playfairEncrypt(plaintext, key);
    cout << "Encrypted Text: " << encrypted << endl;

    string decrypted = playfairDecrypt(encrypted, key);
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}
