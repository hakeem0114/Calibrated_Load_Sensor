//Libraries
#include <LiquidCrystal.h>
#include <Stepper.h>
#include <PID_v1.h>

//LCD
LiquidCrystal lcd(9,8,4,5,6,7);//(rs,e,d4,d5,d6,d7)

//Ultrasonic sensor
const int trigPin = 3, echoPin = 2;
float duration;
float distanceCM, distanceINCH ;
float  distanceM;
float mass = 0, weight = 0 ; 

//Stepper pins
int in1Pin = 10;
int in2Pin = 11;
int in3Pin = 12;
int in4Pin = 13;
int pos; // position of motor
Stepper motor(512, in1Pin, in2Pin, in3Pin, in4Pin);  

//Led
#define LED A0  // The pin the LED is connected to

//LDR
int sensorPin = A5; // select the input pin for LDR
int sensorValue = 0; // variable to store the value coming from the sensor

//PID controller
#define PIN_INPUT 0
#define PIN_OUTPUT 1 
//It is connected to the tx/rx pins so the code is uploaded before the wire is connected

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp=2, Ki=0.5, Kd=1; //Variables modified to achieve the best calibration
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

//////////////////////////////////////////////////////////////////
void setup() 
{
  lcd.begin(16,2); //Start LCD display
  pinMode(trigPin, OUTPUT); //Defines sensor pins as I/O
  pinMode(echoPin, INPUT);

  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);

  motor.setSpeed(20); //Sets the stepper motor speed

  //PID variable initialization
  Input = analogRead(PIN_INPUT);
  Setpoint = 100;

  //turns the PID on
  myPID.SetMode(AUTOMATIC); //Auto-calibrates

  pinMode(LED, OUTPUT); // Declare the LED as an output

  Serial.begin(9600); //sets serial port for communication
  
}
////////////////////////////////////////////////////////////////


void loop() 
{
  //LDR
  sensorValue = analogRead(sensorPin); // read the value from the sensor
  Serial.println(sensorValue); //prints the values coming from the sensor on the screen

  //LCD
   lcd.clear(); //Clears the LCD
   delay(10);

  //Starts ultrasonic sensor readings
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);//determine duration to calculate distance 

  //Distance measurements
  distanceCM = duration*0.034/2;
  distanceM = distanceCM/ 100; 
  distanceINCH = duration*0.0133/2;
  weight = (mass) * 0.0098;  // 1 g = 0.001 kg

   //Calibrates the analog values
    Input = analogRead(PIN_INPUT);
    myPID.Compute();
    analogWrite(PIN_OUTPUT, Output);
  

  //Weight scale, sensor readings 
  if (distanceCM > 9 && distanceCM < 11 ) //If distance = 10cm
   {
    
      /////////////////////////////////////////////////////////////////////
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Put on mass");
      delay(10);
      ///////////////////////////////////////////////////////////////////
       
   }
    else if (distanceCM > 8 && distanceCM < 10) //If distance = 9cm
      {
         mass = 69; //Mass of 1 AA = 23kg, Mass of 3 batteries = 69 kg
          motor.step(300);
          delay (2000);

        closed_loop1(); //LDR checks to see if stepper motor reached its position
        
        lcd.setCursor(0,0);
        lcd.print("mass: ");
        lcd.print(mass);
        lcd.print("g"); //grams
        delay(10);
      
        lcd.setCursor(0,1);
        lcd.print("Weight: ");
        lcd.print(weight);
        lcd.print("N"); //Newtons
        delay(100);
        starting(); //Starting position for stepper motor
      }

       else if (distanceCM > 7 && distanceCM < 9) //If distance = 8cm
      {

         mass = 138; //Mass of 1 AA = 23kg, Mass of 3 batteries = 69 kg
         motor.step(700);
        delay (2000);
        closed_loop2(); //LDR checks to see if stepper motor reached its position
        /////////////////////////////////////////////////////////////////////
        lcd.setCursor(0,0);
        lcd.print("mass: ");
        lcd.print(mass);
        lcd.print("g"); //grams
        delay(10);
      
        lcd.setCursor(0,1);
        lcd.print("Weight: ");
        lcd.print(weight);
        lcd.print("N"); //Newtons
        delay(100);
        ///////////////////////////////////////////////////////////////////
       starting(); //Starting position for stepper motor
      
      }
        
       else if (distanceCM > 6 && distanceCM < 8) //If distance = 7cm
      {
          mass = 207; //Mass of 1 AA = 23kg, Mass of 3 batteries = 69 kg
          motor.step(900);
          delay (2000);
          closed_loop3(); //LDR checks to see if stepper motor reached its position
         /////////////////////////////////////////////////////////////////////
          lcd.setCursor(0,0);
          lcd.print("mass: ");
          lcd.print(mass);
          lcd.print("g"); //grams
          delay(10);
        
          lcd.setCursor(0,1);
          lcd.print("Weight: ");
          lcd.print(weight);
          lcd.print("N"); //Newtons
          delay(100);
          ///////////////////////////////////////////////////////////////////
        starting(); //Starting position for stepper motor
      }  

     
  
}


//Homing function
void starting()
{
       if (distanceCM > 8 && distanceCM < 10) //If distance = 9cm
       {
        
         motor.step(-300);
         delay (5000);
       }
       
       else if (distanceCM > 7 && distanceCM < 9) //If distance = 8cm
       {
        
         motor.step(-700);
         delay (5000);
       }

       else if (distanceCM > 6 && distanceCM < 8) //If distance = 7cm
       {
        
         motor.step(-900);
         delay (5000);
       }
     
       
}

//Closed Loop check
void closed_loop1()   
{
  if (sensorValue > 82 && sensorValue < 85) //If stepper motor moves to correct position
      { //Flash led twice
          digitalWrite(LED, HIGH); // Turn the LED on
          delay(100);
          digitalWrite(LED, LOW); // Turn the LED on
          digitalWrite(LED, HIGH); // Turn the LED on
          delay(100);
          digitalWrite(LED, LOW); // Turn the LED on
      }
}

void closed_loop2()   
{
   if (sensorValue > 65 && sensorValue < 69) //If stepper motor moves to correct position
      { //Flash led twice
          digitalWrite(LED, HIGH); // Turn the LED on
          delay(100);
          digitalWrite(LED, LOW); // Turn the LED on
          digitalWrite(LED, HIGH); // Turn the LED on
          delay(100);
          digitalWrite(LED, LOW); // Turn the LED on
      }
}

void closed_loop3()   
{
   if (sensorValue > 73 && sensorValue < 78) //If stepper motor moves to correct position
      { //Flash led twice
          digitalWrite(LED, HIGH); // Turn the LED on
          delay(100);
          digitalWrite(LED, LOW); // Turn the LED on
          digitalWrite(LED, HIGH); // Turn the LED on
          delay(100);
          digitalWrite(LED, LOW); // Turn the LED on
      }
      
}
