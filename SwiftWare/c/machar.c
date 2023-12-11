#include <math.h>

#ifndef PRECISION
   #define PRECISION float
   #define MACHAR machar
#endif

#define CONV(i) ((PRECISION)(i))

void dmachar(int *ibeta,int *it,int *irnd,int *ngrd,int *machep,
             int *negep,int *iexp,int *minexp,int *maxexp,double *eps,
             double *epsneg,double *xmin,double *xmax);
void machar(int *ibeta, int *it, int *irnd, int *ngrd,int *machep,
            int *negep, int *iexp, int *minexp, int *maxexp, float *eps,
            float *epsneg, float *xmin, float *xmax);


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * $Id: machar.c,v 1.1.1.1 2010/07/13 17:33:54 swift Exp $
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * RCS Log:
 *
 * $Log: machar.c,v $
 * Revision 1.1.1.1  2010/07/13 17:33:54  swift
 * This distribution contains the source code for the Float Mission Simulator
 * used to simulate, debug, and test float firmware.
 *
 * Revision 1.1.1.1  2003/11/12 23:22:58  swift
 * Apf9 firmware for a 260ml Apex with SBE41 CTD.
 *
 * Revision 1.2  2001/05/13 10:38:45  navo
 * Modifications for porting from UW to NAVO.
 *
 * Revision 1.1  2001/05/04 04:23:29  navo
 * Initial revision
 *
 *========================================================================*/
/* function to ferret out machine properties                              */
/*========================================================================*/
void MACHAR(int *ibeta, int *it, int *irnd, int *ngrd, int *machep, int *negep,
   int *iexp, int *minexp, int *maxexp, PRECISION *eps, PRECISION *epsneg,
   PRECISION *xmin, PRECISION *xmax)
{
   int i,itemp,iz,j,k,mx,nxres;
   PRECISION a,b,beta,betah,betain,one,t,temp,temp1,tempa,two,y,z,zero;

   one=CONV(1);
   two=one+one;
   zero=one-one;
   a=one;
   do {
      a += a;
      temp=a+one;
      temp1=temp-a;
   } while (temp1-one == zero);
   b=one;
   do {
      b += b;
      temp=a+b;
      itemp=(int)(temp-a);
   } while (itemp == 0);
   *ibeta=itemp;
   beta=CONV(*ibeta);
   *it=0;
   b=one;
   do {
      ++(*it);
      b *= beta;
      temp=b+one;
      temp1=temp-b;
   } while (temp1-one == zero);
   *irnd=0;
   betah=beta/two;
   temp=a+betah;
   if (temp-a != zero) *irnd=1;
   tempa=a+beta;
   temp=tempa+betah;
   if (*irnd == 0 && temp-tempa != zero) *irnd=2;
   *negep=(*it)+3;
   betain=one/beta;
   a=one;
   for (i=1;i<=(*negep);i++) a *= betain;
   b=a;
   for (;;) {
      temp=one-a;
      if (temp-one != zero) break;
      a *= beta;
      --(*negep);
   }
   *negep = -(*negep);
   *epsneg=a;
   *machep = -(*it)-3;
   a=b;
   for (;;) {
      temp=one+a;
      if (temp-one != zero) break;
      a *= beta;
      ++(*machep);
   }
   *eps=a;
   *ngrd=0;
   temp=one+(*eps);
   if (*irnd == 0 && temp*one-one != zero) *ngrd=1;
   i=0;
   k=1;
   z=betain;
   t=one+(*eps);
   nxres=0;
   for (;;) {
      y=z;
      z=y*y;
      a=z*one;
      temp=z*t;
      if (a+a == zero || fabs(z) >= y) break;
      temp1=temp*betain;
      if (temp1*beta == z) break;
      ++i;
      k += k;
   }
   if (*ibeta != 10) {
      *iexp=i+1;
      mx=k+k;
   } else {
      *iexp=2;
      iz=(*ibeta);
      while (k >= iz) {
         iz *= *ibeta;
         ++(*iexp);
      }
      mx=iz+iz-1;
   }
   for (;;) {
      *xmin=y;
      y *= betain;
      a=y*one;
      temp=y*t;
      if (a+a != zero && fabs(y) < *xmin) {
         ++k;
         temp1=temp*betain;
         if (temp1*beta == y && temp != y) {
            nxres=3;
            *xmin=y;
            break;
         }
      }
      else break;
   }
   *minexp = -k;
   if (mx <= k+k-3 && *ibeta != 10) {
      mx += mx;
      ++(*iexp);
   }
   *maxexp=mx+(*minexp);
   *irnd += nxres;
   if (*irnd >= 2) *maxexp -= 2;
   i=(*maxexp)+(*minexp);
   if (*ibeta == 2 && !i) --(*maxexp);
   if (i > 20) --(*maxexp);
   if (a != y) *maxexp -= 2;
   *xmax=one-(*epsneg);
   if ((*xmax)*one != *xmax) *xmax=one-beta*(*epsneg);
   *xmax /= (*xmin*beta*beta*beta);
   i=(*maxexp)+(*minexp)+3;
   for (j=1;j<=i;j++) {
      if (*ibeta == 2) *xmax += *xmax;
      else *xmax *= beta;
   }
}
#undef CONV
