

/*
 * A program for me to develop a library for a joystick.
 * 
 * The joystick has two axis, X and Y and they both range from 0 to 1024.
 * 
 * The main program runs some tests to verify the output of the joystick.
 */

#include "joystick.h"

void setup() {
  Serial.begin(9600);
}

Joystick joystick(255);

void loop() {
/*

  int x;
  int y;
  int lPower;
  int rPower;
  float rad;
  for(int i = 90; i >= 0; i -= 5) {
    rad = 0.01745;
    x = 512 * ( 1 + cos(i * rad));
    y = 512 * ( 1 - sin(i * rad));
    if (i < 23) {
      lPower = - 255;
      rPower = - 255 * ((i - 22.5) / 22.5);
    } else if (i < 45) {
      lPower = -255;
      rPower = -255 * ((i - 22.5) / 45);
    } else {
      lPower = - 255;
      rPower = - 255 * (1 - (90.0 - i) / 90);
    }

    Serial.print("verify(");
    Serial.print(x);
    Serial.print(", ");
    Serial.print(y);
    Serial.print(", ");
    Serial.print(lPower);
    Serial.print(", ");
    Serial.print(rPower);
    Serial.print(")");
    Serial.print("; // ");
    Serial.println(360 - i);
  }

  delay(200000);
*/  
  
  // Centre.
  verify(512, 512, 0, 0);

  // First quarter.
  verify(1024, 512, 255, -255); // 0
  verify(1022, 556, 255, -198); // 5
  verify(1016, 600, 255, -141); // 10
  verify(1006, 644, 255, -85);  // 15
  verify(993, 687, 255, -28);   // 20
  verify(976, 728, 255, 14);    // 25
  verify(955, 767, 255, 42);    // 30
  verify(931, 805, 255, 70);    // 35
  verify(904, 841, 255, 99);    // 40
  verify(874, 873, 255, 127);   // 45
  verify(841, 904, 255, 141);   // 50
  verify(805, 931, 255, 155);   // 55
  verify(768, 955, 255, 169);   // 60
  verify(728, 975, 255, 184);   // 65
  verify(687, 993, 255, 198);   // 70
  verify(644, 1006, 255, 212);  // 75
  verify(601, 1016, 255, 226);  // 80
  verify(556, 1022, 255, 240);  // 85
  verify(512, 1023, 255, 255);  // 90

  // Second quarter.
  verify(0, 512, -255, 255); // 180
  verify(1, 556, -198, 255); // 175
  verify(7, 600, -141, 255); // 170
  verify(17, 644, -85, 255); // 165
  verify(30, 687, -28, 255); // 160
  verify(47, 728, 14, 255); // 155
  verify(68, 767, 42, 255); // 150
  verify(92, 805, 70, 255); // 145
  verify(119, 841, 99, 255); // 140
  verify(149, 873, 127, 255); // 135
  verify(182, 904, 141, 255); // 130
  verify(218, 931, 155, 255); // 125
  verify(255, 955, 169, 255); // 120
  verify(295, 975, 184, 255); // 115
  verify(336, 993, 198, 255); // 110
  verify(379, 1006, 212, 255); // 105
  verify(422, 1016, 226, 255); // 100
  verify(467, 1022, 240, 255); // 95
  verify(511, 1023, 255, 255); // 90

  // Third qudrant.
  verify(1, 467, 198, -255);    // 185
  verify(7, 423, 141, -255);    // 190
  verify(17, 379, 85, -255);    // 195
  verify(30, 336, 28, -255);    // 200
  verify(47, 295, -14, -255);   // 205
  verify(68, 256, -42, -255);   // 210
  verify(92, 218, -70, -255);   // 215
  verify(119, 182, -99, -255);  // 220
  verify(149, 150, -127, -255); // 225
  verify(182, 119, -141, -255); // 230
  verify(218, 92, -155, -255);  // 235
  verify(255, 68, -169, -255);  // 240
  verify(295, 48, -184, -255);  // 245
  verify(336, 30, -198, -255);  // 250
  verify(379, 17, -212, -255);  // 255
  verify(422, 7, -226, -255);   // 260
  verify(467, 1, -240, -255);   // 265
  verify(511, 0, -255, -255);   // 270

  // Quarter qudrant.
  verify(512, 0, -255, -255);   // 270
  verify(556, 1, -255, -240);   // 275
  verify(601, 7, -255, -226);   // 280
  verify(644, 17, -255, -212);  // 285
  verify(687, 30, -255, -198);  // 290
  verify(728, 48, -255, -184);  // 295
  verify(768, 68, -255, -169);  // 300
  verify(805, 92, -255, -155);  // 305
  verify(841, 119, -255, -141); // 310
  verify(874, 150, -255, -127); // 315
  verify(904, 182, -255, -99);  // 320
  verify(931, 218, -255, -70);  // 325
  verify(955, 256, -255, -42);  // 330
  verify(976, 295, -255, -14);  // 335
  verify(993, 336, -255, 28);   // 340
  verify(1006, 379, -255, 85);  // 345
  verify(1016, 423, -255, 141); // 350
  verify(1022, 467, -255, 198); // 355
  
  delay(200000);
}

void verify(int x, int y, int expectedLeft, int expectedRight) {
  joystick.setCoordinates(x, y);
  
  int lPower = joystick.getLeftMotorPower();
  int rPower = joystick.getRightMotorPower();

  int tolerance = 10;
  int lDifference = abs(lPower - expectedLeft);
  int rDifference = abs(rPower - expectedRight);

  if (lPower >= -255 && lPower <= 255 && rPower >= -255 && rPower <= 255 
      &&  lDifference <= tolerance && rDifference <= tolerance) {
    Serial.print("[OK]    for (");
  } else {
    Serial.print("[ERROR] for (");
  }
  
  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.print(") and power (");
  Serial.print(lPower);
  Serial.print(", ");
  Serial.print(rPower);
  Serial.println(")");
}
