#include <ARMbot.h>

ARMbot Robot;

void setup()
{
	Serial.begin(9600);
  	Robot.disable_rc();
  	Robot.init();
  	Robot.begins();
}
void loop()
{
  	Robot.start();
}