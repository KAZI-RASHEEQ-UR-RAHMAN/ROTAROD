#include <Arduino.h>
#include <TM1637Display.h>

// ---------------- Pin Definitions ----------------
#define STEP_PIN 3 
#define DIR_PIN 2 
#define BTN_UP 5 
#define BTN_DOWN 6 

// TM1637 display pins
#define CLK_PIN 7 
#define DIO_PIN 8 

// ---------------- Objects ----------------
TM1637Display display(CLK_PIN, DIO_PIN);

// ---------------- Motor & Stepper Variables ----------------
volatile int rpm = 0;
const int rpmMin = 0;
const int rpmMax = 250; // safe max RPM
const int stepsPerRev = 200;   // full steps
const int microsteps = 4;      // TB6600 set to 1/4
const long totalSteps = stepsPerRev * microsteps;

unsigned long lastStepTime = 0;
unsigned long stepInterval = 1000000; // µs between steps

// Button state tracking
bool lastUpState = HIGH;
bool lastDownState = HIGH;
unsigned long lastPressTimeUp = 0;
unsigned long lastPressTimeDown = 0;
unsigned long repeatDelay = 500;   // first repeat delay
unsigned long repeatInterval = 200; // auto increment interval

// ---------------- Functions ----------------
void updateStepInterval() {
  if (rpm > 0) {
    stepInterval = (60L * 1000000L) / (rpm * totalSteps); 
  } else {
    stepInterval = 1000000; // effectively stops
  }
}

void changeRPM(int delta) {
  rpm += delta;
  if (rpm < rpmMin) rpm = rpmMin;
  if (rpm > rpmMax) rpm = rpmMax;
  updateStepInterval();
  display.showNumberDec(rpm, true); // update display
}

void handleButton(int pin, bool &lastState, unsigned long &lastPress, int delta) {
  bool state = digitalRead(pin);

  if (lastState == HIGH && state == LOW) {
    // Button just pressed
    changeRPM(delta);
    lastPress = millis();
  }
  else if (state == LOW && (millis() - lastPress) > repeatDelay) {
    // Button held, auto repeat
    if ((millis() - lastPress) > repeatInterval) {
      changeRPM(delta);
      lastPress = millis();
    }
  }
  lastState = state;
}

// ---------------- Setup ----------------
void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);

  digitalWrite(DIR_PIN, HIGH); // fixed direction

  // Enable motor driver permanently
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW); // ENA LOW = motor enabled

  display.setBrightness(0x0f); // max brightness
  display.showNumberDec(rpm, true);

  updateStepInterval();
}

// ---------------- Loop ----------------
void loop() {
  // Handle buttons
  handleButton(BTN_UP, lastUpState, lastPressTimeUp, 5);    // step +5 RPM
  handleButton(BTN_DOWN, lastDownState, lastPressTimeDown, -5); // step -5 RPM

  // Stepper pulse generation
  if (rpm > 0) {
    unsigned long now = micros();
    if (now - lastStepTime >= stepInterval) {
      lastStepTime = now;
      digitalWrite(STEP_PIN, HIGH);
      delayMicroseconds(5); // optimized pulse width for smooth motion
      digitalWrite(STEP_PIN, LOW);
    }
  }
}