#include <stdio.h>   /* required for file io definitions */
#include <malloc.h>
/* #include <stdlib.h> */
#include <math.h>

#define PI		3.1415926
#define K8 		8192
#define NGMAX 		K8
#define NXV 		K8
#define NVY 		NXV/2
#define NSPM 		8	
#define HISTMAX	        512
#define NVBINMAX        1024
#define MAXPARTICLES    920001

#ifndef DBL_MIN
#define DBL_MIN 	1E-200
#endif

#ifndef True
#define True            1
#endif

#ifndef False
#define False           0
#endif

/***********************************/
						  
#if defined(GLOBALORIGIN)
#define GLOBAL
#else
#define GLOBAL extern
#endif

GLOBAL float l, dx, dt, la, ael, epsi, rho0, a1, a2, e0, w0, ese_hist, p,
             ecconst;

GLOBAL float *kes_hist, *pxs_hist, *esem_hist, *ms, *qs, *ts, *nms,
             *ese, **kes, **pxs, **esem, *ke, *te, *x, *vx, *vy,
             *x_array,  *t_array, *k_array, *rho, *phi, *phik, *e,
             *acc, *dvbin, *v_array, *vbint, *vbin, *vbinstart,
             *vbin_inst;

GLOBAL double t;

GLOBAL FILE *InputDeck;

GLOBAL int it, nt, ith, ithl, hist_hi, interval, nsp, localnsp, accum,
       mmax, ng, ng1, iw, ec, k_hi, ins[NSPM+2], np[NSPM+2],vbins[NSPM +2],nvbin[NSPM];


GLOBAL float frand();

// Prototypes
void accel(int, int, double, double, double, double, double);
#undef GLOBAL
