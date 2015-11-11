/* n must be a power of two. For most PC c's, an int is 16 bits,signed.
   In practice, then, n < 2**15 .                                     */

#define FALSE 0
#define TRUE  1
#include <math.h>

cpft(r,i,n,incp,signp)
float r[], i[], signp;
int n,incp;
{
  int span,rc,inc,is,it,ninc,ij,ji,n1,n2;
  register int k0, k1;
  static float sines[16]={ 0., 0., 0., 0., 0., 0., 0., 0., 
			     0., 0., 0., 0., 0., 0., 0., 0.};
  float r0,r1,i0,i1,t,sgn,c,c0,s,s0,sign();
  
  if (sines[1] != 1.0) {
    sines[1] = 1.0;
    t = atan(1.0);
    for (is=2;is <= 15;is++) {
      sines[is] = sin(t);
      t *= 0.5;
    }
  }
  
  if (n == 1) return;
  
  inc = incp;
  sgn = signp;
  ninc = n*inc;
  span = ninc;
  it = n >> 1;
  if ((it > 16384) || (it < 0)) {
    printf(" n out of range in cpft. \n");
    exit(1);
  }
  for (is=1;is <= 15;is++) {
    if (it == 1) break;
    it >>= 1;
  }
  do {
    span >>= 1;
    k0 = 0;
    do {
      k1 = k0 + span;
      r0 = r[k0 + 1];
      i0 = i[k0 + 1];
      r1 = r[k1 + 1];
      i1 = i[k1 + 1];
      r[k0 + 1] = r0 + r1;
      i[k0 + 1] = i0 + i1;
      r[k1 + 1] = r0 - r1;
      i[k1 + 1] = i0 - i1;
      k0 = k1 + span;
    } while (k0 < ninc);
    if (span == inc) break;
    c0 = 2.0*sines[is]*sines[is];
    is--;
    s = sign(sines[is],sgn);
    s0 = s;
    c = 1.0 - c0;
    k0 = inc;
    do {
      k1 = k0 + span;
      r0 = r[k0 + 1];
      i0 = i[k0 + 1];
      r1 = r[k1 + 1];
      i1 = i[k1 + 1];
      r[k0 + 1] = r0 + r1;
      i[k0 + 1] = i0 + i1;
      r0 -= r1;
      i0 -= i1;
      r[k1 + 1] = c*r0 - s*i0;
      i[k1 + 1] = s*r0 + c*i0;
      k0 = k1 + span;
      if (k0 >= ninc) {
	k1 = k0 - ninc;
	c = -c;
	k0 = span - k1;
	if (k1 >= k0) {
	  k0 += inc;
	  if (k0 >= k1) break;
	  t = s + (s0*c - c0*s);
	  c = c - (c0*c + s0*s);
	  s = t;
	}
      }
    } while(TRUE);
  } while(TRUE);
  n1 = ninc - inc;
  n2 = ninc >> 1;
  rc = ij = ji = 0;
  if (n2 != inc) {
    do {
      ij += inc;
      ji += n2;
      t = r[ij + 1];
      r[ij + 1] = r[ji + 1];
      r[ji + 1] = t;
      t = i[ij + 1];
      i[ij + 1] = i[ji + 1];
      i[ji + 1] = t;
      it = n2;
      do {
	it >>= 1;
	rc -= it;
      } while (rc >= 0);
      rc += (it << 1);
      ji = rc;
      ij += inc;
      if (ij < ji) {
	do {
	  ij = n1 - ij;
	  ji = n1 - ji;
	  t = r[ij + 1];
	  r[ij + 1] = r[ji + 1];
	  r[ji + 1] = t;
	  t = i[ij + 1];
	  i[ij + 1] = i[ji + 1];
	  i[ji + 1] = t;
	} while (ij > n2);
      }
      else if (ij >= n2) break;
    } while(TRUE);
  }
}

float sign(a,b)
float a,b;
{
  if (b >= 0.) {
    if (a >= 0.) return(a);
    else         return(-a);
  } else {
    if (a < 0.) return(a);
    else        return(-a);
  }
}

rpft2(a,b,n,incp)
float a[], b[];
int n,incp;
{
  float rp, rm, ip, im;
  int inc, ninc;
  register int lp, lm;
  
  inc = incp;
  ninc = n*inc;
  a[1] = a[1] + a[1];
  b[1] = b[1] + b[1];
  lp = inc;
  lm = ninc - lp;
  if (lp < lm) {
    do {
      rp = a[lp + 1];
      ip = b[lp + 1];		
      rm = a[lm + 1];
      im = b[lm + 1];
      a[lp + 1] = rm + rp;
      b[lp + 1] = ip + im;
      a[lm + 1] = ip - im;
      b[lm + 1] = rm - rp;
      lp += inc;
      lm = ninc - lp;
    } while (lp < lm);
  }
  if (lp <= ninc) {
    a[lp + 1] = a[lp + 1] + a[lp + 1];
    b[lp + 1] = b[lp + 1] + b[lp + 1];
  }
}

rpfti2(a,b,n,incp)
float a[], b[];
int n,incp;
{
  float ca,sa,cb,sb;
  int inc,ninc;
  register int lp, lm;
  
  inc = incp;
  ninc = n*inc;
  lp = inc;
  lm = ninc - lp;
  if (lp < lm) {
    do {
      ca = a[lp + 1];
      cb = b[lp + 1];		
      sa = a[lm + 1];
      sb = b[lm + 1];
      a[lp + 1] = ca - sb;
      b[lp + 1] = cb + sa;
      a[lm + 1] = ca + sb;
      b[lm + 1] = cb - sa;
      lp += inc;
      lm = ninc - lp;
    } while (lp < lm);
  }
}




