#include "es1.h"

#define Zero_Order   0
#define First_Order  1
#define Quadratic_Spline 2
#define Cubic_Spline 3
#define Momentum_Conserving  0
#define Energy_Conserving    1


#define sqr(x) ((x)*(x))
#define acub(x) ((x)*(x)*fabs(x))
#define cub(x) ((x)*(x)*(x))
#define onesix 0.16666666667
#define twothirds 0.6666666667


accel(ilp, iup, q, m, t, p, ke) 
int ilp, iup; 
float q, m, t, *p, *ke; 
{
  int il,iu,j,ng1,i;
  float a,b,c,xii,dxdt,ae,tem,v1s,v2s,vo,vn,s,aa,vyy,vxx;
  float jxii;  /*  this is j-xii, which is used a lot, this will save additions.*/
  
  il = ilp;
  iu = iup;
  dxdt = dx/dt;
  ae = (q/m)*(dt/dxdt);
  if (t != 0.0) ae *= 0.5;

if (ae != ael)
    { 
    ng1 = ng + 1;
/*    tem = ae/ael;  this does nothing, is not used later */
    for (j=1;j<=ng1;j++) acc[j] = e[j]*ae; 

    acc[0]=ae*e[ng];

		
    acc[ng+2]=ae*e[2];
    acc[ng1]=ae*e[1];  
    ael = ae;
  }
  switch (iw-ec)
  {
     case Zero_Order :
       v1s = v2s = 0.0;
       for (i=il;i<=iu;i++) 
       {
	 j = x[i] +0.5 - ecconst;  /*  ecconst is .5 for energy conserving, 0 for momentum conserving.  */
	 vo = vx[i];
	 vn = vo + acc[j+1]; 
	 v1s += vn;
	 v2s += vn*vo;
	 vx[i] = vn;
       }
       *p = m*v1s*dxdt;
       *ke = 0.5*m*v2s*dxdt*dxdt;
       break;

     case First_Order :
       if (t != 0.0) 
       {
	 s = 2.0*t/(1.0 + t*t);
	 v2s = 0.0;
	 for (i=il;i<=iu;i++)
	 {			
	   
	   xii=x[i]-ecconst+1.0;
	   j = xii; 
	   xii-=1.0; 
	   j-=1;
           /*  the reason for the addition and subtraction of
		1 to xii is to avoid an error condition
		in which the truncation causes it to truncate UP
		instead of round down when 0<= x[i] <0.5.  The modification
		ensures that it gets set to the right value.  */
           
	   aa = acc[j+1] + (xii - j)*(acc[j+2] - acc[j+1]);  
	   vyy = vy[i];
	   vxx = vx[i] - t*vyy + aa;
	   vyy += s*vxx;
	   vxx -= t*vyy;
	   v2s += vxx*vxx + vyy*vyy;
	   vx[i] = vxx + aa;
	   vy[i] = vyy;
	 }
	 *ke = 0.5*m*v2s*dxdt*dxdt;
       }
       else {
	 v1s = v2s = 0.0;
	 for (i=il;i<=iu;i++)
	 {			
	   xii=x[i]-ecconst+1;
	   j = xii;
	   xii-=1.0; 
           j-=1;
           /*  the reason for the addition and subtraction of
		1 to xii is to avoid an error condition
		in which the truncation causes it to truncate UP
		instead of round down when 0<= x[i] <0.5.  The modification
		ensures that it gets set to the right value.  */

	   vo = vx[i];
	   vn = vo + acc[j+1] + (xii - j) * (acc[j+2] - acc[j+1]); 
	   v1s += vn;
	   v2s += vo*vn;
	   vx[i] = vn;
	 }
	 *p = m*v1s*dxdt;
	 *ke = 0.5*m*v2s*dxdt*dxdt;
       }  
       break;
     
     case Quadratic_Spline :
       v1s=v2s=0.0;
       for (i=il;i<=iu;i++)
	 {
	   
	   xii=x[i]-ecconst;   /*  Grab the value of x[i] so we don't have to keep
			    dereferencing a pointer  */
	   j=xii+0.5;   /*  Grab the nearest grid point.  */
	   vo=vx[i];    /*  Grab the value of the current velocity  */



	   a=0.75-sqr(j-xii);
	   b=0.5*sqr(0.5-j+xii);
	   vn=vo + a*acc[j+1] + b * acc[j+2] + (1-a-b)*acc[j];
	   v1s+=vn;
	   v2s+=vn*vo;
	   vx[i]=vn;
	 }
       *p=m*v1s*dxdt;
       *ke = .5*m*v2s*dxdt*dxdt;
	break;

     case Cubic_Spline :
       v1s=v2s=0.0;
       for (i=il;i<=iu;i++)
	 {
	   xii=x[i];
	   j=xii+.5;
	   vo=vx[i];
	   jxii=j-xii;

	  
	   if ((jxii)>=0) 
	     { 
/*  The commented assignments are unoptimized.  The uncommented assignments
   below are optimized to reduce the number of multiplications, etc... */

/*	       a=.5*cub(jxii)-sqr(jxii)+.6666666667;  */
	       a=twothirds + jxii*jxii*( -1.0 + 0.5*jxii); 
/*	       b= -.5*cub(jxii-1)-sqr(jxii-1)+.6666666667;  */
	       b=onesix+ 0.5*jxii*(1.0+jxii*(1.0 - jxii));
/*	       c= -cub(jxii+1)/6.0+sqr(jxii+1)-2*(jxii+1)+1.3333333;  */
               c=onesix + onesix*jxii*(-3.0+jxii*(3.0-jxii));  
	       vn =vo+a*acc[j+1]+b*acc[j]+c*acc[j+2]+(1.0-a-b-c)*acc[j-1];
	     }
	   else 
	     { 

/*	       a= -.5*cub(jxii)-sqr(jxii)+.6666666667;  */
               a=twothirds -jxii*jxii*( 1.0 + 0.5*jxii);

/*	       b=.5*cub(jxii+1)-sqr(jxii+1)+.6666666667;  */
	       b=onesix + 0.5 * jxii*(-1.0 + jxii*( 1.0 + jxii));

/*	       c= cub(jxii-1)/6.0+sqr(jxii-1)+2*(jxii-1)+1.3333333;  */
	       c=onesix+ onesix*jxii*(3+jxii*(3+jxii));

	       vn =vo+a*acc[j+1]+b*acc[j+2]+c*acc[j]+(1.0-a-b-c)*acc[j+3];
	     }
	   v1s+=vn;
	   v2s+=vn*vo;
	   vx[i]=vn;
	 }
       *p=m*v1s*dxdt;
       *ke=.5*m*v2s*dxdt*dxdt;
       break;

  
     
     default:
       printf(" Bad iw switch in accel. \n");
       exit(-1);
       break;
  }
}
