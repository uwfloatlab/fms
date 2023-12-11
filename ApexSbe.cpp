#ifndef APEXSBE_OOP
#define APEXSBE_OOP

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * $Id: ApexSbe.cpp,v 1.1.1.1 2010/07/13 17:33:54 swift Exp $
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
 * $Log: ApexSbe.cpp,v $
 * Revision 1.1.1.1  2010/07/13 17:33:54  swift
 * This distribution contains the source code for the Float Mission Simulator
 * used to simulate, debug, and test float firmware.
 *
 * \end{verbatim}
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define ApexSbeChangeLog "$RCSfile: ApexSbe.cpp,v $  $Revision: 1.1.1.1 $  $Date: 2010/07/13 17:33:54 $"

#include <ParaSight.oop>
#include <HydroObs.oop>
#include <regex.h>
#include <assert.h>

#define LEADER  "ApexSbe Agent for the ParaSight Interface [SwiftWare]"
#define VERSION "$Revision: 1.1.1.1 $  $Date: 2010/07/13 17:33:54 $"

/*========================================================================*/
/*                                                                        */
/*========================================================================*/
class ApexSbe: public ParaSight
{
   // data members
   private:

      float M;          // Float mass
      float Pbot;       // Bottom pressure
      float Po;         // Target pressure
      float To;         // Insitu ocean temperature at target pressure
      float So;         // Insitu ocean salinity at target pressure
      float Vo;         // Insitu volume of float at target pressure
      int Co;           // Piston position when neutrally buoyant at target pressure

      float dLnVdp;     // compressibility of float
      float dLnVdt;     // thermal expansibility of float
      float dLnVdc;     // buoyancy generation coefficient of buoyancy engine

      time_t t;         // the time when the most recent pressure was determined
      float  p;         // the most recent determination of pressure;
      
   //function members
   public:

      // initializer constructor for the ApexSbe 
      ApexSbe(float M,float Po,float To,float So,float dLnVdp,float dVdc,int Co,float Pbot=NaN());

      // function to compute the float's buoyancy in ocean water
      float Buoyancy(float P,int C, Hydrography &sea) const;

      // function to compute the float's bouyancy-induced vertical velocity
      float dPdt(float P,int C, Hydrography &sea) const;

      // function to determine the pressure where the float is neutrally buoyant
      float NeutralP(int C, Hydrography &sea) const;

      // function to determine the current pressure of the float
      float P(Hydrography &sea,time_t wait=10000);

      // function to set the current pressure
      void P(float p) {this->p=(p>Pbot)?Pbot:p; t=time(NULL);}
      
      // function to compute the volume of the float
      float Volume(float P,float T,int C) const;
};

#ifdef APEXSBE_CPP

/*------------------------------------------------------------------------*/
/* initializer constructor for the ApexSbe                                */
/*------------------------------------------------------------------------*/
ApexSbe::ApexSbe(float M,float Po,float To,float So,float dLnVdp,float dVdc,int Co,float Pbot):
      t(0), p(NaN())
{
   // log the software LEADER
   msg("ApexSbe::ApexSbe()",LEADER);

   // log the software revision
   msg("ApexSbe::ApexSbe()",VERSION);

   // initialize data members
   this->M=M; this->Po=Po; this->To=To; this->So=So;
   this->dLnVdp=dLnVdp; this->Co=Co; this->Pbot=Pbot;

   // compute insitu density at target depth
   float Ro = 1.0 + eqstate(So,To,Po)/1000;

   // compute insitu volume of float at target pressure
   Vo = M/Ro;

   // compute buoyancy generation coefficient of buoyancy engine
   dLnVdc = dVdc/Vo;

   // initialize the thermal expansibility of float (per C)
   dLnVdt = 6.900e-05; 
}

/*------------------------------------------------------------------------*/
/* function to compute the float's buoyancy in ocean water                */
/*------------------------------------------------------------------------*/
float ApexSbe::Buoyancy(float P, int C, Hydrography &sea) const
{
   float B=NaN();
   
   // log that a negative pressure was encountered
   if (P<0) {msg("ApexSbe::Buoyancy()","Negative pressure (%g dbar) "
                 "adjusted to zero.",P); P=0;}

   // make sure that the pressure is finite
   if (finite(P)) 
   {
      // compute the net buoyancy of the float
      float Rho=sea.Rho(P), T=sea.T(P), V=Volume(P,T,C); B=(Rho*V - M);
   }

   // log an error
   else {msg("ApexSbe::Buoyancy()","Error: P=NaN");}
      
   return B;
}

/*------------------------------------------------------------------------*/
/* function to compute the float's bouyancy-induced vertical velocity     */
/*------------------------------------------------------------------------*/
float ApexSbe::dPdt(float P,int C, Hydrography &sea) const
{
   static const float Wcal=0.08; // Calibration velocity (dbar/s)
   static const float Wmax=0.15; // Maximum velocity (dbar/s)
   static const float Bcal=Buoyancy(Po,Co+25,sea);
   static const float m = Bcal/(M*atanh(-Wcal/Wmax));
   float dPdt = NaN();
   
   // log that a negative pressure was encountered
   if (P<0) {msg("ApexSbe::dPdt()","Negative pressure (%g dbar) "
                 "adjusted to zero.",P);P=0;}
   
   // make sure that the pressure is finite
   if (finite(P))
   {
      // compute the buoyancy force on the float
      float B = Buoyancy(P,C,sea);

      // compute the vertical velocity
      dPdt = Wmax*tanh(B/(M*m));

      // guard against floats flying into the atmosphere
      if (dPdt<0 && P<=0) dPdt=0;

      // guard against floats tunneling into the ocean bottom
      if (finite(Pbot) && dPdt>0 && P>=Pbot) dPdt=0;
   }

   // log an error
   else {msg("ApexSbe::dPdt()","Error: P=NaN");}
      
   return dPdt;
}

