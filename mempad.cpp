//has the transaction handling and things
//the broadcasts are received here and this file is included in some other mining place that is in the block.cpp output of this file 
// #include"Transaction.cpp" will take the json file from here and send the json file from here to other nodes
//assuming the json file is taken/received via network.cpp we need to decipher it and structure it in order to get it into the block class via # include3 mempad in the block.cpp

#include "mempad.h"

//instance of this object will be created and imported into the block.cpp via main()of the block.cpp
mempool::mempool() {
    cout << "Reading transactions (from the transactions.json received from the network of nodes)" << endl;
    read_transaction_from_file();
}

//this is the name of the file from which things will be read very crucial file this is the file that will be transmitted from place to place
void mempool::read_transaction_from_file() {
    ifstream file("transactions.json");  
    if (!file.is_open()) {
        cout << "\nThe file could not be opened";
        return;
    }

    json t_list;  
    file >> t_list;   //content of the file i.e. transaction list into the json object
    file.close();

    for (int i = 0; i < t_list.size(); i++) {
        json tx = t_list[i];   //small json object will be pushed in the json vector of the mempool class
        transactions_rec.push_back(tx);
        cout << "Transaction loaded: " << tx.dump(4) << endl;
    }
}

//this function is for the usage in the block.cpp
// THIS BELOW NEEDS TO BE MODIFIED TO TAKE THE JSON OBJECT VECTOR AND CONVERT IT INTO THE STR4ING OBJECT VECTOR IF ANY CONFUSION ARISES
vector<string> mempool::convert_json_to_strings()   
{
    vector<string> transaction_strings;  

    ifstream file("transactions.json");
    if (!file) {
        cout << "\nError: Could not open transactions.json!";
        return transaction_strings;  // Return empty vector if file cannot be opened
    }

    json t_list;
    file >> t_list;
    file.close();

    if (!t_list.is_array()) {
        cout << "\nError: JSON file is not an array!";
        return transaction_strings;
    }

    for (int i = 0; i < t_list.size(); i++) {
        json tx = t_list[i];

        string tx_string = "Sender: " + tx["sender"].get<string>() + 
                           " -> Receiver: " + tx["receiver"].get<string>() + 
                           " | Amount: " + to_string(tx["amount"].get<int>()) + " MiniBTC";

        transaction_strings.push_back(tx_string);
    }

    // ✅ Debug: Print the transactions being passed
    cout << "\nConverted Transactions to Strings:";
    for (int i = 0; i < transaction_strings.size(); i++) {
        cout << "\nTransaction " << i + 1 << ": " << transaction_strings[i];
    }

    return transaction_strings;
}

//to check the mempool so created
void mempool::show_mempool() {
    cout << "\nThe transactions to be processed are:- ";
    for (int i = 0; i < transactions_rec.size(); i++) {
        json tx = transactions_rec[i];
        cout << "\nSender's public key: " << tx["sender"].get<string>().substr(0, 20) << "...";
        cout << "\nReceiver's public key: " << tx["receiver"].get<string>().substr(0, 20) << "..."; 
        cout << "\nThe amount: " << tx["amount"].get<int>() << " MiniBTC" << endl;
    }
}

/*
int main()
{
    //instance of the object created in network.cpp
    mempool m1;
    return 0;
}
*/
