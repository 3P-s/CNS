#include <iostream>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/dsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <cstring>

using namespace std;

// Function to generate a DSA key pair
DSA *generateDSAKeyPair()
{
    DSA *dsa = DSA_new();
    if (!DSA_generate_parameters_ex(dsa, 1024, NULL, 0, NULL, NULL, NULL))
    {
        cerr << "Error generating DSA parameters." << endl;
        DSA_free(dsa);
        return nullptr;
    }
    if (!DSA_generate_key(dsa))
    {
        cerr << "Error generating DSA key pair." << endl;
        DSA_free(dsa);
        return nullptr;
    }
    return dsa;
}

// Function to sign a message using the DSA private key
bool signMessage(DSA *dsa, const string &message, unsigned char **signature, unsigned int *signature_len)
{
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!mdctx)
    {
        cerr << "Error creating EVP_MD_CTX." << endl;
        return false;
    }

    // Initialize the signing process with DSA private key
    if (EVP_SignInit(mdctx, EVP_sha1()) <= 0)
    {
        cerr << "Error initializing signing." << endl;
        EVP_MD_CTX_free(mdctx);
        return false;
    }

    // Add the message to be signed
    if (EVP_SignUpdate(mdctx, message.c_str(), message.length()) <= 0)
    {
        cerr << "Error during signing." << endl;
        EVP_MD_CTX_free(mdctx);
        return false;
    }

    // Allocate memory for the signature
    *signature = (unsigned char *)OPENSSL_malloc(EVP_PKEY_size(EVP_PKEY_new()));
    if (!*signature)
    {
        cerr << "Error allocating memory for signature." << endl;
        EVP_MD_CTX_free(mdctx);
        return false;
    }

    // Finalize the signing process
    if (EVP_SignFinal(mdctx, *signature, signature_len, EVP_PKEY_new()))
    {
        EVP_MD_CTX_free(mdctx);
        return true;
    }
    else
    {
        cerr << "Error finalizing signature." << endl;
        EVP_MD_CTX_free(mdctx);
        return false;
    }
}

// Function to verify a signature using the DSA public key
bool verifySignature(DSA *dsa, const string &message, unsigned char *signature, unsigned int signature_len)
{
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!mdctx)
    {
        cerr << "Error creating EVP_MD_CTX for verification." << endl;
        return false;
    }

    // Initialize the verification process
    if (EVP_VerifyInit(mdctx, EVP_sha1()) <= 0)
    {
        cerr << "Error initializing verification." << endl;
        EVP_MD_CTX_free(mdctx);
        return false;
    }

    // Add the message to be verified
    if (EVP_VerifyUpdate(mdctx, message.c_str(), message.length()) <= 0)
    {
        cerr << "Error during verification." << endl;
        EVP_MD_CTX_free(mdctx);
        return false;
    }

    // Verify the signature
    if (EVP_VerifyFinal(mdctx, signature, signature_len, EVP_PKEY_new()) == 1)
    {
        cout << "Signature verification successful!" << endl;
        EVP_MD_CTX_free(mdctx);
        return true;
    }
    else
    {
        cerr << "Signature verification failed!" << endl;
        EVP_MD_CTX_free(mdctx);
        return false;
    }
}

int main()
{
    // Generate DSA key pair
    DSA *dsa = generateDSAKeyPair();
    if (!dsa)
    {
        cerr << "Key generation failed." << endl;
        return 1;
    }

    // Input message to be signed
    string message = "This is a test message for Digital Signature Standard.";
    cout << "Message to be signed: " << message << endl;

    // Sign the message
    unsigned char *signature = nullptr;
    unsigned int signature_len = 0;
    if (!signMessage(dsa, message, &signature, &signature_len))
    {
        cerr << "Error signing the message." << endl;
        DSA_free(dsa);
        return 1;
    }

    cout << "Message signed successfully." << endl;

    // Verify the signature
    if (!verifySignature(dsa, message, signature, signature_len))
    {
        cerr << "Signature verification failed." << endl;
        DSA_free(dsa);
        return 1;
    }

    // Clean up
    DSA_free(dsa);
    if (signature)
    {
        OPENSSL_free(signature);
    }

    return 0;
}
