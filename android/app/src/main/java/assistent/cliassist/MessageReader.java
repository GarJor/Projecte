package assistent.cliassist;

import android.os.AsyncTask;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class MessageReader extends AsyncTask<String, Void, Void> {

    Socket s;
    BufferedReader input;
    public String response;

    @Override
    protected Void doInBackground(String... voids) {
        response = voids[0];
        try {
            Integer p = Integer.parseInt(voids[2]);
            s = new Socket(voids[1], p);

            while(response.equals("init")) {
                input = new BufferedReader(new InputStreamReader(s.getInputStream()));
                response = input.readLine();
            }
            //

            s.close();

        }
        catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }



}
