
#ifndef BC_TIMERS
#define BC_TIMERS 1

#include <functional-vlpp.h>
#include <Basic.h>
#include <Function.h>
#include <Pointer.h>

/* 
 * The timer class is used to run a callback periodically.
 * 
 * Every `interval` seconds, f will be executed. tick() should be called often
 * so that the timer runs at the right time.
 * 
 */
class Timer {
  unsigned long interval;
  const vl::Func<void()> f;
  unsigned long lastTime;

public:
  explicit Timer(double interval, const vl::Func<void()> f) : interval((unsigned long)(1000000 * interval)), f(f), lastTime(0) {}
  
  void tick() {
    unsigned long curr_time = micros();

    if (curr_time - lastTime > interval) {
      f();
      lastTime = curr_time;
    }
  }
  
};


#endif

