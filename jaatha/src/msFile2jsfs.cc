#include <R.h>	
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int L=0;
vector<int> MutOfSitePop1(0), MutOfSitePop2(0);
int individual = 0;
bool insideSite = 0;

void printjsfs(int *jsfs, const int &s1, const int &s2);
void parseLine(string line, int *jsfs, const int &s1, const int &s2);

//The function to be called from R
extern "C"{
  void msFile2jsfs(char **filename, int *ps1, int *ps2, int *jsfs) {
    int s1=*ps1, s2=*ps2;

    string line;
    //Rprintf("Filename: %s \n",*filename);
    ifstream myfile (*filename);

    if (!myfile.is_open()) {
      error("File %s not found!",*filename);
    }

    while ( myfile.good() ) {
        getline(myfile, line);
        parseLine(line, jsfs, s1, s2);
    }   

    myfile.close();
  }
}

void parseLine(string line, int *jsfs, const int &s1, const int &s2) {
  //cout << line << endl;
  if (line == "") {
      //cout << "> Empty line detected" << endl;
      if (insideSite){
          //Site ended
          insideSite = 0;
          
          //Calc JSFS
          for(int i=0; i<L; ++i){
              //cout << MutOfSitePop1[i] << " : " << MutOfSitePop2[i] << endl;
              jsfs[ MutOfSitePop1[i] * (s1+1) + MutOfSitePop2[i] ]++;
          }

          //printjsfs(jsfs);

          //Unset Site spezific variables
          individual = 0;
          L = 0;
          //cout << "> Site ended detected" << endl;
      }
  }
  else if (line == "//") {
      insideSite = 1;
      //cout << "> New Site detected" << endl;
  }
  else if ( (line.substr(0,1) == "0" || line.substr(0,1) == "1") && insideSite){
      //cout << "> Data line detected" << endl;

      //Initialize per site variables on first data line
      if (L == 0) {
          L = line.length();
          MutOfSitePop1.resize(L);
          MutOfSitePop2.resize(L);
          for (int i=0; i<L; i++) {
              MutOfSitePop1[i] = 0;
              MutOfSitePop2[i] = 0;
          }
      }

      //cout << "> Individual " << individual << "| Population " << individual / s1 << endl;

      //Parse the individual
      if (individual / s1 == 0){
          //we are in population 1 here
          for(int p=0; p<L; ++p) { 
                  if (line[p] == '1') MutOfSitePop1[p]++;
          }

      }
      else {
          //we are in population 2 here
          for(int p=0; p<L; ++p) {
                  if (line[p] == '1') MutOfSitePop2[p]++;
          }
      }
          
      individual++;
  }
}

void printjsfs(int *jsfs, const int &s1, const int &s2) {
  for (int i=0; i<=s1; i++) {
      for (int j=0; j<=s2; j++) {
            cout << jsfs[ i * (s1 + 1) + j ] << " ";
      }
          cout << endl;
  }
}

int main() {
  int s1=10, s2=15;
  int jsfs[176] = {0};
  char filename[] = "msoutput";
  char* pfilename = filename;

  msFile2jsfs(&pfilename, &s1, &s2, jsfs);
  printjsfs(jsfs, s1, s2);

  return(0);
}
