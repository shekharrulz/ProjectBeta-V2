/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo and Micro support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example

 This example code is in the public domain.

 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
char analog[7];
int a,b,c,d,e,z=36,i,s1,s2,s3,s4,s5;
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  


  // set the data rate for the SoftwareSerial port
  mySerial.begin(115200);

}

void loop() { // run over and over

s1=analogRead(A0);
s2=analogRead(A1);
s3=analogRead(A2);
s4=analogRead(A3);
s5=analogRead(A4);

a= map(s1, 0, 1023, 0, 255);
b= map(s2, 0, 1023, 0, 255);
c= map(s3, 0, 1023, 0, 255);
d= map(s4, 0, 1023, 0, 255);
e= map(s5, 0, 1023, 0, 255);

  Serial.println(a);
   

  Serial.println(b);

  Serial.println(c);

  Serial.println(d);

  Serial.println(e);

    analog[0]='@';
    analog[1]=a;
    analog[2]=b;
    analog[3]=c;
    analog[4]=d;
    analog[5]=e;
    analog[6]='$';
    for(i=0;i<7;i++)
    {mySerial.write(analog[i]);
    
    }
delay(1000);
}

