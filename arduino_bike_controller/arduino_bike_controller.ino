
#include "circular_buffer.h"
#include "reed_switch.h"
#include "timers.h"

const int BUFFER_SIZE = 4 * 50;
const int NUM_RELAYS = 4;

// How much "history" in seconds should be stored in the buffer.
const double MEMORY_TIME = 4;

int relayPins[] = {7, 6, 4, 5};
int relayThreshold[] = {60, 200, 350, 420}; // RPM

// A buffer for the number of reed switch activations at a time step.
CircularBuffer<int, BUFFER_SIZE> reed_buffer;
ReedSwitch reed(2);

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.

  Serial.begin(9600);

  for (int i = 0; i < NUM_RELAYS; i++) {
    pinMode(relayPins[i], OUTPUT);
  }
  
}

// The polling period is dependent both on MEMORY_TIME and BUFFER_SIZE.
// Each time it triggers, the current number of activations of the reed switch is added to the buffer.
// This way, a sum over the buffer will result in the total number of reed switch activations in the 
// last MEMORY_TIME seconds.
Timer record_reed(MEMORY_TIME / BUFFER_SIZE, []() {
  int count = reed.resetTriggerCount();
  reed_buffer.push(count);
});

Timer rpm_log(0.25, []() {
  double rpm = reed_buffer.getSum<double>() * 60 / MEMORY_TIME;
  Serial.print("RPMs: ");
  Serial.println(rpm);
});

Timer lights(1, []() {
  // Assuming one reed switch activation is 1 rotation, getSum() / MEMORY_TIME would be the
  // average rotations per second for the last MEMORY_TIME seconds. We multiply by 60 to get the
  // more common unit of rotations per minute. 
  double rpm = reed_buffer.getSum<double>() * 60 / MEMORY_TIME;

  for (int i = 0; i < NUM_RELAYS; i++) {
    digitalWrite(relayPins[i], rpm >= relayThreshold[i] ? HIGH : LOW);
  }
  
});

void loop() {
  // Update our reed switch watcher and our timers.
  reed.tick();
  record_reed.tick();
  rpm_log.tick();
  lights.tick();
}
