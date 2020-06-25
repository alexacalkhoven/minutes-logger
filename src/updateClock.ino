void updateClock(int val) {
  // Max at 999 (3 digits of display)
  if (val >= 999){
    updateDisplay(999);
  } else {
    updateDisplay(val);
  }
}
