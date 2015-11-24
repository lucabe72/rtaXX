template <typename ts> struct ts_print {
  static inline void print(void) {
    std::cout << "(" <<ts::car::execution_time << ", " << ts::car::period << ", " << ts::car::deadline << ")\n";
    ts_print<typename ts::cdr>::print();
  }
};

template <> struct ts_print <struct EmptyTS> {
  static inline void print(void) {
    std::cout << std::endl;
  }
};

