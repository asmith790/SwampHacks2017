package com.pebbleapp.swamphacks2017.swamphacks2017;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.CountDownTimer;
import android.support.annotation.NonNull;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;
import android.media.MediaPlayer;
import android.media.MediaRecorder;

import com.getpebble.android.kit.PebbleKit;
import com.getpebble.android.kit.util.PebbleDictionary;

import java.io.IOException;
import java.util.Timer;
import java.util.UUID;

public class MainActivity extends AppCompatActivity {

    int threshold = 60;
    private static final String LOG_TAG = "AudioRecordTest";
    private static final int REQUEST_RECORD_AUDIO_PERMISSION = 200;
    private static String mFileName = null;
    MediaRecorder mRecorder = new MediaRecorder();
    MediaPlayer mPlayer = new MediaPlayer();
    boolean startPlaying = true;

    final UUID WATCHAPP_UUID = UUID.fromString("198aeba1-fce1-40bd-9986-131ca23b2917");

    //private static final String WATCHAPP_FILENAME = "vibratealerts.pbw";

    boolean switchOn = false;


    private boolean permissionToRecordAccepted = false;
    private String [] permissions = {Manifest.permission.RECORD_AUDIO};
    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        switch (requestCode){
            case REQUEST_RECORD_AUDIO_PERMISSION:
                permissionToRecordAccepted  = grantResults[0] == PackageManager.PERMISSION_GRANTED;
                break;
        }
        if (!permissionToRecordAccepted ) finish();

    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        ActivityCompat.requestPermissions(this, permissions, 200);
        setContentView(R.layout.activity_main);
        mFileName = getExternalCacheDir().getAbsolutePath();
        mFileName += "/audiorecordtest.3gp";
    }

    public void clickSwitch(View view) {
        if(!switchOn) {
            PebbleKit.startAppOnPebble(getApplicationContext(), WATCHAPP_UUID);
            //Start Recording
            mRecorder = new MediaRecorder();
            mRecorder.setAudioSource(MediaRecorder.AudioSource.VOICE_RECOGNITION);
            mRecorder.setOutputFormat(MediaRecorder.OutputFormat.THREE_GPP);
            mRecorder.setOutputFile(mFileName);
            mRecorder.setAudioEncoder(MediaRecorder.AudioEncoder.AMR_NB);

            try {
                mRecorder.prepare();
            } catch (IOException e) {
                Log.e(LOG_TAG, "prepare() failed");
            }
            mRecorder.start();
        }
        else {
            //Stop recording
            mRecorder.stop();
            mRecorder.release();
            mRecorder = null;
            mPlayer = new MediaPlayer();
            try {
                mPlayer.setDataSource(mFileName);
                mPlayer.prepare();
                mPlayer.start();
            } catch (IOException e) {
                Log.e(LOG_TAG, "prepare() failed");
            }
            PebbleKit.closeAppOnPebble(getApplicationContext(), WATCHAPP_UUID);
        }
        switchOn = !switchOn;
    }

    public void startCalibation(View view) {
        setContentView(R.layout.activity_calibrate);
        final TextView countdown = (TextView)findViewById(R.id.timerText);
        //start playing the recording
        if(startPlaying) {

        }

        new CountDownTimer(6000, 1000) {
            @Override
            public void onTick(long millisUntilFinished) {
                countdown.setText("" + (millisUntilFinished / 1000) );
            }
            @Override
            public void onFinish() {

                //stop playing the recording

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
