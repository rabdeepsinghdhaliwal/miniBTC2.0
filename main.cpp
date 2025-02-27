#include <bits/stdc++.h>
#include "public_ledger.h"
#include "mempad.h"
#include "wallet.h"
#include "Transaction.h"
#include "network.h"  // ✅ Integrated network functionality

using namespace std;

// ✅ Function to DELETE transactions.json immediately after broadcasting
void delete_transactions_file() {
    if (remove("transactions.json") == 0) {
        cout << "\n[🗑️] Deleted transactions.json after broadcasting!\n";
    } else {
        cout << "\n[⚠️] Warning: transactions.json could not be deleted!\n";
    }
}

int main()
{
    io_service io;  // ✅ Required for networking functionality
    string peer_ip; // ✅ Enter the peer's IP manually

    // ✅ Step 1: Ask for peer's IP address (Each laptop should enter the other's IP)
    cout << "\nEnter the IP address of the peer node: ";
    cin >> peer_ip;

    // Create mempool instance to retrieve transactions
    // as soon as this instance is created the vector of json objects in which the json files of all the broadcasted transactions will be collected
    // these json object vector transaction_records will then be converted back to strings and stored in each block which will then be mined and added to the local copy of the public ledger class
    // why we are converting to json!?
    // to send the transactions to the peer-to-peer network that we will create in network.cpp via Golang and socket programming
    // this network.cpp has to contain the code for broadcasting the already json format transactions and the local copy of the public_ledger AFTER MINING THE BLOCK
    // whosoever mines first his public_ledger will be broadcasted and everyone will take that public ledger as their main public ledger mining for the further blocks
    // if possible we need to add in the script or code for the deletion of transactions.json after broadcasting a transaction

    // ✅ Step 2: Create a wallet for the sender
    Wallet w1;  // automatically creates an instance of private and a public key

    // ✅ Step 3: Create the first transactions
    string receiver1 = "8455fw5665651carca";  // enter the public addresses of the receivers from their wallets
    string receiver2 = "wlkfchbwoiurh4u904u";

    Transaction t1(w1.public_key, receiver1, 6);   // creating transactions
    t1.save_to_file();    // saving transactions to json files ..... these will be broadcasted over the network 

    Transaction t2(w1.public_key, receiver2, 10);
    t2.save_to_file();

    // ✅ Step 4: Broadcast transactions.json to the network
    send_transaction(io, peer_ip); // ✅ Send transactions to the peer node
    delete_transactions_file();  // ✅ DELETE transactions.json immediately after broadcasting

    // ✅ Step 5: Receive transactions.json from another node
    receive_transaction(io);  // ✅ Receive new transactions from peer

    // ✅ Step 6: Initialize mempool & read transactions
    mempool m1;
    vector<string> all_trans_in_string_format = m1.convert_json_to_strings();

    // ✅ Step 7: Initialize Blockchain with Genesis Block (containing first 2 transactions)
    Blockchain miniBTC_chain;
    miniBTC_chain.add_block(all_trans_in_string_format); // Adding the first non-genesis block

    // ✅ Step 8: Display Blockchain Info
    miniBTC_chain.display_chain();

    // ----------------------------------------
    // ✅ Step 9: Accepting user input for additional transactions
    // ----------------------------------------

    cout << "\n\nCreating additional transactions for the next block...\n";
    int num_transactions;
    cout << "Enter number of transactions for next block: ";
    cin >> num_transactions;
    
    for (int i = 0; i < num_transactions; i++) {
        string receiver;
        int amount;

        cout << "\nEnter Receiver Public Key: ";
        cin >> receiver;

        cout << "Enter Amount: ";
        cin >> amount;

        Transaction new_tx(w1.public_key, receiver, amount);  // creating another transaction
        new_tx.save_to_file();
    }

    // ✅ Step 10: Broadcast and Receive new transactions
    send_transaction(io, peer_ip); // ✅ Send updated transactions.json to peer
    delete_transactions_file();  // ✅ DELETE transactions.json immediately after broadcasting
    receive_transaction(io);  // ✅ Receive transactions.json from peer

    // ✅ Step 11: Read only newly added transactions
    mempool m2;  // Create a fresh mempool to read new transactions
    vector<string> new_transactions = m2.convert_json_to_strings();

    // ✅ Step 12: Add another block with new transactions
    miniBTC_chain.add_block(new_transactions);

    // ✅ Step 13: Display Updated Blockchain Info
    miniBTC_chain.display_chain();

    return 0;
}
