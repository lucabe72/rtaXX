#define _POSIX_C_SOURCE 200112L
#include <sys/time.h>
#include <sched.h>
#include <time.h>
#include <pthread.h>
#include <cstdlib>
#include <cstring>

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

template <unsigned int c, unsigned int p, unsigned int d>
void task<c,p,d>::wait_next_activation(void)
{
    clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &r, NULL);
    timespec_add_us(&r, period);
}

template <unsigned int c, unsigned int p, unsigned int d>
void *task<c,p,d>::task_body(void *parm)
{
  struct task<c,p,d> *t = reinterpret_cast<struct task<c,p,d> *>(p);

  t->run();

  return NULL;
}

template <unsigned int c, unsigned int p, unsigned int d>
void task<c,p,d>::run(void)
{
  while(1) {
    wait_next_activation();
    job_body(job_arg);
  }
}

template <unsigned int c, unsigned int p, unsigned int d>
int task<c,p,d>::start(struct timespec *activation_time, void *arg)
{
  int res;

  memcpy(&r, activation_time, sizeof(struct timespec));
  job_arg = arg;
  res = pthread_create(&tid, NULL, task_body, (void *)this);
  if (res) {
    return -1;
  }

  return 0;
}
