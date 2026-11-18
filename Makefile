CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic -O2
CPPFLAGS = -Iinclude
TARGET = formula-vm
TEST_TARGET = test_formula_vm
SRCS = src/main.cpp src/formula_vm.cpp
LIB_SRCS = src/formula_vm.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: all clean sample test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

src/%.o: src/%.cpp include/formula_vm.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(TEST_TARGET): tests/test_formula_vm.cpp $(LIB_SRCS) include/formula_vm.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ tests/test_formula_vm.cpp $(LIB_SRCS)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

sample: $(TARGET)
	./$(TARGET) --file samples/demo.fvm

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe $(TEST_TARGET) $(TEST_TARGET).exe
