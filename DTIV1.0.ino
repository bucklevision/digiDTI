//Trinket pins assignament:
#define RXDATA      3      // Pin 3, not used
#define TXDATA      4      // Pin 4, USB out
#define CLOCK       2      // DTI Clock Signal
#define DATA        0      // DTI Data Signal
#define LED         1      // LED Pin, for flashy fun
#define PACKETSIZE  23     // Size of a packet
#define BAUD        115200 // USB BAUD rate

#include <SoftwareSerial.h>
SoftwareSerial usbSerial(RXDATA, TXDATA);

int i;                                  //Counter
int32_t data, buff;                     //Storage of data

void setup()
{
  pinMode(1, OUTPUT);                   //PIN 1 IS LED
  pinMode(0, INPUT);                    //Pin 0 is an input
  pinMode(2, INPUT);                    //Pin 2 is an input
  usbSerial.begin(BAUD);                //Kick off serial connection at BAUD
  usbSerial.println("Digital DTI\n\n"); //Hello World
  delay(5000);                          //Time to think
}

void loop()
{
  while (digitalRead(CLOCK))
  {
  }
  digitalWrite(LED,HIGH);
  dataGrab();             //This was notably more complex - could be inline
  digitalWrite(LED,LOW);
}


void dataGrab()
{
  data = 0;         //Clear any old data
  i = PACKETSIZE;   //Initialise counter
  while (i)
  {
    while (!digitalRead(CLOCK)) //Look for postive going slope
    {
    }
    buff = digitalRead(DATA);     //grab data
    if (i == 3 && buff == 1)      //Handle Negatives
    {
      data = -data;
    }
    buff = buff << (PACKETSIZE);//Take current bit and move it left
    data = buff | data;           //OR it with the existing data
    data = data >> 1;             //Move all data one step right
    i--;                          //Decrease Counter
    while (digitalRead(CLOCK))  //Look for negative going slope
    {
    }    
  }
  usbSerial.print(data);        //Spit data over USB
  usbSerial.print("\n");
}


