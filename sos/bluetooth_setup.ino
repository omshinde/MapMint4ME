/* This sketch is used for setting up Bluetooth module- HC 05.
 * The Bluetooth module is connected to the Arduino Uno via 
 * WEATHERSHIELD developed by SYSLAB.
 * Added in August 2017 for HC-05 setup.
 */

#include <SoftwareSerial.h>

int bt_Tx = 10;
int bt_Rx = 11;
SoftwareSerial BTSerial(bt_Tx, bt_Rx); // TX of HC-05 to D10  | RX of HC-05 to D11

void setup()
{
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  BTSerial.begin(38400);// HC-05 default speed in AT command mode
}

void loop()
{

  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (BTSerial.available())
  { 
    Serial.write(BTSerial.read());
  }

  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available())
  { 
    BTSerial.write(Serial.read());
  }
}  

