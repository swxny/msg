CXX = g++
CXXFLAGS = -std=c++17 -Wall -pthread `pkg-config --cflags sqlite3 ncurses`
LDFLAGS = `pkg-config --libs sqlite3 ncurses`

SRCS = main.cpp chat_server.cpp chat_client.cpp database.cpp
OBJS = $(patsubst %.cpp, build/%.o, $(SRCS))
TARGET = msg

BUILD_DIR = build

# Ensure build folder exists
$(shell mkdir -p $(BUILD_DIR))

all: $(TARGET) clean_objects

# Link the executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile source files into build folder
build/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Remove only the object files after building
clean_objects:
	@rm -f $(OBJS)

# Optional: full clean
clean: clean_objects
	@rm -f $(TARGET)
