CXX=g++
CXXFLAGS=-std=c++17 -Wall -pthread `pkg-config --cflags sqlite3 ncurses`
LDFLAGS=`pkg-config --libs sqlite3 ncurses`

SRCS=main.cpp chat_server.cpp chat_client.cpp database.cpp
OBJS=$(patsubst %.cpp,build/%.o,$(SRCS))

TARGET=build/msg

# Ensure build directory exists
$(shell mkdir -p build)

all: $(TARGET)

# Build target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Build object files
build/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build
