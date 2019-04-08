/* This sketch is used for individual testing of DHT 11 sensor. 
It is used for getting temperature and humidity readings of the surrounding. */

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
  Serial.print("Current Humidity value is ");
  Serial.println(DHT.humidity);
  delay(1000);
}

