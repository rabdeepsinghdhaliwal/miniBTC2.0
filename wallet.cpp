#include "wallet.h"


Wallet::Wallet() {
    balance = 20;
    priv_key = generate_random_priv_key();
    public_key = generate_public_key(priv_key);
}

// Generate Public Key from Private Key
string Wallet::generate_public_key(string &priv) {
    BIGNUM *private_key = BN_new();
    BN_hex2bn(&private_key, priv.c_str());
    EC_GROUP *group = EC_GROUP_new_by_curve_name(NID_secp256k1);
    EC_POINT *public_key = EC_POINT_new(group);
    EC_POINT_mul(group, public_key, private_key, NULL, NULL, NULL);

    char *public_key_hex = EC_POINT_point2hex(group, public_key, POINT_CONVERSION_UNCOMPRESSED, NULL);
    string public_key_str(public_key_hex);

    OPENSSL_free(public_key_hex);
    EC_POINT_free(public_key);
    EC_GROUP_free(group);
    BN_free(private_key);

    return public_key_str;
}

// Generate a 256-bit Random Private Key
string Wallet::generate_random_priv_key() {
    unsigned char private_key[32];
    RAND_bytes(private_key, sizeof(private_key));
    stringstream ss;
    for (int i = 0; i < 32; i++) {
        ss << hex << setw(2) << setfill('0') << (int)private_key[i];
    }
    return ss.str();
}

void Wallet::show_wallet() {
    cout << "Balance: " << balance << " MiniBTC" << endl;
    cout << "Private Key: " << priv_key << endl;
    cout << "Public Key: " << public_key << endl;
}


/*
int main() {
    Wallet wallet;
    wallet.show_wallet(); // Display wallet details
    return 0;
}
*/
