#include <iostream>
#include <vector>
using namespace std;

// Function to multiply matrices
vector<int> matrixMultiplication(vector<vector<int>> key, vector<int> textVec, int n)
{
    vector<int> result(n);
    for (int i = 0; i < n; i++)
    {
        result[i] = 0;
        for (int j = 0; j < n; j++)
        {
            result[i] += key[i][j] * textVec[j];
        }
        result[i] = result[i] % 26; // Modulo 26 for alphabet
    }
    return result;
}

// Function to encrypt using Hill cipher
string hillEncrypt(string message, vector<vector<int>> key)
{
    int n = key.size(); // Size of key matrix (n x n)
    vector<int> textVec(n);

    // Convert text to vector and multiply with key matrix
    for (int i = 0; i < n; i++)
    {
        textVec[i] = message[i] - 'A'; // Convert A=0, B=1, ..., Z=25
    }

    vector<int> cipherVec = matrixMultiplication(key, textVec, n);

    // Convert back to string
    string cipherText = "";
    for (int i = 0; i < n; i++)
    {
        cipherText += cipherVec[i] + 'A';
    }

    return cipherText;
}

int main()
{
    string message = "ACT";                                             // Message of size n
    vector<vector<int>> key = {{6, 24, 1}, {13, 16, 10}, {20, 17, 15}}; // Example key matrix

    cout << "Original Text: " << message << endl;
    string encrypted = hillEncrypt(message, key);
    cout << "Encrypted Text: " << encrypted << endl;

    return 0;
}
