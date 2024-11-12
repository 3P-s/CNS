#include <iostream>
#include <string>
using namespace std;

// Function to encrypt using Rail Fence Cipher
string railFenceEncrypt(string plaintext, int rails)
{
    // Create an empty matrix
    string matrix[rails];

    int row = 0;
    bool down = true;

    // Fill the matrix in a zigzag manner
    for (int i = 0; i < plaintext.length(); i++)
    {
        matrix[row].push_back(plaintext[i]);

        // Reverse direction when we hit the top or bottom rail
        if (down)
        {
            row++;
            if (row == rails)
            {
                row = rails - 2;
                down = false;
            }
        }
        else
        {
            row--;
            if (row == -1)
            {
                row = 1;
                down = true;
            }
        }
    }

    // Concatenate all rows to get the ciphertext
    string ciphertext = "";
    for (int i = 0; i < rails; i++)
    {
        ciphertext += matrix[i];
    }
    return ciphertext;
}

// Function to decrypt using Rail Fence Cipher
string railFenceDecrypt(string ciphertext, int rails)
{
    string matrix[rails];

    int length = ciphertext.length();
    int row = 0, index = 0;
    bool down = true;

    // Create an empty boolean matrix to mark the zigzag path
    bool mark[length][rails];
    for (int i = 0; i < rails; i++)
        for (int j = 0; j < length; j++)
            mark[j][i] = false;

    // Mark the places where the characters will go
    for (int i = 0; i < length; i++)
    {
        mark[i][row] = true;

        if (down)
        {
            row++;
            if (row == rails)
            {
                row = rails - 2;
                down = false;
            }
        }
        else
        {
            row--;
            if (row == -1)
            {
                row = 1;
                down = true;
            }
        }
    }

    // Fill the marked positions with ciphertext characters
    for (int i = 0; i < rails; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if (mark[j][i])
            {
                matrix[i].push_back(ciphertext[index++]);
            }
        }
    }

    // Rebuild the original plaintext from the zigzag path
    row = 0;
    down = true;
    string plaintext = "";
    for (int i = 0; i < length; i++)
    {
        plaintext += matrix[row][0];
        matrix[row].erase(matrix[row].begin());

        if (down)
        {
            row++;
            if (row == rails)
            {
                row = rails - 2;
                down = false;
            }
        }
        else
        {
            row--;
            if (row == -1)
            {
                row = 1;
                down = true;
            }
        }
    }

    return plaintext;
}

int main()
{
    cout<<"Enter the text to be encrypted: ";
    string plaintext;
    getline(cin, plaintext);

    int rails = 3;

    string encrypted = railFenceEncrypt(plaintext, rails);
    cout << "Encrypted Text (Rail Fence): " << encrypted << endl;

    string decrypted = railFenceDecrypt(encrypted, rails);
    cout << "Decrypted Text (Rail Fence): " << decrypted << endl;

    return 0;
}
