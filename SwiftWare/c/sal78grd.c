/****************************************/
/*       member of hydro library        */
/****************************************/
#include <defs.p>
 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * $Id: sal78grd.c,v 1.2 1996/06/15 05:45:57 swift Exp $
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * RCS Log:
 *
 * $Log: sal78grd.c,v $
 * Revision 1.2  1996/06/15 05:45:57  swift
 * Modifications to eliminate compiler warnings with gcc -Wall ...
 *
 * Revision 1.1  1995/10/21 17:26:13  swift
 * Initial revision
 *
 *========================================================================*/
/* function to compute the gradients of Fofonoff's relation (sal78)       */
/*========================================================================*/
/*
   This function computes the salinity from the conductivity ratio, insitu
   temperature, and pressure.  This function is based on eqns(1,2) on p6,7 of
   "Algorithms for computation of fundamental properties of seawater" by
   Fofonoff & Millard, Unesco Technical Papers in Marine Science, No. 44, 53p.
   This function also computes the gradients of the sal78() relation.

      Input:
         R....Conductivity ratio R = C(s,t,p)/C(35,15,0).
         t....Insitu temperature [degree C (IPTS-68)].
         p....Pressure [dbar].

      Output: 
         Dsal78DR....The partial derivative of the sal78() function with
                     respect to the conductivity ratio, (R).  
         Dsal78Dt....The partial derivative of the sal78() function with
                     respect to the insitu temperature, (t).  
         Dsal78Dp....The partial derivative of the sal78() function with
                     respect to the pressure, (p).  

         Each of the above derivatives are computed only if the pointer passed
         to this function is non-NULL.  Thus if only one derivative is needed
         then null pointers can be passed for the other derivatives to avoid
         unnecessary inefficiency.

         This function evaluates the salinity (PSU) as given in eqn(1) on p1
         of the Unesco reference given above and returns this value.

    Check values as given in Fofonoff, et. al. are given in the table below:

        R     t (C)   p (dbar)          Rp        rt         Rt           s
    -----------------------------------------------------------------------    
    1.000    15.000      0.000   1.0000000 1.0000000  1.0000000   35.000000
    1.200    20.000   2000.000   1.0169429 1.1164927  1.0568875   37.245628
    0.650     5.000   1500.000   1.0204864 0.77956585 0.81705885  27.995347

    written by Dana Swift 10/19/95 
*/
double sal78_gradient
(
   double R,
   double t,
   double p,
   double *Dsal78DR,
   double *Dsal78Dt,
   double *Dsal78Dp
)
{
   double a[]={+0.0080,-0.1692,+25.3851,+14.0941,-7.0261,+2.7081};
   double b[]={+0.0005,-0.0056,-0.0066,-0.0375,+0.0636,-0.0144};
   double c[]={+0.6766097,+2.00564e-2,+1.104259e-4,-6.9698e-7,+1.0031e-9};
   double e[]={0,+2.070e-5,-6.370e-10,+3.989e-15};
   double d[]={1,+3.426e-2,+4.464e-4};
   double f[]={+4.215e-1,-3.107e-3};
   double s,Rt,rt,Rp,x,k=0.0162,A,B,C,D,E,F,G,dA,dB,dC,dD,dE,dF,K,DsDx;

   /* evaluate polynomial & rational functions for later use */
   C = dswiftpoly(t,c,4); dC = dswiftpoly_gradient(t,c,4);
   D = dswiftpoly(t,d,2); dD = dswiftpoly_gradient(t,d,2); 
   E = dswiftpoly(p,e,3); dE = dswiftpoly_gradient(p,e,3);
   F = dswiftpoly(t,f,1); dF = dswiftpoly_gradient(t,f,1);
   K = (t-15)/(1+k*(t-15));
 
   /* evaluate eqn(4) on p8 of the Unesco reference given above */
   Rp = 1 + E/(D+R*F);

   /* evaluate eqn(3) on p7 of the Unesco reference given above */
   rt = C;

   /* compute Rt as given on p8 of the Unesco reference given above */
   Rt = R/(Rp*rt); x=sqrt(Rt);

   /* evaluate salinity polynomials */
   A = dswiftpoly(x,a,5); dA = dswiftpoly_gradient(x,a,5); 
   B = dswiftpoly(x,b,5); dB = dswiftpoly_gradient(x,b,5);

   /* evaluate (s) as given by eqn(1) on p6 of the Unesco reference */
   s = A + K*B;

   /* compute Ds/Dx as needed by equations given in the SwiftWare reference */
   DsDx = dA + K*dB;

   /* compute the factor G = (Ds/Dx)(Dx/Drt) in eqn(6-8) of SwiftWare reference */
   G = x*DsDx/2;

   /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
   /* The following section computes the d[sal78(R,t,p)]/dR     */
   /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
   if (Dsal78DR)
   {
      /* compute DRp/DR as given in eqn(10a) of SwiftWare reference */
      double DRpDR = (1-Rp)*F/(D+R*F);

      /* compute Dsal78/DR as given by eqn(6) of SwiftWare reference */
      *Dsal78DR = G*(1/R - DRpDR/Rp);
   }
 
   /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
   /* The following section computes the d[sal78(R,t,p)]/dt     */
   /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
   if (Dsal78Dt)
   {
      /* compute DRp/Dt as given in eqn(10c) of SwiftWare reference */
      double DRpDt = (1-Rp)*(dD+R*dF)/(D+R*F);

      /* compute Drt/Dt as needed in eqn(8) of SwiftWare reference */
      double DrtDt = dC;

      /* compute DK/Dt according to eqn(11) of SwiftWare reference */
      double DKDt = (t-15) ? K*K/((t-15)*(t-15)) : 1;

      /* compute Dsal78/Dt as given by eqn(8) of SwiftWare reference */
      *Dsal78Dt = -G*(DRpDt/Rp + DrtDt/rt) + B*DKDt;
   }

   /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
   /* The following section computes the d[sal78(R,t,p)]/dp     */
   /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
   if (Dsal78Dp)
   {
      /* compute DRp/Dp as given in eqn(10b) of SwiftWare reference */
      double DRpDp = dE/(D+R*F);

      /* compute Dsal78/Dp as given by eqn(7) of SwiftWare reference */
      *Dsal78Dp = -G*(DRpDp/Rp);
   }

   return s;
}
