CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRC = src/main.cpp src/server.cpp src/datastore.cpp src/parser.cpp
OUT = build/redis_server

all:
	mkdir -p build
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -rf build
