/* This sketch is used for seting up Bluetooth module- HC 05 */

#include <SoftwareSerial.h>

int bt_Tx = 10;
int bt_Rx = 11;
SoftwareSerial BTSerial(bt_Tx, bt_Rx); // TX of HC-05 to D10  | RX of HC-05 to D11

void setup()
{
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  BTSerial.begin(38400);  // HC-05 default speed in AT command more
}

void loop()
{

  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (BTSerial.available())
  { //Serial.println("Hi");
    Serial.write(BTSerial.read());
  }

  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available())
  { //BTSerial.println("Hi Bluetooth");
    BTSerial.write(Serial.read());
  }
}  
