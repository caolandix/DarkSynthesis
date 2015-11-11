#include "es1.h"

#define Zero_Order           0
#define First_Order          1
#define Quadratic_Spline     2
#define Cubic_Spline         3
#define Momentum_Conserving  0
#define Energy_Conserving    1

#define sqr(x) ((x)*(x))



#define AKPERP               2.405

fields (ith) 
int ith; 
{
  static int ng2=0, ng1=0; 
  static double *ksqi, *sm;
  int kk, km; 
  register int k, j;
  double kdx2, li, hdx, eses, eot, hdxi, dxi, temp, temp1, e0t, kperp2;
  
  if (ng2 == 0) {
    ng2 = ng/2;
    ksqi = (double *)malloc((ng2+1)*sizeof(double));
    sm = (double *)malloc((ng2+1)*sizeof(double));
    ng1 = ng + 1;
    kperp2 = AKPERP*AKPERP*(la/l*la/l); /* a = charge disk radius*/
    for (k=1;k<=ng2;k++) {
      kdx2 = (PI/ng)*k;
      if ((a1 != 0.0) || (a2 != 0.0)) {
	if (k < ng2) temp = tan(kdx2);
	else         temp = 10000.0;
	temp *= temp;
	temp *= temp; /* suspect overflows at k=ng2 */
	temp1 = sin(kdx2);
	temp1 *= temp1;
	sm[k] = exp(a1*temp1 - a2*temp);
	if (sm[k] < 1.0E-10) sm[k] = 0.0;
      }
      else sm[k] = 1.0;
      temp = 2.0*sin(kdx2)/dx;
      temp = temp*temp;
      temp += kperp2;
      ksqi[k] = (epsi/temp)*sm[k]*sm[k];
    }
  }
  hdx = 0.5*dx;
  for (j=1;j <= ng;j++) {
    rho[j] *= hdx;  
		
    e[j] = 0.0;
  }
  cpft(rho,e,ng,1,1.0); 
  rpft2(rho,e,ng,1);  
  rho[1] = eses = phi[1] = 0.0; 
  for (k=2;k <= ng2;k++) {
    kk = ng + 2 - k;
    phi[k] = ksqi[k-1]*rho[k]; 
    phi[kk] = ksqi[k-1]*rho[kk]; 
    eses += rho[k]*phi[k] + rho[kk]*phi[kk];
  }
  phi[ng2+1] = ksqi[ng2]*rho[ng2+1];
  ese_hist = (2.0*eses + rho[ng2+1]*phi[ng2+1])/(2.0*l);
  li = 1.0/l;
  
  for (km=1; km <=mmax; km++) {
    k = km +1;
    if (k ==1) break;
    kk = ng +2 -k;
    esem_hist[km] = (rho[k]*phi[k] + rho[kk]*phi[kk])*li;
    if (k == kk) esem_hist[km] *= 0.25;
  }
  for (k=2; k<=ng2; k++){
    kk = ng-k;
    rho[k] *= sm[k-1];  
    rho[kk] *= sm[k-1]; 
  }
  rho[ng2+1] *= sm[ng2];  
  for (k=1; k <= ng ;k++)
  {
    rho[k] *= li;
    phi[k] *= li;
  }
  
  phik[1] = 1e-30;
  for (k=1;k <=ng2; k++)
  {
    kk = ng +2 -k;
    phik[k] = li*fabs(phi[k]*rho[k] +phi[kk]*rho[kk]) +1e-30; 
  }
  
  rpfti2(phi,rho,ng,1);
  cpft(phi,rho,ng,1,-1.0);
  phi[ng1] = phi[1];
  rho[ng1] = rho[1];
  if (e0 != 0.0) e0t = e0*cos(w0*t);
  else e0t = 0.0;
  switch (ec) {
  case Momentum_Conserving:
    hdxi = 0.5/dx;
    for (j=2;j <= ng;j++) e[j] = (phi[j-1]-phi[j+1])*hdxi + e0t;
    e[1] = (phi[ng]-phi[2])*hdxi + e0t;
    e[ng + 1] = e[1];
    break;
  case Energy_Conserving:
    dxi = 1.0/dx;
    for (j=1;j <= ng;j++) e[j] = (phi[j]-phi[j+1])*dxi + e0t;
    e[ng + 1] = e[1];
    break;
  default:
    printf(" Bad ec switch in fields. \n");
    exit(-1);
    break;
  }
  ael = 1.0;
}


