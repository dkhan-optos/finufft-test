#ifndef __SPREAD_H__
#define __SPREAD_H__

#include "../finufft/utils.h"
#include "cufinufft.h"

#define MAX_NSPREAD 16
//Kernels for 1D codes (this is outdated ... )
/*
__global__
void CalcBinSize_1d(int M, int nf1, int  bin_size_x, int nbinx,
                    int* bin_size, FLT *x, int* sortidx);
__global__
void FillGhostBin_1d(int bin_size_x, int nbinx, int*bin_size);

__global__
void BinsStartPts_1d(int M, int totalnumbins, int* bin_size, int* bin_startpts);

__global__
void PtsRearrage_1d(int M, int nf1, int bin_size_x, int nbinx,
                    int* bin_startpts, int* sortidx, FLT *x, FLT *x_sorted,
                    FLT *c, FLT *c_sorted);
__global__
void Spread_1d(int nbin_block_x, int nbinx, int *bin_startpts,
               FLT *x_sorted, FLT *c_sorted, FLT *fw, int ns,
               int nf1, FLT es_c, FLT es_beta);
*/

__global__
void RescaleXY_1d(int M, int nf1, int nf2, FLT* x, FLT* y);
//Kernels for 1D codes
__global__
void CalcBinSize_noghost_1d(int M, int nf1, int nf2, int  bin_size_x, int bin_size_y, int nbinx,
                    int nbiny, int* bin_size, FLT *x, FLT *y, int* sortidx);
__global__
void uniformUpdate(int n, int* data, int* buffer);
__global__
void CalcInvertofGlobalSortIdx_1d(int M, int bin_size_x, int bin_size_y, int nbinx,
                                  int nbiny, int* bin_startpts, int* sortidx,
                                  FLT *x, FLT *y, int* index);
__global__
void PtsRearrage_noghost_1d(int M, int nf1, int nf2, int bin_size_x, int bin_size_y, int nbinx,
                int nbiny, int* bin_startpts, int* sortidx, FLT *x, FLT *x_sorted,
                FLT *y, FLT *y_sorted, CUCPX *c, CUCPX *c_sorted);
__global__
void Spread_1d_Odriven(int nbin_block_x, int nbin_block_y, int nbinx, int nbiny, int *bin_startpts,
                       FLT *x_sorted, FLT *y_sorted, CUCPX *c_sorted, CUCPX *fw, int ns,
                       int nf1, int nf2, FLT es_c, FLT es_beta, int fw_width);
__global__
void Spread_1d_Idriven(FLT *x, FLT *y, CUCPX *c, CUCPX *fw, int M, const int ns,
                       int nf1, int nf2, FLT es_c, FLT es_beta, int fw_width);
__global__
void Interp_1d_Idriven(FLT *x, FLT *y, CUCPX *c, CUCPX *fw, int M, const int ns,
                       int nf1, int nf2, FLT es_c, FLT es_beta, int fw_width);
__global__
void Spread_1d_Idriven_Horner(FLT *x, FLT *y, CUCPX *c, CUCPX *fw, int M, const int ns,
                              int nf1, int nf2, FLT es_c, FLT es_beta, int fw_width);
__global__
void Spread_1d_Hybrid(FLT *x, FLT *y, CUCPX *c, CUCPX *fw, int M, const int ns,
                      int nf1, int nf2, FLT es_c, FLT es_beta, int fw_width, int* binstartpts,
                      int* bin_size, int bin_size_x, int bin_size_y);
__global__
void Spread_1d_Simple(FLT *x, FLT *y, CUCPX *c, CUCPX *fw, int M, const int ns,
                      int nf1, int nf2, FLT es_c, FLT es_beta, int fw_width, int bin_size,
                      int bin_size_x, int bin_size_y, int binx, int biny);
__global__
void CalcSubProb_1d(int* bin_size, int* num_subprob, int maxsubprobsize, int numbins);
__global__
void MapBintoSubProb_1d(int* d_subprob_to_bin, int* d_subprobstartpts, int* d_numsubprob,
                        int numbins);
