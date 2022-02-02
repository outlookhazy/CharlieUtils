#ifndef STOPWATCH_T_H_
#define STOPWATCH_T_H_

/**
 * Utility classes for time measurement.
 */
namespace Timing {

  /** Function which supplies a timestamp */
  typedef uint32_t (*TimeSrc)();

  /**
   * Provides a set of functions to measure elapsed time.
   */
  template<TimeSrc timeSrc, uint32_t ticksPerSec>  
  class StopwatchT {  
    public: 

      /**
       * Create new Stopwatch
       * @param start Begin measurement immediately (default false)
       */
      StopwatchT(bool start = false) : _ticksPerSecond(ticksPerSec){
        start ? Restart() : Reset();    
      }

      /**
       * Get measured time (sum of stopped and running)
       * @return Total time measured by Stopwatch
       */
      uint32_t Elapsed() const {
        return _running 
        ? timeSrc() - _timestamp + _stored 
        : _stored;
      }
    
    float ElapsedSeconds() const {
      return Elapsed() / _ticksPerSecond;
    }

      /**
       * Stop timer and clear existing measurement data.
       */
      void Reset() {
        _timestamp = 0;
        _stored = 0;
        _running = false;
      }

      /**
       * Clear existing measurement data and start timer.
       */
      void Restart() {
        _timestamp = timeSrc();
        _stored = 0;
        _running = true;
      }

      /**
       * Start (or resume) timing
       */
      void Start() {
        if(_running) return;
        _timestamp = timeSrc();
        _running = true;        
      }

      /**
       * Stop measurement (storing total elapsed time for later read or resume)
       */
      void Stop() {
        if(!_running) return;
        _stored += timeSrc() - _timestamp;
        _running = false;        
      }
  
    private:
      uint32_t _timestamp = 0;
      uint32_t _stored = 0;
      bool _running = 0;  
    const float _ticksPerSecond;
  };
}

#endif