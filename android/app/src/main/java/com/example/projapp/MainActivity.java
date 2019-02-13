package com.example.projapp;

import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.StrictMode;
import android.speech.RecognizerIntent;
import android.speech.tts.TextToSpeech;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;
import java.nio.CharBuffer;
import java.util.ArrayList;
import java.util.Locale;




public class MainActivity extends AppCompatActivity {

    private TextView comando;
    private String resultat;
    private String IP = "192.168.1.128";
    private int PORT = 5500;
    private TextView response;
    private static Socket s;
    private TextToSpeech textToSpeech;
    private static  PrintWriter pw;

    String toSend = "";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        displayip(IP);
        displayport(PORT);
        comando = (TextView) findViewById(R.id.command);
         response = (TextView) findViewById(R.id.response);
        StrictMode.setThreadPolicy(new StrictMode.ThreadPolicy.Builder().permitNetwork().build());

        //vaina necessaria perk la app parli
        textToSpeech = new TextToSpeech(this, new TextToSpeech.OnInitListener() {
            @Override
            public void onInit(int status) {
                talk();
            }
        });
    }

    public void talk(){
        String toTalk = response.getText().toString();
        textToSpeech.speak(toTalk.subSequence(0,toTalk.length()), TextToSpeech.QUEUE_FLUSH, null, "");
    }
    public void setIPPORT (View view) {
    response.setText("Valors de IP i PORT actualitzats correctament.");
    EditText ipdec = (EditText) findViewById(R.id.ip);
    EditText portdec = (EditText) findViewById(R.id.port);
    IP = ipdec.getText().toString();
    PORT = Integer.parseInt(portdec.getText().toString());


    }

    public void displayip(String ip){
        EditText find_ip = (EditText) findViewById(R.id.ip);
        find_ip.setText(String.valueOf(ip));

    }

    public void displayport(int port){
        EditText find_port = (EditText) findViewById(R.id.port);
        find_port.setText(String.valueOf(port));

    }

    public void getSpeechInput(View view) {
        setIPPORT(view);
        Intent intent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
        intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL, RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
        intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE, Locale.getDefault());

        if (intent.resolveActivity(getPackageManager()) != null) {
            startActivityForResult(intent, 10);
        } else {
            Toast.makeText(this, "No li agrada l'input", Toast.LENGTH_LONG).show();
        }

    }

    public void sendText(String message) {

        try {
            s = new Socket(IP, PORT); //connect to server at port port
            pw = new PrintWriter(s.getOutputStream());
            pw.write(message);

            pw.flush();  //send the missatge
            Toast.makeText(this, "Missatge enviat" , Toast.LENGTH_LONG).show();
            InputStream is = s.getInputStream();

            InputStreamReader isr =  new InputStreamReader(is);

            BufferedReader in = new BufferedReader(isr);

            String res = in.readLine();
            //Log.d("myTask", "IN: "+res);
                response.setText(res);


            this.talk();
            s.close();


        } catch (IOException e) {
            Log.e("myTask", "S: Error", e);
        }
    }








    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
            switch (requestCode){
                case 10:
                    if(resultCode == RESULT_OK && data != null){
                        ArrayList<String> result = data.getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS);
                        toSend = result.get(0);
                        sendText(toSend);
                    }

                    break;
            }
    }
}
