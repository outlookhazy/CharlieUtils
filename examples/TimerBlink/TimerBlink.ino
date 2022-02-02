#include <CharlieUtils.h>

Timer blinkTimer;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // configure the led
  blinkTimer.Interval(1000);    // set timer interval to 1000ms
  blinkTimer.Start();           // start the timer
}

void loop() {
  if(blinkTimer.Elapsed()){ // check if timer has elapsed, it will re-start by default after reporting true
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // set pin to opposite of current state
  }
}
