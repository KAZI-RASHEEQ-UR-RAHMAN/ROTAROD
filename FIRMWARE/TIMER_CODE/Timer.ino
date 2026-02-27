#include <Arduino.h>
#include <TM1637Display.h>

// -------- Timer Struct --------
struct TimerUnit {
  TM1637Display display;
  int platePin;
  int buttonPin;
  bool running;
  unsigned long startMillis;
  unsigned long elapsedMillis;
  bool lastButtonState;
  unsigned long buttonPressTime;
};

// -------- Pins for each timer --------
TimerUnit timers[] = {
  { TM1637Display(2, 3), A0, 4, false, 0, 0, HIGH, 0 }, // Timer 1
  { TM1637Display(5, 6), A1, 7, false, 0, 0, HIGH, 0 }, // Timer 2
  { TM1637Display(8, 9), A2, 10, false, 0, 0, HIGH, 0 } // Timer 3
};

const int numTimers = sizeof(timers) / sizeof(timers[0]);
const unsigned long longPressTime = 1000; // ms for reset

// -------- Functions --------
void updateDisplay(TimerUnit &t) {
  unsigned long totalSeconds = t.elapsedMillis / 1000;
  int minutes = totalSeconds / 60;
  int seconds = totalSeconds % 60;
  int displayVal = minutes * 100 + seconds;
  t.display.showNumberDecEx(displayVal, 0b01000000, true); // show MM:SS
}

void handleButton(TimerUnit &t) {
  bool state = digitalRead(t.buttonPin);

  if (t.lastButtonState == HIGH && state == LOW) {
    // Button pressed
    t.buttonPressTime = millis();
  }
  else if (t.lastButtonState == LOW && state == HIGH) {
    // Button released
    unsigned long pressDuration = millis() - t.buttonPressTime;
    if (pressDuration < longPressTime) {
      // Short press = toggle start/pause
      if (!t.running) {
        t.running = true;
        t.startMillis = millis();
      } else {
        t.running = false;
        t.elapsedMillis += millis() - t.startMillis;
      }
    } else {
      // Long press = reset
      t.running = false;
      t.elapsedMillis = 0;
    }
  }
  t.lastButtonState = state;
}

void handlePlate(TimerUnit &t) {
  if (digitalRead(t.platePin) == LOW && t.running) {
    // Plate touched, pause
    t.running = false;
    t.elapsedMillis += millis() - t.startMillis;
  }
}

void setup() {
  for (int i = 0; i < numTimers; i++) {
    pinMode(timers[i].platePin, INPUT_PULLUP);
    pinMode(timers[i].buttonPin, INPUT_PULLUP);
    timers[i].display.setBrightness(0x0f);
    timers[i].display.showNumberDecEx(0, 0b01000000, true);
  }
}

void loop() {
  for (int i = 0; i < numTimers; i++) {
    handleButton(timers[i]);
    handlePlate(timers[i]);

    if (timers[i].running) {
      unsigned long now = millis();
      timers[i].elapsedMillis += (now - timers[i].startMillis);
      timers[i].startMillis = now;
    }

    updateDisplay(timers[i]);
  }
}