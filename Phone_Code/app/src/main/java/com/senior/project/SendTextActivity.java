package com.senior.project;

import android.Manifest;
import android.app.PendingIntent;
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

public class SendTextActivity extends FullscreenActivity{
    Button sendText;
    private static final int MY_PERMISSIONS_REQUEST_SEND_SMS = 1;


    /**
     * Touch listener to use for in-layout UI controls to delay hiding the
     * system UI. This is to prevent the jarring behavior of controls going away
     * while interacting with activity UI.
     */

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.sendtextscreen);

        //check permisstions
        checkForSmsPermission();
        //get button and set onclicklistener
        sendText = findViewById(R.id.buttonsendtext);
        sendText.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Toast.makeText(getApplicationContext(), "Pressed", Toast.LENGTH_LONG).show();//display the text of button1
                sendText();

            }
        });

    }

    private void sendText()
    {
        TextView textView = (TextView) findViewById(R.id.phonenumber);
        String smsNumber = String.format("smsto: %s",
                textView.getText().toString());

        EditText smsEditText = (EditText) findViewById(R.id.textmessage);
        // Get the text of the SMS message.
        String smsMessage = smsEditText.getText().toString();
        String scAddress = null;

        PendingIntent sentIntent = null, deliveryIntent = null;
        // Use SmsManager.
        SmsManager smsManager = SmsManager.getDefault();
        smsManager.sendTextMessage
                (smsNumber, scAddress, smsMessage,
                        sentIntent, deliveryIntent);

    }
    //already checked in fullscreenactivity, but double check to make sure.
    private void checkForSmsPermission() {
        if (ActivityCompat.checkSelfPermission(this,
                Manifest.permission.SEND_SMS) !=
                PackageManager.PERMISSION_GRANTED) {
            Log.d("app", "needs sms permission");
            // Permission not yet granted. Use requestPermissions().

            ActivityCompat.requestPermissions(this,
                    new String[]{Manifest.permission.SEND_SMS},
                    MY_PERMISSIONS_REQUEST_SEND_SMS);
        } else {
            // Permission already granted.
        }
    }
}
