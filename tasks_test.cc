#include <iostream>
#include "periodic_task.hh"
#include "taskset.hh"
#include "taskset_io.hh"
#include "ceil.hh"
#include "rta.hh"

typedef task<2000, 4000, 4000> t1;
typedef task<3000, 15000, 15000> t2;
typedef task<5000, 28000, 28000> t3;

template<> void t1::job_body(void *)
{
}

template<> void t2::job_body(void *)
{
}

template<> void t3::job_body(void *)
{
}

//typedef struct TaskSet<t2, struct TaskSet<t1, struct TaskSet<t3, struct EmptyTS> > > ts;
typedef struct TaskSet<t3, struct TaskSet<t2, struct TaskSet<t1, struct EmptyTS> > > ts;

int main()
{
  typedef struct ts_print<ts> p;
  typedef struct rta_check<ts> c;
  struct timespec t;

  p::print();
  clock_gettime(CLOCK_REALTIME, &t);
  ts::start(&t);

  while(1);
  std::cout << c::r << std::endl;
  return 0;
}

