/* 
**	ES1 - ELECTROSTATIC 1 DIMENSIONAL PLASMA SIMULATION
**
**
**	REVISION/PROGRAMMER/DATE
**
**	1.0 Conversion from FORTRAN to C/T. Lasinski
**
**	2.0 Conversion to MS C 5.0, improvement of speed and graphics resolution (to
**	EGA), addition of diagnostics (E,P,KE,TE)/John P. Verboncoeur/12-12-87
**
**	2.1 Dynamic array allocation/John P. Verboncoeur/02-23-88
**	2.101 CGA code/John P. Verboncoeur/03-27-88
**	2.102 Fix Maxwellian thermal loaders/John P. Verboncoeur/04-01-88
**	2.103 Fix Magnetized velocity rotator/John P. Verboncoeur/04-18-88
**	2.104 Register optimizations/John P. Verboncoeur/04-21-88
**	2.105 Add kperp (charge disk)/John P. Verboncoeur/05-07-88
**	2.106 Add Field Energy histories for Fourier modes 1-3/John P.
**			Verboncoeur/05-08-88
**	2.107 Enhance display paging scheme/John P. Verboncoeur/06-14-88
**	2.108 Make '.INP' the default input deck extension/John P.
**			Verboncoeur/06-18-88
**	2.109 Enable arbitrary number of text lines in input decks/John P.
**			Verboncoeur/06-20-88
**	2.11  Semi-log plots/John P. Verboncoeur/07-29-88
**	
**	3.0 WinGraphics interface/John P. Verboncoeur and Vahid Vahedi/02-28-89
**
**      4.0 XGRAFIX interface/Vahid Vahedi and John Verboncoeur/01-04-91
**
**      4.1 Velocity distribution diagnostics, quadratic and cubic spline
**          weighting for move and accel, with energy conserving algorithms,
**	    Vx-Vy diagnostic.		
**          Keith Cartwright and Peter Mardahl
**
*/ 
/*
#define GLOBALORIGIN
#include "es1.h"
#undef GLOBALORIGIN
#include <xgrafix.h>

main(int argc, char **argv) {
    int i;
    char outfilename[100];
    int J;
    float Vmax;

    FILE * outfile;
    display_title();

    // Read input file, and initialize params and vars. This function calls SPECIES and LOAD or Restore
    XGInit(argc, argv, &t);
    Start(argc,argv);
    InitWindows(argc, argv);
    history();
    XGStart();
}


void XGMainLoop()
{
  int i;
  char outfilename[100];
  int J;
  float Vmax;

  FILE * outfile;

  // If collisions are included in the simulation load the ion and electron-neutral collision cros-sections



    p = 0.0;
    for (i=1; i <= nsp; i++) 
    {
      accel(ins[i], ins[i+1]-1, qs[i], ms[i], ts[i], &pxs_hist[i], &kes_hist[i]);
      p += pxs_hist[i];
    }
    for (i=1;i <= ng;i++) rho[i] = rho0;  
    rho[ng1] = 0.0;
    rho[ng+2]=rho[0]=0.0;    // ch:zeroing all extra points
    
    for (i=1; i <= nsp; i++) move(ins[i],ins[i+1]-1,qs[i]);

    rho[1]+=rho[ng1];
    rho[2]+=rho[ng+2];
    rho[ng]+=rho[0];
    rho[ng1]=rho[1];
    rho[0]=rho[ng];
    rho[ng+2]=rho[2];
    t= it*dt;


    history();
    velocity();

    fields(ith);
    
    ith = ++it -ithl;
    

}

display_title()
{
  printf("\n\nES1 - Electrostatic 1 Dimensional Code\n");
  printf("version 4.1\n");
  printf("(c) Copyright 1987-92 Regents of the University of California\n");
  printf("Plasma Theory and Simulation Group\n");
  printf("University of California - Berkeley\n");
}

Start(argc,argv) 
int argc;
char *argv[];
{
  char a_char[80];
  int i, j;
  
  // Setting the global parameters to their default values.
  
  l=6.283185307;
  dt=0.2;
  nsp=1;
  
  epsi=1.0;
  ng=32;
  iw=2;
  ec=0;
  
  ins[1] = 1;
  vbins[1] = 1;  // sets up the start of vbin.
  interval=1;
  
  if (!WasInputFileGiven) InputDeck = fopen("es1data","r");
  else InputDeck = fopen(theInputFile,"r");
  
  if (!InputDeck)
  {
    printf("\nCan't find input file %s\n",argv[1]);
    printf("\nCorrect syntax is: ES1 -i file.inp\n");
    exit(-1);
  }
  
  // read lines until we get to numbers
  
  while (fscanf(InputDeck,"%d %g %g %d %d %g %d",
		&nsp, &l, &dt, &nt, &mmax, &la, &accum) <7)
    fscanf(InputDeck, "%s", a_char);
  // note: la is l/a
  
  while (fscanf(InputDeck," %d %d %d %g %g %g %g %g",
		&ng, &iw, &ec, &epsi, &a1, &a2, &e0, &w0) < 8)
    fscanf(InputDeck, "%s", a_char);
  
  if (nsp > NSPM) {
    printf("Number of species nsp cannot exceed NSPM\n");
    exit(-1);
  }

  if(accum<0) { printf("\nError:  accum can't be negative! \n"); exit(1);
	      }

  if(!(ec==1||ec==0)) {
    printf("\n Error:  What are you thinking?  There are only two possible values of ec\n");
    printf("0 and 1.  %d is not 0 or 1.",ec);
    exit(1);
  }
  if(!iw&&ec) {
    printf("\nError:  There IS no energy-conserving algorithm for NGP\n");
    exit(1);
  }


  ecconst=0.0;
  if (ec) {
           ecconst=0.5;
  }
  if(iw>3 || iw<0)
    {
      printf("\nError:  bad iw flag!  Please check your input deck!\n");
      exit(1);
    }

  if (ng > NGMAX) {
    printf("\nNumber of grids ng cannot exceed NGMAX\n");
    exit(-1);
  }
  dx = l/ng;
  ng1= ng+1;
  k_hi= ng/2; 
  
  // Allocating space for arrays
  nms= (float *)malloc((nsp+1)*sizeof(float));
  ms = (float *)malloc((nsp+1)*sizeof(float));
  qs = (float *)malloc((nsp+1)*sizeof(float));
  ts = (float *)malloc((nsp+1)*sizeof(float));
  
  x_array= (float *)malloc((ng+1)*sizeof(float));
  for (i=0; i<= ng; i++) x_array[i] = i*dx;
  
  rho= (float *)malloc((ng+3)*sizeof(float)); 
  phi= (float *)malloc((ng+2)*sizeof(float)); 
  phik=(float *)malloc((ng+2)*sizeof(float));
  
  k_array= (float *)malloc(ng*sizeof(float));
  for(i=0; i< k_hi; i++) k_array[i]= i*2*PI/l;
  
  e  = (float *)malloc((ng+2)*sizeof(float));
  acc= (float *)malloc((ng+3)*sizeof(float)); 

  t_array= (float *)malloc(HISTMAX*sizeof(float));
  ese= (float *)malloc(HISTMAX*sizeof(float));
  ke = (float *)malloc(HISTMAX*sizeof(float));
  te = (float *)malloc(HISTMAX*sizeof(float));
  
  kes_hist= (float *)malloc((nsp+1)*sizeof(float));
  pxs_hist= (float *)malloc((nsp+1)*sizeof(float));
  esem_hist=(float *)malloc((mmax+1)*sizeof(float));
  
  kes = (float **)malloc(nsp*sizeof(float *));
  for (i=0; i< nsp; i++) 
    kes[i] = (float *)malloc(HISTMAX*sizeof(float));
  
  pxs = (float **)malloc(nsp*sizeof(float *));
  for (i=0; i< nsp; i++) 
    pxs[i] = (float *)malloc(HISTMAX*sizeof(float));
  
  esem = (float **)malloc(mmax*sizeof(float *));
  for (i=0; i< mmax; i++) 
    esem[i] = (float *)malloc(HISTMAX*sizeof(float));
  
  x  = (float *)malloc(MAXPARTICLES*sizeof(float));
  vx = (float *)malloc(MAXPARTICLES*sizeof(float));
  vy = (float *)malloc(MAXPARTICLES*sizeof(float));
  
  vbint= (float *)malloc(NVBINMAX*sizeof(float));
  vbin = (float *)malloc(nsp*NVBINMAX*sizeof(float));
  vbin_inst= (float *)malloc(nsp*NVBINMAX*sizeof(float));
  dvbin = (float *)malloc((nsp+1)*sizeof(float));
  vbinstart = (float *)malloc((nsp+1)*sizeof(float));
  v_array = (float *)malloc( NVBINMAX*nsp * sizeof(float));
  for(i=0; i<nsp*NVBINMAX; i++) vbin_inst[i]= 0.0;

  if (!x || !vx || !vy || !vbint || !vbin_inst || !dvbin || !v_array ) {
    printf("START: Could not get enough memory for x or v's.\n");
    exit(1);
  }
  
  printf(" nsp = %2d     l = %8.5f \n",nsp,l);
  printf(" dt = %4.2f    nt = %4d \n",dt,nt);
  printf(" ng = %5d   iw = %2d   ec = %2d  accum = %4d\n",ng,iw,ec,accum);
  printf(" epsi = %4.2f  a1 = %4.2f  a2 = %4.2f \n",epsi,a1,a2);
  
  for (i=1;i <= nsp;i++) 
    init(&ins[i],&ins[i+1],&ms[i],&qs[i],&ts[i],&nms[i],&vbins[i],&vbins[i+1],&dvbin[i],&vbinstart[i],&nvbin[i]);
  // added vbins to param list
  fclose(InputDeck);
  
  for (i=1; i<= nsp; i++) np[i]= ins[i+1] -ins[i];
  
  for (i=0; i < nsp; i++)
  {
    for (j=0; j < HISTMAX; j++) 
    {
      kes[i][j] = 0.0;
      pxs[i][j] = 0.0;
    }
  }
  rho[1]+=rho[ng1];   // These resolve the periodic boundary conditions.
  rho[2]+=rho[ng+2];
  rho[ng]+=rho[0];
  rho[0]=rho[ng];
  rho[ng+2]=rho[2];
  rho[ng1] = rho[1];
  fields(0);
  
  for (i=1; i <= nsp; i++) {
    setv(ins[i], ins[i+1]-1, qs[i], ms[i], ts[i], &pxs_hist[i], &kes_hist[i]);

    // scale all the velocities  properly
    dvbin[i] *= dt/dx;
    vbinstart[i] *= dt/dx;  
  }
  startvel();
}
*/
/*
history()
{
  int i, j, k;
  static int count=1;
  
  if (--count) return;				// only accum every interval steps
  if (hist_hi >= HISTMAX)			// comb time histories
  {
    for (j=0; j< nsp; j++)
    {
      for (i=1, k=4; i<HISTMAX/4; i++, k+=4)
      {
	kes[j][i] = kes[j][k];
	pxs[j][i] = pxs[j][k];
      }
    }
    for (j=0; j< mmax; j++)
    {
      for (i=1, k=4; i<HISTMAX/4; i++, k+=4)
	esem[j][i] = esem[j][k];
    }
    for (i=1, k=4; i<HISTMAX/4; i++, k+=4)
    {
      ese[i] = ese[k];
      ke[i] = ke[k]; 
      te[i] = te[k];
      t_array[i] = t_array[k];
    }
    hist_hi = i;
    interval *= 4;
  }
  t_array[hist_hi]= t;
  for (i=0; i< mmax; i++) esem[i][hist_hi] = fabs(esem_hist[i+1]) +1e-30;
  
  ke[hist_hi]= 1e-30;
  for (j=0; j< nsp; j++) {
    kes[j][hist_hi] = kes_hist[j+1];
    ke[hist_hi] += kes_hist[j+1];
    pxs[j][hist_hi] = pxs_hist[j+1];
  }
  te[hist_hi] = ke[hist_hi] + ese_hist;
  ese[hist_hi]= ese_hist+ 1e-30;
  hist_hi++;
  count = interval;
}


/**********************************************************************
  velocity()
  This code maintains the velocity distribution code.  
  It works thusly:  I wanted to accumulate velocities in bins for
  ten iterations, then slap up a velocity distribution to be seen
  by the users of xes1.

  To do that I had to play the following tricks: 
  I do all the work in vbin_inst, and I'm always displaying vbin.
  When I've accumulated velocities for accum timesteps
  I copy the current accumulated vbin_inst into vbin.


**************************************************************/
/*
velocity()
{
  int  s,nbinmaxi;
  register int i,j;
  static int count=5;
  float pval;
  float *vsps; 	  // vsps is a pointer to the part of the velocity bin array where the species starts
  float vst,dvt;	// this is the vstart[isp],dv[isp]
  if(!accum) return; // if the accum is set to zero, don't bother making a current velocity distribution profile.
  pval=1.0/accum;

  // This code does the velocity-distribution stuff.
  count--;
  if(!count ) {
    for (j=0; j<=nvbin[1];j++) vbint[j]=0.0;
    for(i=1;i<=nsp;i++) {
      for (j=vbins[i];j<=vbins[i]+nvbin[i];j++) {
	vbin[j]=ms[i]*vbin_inst[j];
	vbin_inst[j]=0.0;
      }
      for (j=0; j<=nvbin[1];j++) vbint[j]+= vbin[j+vbins[i]];
    }
  }
  if( !(count)) count=accum;

  for(i=1;i<=nsp;i++) {
    vsps = & (vbin_inst[vbins[i]] );
    vst=vbinstart[i];
    dvt=dvbin[i];
    nbinmaxi=nvbin[i];
    
    if(nbinmaxi>0)
      for (j=ins[i];j<ins[i+1];j++) {
	s= (vx[j]-vst)/dvt;
	if(s>=0 && s<nbinmaxi) vsps[s]+=pval;
      }	
  }
}
  */
  
