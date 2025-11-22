#include "database.h"
#include <sqlite3.h>
#include <sstream>

sqlite3* db;

void init_db() {
    if (sqlite3_open("chat.db", &db)) {
        throw std::runtime_error("Cannot open DB");
    }

    const char* users_sql = "CREATE TABLE IF NOT EXISTS users(id INTEGER PRIMARY KEY, name TEXT);";
    const char* messages_sql = "CREATE TABLE IF NOT EXISTS messages(id INTEGER PRIMARY KEY, user TEXT, msg TEXT);";
    sqlite3_exec(db, users_sql, nullptr, nullptr, nullptr);
    sqlite3_exec(db, messages_sql, nullptr, nullptr, nullptr);
}

void insert_message(const std::string& user, const std::string& msg) {
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, "INSERT INTO messages(user,msg) VALUES(?,?);", -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, user.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, msg.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

std::string get_all_messages() {
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, "SELECT user,msg FROM messages;", -1, &stmt, nullptr);
    std::ostringstream oss;
    while(sqlite3_step(stmt) == SQLITE_ROW){
        std::string user = reinterpret_cast<const char*>(sqlite3_column_text(stmt,0));
        std::string msg = reinterpret_cast<const char*>(sqlite3_column_text(stmt,1));
        oss << user << ": " << msg << "\n";
    }
    sqlite3_finalize(stmt);
    return oss.str();
}
