#include <Servo.h>

// Pin 2 is Wrist (handLeft[0]), Pins 3-7 are fingers 1-5 (handLeft[1-5])
byte firstPinHandLeft = 2;
Servo handLeft[6];

// Pin 8 is Wrist ( handRight[0]), Pins 9-13 are fingers 1-5 (handRight[1-5])
byte firstPinHandRight = 8;
Servo handRight[6];

Servo bicepLeft;
Servo bicepRight;

// First index is which finger (same order as handLeft[])
// Second index is position: 0 for extended (relaxed), 1 for retracted (grip)
// Wrist ( handLeft[0]/posHandLeft[0][y]) is just one way or the other
byte posHandLeft[6][2] = {
  {0,180},
  {110,180},
  {20,110},
  {20,110},
  {20,110},
  {30,120}
};

// First index is which finger (same order as handRight[])
// Second index is position: 0 for extended (relaxed), 1 for retracted (grip)
// Wrist ( handRight[0]/posHandRight[0][y]) is just one way or the other
byte posHandRight[6][2] = {
  {0,180},
  {140, 100},
  {20,90},
  {30,100},
  {30,100},
  {150, 80}
};

byte posBicepLeft[] = {0, 180};
byte posBicepRight[] = {0, 180};

// pos to keep track for rotateServo function
int pos = 0;

void setup() {
  Serial.begin(9600);

  // Set all servos to their current position so no drastic movement happens at start of program
  for(int i=0; i<7; i++) {
    handLeft[i].write(handLeft[i].read());
    handRight[i].write(handRight[i].read());
  }
  bicepLeft.write(bicepLeft.read());
  bicepRight.write(bicepRight.read());

  // Attach all motor (pins)
  for(int i=0; i<7; i++) {
    handLeft[i].attach(i + firstPinHandLeft);
    handRight[i].attach(i + firstPinHandRight);
  }
  bicepLeft.attach(14);
  bicepRight.attach(15);
}

// Cycle between the left hand program and the right hand program
void loop() {
  handLeftMovement();
  handRightMovement();
  delay(5000);
}

// Rotate, Clench, wave backa and forth, unclench, rotate back to origin?
void handLeftMovement() {
  rotateServo(handLeft[0], posHandLeft[0][1], 1000);

  rotateServo(handLeft[5], posHandLeft[5][1], 100);
  rotateServo(handLeft[4], posHandLeft[4][1], 100);
  rotateServo(handLeft[3], posHandLeft[3][1], 100);
  rotateServo(handLeft[2], posHandLeft[2][1], 100);
  rotateServo(handLeft[1], posHandLeft[1][1], 100);
  delay(2000);

  rotateServo(handLeft[0], posHandLeft[0][0], 100);
  rotateServo(handLeft[0], posHandLeft[0][1], 100);
  rotateServo(handLeft[0], posHandLeft[0][0], 100);
  rotateServo(handLeft[0], posHandLeft[0][1], 100);
 
  rotateServo(handLeft[1], posHandLeft[1][0], 100);
  rotateServo(handLeft[2], posHandLeft[2][0], 100);
  rotateServo(handLeft[3], posHandLeft[3][0], 100);
  rotateServo(handLeft[4], posHandLeft[4][0], 100);
  rotateServo(handLeft[5], posHandLeft[5][0], 100);

  rotateServo(handLeft[0], posHandLeft[0][0], 1000);
  delay(2000);
}

// Clench, rotate, thumbs up, unclench, rotate back to origin
void handRightMovement() {
  rotateServo(handRight[5], posHandRight[5][1], 100);
  rotateServo(handRight[4], posHandRight[4][1], 100);
  rotateServo(handRight[3], posHandRight[3][1], 100);
  rotateServo(handRight[2], posHandRight[2][1], 100);
  rotateServo(handRight[1], posHandRight[1][1], 100);
  delay(2000);

  rotateServo(handRight[0], (posHandRight[0][1]/2), 100);
  delay(2000);

  rotateServo(handRight[1], posHandRight[1][0], 100);
  delay (2000);

  rotateServo(handRight[5], posHandRight[5][0], 100);
  rotateServo(handRight[4], posHandRight[4][0], 100);
  rotateServo(handRight[3], posHandRight[3][0], 100);
  rotateServo(handRight[2], posHandRight[2][0], 100);
  delay(2000);

  rotateServo(handRight[0], posHandRight[0][0], 100);
  delay(2000);
}

// Gradually rotates a specific servo to a designated position, then waits for a designated ammount of time before continuing
void rotateServo(Servo servo, int position, int endDelay) {
  int currentPosition = servo.read();

  if(currentPosition <= position) {
    for (pos = currentPosition; pos <= position; pos += 1) { 
     // in steps of 1 degree
     servo.write(pos);
     delay(15);
    }
  } else {
    for (pos = currentPosition; pos >= position; pos -= 1) { 
     // in steps of 1 degree
      servo.write(pos);
      delay(15);
    }
  }
  delay(endDelay);
}