LINK.o=$(CXX)
CXXFLAGS=-Wall -Wextra -pedantic -Wno-enum-compare -std=c++0x
TESTS=ceil_test rta_test ts_test

all: $(TESTS)

clean:
	rm -f *.d
	rm -f *.o
	rm -f $(TESTS)

%.d: %.cc
	$(CXX) -MM -MF $@ $<

include ceil_test.d rta_test.d ts_test.d 
