#include <iostream>
#include <string>
#include "chat_server.h"
#include "chat_client.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage:\n  msg run <ip_addr>\n  msg join <ip_addr>\n";
        return 1;
    }

    std::string cmd = argv[1];
    std::string ip = argv[2];

    if (cmd == "run") {
        run_server(ip);
    } else if (cmd == "join") {
        join_chat(ip);
    } else {
        std::cout << "Unknown command: " << cmd << "\n";
        return 1;
    }

    return 0;
}
