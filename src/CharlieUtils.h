#ifndef CHARLIEUTILS_H_
#define CHARLIEUTILS_H_

#include <Arduino.h>

#include "Timing/Stopwatch_T.h"
#include "Timing/Timer_T.h"

using Timing::StopwatchT;
using Timing::TimerT;

typedef StopwatchT<millis, 1000> Stopwatch;
typedef TimerT<millis, 1000> Timer;


#endif