#include "chat_server.h"
#include "database.h"
#include <iostream>
#include <fstream>
#include <mutex>
#include "lib/httplib.h"

std::mutex db_mutex;

void run_server(const std::string& ip) {
    init_db(); // from database.cpp
    std::ofstream log("chat.log", std::ios::app);

    httplib::Server svr;

    // Send message
    svr.Post("/send", [](const httplib::Request &req, httplib::Response &res){
        std::string user = req.get_param_value("user");
        std::string msg = req.get_param_value("msg");
        std::lock_guard<std::mutex> lock(db_mutex);
        insert_message(user, msg); // database.cpp function
        res.set_content("ok", "text/plain");
    });

    // Fetch messages
    svr.Get("/fetch", [](const httplib::Request &req, httplib::Response &res){
        std::lock_guard<std::mutex> lock(db_mutex);
        res.set_content(get_all_messages(), "text/plain"); // database.cpp function
    });

    std::cout << "     _ __ ___  ___  __ _ \n";
    std::cout << "    | '_ ` _ \\/ __|/ _` |\n";
    std::cout << "    | | | | | \\__ \\ (_| |\n";
    std::cout << "    |_| |_| |_|___/\\__, |\n";
    std::cout << "                   |___/ \n";
    std::cout << "\n";
    std::cout << "Server running at " << ip << ":8080\n";

    svr.listen(ip.c_str(), 8080);
}
