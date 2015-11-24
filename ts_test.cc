#include <iostream>
#include "taskset.hh"
#include "taskset_io.hh"

typedef task<2, 6, 6> t1;
typedef task<3, 12, 12> t2;
typedef task<5, 24, 24> t3;

typedef struct TaskSet<t1, struct TaskSet<t2, struct TaskSet<t3, struct EmptyTS> > > ts;

int main()
{
  typedef struct ts_print<ts> p;

  std::cout << "C = " << t1::execution_time << std::endl;
  std::cout << "P = " << t1::period << std::endl;
  std::cout << "D = " << t1::deadline << std::endl;

  std::cout << "C = " << ts::head::execution_time << std::endl;
  std::cout << "P = " << ts::head::period << std::endl;
  std::cout << "D = " << ts::head::deadline << std::endl;

  p::print();

  return 0;
}

