#include "DataManager.hh"

using namespace std;




int main() {
  DataManager dm("entrada", "salida");
  cout << dm.getFileName(true) << endl;
  cout << dm.getFileName(false) << endl;
}
