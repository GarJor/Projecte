#include "DataManager.hh"
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <stdio.h>

#define PORT 5500

using namespace std;


string rebre(int clientsocket) {
  char buf[4096];

  //clear the buffer
  memset(buf, 0, 4096);
  // WAIT for amesage
  int bytesRecv = recv(clientsocket, buf, 4096,0);
  if ( bytesRecv == -1) {
    cerr << "Problems with connection" << endl;

  }
  if ( bytesRecv == 0) {
    cerr << "Client disconnected" << endl;

  }
  string frase = string(buf, 0, bytesRecv-2);
  return frase;
}


void enviar(int clientsocket, string resposta) {
  char sendBuf[4096];
  memset(sendBuf, 0, 4096);
  sprintf(sendBuf, "%s", resposta.c_str());

  send(clientsocket, sendBuf, strlen(sendBuf)+1, 0);
}







int main() {
  DataManager dm("entrada", "salida");
  // cout << dm.getFileName(true) << endl;
  // cout << dm.getFileName(false) << endl;

  //create socket
  int serverSck = socket(AF_INET, SOCK_STREAM, 0);
  if(serverSck == -1) {
    cerr << "Can't create the socket!" << endl;
    return -1;
  }

  //bind the socket to a IP / port
  sockaddr_in hint;
  hint.sin_family = AF_INET;
  hint.sin_port = htons(PORT);
  inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
  //hint.sin_addr.s_addr=INADDR_ANY;

  if (bind(serverSck, (sockaddr*) &hint, sizeof(hint)) == -1) {
    cerr << "Can't bind to IP/port" << endl;
    return -1;
  }
  cerr << "Server on port " << PORT << endl;
  //mark the socket for listen
  if (listen(serverSck, 5) == -1) {
    cerr << "Can't listen" << endl;
    return -1;
  }

  //Accept a call
  sockaddr_in client;
  socklen_t clientSize = sizeof(client);

while (true) {
  int clientSck = accept(serverSck, (sockaddr*)&client, &clientSize);
  if(clientSck == -1) {
    cerr << "Problem with client connecting" << endl;
    //return -1;
  }


  while (true) {

    string fromClient = rebre(clientSck);
    cout << "RECEIVED: " << fromClient << endl;


    // tractar_frase();
    pair<string, string> resp = dm.guess(fromClient, 0.4);


    enviar(clientSck,resp.second);

  }
}
  //close(clientSck);




}
