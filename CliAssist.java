package assistent.cliassist;

import android.content.Intent;
import android.speech.RecognizerIntent;
import android.speech.tts.TextToSpeech;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

import java.io.DataOutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Locale;

public class CliAssist extends AppCompatActivity {

    private static final int REQUEST_CODE_SPEECH_INPUT = 1000;

    //views from activity
    TextView mTextTv;
    ImageButton mVoiceBtn;
    EditText ipText;
    EditText portText;

    private TextToSpeech mTTS;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_cli_assist);

        mTextTv = findViewById(R.id.textTv);
        mVoiceBtn = findViewById(R.id.voiceBtn);
        ipText = findViewById(R.id.edIP);
        portText = findViewById(R.id.edPORT);

        //Button click to show speech to text dialog
        mVoiceBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                speak();
            }
        });

        // TEXT TO SPEECH
        mTTS = new TextToSpeech(this, new TextToSpeech.OnInitListener() {
            @Override
            public void onInit(int status) {
                if (status == TextToSpeech.SUCCESS) {
                    int result = mTTS.setLanguage(Locale.getDefault());
                }
            }
        });


    }
    public void response(String text) {
        mTTS.speak(text, TextToSpeech.QUEUE_FLUSH, null);
    }


    private void speak() {
        //intent to show speech to text dialog
        Intent intent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
        intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL, RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
        intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE, Locale.getDefault());
        intent.putExtra(RecognizerIntent.EXTRA_PROMPT, "Say something");

        //start intent
        try {
            //show dialog

            startActivityForResult(intent, REQUEST_CODE_SPEECH_INPUT );
        }
        catch (Exception e) {
            //get mesage of error and show
            Toast.makeText(this, ""+e.getMessage(), Toast.LENGTH_SHORT).show();
        }
    }

    //sending result to server
    public void send( String v) {
        MessageSender messageSender = new MessageSender();
        messageSender.execute(v, ipText.getText().toString(), portText.getText().toString());

        String rsp = listenToServer();
        response(rsp);

    }
    public String listenToServer() {
        MessageReader mr = new MessageReader();
        mr.execute("init", ipText.getText().toString(), portText.getText().toString());
        return mr.response;


    }

    //receive voice input and handle it
    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        switch  (requestCode) {
            case REQUEST_CODE_SPEECH_INPUT: {
                if (resultCode == RESULT_OK && data != null) {
                    //get text array from voice intent
                    ArrayList<String> result = data.getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS);
                    mTextTv.setText("You said: "+result.get(0));
                    send(result.get(0));

                }
                break;
            }
        }

    }



}
