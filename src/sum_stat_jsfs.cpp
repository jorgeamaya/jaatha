#include <Rcpp.h>
#include "seg_sites.h"

using namespace Rcpp;

//' Calculate the JSFS from a list of segregating sites statistics
//' 
//' @param seg_sites List of segregating sites
//' @param sample_size A numberic vector of size 2, giving the sample sizes
//'        of the two population for which the JSFS is calulated
//' @return The Joint Site Frequency Spectrum, as a matrix.
// [[Rcpp::export]]
NumericMatrix calcJsfs(const List seg_sites, const NumericVector sample_size) {
  if (sample_size.size() < 2) {
    stop("Two populations need for calculating the JSFS");
  }
  
  NumericMatrix jsfs(sample_size[0]+1, sample_size[1]+1);
  size_t idx1, idx2, ncol, individuals = sample_size[0] + sample_size[1];
  NumericMatrix ss;
  NumericVector trio_locus;
  
  for (int locus = 0; locus < seg_sites.size(); ++locus) {
    ss = as<NumericMatrix>(seg_sites[locus]);
    if (ss.nrow() < individuals) 
      stop("Malformated seg.sites: Too few rows.");
    trio_locus = getTrioLocus(ss);
    ncol = ss.ncol();
    
    for (int j = 0; j < ncol; ++j) {
      if (trio_locus(j) != 0) continue; // Only calculate for middle locus
      idx1 = 0;
      idx2 = 0;
    
      for (int i = 0; i < sample_size[0]; ++i) idx1 += ss(i,j); 
      for (int i = sample_size[0]; i < individuals; ++i) idx2 += ss(i,j); 
    
      ++jsfs(idx1, idx2);
    }
  }
  
  return jsfs;
}
