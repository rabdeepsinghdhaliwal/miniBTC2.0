#pragma once
#include<bits/stdc++.h>
#include"mempad.h"
#include"wallet.h"
#include"Transaction.h"

using namespace std;

class block
{
    public:
    int block_index;    //for the genesis block is 0
    string prev_block_hash;  //for the genesis block is 0000
    string curr_block_hash;
    int nonce;
    vector<string> transactions;  //for storing transactions (maybe in string format from the mempad.cpp!?) how do we import this from there ?

    block(int b , string ph , vector<string> txs); // Constructor

    string custom_hash(int nonce);  //this is a custom hash function that we are using 

    string mining_block(); //Mining process that keeps checking hash criteria

    void show_block_info(); //Displays block information
};
