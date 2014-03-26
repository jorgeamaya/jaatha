// This file was generated by Rcpp::compileAttributes
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// parseOutput
List parseOutput(const std::string file_name, const NumericVector sample_size, const int loci_number, const int program = 0, const bool generate_jsfs = true, const bool generate_seg_sites = false, const bool generate_fpc = false);
RcppExport SEXP jaatha_parseOutput(SEXP file_nameSEXP, SEXP sample_sizeSEXP, SEXP loci_numberSEXP, SEXP programSEXP, SEXP generate_jsfsSEXP, SEXP generate_seg_sitesSEXP, SEXP generate_fpcSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        Rcpp::traits::input_parameter< const std::string >::type file_name(file_nameSEXP );
        Rcpp::traits::input_parameter< const NumericVector >::type sample_size(sample_sizeSEXP );
        Rcpp::traits::input_parameter< const int >::type loci_number(loci_numberSEXP );
        Rcpp::traits::input_parameter< const int >::type program(programSEXP );
        Rcpp::traits::input_parameter< const bool >::type generate_jsfs(generate_jsfsSEXP );
        Rcpp::traits::input_parameter< const bool >::type generate_seg_sites(generate_seg_sitesSEXP );
        Rcpp::traits::input_parameter< const bool >::type generate_fpc(generate_fpcSEXP );
        List __result = parseOutput(file_name, sample_size, loci_number, program, generate_jsfs, generate_seg_sites, generate_fpc);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
// parseMsPositions
CharacterVector parseMsPositions(const std::string line);
RcppExport SEXP jaatha_parseMsPositions(SEXP lineSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        Rcpp::traits::input_parameter< const std::string >::type line(lineSEXP );
        CharacterVector __result = parseMsPositions(line);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
// addToJsfs
void addToJsfs(const NumericMatrix seg_sites, const NumericVector sample_size, const int sample_total, NumericMatrix jsfs);
RcppExport SEXP jaatha_addToJsfs(SEXP seg_sitesSEXP, SEXP sample_sizeSEXP, SEXP sample_totalSEXP, SEXP jsfsSEXP) {
BEGIN_RCPP
    {
        Rcpp::RNGScope __rngScope;
        Rcpp::traits::input_parameter< const NumericMatrix >::type seg_sites(seg_sitesSEXP );
        Rcpp::traits::input_parameter< const NumericVector >::type sample_size(sample_sizeSEXP );
        Rcpp::traits::input_parameter< const int >::type sample_total(sample_totalSEXP );
        Rcpp::traits::input_parameter< NumericMatrix >::type jsfs(jsfsSEXP );
        addToJsfs(seg_sites, sample_size, sample_total, jsfs);
    }
    return R_NilValue;
END_RCPP
}
// addToJsfs2
NumericMatrix addToJsfs2(const NumericMatrix seg_sites, const NumericVector sample_size, const int sample_total, NumericMatrix jsfs);
RcppExport SEXP jaatha_addToJsfs2(SEXP seg_sitesSEXP, SEXP sample_sizeSEXP, SEXP sample_totalSEXP, SEXP jsfsSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        Rcpp::traits::input_parameter< const NumericMatrix >::type seg_sites(seg_sitesSEXP );
        Rcpp::traits::input_parameter< const NumericVector >::type sample_size(sample_sizeSEXP );
        Rcpp::traits::input_parameter< const int >::type sample_total(sample_totalSEXP );
        Rcpp::traits::input_parameter< NumericMatrix >::type jsfs(jsfsSEXP );
        NumericMatrix __result = addToJsfs2(seg_sites, sample_size, sample_total, jsfs);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
