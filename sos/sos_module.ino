/* This sketch is used for complete SOS module comprising of:
 *  DHT11 : Sends Temperature (degree Celsius) and Humidity (%) values
 *  Bluetooth module HC-05 : For transmitting sensor readings to MapMInt4ME
 *  MQ2 : Gas and Smoke Sensor, sending the smoke content in ppm
 * The sensors are connected to Arduino Uno via WEATHERSHIELD developed by SYSLAB. 
 * Added in August 2017 for SOS input support.
 */
 
#include <dht.h>
dht DHT;

/************************Hardware Related Macros************************************/
const int MQ_PIN=A0;                                //defines which analog input channel you are going to use
int RL_VALUE=5;                                     //defines the load resistance on the board, in kilo ohms
/***********************Software Related Macros************************************/
int READ_SAMPLE_TIMES=5;                        //defines how many samples you are going to take in normal operation
int READ_SAMPLE_INTERVAL=50;                   //defines the times interval(in miliseconds) between each samples in 
                                                    //normal operation
 
/**********************Application Related Macros**********************************/
#define           GAS_SMOKE           2    
#define           dht_pin             6
 
/*****************************Globals***********************************************/
float           SmokeCurve[3] ={2.3,0.54,-0.447};    //two points are taken from the curve. 
                                                    //with these two points, a line is formed which is "approximately equivalent" 
                                                    //to the original curve.
                                                    //data format:{ x, y, slope}; point1: (lg200, 0.54), point2: (lg10000,  -0.22)                                                     
float           Ro           =  3.63;               //Initialize Ro as per calibration output

void setup() {
Serial.begin(9600); // Default communication rate of the Bluetooth module
}

void loop() {
  
long PPM_Smoke = 0;
int chk = DHT.read11(dht_pin);
PPM_Smoke = MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_SMOKE);
Serial.print(DHT.humidity);
Serial.print(" % :");
Serial.print(DHT.temperature);
Serial.write(0xC2);
Serial.write(0xB0);
Serial.print("C :");
Serial.print(PPM_Smoke);
Serial.println("ppm");
delay(5000);
}


/****************** MQResistanceCalculation ****************************************
Input:   raw_adc - raw value read from adc, which represents the voltage
Output:  the calculated sensor resistance
Remarks: The sensor and the load resistor forms a voltage divider. Given the voltage
         across the load resistor and its resistance, the resistance of the sensor
         could be derived.
************************************************************************************/ 
float MQResistanceCalculation(int raw_adc)
{
  return ( ((float)RL_VALUE*(1023-raw_adc)/raw_adc));
}
 
/*****************************  MQRead *********************************************
Input:   mq_pin - analog channel
Output:  Rs of the sensor
Remarks: This function use MQResistanceCalculation to caculate the sensor resistenc (Rs).
         The Rs changes as the sensor is in the different concentration of the target
         gas. The sample times and the time interval between samples could be configured
         by changing the definition of the macros.
************************************************************************************/ 
float MQRead(int mq_pin)
{
  int i;
  float rs=0;
 
  for (i=0;i<READ_SAMPLE_TIMES;i++) {
    rs += MQResistanceCalculation(analogRead(mq_pin));
    delay(READ_SAMPLE_INTERVAL);
  }
 
  rs = rs/READ_SAMPLE_TIMES;
  return rs;  
}
 
/*****************************  MQGetGasPercentage **********************************
Input:   rs_ro_ratio - Rs divided by Ro
         gas_id      - target gas type
Output:  ppm of the target gas
Remarks: This function passes different curves to the MQGetPercentage function which 
         calculates the ppm (parts per million) of the target gas.
************************************************************************************/ 
long MQGetGasPercentage(float rs_ro_ratio, int gas_id)
{
 if ( gas_id == GAS_SMOKE ) {
     return MQGetPercentage(rs_ro_ratio,SmokeCurve);
  }    
 
  return 0;
}
 
/*****************************  MQGetPercentage **********************************
Input:   rs_ro_ratio - Rs divided by Ro
         pcurve      - pointer to the curve of the target gas
Output:  ppm of the target gas
Remarks: By using the slope and a point of the line. The x(logarithmic value of ppm) 
         of the line could be derived if y(rs_ro_ratio) is provided. As it is a 
         logarithmic coordinate, power of 10 is used to convert the result to non-logarithmic 
         value.
************************************************************************************/ 
long  MQGetPercentage(float rs_ro_ratio, float *pcurve)
{
  return (pow(10,( ((log(rs_ro_ratio)-pcurve[1])/pcurve[2]) + pcurve[0])));
}
