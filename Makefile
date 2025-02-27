CXX = g++
CXXFLAGS = -O1 -std=c++20
LDFLAGS = 

LONGNUMBER_SRC = LongNumber.cpp
PI_SRC = pi.cpp
TEST_SRC = test.cpp

PI_TARGET = pi_program
TEST_TARGET = test_program

all: $(PI_TARGET) $(TEST_TARGET)

$(PI_TARGET): $(PI_SRC) $(LONGNUMBER_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST_TARGET): $(TEST_SRC) $(LONGNUMBER_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

pi: $(PI_TARGET)
	./$(PI_TARGET) $(precision)

clean:
	rm -f $(PI_TARGET) $(TEST_TARGET)

rebuild: clean all

.PHONY: all test pi clean rebuild
