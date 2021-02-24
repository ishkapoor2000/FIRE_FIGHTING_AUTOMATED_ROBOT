#include <Servo.h>
// #include <AFMotor.h>
Servo myservo;


int pos = 0;
const int flamePin = 11;
char Flame = LOW;
int distancer;
int distancel;

#define LM1 0        // left motor
#define LM2 1        // left motor
#define RM1 2        // right motor
#define RM2 4        // right motor
#define ENA 5        // motor driver
#define ENB 6        // motor driver
#define trigPin 8    // ultrasonic sensor
#define echoPin 9    // ultrasonic sensor
#define pump 10      // water pump[DC motor]
 //#define FS 11        // forward sensor
//#define LS 12        // left sensor
//#define RS 13        // right sensor
#define TS A0        // TMP36 temperature sensor

const int sensorMin = 0;     // sensor min
const int sensorMax = 1024;  // sensor max

// defines variables
long duration; // variable for the duration of sound wave travel
int distance;  // variable for the distance measurement
int ultrasonic();

void setup()
{
  //pinMode(LS, INPUT);
  //pinMode(RS, INPUT);
  //pinMode(FS, INPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(TS, INPUT);

  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);

  

  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 

  Serial.begin(9600); 

  myservo.attach(3); //Water Pump's Base Servo Motor
  myservo.write(90);const int buzzerPin = 12;


  pinMode(buzzerPin, OUTPUT);
  pinMode(flamePin, INPUT);
  Serial.begin(9600);

}

 /*void flame(){
  
  int sensorReading = analogRead(TS); // analog pin A0:
  
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3); //mapping the values sensormin, sensormax, sensorreading
  
  switch (range) {
  case 0:    
    Serial.println("* Close Fire *"); // closer than 1.5 feet away.
    break;
  case 1:    
    Serial.println("* Distant Fire *"); // between 1-3 feet away.
    break;
  case 2:    
    Serial.println("No Fire"); // No fire detected.
    break;
  }
  delay(1);  
  
}*/

void fire_ex()
{    
 delay (500);

    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);

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

  digitalWrite(pump,LOW);
  myservo.write(90);

  Flame=LOW;
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

void loop()
{
  ultrasonic();
  myservo.write(pos);
  

  /*if (digitalRead(LS) ==1 && digitalRead(RS)==1 && digitalRead(FS) ==1) //no fire // If US not detect => move
  {
    //To move 
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
  }
  else if (digitalRead(FS) ==0) //straight
  {
    //Move the robot forward
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    fire = true;
  }
  else if (digitalRead(LS) ==0) //left
  {
    //Move the robot left
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
  }
  else if (digitalRead(RS) ==0) // right
  {
    //Move the robot right
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
  }*/
    Flame = digitalRead(flamePin);
  if (Flame== HIGH)
  {
    Serial.println("Fire!!!");
    //fire_ex();
    //digitalWrite(buzzerPin, HIGH);
  }
  else
  {
    Serial.println("No worries");
    //digitalWrite(buzzerPin, LOW);
  }
  if(distance>8)
  { 
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    }
  
      else if(distance<8 & Flame==HIGH)
      {
        digitalWrite(LM1, LOW);
        digitalWrite(LM2, LOW);
        digitalWrite(RM1, LOW);
        digitalWrite(RM2, LOW);
        fire_ex();
        delay(500);
       }
      else if(distance<8)
      {
        distancer=right();
        distancel=left();
        if(distancer>distancel)
        {
         digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
        }
       else if(distancer<distancel)
        {
        digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
        }
      }
    
 
  delay(300); //Slow down the speed of robot
  
//   Flame = digitalRead(flamePin);
//  if (Flame== HIGH)
//  {
//    Serial.println("Fire!!!");
//    //fire_ex();
//    //digitalWrite(buzzerPin, HIGH);
//  }
//  else
//  {
//    Serial.println("No worries");
//    //digitalWrite(buzzerPin, LOW);
//  }

  /*while (Flame == 1)
  {
    fire_ex();
  }*/

  //flame();
  }
