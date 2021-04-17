// library that allows us to use the Servo class
#include <Servo.h>

// declare the two servo motors
Servo motor1;
Servo motor2;

// initialize the pin for the lazer
int pinLazer = 11;
//initialize a variable that contains the income value from the bluetooth app
char Incoming_value = 0;

// initialize the sensitivity of the servo motors
int sensitivy = 10;

// initialize the speed of the DC motors
int SPEED = 210;

// intitialzie the pin that connects to In1 in L298n module(DC motor controller)
int In1 = 5;
//intitialzie the pin that connects to In2 in L298n module(DC motor controller)
int In2 = 3;
//intitialzie the pin that connects to In3 in L298n module(DC motor controller)
int In3 = 7;
//intitialzie the pin that connects to In4 in L298n module(DC motor controller)
int In4 = 6;
//intitialzie the pin that connects to ENA in L298n module(DC motor controller)
int ENA = 8;
//intitialzie the pin that connects to ENB in L298n module(DC motor controller)
int ENB = 12;

// setup method: used to set the starting values of the pins
// this method runs only ones
void setup() {
  // starting the serial connection
  Serial.begin(9600);

  // adjust the pins for DC motor right
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(ENA, OUTPUT);
  //adjust the pins for DC motor left
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // adjust the pin for the lazer
  pinMode(pinLazer,OUTPUT);
  // set the lazer voltage to zero(Low)
  digitalWrite(pinLazer,LOW);
}
 // initialze varaibles that keep the current degree measurement of the servo motors
 int forward = 0;
 int left = 0;

// initialize a bool variable that controls which motors (servos or DC motors) to be on
 bool areServosOn=false;

 // loop method: it is endless method that runs the main commands of the program
void loop() {

  // checking for a connection
  if (Serial.available() > 0)
  {
    //Read the incoming data from the bluetooth module and store it into variable Incoming_value
    Incoming_value = Serial.read();      
    //Print Value of Incoming_value in Serial monitor
    Serial.print(Incoming_value);   
    //Print New line   
    Serial.print("/n");                  
    
//checking whether the DC motors or the servos are ON
   if (Incoming_value == 'X')
    {
      areServosOn=true;//on
    }
   if(Incoming_value == 'x')
    {
    areServosOn=false;//off
    }
    // the case when the servo motors are turned ON
    if(areServosOn)
    {
      // turning on the lazer
      digitalWrite(pinLazer,HIGH);
      // setting pins 2 and 4 like output for the degrees which the servos are going to be rotated
       motor1.attach(2);
       motor2.attach(4);
       // rotating the first servo motor 10 degrees left 
          if (Incoming_value == 'L') // case left
          {
            if(left<180)
            {
             left += sensitivy;
            }   
            motor1.write(left); 
          }
          // rotating the first servo motor 10 degrees right 
          else if (Incoming_value == 'R')// case right
          {
            if(left>0)
            {
             left -= sensitivy;
            }
              motor1.write(left);
          }
          // rotating the second servo motor 10 degrees up 
         if (Incoming_value == 'F') // case forward
          {
            if(forward<180)
            {
            forward += sensitivy;
            }
              motor2.write(forward);
          }
          // rotating the second servo motor 10 degrees down 
          else if (Incoming_value == 'B') // case down
          {
            if(forward>0)
            {
            forward -= sensitivy;
            } 
              motor2.write(forward);
          }
    }
    // the case when the DC motors are turned ON
    else if(areServosOn==false)
      {     
        // turning off the lazer
        digitalWrite(pinLazer,LOW);
        // rotating the two motors in direction that moves the car forward
        if (Incoming_value == 'F' )
              {
                Incoming_value = 'q';
               digitalWrite(In1, LOW);
                digitalWrite(In2, HIGH);
                digitalWrite(In3, HIGH);
                digitalWrite(In4, LOW);
                analogWrite(ENA, SPEED);
                analogWrite(ENB, SPEED);
                delay(30);
              }
              // rotating the two motors in direction that moves the car backward
              if (Incoming_value == 'B' )
              {
                Incoming_value = 'q';
                digitalWrite(In1, HIGH);
                digitalWrite(In2, LOW);
                digitalWrite(In3, LOW);
                digitalWrite(In4, HIGH);
                analogWrite(ENA, SPEED);
                analogWrite(ENB, SPEED);
                delay(30);
              }
              // rotating the two motors in direction that moves the car left
              if ( Incoming_value == 'L')
              {
                Incoming_value = 'q';
                digitalWrite(In1, LOW);
                digitalWrite(In2, HIGH);
                digitalWrite(In3, LOW);
                digitalWrite(In4, HIGH);
                analogWrite(ENA, SPEED);
                analogWrite(ENB, SPEED);
                delay(30);
              }
              // rotating the two motors in direction that moves the car right
              if (Incoming_value == 'R')
              {
                Incoming_value = 'q';
                digitalWrite(In1, HIGH);
                digitalWrite(In2, LOW);
                digitalWrite(In3, HIGH);
                digitalWrite(In4, LOW);
                analogWrite(ENA, SPEED);
                analogWrite(ENB, SPEED);
                delay(30);
              }
              // stops the DC motors
              digitalWrite(In1, LOW);
              digitalWrite(In2, LOW);
              digitalWrite(In3, LOW);
              digitalWrite(In4, LOW);   
   }
   }
}
