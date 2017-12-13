#include "Pin.h"
void setup() {
  led_int();
  button_int();
  disable_rc
  servo_int();
  Serial.begin(9600);
  led_off();
  bip(5,150);
}

void loop() {
test_button();
test_servo();
}
