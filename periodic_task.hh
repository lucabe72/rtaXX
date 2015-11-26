struct task_instance {
  private:
    pthread_t tid;
    struct timespec r;
    unsigned int period;
    void *job_arg;
    void wait_next_activation(void);
    void run(void);
  public:
    static void *task_body(void *parm);
    void (*job_body)(void *arg);
    task_instance(unsigned int p, struct timespec *t, void (*body)(void *a), void *arg);
};
/*
struct periodic_task {
  private:
    pthread_t tid;
    struct timespec r;
    void *job_arg;
    void job_body(void *p);
    void wait_next_activation(void);
  public:
    void run(void);
    int start(struct timespec *activation_time, void *arg);
};
*/
