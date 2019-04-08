/* This sketch is used for individual testing of DHT 11 sensor. 
 * It is used for getting temperature and humidity readings of the surrounding. 
 * DHT11 is directly connected to Arduino Uno using the WEATHERSHIELD developed by SYSLAB.
 * Added in August 2017 for testing of DHT 11 sensor.
 */

#include <dht.h> //DHT package required for Temperature and Humidity sensor

dht DHT;

#define DHT11_PIN 6

void setup(){  
  Serial.begin(9600);
}

void loop()
{
  int check = DHT.read11(DHT11_PIN);
  Serial.print("Current Temperature is ");
  Serial.println(DHT.temperature);
  Serial.write(0xC2);
  Serial.write(0xB0);
  Serial.print("C :");
  Serial.print("Current Humidity value is ");
  Serial.println(DHT.humidity);
  Serial.print(" % :");
  delay(1000);
}

