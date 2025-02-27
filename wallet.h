#pragma once
#include <bits/stdc++.h>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <openssl/obj_mac.h> // secp256k1 curve
#include <openssl/bn.h>      // Big number calculations
#include <openssl/ec.h>      // Elliptic curve cryptography

using namespace std;

class Wallet {
public:
    int balance;
    string priv_key;
    string public_key;

    
    Wallet();

    // Function Declarations
    string generate_public_key(string &priv);
    string generate_random_priv_key();
    void show_wallet();
};
