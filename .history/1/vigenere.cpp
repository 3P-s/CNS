#include <iostream>
using namespace std;

// Function to generate key to match length of text
string generateKey(string text, string key)
{
    int x = text.size();
    for (int i = 0;; i++)
    {
        if (x == i)
            i = 0;
        if (key.size() == text.size())
            break;
        key.push_back(key[i]);
    }
    return key;
}

// Function to encrypt using Vigenere Cipher
string vigenereEncrypt(string text, string key)
{
    string encryptedText;
    for (int i = 0; i < text.size(); i++)
    {
        // Shift each character based on key
        char x = (text[i] + key[i]) % 26;
        x += 'A';
        encryptedText.push_back(x);
    }
    return encryptedText;
}

// Function to decrypt using Vigenere Cipher
string vigenereDecrypt(string encryptedText, string key)
{
    string decryptedText;
    for (int i = 0; i < encryptedText.size(); i++)
    {
        // Reverse the shift based on key
        char x = (encryptedText[i] - key[i] + 26) % 26;
        x += 'A';
        decryptedText.push_back(x);
    }
    return decryptedText;
}

int main()
{
    cout<<"Enter the text to be encrypted: ";
    string text;
    getline(cin>>ws, text);

    cout<<"Enter the key: ";
    string key;
    cin>>key;

    key = generateKey(text, key);
    string encrypted = vigenereEncrypt(text, key);
    cout << "Original Text: " << text << endl;
    cout << "Encrypted Text: " << encrypted << endl;
    cout << "Decrypted Text: " << vigenereDecrypt(encrypted, key) << endl;

    return 0;
}
