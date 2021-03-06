#include "ARMbot.h"

ARMbot::ARMbot()
{

}

void ARMbot::init()
{
  _sv1.attach(pin_sv1);
  _sv2.attach(pin_sv2);
  _sv3.attach(pin_sv3);
  _sv4.attach(pin_sv4);

  pinMode(BT1, INPUT);
  pinMode(BT2, INPUT);
  pinMode(BT3, INPUT);

  pinMode(PowSV, OUTPUT);
  pinMode(speaker, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
}
void ARMbot::enable_rc()
{
	digitalWrite(PowSV, LOW);
}
void ARMbot::disable_rc()
{
	digitalWrite(PowSV, HIGH);
}
void ARMbot::begin()
{
	readPot();
  enable_rc();
  bool done = 0;
  bool status1 = 0;
  bool status2 = 0;
  bool status3 = 0;
  bool status4 = 0;
  while (!done)
  {
    status1 = servoControl(_val1, _sv1);
    status2 = servoControl(_val2, _sv2);
    status3 = servoControl(_val3, _sv3);
    status4 = servoControl(_val4, _sv4);
    if ((status1 == 1) && (status2 == 1) && (status3 == 1) && (status4 == 1)) done = 1;
    delay(50);
  }
  tick(5,1000,50);
}
void ARMbot::bip(int n, int time_)
{
	for(int i=0;i<n;i++)
  {
    digitalWrite(speaker,HIGH);
    delay(time_);
    digitalWrite(speaker,LOW);
    delay(time_);
  }
}
void ARMbot::tone(uint16_t frequency, uint32_t duration)
{
  int period = 1000000L / frequency;
  int pulse = period / 2;
  for (long i = 0; i < duration * 1000L; i += period)
  {
    digitalWrite(speaker, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(speaker, LOW);
    delayMicroseconds(pulse);
  }
}
void ARMbot::tick(int n, uint16_t frequency, int times)
{
  for(int i=0; i<n; i++)
  {
    tone(frequency, times);
    digitalWrite(speaker, LOW);
    delay(times);
  }
}
void ARMbot::blinks(int n, int time_)
{
	for(int i=0;i<n;i++)
  {
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    delay(time_);
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,HIGH);
    delay(time_);
  }
}
void ARMbot::led_off()
{
	digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,HIGH);
}
void ARMbot::led_on()
{
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
}
void ARMbot::setLed(bool l1, bool l2, bool l3) // led off = 1, led on = 0;
{
  digitalWrite(led1,l1);
  digitalWrite(led2,l2);
  digitalWrite(led3,l3);
}
bool ARMbot::readButton1()
{
  _button1 = digitalRead(BT1);
  if(_button1 == LOW) return 0;
  else return 1;
}
bool ARMbot::readButton2()
{
  _button2 = digitalRead(BT2);
  if(_button2 == LOW) return 0;
  else return 1;
}
bool ARMbot::readButton3()
{
  _button3 = digitalRead(BT3);
  if(_button3 == LOW) return 0;
  else return 1;
}
void ARMbot::readPot()
{
	// Read value of manual speed knob
	enable_rc();
  _val1 = analogRead(Pot1);             // reads the value of the potentiometer (value between 0 and 1023)
  _val2 = analogRead(Pot2);
  _val3 = analogRead(Pot3);
  _val4 = analogRead(Pot4);
  _val1 = map(_val1, 0, 1023, 179, 0);  // scale it to use it with the servo (value between 0 and 180)
  _val2 = map(_val2, 0, 1023, 179, 0);
  _val3 = map(_val3, 0, 1023, 197, 0);
  _val4 = map(_val4, 0, 1023, 120, 160);
}
void ARMbot::setPosition(int pos1, int pos2, int pos3, int pos4)
{
	// Set the servo position
	_sv1.write(pos1);             // Write the position to the servo
  _sv2.write(pos2);
  _sv3.write(pos3);
  _sv4.write(pos4);
  delay(20);
}
void ARMbot::checkValue()
{
	enable_rc();
  readPot();
  if(_val1 != _lastval1)                                    // If the value has changed then update the servo
  {
    setPosition(_val1, _val2, _val3, _val4);                // Set the servo position
    _lastval1 = _val1;                                      // reset to last state
  }
  else if(_val2 != _lastval2)
  {
    setPosition(_val1, _val2, _val3, _val4);
    _lastval2 = _val2;
  }
  else if(_val3 != _lastval3)
  {
    setPosition(_val1, _val2, _val3, _val4);
    _lastval3 = _val3;
  }
  else if(_val4 != _lastval4)
  {
    setPosition(_val1, _val2, _val3, _val4);
    _lastval4 = _val4;
  }
}
bool ARMbot::servoControl(int thePos, Servo theServo)
{
	//This function moves a servo a certain number of steps toward a desired position and returns whether or not it is near or hase recahed that position
  // thePos - the desired position
  // thServo - the address pin of the servo that we want to move
  // theSpeed - the delay between steps of the servo

  int startPos = theServo.read();       //read the current position of the servo we are working with.
  int newPos = startPos;                // newPos holds the position of the servo as it moves

  //define where the pos is with respect to the command
  // if the current position is less that the desired move the position up
  if (startPos < thePos)
  {
    newPos = newPos + 1;
    theServo.write(newPos);
    return 0;                          // Tell primary program that servo has not reached its position
  }

  // Else if the current position is greater than the desired move the servo down
  else if (newPos > thePos)
  {
    newPos = newPos - 1;
    theServo.write(newPos);
    return 0;
  }

  // If the servo is the desired range then tell the main program that the servo has reached the desired position.
  else
  {
    return 1;
  }
}
void ARMbot::ParallelControl(int t, int steps)
{
  enable_rc();
  bool done = 0;
  bool status1 = 0 ;
  bool status2 = 0;
  bool status3 = 0;
  bool status4 = 0;
  for (int i=0;i<steps;i++)
  {
    //Serial.println(String("i = ")+ i);
    //Serial.println(String("steps = ")+ steps);
    while (!done)
    {
      status1 = servoControl(_Position[0][i], _sv1);
      status2 = servoControl(_Position[1][i], _sv2);
      status3 = servoControl(_Position[2][i], _sv3);
      if ((status1 == 1) && (status2 == 1) && (status3 == 1)) done = 1;
      delay(t);
    }
    done = 0;
    while(!done)
    {
      status4 = servoControl(_Position[3][i], _sv4);
      if (status4 == 1) done = 1;
      delay(t);
    }
    	done = 0;
  }
}
void ARMbot::start()
{
  enable_rc();
  bool k = 0;
  for(int i=0;i<50;i++)
  {
    _Position[0][i] = 90;
    _Position[1][i] = 90;
    _Position[2][i] = 90;
    _Position[3][i] = 90;
  }
  while(_count < 100)
  {
    checkValue();
    if(readButton1() == LOW)
    {
      setLed(0,1,1);
      if(k==1) 
      {  
        _count = 0;
        k = 0;
      }
      tick(1,1000,200);
      Serial.print("Pressed ");  Serial.println(_count);
      _Position[0][_count] = _val1;
      _Position[1][_count] = _val2;
      _Position[2][_count] = _val3;
      _Position[3][_count] = _val4;
      _count++; 
    }
    
    if(readButton2() == LOW)
    {
        setLed(1,0,1);
        tick(3,1000,150);
        ParallelControl(20, _count);
        tick(1,1000,500);
        k = 1;
        setLed(1,1,1);
    }
    if(readButton3() == LOW)
    {
      setLed(1,1,0);
      tick(1,1000,1000);
      for(int i=0;i<50;i++)
      {   
        _Position[0][i] = _val1;
        _Position[1][i] = _val2;
        _Position[2][i] = _val3;
        _Position[3][i] = _val4;
      }
      setLed(1,1,1);
    }
  }
  _count = 0;
  blinks(3,200);
  led_off();

}

