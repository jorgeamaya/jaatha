#include <Rcpp.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

std::vector<int> seqFile2jsfs(const std::string &filename, const int &s1, 
                              const int &s2, const int &nLoci) {

  std::ifstream datei(filename.c_str());

  std::string currentSeq, seqName_tmp;
  unsigned int numSeq, seqLen, seqName;   
  int sampleS[2]={s1, s2};
  char outg;
  numSeq=sampleS[0]+sampleS[1]+1;  // +1for outgroup
  std::vector<std::vector<char> > sequence(numSeq);

  //initialize jsfs
  std::vector<int> jsfs;
  jsfs.assign((s1+1)*(s2+1), 0);

  if ( datei.good() ) {
    for (int c=0; c<nLoci; c++){
      //std::cout << "**** locus " << c << " :" << std::endl;
      datei >>  numSeq >> seqLen;  //first 2 numbers of datei are #seq and #positions
      //cout<<"numSeq:   "<<numSeq<<" seqLen: "<<seqLen<<"    ss1: "<<sampleS[0]<<"    ss2: "<<sampleS[1]<<endl;
      // read sequences into 'sequence[][]' (includes outgroup) and simultaneously sort them
      for(int i=0; i<numSeq; ++i) {
        datei >> seqName_tmp >> currentSeq;	

        //ms from phyclust adds an "s" to the seqName. So remove it if it is
        //there...
        if (seqName_tmp.compare(1, 1, "s")) seqName_tmp.erase(0,1);
        seqName = atoi(seqName_tmp.c_str());
        //Rprintf("SeqName: %d", seqName);

        //cout<<"seqName:   "<<seqName<<" currentSeq: "<<currentSeq<<endl;
        const char* cstr=currentSeq.c_str();
        sequence[seqName-1].assign(cstr, cstr+seqLen);
      }

      //look at each position seperately
      for(int pos=0; pos<seqLen; ++pos) {   
        int derivedCount[2]= {0};     // per pop	     
        outg=sequence[numSeq-1][pos];
        //cout<<"**** position "<<pos<<" :"<<outg<<endl;

        // which nucleotides are present at position pos, including outgroup
        for(int i=0; i<sampleS[0]; ++i) {
          if (sequence[i][pos]!=outg){
            ++derivedCount[0];
          }
        }
        for(int i=sampleS[0]; i<(numSeq-1); ++i) {   //without outgroup
          if (sequence[i][pos]!= outg){
            ++derivedCount[1];
          }
        }
        //cout<<"derivedCount:  "<<derivedCount[0]<<"  "<<derivedCount[1]<<endl;

        //jsfs calculation (positions that are same to outgroup will be counted in res[0,0])
        ++jsfs[derivedCount[1]*(sampleS[0]+1)+derivedCount[0]];
      }  // positions  
    }  //nLoci-for
    datei.close();
  } //if file exists
  else{
    std::cerr << "ERROR: Cannot open file '"<< filename[0]<<"'"<< std::endl;		  
  }
  
  return(jsfs);
}

RcppExport SEXP seqgen2jsfs(SEXP filename_, 
                            SEXP s1_,
                            SEXP s2_,
                            SEXP nLoci_) {

  std::string filename = Rcpp::as<std::string>(filename_);
  int s1 = Rcpp::as<int>(s1_);
  int s2 = Rcpp::as<int>(s2_);
  int nLoci = Rcpp::as<int>(nLoci_);

  std::vector<int> jsfs = seqFile2jsfs(filename, s1, s2, nLoci);

  return Rcpp::wrap( jsfs );
}

#ifndef NDEBUG
void printjsfs(std::vector<int> jsfs, const int &s1, const int &s2) {
  for (int i=0; i<=s1; i++) {
    for (int j=0; j<=s2; j++) {
      std::cout << jsfs[ i * (s2 + 1) + j ] << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  int s1=10, s2=11;
  int nloci = 10;
  std::string filename = "seqgen.output";

  std::vector<int> jsfs = seqFile2jsfs(filename, s1, s2, nloci);
  printjsfs(jsfs, s1, s2);

  return(0);
}
#endif
