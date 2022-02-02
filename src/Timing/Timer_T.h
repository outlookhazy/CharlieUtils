#ifndef TIMER_T_H_
#define TIMER_T_H_

#include "Stopwatch_T.h"

/**
 * Utility classes for time measurement.
 */
namespace Timing {
/**
   * Measures an interval of time, with an option to generate recurring notifications.
   */
  template<TimeSrc timeSrc, uint32_t ticksPerSecond>
  class TimerT {
    public:    
      /**
       * Create new timer
       * @param interval how many timer counts before/between elapse
       * @param start start timer on creation (default false)
       * @param autoReset restart timer immediately after reporting elapsed (default true)
       */
      TimerT(uint32_t interval = DEFAULT_INTERVAL, bool start = false, bool autoReset = true) {
        _interval = interval;
        _autoReset = autoReset;
        if(start) Start();
      }

      /**
       * Start timer measurement. No effect if already running.
       */
      void Start() {
        _stopwatch.Start();
      }

      /**
       * Start timer measurement. Start interval over if already running.
       */
      void Restart() {
        _stopwatch.Restart();
      }

      /**
       * Get current timer interval
       * @return current timer interval
       */
      uint32_t Interval() const { return _interval; }

      /**
       * Set timer interval
       * @param interval timer ticks before/between elapsed
       * @param reset re-start measurement with new interval (default true)
       */
      void Interval(uint32_t interval, bool reset = true) { 
        _interval = interval; 
        if(reset) Restart();
      }

      /**
       * Set timer interval
       * @param interval timer seconds before/between elapsed
       * @param reset re-start measurement with new interval (default true)
       */
      void IntervalSeconds(float interval, bool reset = true) { 
        _interval = interval * ticksPerSecond; 
        if(reset) Restart();
      }

      /**
       * Get automatic reset setting
       * @return timer automatically resets after elapsed
       */
      bool AutoReset() const { return _autoReset; }

      /**
       * Update automatic reset setting
       * @param autoReset timer should automatically reset after elapsed
       */
      void AutoReset(bool autoReset) { _autoReset = autoReset; }

      /**
       * Report whether interval has elapsed (and optionally re-starts measurement of a new interval)
       * @return interval has elapsed since last query
       */
      bool Elapsed() {
        if(_stopwatch.Elapsed() > _interval) {
          _autoReset ? _stopwatch.Restart() : _stopwatch.Reset();
          return true;
        }
        return false;
      }
      
    private:
      constexpr static uint32_t DEFAULT_INTERVAL = 100;
      uint32_t _interval;
      bool _autoReset;
      StopwatchT<timeSrc, ticksPerSecond> _stopwatch;
  };  
}

#endif