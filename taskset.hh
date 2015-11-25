template <unsigned int c, unsigned int p, unsigned int d> struct task {
  private:
    pthread_t tid;
    struct timespec r;
    void *job_arg;
    void job_body(void *parm);
    void wait_next_activation(void);
    static void *task_body(void *parm);
  public:
    void run(void);
    int start(struct timespec *activation_time, void *arg);
    enum {execution_time = c};
    enum {period = p};
    enum {deadline = d};
};

struct EmptyTS {};

template <typename head, typename tail> struct TaskSet {
  typedef head car;
  typedef tail cdr;
};


