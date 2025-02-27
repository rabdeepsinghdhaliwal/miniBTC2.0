#include "block.h"

// Constructor - Initializes the block and mines it
block::block(int b , string ph , vector<string> txs)
{
    block_index = b;
    prev_block_hash = ph;
    nonce = 0;
    transactions = txs;
    curr_block_hash = mining_block();  //this will be confirmed after mining process completes by repeatedly finding the custom hash till the hash below the set requirement is not met.
}

// Custom hash function that we are using
string block::custom_hash(int nonce)
{
    int hash = (block_index * nonce);
    for(int i = 0 ; i < prev_block_hash.length() ; i++)
    {
        hash += (int)prev_block_hash[i];  //ascii value sum into the product of blockindex and nonce where nonce is the variable that will/can be altered as per our will if the requirements are not met
    }
    return to_string(hash);
}

// Mining process that keeps checking hash criteria
string block::mining_block()
{
   cout<<"\nThe process of mining and trials and error have begun:-";
   
   if(block_index == 0)
   {
    cout<<"\n[⛓️] Genesis block detected. Assigning fixed hash.";
    return "GENESIS";  //set the current block hash of genesis block this.
   }
   
   string target_prefix = "1";  //as of now this is the criteria we have set
   string working_on_hash;

   while(true)
   {
     working_on_hash = custom_hash(nonce);  //since nonce has started from 0 only as clearly stated in the constructor
     if(working_on_hash.substr(0,1) == target_prefix)
     {
        break;
     }
     nonce++;
   }   
   if(working_on_hash.length() > 5)
   {
     working_on_hash = working_on_hash.substr(0,5);
   }
   cout<<"\nThe block has been mined successfully!!! \nNew block hash: "<<working_on_hash<<"\nnonce: "<<nonce;
   return working_on_hash;
}

// Displays block information
void block::show_block_info() {
    cout << "\nBlock Details:";
    cout << "\n-------------------------------";
    cout << "\nBlock Index: " << block_index;
    cout << "\nPrevious Hash: " << prev_block_hash;
    cout << "\nCurrent Hash: " << curr_block_hash;
    cout << "\nNonce: " << nonce;
    cout << "\nTransactions:";
    
    if (transactions.empty()) {
        cout << "\nNo transactions in this block!";
    } else {
        cout << "\n---------------------";
        for (int i = 0; i < transactions.size(); i++)
        {
            cout << "\nTransaction " << i + 1 << ":\n";
            cout << transactions[i] << endl;
            cout << "---------------------";
        }
    }
    cout << "\n-------------------------------------------------\n";
}
