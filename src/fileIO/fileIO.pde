// FILE IO B/W PROCESSING & ARDUINO
import processing.serial.*;

Serial myPort;  // Create object from Serial class
PrintWriter output;
int total = 0;
int BUFFER = 10; // Should be 10 chars from LOGGED to start of TOTAL

void setup() {
  myPort = new Serial(this, "COM3", 9600);
  output = createWriter("data/minutes-log.txt");
  output.println("LOGGED    TOTAL");
  output.flush();
  myPort.bufferUntil('\n');
}

// KEEP THE DRAW FUNCTION IN 
// (allows it to run and wait for serial event)
void draw() {
} 

void serialEvent (Serial myPort) {
  String val = myPort.readStringUntil('\n');
  int toLog = filter(val);
  total += toLog;
  String spaces = getSpaces(toLog);
  String message = toLog + spaces + total;
  output.println(message);
  output.flush();
}

String getSpaces (int logged) {
  int spaces;
  String result = "";
  
  if (logged <= 9) {
    // one digit
    spaces = BUFFER - 1;
  } else if (logged <= 99) {
    // two digits
    spaces = BUFFER - 2;
  } else {
    // three digits
    spaces = BUFFER - 3;
  }
  
  for (int i = 0; i < spaces; i++) {
    result += " ";
  }
  return result;
}


int filter (String s) {
  // cut off the last char (the newline)
  int len = s.length();
  String substring = s.substring(0, len - 1);
  int result = int (substring);
  return result;
}
