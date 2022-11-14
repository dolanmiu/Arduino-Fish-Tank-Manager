unsigned long smoothedPotValue = 0;

unsigned long calculateIntervalTime() {
  const int potValue = analogRead(DURATION_DIAL);

  const long difference = potValue - smoothedPotValue;
  const long delta = difference / 8;
  smoothedPotValue += delta;
  constrain(smoothedPotValue, 0, 1023);

  const int mins = map(smoothedPotValue, 0, 1023, 1, MINS_PER_HOUR * 2);

  if (mins > 108L) {
    return MINS_PER_DAY;
  }

  return mins;
}

String formatIntervalTime(const unsigned long mins) {
  if (mins < MINS_PER_HOUR) {
    return String(mins) + " mins";
  } else if (mins == MINS_PER_DAY) {
    return "1 DAY";
  } else {
    const unsigned long mMins = mins % MINS_PER_HOUR;
    const unsigned long hours = mins / MINS_PER_HOUR;
    
    const String output = String(hours) + "h, " + String(mMins) + "m";

    return output;
  }
}
