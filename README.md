# MapMint4ME

MapMint4ME is an Android application to record your data on the field. MapMint4ME is an Android application for MapMint
web-mapping services. MapMint4ME gives the users capability to store data without using the internet locally. When the user returns 
back to a place with network connectivity, the recorded data can be uploaded back to the server. After GSoC 2017, it also has the capability to store audio/video recorded files and access data obtained from SOS directly in the MapMint4ME.

The link to the project wiki: [wiki](https://wiki.osgeo.org/wiki/GSoC_17:_Add_Audio,_Video_and_SOS_input_support_in_MapMint4ME).

#### Quick check on installation

Prior to start working with MapMint4ME, it is important that MapMint is installed on your local system. MapMint can be installed by following the procedure given on the official [MapMint website](http://mapmint.com/) and [User guide](http://mapmint.github.io/userguide-fr/introduction/introduction.html). In case of any errors, please refer to the issue page of [mapmint/ansible-roles](https://github.com/mapmint/ansible-roles/issues).

Now, for working on a local instance of MapMint and importing MapMint data to MapMint4ME, you need to connect your cell-phone and local system to the same network. The local instance of MapMint can be accessed by following the link [http://localhost/ui/Dashboard_bs](http://localhost/ui/Dashboard_bs). But, it can also be accessed by replacing **localhost** with your ip address. So, for suppose if IP of my system is **10.13.32.xx**, then I can access my local MapMint instance by following [http://10.13.32.xx/ui/Dashboard_bs](http://10.13.32.xx/ui/Dashboard_bs). This is really very helpful while working with emulated devices. If you are running MapMint4ME on an emulated device then you will require a localhost alias IP (10.0.2.2), because the emulator will itself be hosted on **localhost** of the development machine. Refer to this [link](https://stackoverflow.com/questions/1720346/how-to-get-the-android-emulators-ip-address) for getting more insight.

#### Note: These IP settings are changed in home/src/mapmint/mapmint-services/main.cfg which is the main configuration file of MapMint

Once you have set up your local instance, you could be seeing something similar to the below image after accessing your local instance: [http://10.13.32.xx/ui/Dashboard_bs](http://10.13.32.xx/ui/Dashboard_bs).

![Dashboard](https://github.com/omshinde/MapMint4ME/blob/gsoc-2017-camera/examples/images/main_readme_dashboard.png)
