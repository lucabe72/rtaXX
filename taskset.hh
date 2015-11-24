template <unsigned int c, unsigned int p, unsigned int d> struct task {
  public:
    enum {execution_time = c};
    enum {period = p};
    enum {deadline = d};
};

struct EmptyTS {};

template <typename T, typename L> struct TaskSet {
//template <template <unsigned int c, unsigned int p, unsigned int d> struct task t, typename L> struct TaskSet {
  typedef T head;
  typedef L tail;
};


