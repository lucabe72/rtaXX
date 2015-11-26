template <unsigned int c, unsigned int p, unsigned int d> struct task {
  private:
    static void job_body(void *parm);
  public:
    static int start(struct timespec *activation_time, void *arg = NULL, int prio = 0)
    {
      int res;
      pthread_t tid;
      pthread_attr_t attrs;
      struct task_instance *task;

      pthread_attr_init(&attrs);
      if (prio) {
        struct sched_param sp;

        res = pthread_attr_setinheritsched(&attrs, PTHREAD_EXPLICIT_SCHED);
        if (res != 0) {
          return -1;
        }
        res = pthread_attr_setschedpolicy(&attrs, SCHED_FIFO);
        if (res != 0) {
          return -2;
        }
        /* creation and activation of the new thread */
        sp.sched_priority = prio;
        res = pthread_attr_setschedparam(&attrs, &sp);
        if (res != 0) {
          return -3;
        }
      }
      task = new struct task_instance(period, activation_time, job_body, arg);
      res = pthread_create(&tid, &attrs, task_instance::task_body, (void *)task);
      pthread_attr_destroy(&attrs);
      if (res) {
        delete task;
        return -4;
      }

      return 0;
    }
    enum {execution_time = c};
    enum {period = p};
    enum {deadline = d};
};

struct EmptyTS {
  static void start(struct timespec * /*activation_time*/, unsigned int) {}
};

template <typename head, typename tail> struct TaskSet {
  typedef head car;
  typedef tail cdr;
  static void start(struct timespec *activation_time, unsigned int prio = 0) {
    car::start(activation_time, NULL, prio);
    cdr::start(activation_time, prio ? prio + 1 : 0);
  }
};


