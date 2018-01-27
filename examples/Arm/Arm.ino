#include <Servo.h>
Servo sv1;
Servo sv2;
Servo sv3;
Servo sv4;

#define PowSV 11
#define pin_sv1 5
#define pin_sv2 6
#define pin_sv3 9
#define pin_sv4 10

#define Pot1 A6
#define Pot2 A7
#define Pot3 A0
#define Pot4 A1
#define speaker 2
#define led1 4
#define led2 3
#define led3 7
#define led4 8
#define led5 12
#define BT1 A2
#define BT2 A3

bool button1;
bool button2;
bool button1_ = 1;
bool button2_= button2;
int val1;
int val2;
int val3;
int val4;
int lastval1 = val1;
int lastval2 = val2;
int lastval3 = val3;
int lastval4 = val4;
int count = 0;
int Position1[5] = {90, 90, 90, 90, 90};
int Position2[5] = {90, 90, 90, 90, 90};
int Position3[5] = {90, 90, 90, 90, 90};
int Position4[5] = {90, 90, 90, 90, 90};
///////////////////
void enable_rc()
{
  digitalWrite(PowSV, LOW);
}
void disable_rc()
{
  digitalWrite(PowSV,HIGH);
}
void ARM_int()
{
  pinMode(PowSV, OUTPUT);
  disable_rc();
  sv1.attach(pin_sv1);
  sv2.attach(pin_sv2);
  sv3.attach(pin_sv3);
  sv4.attach(pin_sv4);
  sv1.write(90);
  sv2.write(90);
  sv3.write(90);
  sv4.write(90);


  pinMode(speaker, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  //pinMode(BT1, INPUT_PULLUP);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
}

void bip(int n,int time_)
{
  for(int i=0;i<n;i++)
  {
    digitalWrite(speaker,HIGH);   
    delay(time_);
    digitalWrite(speaker,LOW);
    delay(time_);
  }
}
void nhay(int n,int time_)
{
  for(int i=0;i<n;i++)
  {
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    digitalWrite(led4,LOW);
    digitalWrite(led5,LOW);  
    delay(time_);
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,HIGH);
    digitalWrite(led4,HIGH);
    digitalWrite(led5,HIGH);
    delay(time_);
  }
}
void led_off()
{
  digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,HIGH);
  digitalWrite(led4,HIGH);
  digitalWrite(led5,HIGH);
}

void readPot()                          // Read value of manual speed knob
{                        
  enable_rc();  
  val1 = analogRead(Pot1);           // reads the value of the potentiometer (value between 0 and 1023)
  val2 = analogRead(Pot2);
  val3 = analogRead(Pot3);
  val4 = analogRead(Pot4);
  val1 = map(val1, 0, 1023, 0, 179);  // scale it to use it with the servo (value between 0 and 180)
  val2 = map(val2, 0, 1023, 0, 179);
  val3 = map(val3, 0, 1023, 0, 179);
  val4 = map(val4, 0, 1023, 5, 120);
}
void setPosition(int pos1, int pos2, int pos3, int pos4)    // Set the servo position
{            
  sv1.write(pos1);                                          // Write the position to the servo                                                
  sv2.write(pos2);
  sv3.write(pos3);
  sv4.write(pos4);
  delay(20);                                                // waits for the servo to get there 
}
void checkValue()
{
  enable_rc();
  readPot();
  if(val1 != lastval1)                                      // If the value has changed then update the servo
  {
    setPosition(val1, val2, val3, val4);                    // Set the servo position
    lastval1 = val1;                                        // reset to last state
  }
  else if(val2 != lastval2)
  {
    setPosition(val1, val2, val3, val4);
    lastval2 = val2;
  }
  else if(val3 != lastval3)
  {
    setPosition(val1, val2, val3, val4);
    lastval3 = val3;
  }
  else if(val4 != lastval4)
  {
    setPosition(val1, val2, val3, val4);
    lastval4 = val4;
  }
}
/////////////////

