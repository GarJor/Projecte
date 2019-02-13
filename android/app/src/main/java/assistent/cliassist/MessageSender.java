package assistent.cliassist;

import android.os.AsyncTask;
import android.widget.EditText;

import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;

public class MessageSender extends AsyncTask<String, Void, Void> {

    Socket s;

    PrintWriter pw;



    @Override
    protected Void doInBackground(String... voids) {
        String message = voids[0];
        try {
            Integer p = Integer.parseInt(voids[2]);
            s = new Socket(voids[1], p);
            pw = new PrintWriter(s.getOutputStream());
            pw.write(message);
            pw.flush();

            pw.close();
            s.close();

        }
        catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }



}
