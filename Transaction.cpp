#include "Transaction.h"
#include "nlohmann/json.hpp" // ✅ Ensure JSON is included
using json = nlohmann::json; // ✅ Define json namespace

// Constructor
Transaction::Transaction(string sender, string receiver, int amt) {
    sender_public_key = sender;
    receiver_public_key = receiver;
    amount = amt;
}

// Convert transaction to JSON format
string Transaction::to_JSON() {
    return "{ \"sender\": \"" + sender_public_key + "\", \"receiver\": \"" + receiver_public_key + "\", \"amount\": " + to_string(amount) + " }";
}

// Save transaction (in JSON format) to transactions.json (this will be broadcasted)
void Transaction::save_to_file() {
    json t_list;

    ifstream file("transactions.json");
    if (file) {
        file >> t_list;  // Read existing transactions into JSON object
    }
    file.close();

    // Ensure we are working with a JSON array
    if (!t_list.is_array()) {
        t_list = json::array();
    }

    // Append the new transaction
    t_list.push_back({
        {"sender", sender_public_key},
        {"receiver", receiver_public_key},
        {"amount", amount}
    });

    // ✅ FIX: Overwrite file with correctly formatted JSON array
    ofstream outFile("transactions.json");
    outFile << t_list.dump(4); // Pretty-print JSON with indentation
    outFile.close();

    cout << "\nThe transaction has been converted to JSON format and saved in transactions.json." << endl;
}

// Display transaction details
void Transaction::showTransaction() {
    cout << "\nTransaction Details:" << endl;
    cout << "From: " << sender_public_key.substr(0, 20) << "..." << endl;
    cout << "To: " << receiver_public_key.substr(0, 20) << "..." << endl;
    cout << "Amount: " << amount << " MiniBTC" << endl;
}

// Uncomment below if you want to **test `transaction.cpp` independently**
/*
int main() {
    Wallet sender_wallet;  
    string sender_public_key = sender_wallet.public_key;  

    cout << "\n Your public key (auto-retrieved from wallet): " << sender_public_key.substr(0, 20) << "..." << endl;

    cout << "Enter Receiver Public Key: ";
    string receiver_public_key;
    cin >> receiver_public_key;

    cout << "Enter Amount: ";
    int amount;
    cin >> amount;

    Transaction tx(sender_public_key, receiver_public_key, amount);

    tx.showTransaction();
    tx.save_to_file();

    return 0;
}
*/
