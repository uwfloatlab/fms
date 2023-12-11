#ifndef SBE41CAL_OOP
#define SBE41CAL_OOP

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * $Id: sbe41cal.cpp,v 1.1.1.1 2010/07/13 17:33:54 swift Exp $
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Copyright (C) 2001 Dana Swift.   Written by Dana Swift.
 *  
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/** RCS log of revisions to the C source code.
 *
 * \begin{verbatim}
 * $Log: sbe41cal.cpp,v $
 * Revision 1.1.1.1  2010/07/13 17:33:54  swift
 * This distribution contains the source code for the Float Mission Simulator
 * used to simulate, debug, and test float firmware.
 *
 * \end{verbatim}
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*========================================================================*/
/*                                                                        */
/*========================================================================*/
class Sbe41Cal
{
   public:
      struct Sbe41TCal {double a[4];};
      struct Sbe41PCal {double pa[3],ptha[3],ptca[3],ptcb[3];};
      struct Sbe41CCal {double a[5],CPcor,CTcor,WBOTC;};
      struct Sbe41CalCoef
      {
            Sbe41TCal TCal;
            Sbe41PCal PCal;
            Sbe41CCal CCal;
      };

   private:
       Sbe41CalCoef sbe;

   public:
      Sbe41Cal(Sbe41CalCoef cal): sbe(cal) {}

      double InvertP(double p,double t,double *n);
      double P(double sigma,double t);
      double InvertT(double t);
      double T(double sigma);
};

#ifdef SBE41CAL_CPP

#include <math.p>
#include <math.h>
#include <utils.oop>

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
double Sbe41Cal::InvertT(double t)
{
   double LnN=13,T=1/dswiftpoly(LnN,sbe.TCal.a,3);

   t += 273.15;
   
   while (1)
   {
      double dTdLnN=-T*T*dswiftpoly_gradient(LnN,sbe.TCal.a,3);
      LnN += (t-T)/dTdLnN; T=1/dswiftpoly(LnN,sbe.TCal.a,3);

      if (fabs(t-T)<0.0001) {break;}
   }

   double sigma=exp(LnN);
   
   return sigma;
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
double Sbe41Cal::T(double sigma)
{
   double LnN = log(sigma);
   double T = 1/dswiftpoly(LnN,sbe.TCal.a,3) - 273.15;
   return T;
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
double Sbe41Cal::P(double sigma,double t)
{
   double x = sigma - dswiftpoly(t,sbe.PCal.ptca,2);
   double n = x*sbe.PCal.ptcb[0]/dswiftpoly(t,sbe.PCal.ptcb,2);
   double P = dswiftpoly(n,sbe.PCal.pa,2);
   return P;
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
double Sbe41Cal::InvertP(double p,double t,double *n)
{
   double N=0;
   double P=dswiftpoly(N,sbe.PCal.pa,2);
      
   while (1)
   {
      double dPdN=dswiftpoly_gradient(N,sbe.PCal.pa,2);
      N += (p-P)/dPdN; P=dswiftpoly(N,sbe.PCal.pa,2);

      if (fabs(p-P)<0.01) {break;}
   }

   double x = N*dswiftpoly(t,sbe.PCal.ptcb,2)/sbe.PCal.ptcb[0];
   double sigma = x + dswiftpoly(t,sbe.PCal.ptca,2);

   if (n) *n=N;
   
   return sigma;
}

/*------------------------------------------------------------------------*/
/* function to numerically invert the Fofonoff's sal78 relation           */
/*------------------------------------------------------------------------*/
double InvertSal78(double p,double t,double s)
{
   double R=NaN;
   
   /* check for breaches in the limits of Fofonoff's relation */
   if (!inRange(-2,t,35) || !inRange(0.2,s,42) || !inRange(0,p,10334))
   {
      message("warning in InvertSal78()...range error: "
              "(0.2,-2,0) < (s,t,p) = (%6.3f,%6.3f,%4.0f) < (42,35,10334)\n",s,t,p);
   }
   else
   {
      // define iteration-termination parameters
      const double MaxSErr=0.0002; const int MaxIterations=500;

      // initialize numerical inversion parameters
      R=1; double dSdR,S=sal78_gradient(R,t,p,&dSdR,NULL,NULL);
   
      for (int n=0;;n++)
      {
         // compute the next iterate of the numerical inversion
         R += (s-S)/dSdR; S=sal78_gradient(R,t,p,&dSdR,NULL,NULL);

         // check termination criteria
         if (fabs(s-S)<MaxSErr) break;

         // check for termination failure
         else if (n>MaxIterations) 
         {
            message("warning in InvertSal78() ... Solution did not converge: "
                    "p=%0.1f t=%0.4f s=%0.4f.\n",p,t,s);
            R=NaN; break;
         }
      }
   }
   
   return R;
}

#endif // SBE41CAL_CPP
#endif // SBE41CAL_OOP
