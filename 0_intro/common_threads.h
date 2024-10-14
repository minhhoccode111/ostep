#ifndef __common_threads_h__ // Prevents multiple inclusions of the header file.
#define __common_threads_h__

#include <assert.h>  // For using the assert() function to handle errors.
#include <pthread.h> // For using POSIX threads (pthread).
#include <sched.h>   // For thread scheduling functions.

#ifdef __linux__       // If the code is being compiled on a Linux system.
#include <semaphore.h> // For using semaphores on Linux.
#endif

// Wrapper macro for pthread_create that asserts successful thread creation.
#define Pthread_create(thread, attr, start_routine, arg)                       \
  assert(pthread_create(thread, attr, start_routine, arg) == 0);

// Wrapper macro for pthread_join that asserts successful thread joining.
#define Pthread_join(thread, value_ptr)                                        \
  assert(pthread_join(thread, value_ptr) == 0);

// Wrapper macro for pthread_mutex_lock that asserts successful mutex lock.
#define Pthread_mutex_lock(m) assert(pthread_mutex_lock(m) == 0);

// Wrapper macro for pthread_mutex_unlock that asserts successful mutex unlock.
#define Pthread_mutex_unlock(m) assert(pthread_mutex_unlock(m) == 0);

// Wrapper macro for pthread_cond_signal that asserts successful condition
// signal.
#define Pthread_cond_signal(cond) assert(pthread_cond_signal(cond) == 0);

// Wrapper macro for pthread_cond_wait that asserts successful condition wait.
#define Pthread_cond_wait(cond, mutex)                                         \
  assert(pthread_cond_wait(cond, mutex) == 0);

// Initializes a pthread mutex and asserts successful initialization.
#define Mutex_init(m) assert(pthread_mutex_init(m, NULL) == 0);

// Locks a pthread mutex and asserts successful lock.
#define Mutex_lock(m) assert(pthread_mutex_lock(m) == 0);

// Unlocks a pthread mutex and asserts successful unlock.
#define Mutex_unlock(m) assert(pthread_mutex_unlock(m) == 0);

// Initializes a pthread condition variable and asserts successful
// initialization.
#define Cond_init(cond) assert(pthread_cond_init(cond, NULL) == 0);

// Sends a signal to a pthread condition variable and asserts successful signal.
#define Cond_signal(cond) assert(pthread_cond_signal(cond) == 0);

// Waits on a pthread condition variable and asserts successful wait.
#define Cond_wait(cond, mutex) assert(pthread_cond_wait(cond, mutex) == 0);

#ifdef __linux__ // Only include the semaphore-related code if compiling on
                 // Linux.

// Initializes a semaphore with a given initial value and asserts successful
// initialization.
#define Sem_init(sem, value) assert(sem_init(sem, 0, value) == 0);

// Decrements (locks) the semaphore and asserts successful wait operation.
#define Sem_wait(sem) assert(sem_wait(sem) == 0);

// Increments (unlocks) the semaphore and asserts successful post operation.
#define Sem_post(sem) assert(sem_post(sem) == 0);

#endif // __linux__

#endif // __common_threads_h__
