all:
	g++ main.cpp mutex.cpp OSPriority.cpp -std=c++17 -lpthread -g -o PriorityCeiling