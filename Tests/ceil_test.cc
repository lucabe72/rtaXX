#include <iostream>
#include "ceil.hh"

int main()
{
  int c = my_ceil<28,5>::res;

  std::cout << c << std::endl;

  return 0;
}
