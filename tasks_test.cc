#include <iostream>
#include "periodic_task.hh"
#include "taskset.hh"
#include "taskset_io.hh"
#include "ceil.hh"
#include "rta.hh"

typedef task<20000, 40000, 40000> t1;
typedef task<30000, 150000, 150000> t2;
typedef task<50000, 280000, 280000> t3;

template<> void t1::job_body(void *)
{
  int i,j;
 
  for (i=0; i<3; i++) {
    for (j=0; j<1000; j++) ;
    printf("1");
    fflush(stdout);
  }
}

template<> void t2::job_body(void *)
{
  int i,j;

  for (i=0; i<5; i++) {
    for (j=0; j<10000; j++) ;
    printf("2");
    fflush(stdout);
  }
}

template<> void t3::job_body(void *)
{
  static uint64_t previous;
  uint64_t t;
  struct timespec tv;

  if (previous == 0) {
    clock_gettime(CLOCK_REALTIME, &tv);
    previous = tv.tv_sec * 1000ULL + tv.tv_nsec / 1000000ULL;
  }

  clock_gettime(CLOCK_REALTIME, &tv);
  t = tv.tv_sec * 1000ULL + tv.tv_nsec / 1000000ULL;
  printf("\tT: %llu\n", t - previous);
  previous = t;
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
  ts::start(&t, 10);

  while(1);
  std::cout << c::r << std::endl;
  return 0;
}

