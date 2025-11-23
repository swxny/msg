CXX = g++
CXXFLAGS = -std=c++17 -Wall -pthread `pkg-config --cflags sqlite3 ncurses`
LDFLAGS = `pkg-config --libs sqlite3 ncurses`

SRCS = main.cpp chat_server.cpp chat_client.cpp database.cpp
OBJS = $(patsubst %.cpp, build/%.o, $(SRCS))
TARGET = build/msg

BUILD_DIR = build

# Ensure build folder exists
$(shell mkdir -p $(BUILD_DIR))

# Default target: build executable, then remove object files
all: $(TARGET)
	$(MAKE) clean_objects

# Link the executable in build/
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile source files into build/
build/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Remove only object files after building
clean_objects:
	@rm -f $(OBJS)

# Full clean: remove object files + executable
clean: clean_objects
	@rm -f $(TARGET)
