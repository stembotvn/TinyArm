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

#define DK_sv1 A2
#define DK_sv2 A3
#define DK_sv3 A0
#define DK_sv4 A1
#define speaker 2
#define led1 13
#define led2 3
#define led3 4
#define led4 8
#define led5 7
#define BT1 12
#define BT2 A7
#define BT3 A6

#define enable_rc digitalWrite(PowSV, HIGH);
#define disable_rc digitalWrite(PowSV, LOW);
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

int button1 = 0;
int button2 = 0;
int button3 = 0;
int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;
int k;

void servo_int()
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
}
void setup()
{
  Serial.begin(9600);
//  sv1.attach(pin_sv1);
//  sv2.attach(pin_sv2);
//  sv3.attach(pin_sv3);
//  sv4.attach(pin_sv4);

  pinMode(speaker, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(BT1, INPUT);
  pinMode(BT2, INPUT);
  pinMode(BT3, INPUT);
  pinMode(PowSV, OUTPUT);
  disable_rc
  servo_int();

  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
}
void testSV1()
{
  enable_rc
  val1 = analogRead(DK_sv1);
  val1 = map(val1, 0, 1023, 0, 180);
  sv1.write(val1);
  Serial.println(val1);

  val2 = analogRead(DK_sv2);
  val2 = map(val2, 0, 1023, 0, 180);
  sv2.write(val2);
  Serial.println(val2);

  val3 = analogRead(DK_sv3);
  val3 = map(val3, 0, 1023, 0, 180);
  sv3.write(val3);
  Serial.println(val3);

  val4 = analogRead(DK_sv4);
  val4 = map(val4, 0, 1023, 0, 180);
  sv4.write(val4);
  Serial.println(val4);
}
void read_button()
{
  button1 = digitalRead(BT1);
  button2 = analogRead(BT2);
  button3 = analogRead(BT3);

  if(button1 == LOW)
  {
    led1_on
    k = 1;
    disable_rc
  }
  else if(button2 < 100)
  {
    led2_on
    k = 2;
  }
  else if(button3 < 100)
  {
    led3_on
    k = 3;
  }
  else 
  {
    led1_off
    led2_off
    led3_off
  }
}
void loop()
{
  testSV1();
  read_button();
}

