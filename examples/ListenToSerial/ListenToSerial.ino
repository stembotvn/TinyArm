#include <ARMbot.h>

ARMbot Robot;

const int MAX_BUF      = 64;
char buffer[MAX_BUF];
int sofar;
////////////////////////////////////////////////////////////////////////////////////////////
void processCommand() {
  int Base;
  int Shoulder;
  int Elbow;
  int Grip;
  int speed;
  if( !strncmp(buffer,"moveArm",7))
  {
    char *ptr=buffer;
    while(ptr && ptr<buffer+sofar)
    {
      ptr=strchr(ptr,' ')+1;
      switch(*ptr)
      {
        case 'B': Base=atof(ptr+1); break;
        case 'S': Shoulder=atof(ptr+1); break;
        case 'E': Elbow=atof(ptr+1); break;
        case 'G': Grip=atof(ptr+1); break;
        case 'V': speed=atof(ptr+1); break;
        default: ptr=0; break;
      }
    }
    Robot.moveArm(Base, Shoulder, Elbow, Grip, speed);
  }
  /////////////////// set Base //////////////////////////////
  else if( !strncmp(buffer,"setBase",7))
  {
    char *ptr=buffer;
    while(ptr && ptr<buffer+sofar)
    {
      ptr=strchr(ptr,' ')+1;
      switch(*ptr)
      {
        case 'B': Base=atof(ptr+1); break;
        case 'V': speed=atof(ptr+1); break;
        default: ptr=0; break;
      }
    }
    Robot.setBase(Base, speed);
  }
  /////////////////// set Shoulder ///////////////////////////
  else if( !strncmp(buffer,"setShoulder",11))
  {
    char *ptr=buffer;
    while(ptr && ptr<buffer+sofar)
    {
      ptr=strchr(ptr,' ')+1;
      switch(*ptr)
      {
        case 'S': Shoulder=atof(ptr+1); break;
        case 'V': speed=atof(ptr+1); break;
        default: ptr=0; break;
      }
    }
    Robot.setShoulder(Shoulder, speed);
  }
  ///////////////// set Elbow ///////////////////////////////
  else if( !strncmp(buffer,"setElbow",8))
  {
    char *ptr=buffer;
    while(ptr && ptr<buffer+sofar)
    {
      ptr=strchr(ptr,' ')+1;
      switch(*ptr)
      {
        case 'E': Elbow=atof(ptr+1); break;
        case 'V': speed=atof(ptr+1); break;
        default: ptr=0; break;
      }
    }
    Robot.setElbow(Elbow, speed);
  }
  //////////////// set Grip ////////////////////////////
  else if( !strncmp(buffer,"setGrip",7))
  {
    char *ptr=buffer;
    while(ptr && ptr<buffer+sofar)
    {
      ptr=strchr(ptr,' ')+1;
      switch(*ptr)
      {
        case 'G': Grip=atof(ptr+1); break;
        case 'V': speed=atof(ptr+1); break;
        default: ptr=0; break;
      }
    }
    Robot.setGrip(Grip, speed);
  }
}
//////////////////////////////////////////////////////////////////////////////////
void listenToSerial()
{
  while(Serial.available() > 0)
  {
    buffer[sofar++]=Serial.read();
    if(buffer[sofar-1]==';') break;  // in case there are multiple instructions
  }
  // if we hit a semi-colon, assume end of instruction.
  if(sofar>0 && buffer[sofar-1]==';')
  {
    buffer[sofar]=0;
    // echo confirmation
    Serial.println(buffer);
    // do something with the command
    processCommand();
    // reset the buffer
    sofar=0;
    // echo completion
    Serial.print(F("> "));
  }
}
void setup()
{
  Serial.begin(9600);
  Robot.disable_rc();
  Robot.init();
  Robot.begin();
}
void loop()
{
  listenToSerial();
}
