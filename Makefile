TESTS=ceil_test rta_test ts_test
CXXFLAGS=-Wall -Wextra -pedantic -std=c++0x

all: $(TESTS)

clean:
	rm -f $(TESTS)
