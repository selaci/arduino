#include <receiver.h>
#include <joystick.h>

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

const byte IN3 = 5;
const byte IN4 = 4;
const byte EN2 = 3;

/*
 * Right motor pin layout.
 */

const byte EN1 = 10;
const byte IN1 = 9;
const byte IN2 = 8;


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
  Serial.begin(9600);

  // Start with motors disabled.
  digitalWrite(EN1, LOW);
  digitalWrite(EN2, LOW);
}

int sequenceIndex = 0;

int next;

// Serial receiver.
Receiver receiver('^', '$');

// Joystick that calculates power for the motors, based on coordinates "x" and "y".
Joystick joystick(255);

void loop() {
  receiver.read();
  processCommand();

  next = sequences[sequenceIndex]->next();

  digitalWrite(LATCH, LOW);
  shiftOut(DATA, SHIFT, MSBFIRST, next);
  digitalWrite(LATCH, HIGH);

  delay(75);
}

int lForward = true;
int rForward = true;
       
boolean leftMotorHasScheduledPower = false;
int scheduledPowerForLeftMotor;

boolean rightMotorHasScheduledPower;
int scheduledPowerForRightMotor;

void processCommand() {
  if (receiver.hasData()) {
    String command = receiver.getData();

    if (command.startsWith("CHANGE_SEQUENCE")) {
	    changeSequence();
    } else if (command.startsWith("MOVEMENT")) {

      byte colon = command.indexOf(':');
      byte coma = command.indexOf(',');
      byte _end = command.length();

      int x = command.substring(colon + 1, coma).toInt();
      int y = command.substring(coma + 1, _end).toInt();
      
      joystick.setCoordinates(x, y);

      leftMotorHasScheduledPower = false;
      rightMotorHasScheduledPower = false;
      
      move(joystick.getLeftMotorPower(), joystick.getRightMotorPower());
    }
  } else {
    if (scheduledPowerForLeftMotor || scheduledPowerForRightMotor) {\
      scheduledPowerForLeftMotor = false;
      scheduledPowerForRightMotor = false;
      applyPower(scheduledPowerForLeftMotor, scheduledPowerForRightMotor);
    }
  }
}

void changeSequence() {
  sequenceIndex = ++sequenceIndex % 2;
}

void move(int lPower, int rPower) {
  if (leftMotorHasChangedDirection(lPower)) {
    lPower = 0;
    setSchedulePowerLeftMotor(lPower);
  }

  setDirectionForLeftMotor(lPower);
      
  if (rightMotorHasChangedDirection(rPower)) {
    setSchedulePowerForRightMotor(rPower);  
    rPower = 0;
  }
  
  setDirectionForRightMotor(rPower);
  
  applyPower(lPower, rPower);
}

boolean leftMotorHasChangedDirection(int lPower) {
  return motorHasChangedDirection(lForward, lPower);
}

boolean rightMotorHasChangedDirection(int rPower) {
  return motorHasChangedDirection(rForward, rPower);
}

boolean motorHasChangedDirection(boolean mForward, int mPower) {
  if(mPower == 0) {
    return false;
  }
  
  if (mForward) { // It was moving forward before.
    if (mPower > 0) { // It moves forward now.
      return false;
    } else { // It changes direction.
      return true;
    }
  } else { // It was moving backward before.
    if (mPower < 0) { // It moves backward now.
      return false;
    } else { // It changes direction.
      return true;
    }
  }
}

void setDirectionForLeftMotor(int lPower) {
  if (lPower > 0) {
    lForward = true;

    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else {
    lForward = false;

    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
}

void setDirectionForRightMotor(int rPower) {
  if (rPower > 0) {
    rForward = true;

    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);    
  } else {
    rForward = false;
    
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
}

void applyPower(int lPower, int rPower) {
  analogWrite(EN1, lPower);
  analogWrite(EN2, rPower);
}
     
void setSchedulePowerLeftMotor(int power) {
  leftMotorHasScheduledPower = true;
  scheduledPowerForLeftMotor = power;
}

void setSchedulePowerForRightMotor(int power) {
  rightMotorHasScheduledPower = true;
  scheduledPowerForRightMotor = power;
}
