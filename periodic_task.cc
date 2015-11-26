#define _POSIX_C_SOURCE 200112L
#include <sys/time.h>
#include <sched.h>
#include <time.h>
#include <pthread.h>
#include <cstdlib>
#include <cstring>

#include "periodic_task.hh"
#include "taskset.hh"

#define NSEC_PER_SEC 1000000000ULL
static inline void timespec_add_us(struct timespec *t, unsigned int d)
{
    d *= 1000;
    d += t->tv_nsec;
    while (d >= NSEC_PER_SEC) {
        d -= NSEC_PER_SEC;
        t->tv_sec += 1;
    }
    t->tv_nsec = d;
}

void task_instance::wait_next_activation(void)
{
    clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &r, NULL);
    timespec_add_us(&r, period);
}

void *task_instance::task_body(void *parm)
{
  struct task_instance *t = reinterpret_cast<struct task_instance *>(parm);

  t->run();

  return NULL;
}

void task_instance::run(void)
{
  while(1) {
    wait_next_activation();
    job_body(job_arg);
  }
}

task_instance::task_instance(unsigned int p, struct timespec *t, void (*body)(void *a), void *arg)
{
  memcpy(&r, t, sizeof(struct timespec));  
  period = p;
  job_body = body;
  job_arg = arg;
}

#if 0
template <unsigned int c, unsigned int p, unsigned int d>
int task<c,p,d>::start(struct timespec *activation_time, void *arg)
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
#endif
