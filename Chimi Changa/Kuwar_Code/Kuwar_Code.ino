#include <Servo.h>
Servo myservo;
 
int pos = 0;    
boolean fire = false;
 
#define LS 9      // left sensor
#define RS 10      // right sensor
#define FS 8 //forward sensor
 
#define LM1 2       // left motor
#define LM2 3       // left motor
#define RM1 4       // right motor
#define RM2 5       // right motor
#define pump 6
void setup()
{
 pinMode(LS, INPUT);
  pinMode(RS, INPUT);
  pinMode(FS, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(pump, OUTPUT);
 
  myservo.attach(11);
  myservo.write(90); 
}
void fire_ex()
{    
 delay (500);
 
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    
   digitalWrite(pump, HIGH); delay(500);
    
    for (pos = 50; pos <= 130; pos += 1) { 
    myservo.write(pos); 
    delay(10);  
  }
  for (pos = 130; pos >= 50; pos -= 1) { 
    myservo.write(pos); 
    delay(10);
  }
  
  digitalWrite(pump,LOW);
  myservo.write(90);
  
  fire=false;
}
void loop()
{
        myservo.write(90);   
if (digitalRead(LS) ==1 && digitalRead(RS)==1 && digitalRead(FS) ==1) //no fire
{
//Do not move 
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
}
delay(300); //Slow down the speed of robot
while (fire == true)
{
fire_ex();
}
}
