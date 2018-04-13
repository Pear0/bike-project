
#ifndef BC_REED_SWITCH
#define BC_REED_SWITCH 1


/**
 * The ReedSwitch class encompasses monitoring a physical switch (such as a reed switch) and counting the number of
 * times the switch has been activated. It makes assumptions about the switch including that the pin will be pulled LOW
 * when the switch is activated and some mechanism (eg. a pull-up resistor) will raise the voltage when the switch is open.
 * 
 * tick() should be called often otherwise some switch activations may be missed.
 * 
 * Currently this class does implement any sort of debouncing.
 */
class ReedSwitch {
  const int pin;
  bool is_activated;
  bool was_activated;
  int trigger_count;

  bool isActivated() {
    return digitalRead(pin) == LOW;
  }

public:
  explicit ReedSwitch(int pin) : pin(pin) {
    pinMode(pin, INPUT);
  }

  void tick() {
    was_activated = is_activated;
    is_activated = isActivated();

    if (is_activated && !was_activated) {
      trigger_count++;
    }
  }

  /*
   * This method exposes the number of times the switch has been triggered and simultaneously clears the internal count.
   */
  int resetTriggerCount() {
    int count = trigger_count;
    trigger_count = 0;
    return count;
  }

};


#endif

