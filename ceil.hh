template <int a, int b> struct my_ceil {
  //enum {res = (a < b) ? 1 : 1 + my_ceil<a - b, b>::res};
  enum {res = 1 + my_ceil<a - b < 0 ? 0 : a - b,b>::res};
};

template <int b> struct my_ceil<0, b> {
  enum {res = 0};
};
