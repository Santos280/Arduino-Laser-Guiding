
 #include<SoftwareSerial.h>
#include <Servo.h>
Servo m1;
Servo m2;                       // Create Servo object m1 and m2
SoftwareSerial BTserial(2,3);   // RX and TX;
int p1=0,p2=0,z=0;              // Initial position of servo 1 and 2

void setup() 
{
  boolean Status=false;          // Status of bluetooth
   pinMode(8,OUTPUT);            // for Laser
   pinMode(12,INPUT);            // for detecting status of bluetooth
   pinMode(13,OUTPUT);           // Display status of bluetooth
  BTserial.begin(9600);          // Initialise Serial communication via bluetooth
  m1.attach(6);                  // Attaches the servo on pin 9 to the servo object
  m2.attach(7);                  // Attaches the servo on pin 10 to the servo object
  while(!Status)
  {
    if(digitalRead(12)==HIGH)
      Status=true;
}
digitalWrite(13,HIGH);           // Indicates that bluetooth is connected
}
void loop()
{ 
  if(BTserial.available()>0)
   z=BTserial.read();
{ 
                                 // For seervo m1
  while(z=='1')
  {
   p1=increment(p1);            // User defined 
   m1.write(p1);
   delay(20);             
    break;
  }
   while(z=='2')
   {
   p1=decrement(p1);         // User defined
   m1.write(p1);
   delay(20);    // for stability
    break;
   }
                            // Simialrly for servo m2
  while(z=='3')
  { 
   p2=increment(p2);
   m2.write(p2);
   delay(20);     //For stability
    break;
  }
   while(z=='4')
   {
   p2=decrement(p2);  
   m2.write(p2); 
   delay(20);       // For stability
    break;
   }
   if (z=='0')    // Make servo m1 to return to its initial position
   {
    m1.write(90);
    delay(20);
   }
   if (z=='9')    // Make servo m2 return to its initial position
   {
    m2.write(90);
    delay(20);
   }
   if (z=='a')           // To turn laser on
    digitalWrite(8,HIGH); 
   if (z=='b')          // To turn laser off
  digitalWrite(8,LOW); 
  }
}
int increment(int pos)
{
    pos=pos+5;                   // Increment the angle by 5 degree when button is pressed
    if (pos>180)                // The max anlgle of servo is 180 degrees
    pos=180;
     return(pos);
}
int decrement(int pos)
{
    pos=pos-5;                 // Decrement the angle by 5 degrees when the button is pressed
    if(pos<0)                 // The minimum angle of servo is 0 degrees
    pos=0;  
    return(pos);                 
}