/************************************************************************/
/* frand() returns values 0 through 1.                                  */
/* From "Random number generators: good ones are hard to find", S. Park */
/* and K. Miller, Communications of ACM, October 1988, pp 1192-1201.    */
/* This is from page 1195, and is to work on any system for which       */
/* maxint is 2**31-1 or larger. Due earlier to Schrage, as cited by P&M.*/
/*                                                                      */
/* Note: OK values for iseed are 1 through 2**31-2. Give it 0 or 2*31-1 */
/* and it will return the same values thereafter!                       */
/*                                                                      */
/* C version 6/91, Bruce Langdon.                                       */
/*                                                                      */
/* Algorithm replaces seed by mod(a*seed,m). First represent            */
/* seed = q*hi + lo.  Then                                              */
/* a*seed = a*q*hi + lo = (m - r)*hi + a*lo = (a*lo - r*hi) + m*hi,     */
/* and new seed = a*lo - r*hi unless negative; if so, then add m.       */
/*
float frand()
{
  long a = 16807, m = 2147483647, q = 127773, r = 2836;
  long hi, lo;
  static long seed=31207321;
  float fnumb;

  hi = seed/q;
  lo = seed - q*hi;
  seed = a*lo - r*hi;
  // "seed" will always be a legal integer of 32 bits (including sign).
  if(seed <= 0) seed = seed + m;
  fnumb = seed/2147483646.0;

  return(fnumb);
}
/*
/***********************************************************************/
