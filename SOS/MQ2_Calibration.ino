/* This sketch is used for calibrating the MQ2 Gas sensor */


const int MQ_PIN=A0;                                //defines analog input channel which will be used
int RL_VALUE=5;                                     //defines the load resistance on the board, in kilo ohms
float RO_CLEAN_AIR_FACTOR=9.83;                     //RO_CLEAR_AIR_FACTOR=(Sensor resistance in clean air)/RO,
int CALIBRATION_SAMPLE_TIMES=50;                    //defines number of samples taken in the calibration phase
int CALIBRATION_SAMPLE_INTERVAL=500;                //defines the time interval(in miliseconds) between consecutive sample reading
  
void setup() {
Serial.begin(9600);
  
Serial.print("Calibrating...");
  
float  Ro = MQCalibration(MQ_PIN);                         //Calibrating the sensor. Please make sure that the sensor is in clean air while calibrating         
 
  Serial.print("Calibration Done!");                               
  Serial.print("Ro = ");
  Serial.print(Ro);
  Serial.print("kohm");
  
  delay(3000);
}

void loop() {

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
 
/***************************** MQCalibration ****************************************
Input:   mq_pin - analog channel
Output:  Ro of the sensor
Remarks: This function assumes that the sensor is in clean air. It use  
         MQResistanceCalculation to calculates the sensor resistance in clean air 
         and then divides it with RO_CLEAN_AIR_FACTOR. RO_CLEAN_AIR_FACTOR is about 
         10, which differs slightly between different sensors.
************************************************************************************/ 

float MQCalibration(int mq_pin)
{
  int i;
  float val=0;

  for (i=0;i<CALIBRATION_SAMPLE_TIMES;i++) {            //For multiple samples
    val += MQResistanceCalculation(analogRead(mq_pin));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  val = val/CALIBRATION_SAMPLE_TIMES;                   //calculate the average value
  val = val/RO_CLEAN_AIR_FACTOR;                        //divided by RO_CLEAN_AIR_FACTOR yields the Ro                                        
  return val;                                           //according to the chart in the MQ2datasheet 

}
