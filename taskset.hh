template <unsigned int c, unsigned int p, unsigned int d> struct task {
  private:
    static void job_body(void *parm);
  public:
    static int start(struct timespec *activation_time, void *arg)
    {
      int res;
      pthread_t tid;
      struct task_instance *task;

      task = new struct task_instance(period, activation_time, job_body, arg);
      res = pthread_create(&tid, NULL, task_instance::task_body, (void *)task);
      if (res) {
        return -1;
      }

      return 0;
    }
    enum {execution_time = c};
    enum {period = p};
    enum {deadline = d};
};

struct EmptyTS {
  static void start(struct timespec *activation_time) {}
};

template <typename head, typename tail> struct TaskSet {
  typedef head car;
  typedef tail cdr;
  static void start(struct timespec *activation_time) {
    car::start(activation_time, NULL);
    cdr::start(activation_time);
  }
};


