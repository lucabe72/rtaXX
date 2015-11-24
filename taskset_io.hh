template <typename ts> struct ts_print {
  static inline void print(void) {
    std::cout << "(" <<ts::head::execution_time << ", " << ts::head::period << ", " << ts::head::deadline << ")\n";
    ts_print<typename ts::tail>::print();
  }
};

template <> struct ts_print <struct EmptyTS> {
  static inline void print(void) {
    std::cout << std::endl;
  }
};

