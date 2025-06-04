package com.senior.project;

import android.Manifest;
import android.app.PendingIntent;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattDescriptor;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothProfile;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.telephony.SmsManager;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import androidx.core.app.ActivityCompat;
import android.graphics.Bitmap;
import android.graphics.Matrix;
import java.io.UnsupportedEncodingException;
import java.util.HashMap;
import java.util.List;
import java.util.UUID;
import android.widget.ImageView;

import static android.nfc.NfcAdapter.EXTRA_DATA;


public class BLEActivity extends FullscreenActivity{
    private static final int STATE_DISCONNECTED = 0;
    private static final int STATE_CONNECTING = 1;
    private static final int STATE_CONNECTED = 2;
    private byte[] pin;
    private TextView dataout, isconnected, accdataout,angletext;
    private static final int MY_PERMISSIONS_REQUEST_SEND_SMS = 1;
    private BluetoothGatt bluetoothGatt;
    private BluetoothGattCharacteristic characteristic;
    private int connectionState = STATE_DISCONNECTED;
    BluetoothGattCharacteristic mReadCharacteristic;
    BluetoothGattCharacteristic mReadCharacteristicAngle;
    private final static String TAG = BLEActivity.class.getSimpleName();
    private Button reconnect, getgyrodata, getangledata;
    public final static UUID UUID_GYRO_ACC_MEASUREMENT = UUID.fromString("340a1b80-cf4b-11e1-ac36-0002a5d5c51b");
    public final static UUID UUID_ANGLE_MEASUREMENT = UUID.fromString("01c50b60-e48c-11e2-a073-0002a5d5c51b");
    private ImageView arrow;
    public final static String ACTION_GATT_CONNECTED =
            "com.example.bluetooth.le.ACTION_GATT_CONNECTED";
    public final static String ACTION_GATT_DISCONNECTED =
            "com.example.bluetooth.le.ACTION_GATT_DISCONNECTED";
    public final static String ACTION_GATT_SERVICES_DISCOVERED =
            "com.example.bluetooth.le.ACTION_GATT_SERVICES_DISCOVERED";
    public final static String ACTION_DATA_AVAILABLE =
            "com.example.bluetooth.le.ACTION_DATA_AVAILABLE";
    public final static String EXTRA_DATA =
            "com.example.bluetooth.le.EXTRA_DATA";
    /**
     * Touch listener to use for in-layout UI controls to delay hiding the
     * system UI. This is to prevent the jarring behavior of controls going away
     * while interacting with activity UI.
     */
    private BluetoothDevice x;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        //assign layout
        setContentView(R.layout.blescreen);

        //setup textview's
        accdataout = findViewById(R.id.accdata);
        accdataout.setText("MAX ACC x: 0 y: 0 z: 0");
        dataout = findViewById(R.id.gyrodata);
        dataout.setText("MAX GYRO x: XX y: 0 z: 0");
        isconnected = findViewById(R.id.blestatus);
        isconnected.setText("NOT CONNECTED");
        angletext = findViewById(R.id.angletext);
        angletext.setText("NOT CONNECTED");

        //setup button's
        reconnect = (Button) findViewById(R.id.reconnect);
        getgyrodata = (Button) findViewById(R.id.getdatagyro);
        getangledata = (Button) findViewById(R.id.getangle);

        //get arrow image
        arrow = findViewById(R.id.arrow);


        //Bluetooth has a programed pin of 123456 on the board side code
        pin = "123456".getBytes();
        //get BLE device from previous activity
        x = getIntent().getExtras().getParcelable("btdevice");
        x.setPin(pin);
        //try connecting to BLE device
        bluetoothGatt = x.connectGatt(BLEActivity.this, false, gattCallback);


