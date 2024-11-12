#include <iostream>
#include <openssl/sha.h> // Include the OpenSSL library for SHA-1
#include <iomanip>
#include <sstream>
#include <cstring>

using namespace std;

// Function to convert bytes to a hexadecimal string
string toHexString(const unsigned char *digest, int length)
{
    stringstream ss;
    ss << hex << setfill('0');
    for (int i = 0; i < length; ++i)
    {
        ss << setw(2) << static_cast<unsigned int>(digest[i]);
    }
    return ss.str();
}

// Function to calculate the SHA-1 hash of the input text
string calculateSHA1(const string &text)
{
    unsigned char digest[SHA_DIGEST_LENGTH]; // 20-byte array to store the result
    SHA_CTX ctx;

    // Initialize the SHA-1 context
    SHA1_Init(&ctx);

    // Update the context with the text (input)
    SHA1_Update(&ctx, text.c_str(), text.size());

    // Finalize the calculation and store the result in digest
    SHA1_Final(digest, &ctx);

    // Convert the digest to a hexadecimal string and return
    return toHexString(digest, SHA_DIGEST_LENGTH);
}

int main()
{
    // Input text to hash
    string inputText;
    cout << "Enter text to calculate SHA-1 hash: ";
    getline(cin, inputText);

    // Calculate the SHA-1 hash
    string hash = calculateSHA1(inputText);

    // Display the result
    cout << "SHA-1 Digest: " << hash << endl;

    return 0;
}
