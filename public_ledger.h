#pragma once
#include <bits/stdc++.h>
#include "block.h"

using namespace std;

class Blockchain
{
public:
    vector<block> chain; // Vector storing blocks of the blockchain

    Blockchain();  //keep in mind developer this constructor has to be used only once in each laptop for the genesis block with no transactions
                   //the rest of the blocks will be added after mining and broadcast processes

    void add_block(vector<string> transactions); // Function to add a new block to the chain

    void display_chain(); // Function to display the blockchain
};
