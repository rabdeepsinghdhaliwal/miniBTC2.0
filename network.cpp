//golang and c++ local network interface
//the json file in transaction is imported in networking.cpp and then sent/broadcasted over to the network 
//#include<bits/stdc++.h>
//#include"Transaction.cpp"  // or I don not know as of now that the transactions.json is to be included in here ?
//this should be integrated with the wallet.cpp somehow mate !
//this will use only the public keys as addressees generated to send or receive the broadcasts from the network mate
#include "network.h"

void receive_transaction(io_service& io) {
    tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 12345)); // Listening on port 12345
    tcp::socket socket(io);
    acceptor.accept(socket);

    cout << "[📥] Receiving transaction file..." << endl;

    ofstream outFile("transactions.json", ios::binary);
    if (!outFile) {
        cerr << "[❌] Error: Could not open transactions.json for writing!" << endl;
        return;
    }

    char buffer[1024]; // Buffer to receive data
    boost::system::error_code ec;

    while (true) {
        size_t len = socket.read_some(boost::asio::buffer(buffer), ec);
        if (ec == boost::asio::error::eof) break; // End of file (normal)
        if (ec) {
            cerr << "[❌] Error: " << ec.message() << endl;
            break;
        }
        outFile.write(buffer, len);
    }

    outFile.close();
    cout << "[✅] Transaction received and saved to transactions.json!" << endl;
}

void send_transaction(io_service& io, const string& server_ip) {
    tcp::socket socket(io);
    socket.connect(tcp::endpoint(ip::address::from_string(server_ip), 12345)); // Connect to server

    cout << "[📤] Sending transactions.json file..." << endl;

    ifstream inFile("transactions.json", ios::binary);
    if (!inFile) {
        cerr << "[❌] Error: Could not open transactions.json for reading!" << endl;
        return;
    }

    char buffer[1024]; // Buffer to send data
    while (!inFile.eof()) {
        inFile.read(buffer, sizeof(buffer));
        size_t bytesRead = inFile.gcount();
        boost::system::error_code ec;
        socket.write_some(boost::asio::buffer(buffer, bytesRead), ec);

        if (ec) {
            cerr << "[❌] Error sending data: " << ec.message() << endl;
            break;
        }
    }

    inFile.close();
    cout << "[✅] Transaction file sent successfully!" << endl;
}
