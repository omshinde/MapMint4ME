## Examples of audio/video and SOS input support 

This section comprises of following parts:
* Setup tables in MapMint local instance 
* Importing data to the MapMint4ME from MapMint local instance
* Editing tables in the MapMint4ME for audio/video and SOS input data

### Setup tables in MapMint local instance

Before moving ahead, it would be neccesary that **MapMint is installed properly** and you are able to access **Dashboard** module of MapMint web interface. Please visit **[Quick Check on installation](https://github.com/omshinde/MapMint4ME/tree/gsoc-2017-camera#quick-check-on-installation)** to confirm that you are able to access MapMint Dashboard. Once it is confirmed, you can proceed further with below mentioned steps.

The next step requires to setup the **Tables** module of the MapMint web interface. Please refer to the following link which explains about setting up **Tables** module in MapMint. 
It explains in a step-by-step manner, the procedure to setup tables module.
[Successful publication of tables using Tables module in MapMint](https://github.com/mapmint/mapmint/issues/9)

Following the procedure mentioned in the above link for publishing tables using Tables module, I am creating following two tables for this example:

1. **test_table** by the title **Test_video**. The View name is Test Video View

![Test Video view](https://github.com/omshinde/MapMint4ME/blob/gsoc-2017-camera/examples/images/example_test_video.png)

It contains the following columns:
* Id  - integer 
* Name  - variable character(50)
* Description  -  text
* Upload  -  bytea (for binary files)
* Uid  -  integer

2. **sos_test_table** by the title **Test_SOS**. The View name is Test SOS View

![Test SOS view](https://github.com/omshinde/MapMint4ME/blob/gsoc-2017-camera/examples/images/example_test_sos.png)

It contains the following columns:
* Id  -  integer
* Name  -  variable character(50) 
* Description  -  text
* Sos  -  text
* Uid  -  integer

### Importing data to the MapMint4ME from the local instance

For this also, please refer the following link explaining the process to import data from the localinstance to the MapMint4ME.
[Using MapMint4ME for adding and editing tables](https://github.com/mapmint/mapmint/issues/10)

In the above link, I was using the emulator of Android Studio. But, in this section, I will post images taken from testing with real device.

After installing and runnig MapMint4ME, please click on *Import* icon. After clicking on the icon, you will see a screen like in the following image.

<p align="center">
<img src="https://github.com/omshinde/MapMint4ME/blob/gsoc-2017-camera/examples/images/add_server.png" width="280" height="400">
</p>

It is mentioning that there is no MapMint server registered yet. So Let's register it. Click on the icon for **Add a Server**, and you will see the following screen.

<p align="center">
<img src="https://github.com/omshinde/MapMint4ME/blob/gsoc-2017-camera/examples/images/server_details.png" width="280" height="400">
</p>

Click on the Add Server icon. Now, you will something like this screen.

<p align="center">
<img src="https://github.com/omshinde/MapMint4ME/blob/gsoc-2017-camera/examples/images/server_added.png" width="280" height="400">
</p>

Now, click on the **import** icon at the side. the navigation bar will start moving till 100% and you will see a screen like the below image.

<p align="center">
<img src="https://github.com/omshinde/MapMint4ME/blob/gsoc-2017-camera/examples/images/import_done.png" width="280" height="400">
</p>

Now, from the **View** tab you will see the tables imported from the MapMint.


<p align="center">
<img src="https://github.com/omshinde/MapMint4ME/blob/gsoc-2017-camera/examples/images/imported_tables.png" width="280" height="400">
</p>

Now, we can fianlly move towards seeing audio/video and SOS input data loaded into the tables.

### Audio/ Video recordings loading into the tables
In the **Edit** tab, you will be getting folowing four options:
* Select an existing photo
* Take a picture
* Select an existing video
* Record a video

It will be similar to the below image.

<p align="center">
<img src="https://github.com/omshinde/MapMint4ME/blob/gsoc-2017-camera/examples/images/options.png" width="280" height="400">
</p>

For video recording fucntion,I can only choose **Test Video View** because only it contains a variable to store binary values.
Out of these options, **Selecting an existing video** and **Record a video**, options are added in GSoC 2017. On clicking on any of these options, you will be able to perform that corresponding function.
On clicking **ADD** icon, you will see that the value gets incremented in the **Test Video View**.

<p align="center">
<img src="https://github.com/omshinde/MapMint4ME/blob/gsoc-2017-camera/examples/images/video_in_table.png" width="280" height="400">
</p>

### SOS data loading into the table
#### NOTE: Before loading SOS data into the table, make sure that your SOS module is setup. Please refer [Setting up SOS module](https://github.com/omshinde/MapMint4ME/tree/gsoc-2017-camera/sos#setting-up-the-sensor-observation-service-sos) before moving forward.

Similar to the video recording function, you will be seeing following options for importing SOS.
* Import a reading: Take readings from SOS
* Directly entering text into the Text field

<p align="center">
<img src="https://github.com/omshinde/MapMint4ME/blob/gsoc-2017-camera/examples/images/options_sos.png" width="280" height="400">
</p>

On clicking the option for **Take readings from SOS**
You will get to see the following output. The readings displayed are in the following format **Humidity(%):Temperature(Deg Celsius):Smoke content(ppm)**
The results after adding the files will be like in following figure.

<p align="center">
<img src="https://github.com/omshinde/MapMint4ME/blob/gsoc-2017-camera/examples/images/readings_in_textbox.png" width="280" height="400">
</p>

<p align="center">
<img src="https://github.com/omshinde/MapMint4ME/blob/gsoc-2017-camera/examples/images/readings_in_table.png" width="280" height="400">
</p>

As we can see, the readings obtained from the SOS module is stored in the Tables.

The code can be seen at the [link](https://github.com/omshinde/MapMint4ME/tree/gsoc-2017-camera).
