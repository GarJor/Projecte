#include <iostream>
#include <vector>
#include <map>


using namespace std;

class DataManager {
  private:
    string fnInp, fnOut; //file name input, file name out;
    string matchedClass;
    int matchedIndex;
    map< string, vector< vector<string> > > InpData;
    map< string, vector< vector<string> > > OutData;
    vector<string> classes;


    /*
    it loads the data from input file in InpData and the data from output file in OutData
    */
    void load();


    /*
    returns the similarity of two strings in a range from 0 to 1
    */
    double similarity(const string& s1, const string& s2);
  public:
    //CONSTRUCTOR
    DataManager(string filenameInp, string filenameOut);




    //GETERS
    /*
    return the input filename if mx = true, else return the output file name
    */
    string getFileName(bool mx);

    /*
    returns matched_class, output for an incomming input
    */
    pair<string, vector<string>> guess(string toGuess, double llindra);

    /*
    returns de matrix of strings stored with the classname class
    */
    vector< vector<string> > getInpByClass(string clase);

    /*
    returns de matrix of strings stored with the classname class
    */
    vector< vector<string> > getOutByClass(string clase) ;

    vector<string>  getClassNames();

    //SETERS


};
