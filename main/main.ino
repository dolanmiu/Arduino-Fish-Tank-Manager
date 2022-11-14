#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const Adafruit_SSD1306 display(128, 32, &Wire, -1);

const unsigned long MILLIS_PER_MINUTE = 60000L;
const unsigned long MILLIS_PER_DAY = 86400000L;
const unsigned long MILLIS_PER_HOUR = 3600000L;
const unsigned long MILLIS_PER_SECOND = 1000L;

// Electric Relays
const int WATER_OUTPUT_RELAY = 2;
const int WATER_INPUT_RELAY = 3;

const int WATER_OUTPUT_VALVE = 4;
const int WATER_INPUT_VALVE = 5;

const int WATER_PUMP = 6;
const int DOSING_PUMP = 7;
// End Electric Relays

const int CYCLE_BUTTON = 8;
const int WATER_IN_BUTTON = 9;
const int WATER_OUT_BUTTON = 10;
const int DOSING_BUTTON = 11;
const int STOP_BUTTON = 12;

unsigned long NEXT_CYCLE_START_MILLIS = MILLIS_PER_DAY;

enum STATE_ENUM {CYCLE, OFF, PUMP_IN, PUMP_OUT, DOSING};

// Global Variables
uint8_t state = OFF;


void setup() {
  Serial.begin(9600);

  pinMode(CYCLE_BUTTON, INPUT);
  digitalWrite(CYCLE_BUTTON, HIGH);

  pinMode(WATER_IN_BUTTON, INPUT);
  digitalWrite(WATER_IN_BUTTON, HIGH);

  pinMode(WATER_OUT_BUTTON, INPUT);
  digitalWrite(WATER_OUT_BUTTON, HIGH);

  pinMode(DOSING_BUTTON, INPUT);
  digitalWrite(DOSING_BUTTON, HIGH);

  pinMode(STOP_BUTTON, INPUT);
  digitalWrite(STOP_BUTTON, HIGH);

  pinMode(WATER_OUTPUT_RELAY, OUTPUT);
  pinMode(WATER_INPUT_RELAY, OUTPUT);
  pinMode(WATER_OUTPUT_VALVE, OUTPUT);
  pinMode(WATER_INPUT_VALVE, OUTPUT);
  pinMode(WATER_PUMP, OUTPUT);
  pinMode(DOSING_PUMP, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  initDisplay();

  // TODO: setCycleStartTime();
}

void loop() {
  tickTime();
  
  switch (state) {
    case OFF:
      offState();
      break;
    case CYCLE:
      cycleState();
      break;
    case PUMP_IN:
      pumpInState();
      break;
    case PUMP_OUT:
      pumpOutState();
      break;
    case DOSING:
      dosingState();
      break;
    default:
      offState();
      break;
  }

  readInputs();
}

void readInputs() {
  int val = digitalRead(CYCLE_BUTTON);
  if (val == 0) {
    state = CYCLE;
  }

  val = digitalRead(WATER_IN_BUTTON);
  if (val == 0) {
    state = PUMP_IN;
  }

  val = digitalRead(WATER_OUT_BUTTON);
  if (val == 0) {
    state = PUMP_OUT;
  }

  val = digitalRead(DOSING_BUTTON);
  if (val == 0) {
    state = DOSING;
  }

  val = digitalRead(STOP_BUTTON);
  if (val == 0) {
    state = OFF;
  }
}

void setCycleStartTime() {
  NEXT_CYCLE_START_MILLIS = calculateIntervalTime() * MILLIS_PER_MINUTE;
  Serial.println("Setting next start time:");
  Serial.println(NEXT_CYCLE_START_MILLIS);
}


