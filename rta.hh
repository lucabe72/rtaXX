template <typename ts, unsigned int r> struct r0 {
  enum {value = r0<typename ts::tail, r>::value + my_ceil<r, ts::head::period>::res * ts::head::execution_time};
};

template <unsigned int r> struct r0<struct EmptyTS, r> {
  enum {value = 0};
};

template <bool equal, typename ts, unsigned int r> struct r1 {
//  enum {r1 = (r == r0<ts, r>::rt) ? r : response_time<ts, r0<ts, r>::rt>::r1};
  enum {value = r1<r == r0<ts, r>::value, ts, r0<ts, r>::value>::value};
//  enum {r1 = response_time<ts, r0<ts, r>::rt>::r1};
//  enum {r1 = response_time<struct EmptyTS, r0<ts, r>::rt>::r1};
};

template <typename ts, unsigned int r> struct r1<true, ts, r> {
  enum {value = r};
};

template <typename ts> struct response_time {
  enum {r = r1<false, ts, 1>::value};
};
