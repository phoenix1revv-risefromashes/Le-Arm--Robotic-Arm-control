#include <Servo.h>

// ====== Servo objects ======
Servo baseServo;      // rotates arm left/right
Servo shoulderServo;  // main arm lift
Servo elbowServo;     // forearm bend
Servo wristServo;     // wrist tilt for pouring
Servo gripperServo;   // claw open/close

// ====== Pins (change if yours are different) ======
const int BASE_PIN = 3;
const int SHOULDER_PIN = 5;
const int ELBOW_PIN = 6;
const int WRIST_PIN = 9;
const int GRIPPER_PIN = 10;

// ====== Current servo positions ======
int basePos = 90;
int shoulderPos = 90;
int elbowPos = 90;
int wristPos = 90;
int gripperPos = 80;   // open-ish

// ====== TUNE THESE FOR YOUR ARM ======
// Source cup position
const int SRC_BASE      = 70;
const int SRC_SHOULDER  = 120;
const int SRC_ELBOW     = 70;
const int SRC_WRIST     = 95;

// Target cup position
const int TGT_BASE      = 120;
const int TGT_SHOULDER  = 105;
const int TGT_ELBOW     = 85;
const int TGT_WRIST     = 95;

// Gripper values
const int GRIP_OPEN     = 80;
const int GRIP_CLOSED   = 38;   // tune carefully based on cup width

// Safe home pose
const int HOME_BASE      = 90;
const int HOME_SHOULDER  = 90;
const int HOME_ELBOW     = 90;
const int HOME_WRIST     = 90;

// ====== Smooth movement helpers ======
void moveServoSmooth(Servo &servo, int &currentPos, int targetPos, int stepDelay = 15) {
  if (currentPos < targetPos) {
    for (int p = currentPos; p <= targetPos; p++) {
      servo.write(p);
      delay(stepDelay);
    }
  } else {
    for (int p = currentPos; p >= targetPos; p--) {
      servo.write(p);
      delay(stepDelay);
    }
  }
  currentPos = targetPos;
}

void moveAllSmooth(int b, int s, int e, int w, int g, int stepDelay = 15) {
  // move in small synchronized steps
  int maxDiff = max(abs(basePos - b),
               max(abs(shoulderPos - s),
               max(abs(elbowPos - e),
               max(abs(wristPos - w), abs(gripperPos - g)))));

  if (maxDiff == 0) return;

  for (int i = 1; i <= maxDiff; i++) {
    baseServo.write(basePos + (b - basePos) * i / maxDiff);
    shoulderServo.write(shoulderPos + (s - shoulderPos) * i / maxDiff);
    elbowServo.write(elbowPos + (e - elbowPos) * i / maxDiff);
    wristServo.write(wristPos + (w - wristPos) * i / maxDiff);
    gripperServo.write(gripperPos + (g - gripperPos) * i / maxDiff);
    delay(stepDelay);
  }

  basePos = b;
  shoulderPos = s;
  elbowPos = e;
  wristPos = w;
  gripperPos = g;
}

// ====== Motion sequence helpers ======
void goHome() {
  moveAllSmooth(HOME_BASE, HOME_SHOULDER, HOME_ELBOW, HOME_WRIST, GRIP_OPEN, 12);
  delay(600);
}

void moveAboveSourceCup() {
  moveAllSmooth(SRC_BASE, 105, 95, SRC_WRIST, GRIP_OPEN, 12);
  delay(500);
}

void lowerToSourceCup() {
  moveAllSmooth(SRC_BASE, SRC_SHOULDER, SRC_ELBOW, SRC_WRIST, GRIP_OPEN, 12);
  delay(700);
}

void gripCup() {
  moveAllSmooth(SRC_BASE, SRC_SHOULDER, SRC_ELBOW, SRC_WRIST, GRIP_CLOSED, 12);
  delay(800);
}

void liftCup() {
  moveAllSmooth(SRC_BASE, 95, 100, 95, GRIP_CLOSED, 12);
  delay(700);
}

void moveAboveTargetCup() {
  moveAllSmooth(TGT_BASE, TGT_SHOULDER, TGT_ELBOW, TGT_WRIST, GRIP_CLOSED, 12);
  delay(800);
}

void pourIntoTargetCup() {
  // tilt gradually for a smoother pour
  for (int angle = wristPos; angle >= 45; angle -= 2) {
    wristServo.write(angle);
    delay(50);
  }
  wristPos = 45;
  delay(1800);  // hold pour
}

void returnFromPour() {
  moveAllSmooth(TGT_BASE, TGT_SHOULDER, TGT_ELBOW, TGT_WRIST, GRIP_CLOSED, 12);
  delay(700);
}

void placeCupDown() {
  moveAllSmooth(TGT_BASE, 120, 70, 95, GRIP_CLOSED, 12);
  delay(700);
}

void releaseCup() {
  moveAllSmooth(TGT_BASE, 120, 70, 95, GRIP_OPEN, 12);
  delay(700);
}

void setup() {
  baseServo.attach(BASE_PIN);
  shoulderServo.attach(SHOULDER_PIN);
  elbowServo.attach(ELBOW_PIN);
  wristServo.attach(WRIST_PIN);
  gripperServo.attach(GRIPPER_PIN);

  // initialize at home
  baseServo.write(basePos);
  shoulderServo.write(shoulderPos);
  elbowServo.write(elbowPos);
  wristServo.write(wristPos);
  gripperServo.write(gripperPos);

  delay(1000);
  goHome();
}

void loop() {
  moveAboveSourceCup();
  lowerToSourceCup();
  gripCup();
  liftCup();
  moveAboveTargetCup();
  pourIntoTargetCup();
  returnFromPour();
  placeCupDown();
  releaseCup();
  goHome();

  delay(5000); // wait before repeating
}
