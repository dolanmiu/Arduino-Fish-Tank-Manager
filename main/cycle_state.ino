const unsigned long CYCLE_DURATION = 10000L;
const unsigned long CYCLE_HALF_DURATION = CYCLE_DURATION / 2;

bool isFirstCycleStart = true;

void cycleState() {
  if (isFirstCycleStart) {
    resetTime();
    isFirstCycleStart = false;
  }

  turnOffDosingPump();

  const unsigned long delta = getSystemTime();

  if (delta < CYCLE_HALF_DURATION) {
    drawCycleText("Pumping water in", (float)delta / (float)CYCLE_HALF_DURATION);
    openValves();
    setWaterRelayToRemoveWater();
    turnOnPump();
  } else if (delta < CYCLE_DURATION) {
    drawCycleText("Pumping water out", (float)(delta - CYCLE_HALF_DURATION) / (float)CYCLE_HALF_DURATION);
    openValves();
    setWaterRelayToAddWater();
    turnOnPump();
  } else {
    // Finished
    turnOffPump();
    closeValves();
    state = OFF;
    isFirstCycleStart = true;
    setCycleStartTime();
  }
}

void drawCycleText(const String text, const float ratio) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  display.println("Cycling. ");
  display.println("Pumping water in");
  const int margin = 3;
  const int yPosition = 18;
  const int height = 14;
  const int width = 128;
  display.drawRect(margin, yPosition, width - margin - margin, height, WHITE);
  display.fillRect(margin + 2, yPosition + 2, (ratio * (float)128) - margin - margin - 4, height - 4, WHITE);
  const int percent = (int)(ratio * 100);
  const int characterOffset = percent < 10 ? 2 : 5;
  display.setCursor(64 - characterOffset, 21);
  display.setTextColor(WHITE, BLACK);
  display.print(percent);
  display.display();
}

void checkIfNeedToCycle() {
  long timeLeft = NEXT_CYCLE_START_MILLIS - getSystemTime();

  if (timeLeft < 0) {
    state = CYCLE;
  }
}