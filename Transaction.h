#pragma once
#include <bits/stdc++.h>
#include <fstream>
#include "wallet.h" // Include wallet to get sender's public key

using namespace std;

class Transaction {
public:
    string sender_public_key;   // Retrieved from Wallet object
    string receiver_public_key; // Entered manually after running the script
    int amount;

    // Constructor Declaration
    Transaction(string sender, string receiver, int amt);

    // Convert transaction to JSON format
    string to_JSON();

    // Save transaction(in json format) to transactions.json (this will be broadcasted)
    void save_to_file();

    // Display transaction details
    void showTransaction();
};
