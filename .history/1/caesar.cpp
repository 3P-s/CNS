#include <iostream>
using namespace std;

// Function to encrypt text using Caesar Cipher
string caesarEncrypt(string text, int s)
{
    string result = "";

    // Traverse text
    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] == ' ')
        {
            result += ' ';
            continue;
        }
        // Encrypt uppercase characters
        if (isupper(text[i]))
        {
            result += char(int(text[i] + s - 65) % 26 + 65);
        }
        // Encrypt lowercase characters
        else
        {
            result += char(int(text[i] + s - 97) % 26 + 97);
        }
    }
    return result;
}

// Function to decrypt text using Caesar Cipher
string caesarDecrypt(string text, int s)
{
    return caesarEncrypt(text, 26 - s); // Decryption is reverse of encryption
}

int main()
{
    cout << "Enter the text to be encrypted: ";
    string text;
    getline(cin, text);
    cout << "Enter the shift value: ";
    int s;
    cin >> s;

    cout << "Original Text: " << text << endl;
    string encrypted = caesarEncrypt(text, s);
    cout << "Encrypted Text: " << encrypted << endl;
    cout << "Decrypted Text: " << caesarDecrypt(encrypted, s) << endl;

    return 0;
}
