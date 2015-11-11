#include "es1.h"
#include <xgrafix.h>

/****************************************************************/

InitWindows(argc, argv)
int argc;
char *argv[];
{
  int i, j;
  char **buffer;


  /*********************************************/
  /* Set up each window structure              */
 
  XGSet2D("linlin", "X", "Vx-X Phase Space", "closed", 300, 10, dx, dx/dt,
          False, False, 0.0, l, -3.0, 3.0);

  for (i=nsp; i>=1; i--) XGScat2D(&x[ins[i]], &vx[ins[i]], &np[i], i-1);

  /*********************************************/
  /*********************************************/
  /* Set up each window structure              */
 
  /*  set up  windows for velocity distributions.  */
  buffer = (char **)malloc((nsp+1)*sizeof(char *));
  for(i=1; i<=nsp; i++)
  {
    buffer[i]= (char *)malloc(25*sizeof(char));

    sprintf(buffer[i], "Vy vs Vx species %d", i);

	if(ts[i]){
	  XGSet2D("linlin", "Velocity", buffer[i], "closed", 300, 10, dx/dt, dx/dt,
          False, False,-3.0,3.0, -3.0, 3.0);

	XGScat2D(&vx[ins[i]], &vy[ins[i]], &np[i], i-1); 
	}

  }
  
  /*********************************************/
  if(accum) {
    /*  set up  windows for velocity distributions.  */
    buffer = (char **)malloc((nsp+1)*sizeof(char *));
    for(i=1; i<=nsp; i++) {
      buffer[i]= (char *)malloc(25*sizeof(char));
      sprintf(buffer[i], "Species %d f(Vx)", i);
      
      XGSet2D("linlin", "Velocity", buffer[i], "closed", 700, 400, 1.0, 1.0, True, True, 0.0, 0.0, 0.0, 0.0);
      
      XGCurve(&(v_array[vbins[i]]), &(vbin[vbins[i]]), &(nvbin[i]), i-1);
    }
    /********************************************/
    /*  this graph puts up a curve of ALL the velocity distributions. */
    XGSet2D("linlin","Velocity","f(v) ALL species","closed",700,400,1.0,1.0,True,True, 0.0, 0.0, 0.0, 0.0);
    
    for (i=nsp; i>=1; i--) XGCurve(&(v_array[vbins[i]]), &(vbin[vbins[i]]), &(nvbin[i]), i-1);
    
    /********************************************/
    /*  this graph puts up a curve of ALL the velocity distributions. */
    XGSet2D("linlin","Velocity","f(v) total","closed",700,400,1.0,1.0,True,True, 0.0, 0.0, 0.0, 0.0);
    
    XGCurve(&(v_array[vbins[1]]), vbint, &(nvbin[1]), 3);
    
  }
  /*********************************************/

  XGSet2D("linlin", "X", "rho(x)", "closed", 400, 100, 1.0, 1.0, False, True, 0.0, l, 0.0, 0.0);

  XGCurve(x_array, &rho[1], &ng1, 2);

  /*********************************************/

  XGSet2D("linlin", "X", "E field(x)", "closed", 10, 500, 1.0, 1.0, False, True, 0.0, l, 0.0, 0.0);

  XGCurve(x_array, &e[1], &ng1, 3);

  /*********************************************/

  XGSet2D("linlin", "X", "Potential(x)", "closed", 400, 300, 1.0, 1.0, False, True, 0.0, l, 0.0, 0.0);

  XGCurve(x_array, &phi[1], &ng1, 4);

  /*********************************************/

  XGSet2D("linlog", "k", "Potential(k)", "closed", 600, 300, 1.0, 1.0, True, True, 0.0, 0.0, 0.0, 0.0);

  XGCurve(k_array, &phik[1], &k_hi, 3);

  /*********************************************/

  XGSet2D("linlin", "Time", "Kinetic Energy(t)", "closed", 800, 200,
          1.0, 1.0, True, True, 0.0, 0.0, 0.0, 0.0);
  
  for (i=nsp-1; i>=0; i--) XGCurve(t_array, kes[i], &hist_hi, i);
  XGCurve(t_array, ke, &hist_hi, 4);
  
  /*********************************************/
 
  XGSet2D("linlog", "Time", "Field Energy(t)", "closed", 700, 400, 1.0, 1.0, True, True, 0.0, 0.0, 0.0, 0.0);

  XGCurve(t_array, ese, &hist_hi, 4);

  /*********************************************/

  buffer = (char **)malloc(mmax*sizeof(char *));
  for(i=0; i<mmax; i++)
  {
    buffer[i]= (char *)malloc(25*sizeof(char));
    sprintf(buffer[i], "Mode %d ESE", i+1);
    
    XGSet2D("linlog", "Time", buffer[i], "closed", 700, 400, 1.0, 1.0, True, True, 0.0, 0.0, 0.0, 0.0);

    XGCurve(t_array, esem[i], &hist_hi, 4);
  }

  /*********************************************/

  XGSet2D("linlin", "Time", "Total Energy(t)", "closed", 700, 600, 1.0, 1.0, True, True, 0.0, 0.0, 0.0, 0.0);

  XGCurve(t_array, te, &hist_hi, 4);

  /*********************************************/
} 

/***************************************************************/

Dump(filename)
char *filename;
{

}

/****************************************************************/

Quit()
{

}

/****************************************************************/




