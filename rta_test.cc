#include <iostream>
#include "taskset.hh"
#include "taskset_io.hh"
#include "ceil.hh"
#include "rta.hh"

typedef task<2, 6, 6> t1;
typedef task<3, 12, 12> t2;
typedef task<5, 24, 24> t3;

typedef struct TaskSet<t1, struct TaskSet<t2, struct TaskSet<t3, struct EmptyTS> > > ts;

int main()
{
  typedef struct ts_print<ts> p;
  typedef struct response_time<ts> rt;

  p::print();
  std::cout << rt::r << std::endl;

  return 0;
}

