/*
 * A motor driver receiver with additional LED sequence.
 *
 * This program reads data from the serial channel and decodes it
 * into commands. Each command follows this format:
 *  ^COMMAND_NAME[:COMMAND_DATA]$
 *
 * The first character is "^" and the last one is "$".
 * Some commands may have additional data, which must follow the
 * command name with ":".
 *
 * The supported commands are:
 *
 * ^CHANGE_SEQUENCE$
 *  * Iterates through the LED sequences that have been implemented
 *    in this program.
 * ^MOVEMENT:x,y$
 *  * Changes the power deliever to the left and right motor.
 *    x , is the horizontal axis and ranges from 0 to 1023.
 *    y , is the vertical axis and ranges from 0 to 1023.
 *    These ranges map to values that range from 0 to 255.
 *    Because the motors seem to make some noise at lower power levels, this
 *    application only delivers power to the motors if the power level is
 *    greater than 30.
 */

/*
 * An abstract class that defines the contract each LED sequence must implement.
 *
 * Each sequence is supposed to upate the current sequence at a certain intervals.
 * The LED is controlled by a 74HC595 shift register. So the sequence returns an
 * integer. In this case the integer must range from 0 to 255.
 */
class Sequence {
public:

  /*
   * The next integer in the sequence. It can actually be any value, even the same
   * one in case the sequence does not change for whatever reason.
   */
  virtual int next() = 0;
};

/*
 * A sequence that moves from left to right and then back from right to left.
 */
class Horizontal: public Sequence {
private:

  int sequence[8] = {1, 2, 4, 8, 16, 32, 64, 128};
  int length = 8;
  int index = -1;
  bool increasing = true;

public:

  int next() {
    if (isIncreasing()) {
      return nextToRight();
    } else {
      return nextToLeft();
    }
  }

private:

  bool isIncreasing() {
    return increasing;
  }

  int nextToRight() {
    index++;
    if (index == length - 1) {
      increasing = false;
    }

    return sequence[index];
  }

  int nextToLeft() {
    index--;
    if (index == 0) {
      increasing = true;
    }

    return sequence[index];
  }
};

/*
 * A random sequencer.
 */
class Random: public Sequence {
public:

  int next() {
    return random(0, 256); // [0, 256) => [0, 255]
  }
};

/*
 * An array of sequences.
 */
Sequence* sequences[2] = { new Horizontal(), new Random() };

/*
 * 74HC595 pin layout.
 */
const byte DATA = 11;
const byte LATCH = 12;
const byte SHIFT = 13;

/*
 * Left motor pin layout.
 */

const byte EN1 = 3;
const byte IN1 = 4;
const byte IN2 = 5;

/*
 * Right motor pin layout.
 */

const byte IN3 = 8;
const byte IN4 = 9;
const byte EN2 = 10;

/*
 * The minimum value that will be sent to the motors. If the current value
 * is lower than this minimum then, 0 is delivered.
 */
const byte MINIMUM = 30;

/*
 * Commands.
 */
const char* MOVEMENT = "MOVEMENT";
const char* SEQUENCE = "SEQUENCE";

void setup() {
  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(SHIFT, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Initialise serial channel.
  Serial.begin(115200);

  // Start with motors disabled.
  digitalWrite(EN1, LOW);
  digitalWrite(EN2, LOW);
}

const byte numChars = 32;
char receivedChars[numChars];

static boolean newData = false;

int sequenceIndex = 0;

int next;
void loop() {
  recvWithStartEndMarkers();
  processCommand();

  next = sequences[sequenceIndex]->next();

  digitalWrite(LATCH, LOW);
  shiftOut(DATA, SHIFT, MSBFIRST, next);
  digitalWrite(LATCH, HIGH);

  delay(75);
}

void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '^';
  char endMarker = '$';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
	      ndx++;
	      if (ndx >= numChars) {
	        ndx = numChars - 1;
	      }
      } else {
        receivedChars[ndx] = '\0'; // terminate the string
	      recvInProgress = false;
	      ndx = 0;
        newData = true;
      }
    }
    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}

void processCommand() {


  if (newData) {
    String command = String(receivedChars);

    if (command.startsWith("CHANGE_SEQUENCE")) {
	    changeSequence();
    } else if (command.startsWith("MOVEMENT")) {

      Serial.print("Command: ");
      Serial.println(command);

      byte colon = command.indexOf(':');
      byte coma = command.indexOf(',');
      byte end = command.length();

      int x = command.substring(colon + 1, coma).toInt();
      int y = command.substring(coma + 1, end).toInt();
      move(x, y);
    }

    newData = false;
  }
}

void changeSequence() {
  sequenceIndex = ++sequenceIndex % 2;
}

byte motorSpeed1 = 0;
byte motorSpeed2 = 0;

void move(int x, int y) {
  if ( y < 460 ) {
    // Motor left backward.
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    // Motor right backward.
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);

    y = y - 460;
    y = y * - 1;
    motorSpeed1 = map(y, 0, 460, 0, 255);
    motorSpeed2 = map(y, 0, 460, 0, 255);
  } else if ( y > 564 ) {
    // Motor left forward.
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    // Motor right forward.
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    motorSpeed1 = map(y, 564, 1023, 0, 255);
    motorSpeed2 = map(y, 564, 1023, 0, 255);
  } else {
    motorSpeed1 = 0;
    motorSpeed2 = 0;
  }

  if ( x < 460 ) {
    // Turn left.
    x = x - 460;
    x = x * -1;

    motorSpeed1 -= map(x, 0, 460, 0, 255);
    motorSpeed2 += map(x, 0, 460, 0, 255);

    if (motorSpeed1 < 0) { motorSpeed1 = 0; }
    if (motorSpeed2 > 255) { motorSpeed2 = 255; }

  } else if ( x > 564 ) {
    // Turn right.
    motorSpeed1 += map(x, 564, 1023, 0, 255);
    motorSpeed2 -= map(x, 564, 1023, 0, 255);

    if (motorSpeed1 > 255) { motorSpeed1 = 255; }
    if (motorSpeed2 < 0) { motorSpeed2 = 0; }
  }

  if (motorSpeed1 < MINIMUM) { motorSpeed1 = 0; }
  if (motorSpeed2 < MINIMUM) { motorSpeed2= 0; }

  analogWrite(EN1, motorSpeed1);
  analogWrite(EN2, motorSpeed2);
}
