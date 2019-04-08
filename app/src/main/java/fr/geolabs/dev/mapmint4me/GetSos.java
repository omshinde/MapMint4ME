/**************************************************************
 * This class listens sensor data readings transmitted by
 * the SOS (Bluetooth Module, Temperature and Humidity sensor,
 * and Smoke sensor. Then displays the data in form of a string.
 * Finally, stores it in the database.
 * Added in August 2017 for SOS input support
 **************************************************************/

package fr.geolabs.dev.mapmint4me;

import android.*;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Handler;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.InvocationTargetException;
import java.util.Set;
import java.util.UUID;

/***************************************************************
 * This function searches for all the available Bluetooth enabled
 * devices nearby. After that selects the BmateOCU, which is the
 * Bluetooth module (HC-05). Receives information from the bluetooth
 * module and sends it for publishing.
 * @output dataObtained
 ******************************************************************/
public class GetSos extends Activity {
    BluetoothAdapter mBluetoothAdapter;
    BluetoothSocket mBluetoothSocket;
    BluetoothDevice mBluetoothDevice;
    InputStream mInputStream;
    Thread workerThread;
    byte[] mmBuffer;
    int readBufferPosition;
    StringBuffer output;
    int counter;
    volatile boolean stopWorker;
    String dataObtained;

    public String getSos(String id) throws IOException {

        findBluetooth();
        dataObtained = openBluetooth();
        try {
            closeBluetooth();
        } catch (IOException ex) {
            Toast.makeText(getBaseContext(), "Closing Bluetooth Failed", Toast.LENGTH_SHORT).show();
        }
        return dataObtained;
    }

    //Searching for available Bluetooth enabled devices nearby
    void findBluetooth() {
        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if (mBluetoothAdapter == null) {
            System.out.println("Not Available");
        }

        if (!mBluetoothAdapter.isEnabled()) {
            Intent enableBluetooth = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            mBluetoothAdapter.enable();
        }

        Set<BluetoothDevice> pairedDevices = mBluetoothAdapter.getBondedDevices();
        if (pairedDevices.size() > 0) {
            for (BluetoothDevice device : pairedDevices) {
                if (device.getName().equals("BmateOCU")) {
                    mBluetoothDevice = device;
                    break;
                }
            }
        }
        System.out.println("Bluetooth device found");
    }

    String openBluetooth() throws IOException {
        UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
        BluetoothSocket tmp = null;
        try {
            tmp = mBluetoothDevice.createRfcommSocketToServiceRecord(uuid);
        } catch (IOException ex) {
        }
        mBluetoothSocket = tmp;
        run();
        String data = startListeningData();
        return data;
    }

    public void run() {
        mBluetoothAdapter.cancelDiscovery();

        try {
            //Connecting to Bluetooth Socket
            mBluetoothSocket.connect();
        } catch (IOException ex) {
            try {
                System.out.println("Trying Fallback");
                mBluetoothSocket =(BluetoothSocket) mBluetoothDevice.getClass().getMethod("createRfcommSocket", new Class[] {int.class}).invoke(mBluetoothDevice,1);
                mBluetoothSocket.connect();
            } catch (Exception e) {
            }
        }
        return;
    }

    public String startListeningData() throws IOException {
        final Handler handler = new Handler();
        //final BluetoothSocket mBluetoothSocket;
        final InputStream mInputStream;
        byte[] mmBuffer;
        String output;
        output = null;
        final byte delimiter = 10;

        InputStream tmpIn = null;

        try {
            tmpIn = mBluetoothSocket.getInputStream();
        } catch (IOException e) {
        }
        mInputStream = tmpIn;
        mmBuffer = new byte[1024];
        while (true) {
            int bytesAvailable;
            bytesAvailable = mInputStream.read(mmBuffer);
            if (bytesAvailable > 0) {
                byte[] packetBytes = new byte[bytesAvailable];
                mInputStream.read(packetBytes);
                //byte[] packetBytes = mInputStream.read(mmBuffer);
                for (int i = 0; i < bytesAvailable; i++) {
                    byte b = packetBytes[i];
                    if (b == delimiter) {
                        byte[] encodedBytes = new byte[readBufferPosition];
                        System.arraycopy(mmBuffer, 0, encodedBytes, 0, encodedBytes.length);
                        final String data = new String(encodedBytes, "US-ASCII");
                        readBufferPosition = 0;
                        output = data;
                    } else {
                        mmBuffer[readBufferPosition++] = b;
                    }
                }
            }
            return output;
        }

    }

    void closeBluetooth() throws IOException {
        mBluetoothAdapter.disable();
        mBluetoothSocket.close();
        System.out.println("Socket Closed");
    }
}