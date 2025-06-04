//fullscreenactivity
package com.senior.project;

import android.Manifest;
import android.annotation.SuppressLint;

import androidx.annotation.NonNull;
import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import android.app.AlertDialog;
import android.app.LauncherActivity;
import android.app.ListActivity;
import android.app.PendingIntent;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattDescriptor;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothProfile;
import android.bluetooth.BluetoothSocket;
import android.bluetooth.le.BluetoothLeScanner;
import android.bluetooth.le.ScanCallback;
import android.bluetooth.le.ScanResult;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.ActivityInfo;
import android.content.pm.PackageManager;
import android.graphics.Color;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.os.SystemClock;
import android.preference.PreferenceManager;
import android.telephony.SmsManager;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.UUID;

/**
 * An example full-screen activity that shows and hides the system UI (i.e.
 * status bar and navigation/system bar) with user interaction.
 */
public class FullscreenActivity extends AppCompatActivity  {
    boolean enabled  = true;
    private Button search;
    private Button stopsearching;
    private ListView listView;
    private Button BLEconnect ;
    ListView simpleList;
    private BluetoothDevice x;
    Button sendText;
    BluetoothGattService mCustomService;
    BluetoothGattService mCustomServiceangle;
    private BluetoothAdapter mBTAdapter;
    private BluetoothLeScanner btScanner;
    ArrayList<BluetoothDevice> resultsble ;
    ArrayList<String> results;
    private static ArrayAdapter<String> arrayAdapter ;
    private static final int SEND_SMS_MY_PERMS = 1;
    private static final int BLUETOOTH_MY_PERMS = 2;
    private static final int BLUETOOTH_ADMIN_MY_PERMS = 3;
    private static final int ACCESS_FINE_MY_PERMS = 5;
    private static final int ACCESS_COARSE_LOCATION_MY_PERMS = 6;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_fullscreen);

        //get button and listview
        search = (Button) findViewById(R.id.search);
        stopsearching = (Button) findViewById(R.id.connect);
        listView = (ListView) findViewById(R.id.listview);
        sendText = findViewById(R.id.buttonsendtextscreen);
        BLEconnect = findViewById(R.id.blestart);

        //check permissions and ask user to agree if not already have agreed
        checkPermiss();

        //start BLE search of device
        BLEconnect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent discoverableIntent = new
                        Intent(BluetoothAdapter.ACTION_REQUEST_DISCOVERABLE);
                discoverableIntent.putExtra(BluetoothAdapter.EXTRA_DISCOVERABLE_DURATION, 300);//searchings for 300 seconds
                startActivity(discoverableIntent);
                btScanner.startScan(leScanCallback);
            }
        });

        //start new screen for
        sendText.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //   close();
                Toast.makeText(getApplicationContext(), "Pressed", Toast.LENGTH_LONG).show();//display the text of button1
                Intent intent = new Intent(FullscreenActivity.this, SendTextActivity.class);
               startActivity(intent);

            }
        });



        //setup BLE adapter
        mBTAdapter = BluetoothAdapter.getDefaultAdapter();
        btScanner = mBTAdapter.getBluetoothLeScanner();
        resultsble = new ArrayList<>();
        //list to hold strings of strings of BLE device names
        results = new ArrayList<String>();
        //how to show on screen
        arrayAdapter = new ArrayAdapter(this, android.R.layout.simple_list_item_1, results);
        listView.setAdapter(arrayAdapter);
        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> a, View v, int position,
                                    long id) {
                //get BLE device the user clicked on
                x = resultsble.get(position);
                Intent intent = new Intent(FullscreenActivity.this, BLEActivity.class);
                //send BLE device the user intends to connect to
                intent.putExtra("btdevice", x);
                //start BLEActivity
                startActivity(intent);
            }
        });

        search.setOnClickListener(new View.OnClickListener() {


            @Override
            public void onClick(View arg0) {
                //update list
                arrayAdapter.notifyDataSetChanged();
            }
        });

        //stop searching
        stopsearching.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View arg0) {
                btScanner.flushPendingScanResults(leScanCallback);
                btScanner.stopScan(leScanCallback);
                Log.d("CONN", "stop scanning");

            }
        });

    }

        //callback for new BLE device found while searching
       private ScanCallback leScanCallback = new ScanCallback() {
     //   View vi = convertView;
      //  MyAdapter.ViewHolder holder;
        @Override
        public void onScanResult(int callbackType, ScanResult result) {
            simpleList = (ListView)findViewById(R.id.listview);
            BluetoothDevice device  = result.getDevice();
            // add could be a boolean but boolean's take up a lot of memory compared to int's
            int add = 0;
            //check to see if new BLE device is already on list
            for(int i = 0; i < resultsble.size();i++) {
                if (device.getAddress().equals(resultsble.get(i).getAddress()))
                    add = 5;
            }
            //make sure it has a name then add it to the list if not already on list
            if(add == 0 && device.getName() != null) {
                resultsble.add(device);
                results.add(device.getName());
            }
       //     Log.d("BLE device", "Device Name: " + result.getDevice().getName() + " rssi: " + result.getRssi() + "\n");

        }
    };


    @Override
    public void onRequestPermissionsResult(int requestCode,
                                           String[] permissions, int[] grantResults) {
        Log.d("Permission Denied ", "permission Denied from user " + requestCode);

        if ((requestCode > 0) && (requestCode <= ACCESS_COARSE_LOCATION_MY_PERMS) )
                // If request is cancelled,
                if (grantResults.length > 0
                        && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    // permission was granted
                } else {
                    Log.d("Permission Denied ", "permission Denied from user " + requestCode);
                    // permission denied
                }
                return;


    }


    //check permissions for everything needed
    private void checkPermiss()
    {
        // Here, thisActivity is the current activity
        if (ContextCompat.checkSelfPermission(FullscreenActivity.this,
                Manifest.permission.SEND_SMS)
                != PackageManager.PERMISSION_GRANTED) {

            // Permission is not granted
            if (ActivityCompat.shouldShowRequestPermissionRationale(FullscreenActivity.this,
                    Manifest.permission.SEND_SMS)) {
                Log.d("First try","requesting permission for request code " +SEND_SMS_MY_PERMS );
            } else {
                // No explanation needed; request the permission
                ActivityCompat.requestPermissions(FullscreenActivity.this,
                        new String[]{Manifest.permission.SEND_SMS},
                        SEND_SMS_MY_PERMS);
                Log.d("Second try","requesting permission for request code " +SEND_SMS_MY_PERMS );

            }
        }
        if (ContextCompat.checkSelfPermission(FullscreenActivity.this,
                Manifest.permission.BLUETOOTH)
                != PackageManager.PERMISSION_GRANTED) {

            // Permission is not granted
            if (ActivityCompat.shouldShowRequestPermissionRationale(FullscreenActivity.this,
                    Manifest.permission.BLUETOOTH)) {
                Log.d("First try","requesting permission for request code " +BLUETOOTH_MY_PERMS );
            } else {
                // No explanation needed; request the permission
                ActivityCompat.requestPermissions(FullscreenActivity.this,
                        new String[]{Manifest.permission.SEND_SMS},
                        BLUETOOTH_MY_PERMS);
                Log.d("Second try","requesting permission for request code " +BLUETOOTH_MY_PERMS );

            }
        }
        if (ContextCompat.checkSelfPermission(FullscreenActivity.this,
                Manifest.permission.BLUETOOTH_ADMIN)
                != PackageManager.PERMISSION_GRANTED) {

            // Permission is not granted
            if (ActivityCompat.shouldShowRequestPermissionRationale(FullscreenActivity.this,
                    Manifest.permission.BLUETOOTH_ADMIN)) {
                Log.d("First try","requesting permission for request code " +BLUETOOTH_ADMIN_MY_PERMS );
            } else {
                // No explanation needed; request the permission
                ActivityCompat.requestPermissions(FullscreenActivity.this,
                        new String[]{Manifest.permission.BLUETOOTH_ADMIN},
                        BLUETOOTH_ADMIN_MY_PERMS);
                Log.d("Second try","requesting permission for request code " +BLUETOOTH_ADMIN_MY_PERMS );

            }
        }
        if (ContextCompat.checkSelfPermission(FullscreenActivity.this,
                Manifest.permission.SEND_SMS)
                != PackageManager.PERMISSION_GRANTED) {

            // Permission is not granted
            if (ActivityCompat.shouldShowRequestPermissionRationale(FullscreenActivity.this,
                    Manifest.permission.ACCESS_FINE_LOCATION)) {
                Log.d("First try","requesting permission for request code " +ACCESS_FINE_MY_PERMS );
            } else {
                // No explanation needed; request the permission
                ActivityCompat.requestPermissions(FullscreenActivity.this,
                        new String[]{Manifest.permission.ACCESS_FINE_LOCATION},
                        ACCESS_FINE_MY_PERMS);
                Log.d("Second try","requesting permission for request code " +ACCESS_FINE_MY_PERMS );

            }
        }
        if (ContextCompat.checkSelfPermission(FullscreenActivity.this,
                Manifest.permission.ACCESS_COARSE_LOCATION)
                != PackageManager.PERMISSION_GRANTED) {

            // Permission is not granted
            if (ActivityCompat.shouldShowRequestPermissionRationale(FullscreenActivity.this,
                    Manifest.permission.ACCESS_COARSE_LOCATION)) {
                Log.d("First try","requesting permission for request code " +ACCESS_COARSE_LOCATION_MY_PERMS );
            } else {
                // No explanation needed; request the permission
                ActivityCompat.requestPermissions(FullscreenActivity.this,
                        new String[]{Manifest.permission.ACCESS_COARSE_LOCATION},
                        ACCESS_COARSE_LOCATION_MY_PERMS);
                Log.d("Second try","requesting permission for request code " +ACCESS_COARSE_LOCATION_MY_PERMS );

            }
        }
    }
}