void ARMbot::setBase(int pos,int speed)
{
  enable_rc();
  bool done = 0;
  bool status1 = 0 ;
  while (!done)
  {
    status1 = servoControl(pos, _sv1);
    if (status1 == 1) done = 1;
    delay(speed);
  }
  done = 0;
}
void ARMbot::setShoulder(int pos,int speed)
{
  enable_rc();
  bool done = 0;
  bool status1 = 0 ;
  while (!done)
  {
    status1 = servoControl(pos, _sv2);
    if (status1 == 1) done = 1;
    delay(speed);
  }
  done = 0;
}
void ARMbot::setElbow(int pos,int speed)
{
  enable_rc();
  bool done = 0;
  bool status1 = 0 ;
  while (!done)
  {
    status1 = servoControl(pos, _sv3);
    if (status1 == 1) done = 1;
    delay(speed);
  }
  done = 0;
}
void ARMbot::setGrip(int pos,int speed)
{
  enable_rc();
  bool done = 0;
  bool status1 = 0 ;
  while (!done)
  {
    status1 = servoControl(pos, _sv4);
    if (status1 == 1) done = 1;
    delay(speed);
  }
  done = 0;
}
void ARMbot::moveArm(int Base_pos,int Shoulder_pos,int Elbow_pos,int Grip_pos,int speed)//move parallel servo to target
{
  _Position[0][0] = Base_pos;
  _Position[0][0] = Shoulder_pos;
  _Position[0][0] = Elbow_pos;
  _Position[0][0] = Grip_pos;
  ParallelControl(speed, 1);
}