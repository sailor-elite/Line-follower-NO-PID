#include <Arduino.h>

#define R_LINE_SENSOR 7
#define L_LINE_SENSOR 6
#define R_SUPPORT_SENSOR 8
#define L_SUPPORT_SENSOR 9
#define motor1P1 2
#define motor1P2 3
#define motor2P1 4
#define motor2P2 5
#define PWM_Value 255
#define pwm1 12
#define pwm2 13
#define THRESHOLD 800
#define PWM_DUTY 255

void MoveForward() {
  analogWrite(pwm1, 130);
  analogWrite(pwm2, 130);
  digitalWrite(motor1P1, HIGH);
  digitalWrite(motor1P2, LOW);
  digitalWrite(motor2P1, HIGH);
  digitalWrite(motor2P2, LOW);
}

void MoveRight() {
  analogWrite(pwm1, 130);
  analogWrite(pwm2, 130);
  digitalWrite(motor1P1, HIGH);
  digitalWrite(motor1P2, LOW);
  digitalWrite(motor2P1, LOW);
  digitalWrite(motor2P2, HIGH);
}

void MoveLeft() {
  analogWrite(pwm1, 130);
  analogWrite(pwm2, 130);
  digitalWrite(motor1P1, LOW);
  digitalWrite(motor1P2, HIGH);
  digitalWrite(motor2P1, HIGH);
  digitalWrite(motor2P2, LOW);
}

void setup() {
  pinMode(motor1P1, OUTPUT);
  pinMode(motor1P2, OUTPUT);
  pinMode(motor2P1, OUTPUT);
  pinMode(motor2P2, OUTPUT);
  pinMode(L_LINE_SENSOR, INPUT);
  pinMode(R_LINE_SENSOR, INPUT);
  Serial.begin(9600);
}

bool isLeftSensorActive(int LeftSensorVal) {
  return (LeftSensorVal >= THRESHOLD);
}

bool isRightSensorActive(int RightSensorVal) {
  return (RightSensorVal >= THRESHOLD);
}
bool isRightSupportSensorActive(int RightSupportSensorVal) {
  return (RightSupportSensorVal >= THRESHOLD);
}
bool isLeftSupportSensorActive(int LeftSupportSensorVal) {
  return (LeftSupportSensorVal >= THRESHOLD);
}

void loop() {
  int LeftSensor = analogRead(L_LINE_SENSOR);
  int RightSensor = analogRead(R_LINE_SENSOR);
  int LeftSupportSensor = analogRead(L_SUPPORT_SENSOR);
  int RightSupportSensor = analogRead(R_SUPPORT_SENSOR);
  
  bool RightState = isRightSensorActive(RightSensor);
  bool LeftState = isLeftSensorActive(LeftSensor);
  bool RightSupportState = isRightSupportSensorActive(RightSupportSensor);
  bool LeftSupportState = isLeftSupportSensorActive(LeftSupportSensor);


  if ((!RightState && !LeftState)) {
    if (LeftSupportSensor <= 2000) {
      do{
       MoveLeft();
    }while(!(isRightSensorActive(analogRead(R_LINE_SENSOR))) && !(isLeftSensorActive(analogRead(L_LINE_SENSOR))));

    while (isRightSensorActive(analogRead(R_LINE_SENSOR)) && isLeftSensorActive(analogRead(L_LINE_SENSOR))){
        MoveForward();
      }
    }
    if (RightSupportSensor <= 2000){
      do{
        MoveRight();
      }while (!(isRightSensorActive(analogRead(R_LINE_SENSOR))) && !(isLeftSensorActive(analogRead(L_LINE_SENSOR))));

      while (isRightSensorActive(analogRead(R_LINE_SENSOR)) && (isLeftSensorActive(analogRead(L_LINE_SENSOR)))){
        MoveForward();
      }
    if ((RightSupportSensor <= 2000) && (LeftSupportSensor <= 2000)){
      MoveForward();
    }
    }
    else{
      MoveForward();
    }
    }
  else if (RightState && LeftState){
    if (LeftSupportSensor <= 2000) {
      MoveLeft();
    }
    if (RightSupportSensor <= 2000)
    {
      MoveRight();
    }
    if ((RightSupportSensor <= 2000) && (LeftSupportSensor <= 2000)){
      MoveForward();
    }
    else{
      MoveForward();
    }
  }
  else if (!RightState && LeftState) {
    MoveRight();

  } 
  else if (RightState && !LeftState) {
      MoveLeft();
  }

}