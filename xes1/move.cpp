// #include "es1.h"
/*
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


move(ilp,iup,q)
int ilp,iup;
float q;

{
  int il,iu;
  register int i, j;
  float xn,qdx,drho;
  float a,b,c,xii;
  float jxii;  // = j-xii:  we use it so much it's worth defining it.
  
  il = ilp;
  iu = iup;
  qdx = q/dx;
  xn = ng;
  switch (iw) 
  {
  case Zero_Order :
    for (i=il;i <= iu;i++) 
    {
      x[i] += vx[i];
      if (x[i] < 0.0) x[i] += xn;
      else if (x[i] >= xn) x[i] -= xn;
      j = x[i] + 0.5;
      rho[j+1] += qdx;  
    }
    break;
  case First_Order :
    for (i=il;i <= iu;i++) 
    {
      x[i] += vx[i];
      if (x[i] < 0.0) x[i] += xn;
      else if (x[i] >= xn) x[i] -= xn;
      j = x[i];
      drho = qdx*(x[i] - j);
      rho[j+1] += qdx - drho; 
      rho[j+2] += drho;		
    }
   break;
  case Quadratic_Spline :
    for (i=il;i <= iu;i++) 
    {
 

      x[i] += vx[i];
      if (x[i] < 0.0) x[i] += xn;
      else if (x[i] >= xn) x[i] -= xn;
      xii=x[i];     // By looking up x[i] and storing it in xii, I save three additions --
            // I must do an addition every time I use a subscript!


      j = xii + 0.5;     // Extract the nearest grid point: using truncation to do rounding- j is int.

      a=0.75 - sqr(j - xii); // Get the coefficient for the nearest  grid point.  It's a function of the distance.

      b=0.5 * sqr( 0.5 - j + xii );
                           // Get the coefficient for the grid location one to the right.
                            
      rho[j+1]+=a * qdx;
      rho[j+2]+=b * qdx;
      rho[j]+=( 1.0 - a - b ) * qdx;
    }

    break;
   

  case Cubic_Spline :
         for (i=il;i<=iu;i++)
           {
	     x[i]+= vx[i];
             if (x[i] <0.0) x[i] += xn;
             else if (x[i]>=xn) x[i]-=xn;
             xii=x[i];
             j=xii+.5;
	     jxii=j-xii;

           if ((jxii)>=0) 
             {

// Below, the commented out assignments were the original weighting functions.
// the actual assignments are optimized versions of the comment assignments.
// a=.5*cub(jxii)-sqr(jxii)+twothirds;
	       a=twothirds + jxii*jxii*( -1.0 + 0.5*jxii); 

//               b= -.5*cub(jxii-1)-sqr(jxii-1)+twothirds;
	       b=onesix+ 0.5*jxii*(1.0+jxii*(1.0 - jxii));
//		 c= -cub(jxii+1)/6.0+sqr(jxii+1)-2*(jxii+1)+1.3333333;
               c=onesix + onesix*jxii*(-3.0+jxii*(3.0-jxii));  

 	       rho[j+1]+=a*qdx;
	       rho[j+2]+=c*qdx;
	       rho[j]+=b*qdx;
	       rho[j-1]+=(1.0 -a -b -c) * qdx;
             }
           else
             { 
//               a= -.5*cub(jxii)-sqr(jxii)+twothirds;
               a=twothirds -jxii*jxii*( 1.0 + 0.5*jxii);
//               b=.5*cub(jxii+1)-sqr(jxii+1)+twothirds;
	       b=onesix + 0.5 * jxii*(-1.0 + jxii*( 1.0 + jxii));
//               c= cub(jxii-1)/6.0+sqr(jxii-1)+2*(jxii-1)+1.3333333;
	       c=onesix+ onesix*jxii*(3+jxii*(3+jxii));

 	       rho[j+1]+=a*qdx;
	       rho[j+2]+=b*qdx;
	       rho[j]+=c*qdx;
	       rho[j+3]+=(1.0 -a -b -c) * qdx;
		
             }

           }
         break;


  default:
    printf("Bad iw switch in move \n");
    exit(-1);
    break;
  }
}
*/
