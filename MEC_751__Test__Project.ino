#include <LiquidCrystal.h>
#include <Stepper.h>

////////////////////////////////////////////////////
//LCD
LiquidCrystal lcd(9,8,4,5,6,7);//(rs,e,d4,d5,d6,d7)
const int trigPin = 3, echoPin = 2;
float duration;
float distanceCM, distanceINCH ;
float  distanceM;
float mass = 0, weight = 0 ; 
////////////////////////////////////////////////////

///////////////////////////////////////////
//Stepper pins
int in1Pin = 10;
int in2Pin = 11;
int in3Pin = 12;
int in4Pin = 13;
int pos; // position of motor

Stepper motor(512, in1Pin, in2Pin, in3Pin, in4Pin);  
/////////////////////////////////////////////


////////////////////////////////////////////
//Led
#define LED A0  // The pin the LED is connected to

#define IR_SENSOR_RIGHT A1

//////////////////////////////////////////

void setup() 
{
  lcd.begin(16,2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

    pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);

    motor.setSpeed(20);

    pinMode(LED, OUTPUT); // Declare the LED as an output
}

void loop() 
{
   /////////////////////////////////////////////////////
   //main
   lcd.clear();
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
  weight = (mass) * 0.0098;  // 1g = 0.001 kg
  ///////////////////////////////////////////////////////
/*
//2 
lcd.clear();
delay (5000);
      motor.step(275);
      delay (5000);
         motor.step(-275);
         
  mass = 69; //Mass of 1 AA = 23kg, Mass of 3 batteries = 69 kg    
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

//4
lcd.clear();
delay (5000);
      motor.step(555);
      delay (5000);
      motor.step(-555);
         
  mass = 138; //Mass of 1 AA = 23kg, Mass of 3 batteries = 69 kg
     
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
*/

// mass = 69, 138, 207
    
//motor = 300, 700, 900

//ldr: 82-85, 65-69, 73-78



//69
lcd.clear();
delay (5000);

  mass = 69; //Mass of 1 AA = 23kg, Mass of 3 batteries = 69 kg

  //LCD   
  lcd.setCursor(0,0);
  lcd.print("mass: ");
  lcd.print("69 g"); //grams
  delay(100);

      //motor
      motor.step(300);
      delay (5000);
      motor.step(-300);
         


  //LED
   digitalWrite(LED, HIGH); // Turn the LED on
   delay (100);
  digitalWrite(LED, LOW); // Turn the LED on
   delay (100);
   digitalWrite(LED, HIGH); // Turn the LED on
   delay (100);
  digitalWrite(LED, LOW); // Turn the LED on
   delay (100);

  

//138
lcd.clear();
delay (5000);

  mass = 207; //Mass of 1 AA = 23kg, Mass of 3 batteries = 69 kg

  //LCD   
  lcd.setCursor(0,0);
  lcd.print("mass: ");
  lcd.print("138 g"); //grams
  delay(100);

      //motor
      motor.step(700);
      delay (5000);
      motor.step(-700);
         

  //LED
   digitalWrite(LED, HIGH); // Turn the LED on
   delay (100);
  digitalWrite(LED, LOW); // Turn the LED on
   delay (100);
   digitalWrite(LED, HIGH); // Turn the LED on
   delay (100);
  digitalWrite(LED, LOW); // Turn the LED on
   delay (100);


//207
lcd.clear();
delay (5000);

  mass = 207; //Mass of 1 AA = 23kg, Mass of 3 batteries = 69 kg

  //LCD   
  lcd.setCursor(0,0);
  lcd.print("mass: ");
  lcd.print("207 g"); //grams
  delay(100);
      //motor
      motor.step(900);
      delay (5000);
      motor.step(-900);
         


  //LED
   digitalWrite(LED, HIGH); // Turn the LED on
   delay (100);
  digitalWrite(LED, LOW); // Turn the LED on
   delay (100);
   digitalWrite(LED, HIGH); // Turn the LED on
   delay (100);
  digitalWrite(LED, LOW); // Turn the LED on
   delay (100);

   delay (5000);
/*

  
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
      motor.step(275);
      delay (2000);

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

       else if (distanceCM > 7 && distanceCM < 9) //If distance = 8cm
      {

         mass = 138; //Mass of 1 AA = 23kg, Mass of 3 batteries = 69 kg
      motor.step(555);
      delay (2000);

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
        motor.step(840);
        delay (2000);

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
    

  // Weight = distanceCM - 1 

  
  /*
  lcd.setCursor(0,0);
  lcd.print("DistanceCM: ");
  lcd.print(distanceCM); lcd.print("cm");delay(10);
  
  /*
  lcd.setCursor(0,1);
  lcd.print("Distance: ");
  lcd.print(distanceINCH); lcd.print("inch");delay(100);
  
   lcd.setCursor(0,1);
  lcd.print("DistanceM: ");
  lcd.print(distanceCM/100); lcd.print("m");delay(100);
  
  if(distanceINCH>99){//for displaying purposes
      lcd.clear(); delay(10);
    }
   */
  
}
////////////////////////////////////////////////////////////////

//Homing motor
void starting()
{
           
       if (distanceCM > 8 && distanceCM < 10) //If distance = 9cm
       {
        
         motor.step(-275);
         delay (5000);
       }
       
       else if (distanceCM > 7 && distanceCM < 9) //If distance = 8cm
       {
        
         motor.step(-555);
         delay (5000);
       }

       else if (distanceCM > 6 && distanceCM < 8) //If distance = 8cm
       {
        
         motor.step(-840);
         delay (5000);
       }
     
       
     

}