__global__
void Spread_1d_Subprob(FLT *x, FLT *y, CUCPX *c, CUCPX *fw, int M, const int ns,
                          int nf1, int nf2, FLT es_c, FLT es_beta, FLT sigma, int fw_width, int* binstartpts,
                          int* bin_size, int bin_size_x, int bin_size_y, int* subprob_to_bin,
                          int* subprobstartpts, int* numsubprob, int maxsubprobsize, int nbinx, int nbiny,
                          int* idxnupts);
__global__
void Interp_1d_Subprob(FLT *x, FLT *y, CUCPX *c, CUCPX *fw, int M, const int ns,
                          int nf1, int nf2, FLT es_c, FLT es_beta, FLT sigma, int fw_width, int* binstartpts,
                          int* bin_size, int bin_size_x, int bin_size_y, int* subprob_to_bin,
                          int* subprobstartpts, int* numsubprob, int maxsubprobsize, int nbinx, int nbiny,
                          int* idxnupts);

//Kernels for 2D codes
__global__
void RescaleXY_2d(int M, int nf1, int nf2, FLT* x, FLT* y);
__global__
void CalcBinSize_noghost_2d(int M, int nf1, int nf2, int  bin_size_x, int bin_size_y, int nbinx,
                    int nbiny, int* bin_size, FLT *x, FLT *y, int* sortidx);
__global__
void uniformUpdate(int n, int* data, int* buffer);
__global__
void CalcInvertofGlobalSortIdx_2d(int M, int bin_size_x, int bin_size_y, int nbinx,
                                  int nbiny, int* bin_startpts, int* sortidx,
                                  FLT *x, FLT *y, int* index);
__global__
void PtsRearrage_noghost_2d(int M, int nf1, int nf2, int bin_size_x, int bin_size_y, int nbinx,
                int nbiny, int* bin_startpts, int* sortidx, FLT *x, FLT *x_sorted,
                FLT *y, FLT *y_sorted, CUCPX *c, CUCPX *c_sorted);
__global__
void Spread_2d_Odriven(int nbin_block_x, int nbin_block_y, int nbinx, int nbiny, int *bin_startpts,
                       FLT *x_sorted, FLT *y_sorted, CUCPX *c_sorted, CUCPX *fw, int ns,
                       int nf1, int nf2, FLT es_c, FLT es_beta, int fw_width);
__global__
void Spread_2d_Idriven(FLT *x, FLT *y, CUCPX *c, CUCPX *fw, int M, const int ns,
                       int nf1, int nf2, FLT es_c, FLT es_beta, int fw_width);
__global__
void Interp_2d_Idriven(FLT *x, FLT *y, CUCPX *c, CUCPX *fw, int M, const int ns,
                       int nf1, int nf2, FLT es_c, FLT es_beta, int fw_width);
__global__
void Spread_2d_Idriven_Horner(FLT *x, FLT *y, CUCPX *c, CUCPX *fw, int M, const int ns,
                              int nf1, int nf2, FLT es_c, FLT es_beta, int fw_width);
__global__
void Spread_2d_Hybrid(FLT *x, FLT *y, CUCPX *c, CUCPX *fw, int M, const int ns,
                      int nf1, int nf2, FLT es_c, FLT es_beta, int fw_width, int* binstartpts,
                      int* bin_size, int bin_size_x, int bin_size_y);
__global__
void Spread_2d_Simple(FLT *x, FLT *y, CUCPX *c, CUCPX *fw, int M, const int ns,
                      int nf1, int nf2, FLT es_c, FLT es_beta, int fw_width, int bin_size,
                      int bin_size_x, int bin_size_y, int binx, int biny);
__global__
void CalcSubProb_2d(int* bin_size, int* num_subprob, int maxsubprobsize, int numbins);
__global__
void MapBintoSubProb_2d(int* d_subprob_to_bin, int* d_subprobstartpts, int* d_numsubprob,
                        int numbins);
__global__
void Spread_2d_Subprob(FLT *x, FLT *y, CUCPX *c, CUCPX *fw, int M, const int ns,
                          int nf1, int nf2, FLT es_c, FLT es_beta, FLT sigma, int fw_width, int* binstartpts,
                          int* bin_size, int bin_size_x, int bin_size_y, int* subprob_to_bin,
                          int* subprobstartpts, int* numsubprob, int maxsubprobsize, int nbinx, int nbiny,
                          int* idxnupts);
