#include <Servo.h>
#include <AFMotor.h>
Servo myservo;

int pos = 0;
int c1,c2,c3,casee=0;
int h,l=0;
const int flamepin = 11;
int Flame = HIGH;
int distancer;
int distancel;
//char z;


#define MAX_SPEED 200 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);


int speedSet = 0;
#define trigPin A3    // ultrasonic sensor
#define echoPin A2    // ultrasonic sensor
#define pump 13      // water pump[DC motor]
//#define FS A4        // flame sensor


//Servo
const int sensorMin = 0;     // sensor min
const int sensorMax = 1024;  // sensor max

// defines variables
long duration; // variable for the duration of sound wave travel
int distance;  // variable for the distance measurement
int ultrasonic();

void setup()
{
  pinMode(pump, OUTPUT);
  pinMode(flamepin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);

  myservo.attach(8); //Water Pump's Base Servo Motor
  myservo.write(90);
  //  pinMode(FS, INPUT);
  //  Serial.begin(9600);

  motor1.setSpeed(200);
  motor1.run(RELEASE);
  motor2.setSpeed(200);
  motor2.run(RELEASE);
  motor3.setSpeed(200);
  motor3.run(RELEASE);
  motor4.setSpeed(200);
  motor4.run(RELEASE);

}


void fire_ex()
{
  delay (500);
  moveForward(); /////////////////////////////////////////////////

  digitalWrite(pump, HIGH); //Turn the pump ON for DC Motor
  delay(500);

  for (pos = 50; pos <= 130; pos += 1) {
    myservo.write(pos);
    delay(100);
  }
  for (pos = 130; pos >= 50; pos -= 1) {
    myservo.write(pos);
    delay(100);
  }

  digitalWrite(pump, LOW);
  myservo.write(90);

  Flame = HIGH;
}

int ultrasonic()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}

int right()
{
  myservo.write(50);
  delay(500);
  int dist = ultrasonic();
  delay(100);
  myservo.write(110);
  return dist;
}
int left()
{
  myservo.write(170);
  delay(500);
  int dist = ultrasonic();
  delay(100);
  myservo.write(110);
  return dist;
}
void moveStop()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void moveForward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
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

void loop()
{
  // moveForward(); ///////////////////////////////////////////////////////////////////// dhyand do
  ultrasonic();
  myservo.write(pos);
  

  Flame = digitalRead(flamepin);
  //Flame = Serial.read();
   if (Flame==LOW)
   {l=0;
     l+=1;
   }
   else
   {h=0;
     h+=1;
   }

   if (distance > 8)
  {
   c1=0; 
   c1+=1;
   casee=c1;
  }

  else if (distance < 8 && l==1)
    
  {
   c2=0;
   c2+=2;
   casee=c2;
  }
  else if (distance < 8 && h==1)
  {
   c3=0;
   c3+=3;
   casee=c3;
  }

 switch(casee)
{
   case 1: moveForward();
              break;

 
   case 2: Serial.println("Flame");
           moveStop();
           fire_ex();
           delay(500);
           break;
  
   case 3: moveStop();
        distancer = right();
        distancel = left();
       if (distancer > distancel)
    {
      turnRight();
    }
      else if (distancer < distancel)
    {
      turnLeft();
    }
     break;  

 
  default:  Serial.println("no worries");
  
}
  delay(300); //Slow down the speed of robot

}
