
void offState() {
  const long timeLeft = NEXT_CYCLE_START_MILLIS - getSystemTime();

  drawOffText("Idle. Next Cycle in: ", timeToString(timeLeft));

  closeValves();
  turnOffPump();
  setWaterRelayToRemoveWater();
  turnOffDosingPump();
  checkIfNeedToCycle();
}

String timeToString(const long t) {
  const char str[12];

  const long hours = floor(t / MILLIS_PER_HOUR);
  const long mins = floor((t % MILLIS_PER_HOUR) / MILLIS_PER_MINUTE);
  const long secs = floor((t % MILLIS_PER_MINUTE) / MILLIS_PER_SECOND);
  const long milliSecs = t % 1000;

  const bool isBlink = milliSecs > 500;
  const char* timeFormat = isBlink ? "%02ld:%02ld:%02ld" : "%02ld %02ld %02ld";

  sprintf(str, timeFormat, hours, mins, secs);
  return str;
}

void drawOffText(const String text, const String t) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(text);
  display.setCursor(15, 15);
  display.setTextSize(2);
  display.println(t);

  display.display();
}