__global__
void Interp_2d_Subprob(FLT *x, FLT *y, CUCPX *c, CUCPX *fw, int M, const int ns,
                          int nf1, int nf2, FLT es_c, FLT es_beta, FLT sigma, int fw_width, int* binstartpts,
                          int* bin_size, int bin_size_x, int bin_size_y, int* subprob_to_bin,
                          int* subprobstartpts, int* numsubprob, int maxsubprobsize, int nbinx, int nbiny,
                          int* idxnupts);
// 1d
int cufinufft_spread1d(int ms, int mt, int nf1, int nf2, CPX* h_fw, int M, FLT *h_kx,
                       FLT *h_ky, CPX* h_c, cufinufft_opts &opts, cufinufft_plan *dmem);
int cufinufft_interp1d(int ms, int mt, int nf1, int nf2, CPX* h_fw, int M, FLT *h_kx,
                       FLT *h_ky, CPX* h_c, cufinufft_opts &opts, cufinufft_plan *dmem);
int cuspread1d_idriven(int nf1, int nf2, int fw_width, int M, const cufinufft_opts opts,
                       cufinufft_plan *d_mem);
int cuinterp1d_idriven(int nf1, int nf2, int fw_width, int M, const cufinufft_opts opts,
                       cufinufft_plan *d_mem);
int cuspread1d_idriven_sorted(int nf1, int nf2, int fw_width, int M, const cufinufft_opts opts,
                       cufinufft_plan *d_mem);
int cuspread1d_hybrid(int nf1, int nf2, int fw_width, int M, const cufinufft_opts opts,
                      cufinufft_plan *d_mem);
int cuspread1d_subprob(int nf1, int nf2, int fw_width, int M, const cufinufft_opts opts,
                       cufinufft_plan *d_mem);
int cuinterp1d_subprob(int nf1, int nf2, int fw_width, int M, const cufinufft_opts opts,
                       cufinufft_plan *d_mem);
int cuspread1d_simple(int nf1, int nf2, int fw_width, CUCPX* d_fw, int M, FLT *d_kx,
                      FLT *d_ky, CUCPX *d_c, const cufinufft_opts opts, int binx, int biny);
int cuspread1d(cufinufft_opts &opts, cufinufft_plan* d_plan);
int cuinterp1d(cufinufft_opts &opts, cufinufft_plan* d_plan);

// 2d
int cufinufft_spread2d(int ms, int mt, int nf1, int nf2, CPX* h_fw, int M, FLT *h_kx,
                       FLT *h_ky, CPX* h_c, cufinufft_opts &opts, cufinufft_plan *dmem);
int cufinufft_interp2d(int ms, int mt, int nf1, int nf2, CPX* h_fw, int M, FLT *h_kx,
                       FLT *h_ky, CPX* h_c, cufinufft_opts &opts, cufinufft_plan *dmem);
int cuspread2d_idriven(int nf1, int nf2, int fw_width, int M, const cufinufft_opts opts,
                       cufinufft_plan *d_mem);
int cuinterp2d_idriven(int nf1, int nf2, int fw_width, int M, const cufinufft_opts opts,
                       cufinufft_plan *d_mem);
int cuspread2d_idriven_sorted(int nf1, int nf2, int fw_width, int M, const cufinufft_opts opts,
                               cufinufft_plan *d_mem);
int cuspread2d_hybrid(int nf1, int nf2, int fw_width, int M, const cufinufft_opts opts,
                      cufinufft_plan *d_mem);
int cuspread2d_subprob(int nf1, int nf2, int fw_width, int M, const cufinufft_opts opts,
                       cufinufft_plan *d_mem);
int cuinterp2d_subprob(int nf1, int nf2, int fw_width, int M, const cufinufft_opts opts,
                       cufinufft_plan *d_mem);
int cuspread2d_simple(int nf1, int nf2, int fw_width, CUCPX* d_fw, int M, FLT *d_kx,
                      FLT *d_ky, CUCPX *d_c, const cufinufft_opts opts, int binx, int biny);
int cuspread2d(cufinufft_opts &opts, cufinufft_plan* d_plan);
int cuinterp2d(cufinufft_opts &opts, cufinufft_plan* d_plan);
#endif
