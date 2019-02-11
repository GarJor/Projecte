//created by Jordi Garcia Aguilar
#include "DataManager.hh"

#include <fstream>
#include <algorithm>

using namespace std;

DataManager::DataManager(string filenameInp, string filenameOut){
  this->fnInp = filenameInp;
  this->fnOut = filenameOut;
  this->matchedClass = "nul";
  this->matchedIndex = -1;
  this->classes = vector<string>();
  this->load();
}

string DataManager::getFileName(bool mx){
  if (mx) return this->fnInp;
  return this->fnOut;

}

vector< vector<string> > DataManager::getInpByClass(string clase){
  return this->InpData[clase];

}

vector<string>  DataManager::getOutByClass(string clase){
  return this->OutData[clase];
}

void DataManager::load() {

//getting inputs
  // attach an input stream to the wanted file
  ifstream input_stream(this->fnInp);

  // check stream status
  if (!input_stream) cerr << "Can't open input file!";

  //parse the file
  string line;
  vector< vector<string> > content;
  vector<string> list;
  bool readClass = true;
  int push = false;
  // extract all the text from the input file
  while (getline(input_stream, line)) {
    if(readClass) {
      this->classes.push_back(line);
      readClass = false;
    }
    else if (line == "}") {
      content.push_back(list);
      list.clear();
      readClass = true;
      this->InpData[this->classes[this->classes.size()-1]] = content;
      content.clear();
      push = false;
    }
    else if (line[0] == '-'){
      if(push) content.push_back(list);
      list.clear();
      push = true;
    }
    else {
      list.push_back(line);
    }

  }
  //getting outputs

  ifstream output_stream(this->fnOut);

  // check stream status
  if (!output_stream) cerr << "Can't open output file!";
  int index = -1;
  int end = this->classes.size()-1;
  // extract all the text from the output file
  while (getline(output_stream, line)) {

    if (index < end && line == this->classes[index+1]) ++index;
    else if (line == "}") {
      this->OutData[this->classes[index]] = list;
      list.clear();
    }
    else if (line[0] != '-' && line[0] != '{'){

      list.push_back(line);
    }

  }


}


pair<string, string> DataManager::guess(string toGuess, double llindar) {
  this->matchedClass = "nul";
  this->matchedIndex = -1;
  int index = 0;
  string mtchclas = "nul";
  double track = 0.0;
  for(string clas : this->classes) {
    cerr << "#C " << clas << endl;
    index = 0;
    for(auto list : this->InpData[clas]) {
      //for(int i = 0 ; i < list.size(); ++i) {

      for(string frase : list){
        cerr << index << endl;
        double val = this->similarity(toGuess, frase);
        cerr << toGuess << " || " << frase << " :: " << val << endl;
        if(val >= llindar && val > track ) {
          cerr << "ENTERED on " << index << endl;
          this->matchedClass = clas;
          this->matchedIndex = index;

          if(val == 1.0) return make_pair(clas, getOutByClass(clas)[index]);
        }

      }
      ++index;
    }
  }
  cerr << index << endl;
  if (index == -1) return make_pair("nul", "No te he entendido");
  return make_pair(this->matchedClass, getOutByClass(this->matchedClass)[index]);
}


double DataManager::similarity(const string& s1, const string& s2) {
	const size_t len1 = s1.size(), len2 = s2.size();
	vector<vector<unsigned int>> d(len1 + 1, vector<unsigned int>(len2 + 1));

	d[0][0] = 0;
	for(unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
	for(unsigned int i = 1; i <= len2; ++i) d[0][i] = i;

	for(unsigned int i = 1; i <= len1; ++i)
		for(unsigned int j = 1; j <= len2; ++j)
                      // note that std::min({arg1, arg2, arg3}) works only in C++11,
                      // for C++98 use std::min(std::min(arg1, arg2), arg3)
                      d[i][j] = min({ d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1) });

                      double a = (d[len1][len2] + 0.01);
                      double b = 1.0 - ((a- 0.01)/ max(s1.size(), s2.size()));


	return b;
}

vector<string>  DataManager::getClassNames() {
  return this->classes;
}
