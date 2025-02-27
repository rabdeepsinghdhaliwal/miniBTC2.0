#pragma once
#include <iostream>
#include <fstream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;
using ip::tcp;

void receive_transaction(io_service& io);  // Function to receive transactions.json
void send_transaction(io_service& io, const string& server_ip); // Function to send transactions.json
