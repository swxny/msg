CXX = g++
CXXFLAGS = -std=c++17 -Wall -pthread `pkg-config --cflags sqlite3 ncurses`
LDFLAGS = `pkg-config --libs sqlite3 ncurses`

SRCS = main.cpp chat_server.cpp chat_client.cpp database.cpp
OBJS = $(patsubst %.cpp, build/%.o, $(SRCS))
TARGET = msg

# Create build folder if it doesn't exist
BUILD_DIR = build
$(shell mkdir -p $(BUILD_DIR))

all: $(TARGET) clean_o

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile source files into build folder
build/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Remove object files after building
clean_o:
	rm -f build/*.o

clean: clean_o
	rm -f $(TARGET)
