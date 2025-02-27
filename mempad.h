#pragma once
#include <bits/stdc++.h>
//#include "network.cpp"   // the network.cpp will receive the transactions.json in json format and store/use it here in the mempool
#include "nlohmann/json.hpp"
#include "Transaction.h"
#include <fstream>

// will have to delete the old transactions after the process of adding to the public ledger is complete !! 

using namespace std;
using json = nlohmann::json;

class mempool
{
public:
    vector<json> transactions_rec;  // collection of json objects/format of all the transactions. this will be imported in block.cpp

    // Constructor Declaration
    mempool();

    // Read transactions from transactions.json file
    void read_transaction_from_file();

    // Convert JSON transactions into a vector of formatted strings (for usage in block.cpp)
    vector<string> convert_json_to_strings();

    // Display transactions currently in mempool
    void show_mempool();
};
