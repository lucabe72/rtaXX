template <unsigned int c, unsigned int p, unsigned int d> struct task {
  public:
    enum {execution_time = c};
    enum {period = p};
    enum {deadline = d};
};

struct EmptyTS {};

template <typename head, typename tail> struct TaskSet {
  typedef head car;
  typedef tail cdr;
};


