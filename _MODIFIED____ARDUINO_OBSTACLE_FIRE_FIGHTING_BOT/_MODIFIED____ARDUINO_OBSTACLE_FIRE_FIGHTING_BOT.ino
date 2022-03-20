

#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>



//Servo
const int sensorMin = 0;     // sensor min
const int sensorMax = 1024;  // sensor max

#define TRIG_PIN A3    // ultrasonic sensor
#define ECHO_PIN A2    // ultrasonic sensor
#define pump 11   // water pump[DC motor]
#define MAX_DISTANCE 200
#define MAX_SPEED 190 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20
int sensorReading = analogRead(A0);

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
Servo myservo;

boolean goesForward = false;
int distance = 100;
int speedSet = 0;

int pos = 0;


void setup() {
  Serial.begin(9600);
  myservo.attach(8);
  myservo.write(115);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
  int distanceR = 0;
  int distanceL =  0;
  delay(40);

  if (distance <= 8)
  {
    Serial.println(distance);
    moveStop();
    delay(100);
    sensorReading = analogRead(A0);
    int range = map(sensorReading, sensorMin, sensorMax, 0, 3);
    Serial.println("Distance is less than 8");
    Serial.println(range);
    if (range == 0)
    {
      
      Serial.println("Flame");
      moveStop();
      fire_ex();
      delay(500);
    }
    else
    {
//      moveStop();
      moveBackward();
      delay(300);
      moveStop();
      delay(200);
      distanceR = lookRight();
      delay(200);
      distanceL = lookLeft();
      delay(200);

      if (distanceR >= distanceL)
      {
        turnRight();
        moveStop();
      }
      else
      {
        turnLeft();
        moveStop();
      }
    }
  } else
  {
    Serial.println(distance);
    moveForward();
  }
  distance = readPing();
}

int lookRight()
{
  myservo.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(115);
  return distance;
}

int lookLeft()
{
  myservo.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(115);
  return distance;
  delay(100);
}

int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0)
  {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void moveForward() {

  if (!goesForward)
  {
    goesForward = true;
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) // slowly bring the speed up to avoid loading down the batteries too quickly
    {
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      motor3.setSpeed(speedSet);
      motor4.setSpeed(speedSet);
      delay(5);
    }
  }
}

void moveBackward() {
  goesForward = false;
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
  }
}

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(500);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void turnLeft() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(500);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
void fire_ex()
{
  delay (500);
  
  Serial.println("starting pump");
  digitalWrite(pump, HIGH); //Turn the pump ON for DC Motor
  Serial.println("calling pump");
  delay(500);
  
  for (pos = 50; pos <= 130; pos += 1) {
    myservo.write(pos);
    delay(100);
  }
  for (pos = 130; pos >= 50; pos -= 1) {
    myservo.write(pos);
    delay(100);
  }
  // need to add condition to check if fire is low or high
   sensorReading = analogRead(A0);
   int range = map(sensorReading, sensorMin, sensorMax, 0, 3);
   if (range==0)
  {
    fire_ex();
    }
  else{
  digitalWrite(pump, LOW);
  myservo.write(90);
  }
}
