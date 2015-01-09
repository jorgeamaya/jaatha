#include <Rcpp.h>
#include "seg_sites.h"

using namespace Rcpp;

int getType(size_t snp_1, size_t snp_2, 
            const NumericVector positions, const NumericVector trio_locus) {
              
  if (trio_locus(snp_1) == 0 && trio_locus(snp_2) == 0) {
    return(std::abs(positions(snp_1) - positions(snp_2)) > 0.1); 
  }
  
  if (trio_locus(snp_1) != trio_locus(snp_2)) {
    return 3;
  }
  
  return 2;
}

bool is_singleton(const NumericMatrix seg_sites,
                  const IntegerVector individuals,
                  const size_t snp) {
                    
  size_t mut_count = 0;
  for (int i = 0; i < individuals.size(); ++i) {
    mut_count += seg_sites(individuals(i)-1, snp);
  }
  
  return(mut_count == 1);
}


// [[Rcpp::export]]
NumericMatrix calcPercentFpcViolation(const List seg_sites_list,
                                      const IntegerVector individuals,
                                      const NumericMatrix locus_length) {
                                
  size_t loci_number = seg_sites_list.size();
  if (loci_number != (size_t)locus_length.nrow()) stop("Locus number mismatch");
  size_t type; // 0 = near, 1 = far, 2 = on outer locus, 3 = between loci;
  
  NumericMatrix violations(loci_number, 6);
  violations.attr("dimnames") = 
    List::create(R_NilValue, CharacterVector::create(
        "mid_near", "mid_far", "outer", "between", "mid", "perc_polym")
    ); 
  
  NumericVector total_count(4);
  std::vector<bool> combinations(4);
  NumericMatrix seg_sites;
  NumericVector positions, trio_locus;
  
  for (size_t locus = 0; locus < loci_number; ++locus) {
    // Reset variables
    std::fill(total_count.begin(), total_count.end(), 0);   
    
    // Get the locus
    seg_sites = as<NumericMatrix>(seg_sites_list[locus]);
    positions = getPositions(seg_sites);
    trio_locus = getTrioLocus(seg_sites);

    // Look at all pairs of SNPs
    for (int i = 0; i < seg_sites.ncol(); ++i) {
      // Ignore singletons
      if (is_singleton(seg_sites, individuals, i)) continue;
      
      for (int j = i + 1; j < seg_sites.ncol(); ++j) {
        // Ignore singletons
        if (is_singleton(seg_sites, individuals, j)) continue;
        // Ignore SNP pairs between outer loci
        if (std::abs(trio_locus(i) - trio_locus(j)) == 2) continue;
        
        // Reset combination counter
        std::fill(combinations.begin(), combinations.end(), false);
      
        // Get the type of the SNP pair
        type = getType(i, j, positions, trio_locus);

        // Count combinations
        for (int k = 0; k < individuals.size(); ++k) {
          combinations[2*seg_sites(individuals(k)-1, i) + seg_sites(individuals(k)-1, j)] = true;
        }
      
        // If we have all combinations
        if (combinations[0] && combinations[1] && combinations[2] && combinations[3]) {
          ++violations(locus, type);
        }

        ++total_count(type);
      }
    }

    // Calculate %violations for all SNP pairs in middle locus
    violations(locus, 4) = (violations(locus, 0) + violations(locus, 1)) / 
                           (total_count(0) + total_count(1));
    
    // Calculate %violations for near and far SNP pairs in middle locus,
    // and for pairs between loci.
    for (int i = 0; i < 4; ++i) violations(locus, i) /= total_count(i);
    
    // Calculate SNPs per basepair for middle locus
    violations(locus, 5) = sum(trio_locus == 0) / locus_length(locus, 2);
  }
  
  return violations;
}
