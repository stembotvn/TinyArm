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

#define enable_rc   digitalWrite(PowSV, LOW);
#define disable_rc  digitalWrite(PowSV, HIGH);
#define led1_on     digitalWrite(led1,LOW);
#define led1_off    digitalWrite(led1,HIGH);
#define led2_on     digitalWrite(led2,LOW);
#define led2_off    digitalWrite(led2,HIGH);
#define led3_on     digitalWrite(led3,LOW);
#define led3_off    digitalWrite(led3,HIGH);
#define led4_on     digitalWrite(led4,LOW);
#define led4_off    digitalWrite(led4,HIGH);
#define led5_on     digitalWrite(led5,LOW);
#define led5_off    digitalWrite(led5,HIGH);
#define speaker_on  digitalWrite(speaker,HIGH);
#define speaker_off digitalWrite(speaker,LOW);

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
void ARM_int()
{
  pinMode(PowSV, OUTPUT);
  disable_rc
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
    speaker_on   
    delay(time_);
    speaker_off
    delay(time_);
  }
}
void nhay(int n,int time_)
{
  for(int i=0;i<n;i++)
  {
    led1_on led2_on led3_on led4_on led5_on   
    delay(time_);
    led1_off led2_off led3_off led4_off led5_off 
    delay(time_);
  }
}
void led_off()
{
  led1_off 
  led2_off 
  led3_off 
  led4_off 
  led5_off 
}

void readPot()                          // Read value of manual speed knob
{                        
  enable_rc   
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
void controlSV()
{
  enable_rc
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
void controlServo(int t)                                          //Servo speed control
{
  enable_rc
  for(int i = 0; i < 4; i++)
    {
      if(Position1[i] < Position1[i+1])
      {
        for(int j = Position1[i]; j <= Position1[i+1]; j++)
        {
          sv1.write(j);
          delay(t);
        }
      }
      else if(Position1[i] > Position1[i+1])
      {
        for(int j = Position1[i]; j >= Position1[i+1]; j--)
        {
          sv1.write(j);
          delay(t);
        }
      }
      
      ////////////////  2  ////////////////
      if(Position2[i] < Position2[i+1])
      {
        for(int j = Position2[i]; j <= Position2[i+1]; j++)
        {
          sv2.write(j);
          delay(t);
        }
      }
      else if(Position2[i] > Position2[i+1])
      {
        for(int j = Position2[i]; j >= Position2[i+1]; j--)
        {
          sv2.write(j);
          delay(t);
        }
      }
      
      ///////////////  3  /////////////////
      if(Position3[i] < Position3[i+1])
      {
        for(int j = Position3[i]; j <= Position3[i+1]; j++)
        {
          sv3.write(j);
          delay(t);
        }
      }
      else if(Position3[i] > Position3[i+1])
      {
        for(int j = Position3[i]; j >= Position3[i+1]; j--)
        {
          sv3.write(j);
          delay(t);
        }
      }
      
      ////////////////  4  /////////////////////
      if(Position4[i] < Position4[i+1])
      {
        for(int j = Position4[i]; j <= Position4[i+1]; j++)
        {
          sv4.write(j);
          delay(t);
        }
      }
      else if(Position4[i] > Position4[i+1])
      {
        for(int j = Position4[i]; j >= Position4[i+1]; j--)
        {
          sv4.write(j);
          delay(t);
        }
      }
    }
    bip(1,500);
}

void start()
{
  enable_rc
  button1 = digitalRead(BT1);
  button2 = digitalRead(BT2);
  controlSV();
  
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
      led1_on
      break;
    case 3:
      Position1[2] = val1;
      Position2[2] = val2;
      Position3[2] = val3;
      Position4[2] = val4;
      led2_on
      break;
    case 4:
      Position1[3] = val1;
      Position2[3] = val2;
      Position3[3] = val3;
      Position4[3] = val4;
      led3_on
      break;
      case 5:
      Position1[4] = val1;
      Position2[4] = val2;
      Position3[4] = val3;
      Position4[4] = val4;
      led4_on
      break;
    case 6:
      led5_on
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
    controlSpeed(20);
  }
}


///////////////////
void setup()
{
  Serial.begin(9600);
  disable_rc
  ARM_int();
}

void loop()
{
  start();
}
