#include "public_ledger.h"

//keep in mind developer this constructor has to be used only once in each laptop for the genesis block with no transactions
//the rest of the blocks will be added after mining and broadcast processes
Blockchain::Blockchain()
{
    vector<string> empty_transactions;
    block genesis_block(0, "00000", empty_transactions); //creation of the genesis block 
    chain.push_back(genesis_block);
    cout << "\nThe genesis block has been created and successfully added to the blockchain!!"; 
}

//this will directly take transactions in string format and start the mining process immediately/automatically
void Blockchain::add_block(vector<string> transactions)
{
    //transactions.json se json se yeh jo transactions add_block() isme save honi chahiye
    string prev_hash = chain.back().curr_block_hash;
    block new_block(chain.size(), prev_hash, transactions);  //block constructor and mining
    //the size of the chain will be the block's index only.
    chain.push_back(new_block);
    cout << "\n[✅] Block " << new_block.block_index << " has been added to the Blockchain!";
}


//function to display blockchain ledger
void Blockchain::display_chain()
{
    cout << "\n========= Blockchain Ledger =========";
    for (int i = 0; i < chain.size(); i++)
    {
        cout << "\n\nBlock " << i << ":";
        chain[i].show_block_info();
    }
    cout << "\n=====================================\n";
}
