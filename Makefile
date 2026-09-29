CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic -O2
CPPFLAGS = -Iinclude
TARGET = formula-vm
SRCS = src/main.cpp src/formula_vm.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: all clean sample

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

src/%.o: src/%.cpp include/formula_vm.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

sample: $(TARGET)
	./$(TARGET) --file samples/demo.fvm

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe
