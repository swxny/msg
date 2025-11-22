#include "chat_client.h"
#include <iostream>
#include <vector>
#include <string>
#include "httplib.h"
#include <ncurses.h>

void join_chat(const std::string& ip) {
    initscr();
    cbreak();
    echo();          // typed characters are visible
    scrollok(stdscr, TRUE);

    std::string username = "anonymous";
    mvprintw(0,0,"Enter username (default: anonymous): ");
    char buf[32];
    getnstr(buf, 31);
    if (buf[0] != '\0') username = buf;

    httplib::Client cli(ip.c_str(), 8080);

    std::vector<std::string> messages; // store messages for scrolling

    while(true) {
        // Fetch messages
        auto res = cli.Get("/fetch");
        if (res && res->status == 200) {
            std::string body = res->body;

            // Split body into lines
            messages.clear();
            size_t prev = 0, pos;
            while ((pos = body.find('\n', prev)) != std::string::npos) {
                messages.push_back(body.substr(prev, pos - prev));
                prev = pos + 1;
            }
            if(prev < body.size())
                messages.push_back(body.substr(prev));

            // Show only last lines that fit the terminal
            size_t max_lines = LINES - 3;
            size_t start = messages.size() > max_lines ? messages.size() - max_lines : 0;

            clear();
            mvprintw(0,0,"Username: %s\n", username.c_str());

            int row = 1;
            for(size_t i = start; i < messages.size(); ++i) {
                mvprintw(row++, 0, "%s", messages[i].c_str());
            }

            mvprintw(LINES-2,0,"Type message: ");
            move(LINES-2,13);
            refresh();
        }

        // Read input
        char msg[256];
        getnstr(msg, 255);

        if(msg[0]!='\0') {
            httplib::Params params;
            params.emplace("user", username);
            params.emplace("msg", msg);
            cli.Post("/send", params);
        }
    }

    endwin();
}
