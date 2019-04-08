## Setting up the Sensor Observation Service (SOS)

To access SOS data directly to the MapMint4ME, the sensors and the Bluetooth module need to be setup. 
The SOS module comprises of following components:

* [DHT11](https://github.com/omshinde/MapMint4ME/blob/gsoc-2017-camera/sos/Datasheets/DHT11%20Datasheet.pdf): Temperature and Humidity Sensor
* [MQ2](https://github.com/omshinde/MapMint4ME/blob/gsoc-2017-camera/sos/Datasheets/MQ2%20datasheet.pdf): Gas and Smoke Sensor
* [HC05](https://github.com/omshinde/MapMint4ME/blob/gsoc-2017-camera/sos/Datasheets/HC-05%20datasheet.pdf): Bluetooth module
* Weathershield - created by SYSLAB. I am thankful to them for their support and help, especially to Mr. Tanmay Jambhekar.
* [Arduino UNO](https://github.com/omshinde/MapMint4ME/blob/gsoc-2017-camera/sos/Datasheets/ARDUINOUNO328.pdf): Arduino UNO microcontroller for communicating between sensors and Bluetooth module

A brief overview of AT commands for HC-05 Bluetooth module can be obtained [here](https://github.com/omshinde/MapMint4ME/blob/gsoc-2017-camera/sos/Datasheets/HC-05%20AT%20Commands.pdf).

The process of Sensor data transmission to the Android application comprises of following steps:
1. Sensors sense data from the environment
2. Microcontroller processes the data and sends it to the Bluetooth module for transmission
3. Bluetooth module transmits the data, MapMint4ME receives this data while being paired with the Bluetooth module
4. MapMint4ME displays the data and then pushes it to the database

This data in the database can be exported to the MapMint server for further visualization and analysis.

#### Tasks to be performed
* Setup Bluetooth module
* **Test DHT11** and **calibrate MQ2** individually
* Combine both modules to work as **Sensor Observation Service**

### Note: The codes presented here are for Arduino UNO. You will require Arduino IDE for programming Arduino.
The Arduino IDE can be downloaded from the official Arduino [website](https://www.arduino.cc/en/Main/Software).

#### Task 1 - Setup Bluetooth module
The Bluetooth modules come with a default name of **HC-05** and default passkey of **1234** or **0000**. But, for communicating with it,
it is better to change these credentials. For this, we need to enter command mode of HC-05.
The connections are as follows:
HC-05         -          Arduino |
 Vcc          -             5V   |
 GND          -             GND  |
 Tx           -             D10  |
 Rx           -             D11  |
 
 The Tx and Rx pins connection can be different too. The only condition is that according to the connections, the [code](https://github.com/omshinde/MapMint4ME/blob/gsoc-2017-camera/sos/bluetooth_setup.ino#L9) needs to be modified.
 Connect all the pins except Vcc. Run the [bluetooth_setup.ino](https://github.com/omshinde/MapMint4ME/blob/gsoc-2017-camera/sos/bluetooth_setup.ino) with Arduino connected through 
 the debug cable. Now, connect Vcc on HC-05 to Arduino's 5V pressing the button switch. This is necessary for entering Command mode.
 
 ![HC-05](https://github.com/omshinde/MapMint4ME/blob/gsoc-2017-camera/sos/images/HC-05.jpg)
 The key button is highlighted in above image.
 Open the serial monitor and Enter **AT**. If you see **OK** as a response then you are good to move ahead. 
 Once you receive **OK** as output, Enter the following commands:
 
 * AT+NAME=BmateOCU
 * AT+PSWD=xxxx (xxxx= Anything can be entered as per wish)
 This will change the pass key and device name of HC-05. Check it pairing it with your cell phone. While checking the device need
 not be in command mode.
 
 #### Task 2 - DHT11 Testing
 DHT11 can be directly tested by mounting it on WEATHERSHIELD. The PCB design of WEATHERSHIELD will be shown below.
 Shields usually save your modules from damage. Upload [dht11_test.ino](https://github.com/omshinde/MapMint4ME/blob/gsoc-2017-camera/sos/dht11_test.ino) on Arduino.
 Open the serial monitor to see the Temperature and Humidity readings. 
 
 #### Task 3 - MQ2 calibration
 Similar to DHT11, MQ2 can also be mounted on WEATHERSHIELD for calibration. Upload [MQ2_Calibration.ino](https://github.com/omshinde/MapMint4ME/blob/gsoc-2017-camera/sos/MQ2_Calibration.ino) on Arduino.
 Open the serial monitor to obtain the value of R0 in KOhms. Note this value.
 
 Before moving to next part of combining all these modules, let's have a look at the layout of WEATHERSHIELD.
 ![Weathershield layout](https://github.com/omshinde/MapMint4ME/blob/gsoc-2017-camera/sos/images/weathershield_layout.png)
 
 The sensors and the Bluetooth module can be directly mounted on the shield.
 
 #### Task 4 - Combine all the modules together as SOS
 After connecting all the components on the WEATHERSHIELD, open [sos_module.ino](https://github.com/omshinde/MapMint4ME/blob/gsoc-2017-camera/sos/sos_module.ino).
 Now, change the value of [R0](https://github.com/omshinde/MapMint4ME/blob/gsoc-2017-camera/sos/sos_module.ino#L29) as obtained while calibrating the MQ2 sensor.
 Upload the [sos_module.ino](https://github.com/omshinde/MapMint4ME/blob/gsoc-2017-camera/sos/sos_module.ino) on Arduino and open the serial monitor to see the readings transmitted by sensors via Bluetooth module.
 
 The readings will be transmitted to the MapMint4ME and could be stored in the **tables**.
 
