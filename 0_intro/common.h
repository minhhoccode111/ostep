#ifndef __common_h__
#define __common_h__

#include <assert.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>

double GetTime() {
  // timeval is a structure that holds the time in seconds (tv_sec) and
  // microseconds (tv_usec)
  struct timeval t;
  // The gettimeofday() function populates the timeval structure t with the
  // current time. It returns 0 on success and -1 on failure, which is stored in
  // rc
  int rc = gettimeofday(&t, NULL);
  // The assert() ensures that gettimeofday() succeeded. If rc is not 0, the
  // program will terminate, indicating an error occurred in retrieving the
  // time.
  assert(rc == 0);
  // The function returns the current time as a double, combining the seconds
  // (t.tv_sec) and microseconds (t.tv_usec). t.tv_usec is divided by 1e6
  // (1,000,000) to convert microseconds to seconds, so the total result is the
  // time in seconds, including fractions of a second
  return (double)t.tv_sec + (double)t.tv_usec / 1e6;
}

// wait for `howlong` seconds
void Spin(int howlong) {
  double t = GetTime();
  while ((GetTime() - t) < (double)howlong)
    ; // do nothing in loop
}

#endif // __common_h__
