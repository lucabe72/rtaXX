template <typename ts, unsigned int r> struct r0 {
  enum {value = r0<typename ts::cdr, r>::value + my_ceil<r, ts::car::period>::res * ts::car::execution_time};
};

template <unsigned int r> struct r0<struct EmptyTS, r> {
  enum {value = 0};
};

template <bool equal, typename ts, unsigned int r> struct r1 {
  enum {value = r1<r == r0<ts, r>::value, ts, r0<ts, r>::value>::value};
};

template <typename ts, unsigned int r> struct r1<true, ts, r> {
  enum {value = r};
};

template <typename ts> struct response_time {
  enum {r = r1<false, ts, 1>::value};
};

template <typename ts> struct rta_check {
  enum {r = response_time<ts>::r};
  enum {d = ts::car::deadline};
  static_assert(r < d, "Not schedulable!");
  typedef struct rta_check<typename ts::cdr> r1;
  enum {r_1 = r1::r};
};

template <> struct rta_check<EmptyTS> {
  enum {r = 0};
};

