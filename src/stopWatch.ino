/* BUTTONS */
int onButton = 12;
int resetButton = 13;

/* CONTROLS */
int toReset = false;
int startCount = -1;

/* DATA */
int seconds = 0;
int minutes = 0;
unsigned long startTime = 0;
int pauseTime = 0;
int pausedTime = 0;

/* DISPLAY */
/* Order: D1 D2 D3 D4 */
/* Note: D1 not used (not enough pins)*/
int a = 2;
int b = 3;
int c = 4;
int d = 5;
int e = 6;
int f = 7;
int g = 8;
int D2 = 10;
int D3 = 11;
int D4 = 9;

void setup() {
  /* Setup socket for sending data to log file */
  Serial.begin(9600);
  /* Setup pins */
  pinMode(onButton, OUTPUT);
  pinMode(resetButton, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
}

void loop() {
  if (digitalRead(resetButton) == HIGH) { // Check for button push
    doReset();
  }
  if (digitalRead(onButton) == HIGH) {
    doStartStop();
  }
  if (startCount == 1) {
    count();
  }
  if (seconds >= 0) { // Filter out any misleading values that result from lag
    updateClock(minutes);
  }
}

void doReset() {
  if (seconds > 0) { // Only send positive, non-zero values to the log
    Serial.println(seconds);
  }
  seconds = 0;
  pauseTime = 0;
  pausedTime = 0;
  startCount = 1;
  startTime = millis();
  delay(50); // Prevent accidental button reads
}

void doStartStop() {
  startCount *= -1;
  if (startCount == -1) {
    // Pause
    pauseTime = millis();
  } else if (startCount == 1) {
    // Resume
    pausedTime += millis() - pauseTime;
  }
  delay(50); // Prevent accidental button reads
}

void count() {
  seconds = (millis() - startTime - pausedTime) / 1000;
  minutes = (millis() - startTime - pausedTime) / 60000;
}
