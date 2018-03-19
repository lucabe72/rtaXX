template <typename ts, unsigned int r> struct r0 {
  enum {value = r0<typename ts::cdr, r>::value + my_ceil<r, ts::car::period>::res * ts::car::execution_time};
};

template <unsigned int r> struct r0<struct EmptyTS, r> {
  enum {value = 0};
};

template <bool equal, typename ts, unsigned int r, unsigned int d> struct r1 {
  enum {newr = r0<ts, r>::value};
  enum {value = r1<(r == newr) || (r > d), ts, newr, d>::value};
};

template <typename ts, unsigned int r, unsigned int d> struct r1<true, ts, r, d> {
  enum {value = r};
};

template <typename ts, unsigned int d> struct response_time {
  enum {r = r1<false, ts, 1, d>::value};
};

template <typename ts> struct rta_check {
  enum {d = ts::car::deadline};
  enum {r = response_time<ts,ts::car::period>::r};
  static_assert(r < d, "Not schedulable!");
  typedef struct rta_check<typename ts::cdr> r1;
  enum {r_1 = r1::r};
};

template <> struct rta_check<EmptyTS> {
  enum {r = 0};
};

