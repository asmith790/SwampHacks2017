package com.pebbleapp.swamphacks2017.swamphacks2017;

import android.content.Intent;
import android.os.CountDownTimer;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.getpebble.android.kit.PebbleKit;
import com.getpebble.android.kit.util.PebbleDictionary;

import java.util.Timer;
import java.util.UUID;

public class MainActivity extends AppCompatActivity {
    final UUID WATCHAPP_UUID = UUID.fromString("198aeba1-fce1-40bd-9986-131ca23b2917");
    //private static final String WATCHAPP_FILENAME = "vibratealerts.pbw";
    boolean switchOn = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void clickSwitch(View view) {
        if(!switchOn) {
            PebbleKit.startAppOnPebble(getApplicationContext(), WATCHAPP_UUID);
        }
        else {
            PebbleKit.closeAppOnPebble(getApplicationContext(), WATCHAPP_UUID);
        }
        switchOn = !switchOn;
    }

    public void startCalibation(View view) {
        setContentView(R.layout.activity_calibrate);
        final TextView countdown = (TextView)findViewById(R.id.timerText);
        new CountDownTimer(6000, 1000) {
            @Override
            public void onTick(long millisUntilFinished) {
                countdown.setText("" + (millisUntilFinished / 1000) );
            }
            @Override
            public void onFinish() {
                setContentView(R.layout.activity_main);

                LayoutInflater inflater = getLayoutInflater();
                View layout = inflater.inflate(R.layout.toast_calibration,
                        (ViewGroup) findViewById(R.id.custom_toast_container));

                TextView text = (TextView) layout.findViewById(R.id.toastText);
                text.setText("Volume Threshold Set!");

                Toast toast = new Toast(getApplicationContext());
                toast.setGravity(Gravity.CENTER_VERTICAL, 0, 400);
                toast.setDuration(Toast.LENGTH_LONG);
                toast.setView(layout);
                toast.show();
            }
        }.start();
    }
}
