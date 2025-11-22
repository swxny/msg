# msg

A simple terminal-based chat client/server in C++ using HTTP, SQLite3, and ncurses.

---

## Features

* CLI chat server and client (`msg run <ip>` / `msg join <ip>`).
* Stores usernames and messages in SQLite3 database.
* Real-time message display with scrolling.
* Default username is `anonymous`.
* Terminal UI using ncurses.

---

## Requirements

* C++17 compiler (g++ recommended)
* [SQLite3](https://www.sqlite.org/) development libraries
* [ncurses](https://invisible-island.net/ncurses/) development libraries
* [cpp-httplib](https://github.com/yhirose/cpp-httplib) (header-only)
* Make

---

## Build

```bash
make
```

The binary will be created in the `build/` folder.

---

## Usage

Start server:

```bash
./build/msg run <ip_address>
```

Join chat as client:

```bash
./build/msg join <ip_address>
```

When joining, you can set a username or use the default `anonymous`. Type messages at the prompt and press Enter to send.

---

## Project Structure

* `main.cpp` – main entry point
* `chat_server.cpp` – server code
* `chat_client.cpp` – client code
* `database.cpp` – SQLite3 database management
* `Makefile` – build system
* `httplib.h` – HTTP library (header-only)

---

## License

This project is licensed under the [GPL-3.0 License](https://www.gnu.org/licenses/gpl-3.0.en.html).

---

## Author

[swxny](https://github.com/swxny)
