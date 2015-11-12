// #include "es1.h"
  
// I removed rho0, since it is not used.
/*
init(il1,il2,m,q,t,nm,vbin1,vbin2,dvb,vstart,nvbin)
     int *il1,*il2,*vbin1,*vbin2,*nvbin;
     float *m,*q,*t,*nm,*dvb,*vstart;
{
  float wp= 1.0, wc= 0.0, qm= -1.0, vt1= 0.0, vt2= 0.0, v0=0.0,
        x1= 0.0, v1= 0.0, thetax = 0.0, thetav= 0.0, ddx, x0,
        vmax, dv, vvnv2, vv, fv, df, xs, xsi, theta, lg, vupper,vlower;

  int ngr, i, j, i1, i2, n=128, nlg=1, nv2=0, mode=1,nbins=100;
  char a_char[80];


  *dvb=1.0;  // this is a huge default.

  printf("\n");
  while (fscanf(InputDeck, "%d %d %d %d ", &n, &nv2, &nlg, &mode) < 4)  // added nbins
    fscanf(InputDeck,"%s",a_char);
  while (fscanf(InputDeck, "%g %g %g %g %g %g", &wp, &wc, &qm, &vt1, &vt2, &v0) < 6)
    fscanf(InputDeck,"%s",a_char);
  while (fscanf(InputDeck,"%g %g %g %g", &x1, &v1, &thetax, &thetav) < 4)
    fscanf(InputDeck,"%s",a_char);
  while(fscanf(InputDeck," %d %g %g ",&nbins,&vlower,&vupper) < 3)
    fscanf(InputDeck,"%s",a_char);
  printf("\n");
  printf(" n = %4d  nv2 = %4d  nlg = %4d  mode = %4d \n", 
	 n,nv2,nlg,mode);
  printf(" wp = %6.3f   wc = %6.3f   qm = %6.3f \n",wp,wc,qm);
  printf(" vt1 = %6.3f  vt2 = %6.3f  v0 = %6.3f \n",vt1,vt2,v0);
  printf(" x1 = %6.3f   v1 = %6.3f   thetax = %6.3f   thetav = %6.3f \n",
	 x1,v1,thetax,thetav);
  printf(" nbins = %4d   vlower = %6.3f  vupper = %6.3f ",nbins,vlower,vupper);
  printf("\n");
  
  *t = tan(-0.5*wc*dt);
  *il2 = *il1 + n;
  
  *q = l*wp*wp/(epsi*n*qm);
  *m = *q/qm;
  *nm = n*(*m);
  ngr = n/nlg;
  lg = l/nlg;
  ddx = l/n;


  if(nbins>NVBINMAX) nbins=NVBINMAX;
  if(nbins<2) nbins=2;
  *nvbin=nbins;
  *vbin2= *vbin1 + nbins;
  if(vupper-vlower < 0.0)
	{
	printf("\nError in INIT: vupper must be > vlower! \n");
	exit(1);
	}
  if(vt1<0 ||vt2<0)
	{ printf("\nError in INIT: can't have negative thermal voltages!\n");
	exit(1);
	}
  if(vupper-vlower > 0.0)
	{
	*vstart=vlower;
	*dvb=(vupper-vlower)/nbins;
	}
  else
  if(vt1 + vt2 > 0.0) 
  {
    *vstart= v0 - 5.0*(vt1 + vt2);  
    *dvb = 10.0* (vt1 + vt2) / nbins;  // so that the distribution goes from v0-5*vt to v0+5*vt
   }
  else if (fabs(v0)>0)
  {
    if(v0>0) {
	*vstart=0.0;
	*dvb=2*v0/nbins;
        }
    else {
	*vstart=2.0*v0;
	*dvb= -2*v0/nbins;
        }
  }
  else
  {
    *vstart=0.0;
    *dvb=1/nbins;
  }
  
  // setup v_array for this species
  for(i= *vbin1;i< *vbin2;i++)
	v_array[i]= (*vstart + (i-*vbin1+0.5)*(*dvb));

  for (i=1;i <= ngr;i++) {
    i1 = i - 1 + *il1;
    x0 = ( i - 0.5)*ddx;
    x[i1] = x0;
    vx[i1] = v0;
  }
  if (vt2 != 0.0) 
  {
    vmax = 5.0*vt2;
    dv = 2.0*vmax/(n - 1);
    vvnv2 = 1.0;
    x[*il1] = 0.0;
    for (i=2;i <= n;i++)
    {
      vv = ((i - 1.5)*dv - vmax)/vt2;
      if (nv2 != 0) vvnv2 = pow(vv,(float)nv2);
      fv = vvnv2*exp(-0.5*vv*vv);
      i1 = i - 1 + *il1;
      x[i1] = x[i1 - 1] + ((fv >= 0.0) ? fv : 0.0);
    }
    df = x[i1]/ngr;
    i1 = *il1;
    j = *il1;
    for (i=1;i <= ngr;i++)
    {
      fv = (i - 0.5)*df;
      while (fv >= x[j+1]) {
	j++;
	if (j > (*il2 - 2)) perror("distribution function error");
      }
      vv = dv*(j - *il1 + (fv - x[j])/(x[j+1] - x[j])) - vmax;
      vx[i1] += vv;
      i1++;
    }
    xs = 0.0;
    for (i=1;i <= ngr;i++)
    {
      i1 = i - 1 + *il1;
      x[i1] = xs*lg + 0.5*ddx;
      xsi = 1.0;
      do
      {
	xsi *= 0.5;
	xs -= xsi;
      } while (xs >= 0.0);
      xs += 2.0*xsi;
    }
    i1 = ngr + *il1 - 1;
  }
  if (wc != 0.0) 
  {
    for (i=1; i<=ngr; i++) 
    {
      i1 = i - 1 + *il1;
      vv = vx[i1];
      theta = 2*PI*frand();
      vx[i1] = vv*cos(theta);
      vy[i1] = vv*sin(theta);
    }
  }
  if (nlg != 1)
  {
    j = ngr + 1;
    xs = 0.0;
    for (i=j;i <= n;i+=ngr)
    {
      xs += lg;
      for (j=1;j <= ngr;j++) 
      {
	i1 = j - 1 + *il1;
	i2 = i1 + i - 1;
	x[i2] = x[i1] + xs;
	vx[i2] = vx[i1];
	if (wc != 0.0) vy[i2] = vy[i1];
      }
    }
  }
  if (vt1 != 0.0)
  {
    for (i=1;i <= n;i++)
    {
      i1 = i - 1 + *il1;
      for (j=0; j<12; j++)
      {
	if (wc != 0.0) vy[i1] += vt1*(frand() - 0.5);
	vx[i1] += vt1*(frand() - 0.5);
      }
    }
  }
  for (i=1;i <= n;i++)
  {
    i1 = i - 1 + *il1;
    theta = 2*PI*mode*x[i1]/l;
    x[i1] += x1*cos(theta + thetax);
    vx[i1] += v1*sin(theta + thetav);
  }
  setrho(*il1,*il2 - 1,*q,(*q)*n/l);


}


// all this function does is set up the initial velocity distribution diagnostic to reflect the startup values.
startvel()
{
  int i,j,s,nbinmaxi;
  float *vsps;          // vsps is a pointer to the part of the velocity bin array where the species starts

  float vst,dvt;        // this is the vstart[isp],dv[isp]
  float *temp;


  // This code does the velocity-distribution stuff.
  for(i=1;i<=nsp;i++) {
    vsps = & (vbin[vbins[i]] );
    vst=vbinstart[i];
    dvt=dvbin[i];
    nbinmaxi=nvbin[i];
    for (j=vbins[i];j<=vbins[i]+nvbin[i];j++) vbin[j]=0.0;
    if(nbinmaxi>0&&accum)
      for (j=ins[i];j<ins[i+1];j++) {
	s= (vx[j]-vst)/dvt;
	if(s>=0&&s<nbinmaxi)  vsps[s]+=0.10;
      }   
  }
}
*/
