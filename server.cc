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
<<<<<<< HEAD
#define LLINDAR 0.4

=======
>>>>>>> 335531d276ab1c7aa2f120b0d23ed6ef15a2c2a4

using namespace std;


<<<<<<< HEAD

=======
>>>>>>> 335531d276ab1c7aa2f120b0d23ed6ef15a2c2a4
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
<<<<<<< HEAD
  string frase = string(buf, 0, bytesRecv);  //AQUIIIIIII
=======
  string frase = string(buf, 0, bytesRecv-2);
>>>>>>> 335531d276ab1c7aa2f120b0d23ed6ef15a2c2a4
  return frase;
}


void enviar(int clientsocket, string resposta) {
  char sendBuf[4096];
  memset(sendBuf, 0, 4096);
  sprintf(sendBuf, "%s", resposta.c_str());

  send(clientsocket, sendBuf, strlen(sendBuf)+1, 0);
}




<<<<<<< HEAD
int tractar_frase(string frase, DataManager& dm, int clientSck) {

  pair<string, string> resp = dm.guess(frase, LLINDAR);


  //diferents tractaments segon la classe de inp/out
  if(resp.first == "Interact") enviar(clientSck,resp.second);
  else if(resp.first == "Script"){
    char command[1024];
    sprintf(command,"scripts/%s",resp.second.c_str());
    system(command);
  }

  return 0;
}


int main() {

  //create DataManager
  DataManager dm("entrada", "salida");

=======



int main() {
  DataManager dm("entrada", "salida");
  // cout << dm.getFileName(true) << endl;
  // cout << dm.getFileName(false) << endl;
>>>>>>> 335531d276ab1c7aa2f120b0d23ed6ef15a2c2a4

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
<<<<<<< HEAD
  //inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
  hint.sin_addr.s_addr=INADDR_ANY;
=======
  inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
  //hint.sin_addr.s_addr=INADDR_ANY;
>>>>>>> 335531d276ab1c7aa2f120b0d23ed6ef15a2c2a4

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
<<<<<<< HEAD
  socklen_t clientSize = sizeof(hint);
  int clientSck;
while (true) {


    //acceptem coneccio del client
    clientSck = accept(serverSck, (sockaddr*)&client, &clientSize);
    if(clientSck == -1) cerr << "Problem with client connecting" << endl;



    //llegim del client socket
    string fromClient = rebre(clientSck);
    cerr << "RECEIVED: " << fromClient << endl;

    //tractem input
    tractar_frase(fromClient, dm, clientSck);



=======
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
>>>>>>> 335531d276ab1c7aa2f120b0d23ed6ef15a2c2a4
}
  //close(clientSck);




}
