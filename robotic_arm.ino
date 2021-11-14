#include <Servo.h>
/*
 * My name is Lautaro and if you read this please forgive the english in my comments.I know my english sucks lol.
 */
//Configuration parameters
const int serialPort = 9600;

//define our servos
Servo servoBase;
Servo servoShoulder;
Servo servoElbow;
Servo servoWristRoll;
Servo servoWristPitch;
Servo servoGripper;

//Joysticks pins (Analog)
const int joy1PinX = A0;
const int joy1PinY = A1;
const int Joy1Button = 3;

//Servos' connections
const int servoBasePin = 5;
const int servoShoulderPin = 6;
const int servoElbowPin = 7;
const int servoWristRollPin = 8;
const int servoWristPitchPin = 9;
const int servoGripperPin = 10;
 
//Initial position values
const int servoBaseInitialPos = 90;
const int servoShoulderInitialPos = 90;
const int servoElbowInitialPos = 90;
const int servoWristRollInitialPos = 140;
const int servoWristPitchInitialPos = 85;
const int servoGripperInitialPos = 90;

//Variable to read the values from the analog pins
int joy1PosX;
int joy1PosY;
int joy2PosX;
int joy2PosY;

//Variables corresponding to the servos' positions
int servoBasePos, servoShoulderPos, servoElbowPos, servoWristRollPos, servoWristPitchPos, servoGripperPos; // current position
int absJoystickVal;
int sum;
int substraction;

//Test helpful constants
const String xString = "X: ";
const String yString = "    | Y: ";
const String servoPosString = "   | servo's position: ";
const String speedString = "    | servo's speed: ";

String serialData;

void setup() {
  //I have this for testing
  Serial.begin(serialPort);//Port 9600 is the default port for Serial communication

  //Conncectin the joystics to the arduino
  pinMode(joy1PinX, INPUT);
  pinMode(joy1PinY, INPUT);
  pinMode(Joy1Button, INPUT);
  digitalWrite(Joy1Button,HIGH);

  //Connecting the servos to the arduino
  servoBase.attach(servoBasePin);
  servoShoulder.attach(servoShoulderPin);
  servoElbow.attach(servoElbowPin);
  servoWristRoll.attach(servoWristRollPin);
  servoWristPitch.attach(servoWristPitchPin);
  servoGripper.attach(servoGripperPin);

  initialPosition();
}

void loop() {
  moveBase();
  moveShoulder();
  testJoystick();
}

void testJoystick () {
  serialData = xString + joy1PosX + servoPosString + servoBasePos + speedString + distanceDueToJoystickPosition(joy1PosX);
  Serial.println(serialData);
}

void moveBase(){
  joy1PosX = map(analogRead(joy1PinX), 0, 1023, -100, 100); //read the value of joystick (between 0-1023)
  if (joy1PosX < -10 || joy1PosX > 10) {
    if (joy1PosX > 10 && servoBasePos < 180) {
      servoBasePos = sumOfDistance(servoBasePos,joy1PosX);
      servoBase.write(servoBasePos);
    } else if (joy1PosX < -10 && servoBasePos > 0){
      servoBasePos = substractionOfDistance(servoBasePos,joy1PosX);
      servoBase.write(servoBasePos);
    } 
  }
}

void moveShoulder() {
    joy1PosY = map(analogRead(joy1PinY), 0, 1023, -100, 100); //read the value of joystick (between 0-1023)
  if (joy1PosY < -10 || joy1PosY > 10) {
    if (joy1PosY > 10 && servoShoulderPos < 180) {
      servoShoulderPos = sumOfDistance(servoShoulderPos,joy1PosY);
      servoShoulder.write(servoShoulderPos);
    } else if (joy1PosY < -10 && servoShoulderPos > 0){
      servoShoulderPos = substractionOfDistance(servoShoulderPos,joy1PosY);
      servoShoulder.write(servoShoulderPos);
    } 
  }
}

int sumOfDistance(int servoPPosition, int joyPosition) {
  sum = servoPPosition + distanceDueToJoystickPosition(joyPosition);
  if (sum > 180) {
    return 180;
  } else {
    return sum;
  }
}

int substractionOfDistance(int servoPPosition, int joyPosition) {
  substraction = servoPPosition - distanceDueToJoystickPosition(joyPosition);
  if (substraction < 0) {
    return 0; 
  } else {
    return substraction;
  }
}

//Calculates how much movement should add due to they joystick position
int distanceDueToJoystickPosition (int joyPosition) {
  absJoystickVal = abs(joyPosition);
  if (absJoystickVal >= 10 && absJoystickVal < 50) {
    return 1;
  } else if (absJoystickVal >= 50 && absJoystickVal < 100) {
    return 5;
  } else if (absJoystickVal == 100) {
    return 15;
  } else {
    return 0;
  }
}

// Robot arm initial position
void initialPosition() {
  servoBasePos = servoBaseInitialPos;
  servoShoulderPos = servoShoulderInitialPos;
  servoElbowPos = servoElbowInitialPos;
  servoWristRollPos = servoWristRollInitialPos;
  servoWristPitchPos = servoWristPitchInitialPos;
  servoGripperPos = servoGripperInitialPos;
  servoBase.write(servoBasePos);
  servoShoulder.write(servoShoulderPos);
  servoElbow.write(servoElbowPos);
  servoWristRoll.write(servoWristRollPos);
  servoWristPitch.write(servoWristPitchPos);
  servoGripper.write(servoGripperPos);
}
