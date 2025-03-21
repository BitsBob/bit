CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
LDFLAGS += -lssl -lcrypto

SRC = src/init.cpp src/utils.cpp src/add.cpp src/main.cpp src/commit.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = bit

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