        //button to reconnect
        reconnect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //try connecting to BLE device
                bluetoothGatt = x.connectGatt(BLEActivity.this, false, gattCallback);

            }
        });
        //button to get gyro data
        getgyrodata.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //starts process of asking to board to send back the gyro data
                 if(bluetoothGatt.readCharacteristic(mReadCharacteristic) == false){
                     Log.w(TAG, "Failed to read characteristic");
                 }

            }
        });
        getangledata.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //starts process of asking board to send back angle data
                if(bluetoothGatt.readCharacteristic(mReadCharacteristicAngle) == false){
                    Log.w(TAG, "Failed to read characteristic");
                }
            }
        });

    }

    //bluetooth BLE callback runs functions when apporpiate
    private final BluetoothGattCallback gattCallback =
            new BluetoothGattCallback() {
                @Override
                public void onConnectionStateChange(BluetoothGatt gatt, int status,
                                                    int newState) {
                    String intentAction;
                    if (newState == BluetoothProfile.STATE_CONNECTED) {
                        //set variables to connected
                        intentAction = ACTION_GATT_CONNECTED;
                        connectionState = STATE_CONNECTED;
                        broadcastUpdate(intentAction);
                        isconnected.setText("GATT CONNECTED");
                        Log.i(TAG, "Connected to GATT server.");
                        Log.i(TAG, "Attempting to start service discovery:" +
                                bluetoothGatt.discoverServices());

                    } else if (newState == BluetoothProfile.STATE_DISCONNECTED) {
                        //set variables to disconnected
                        Log.w("BLE", "BLE DISCONNECTED" );
                        isconnected.setText("GATT DISCONNECTED");
                        intentAction = ACTION_GATT_DISCONNECTED;
                        connectionState = STATE_DISCONNECTED;
                        broadcastUpdate(intentAction);
                    }
                }

                @Override
                // New services discovered
                public void onServicesDiscovered(BluetoothGatt gatt, int status) {
                    Log.w(TAG, "onServicesDiscovered received: " );
                    List<BluetoothGattService> listservices = gatt.getServices();
                    UUID uuid;
                    for (BluetoothGattService gattService : listservices) {
                        HashMap<String, String> currentServiceData =
                                new HashMap<String, String>();
                        uuid = gattService.getUuid();

                        //prints out service ID
                        Log.d("uuids", "UUID1: " + uuid);
                        List<BluetoothGattCharacteristic> gattCharacteristics = gattService.getCharacteristics();

                        // Loops through available Characteristics.
                        for (BluetoothGattCharacteristic gattCharacteristic : gattCharacteristics) {
                            uuid = gattCharacteristic.getUuid();
                            characteristic = new BluetoothGattCharacteristic(uuid,BluetoothGattCharacteristic.PROPERTY_WRITE, BluetoothGattCharacteristic.PERMISSION_WRITE);
                            characteristic.addDescriptor(new BluetoothGattDescriptor(uuid, BluetoothGattDescriptor.PERMISSION_READ));
                            bluetoothGatt.setCharacteristicNotification(characteristic, enabled);
                            BluetoothGattDescriptor descriptor = characteristic.getDescriptor(uuid);
                            descriptor.setValue(BluetoothGattDescriptor.ENABLE_NOTIFICATION_VALUE);
                            bluetoothGatt.writeDescriptor(descriptor);
                            Log.d("uuids", "UUID2: " + uuid);

                        }
                    }


                    if (status == BluetoothGatt.GATT_SUCCESS) {
                        broadcastUpdate(ACTION_GATT_SERVICES_DISCOVERED);
                    } else {
                        Log.w(TAG, "onServicesDiscovered received: " + status);
                    }

                    //sets up characteristic for reading acc/gyro
                    mCustomService = bluetoothGatt.getService(UUID.fromString("02366e80-cf3a-11e1-9ab4-0002a5d5c51b"));
                    if(mCustomService == null){
                        Log.w(TAG, "Custom BLE Service not found");
                        return;
                    }
                    mReadCharacteristic = mCustomService.getCharacteristic(UUID.fromString("340a1b80-cf4b-11e1-ac36-0002a5d5c51b"));

                    //sets up characteristic for reading angle
                    mCustomServiceangle = bluetoothGatt.getService(UUID.fromString("42821a40-e477-11e2-82d0-0002a5d5c51b"));//service UUID
                    if(mCustomServiceangle == null){
                        Log.w(TAG, "Custom BLE Service not found");
                        return;
                    }
                    mReadCharacteristicAngle = mCustomServiceangle.getCharacteristic(UUID.fromString("01c50b60-e48c-11e2-a073-0002a5d5c51b"));//characteritic UUID

                }

                @Override
                // Result of a characteristic read operation
                public void onCharacteristicRead(BluetoothGatt gatt,
                                                 BluetoothGattCharacteristic characteristic,
                                                 int status) {
                    Log.d("char read","charread here");
                    if (status == BluetoothGatt.GATT_SUCCESS) {
                        broadcastUpdate(ACTION_DATA_AVAILABLE, characteristic);
                    }
                }

                @Override
                //call back for characteristic changed
                public void onCharacteristicChanged(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic) {
                    super.onCharacteristicChanged(gatt, characteristic);
                    byte[] messageBytes = characteristic.getValue();
                    String messageString = null;
                    Log.d("message","Received message: ");
                    try {
                        messageString = new String(messageBytes, "UTF-8");
                    } catch (UnsupportedEncodingException e) {
                        Log.e(TAG, "Unable to convert message bytes to string");
                    }
                    Log.d("message","Received message: " + messageString);
                }
            };
    private void broadcastUpdate(final String action) {
        final Intent intent = new Intent(action);
        sendBroadcast(intent);
    }

    private void broadcastUpdate(final String action,
                                 final BluetoothGattCharacteristic characteristic) {
        final Intent intent = new Intent(action);

        // This is special handling for the Heart Rate Measurement profile. Data
        // parsing is carried out as per profile specifications.
        Log.d("UUID","UUID:" + characteristic.getUuid());
        if (UUID_GYRO_ACC_MEASUREMENT.equals(characteristic.getUuid())) {

            int flag = characteristic.getProperties();
            Log.d("flag","flag: "+flag);

            float gyroscale = (float)4.375 * (2000/125)/1000;
            float accscale = (float) 0.061 * (16>>1) /1000;
            Log.d(TAG, String.format("acc scale:" +accscale + "   gyro scale:" + gyroscale));
            //read in data
            float maxGyrox = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_SINT16,0)*gyroscale;
            Log.d(TAG, String.format("Received X: "+maxGyrox));
            float maxGyroy = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_SINT16,2) *gyroscale;
            Log.d(TAG, String.format("Received Y: "+maxGyroy));
            float maxGyroz = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_SINT16,4)*gyroscale;
            Log.d(TAG, String.format("Received Z: "+maxGyroz));
            float maxAccx = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_SINT16,6) *accscale;
            Log.d(TAG, String.format("Received X: "+maxAccx));
            float maxAccy = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_SINT16,8)*accscale;
            Log.d(TAG, String.format("Received Y: "+maxAccy));
            float maxAccz = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_SINT16,10)*accscale;
            Log.d(TAG, String.format("Received Z: "+maxAccz));

            //show data on screen
            dataout.setText("MAX GYRO x: "+maxGyrox + "y: "+maxGyroy+" z:" +maxGyroz);
            accdataout.setText("MAX ACC x:" +maxAccx + "y: "+maxAccy+" z:" +maxAccz);

        }
        else if (UUID_ANGLE_MEASUREMENT.equals(characteristic.getUuid())) {

            int flag = characteristic.getProperties();
            Log.d("flag","flag: "+flag);
            int format = -1;
            if ((flag & 0x01) != 0) {
                format = BluetoothGattCharacteristic.FORMAT_UINT16;
                Log.d(TAG, "format UINT16.");
            } else {
                format = BluetoothGattCharacteristic.FORMAT_UINT8;
                Log.d(TAG, " format UINT8.");
            }
            //read in angle and rotate image & print out on logs
            float angle = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_SINT16,0);
            angletext.setText("Angle:" +angle);
            Log.d(TAG, String.format("ANGLE: "+angle));
            rotateImage(arrow, angle);

        }else {
            // For all other profiles, writes the data formatted in HEX.
            final byte[] data = characteristic.getValue();
            double heartRate = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_FLOAT,0);
            Log.d(TAG, String.format("Received: "+heartRate));
            dataout.setText("MAX GYRO x: "+heartRate + "y: 0 z: 0");

           /* heartRate = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_UINT16,2);
            Log.d(TAG, String.format("Received heart rate2: "+heartRate));
            heartRate = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_UINT16,4);
            Log.d(TAG, String.format("Received heart rate3: "+heartRate));
            */
            if (data != null && data.length > 0) {
                final StringBuilder stringBuilder = new StringBuilder(data.length);
                for(byte byteChar : data)
                    stringBuilder.append(String.format("%02X ", byteChar));
                intent.putExtra(EXTRA_DATA, new String(data) + "\n" +
                        stringBuilder.toString());
            }
        }
        sendBroadcast(intent);


    }
    private void rotateImage(ImageView imageView, float angle) {
        //code to rotate image on BLE screen
        imageView.setPivotX(imageView.getWidth() / 2);
        imageView.setPivotY(imageView.getHeight() / 2);
        imageView.setRotation(angle);
    }
}
