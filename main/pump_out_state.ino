void pumpOutState() {
  openValves();
  setWaterRelayToRemoveWater();
  turnOnPump();
  turnOffDosingPump();

  drawPumpOutText();
  checkIfPumpOutNeedsToStop();
}

void checkIfPumpOutNeedsToStop() {
  int val = digitalRead(WATER_OUT_BUTTON);
  if (val == 1) {
    state = OFF;
  }
}

void drawPumpOutText() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Pumping Out Water");
  display.setCursor(62, 15);
  display.setTextSize(2);
  display.println(createLoadingSpinner());

  display.display();
}
