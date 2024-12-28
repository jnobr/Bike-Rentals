CXX = g++ 
CXXFLAGS = -g -Wall -Wextra -Wpedantic

.PHONY: all
all: main 

.PHONY: check
check: bike_tests

bike_tests: bike_tests.cpp system_helper_functions.o bike.o
	$(CXX) $(CXXFLAGS) -o $@ $^
main: main.cpp bike.o system_helper_functions.o
	$(CXX) $(CXXFLAGS) -o $@ $^
bike.o: bike.cpp bike.h 
	$(CXX) $(CXXFLAGS) -c $^
system_helper_functions.o: system_helper_functions.cpp system_helper_functions.h 
	$(CXX) $(CXXFLAGS) -c $^

.PHONY: clean
clean:
	rm *.o 
	rm main
