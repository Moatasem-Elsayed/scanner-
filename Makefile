
CXX = g++
BUILD_DIRECTORY=build/

$(BUILD_DIRECTORY)scanner: $(BUILD_DIRECTORY)main.o $(BUILD_DIRECTORY)decorator.o $(BUILD_DIRECTORY)scan.o
	@$(CXX) $^ -o $(BUILD_DIRECTORY)scanner

$(BUILD_DIRECTORY)scan.o: scan.cpp $(BUILD_DIRECTORY)
	@$(CXX) --std=c++17 -c scan.cpp -o $(BUILD_DIRECTORY)scan.o
$(BUILD_DIRECTORY)decorator.o: decorator.cpp $(BUILD_DIRECTORY)
	@$(CXX) --std=c++17 -c decorator.cpp -o $(BUILD_DIRECTORY)decorator.o
$(BUILD_DIRECTORY)main.o: main.cpp $(BUILD_DIRECTORY)
	@$(CXX) --std=c++17 -c main.cpp -o $(BUILD_DIRECTORY)main.o

$(BUILD_DIRECTORY):
	@mkdir build
clean:
	@rm -rf $(BUILD_DIRECTORY)
