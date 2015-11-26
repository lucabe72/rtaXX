template <typename ts> struct task_factory {
  private:
    static int start_p(struct timespec *activation_time, unsigned int period, void (*job_body)(void *a), void *arg = NULL, int prio = 0)
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
  public:
    static void start(struct timespec *activation_time, unsigned int prio = 0) {
      start_p(activation_time, ts::car::period, ts::car::job_body, NULL, prio);
      task_factory<typename ts::cdr>::start(activation_time, prio ? prio + 1 : 0);
    }
};

template <> struct task_factory<EmptyTS> {
  static void start(struct timespec * /*activation_time*/, unsigned int) {}
};
