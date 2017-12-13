#include <Servo.h>
Servo j1;
Servo j2;
Servo j3;
Servo j4;
#define en_servo 11 
#define pin_j1 5
#define pin_j2 6
#define pin_j3 9
#define pin_j4 10
#define Apin_j1 A0
#define Apin_j2 A1
#define Apin_j3 A2
#define Apin_j4 A3
#define Power_in A4
#define speaker 2
#define led1 13
#define led2 3
#define led3 4
#define led4 8
#define led5 7
#define button1 12
#define button2 A7
#define button3 A6
#define enable_rc   analogWrite(en_servo,255);
#define disable_rc  analogWrite(en_servo,0);
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
int val_bt1,val_bt2,val_bt3,val; 
void servo_int();
void test_servo();
void led_int();
void button_int();
void nhay(int n);
void servo_int()
{
  pinMode(en_servo, OUTPUT);
  disable_rc
  j1.attach(pin_j1);j2.attach(pin_j2);j3.attach(pin_j3);j4.attach(pin_j4);
}
void led_int()
{
    pinMode(speaker, OUTPUT);
    pinMode(led1, OUTPUT);pinMode(led2, OUTPUT);pinMode(led3, OUTPUT);pinMode(led4, OUTPUT);pinMode(led5, OUTPUT);
}
void button_int()
{
    pinMode(button1, INPUT);
    pinMode(button2, INPUT);
    pinMode(button3, INPUT);
}
void test_servo()
{
  val = analogRead(Apin_j4);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  j4.write(val);                  // sets the servo position according to the scaled value
  Serial.println(val);
}
void test_button()
{
  // read the state of the pushbutton value:
  val_bt1 = digitalRead(button1);
  val_bt2 = analogRead(button2);
  val_bt3 = analogRead(button3);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (val_bt1 == HIGH) led1_off
  else {enable_rc led1_on }
  if (val_bt2 >100) led2_off
  else {disable_rc led2_on }
  if (val_bt3 >100) led3_off
  else led3_on
}
void led_off()
{
      led1_off led2_off led3_off led4_off led5_off 
}
void nhay(int n,int time_)
{
  for(int i=0;i<=n;i++)
  {
    led1_on led2_on led3_on led4_on led5_on   
    delay(time_);
    led1_off led2_off led3_off led4_off led5_off 
    delay(time_);
  }
}
void bip(int n,int time_)
{
  for(int i=0;i<=n;i++)
  {
    speaker_on   
    delay(time_);
    speaker_off
    delay(time_);
  }
}


