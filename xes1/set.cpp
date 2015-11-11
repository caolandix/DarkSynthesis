
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

setrho(il,iu,q,rhos)
int il,iu;
float q,rhos;
{
   register int i,j;
   float qdx,drho,a,b,c,xii;
   static float dxi,xn;

	qdx = q/dx;
	if ( il == 1 ) {
		for (j=1;j <= ng;j++) rho[j] = rho0; 
		rho[ng1] = 0.0;
		rho[0]=rho[ng+2]=0.0;
		dxi = 1.0/dx;
		xn = ng;
	}
	rho0 -= rhos;
	for (j=1;j <= ng;j++) rho[j] -= rhos;
	switch (iw) {
		case Zero_Order :
			for (i=il;i <= iu;i++) {
				x[i] *= dxi;
				if (x[i] < 0.0) x[i] += xn;
				if (x[i] >= xn) x[i] -= xn;
				j = x[i] + 0.5;
				rho[j + 1] += qdx; 
			}
			break;
		case First_Order :
			for (i=il;i <= iu;i++) {
				x[i] *= dxi;
				if (x[i] < 0.0) x[i] += xn;
				if (x[i] >= xn) x[i] -= xn;
				j = x[i];
				drho = qdx*(x[i] - j);
				rho[j + 1] += qdx - drho; 
				rho[j + 2] += drho;
			}
			break;

		
		      case Quadratic_Spline :
			for (i=il;i <= iu;i++) 
			  {
			    
			    
			    x[i] *= dxi;
			    if (x[i] < 0.0) x[i] += xn;
			    else if (x[i] >= xn) x[i] -= xn;
			    xii=x[i];
			    /*  By looking up x[i] and storing it in xii, save
				three additions--I must do an addition every
				time I use a subscript!  */

			    j = xii + 0.5;    
			    /*  Extract the nearest grid point:
				using truncation to do rounding- j is int. */

			    a=0.75 - sqr(j - xii);  
			    /*  Get the coefficient for the nearest 
				grid point.  It's a function of the distance.*/
			    
			    b=0.5 * sqr( 1.5 -  (j+1) + xii );
			    /*  Get the coefficient for the grid location
				one to the right.  Since (j+2)-xii is aways
				postive the fabs doesn`t need to be there. */
			    
                            
			    rho[j+1]+=a * qdx;
			    rho[j+2]+=b * qdx;
			    rho[j]+=( 1.0 - a - b ) * qdx;
			  }
			  break;
			
		      case Cubic_Spline :
			for (i=il;i<=iu;i++)
			  {
			    x[i] *=dxi;
			    if (x[i] <0.0) x[i] += xn;
			    else if (x[i]>=xn) x[i]-=xn;
			    xii=x[i];
			    j=xii+.5;

			    if ((j-xii)>=0)
			      {
				a=.5*cub(j-xii)-sqr(j-xii)+.6666666667;
				b= -.5*cub(j-1-xii)-sqr(j-1-xii)+.6666666667;
				c= -cub(j+1-xii)/6.0+sqr(j+1-xii)-2*(j+1-xii)+1.3333333;
				rho[j+1]+=a*qdx;
				rho[j+2]+=c*qdx;
				rho[j]+=b*qdx;
				rho[j-1]+=(1.0 -a -b -c) * qdx;
			      }
			    else
			      { 
				a= -.5*cub(j-xii)-sqr(j-xii)+.6666666667;
				b=.5*cub(j+1-xii)-sqr(j+1-xii)+.6666666667;
				c= cub(j-1-xii)/6.0+sqr(j-1-xii)+2*(j-1-xii)+1.3333333;
				rho[j+1]+=a*qdx;
				rho[j+2]+=b*qdx;
				rho[j]+=c*qdx;
				rho[j+3]+=(1.0 -a -b -c) * qdx;
				
			      }
			  }
			break;
			
			
		      default:
       			printf(" Bad iw switch in setrho. \n");
			exit(-1);
			break;
		      }
}

/****************************************************************/

setv(il, iu, q, m, t, p, ke)
int il, iu;
float q, m, t, *p, *ke;
{
	register int i;
	float dtdx, c, s, vxx;
	
	dtdx = dt/dx;
	if (t != 0.0)
	{
		c = 1.0 /sqrt(1.0 + t*t);
		s = c*t;
		for (i=il; i<=iu; i++)
		{
			vxx = vx[i];
			vx[i] =  c*vxx + s*vy[i];
			vy[i] = -s*vxx + c*vy[i];
			vy[i] *= dtdx;
		}
	}
	for (i=il; i<=iu; i++) 
	  vx[i] *= dtdx;
	accel(il, iu, -0.5*q, m, 0.0, p, ke);
}












