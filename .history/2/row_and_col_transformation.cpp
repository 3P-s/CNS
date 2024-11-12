#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to generate the column order based on the key
vector<int> getColumnOrder(string key)
{
    vector<pair<char, int>> keyWithIndices;
    for (int i = 0; i < key.size(); i++)
    {
        keyWithIndices.push_back({key[i], i});
    }

    // Sort based on key characters
    sort(keyWithIndices.begin(), keyWithIndices.end());

    vector<int> order;
    for (auto &p : keyWithIndices)
    {
        order.push_back(p.second);
    }

    return order;
}

// Function to encrypt using Row and Column Transformation Cipher
string rowColumnEncrypt(string plaintext, string key)
{
    int columns = key.size();
    int rows = (plaintext.size() + columns - 1) / columns; // Round up for rows

    // Pad the plaintext if necessary
    while (plaintext.size() < rows * columns)
    {
        plaintext += 'X'; // Padding with 'X'
    }

    // Create a matrix row-wise
    vector<vector<char>> matrix(rows, vector<char>(columns));
    int index = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix[i][j] = plaintext[index++];
        }
    }

    // Get column order based on the key
    vector<int> columnOrder = getColumnOrder(key);

    // Read the matrix column-wise in the order determined by the key
    string ciphertext = "";
    for (int col : columnOrder)
    {
        for (int i = 0; i < rows; i++)
        {
            ciphertext += matrix[i][col];
        }
    }

    return ciphertext;
}

// Function to decrypt using Row and Column Transformation Cipher
string rowColumnDecrypt(string ciphertext, string key)
{
    int columns = key.size();
    int rows = (ciphertext.size() + columns - 1) / columns; // Calculate rows

    // Create an empty matrix
    vector<vector<char>> matrix(rows, vector<char>(columns));

    // Get the column order based on the key
    vector<int> columnOrder = getColumnOrder(key);

    // Fill the matrix column-wise in the order determined by the key
    int index = 0;
    for (int col : columnOrder)
    {
        for (int i = 0; i < rows; i++)
        {
            matrix[i][col] = ciphertext[index++];
        }
    }

    // Read the matrix row-wise to get the plaintext
    string plaintext = "";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            plaintext += matrix[i][j];
        }
    }

    // Remove padding if any
    while (plaintext.back() == 'X')
    {
        plaintext.pop_back();
    }

    return plaintext;
}

int main()
{
    string plaintext;
    cout << "Enter the text to be encrypted: ";
    getline(cin>>ws, plaintext);

    string key;
    cout << "Enter the key: ";
    cin >> key;

    string encrypted = rowColumnEncrypt(plaintext, key);
    cout << "Encrypted Text (Row-Column): " << encrypted << endl;

    string decrypted = rowColumnDecrypt(encrypted, key);
    cout << "Decrypted Text (Row-Column): " << decrypted << endl;

    return 0;
}