/*------------------------------------------------------------------------*/
/* function to determine the pressure where the float is neutrally buoyant*/
/*------------------------------------------------------------------------*/
float ApexSbe::NeutralP(int C, Hydrography &sea) const
{
   const float dPmax=1.0,Bmax=0.5;
   bool status=false;
   float P=sea.Pmin(),B=Buoyancy(P,C,sea),Po=sea.Pmax(),Bo=Buoyancy(Po,C,sea),dBdP=1.0;
   unsigned int N=0,Nmax=300;

   while (1)
   {
      // estimate the buoyancy gradient
      if (fabs(P-Po)>dPmax && fabs(B-Bo)>Bmax) {dBdP = (B-Bo)/(P-Po);} else dBdP=1.0;
      
      // save the current estimates
      Po=P; Bo=B; P-=B/dBdP;

      // check if the estimate is too shallow
      if (P<sea.Pmin())
      {
         // reset the pressure to the minimum in the hydrographic profile
         P=sea.Pmin();

         // check if the last iteration also yielded the mimimum pressure
         if (Po==sea.Pmin())
         {
            // check if the profile reaches the surface
            if (sea.Pmin()>0) {msg("ApexSbe::NeutralP()","Hydrographic profile "
                                   "doesn't extend to surface.");}

            // signal success
            else status=true;

            break;
         } 
      }

      // check if the estimate is too deep 
      else if (P>sea.Pmax())
      {
         // reset the pressure to the maximum in the hydrographic profile
         P=sea.Pmax();

         // check if the last iteration also yielded the maximum pressure
         if (Po==sea.Pmax())
         {
            // make a log entry that the float is too deep
            msg("ApexSbe::NeutralP()","Neutral pressure is deeper "
                "than the hydrographic profile extends.");
            goto Err;
         }
      }

      // compute the buoyancy at the current pressure estimate
      B=Buoyancy(P,C,sea);

      // check convergence conditions
      if (fabs(P-Po)<=dPmax && fabs(B)<=Bmax) {status=true; break;}

      // bail out if the number of iterations exceeds Nmax
      N++; if (N>Nmax) {msg("ApexSbe::NeutralP()","Convergence failure."); goto Err;}
   } 

   // make a log entry if the neutral pressure wasn't found
   Err: if (!status) msg("ApexSbe::NeutralP()","Neutral pressure not found.");
   
   return P;
}

/*------------------------------------------------------------------------*/
/* function to determine the current pressure of the float                */
/*------------------------------------------------------------------------*/
float ApexSbe::P(Hydrography &sea,time_t wait)
{
   // get the current time (sec)
   time_t now = time(NULL);

   // compute the number of seconds since the last pressure determination
   time_t dt=(now-t);

   // get the piston position
   int C = PistonExtension();

   // get the neutral pressure
   float Pn=NeutralP(C,sea);

   // compute the vertical ascent
   float dpdt=NaN();

   // check if the neutral pressure is NaN 
   if (!finite(Pn)) p=NaN();

   // check if the elapsed time exceeds the buoyancy time scale
   else if (dt>wait || isnan(p)) {p=Pn; dpdt=dPdt(p,C,sea);}

   // compute the current pressure
   else
   {
      // compute the vertical ascent
      dpdt=dPdt(p,C,sea);

      // compute the estimate of the current pressure
      float P = p + dpdt*dt; p=P;

      // make sure the float remains in the water
      if (P<0) p=0;

      // check if the computed pressure has over-shot the neutral pressure on ascent
      if (P<Pn && dpdt<=0) p=Pn;

      // check if the computed pressure has over-shot the neutral pressure on descent
      if (P>Pn && dpdt>=0) p=Pn;
      
      // if the computed pressure is NaN then set the pressure to the neutral pressure
      if (!finite(P)) p=Pn;
   }

   // set the time-register to the current time
   t=now;

   // check if the computed pressure is deeper than the bottom depth
   if (p>Pbot && finite(Pbot)) p=Pbot;

   // log an entry
   msg("ApexSbe::P()","Piston extension(%3d)  neutral pressure(%6.1fdbar)  "
       "pressure(%7.2fdbar),  ascent rate(%6.2fmbar/s)   time(%lds)",C,Pn,p,dpdt*100,t);
   
   return p;
}

/*------------------------------------------------------------------------*/
/* function to compute the volume of the float                            */
/*------------------------------------------------------------------------*/
float ApexSbe::Volume(float P,float T,int C) const
{
   // log that a negative pressure was encountered
   if (P<0) {msg("ApexSbe::Volume()","Negative pressure (%g dbar) "
                 "adjusted to zero.",P); P=0;}

   // compute the volume of the float under insitu conditions
   float V = Vo*(1 + dLnVdp*(P-Po) + dLnVdt*(T-To) + dLnVdc*(C-Co));

   return V;
}

#endif // APEXSBE_OOP
#endif // APEXSBE_CPP
#undef LEADER
#undef VERSION
