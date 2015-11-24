#include <iostream>
#include "taskset.hh"
#include "taskset_io.hh"
#include "ceil.hh"
#include "rta.hh"

typedef task<2, 4, 4> t1;
typedef task<3, 15, 15> t2;
typedef task<5, 28, 28> t3;

typedef struct TaskSet<t2, struct TaskSet<t1, struct TaskSet<t3, struct EmptyTS> > > ts;
//typedef struct TaskSet<t3, struct TaskSet<t2, struct TaskSet<t1, struct EmptyTS> > > ts;

int main()
{
  typedef struct ts_print<ts> p;
  typedef struct rta_check<ts> c;

  p::print();
  std::cout << c::r << std::endl;
  return 0;
}

