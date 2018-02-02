LINK.o=$(CXX) $(LDFLAGS)
CXXFLAGS=-Wall -Wextra -pedantic -Wno-enum-compare -std=c++0x
LDFLAGS=-pthread
TESTS=ceil_test rta_test ts_test tasks_test
LDLIBS=-lrt
VPATH=..
CPPFLAGS=-I..

all: $(TESTS)

tasks_test:: tasks_test.o periodic_task.o

clean:
	rm -f *.d
	rm -f *.o
	rm -f $(TESTS)

%.d: %.cc
	$(CXX) $(CPPFLAGS) -MM -MF $@ $<

include ceil_test.d rta_test.d ts_test.d tasks_test.d periodic_task.d