bool servoControl (int thePos,int startPos, Servo theServo )    //Function Form: outputType FunctionName (inputType localInputName)
{     
    //This function moves a servo a certain number of steps toward a desired position and returns whether or not it is near or hase recahed that position
    // thePos - the desired position
    // thServo - the address pin of the servo that we want to move
    // theSpeed - the delay between steps of the servo
    
    //int startPos = theServo.read();       //read the current position of the servo we are working with.
    int newPos = startPos;                // newPos holds the position of the servo as it moves
    
    //define where the pos is with respect to the command
    // if the current position is less that the desired move the position up
    if (startPos < thePos){
       newPos = newPos + 1;               
       theServo.write(newPos);
    //   delay(theSpeed);
       return 0;                          // Tell primary program that servo has not reached its position     
    }

    // Else if the current position is greater than the desired move the servo down
    else if (newPos > thePos){
      newPos = newPos - 1;
      theServo.write(newPos);
   //   delay(theSpeed);
      return 0;  
    }  

    // If the servo is +-5 within the desired range then tell the main program that the servo has reached the desired position.
    else 
    {
        return 1;
    }  
}
void ParallelControl(int t,int count)                                          //Servo speed control
{
  enable_rc();
  bool done = 0;
  bool status1 = 0 ;
  bool status2 = 0;
  bool status3 = 0;
  bool status4 = 0;
  for (int i=0;i<count;i++)
  {
    while (!done)
    {
      status1 = servoControl(Position1[i],Position1[i+1], sv1);
      status2 = servoControl(Position2[i],Position2[i+1], sv2);
      status3 = servoControl(Position3[i],Position3[i+1], sv3);
      status4 = servoControl(Position4[i],Position4[i+1], sv4);

      if (status1 == 1 & status2 == 1 & status3 == 1 & status4 == 1) done = 1;
      delay(t);
    }
  }
  bip(1,500);
}
void start()
{
  enable_rc();
  button1 = digitalRead(BT1);
  button2 = digitalRead(BT2);
  checkValue();
  
  if(button1 != button1_)
  {
    if(button1 == LOW)
    {
      bip(1,200);
      count++;
      Serial.print("Pressed ");  Serial.println(count);

    }
    else Serial.println("Release ");
    button1_ = button1;
  }
 
  switch(count) //record position servo
  {
    case 1:
      Position1[0] = val1;
      Position2[0] = val2;
      Position3[0] = val3;
      Position4[0] = val4;
      break;
    case 2:
      Position1[1] = val1;
      Position2[1] = val2;
      Position3[1] = val3;
      Position4[1] = val4;
      digitalWrite(led1,LOW);
      break;
    case 3:
      Position1[2] = val1;
      Position2[2] = val2;
      Position3[2] = val3;
      Position4[2] = val4;
      digitalWrite(led2,LOW);
      break;
    case 4:
      Position1[3] = val1;
      Position2[3] = val2;
      Position3[3] = val3;
      Position4[3] = val4;
      digitalWrite(led3,LOW);
      break;
      case 5:
      Position1[4] = val1;
      Position2[4] = val2;
      Position3[4] = val3;
      Position4[4] = val4;
      digitalWrite(led4,LOW);
      break;
    case 6:
      digitalWrite(led5,LOW);
      break;
    case 7:
      nhay(3,200);
      led_off();
      count = 0;
      for(int i=0;i<=4;i++)
      {
        Position1[i] = val1;
        Position2[i] = val2;
        Position3[i] = val3;
        Position4[i] = val4;
      }
      break;
  }

  if(button2 == LOW)
  {
    bip(3,150);
    ParallelControl(20, count);
  }
}


///////////////////
void setup()
{
  Serial.begin(9600);
  disable_rc();
  ARM_int();
}

void loop()
{
  start();
}
