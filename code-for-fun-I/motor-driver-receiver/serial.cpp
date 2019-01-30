#include "constants.h"
#include "receiver.h"
#include <joystick.h>
#include "decoder.h"

Receiver receiver('^', '$');
Joystick joystick(255);
Decoder decoder;

/*
 * The prototype for the processing of the command that has been received through the serial channel.
 */
void parseSerialData(byte* data);

/*
 * The prototype for changing the LED sequence.
 */
void changeSequence();

/*
 * The prototype for moving the vehicle.
 */
void moveVehicle(int x, int y);

/*
 * Sends a message following a certain format through the serial channel.
 */
void sendMessage(String message) {
  Serial.println("^\"" + message + "\"$");
}

/*
 * Prototype to extract the coordiantes of a move command.
 */
bool parseCoordinates(int x, int y);

/*
 * Prototype to avoid too much throttle change.
 */
void smoothPower(int *lPower, int *Power);

/*
 * Apply the power for the left and right power.
 */
void applyPower(int lPower, int rPower);

void applyPowerToLeft(int power);

void applyPowerToRight(int power);

/*
 * Reads the serial channel in order to determine whether there is any command that needs to be processed.
 */
 byte buffer[64] = {};

int previousLeftPower = 0;
int previousRightPower = 0;
int scheduledLeftPower = 0;
int scheduledRightPower = 0;

bool hasLeftScheduledPower = false;
bool hasRightScheduledPower = false;

void processSerial() {
  receiver.read();
  if (receiver.hasData()) {
    byte* data = receiver.getData();
    parseSerialData(data);
  } else {
    if (hasLeftScheduledPower) {
      applyPowerToLeft(scheduledLeftPower);
      hasLeftScheduledPower = false;     
    }

    if (hasRightScheduledPower) {
      applyPowerToRight(scheduledRightPower);
      hasRightScheduledPower = false;
    }
  }
}

void parseSerialData(byte* data) {
  switch(decoder.getCommand(data)) {
    case MOVE:
      if (DEBUG) {
        Serial.print("In parseSerialData. X: ");
        Serial.print(decoder.getX(data));
        Serial.print(", y: ");
        Serial.println(decoder.getY(data));
      }
      moveVehicle(decoder.getX(data), decoder.getY(data));
      break;
    case CHANGE_LED_SEQUENCE:
      changeSequence();
      break;
    default:
      sendMessage(UNEXPECTED_COMMAND + decoder.getCommand(data));
      break;
  }
}

void changeSequence() {
  // TODO.  
}

void moveVehicle(int x, int y) {
  bool hasCoordinates = parseCoordinates(x, y);
  
  if (!hasCoordinates) {
    sendMessage(UNEXPECTED_DATA + " X: " + x + ", Y: " + y);
    return;
  }

  joystick.setCoordinates(x, y);
  
  int lPower, rPower;
  lPower = joystick.getLeftMotorPower();
  rPower = joystick.getRightMotorPower();

  smoothPower(&lPower, &rPower);
  applyPower(lPower, rPower);
}

bool parseCoordinates(int x, int y) {
  return (x != -1) && (y != -1);
}

void smoothPower(int* lPower, int* rPower) {
  if (DEBUG) {
    Serial.print("^Pre-smooth power: ");
    Serial.print(*lPower);
    Serial.print(',');
    Serial.print(*rPower);
    Serial.print(", ");
    Serial.print(previousLeftPower);
    Serial.print(", ");
    Serial.println(previousRightPower);
  }

  if (*lPower >= 0) {
    if (previousLeftPower < 0) { // Change direction.
      scheduledLeftPower = *lPower;
      hasLeftScheduledPower = true;
      *lPower = 0;      
    }
  } else { // *lPower < 0
    if (previousLeftPower > 0) { // Change direction.
      scheduledLeftPower = *lPower;
      hasLeftScheduledPower = *lPower;
      *lPower = 0;
    }
  }

  if (*rPower >= 0) {
    if (previousRightPower < 0) { // Change direction,
      scheduledRightPower = *rPower;
      hasRightScheduledPower = *rPower;
      *rPower = 0;      
    }
  } else { // *rPower < 0
    if (previousRightPower > 0) {
      scheduledRightPower = *rPower;
      hasRightScheduledPower = true;
      *rPower = 0;
    }
  }

  if (DEBUG) { 
    Serial.print("^Post-smooth power: ");
    Serial.print(*lPower);
    Serial.print(',');
    Serial.print(*rPower);
    Serial.println('$');
  }
}

void applyPower(int lPower, int rPower) {
  applyPowerToLeft(lPower);
  applyPowerToRight(rPower);
}

void applyPowerToLeft(int power) {
  previousLeftPower = power;

  if (DEBUG) {
    Serial.print("^Apply to power left: ");
    Serial.print(power);
    Serial.println('$');
  }
  
  if (power >= 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else {
    power *= -1;
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }

  analogWrite(EN1, power);
}

void applyPowerToRight(int power) {
  previousRightPower = power;

  if (DEBUG) {
    Serial.print("^Apply to power right: ");
    Serial.print(power);
    Serial.println('$');
  }
  
  if (power >= 0) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else {
    power *= -1;
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }

  analogWrite(EN2, power);
}

