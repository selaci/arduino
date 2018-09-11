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
      nextToRight();
    } else {
      nextToLeft();
    }
  }

private:

  bool isIncreasing() {
    return increasing;
  }

  int nextToRight() {
    index++;
    if (index = length - 1) {
      increasing = false;
    }

    return sequence[index];
  }

  int nextToLeft() {
    index--;
    if (index = 0) {
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
const byte DATA = 13;
const byte LATCH = 12;
const byte SHIFT = 11;

/*
 * Left motor pin layout.
 */

const byte EN1 = 10;
const byte IN1 = 9;
const byte IN2 = 8;

/*
 * Right motor pin layout.
 */

const byte IN3 = 5;
const byte IN4 = 4;
const byte EN2 = 3;

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
}

const byte numChars = 32;
char receivedChars[numChars];

boolean newData = false;

void loop() {
  recvWithStartEndMarkers();
  processCommand();
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
      }
      else {
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
  if (newData == true) {
    String command = String(receivedChars);
    if (command.startsWith("SEQUENCE")) {
	    changeSequence();
    } else if (command.startsWith("MOVEMENT")) {
      byte colon = command.indexOf(':');
      byte coma = command.indexOf(',');
      byte end = command.length();

      int x = command.substring(colon, coma).toInt();
      int y = command.substring(coma, end).toInt();

      move(x, y);
    }
    
    newData = false;
  }
}  

void changeSequence() {
  // TO BE DONE.
}

void move(int x, int y) {
  // TO BE DONE.
}

