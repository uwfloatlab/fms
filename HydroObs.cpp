#ifndef HYDROOBS_OOP
#define HYDROOBS_OOP

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * $Id: HydroObs.cpp,v 1.1.1.1 2010/07/13 17:33:54 swift Exp $
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
 * $Log: HydroObs.cpp,v $
 * Revision 1.1.1.1  2010/07/13 17:33:54  swift
 * This distribution contains the source code for the Float Mission Simulator
 * used to simulate, debug, and test float firmware.
 *
 * \end{verbatim}
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <defs.oop>
#include <lsprf.oop>

struct HydroObs {float p,t,s,rho;};

/*========================================================================*/
/*                                                                        */
/*========================================================================*/
class Hydrography
{
   // data members
   protected:

      // define an array of hydrographic observation
      LSplineProfile t,s;
      
   // function members
   public:

      // virtual destructor
      virtual ~Hydrography(void) {}
      
      // function to return the number of points in the profile
      unsigned NPnt(void) {return t.NPnt();}
      
      // function to return the (i)th pressure in the profile
      double P(unsigned int i) {return t.x[i];}
      
      // function to return the maximum pressure in the profile
      double Pmax(void) const {return t.xmax;}

      // function to return the minimum pressure in the profile
      double Pmin(void) const {return t.xmin;}

      virtual void Properties(ostream &dest)=0;
      
      // function to compute the insitu density at a given pressure
      double Rho(float p);

      // function to compute the salinity at a given pressure
      double S(float p);

      // function to compute the temperature at a given pressure
      double T(float p);
};

/*========================================================================*/
/*                                                                        */
/*========================================================================*/
class ArabianSeaHydrography: public Hydrography
{
   // function members
   public:

      // initialization constructor
      ArabianSeaHydrography(void);

      // function to print properties of the profile
      void Properties(ostream &dest=cout);
};

/*========================================================================*/
/*                                                                        */
/*========================================================================*/
class BayOfBengalHydrography: public Hydrography
{
   // function members
   public:

      // initialization constructor
      BayOfBengalHydrography(void);

      // function to print properties of the profile
      void Properties(ostream &dest=cout);
};

/*========================================================================*/
/*                                                                        */
/*========================================================================*/
class BlackSeaHydrography: public Hydrography
{
   // function members
   public:

      // initialization constructor
      BlackSeaHydrography(void);

      // function to print properties of the profile
      void Properties(ostream &dest=cout);
};

/*========================================================================*/
/*                                                                        */
/*========================================================================*/
class GulfOfMexicoHydrography: public Hydrography
{
   // function members
   public:

      // initialization constructor
      GulfOfMexicoHydrography(void);

      // function to print properties of the profile
      void Properties(ostream &dest=cout);
};

/*========================================================================*/
/*                                                                        */
/*========================================================================*/
class HawaiiPacificHydrography: public Hydrography
{
   // function members
   public:

      // initialization constructor
      HawaiiPacificHydrography(void);

      // function to print properties of the profile
      void Properties(ostream &dest=cout);
};

/*========================================================================*/
/*                                                                        */
/*========================================================================*/
class IndianOceanHydrography: public Hydrography
{
   // function members
   public:

      // initialization constructor
      IndianOceanHydrography(void);

      // function to print properties of the profile
      void Properties(ostream &dest=cout);
};

/*========================================================================*/
/*                                                                        */
/*========================================================================*/
class JapanSeaHydrography: public Hydrography
{
   // function members
   public:

      // initialization constructor
      JapanSeaHydrography(void);

      // function to print properties of the profile
      void Properties(ostream &dest=cout);
};

/*========================================================================*/
/*                                                                        */
/*========================================================================*/
class KurishioHydrography: public Hydrography
{
   // function members
   public:

      // initialization constructor
      KurishioHydrography(void);

      // function to print properties of the profile
      void Properties(ostream &dest=cout);
};

/*========================================================================*/
/*                                                                        */
/*========================================================================*/
class LaboradorSeaHydrography: public Hydrography
{
   // function members
   public:

      // initialization constructor
      LaboradorSeaHydrography(void);

      // function to print properties of the profile
      void Properties(ostream &dest=cout);
};

/*========================================================================*/
/*                                                                        */
/*========================================================================*/
class MedSeaHydrography: public Hydrography
{
   // function members
   public:

      // initialization constructor
      MedSeaHydrography(void);

      // function to print properties of the profile
      void Properties(ostream &dest=cout);
};

/*========================================================================*/
/*                                                                        */
/*========================================================================*/
class OkhotskSeaHydrography: public Hydrography
{
   // function members
   public:

      // initialization constructor
      OkhotskSeaHydrography(void);

      // function to print properties of the profile
      void Properties(ostream &dest=cout);
};

/*========================================================================*/
/*                                                                        */
/*========================================================================*/
class OkhotskSeaIceHydrography: public Hydrography
{
   // function members
   public:

      // initialization constructor
      OkhotskSeaIceHydrography(void);

      // function to print properties of the profile
      void Properties(ostream &dest=cout);
};

/*========================================================================*/
/*                                                                        */
/*========================================================================*/
class RossSeaHydrography: public Hydrography
{
   // function members
   public:

      // initialization constructor
      RossSeaHydrography(void);

      // function to print properties of the profile
      void Properties(ostream &dest=cout);
};

/*========================================================================*/
/*                                                                        */
/*========================================================================*/
class RossSeaIceHydrography: public Hydrography
{
   // function members
   public:

      // initialization constructor
      RossSeaIceHydrography(void);

      // function to print properties of the profile
      void Properties(ostream &dest=cout);
};

/*========================================================================*/
/*                                                                        */
/*========================================================================*/
class SargassoHydrography: public Hydrography
{
   // function members
   public:

      // initialization constructor
      SargassoHydrography(void);

      // function to print properties of the profile
      void Properties(ostream &dest=cout);
};

/*========================================================================*/
/*                                                                        */
/*========================================================================*/
class SargassoModeWaterHydrography: public Hydrography
{
   // function members
   public:

      // initialization constructor
      SargassoModeWaterHydrography(void);

      // function to print properties of the profile
      void Properties(ostream &dest=cout);
};

/*========================================================================*/
/*                                                                        */
/*========================================================================*/
class SouthPacificNoppHydrography: public Hydrography
{
   // function members
   public:

      // initialization constructor
      SouthPacificNoppHydrography(void);

      // function to print properties of the profile
      void Properties(ostream &dest=cout);
};

/*========================================================================*/
/*                                                                        */
/*========================================================================*/
class SubtropicalNePacificHydrography: public Hydrography
{
   // function members
   public:

      // initialization constructor
      SubtropicalNePacificHydrography(void);

      // function to print properties of the profile
      void Properties(ostream &dest=cout);
};

/*========================================================================*/
/*                                                                        */
/*========================================================================*/
class TropicalAtlanticHydrography: public Hydrography
{
   // function members
   public:

      // initialization constructor
      TropicalAtlanticHydrography(void);

      // function to print properties of the profile
      void Properties(ostream &dest=cout);
};

/*========================================================================*/
/*                                                                        */
/*========================================================================*/
class TropicalPacificHydrography: public Hydrography
{
   // function members
   public:

      // initialization constructor
      TropicalPacificHydrography(void);

      // function to print properties of the profile
      void Properties(ostream &dest=cout);
};

#ifdef HYDROOBS_CPP

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
void ArabianSeaHydrography::Properties(ostream &dest)
{
   fprintf(dest,"$ Hydrography:    %s\n"
             "$    %6s %7s %7s %10s\n"
             "$    %6s %7s %7s %10s\n",
             "Arabian Sea (21.50N 63.41E) Dec-21-1986",
             "pres","temp","sal","density",
             "dbar","C","PSU","g/ml"
             );

   for (unsigned int i=0; i<t.NPnt(); i++)
   {
      double rho = 1 + eqstate(s.y[i],t.y[i],t.x[i])/1000;

      fprintf(dest,"$    %6.1f %7.3f %7.3f %10.6f\n",
                t.x[i],t.y[i],s.y[i],rho);
   }
   fprintf(dest,"$\n");
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
void BayOfBengalHydrography::Properties(ostream &dest)
{
   fprintf(dest,"$ Hydrography:    %s\n"
             "$    %6s %7s %7s %10s\n"
             "$    %6s %7s %7s %10s\n",
             "BayOfBengal (14.74N 81.82E) Nov-09-2002",
             "pres","temp","sal","density",
             "dbar","C","PSU","g/ml"
             );

   for (unsigned int i=0; i<t.NPnt(); i++)
   {
      double rho = 1 + eqstate(s.y[i],t.y[i],t.x[i])/1000;

      fprintf(dest,"$    %6.1f %7.3f %7.3f %10.6f\n",
                t.x[i],t.y[i],s.y[i],rho);
   }
   fprintf(dest,"$\n");
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
void BlackSeaHydrography::Properties(ostream &dest)
{
   fprintf(dest,"$ Hydrography:    %s\n"
             "$    %6s %7s %7s %10s\n"
             "$    %6s %7s %7s %10s\n",
             "Black Sea (42.51N 30.74E) May-26-2001",
             "pres","temp","sal","density",
             "dbar","C","PSU","g/ml"
             );

   for (unsigned int i=0; i<t.NPnt(); i++)
   {
      double rho = 1 + eqstate(s.y[i],t.y[i],t.x[i])/1000;

      fprintf(dest,"$    %6.1f %7.3f %7.3f %10.6f\n",
                t.x[i],t.y[i],s.y[i],rho);
   }
   fprintf(dest,"$\n");
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
void GulfOfMexicoHydrography::Properties(ostream &dest)
{
   fprintf(dest,"$ Hydrography:    %s\n"
             "$    %6s %7s %7s %10s\n"
             "$    %6s %7s %7s %10s\n",
             "Gulf of Mexico (24.93N, 84.58W) Nov-12-1983",
             "pres","temp","sal","density",
             "dbar","C","PSU","g/ml"
             );

   for (unsigned int i=0; i<t.NPnt(); i++)
   {
      double rho = 1 + eqstate(s.y[i],t.y[i],t.x[i])/1000;

      fprintf(dest,"$    %6.1f %7.3f %7.3f %10.6f\n",
                t.x[i],t.y[i],s.y[i],rho);
   }
   fprintf(dest,"$\n");
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
void HawaiiPacificHydrography::Properties(ostream &dest)
{
   fprintf(dest,"$ Hydrography:    %s\n"
             "$    %6s %7s %7s %10s\n"
             "$    %6s %7s %7s %10s\n",
             "Hawaii-Pacific (21.85N, 155.03W) Sep-09-1973",
             "pres","temp","sal","density",
             "dbar","C","PSU","g/ml"
             );

   for (unsigned int i=0; i<t.NPnt(); i++)
   {
      double rho = 1 + eqstate(s.y[i],t.y[i],t.x[i])/1000;

      fprintf(dest,"$    %6.1f %7.3f %7.3f %10.6f\n",
                t.x[i],t.y[i],s.y[i],rho);
   }
   fprintf(dest,"$\n");
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
void IndianOceanHydrography::Properties(ostream &dest)
{
   fprintf(dest,"$ Hydrography:    %s\n"
             "$    %6s %7s %7s %10s\n"
             "$    %6s %7s %7s %10s\n",
             "S Indian Ocean (17.95S, 94.81E) Apr-04-2007 Prf:0009.001",
             "pres","temp","sal","density",
             "dbar","C","PSU","g/ml"
             );

   for (unsigned int i=0; i<t.NPnt(); i++)
   {
      double rho = 1 + eqstate(s.y[i],t.y[i],t.x[i])/1000;

      fprintf(dest,"$    %6.1f %7.3f %7.3f %10.6f\n",
                t.x[i],t.y[i],s.y[i],rho);
   }
   fprintf(dest,"$\n");
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
void JapanSeaHydrography::Properties(ostream &dest)
{
   fprintf(dest,"$ Hydrography:    %s\n"
             "$    %6s %7s %7s %10s\n"
             "$    %6s %7s %7s %10s\n",
             "Japan Sea (39.33N, 133.90E) Sep-09-1999 JES float 195",
             "pres","temp","sal","density",
             "dbar","C","PSU","g/ml"
             );

   for (unsigned int i=0; i<t.NPnt(); i++)
   {
      double rho = 1 + eqstate(s.y[i],t.y[i],t.x[i])/1000;

      fprintf(dest,"$    %6.1f %7.3f %7.3f %10.6f\n",
                t.x[i],t.y[i],s.y[i],rho);
   }
   fprintf(dest,"$\n");
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
void KurishioHydrography::Properties(ostream &dest)
{
   fprintf(dest,"$ Hydrography:    %s\n"
             "$    %6s %7s %7s %10s\n"
             "$    %6s %7s %7s %10s\n",
             "Kurishio (33.83N, 141.20W) Feb-14-1988",
             "pres","temp","sal","density",
             "dbar","C","PSU","g/ml"
             );

   for (unsigned int i=0; i<t.NPnt(); i++)
   {
      double rho = 1 + eqstate(s.y[i],t.y[i],t.x[i])/1000;

      fprintf(dest,"$    %6.1f %7.3f %7.3f %10.6f\n",
                t.x[i],t.y[i],s.y[i],rho);
   }
   fprintf(dest,"$\n");
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
void LaboradorSeaHydrography::Properties(ostream &dest)
{
   fprintf(dest,"$ Hydrography:    %s\n"
             "$    %6s %7s %7s %10s\n"
             "$    %6s %7s %7s %10s\n",
             "LaboradorSea (57.50N, 56.0W) Jul-30-2003",
             "pres","temp","sal","density",
             "dbar","C","PSU","g/ml"
             );

   for (unsigned int i=0; i<t.NPnt(); i++)
   {
      double rho = 1 + eqstate(s.y[i],t.y[i],t.x[i])/1000;

      fprintf(dest,"$    %6.1f %7.3f %7.3f %10.6f\n",
                t.x[i],t.y[i],s.y[i],rho);
   }
   fprintf(dest,"$\n");
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
void MedSeaHydrography::Properties(ostream &dest)
{
   fprintf(dest,"$ Hydrography:    %s\n"
             "$    %6s %7s %7s %10s\n"
             "$    %6s %7s %7s %10s\n",
             "MedSea (24.36N, 62.22E) Jun-18-2004",
             "pres","temp","sal","density",
             "dbar","C","PSU","g/ml"
             );

   for (unsigned int i=0; i<t.NPnt(); i++)
   {
      double rho = 1 + eqstate(s.y[i],t.y[i],t.x[i])/1000;

      fprintf(dest,"$    %6.1f %7.3f %7.3f %10.6f\n",
                t.x[i],t.y[i],s.y[i],rho);
   }
   fprintf(dest,"$\n");
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
void OkhotskSeaHydrography::Properties(ostream &dest)
{
   fprintf(dest,"$ Hydrography:    %s\n"
             "$    %6s %7s %7s %10s\n"
             "$    %6s %7s %7s %10s\n",
             "OkhotskSea (57.50N, 56.0W) Jul-30-2003",
             "pres","temp","sal","density",
             "dbar","C","PSU","g/ml"
             );

   for (unsigned int i=0; i<t.NPnt(); i++)
   {
      double rho = 1 + eqstate(s.y[i],t.y[i],t.x[i])/1000;

      fprintf(dest,"$    %6.1f %7.3f %7.3f %10.6f\n",
                t.x[i],t.y[i],s.y[i],rho);
   }
   fprintf(dest,"$\n");
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
void OkhotskSeaIceHydrography::Properties(ostream &dest)
{
   fprintf(dest,"$ Hydrography:    %s\n"
             "$    %6s %7s %7s %10s\n"
             "$    %6s %7s %7s %10s\n",
             "OkhotskSeaIce (57.50N, 56.0W) Jul-30-2003",
             "pres","temp","sal","density",
             "dbar","C","PSU","g/ml"
             );

   for (unsigned int i=0; i<t.NPnt(); i++)
   {
      double rho = 1 + eqstate(s.y[i],t.y[i],t.x[i])/1000;

      fprintf(dest,"$    %6.1f %7.3f %7.3f %10.6f\n",
                t.x[i],t.y[i],s.y[i],rho);
   }
   fprintf(dest,"$\n");
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
void RossSeaHydrography::Properties(ostream &dest)
{
   fprintf(dest,"$ Hydrography:    %s\n"
             "$    %6s %7s %7s %10s\n"
             "$    %6s %7s %7s %10s\n",
             "Ross Sea (62.4S  219.8E) Oct-06-2005",
             "pres","temp","sal","density",
             "dbar","C","PSU","g/ml"
             );

   for (unsigned int i=0; i<t.NPnt(); i++)
   {
      double rho = 1 + eqstate(s.y[i],t.y[i],t.x[i])/1000;

      fprintf(dest,"$    %6.1f %7.3f %7.3f %10.6f\n",
                t.x[i],t.y[i],s.y[i],rho);
   }
   fprintf(dest,"$\n");
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
void RossSeaIceHydrography::Properties(ostream &dest)
{
   fprintf(dest,"$ Hydrography:    %s\n"
             "$    %6s %7s %7s %10s\n"
             "$    %6s %7s %7s %10s\n",
             "Ross Sea (73.0S  171.2E) Nov-11-2001",
             "pres","temp","sal","density",
             "dbar","C","PSU","g/ml"
             );

   for (unsigned int i=0; i<t.NPnt(); i++)
   {
      double rho = 1 + eqstate(s.y[i],t.y[i],t.x[i])/1000;

      fprintf(dest,"$    %6.1f %7.3f %7.3f %10.6f\n",
                t.x[i],t.y[i],s.y[i],rho);
   }
   fprintf(dest,"$\n");
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
void SargassoHydrography::Properties(ostream &dest)
{
   fprintf(dest,"$ Hydrography:    %s\n"
             "$    %6s %7s %7s %10s\n"
             "$    %6s %7s %7s %10s\n",
             "Sargasso Region (32.56N, 64.23W) Sep-08-2000 NOPP float 422",
             "pres","temp","sal","density",
             "dbar","C","PSU","g/ml"
             );

   for (unsigned int i=0; i<t.NPnt(); i++)
   {
      double rho = 1 + eqstate(s.y[i],t.y[i],t.x[i])/1000;

      fprintf(dest,"$    %6.1f %7.3f %7.3f %10.6f\n",
                t.x[i],t.y[i],s.y[i],rho);
   }
   fprintf(dest,"$\n");
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
void SargassoModeWaterHydrography::Properties(ostream &dest)
{
   fprintf(dest,"$ Hydrography:    %s\n"
             "$    %6s %7s %7s %10s\n"
             "$    %6s %7s %7s %10s\n",
             "Sargasso 18deg Region (34.67N, 64.8W) Mar-10-2001 NOPP float 422",
             "pres","temp","sal","density",
             "dbar","C","PSU","g/ml"
             );

   for (unsigned int i=0; i<t.NPnt(); i++)
   {
      double rho = 1 + eqstate(s.y[i],t.y[i],t.x[i])/1000;

      fprintf(dest,"$    %6.1f %7.3f %7.3f %10.6f\n",
                t.x[i],t.y[i],s.y[i],rho);
   }
   fprintf(dest,"$\n");
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
void SouthPacificNoppHydrography::Properties(ostream &dest)
{
   fprintf(dest,"$ Hydrography:    %s\n"
             "$    %6s %7s %7s %10s\n"
             "$    %6s %7s %7s %10s\n",
             "South Pacific NOPP Region (12.10S, 129.76W) Nov-14-1999 NOPP float 421",
             "pres","temp","sal","density",
             "dbar","C","PSU","g/ml"
             );

   for (unsigned int i=0; i<t.NPnt(); i++)
   {
      double rho = 1 + eqstate(s.y[i],t.y[i],t.x[i])/1000;

      fprintf(dest,"$    %6.1f %7.3f %7.3f %10.6f\n",
                t.x[i],t.y[i],s.y[i],rho);
   }
   fprintf(dest,"$\n");
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
void SubtropicalNePacificHydrography::Properties(ostream &dest)
{
   fprintf(dest,"$ Hydrography:    %s\n"
             "$    %6s %7s %7s %10s\n"
             "$    %6s %7s %7s %10s\n",
             "Subtropical NE Pacific (36.60N, 123.10W)",
             "pres","temp","sal","density",
             "dbar","C","PSU","g/ml"
             );

   for (unsigned int i=0; i<t.NPnt(); i++)
   {
      double rho = 1 + eqstate(s.y[i],t.y[i],t.x[i])/1000;

      fprintf(dest,"$    %6.1f %7.3f %7.3f %10.6f\n",
                t.x[i],t.y[i],s.y[i],rho);
   }
   fprintf(dest,"$\n");
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
void TropicalAtlanticHydrography::Properties(ostream &dest)
{
   fprintf(dest,"$ Hydrography:    %s\n"
             "$    %6s %7s %7s %10s\n"
             "$    %6s %7s %7s %10s\n",
             "Tropical Atlantic (0.23S, 2.33E)",
             "pres","temp","sal","density",
             "dbar","C","PSU","g/ml"
             );

   for (unsigned int i=0; i<t.NPnt(); i++)
   {
      double rho = 1 + eqstate(s.y[i],t.y[i],t.x[i])/1000;

      fprintf(dest,"$    %6.1f %7.3f %7.3f %10.6f\n",
                t.x[i],t.y[i],s.y[i],rho);
   }
   fprintf(dest,"$\n");
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
void TropicalPacificHydrography::Properties(ostream &dest)
{
   fprintf(dest,"$ Hydrography:    %s\n"
             "$    %6s %7s %7s %10s\n"
             "$    %6s %7s %7s %10s\n",
             "Tropical Atlantic (0.23S, 2.33E)",
             "pres","temp","sal","density",
             "dbar","C","PSU","g/ml"
             );

   for (unsigned int i=0; i<t.NPnt(); i++)
   {
      double rho = 1 + eqstate(s.y[i],t.y[i],t.x[i])/1000;

      fprintf(dest,"$    %6.1f %7.3f %7.3f %10.6f\n",
                t.x[i],t.y[i],s.y[i],rho);
   }
   fprintf(dest,"$\n");
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
ArabianSeaHydrography::ArabianSeaHydrography(void)
{
   HydroObs pts[]=
   {
      //    lat     lon       date   time 
      //  21.50   63.41 12/21/1986 19.400 
      //     p       t       s   //  theta  sigma
      {    0.0, 25.010, 36.400}, // 25.005 24.400
      {   23.1, 25.010, 36.400}, // 25.005 24.400
      {   73.2, 24.990, 36.390}, // 24.974 24.402
      {   99.3, 22.220, 36.160}, // 22.200 25.045
      {  148.5, 19.330, 35.900}, // 19.303 25.632
      {  198.7, 17.790, 35.920}, // 17.756 26.038
      {  275.2, 17.160, 36.320}, // 17.114 26.502
      {  401.0, 14.250, 36.000}, // 14.190 26.920
      {  476.5, 13.470, 35.890}, // 13.402 27.001
      {  602.5, 12.020, 35.690}, // 11.940 27.137
      {  803.2, 10.520, 35.560}, // 10.420 27.316
      { 1006.1,  9.000, 35.420}, //  8.885 27.466
      { 1208.3,  7.530, 35.260}, //  7.404 27.567
   };
   unsigned int n = sizeof(pts)/sizeof(HydroObs);
   
   // make sure there are at least 3 points in the profile
   if (n<3)
   {
      swifterr("error in ArabianSeaHydrography::ArabianSeaHydrography() ... "
               "Hydrographic profile must contain at least 3 points\n");
   }
   
   // make sure the profile starts at the surface
   if (pts[0].p!=0)
   {
      swifterr("error in ArabianSeaHydrography::ArabianSeaHydrography() ... "
               "First observation in profile must be at surface.\n");
   }
   
   // make sure the pressure increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (pts[i].p<=pts[i-1].p)
      {
         swifterr("error in ArabianSeaHydrography::ArabianSeaHydrography() ... "
                  "Hydrographic profile not monotonically increasing in pressure.\n");
      }
   }

   // load the profiles into the linear spline objects
   for (unsigned int i=0; i<n; i++)
   {
      t.Append(pts[i].p,pts[i].t); s.Append(pts[i].p,pts[i].s);
   }

   // seek extremes in the profiles
   t.SeekExtremes(); s.SeekExtremes();
   
   // make sure the density increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (Rho(pts[i].p)<=Rho(pts[i-1].p))
      {
         swifterr("error in ArabianSeaHydrography::ArabianSeaHydrography() ... "
                  "Hydrographic profile not monotonically increasing in density.\n");
      }
   }
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
BayOfBengalHydrography::BayOfBengalHydrography(void)
{
   HydroObs pts[]=
   {
      //    lat     lon       date   time
      //  14.74   81.82 11/09/2002  3.711
      //   p        t        s   //   theta    sigma
      {   0.0,  27.973,  17.520}, //  27.973   9.3183
      {  10.0,  27.973,  17.520}, //  27.973   9.3183
      {  14.1,  27.973,  27.520}, //  27.970  16.7930      
      {  19.8,  28.240,  28.522}, //  28.235  17.4587
      {  29.8,  28.445,  31.879}, //  28.438  19.9097
      {  39.8,  28.543,  33.459}, //  28.534  21.0641
      {  49.6,  28.583,  33.927}, //  28.571  21.4031
      {  59.8,  27.894,  34.717}, //  27.880  22.2232
      {  69.6,  25.772,  34.899}, //  25.757  23.0347
      {  79.4,  24.037,  34.946}, //  24.020  23.5962
      {  89.6,  23.404,  34.909}, //  23.385  23.7546
      {  99.7,  22.649,  34.946}, //  22.629  24.0006
      { 109.6,  21.134,  34.889}, //  21.113  24.3800
      { 119.6,  20.604,  34.895}, //  20.581  24.5284
      { 139.5,  19.286,  34.932}, //  19.261  24.9035
      { 159.6,  18.121,  34.982}, //  18.093  25.2363
      { 179.6,  16.601,  34.915}, //  16.572  25.5509
      { 199.5,  15.094,  34.956}, //  15.064  25.9248
      { 224.5,  13.797,  34.994}, //  13.765  26.2324
      { 249.2,  12.827,  35.015}, //  12.793  26.4466
      { 274.0,  12.490,  35.019}, //  12.453  26.5167
      { 298.8,  12.031,  35.031}, //  11.992  26.6153
      { 324.5,  11.667,  35.031}, //  11.625  26.6848
      { 349.6,  11.350,  35.031}, //  11.306  26.7442
      { 374.1,  11.088,  35.033}, //  11.041  26.7942
      { 399.2,  10.814,  35.032}, //  10.765  26.8434
      { 449.3,  10.441,  35.030}, //  10.387  26.9088
      { 499.0,  10.031,  35.034}, //   9.972  26.9837
      { 549.3,   9.777,  35.029}, //   9.713  27.0238
      { 599.3,   9.480,  35.017}, //   9.411  27.0648
      { 645.0,   9.216,  35.018},  //   9.143  27.1095
      { 784.3,   8.860,  35.185},
      { 986.1,   8.080,  35.222},
      {1248.8,   6.000,  35.005},
      {1547.2,   4.480,  34.901},
      {1843.1,   3.420,  34.847},
      {2135.3,   2.440,  34.790},
      {2426.9,   2.140,  34.765},
      {2724.0,   1.920,  34.760},
      {3029.6,   1.760,  34.761},
      {3182.6,   1.700,  34.746}
   };
   unsigned int n = sizeof(pts)/sizeof(HydroObs);
   
   // make sure there are at least 3 points in the profile
   if (n<3)
   {
      swifterr("error in BayOfBengalHydrography::BayOfBengalHydrography() ... "
               "Hydrographic profile must contain at least 3 points\n");
   }
   
   // make sure the profile starts at the surface
   if (pts[0].p!=0)
   {
      swifterr("error in BayOfBengalHydrography::BayOfBengalHydrography() ... "
               "First observation in profile must be at surface.\n");
   }
   
   // make sure the pressure increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (pts[i].p<=pts[i-1].p)
      {
         swifterr("error in BayOfBengalHydrography::BayOfBengalHydrography() ... "
                  "Hydrographic profile not monotonically increasing in pressure.\n");
      }
   }

   // load the profiles into the linear spline objects
   for (unsigned int i=0; i<n; i++)
   {
      t.Append(pts[i].p,pts[i].t); s.Append(pts[i].p,pts[i].s);
   }

   // seek extremes in the profiles
   t.SeekExtremes(); s.SeekExtremes();
   
   // make sure the density increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (Rho(pts[i].p)<=Rho(pts[i-1].p))
      {
         swifterr("error in BayOfBengalHydrography::BayOfBengalHydrography() ... "
                  "Hydrographic profile not monotonically increasing in density.\n");
      }
   }
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
BlackSeaHydrography::BlackSeaHydrography(void)
{
   HydroObs pts[]=
   {
      //   lat     lon       date   time zmax    n
      // 42.51   30.74 05/26/2001 10.982 2097 2096
      //     p        t        s
      {    0.0, 15.5340, 18.0722},
      {    5.0, 15.4726, 18.0719},
      {   10.0, 15.2263, 18.0724},
      {   15.0, 14.8097, 18.0751},
      {   20.0, 13.0517, 18.0763},
      {   25.0,  9.9502, 18.0831},
      {   30.0,  9.1794, 18.1036},
      {   40.0,  8.5238, 18.1158},
      {   50.0,  8.0191, 18.2878},
      {   60.0,  7.7286, 19.0419},
      {   70.0,  7.8680, 19.5805},
      {   80.0,  7.9812, 19.9843},
      {   90.0,  8.1186, 20.3591},
      {  100.0,  8.2126, 20.5830},
      {  110.0,  8.3072, 20.7834},
      {  120.0,  8.3723, 20.9102},
      {  130.0,  8.4283, 21.0314},
      {  140.0,  8.4895, 21.1355},
      {  150.0,  8.5413, 21.2216},
      {  160.0,  8.5817, 21.2925},
      {  170.0,  8.6149, 21.3577},
      {  180.0,  8.6510, 21.4195},
      {  190.0,  8.6764, 21.4735},
      {  200.0,  8.7104, 21.5157},
      {  250.0,  8.7768, 21.6945},
      {  300.0,  8.8189, 21.8097},
      {  350.0,  8.8435, 21.8941},
      {  400.0,  8.8600, 21.9605},
      {  450.0,  8.8724, 22.0176},
      {  500.0,  8.8803, 22.0645},
      {  600.0,  8.8926, 22.1401},
      {  700.0,  8.9046, 22.1964},
      {  800.0,  8.9190, 22.2354},
      {  900.0,  8.9358, 22.2669},
      { 1000.0,  8.9535, 22.2897},
      { 1100.0,  8.9698, 22.3039},
      { 1200.0,  8.9855, 22.3138},
      { 1300.0,  9.0013, 22.3209},
      { 1400.0,  9.0160, 22.3256},
      { 1500.0,  9.0307, 22.3293},
      { 1550.0,  9.0378, 22.3306},
      { 1600.0,  9.0451, 22.3322},
      { 1700.0,  9.0594, 22.3341},
      { 1800.0,  9.0783, 22.3378},
      { 1900.0,  9.0898, 22.3380},
      { 2000.0,  9.1015, 22.3380},
      { 2097.0,  9.1130, 22.3380},
   };
   unsigned int n = sizeof(pts)/sizeof(HydroObs);
   
   // make sure there are at least 3 points in the profile
   if (n<3)
   {
      swifterr("error in BlackSeaHydrography::BlackSeaHydrography() ... "
               "Hydrographic profile must contain at least 3 points\n");
   }
   
   // make sure the profile starts at the surface
   if (pts[0].p!=0)
   {
      swifterr("error in BlackSeaHydrography::BlackSeaHydrography() ... "
               "First observation in profile must be at surface.\n");
   }
   
   // make sure the pressure increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (pts[i].p<=pts[i-1].p)
      {
         swifterr("error in BlackSeaHydrography::BlackSeaHydrography() ... "
                  "Hydrographic profile not monotonically increasing in pressure.\n");
      }
   }

   // load the profiles into the linear spline objects
   for (unsigned int i=0; i<n; i++)
   {
      t.Append(pts[i].p,pts[i].t); s.Append(pts[i].p,pts[i].s);
   }

   // seek extremes in the profiles
   t.SeekExtremes(); s.SeekExtremes();
   
   // make sure the density increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (Rho(pts[i].p)<=Rho(pts[i-1].p))
      {
         swifterr("error in BlackSeaHydrography::BlackSeaHydrography() ... "
                  "Hydrographic profile not monotonically increasing in density.\n");
      }
   }
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
GulfOfMexicoHydrography::GulfOfMexicoHydrography(void)
{
   HydroObs pts[]=
   {
      //    lat     lon       date   time  zbot  zmax sh co           stnid     n
      //  24.93  -84.58 11/12/1983 13.300 *****  1500  * 32 obs,3077,774761    13
      //    p      t      s      //  theta  sigma     O2     Si    NO3    PO4
      {    0.0, 25.850, 36.029}, 
      {    5.0, 25.850, 36.029}, // 25.849 23.859  4.380    1.1   0.20  0.100
      {   41.1, 25.830, 35.979}, // 25.821 23.830  3.970    4.1  12.00  0.720
      {   99.3, 18.919, 36.389}, // 18.901 26.110  3.660    2.5   6.50  0.410
      {  147.6, 16.869, 36.240}, // 16.845 26.505  2.890    2.3   5.10  0.380
      {  200.9, 14.200, 35.839}, // 14.170 26.800  2.610    7.2  19.30  1.150
      {  301.5, 11.180, 35.389}, // 11.142 27.053  2.450      *      *      *
      {  396.2,  9.560, 35.149}, //  9.515 27.151  2.420   15.8  28.70  1.830
      {  502.0,  8.330, 35.009}, //  8.277 27.239  2.360   14.1  24.50  1.680
      {  603.8,  7.230, 34.919}, //  7.171 27.331  2.560   21.3  31.80  2.070
      {  805.7,  5.640, 34.899}, //  5.570 27.527  3.090   25.1  29.80  2.000
      { 1007.7,  5.181, 34.919}, //  5.095 27.600  3.500   25.5  28.30  1.900
      { 1211.0,  4.711, 34.949}, //  4.610 27.680  3.880   25.9  26.60  1.780
      { 1513.7,  4.280, 34.970}, //  4.155 27.746  4.050   24.5  24.20  1.620
   };
   unsigned int n = sizeof(pts)/sizeof(HydroObs);
   
   // make sure there are at least 3 points in the profile
   if (n<3)
   {
      swifterr("error in GulfOfMexicoHydrography::GulfOfMexicoHydrography() ... "
               "Hydrographic profile must contain at least 3 points\n");
   }
   
   // make sure the profile starts at the surface
   if (pts[0].p!=0)
   {
      swifterr("error in GulfOfMexicoHydrography::GulfOfMexicoHydrography() ... "
               "First observation in profile must be at surface.\n");
   }
   
   // make sure the pressure increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (pts[i].p<=pts[i-1].p)
      {
         swifterr("error in GulfOfMexicoHydrography::GulfOfMexicoHydrography() ... "
                  "Hydrographic profile not monotonically increasing in pressure.\n");
      }
   }

   // load the profiles into the linear spline objects
   for (unsigned int i=0; i<n; i++)
   {
      t.Append(pts[i].p,pts[i].t); s.Append(pts[i].p,pts[i].s);
   }

   // seek extremes in the profiles
   t.SeekExtremes(); s.SeekExtremes();
   
   // make sure the density increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (Rho(pts[i].p)<=Rho(pts[i-1].p))
      {
         swifterr("error in GulfOfMexicoHydrography::GulfOfMexicoHydrography() ... "
                  "Hydrographic profile not monotonically increasing in density.\n");
      }
   }
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
HawaiiPacificHydrography::HawaiiPacificHydrography(void)
{
   HydroObs pts[]=
   {
      //    lat     lon       date   time   zmax 
      //  21.85 -155.03 09/09/1973 15.200   3042
      //     p       t       s        theta  sigma
      {    0.0, 25.527, 35.133}, //  25.527 23.282
      {   10.0, 25.527, 35.135}, //  25.525 23.284
      {   20.0, 25.531, 35.146}, //  25.527 23.292
      {   30.0, 25.536, 35.148}, //  25.529 23.293
      {   50.1, 25.495, 35.285}, //  25.484 23.410
      {   76.1, 22.779, 35.226}, //  22.764 24.175
      {  101.2, 21.420, 35.233}, //  21.400 24.563
      {  126.3, 20.299, 35.195}, //  20.275 24.839
      {  151.4, 19.643, 35.192}, //  19.615 25.010
      {  176.5, 18.128, 34.946}, //  18.098 25.208
      {  201.6, 16.691, 34.771}, //  16.658 25.420
      {  226.7, 14.940, 34.510}, //  14.906 25.615
      {  251.9, 13.488, 34.361}, //  13.453 25.807
      {  303.1, 11.342, 34.209}, //  11.304 26.105
      {  353.4,  9.662, 34.169}, //   9.622 26.367
      {  404.8,  8.655, 34.159}, //   8.612 26.521
      {  454.1,  7.914, 34.195}, //   7.868 26.661
      {  504.5,  7.151, 34.205}, //   7.103 26.779
      {  554.8,  6.478, 34.253}, //   6.428 26.907
      {  605.2,  6.230, 34.313}, //   6.176 26.988
      {  655.6,  5.793, 34.330}, //   5.736 27.056
      {  706.1,  5.643, 34.368}, //   5.582 27.105
      {  757.5,  5.351, 34.400}, //   5.287 27.166
      {  806.9,  5.105, 34.423}, //   5.038 27.213
      {  858.4,  4.866, 34.445}, //   4.796 27.259
      {  908.9,  4.589, 34.453}, //   4.517 27.296
      {  959.4,  4.481, 34.472}, //   4.405 27.323
      { 1009.9,  4.295, 34.489}, //   4.216 27.357
      { 1111.0,  4.016, 34.505}, //   3.931 27.400
      { 1212.1,  3.737, 34.527}, //   3.646 27.446
      { 1313.3,  3.444, 34.543}, //   3.347 27.488
      { 1415.5,  3.243, 34.555}, //   3.139 27.517
      { 1515.7,  3.035, 34.564}, //   2.925 27.544
      { 1617.1,  2.834, 34.576}, //   2.718 27.572
      { 1719.4,  2.664, 34.585}, //   2.542 27.595
      { 1819.8,  2.518, 34.595}, //   2.389 27.616
      { 1922.3,  2.371, 34.604}, //   2.235 27.635
      { 2023.8,  2.219, 34.613}, //   2.077 27.656
      { 2227.0,  2.028, 34.626}, //   1.871 27.682
      { 2434.5,  1.895, 34.639}, //   1.722 27.704
      { 2636.0,  1.737, 34.648}, //   1.549 27.724
      { 2837.7,  1.650, 34.657}, //   1.445 27.739
      { 3041.7,  1.583, 34.662}, //   1.360 27.749
   };
   unsigned int n = sizeof(pts)/sizeof(HydroObs);
   
   // make sure there are at least 3 points in the profile
   if (n<3)
   {
      swifterr("error in HawaiiPacificHydrography::HawaiiPacificHydrography() ... "
               "Hydrographic profile must contain at least 3 points\n");
   }
   
   // make sure the profile starts at the surface
   if (pts[0].p!=0)
   {
      swifterr("error in HawaiiPacificHydrography::HawaiiPacificHydrography() ... "
               "First observation in profile must be at surface.\n");
   }
   
   // make sure the pressure increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (pts[i].p<=pts[i-1].p)
      {
         swifterr("error in HawaiiPacificHydrography::HawaiiPacificHydrography() ... "
                  "Hydrographic profile not monotonically increasing in pressure.\n");
      }
   }

   // load the profiles into the linear spline objects
   for (unsigned int i=0; i<n; i++)
   {
      t.Append(pts[i].p,pts[i].t); s.Append(pts[i].p,pts[i].s);
   }

   // seek extremes in the profiles
   t.SeekExtremes(); s.SeekExtremes();
   
   // make sure the density increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (Rho(pts[i].p)<=Rho(pts[i-1].p))
      {
         swifterr("error in HawaiiPacificHydrography::HawaiiPacificHydrography() ... "
                  "Hydrographic profile not monotonically increasing in density.\n");
      }
   }
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
IndianOceanHydrography::IndianOceanHydrography(void)
{
   HydroObs pts[]=
   {
      //    lat     lon       date   time   zmax     stnid 
      // -17.95   94.81 04/02/2007 10.190   1998  0009.001
      //      p        t        s        theta    sigma
      {     0.0,  25.936,  35.170},
      {     5.9,  25.936,  35.170}, //  25.935  23.1839
      {    10.2,  25.939,  35.170}, //  25.937  23.1833
      {    19.4,  25.918,  35.171}, //  25.914  23.1912
      {    30.1,  25.841,  35.178}, //  25.834  23.2212
      {    40.1,  25.810,  35.184}, //  25.801  23.2360
      {    50.0,  25.791,  35.189}, //  25.780  23.2463
      {    60.0,  25.629,  35.220}, //  25.616  23.3206
      {    68.7,  25.616,  35.224}, //  25.601  23.3282
      {    80.6,  25.582,  35.207}, //  25.564  23.3267
      {    89.6,  23.672,  35.153}, //  23.653  23.8612
      {   100.6,  22.871,  35.228}, //  22.850  24.1512
      {   109.1,  22.366,  35.306}, //  22.344  24.3548
      {   120.1,  22.024,  35.369}, //  22.000  24.4997
      {   129.9,  21.787,  35.395}, //  21.761  24.5862
      {   140.0,  21.567,  35.424}, //  21.540  24.6699
      {   150.4,  21.426,  35.446}, //  21.397  24.7261
      {   160.4,  21.270,  35.480}, //  21.239  24.7954
      {   170.2,  20.795,  35.546}, //  20.763  24.9756
      {   179.7,  20.610,  35.577}, //  20.576  25.0496
      {   190.2,  20.379,  35.649}, //  20.343  25.1669
      {   200.5,  20.146,  35.722}, //  20.109  25.2851
      {   210.6,  19.950,  35.760}, //  19.911  25.3664
      {   219.2,  19.575,  35.783}, //  19.535  25.4827
      {   230.0,  19.129,  35.808}, //  19.087  25.6176
      {   239.8,  18.962,  35.820}, //  18.919  25.6700
      {   249.5,  18.597,  35.793}, //  18.553  25.7424
      {   259.4,  18.254,  35.791}, //  18.209  25.8273
      {   270.0,  17.783,  35.759}, //  17.737  25.9196
      {   280.1,  17.613,  35.755}, //  17.565  25.9584
      {   289.9,  17.335,  35.735}, //  17.286  26.0108
      {   300.4,  16.726,  35.693}, //  16.677  26.1241
      {   308.1,  16.322,  35.646}, //  16.272  26.1827
      {   320.1,  15.715,  35.587}, //  15.665  26.2768
      {   330.4,  14.782,  35.473}, //  14.732  26.3963
      {   340.1,  14.227,  35.407}, //  14.177  26.4650
      {   349.6,  13.892,  35.371}, //  13.841  26.5080
      {   359.5,  13.549,  35.323}, //  13.498  26.5423
      {   379.9,  12.841,  35.217}, //  12.789  26.6040
      {   400.4,  12.214,  35.127}, //  12.161  26.6574
      {   450.2,  10.664,  34.882}, //  10.609  26.7542
      {   500.4,   9.809,  34.752}, //   9.751  26.8009
      {   550.2,   9.279,  34.679}, //   9.217  26.8321
      {   600.0,   8.582,  34.605}, //   8.518  26.8851
      {   650.1,   7.679,  34.548}, //   7.613  26.9760
      {   700.6,   6.854,  34.533}, //   6.787  27.0803
      {   749.8,   6.685,  34.618}, //   6.614  27.1707
      {   799.9,   6.258,  34.625}, //   6.185  27.2328
      {   849.8,   5.985,  34.639}, //   5.909  27.2792
      {   899.6,   5.872,  34.653}, //   5.792  27.3050
      {   950.2,   5.704,  34.657}, //   5.620  27.3294
      {   969.2,   5.384,  34.663}, //   5.300  27.3729
      {  1000.0,   5.456,  34.662}, //   5.369  27.3639
      {  1050.3,   5.185,  34.659}, //   5.095  27.3939
      {  1099.9,   5.023,  34.662}, //   4.930  27.4155
      {  1150.4,   4.846,  34.661}, //   4.750  27.4352
      {  1200.3,   4.622,  34.655}, //   4.523  27.4558
      {  1250.2,   4.475,  34.655}, //   4.373  27.4722
      {  1299.6,   4.318,  34.657}, //   4.213  27.4910
      {  1350.0,   4.138,  34.660}, //   4.031  27.5126
      {  1400.5,   3.896,  34.664}, //   3.787  27.5409
      {  1450.4,   3.723,  34.668}, //   3.611  27.5617
      {  1500.3,   3.599,  34.672}, //   3.484  27.5774
      {  1549.6,   3.465,  34.676}, //   3.347  27.5939
      {  1600.0,   3.308,  34.682}, //   3.188  27.6139
      {  1650.3,   3.171,  34.687}, //   3.048  27.6309
      {  1700.3,   3.037,  34.695}, //   2.911  27.6498
      {  1750.4,   2.926,  34.698}, //   2.797  27.6625
      {  1800.2,   2.805,  34.701}, //   2.674  27.6758
      {  1850.4,   2.717,  34.703}, //   2.582  27.6854
      {  1899.7,   2.639,  34.705}, //   2.501  27.6940
      {  1949.4,   2.551,  34.710}, //   2.410  27.7057
      {  1997.5,   2.478,  34.712}, //   2.334  27.7138
      {  3000.0,   2.478,  34.712}, 
   };
   unsigned int n = sizeof(pts)/sizeof(HydroObs);
   
   // make sure there are at least 3 points in the profile
   if (n<3)
   {
      swifterr("error in IndianOceanHydrography::IndianOceanHydrography() ... "
               "Hydrographic profile must contain at least 3 points\n");
   }
   
   // make sure the profile starts at the surface
   if (pts[0].p!=0)
   {
      swifterr("error in IndianOceanHydrography::IndianOceanHydrography() ... "
               "First observation in profile must be at surface.\n");
   }
   
   // make sure the pressure increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (pts[i].p<=pts[i-1].p)
      {
         swifterr("error in IndianOceanHydrography::IndianOceanHydrography() ... "
                  "Hydrographic profile not monotonically increasing in pressure.\n");
      }
   }

   // load the profiles into the linear spline objects
   for (unsigned int i=0; i<n; i++)
   {
      t.Append(pts[i].p,pts[i].t); s.Append(pts[i].p,pts[i].s);
   }

   // seek extremes in the profiles
   t.SeekExtremes(); s.SeekExtremes();
   
   // make sure the density increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (Rho(pts[i].p)<=Rho(pts[i-1].p))
      {
         swifterr("error in IndianOceanHydrography::IndianOceanHydrography() ... "
                  "Hydrographic profile not monotonically increasing in density.\n");
      }
   }
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
JapanSeaHydrography::JapanSeaHydrography(void)
{
   HydroObs pts[]=
   {
      //    lat     lon       date   time  zmax   stnid  n
      //  39.33  133.90 09/09/1999 16.956  1007 195.026 53
      //     p       t        s        theta    sigma
      {    0.0, 24.164, 33.2488}, //  24.163  22.2700
      {    9.7, 23.933, 33.3437}, //  23.931  22.4099
      {   19.8, 22.168, 33.6167}, //  22.164  23.1228
      {   29.6, 17.843, 34.4372}, //  17.838  24.8818
      {   39.5, 15.902, 34.3900}, //  15.896  25.3029
      {   49.7, 14.503, 34.3972}, //  14.496  25.6170
      {   59.4, 12.733, 34.3107}, //  12.725  25.9140
      {   69.6, 11.215, 34.2526}, //  11.206  26.1566
      {   79.3, 10.157, 34.1898}, //  10.148  26.2945
      {   89.2,  8.984, 34.1405}, //   8.975  26.4495
      {   99.3,  8.026, 34.1176}, //   8.016  26.5787
      {  109.5,  7.209, 34.0945}, //   7.199  26.6782
      {  119.6,  6.160, 34.0764}, //   6.150  26.8040
      {  129.5,  5.270, 34.0635}, //   5.260  26.9028
      {  139.4,  4.472, 34.0555}, //   4.462  26.9863
      {  149.5,  4.219, 34.0482}, //   4.208  27.0075
      {  159.5,  3.680, 34.0515}, //   3.669  27.0649
      {  169.1,  3.396, 34.0563}, //   3.385  27.0962
      {  179.5,  3.137, 34.0545}, //   3.126  27.1189
      {  189.0,  2.734, 34.0554}, //   2.723  27.1556
      {  199.1,  2.231, 34.0519}, //   2.220  27.1947
      {  209.5,  1.937, 34.0511}, //   1.926  27.2171
      {  219.5,  1.769, 34.0573}, //   1.758  27.2348
      {  229.6,  1.604, 34.0579}, //   1.593  27.2474
      {  239.5,  1.522, 34.0601}, //   1.510  27.2551
      {  249.4,  1.419, 34.0691}, //   1.407  27.2696
      {  259.1,  1.291, 34.0700}, //   1.279  27.2792
      {  269.0,  1.188, 34.0688}, //   1.175  27.2852
      {  279.3,  1.124, 34.0687}, //   1.111  27.2893
      {  289.5,  1.062, 34.0704}, //   1.049  27.2948
      {  299.4,  1.030, 34.0705}, //   1.016  27.2970
      {  309.6,  0.985, 34.0721}, //   0.971  27.3012
      {  319.1,  0.963, 34.0719}, //   0.948  27.3025
      {  329.3,  0.930, 34.0721}, //   0.915  27.3048
      {  339.3,  0.896, 34.0720}, //   0.881  27.3068
      {  349.4,  0.863, 34.0726}, //   0.847  27.3094
      {  359.5,  0.832, 34.0719}, //   0.816  27.3108
      {  379.5,  0.787, 34.0730}, //   0.770  27.3145
      {  399.5,  0.735, 34.0722}, //   0.717  27.3171
      {  449.4,  0.629, 34.0718}, //   0.609  27.3233
      {  499.3,  0.556, 34.0710}, //   0.534  27.3270
      {  549.1,  0.495, 34.0702}, //   0.471  27.3300
      {  599.3,  0.440, 34.0699}, //   0.414  27.3331
      {  649.5,  0.398, 34.0691}, //   0.370  27.3349
      {  699.2,  0.367, 34.0687}, //   0.336  27.3365
      {  749.3,  0.333, 34.0686}, //   0.300  27.3384
      {  799.4,  0.315, 34.0679}, //   0.279  27.3390
      {  849.3,  0.296, 34.0680}, //   0.258  27.3402
      {  899.3,  0.280, 34.0679}, //   0.239  27.3411
      {  949.3,  0.268, 34.0679}, //   0.225  27.3419
      {  978.9,  0.259, 34.0676}, //   0.214  27.3422
      {  999.2,  0.253, 34.0676}, //   0.207  27.3426
      { 1006.8,  0.252, 34.0681}, //   0.206  27.3431
   };
   unsigned int n = sizeof(pts)/sizeof(HydroObs);
   
   // make sure there are at least 3 points in the profile
   if (n<3)
   {
      swifterr("error in JapanSeaHydrography::JapanSeaHydrography() ... "
               "Hydrographic profile must contain at least 3 points\n");
   }
   
   // make sure the profile starts at the surface
   if (pts[0].p!=0)
   {
      swifterr("error in JapanSeaHydrography::JapanSeaHydrography() ... "
               "First observation in profile must be at surface.\n");
   }
   
   // make sure the pressure increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (pts[i].p<=pts[i-1].p)
      {
         swifterr("error in JapanSeaHydrography::JapanSeaHydrography() ... "
                  "Hydrographic profile not monotonically increasing in pressure.\n");
      }
   }

   // load the profiles into the linear spline objects
   for (unsigned int i=0; i<n; i++)
   {
      t.Append(pts[i].p,pts[i].t); s.Append(pts[i].p,pts[i].s);
   }

   // seek extremes in the profiles
   t.SeekExtremes(); s.SeekExtremes();
   
   // make sure the density increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (Rho(pts[i].p)<=Rho(pts[i-1].p))
      {
         swifterr("error in JapanSeaHydrography::JapanSeaHydrography() ... "
                  "Hydrographic profile not monotonically increasing in density.\n");
      }
   }
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
KurishioHydrography::KurishioHydrography(void)
{
   HydroObs pts[]=
   {
      //    lat     lon       date   time  zbot  zmax sh co           stnid     n
      //  33.83  141.20 02/14/1988  5.200 *****  2532  * 49 obs,3900,802295    24
      //     p       t       s       theta  sigma     O2    NO3    PO4
      {    0.0, 18.760, 34.873}, // 18.760 24.988  5.290   1.00  0.150
      {   10.0, 18.760, 34.873}, // 18.738 24.992  5.260   1.00  0.140
      {   25.1, 18.760, 34.873}, // 18.756 24.987  5.260   1.00  0.140
      {   50.2, 18.740, 34.873}, // 18.731 24.994  5.260   1.00  0.140
      {   74.3, 18.730, 34.873}, // 18.717 24.997  5.240   1.00  0.130
      {   99.4, 18.650, 34.874}, // 18.633 25.019  5.240   1.20  0.150
      {  124.5, 18.490, 34.864}, // 18.468 25.053  5.150   1.60  0.170
      {  148.7, 18.430, 34.870}, // 18.404 25.073  5.240   1.40  0.170
      {  172.8, 18.350, 34.872}, // 18.320 25.096  5.170   1.40  0.170
      {  197.9, 18.350, 34.872}, // 18.316 25.095  5.200   1.50  0.190
      {  246.2, 18.150, 34.854}, // 18.107 25.135  5.020   2.30  0.300
      {  294.4, 17.060, 34.769}, // 17.011 25.335  4.610   5.60  0.470
      {  427.3, 14.860, 34.624}, // 14.795 25.727  4.390   9.80  0.750
      {  527.0, 12.430, 34.442}, // 12.359 26.087  4.280  14.20  1.080
      {  627.8,  9.910, 34.270}, //  9.837 26.410  4.010  20.10  1.510
      {  727.7,  7.550, 34.145}, //  7.477 26.679  3.320  26.80  1.990
      {  827.6,  6.080, 34.134}, //  6.006 26.868  2.690  31.60  2.380
      {  927.6,  4.960, 34.184}, //  4.884 27.042  1.950  36.70  2.740
      { 1028.7,  4.500, 34.304}, //  4.418 27.188  1.680  38.10  2.860
      { 1279.6,  3.360, 34.424}, //  3.267 27.401  1.590  39.70  2.980
      { 1550.2,  2.530, 34.510}, //  2.424 27.545  1.640  41.00  3.050
      { 1802.8,  2.240, 34.551}, //  2.116 27.603  1.770  40.90  3.040
      { 2055.8,  1.990, 34.586}, //  1.849 27.652  1.950  40.50  3.030
      { 2562.6,  1.690, 34.638}, //  1.510 27.719  2.640  38.60  2.890
   };
   unsigned int n = sizeof(pts)/sizeof(HydroObs);
   
   // make sure there are at least 3 points in the profile
   if (n<3)
   {
      swifterr("error in KurishioHydrography::KurishioHydrography() ... "
               "Hydrographic profile must contain at least 3 points\n");
   }
   
   // make sure the profile starts at the surface
   if (pts[0].p!=0)
   {
      swifterr("error in KurishioHydrography::KurishioHydrography() ... "
               "First observation in profile must be at surface.\n");
   }
   
   // make sure the pressure increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (pts[i].p<=pts[i-1].p)
      {
         swifterr("error in KurishioHydrography::KurishioHydrography() ... "
                  "Hydrographic profile not monotonically increasing in pressure.\n");
      }
   }

   // load the profiles into the linear spline objects
   for (unsigned int i=0; i<n; i++)
   {
      t.Append(pts[i].p,pts[i].t); s.Append(pts[i].p,pts[i].s);
   }

   // seek extremes in the profiles
   t.SeekExtremes(); s.SeekExtremes();
   
   // make sure the density increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (Rho(pts[i].p)<=Rho(pts[i-1].p))
      {
         swifterr("error in KurishioHydrography::KurishioHydrography() ... "
                  "Hydrographic profile not monotonically increasing in density.\n");
      }
   }
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
LaboradorSeaHydrography::LaboradorSeaHydrography(void)
{
   HydroObs pts[]=
   {
      //    lat     lon       date   time  zbot  zmax sh co           stnid      n
      //  57.50  304.05 07/30/2003  2.853     *  1999  *  *        0570.074     61
      //     p        t        s        theta    sigma
      {    0.0,  10.608,  34.190}, //  10.607  26.2151
      {    9.8,  10.608,  34.190}, //  10.607  26.2151
      {   19.6,   8.056,  34.162}, //   8.054  26.6079
      {   29.4,   6.179,  34.320}, //   6.176  26.9930
      {   39.4,   4.887,  34.449}, //   4.884  27.2518
      {   49.2,   4.437,  34.528}, //   4.433  27.3647
      {   59.3,   4.226,  34.600}, //   4.222  27.4447
      {   69.1,   4.149,  34.668}, //   4.144  27.5071
      {   79.1,   4.068,  34.710}, //   4.062  27.5491
      {   99.6,   4.108,  34.761}, //   4.101  27.5856
      {  119.5,   4.115,  34.789}, //   4.107  27.6073
      {  139.5,   4.236,  34.822}, //   4.226  27.6208
      {  159.2,   4.300,  34.840}, //   4.288  27.6284
      {  179.5,   4.209,  34.840}, //   4.196  27.6383
      {  199.5,   4.157,  34.840}, //   4.143  27.6440
      {  224.5,   3.980,  34.832}, //   3.964  27.6564
      {  249.0,   3.956,  34.840}, //   3.939  27.6654
      {  273.9,   3.911,  34.841}, //   3.892  27.6711
      {  299.1,   3.946,  34.851}, //   3.925  27.6756
      {  324.2,   3.896,  34.849}, //   3.873  27.6793
      {  349.5,   3.851,  34.847}, //   3.826  27.6826
      {  374.3,   3.827,  34.849}, //   3.801  27.6868
      {  399.0,   3.790,  34.848}, //   3.762  27.6899
      {  424.2,   3.768,  34.848}, //   3.738  27.6923
      {  449.5,   3.745,  34.849}, //   3.713  27.6956
      {  473.9,   3.735,  34.851}, //   3.702  27.6984
      {  499.5,   3.703,  34.850}, //   3.668  27.7010
      {  524.4,   3.676,  34.849}, //   3.639  27.7031
      {  549.5,   3.667,  34.851}, //   3.628  27.7058
      {  574.5,   3.657,  34.850}, //   3.617  27.7062
      {  599.4,   3.630,  34.849}, //   3.588  27.7083
      {  624.5,   3.647,  34.853}, //   3.603  27.7099
      {  649.5,   3.634,  34.854}, //   3.588  27.7122
      {  674.2,   3.628,  34.855}, //   3.580  27.7138
      {  699.2,   3.618,  34.856}, //   3.568  27.7158
      {  749.4,   3.576,  34.855}, //   3.523  27.7195
      {  799.3,   3.543,  34.855}, //   3.486  27.7231
      {  849.2,   3.511,  34.854}, //   3.450  27.7258
      {  899.3,   3.471,  34.852}, //   3.407  27.7285
      {  949.5,   3.439,  34.850}, //   3.371  27.7303
      {  999.1,   3.416,  34.850}, //   3.344  27.7329
      { 1049.2,   3.369,  34.845}, //   3.294  27.7338
      { 1099.3,   3.361,  34.848}, //   3.282  27.7374
      { 1149.5,   3.415,  34.860}, //   3.331  27.7422
      { 1199.6,   3.454,  34.870}, //   3.366  27.7468
      { 1249.0,   3.465,  34.877}, //   3.372  27.7517
      { 1299.1,   3.465,  34.881}, //   3.368  27.7553
      { 1349.1,   3.453,  34.885}, //   3.352  27.7601
      { 1399.6,   3.411,  34.884}, //   3.306  27.7637
      { 1449.5,   3.371,  34.884}, //   3.262  27.7679
      { 1498.3,   3.360,  34.884}, //   3.247  27.7694
      { 1499.2,   3.315,  34.880}, //   3.203  27.7704
      { 1549.1,   3.270,  34.879}, //   3.154  27.7742
      { 1599.4,   3.236,  34.877}, //   3.116  27.7762
      { 1649.4,   3.189,  34.874}, //   3.065  27.7786
      { 1699.2,   3.155,  34.872}, //   3.027  27.7805
      { 1749.4,   3.132,  34.874}, //   3.000  27.7846
      { 1799.4,   3.109,  34.876}, //   2.973  27.7887
      { 1849.3,   3.094,  34.879}, //   2.954  27.7929
      { 1899.2,   3.066,  34.880}, //   2.922  27.7966
      { 1949.0,   3.037,  34.882}, //   2.889  27.8012
      { 1999.4,   3.014,  34.884}, //   2.861  27.8053
      { 2200.0,   3.014,  34.884},
   };
   unsigned int n = sizeof(pts)/sizeof(HydroObs);
   
   // make sure there are at least 3 points in the profile
   if (n<3)
   {
      swifterr("error in LaboradorSeaHydrography::LaboradorSeaHydrography() ... "
               "Hydrographic profile must contain at least 3 points\n");
   }
   
   // make sure the profile starts at the surface
   if (pts[0].p!=0)
   {
      swifterr("error in LaboradorSeaHydrography::LaboradorSeaHydrography() ... "
               "First observation in profile must be at surface.\n");
   }
   
   // make sure the pressure increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (pts[i].p<=pts[i-1].p)
      {
         swifterr("error in LaboradorSeaHydrography::LaboradorSeaHydrography() ... "
                  "Hydrographic profile not monotonically increasing in pressure.\n");
      }
   }

   // load the profiles into the linear spline objects
   for (unsigned int i=0; i<n; i++)
   {
      t.Append(pts[i].p,pts[i].t); s.Append(pts[i].p,pts[i].s);
   }

   // seek extremes in the profiles
   t.SeekExtremes(); s.SeekExtremes();
   
   // make sure the density increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (Rho(pts[i].p)<=Rho(pts[i-1].p))
      {
         swifterr("error in LaboradorSeaHydrography::LaboradorSeaHydrography() ... "
                  "Hydrographic profile not monotonically increasing in density.\n");
      }
   }
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
MedSeaHydrography::MedSeaHydrography(void)
{
   HydroObs pts[]=
   {
      //    lat     lon       date   time  zmax      stnid      n
      //  24.36   62.22 06/18/2004 12.170  1057   1775.013     36
      //      p        t        s   //   theta    sigma
      {     0.0,  29.756,  36.628},
      {     4.3,  29.756,  36.628}, //  29.755  23.0337
      {     9.6,  29.675,  36.625}, //  29.673  23.0595
      {    19.8,  28.939,  36.507}, //  28.934  23.2205
      {    29.5,  26.527,  36.275}, //  26.520  23.8336
      {    39.5,  25.462,  36.354}, //  25.453  24.2274
      {    49.7,  24.409,  36.447}, //  24.398  24.6197
      {    59.5,  24.085,  36.479}, //  24.072  24.7417
      {    69.5,  23.875,  36.571}, //  23.860  24.8746
      {    79.6,  22.804,  36.306}, //  22.788  24.9875
      {    89.7,  22.217,  36.254}, //  22.199  25.1163
      {    99.6,  22.360,  36.390}, //  22.340  25.1796
      {   109.4,  21.737,  36.277}, //  21.715  25.2699
      {   119.6,  21.703,  36.346}, //  21.679  25.3325
      {   139.3,  20.406,  36.155}, //  20.380  25.5430
      {   159.3,  19.611,  36.097}, //  19.582  25.7103
      {   179.6,  18.619,  36.091}, //  18.587  25.9618
      {   199.2,  18.428,  36.161}, //  18.393  26.0645
      {   224.4,  17.832,  36.169}, //  17.793  26.2200
      {   249.4,  17.872,  36.379}, //  17.829  26.3723
      {   274.3,  17.820,  36.485}, //  17.773  26.4674
      {   299.4,  17.316,  36.457}, //  17.265  26.5701
      {   324.2,  16.613,  36.370}, //  16.560  26.6722
      {   349.5,  15.988,  36.291}, //  15.932  26.7578
      {   374.4,  16.151,  36.424}, //  16.090  26.8236
      {   399.1,  15.081,  36.204}, //  15.019  26.8972
      {   449.5,  14.005,  35.993}, //  13.939  26.9686
      {   499.3,  13.310,  35.880}, //  13.239  27.0269
      {   549.4,  12.706,  35.784}, //  12.630  27.0754
      {   599.6,  12.122,  35.703}, //  12.041  27.1279
      {   674.5,  11.615,  35.657}, //  11.527  27.1903
      {   749.3,  11.111,  35.615}, //  11.015  27.2524
      {   824.2,  10.452,  35.559}, //  10.350  27.3281
      {   899.1,   9.879,  35.510}, //   9.771  27.3900
      {   999.5,   9.303,  35.453}, //   9.187  27.4430
      {  1056.5,   8.826,  35.407}, //   8.706  27.4844
      {  2015.0,   8.828,  35.407}
   };
   unsigned int n = sizeof(pts)/sizeof(HydroObs);
   
   // make sure there are at least 3 points in the profile
   if (n<3)
   {
      swifterr("error in MedSeaHydrography::MedSeaHydrography() ... "
               "Hydrographic profile must contain at least 3 points\n");
   }
   
   // make sure the profile starts at the surface
   if (pts[0].p!=0)
   {
      swifterr("error in MedSeaHydrography::MedSeaHydrography() ... "
               "First observation in profile must be at surface.\n");
   }
   
   // make sure the pressure increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (pts[i].p<=pts[i-1].p)
      {
         swifterr("error in MedSeaHydrography::MedSeaHydrography() ... "
                  "Hydrographic profile not monotonically increasing in pressure.\n");
      }
   }

   // load the profiles into the linear spline objects
   for (unsigned int i=0; i<n; i++)
   {
      t.Append(pts[i].p,pts[i].t); s.Append(pts[i].p,pts[i].s);
   }

   // seek extremes in the profiles
   t.SeekExtremes(); s.SeekExtremes();
   
   // make sure the density increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (Rho(pts[i].p)<=Rho(pts[i-1].p))
      {
         swifterr("error in MedSeaHydrography::MedSeaHydrography() ... "
                  "Hydrographic profile not monotonically increasing in density.\n");
      }
   }
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
OkhotskSeaHydrography::OkhotskSeaHydrography(void)
{
   HydroObs pts[]=
   {
      //    lat     lon       date   time  zbot  zmax sh co           stnid      n
      //  45.35  145.41 10/27/2002  1.685     *  1654  *  *        0970.001     65
      //      p       t       s   //   theta    sigma
      {     0.0,  10.160,  32.519}, //
      {     6.3,  10.160,  32.519}, //  10.159  24.9890
      {     9.5,  10.160,  32.520}, //  10.159  24.9899
      {    19.7,  10.164,  32.514}, //  10.162  24.9847
      {    29.6,  10.030,  32.533}, //  10.027  25.0221
      {    39.3,   7.176,  33.187}, //   7.172  25.9675
      {    49.3,   4.345,  33.171}, //   4.342  26.2966
      {    59.3,   2.099,  33.117}, //   2.096  26.4560
      {    69.4,   1.218,  33.143}, //   1.215  26.5387
      {    78.8,   0.488,  33.138}, //   0.485  26.5782
      {    88.8,   0.303,  33.152}, //   0.300  26.5994
      {    99.1,   0.463,  33.179}, //   0.459  26.6127
      {   108.8,   0.371,  33.183}, //   0.367  26.6208
      {   119.3,  -0.012,  33.187}, //  -0.016  26.6435
      {   129.3,   0.092,  33.207}, //   0.087  26.6546
      {   139.5,   0.140,  33.216}, //   0.135  26.6595
      {   149.5,   0.129,  33.232}, //   0.124  26.6729
      {   159.4,   0.153,  33.238}, //   0.147  26.6766
      {   169.4,   0.280,  33.247}, //   0.274  26.6774
      {   179.2,   0.265,  33.266}, //   0.258  26.6935
      {   189.2,   0.378,  33.278}, //   0.371  26.6972
      {   198.9,   0.387,  33.287}, //   0.379  26.7040
      {   209.0,   0.312,  33.293}, //   0.304  26.7128
      {   219.4,   0.374,  33.304}, //   0.366  26.7184
      {   228.8,   0.462,  33.319}, //   0.453  26.7258
      {   238.9,   0.579,  33.334}, //   0.569  26.7314
      {   249.3,   0.657,  33.348}, //   0.647  26.7383
      {   259.4,   0.821,  33.371}, //   0.810  26.7472
      {   269.4,   0.857,  33.381}, //   0.845  26.7531
      {   279.2,   1.156,  33.410}, //   1.143  26.7579
      {   289.5,   0.940,  33.408}, //   0.927  26.7698
      {   299.2,   0.934,  33.418}, //   0.921  26.7783
      {   309.0,   1.016,  33.435}, //   1.002  26.7869
      {   319.4,   1.058,  33.445}, //   1.044  26.7923
      {   329.3,   1.118,  33.461}, //   1.103  26.8014
      {   339.5,   1.132,  33.478}, //   1.116  26.8142
      {   349.0,   1.165,  33.490}, //   1.149  26.8218
      {   359.4,   1.203,  33.499}, //   1.186  26.8266
      {   379.2,   1.391,  33.545}, //   1.373  26.8511
      {   399.5,   1.511,  33.587}, //   1.491  26.8767
      {   449.2,   1.545,  33.644}, //   1.522  26.9203
      {   499.0,   1.700,  33.725}, //   1.674  26.9745
      {   549.4,   1.841,  33.809}, //   1.811  27.0318
      {   599.0,   2.004,  33.906}, //   1.970  27.0975
      {   649.3,   2.136,  33.989}, //   2.099  27.1540
      {   699.3,   2.223,  34.058}, //   2.182  27.2027
      {   749.1,   2.281,  34.114}, //   2.236  27.2432
      {   799.4,   2.310,  34.152}, //   2.262  27.2715
      {   849.4,   2.331,  34.186}, //   2.279  27.2973
      {   899.2,   2.349,  34.234}, //   2.293  27.3346
      {   949.4,   2.348,  34.278}, //   2.289  27.3701
      {   999.2,   2.340,  34.321}, //   2.277  27.4055
      {  1049.1,   2.322,  34.351}, //   2.256  27.4313
      {  1099.2,   2.297,  34.378}, //   2.228  27.4552
      {  1148.9,   2.268,  34.408}, //   2.195  27.4818
      {  1199.2,   2.235,  34.430}, //   2.159  27.5024
      {  1249.2,   2.210,  34.445}, //   2.130  27.5167
      {  1299.3,   2.185,  34.458}, //   2.102  27.5294
      {  1348.8,   2.160,  34.471}, //   2.073  27.5421
      {  1399.2,   2.139,  34.482}, //   2.049  27.5528
      {  1449.5,   2.119,  34.491}, //   2.025  27.5619
      {  1499.4,   2.105,  34.498}, //   2.007  27.5689
      {  1548.9,   2.087,  34.505}, //   1.986  27.5762
      {  1599.0,   2.069,  34.512}, //   1.964  27.5835
      {  1649.1,   2.050,  34.520}, //   1.941  27.5917
      {  1653.8,   2.050,  34.519}, //   1.941  27.5910
   };
   unsigned int n = sizeof(pts)/sizeof(HydroObs);
   
   // make sure there are at least 3 points in the profile
   if (n<3)
   {
      swifterr("error in OkhotskSeaHydrography::OkhotskSeaHydrography() ... "
               "Hydrographic profile must contain at least 3 points\n");
   }
   
   // make sure the profile starts at the surface
   if (pts[0].p!=0)
   {
      swifterr("error in OkhotskSeaHydrography::OkhotskSeaHydrography() ... "
               "First observation in profile must be at surface.\n");
   }
   
   // make sure the pressure increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (pts[i].p<=pts[i-1].p)
      {
         swifterr("error in OkhotskSeaHydrography::OkhotskSeaHydrography() ... "
                  "Hydrographic profile not monotonically increasing in pressure.\n");
      }
   }

   // load the profiles into the linear spline objects
   for (unsigned int i=0; i<n; i++)
   {
      t.Append(pts[i].p,pts[i].t); s.Append(pts[i].p,pts[i].s);
   }

   // seek extremes in the profiles
   t.SeekExtremes(); s.SeekExtremes();
   
   // make sure the density increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (Rho(pts[i].p)<=Rho(pts[i-1].p))
      {
         swifterr("error in OkhotskSeaHydrography::OkhotskSeaHydrography() ... "
                  "Hydrographic profile not monotonically increasing in density.\n");
      }
   }
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
OkhotskSeaIceHydrography::OkhotskSeaIceHydrography(void)
{
   HydroObs pts[]=
   {
      //    lat     lon       date   time  zbot  zmax sh co           stnid      n
      //  49.53  145.65 01/07/2001 18.758     *  1654  *  *        0281.020     37
      //      p       t        s   //   theta    sigma
      {     0.0,  -1.757,  32.6994},
      {     5.0,  -1.757,  32.6994}, //  -1.757  26.3095
      {     8.2,  -1.755,  32.6988}, //  -1.755  26.3089
      {    13.7,  -1.752,  32.6986}, //  -1.752  26.3087
      {    19.0,  -1.757,  32.6992}, //  -1.757  26.3093
      {    23.8,  -1.752,  32.6988}, //  -1.752  26.3089
      {    28.5,  -1.745,  32.7007}, //  -1.746  26.3103
      {    39.0,  -1.735,  32.6991}, //  -1.736  26.3088
      {    49.2,  -1.722,  32.7038}, //  -1.723  26.3123
      {    58.7,  -1.728,  32.7018}, //  -1.729  26.3108
      {    68.5,  -1.715,  32.7061}, //  -1.716  26.3140
      {    78.7,  -1.720,  32.7062}, //  -1.721  26.3142
      {    88.8,  -1.673,  32.7262}, //  -1.675  26.3294
      {    98.8,  -0.893,  32.9136}, //  -0.896  26.4589
      {   108.9,  -0.013,  33.1037}, //  -0.017  26.5763
      {   119.2,   0.316,  33.1914}, //   0.312  26.6305
      {   129.2,   0.379,  33.2255}, //   0.374  26.6547
      {   139.2,   0.403,  33.2421}, //   0.398  26.6668
      {   149.0,   0.392,  33.2465}, //   0.386  26.6710
      {   158.8,   0.355,  33.2675}, //   0.349  26.6899
      {   168.8,   0.320,  33.2793}, //   0.314  26.7013
      {   178.8,   0.304,  33.2915}, //   0.297  26.7120
      {   188.7,   0.288,  33.3079}, //   0.281  26.7261
      {   198.6,   0.311,  33.3287}, //   0.303  26.7417
      {   218.5,   0.294,  33.3556}, //   0.286  26.7643
      {   239.2,   0.484,  33.3855}, //   0.474  26.7782
      {   259.1,   0.628,  33.4128}, //   0.617  26.7921
      {   278.8,   0.564,  33.4192}, //   0.553  26.8010
      {   298.3,   0.409,  33.4259}, //   0.397  26.8150
      {   319.2,   0.478,  33.4527}, //   0.465  26.8328
      {   339.0,   0.689,  33.4950}, //   0.675  26.8550
      {   358.6,   1.180,  33.5757}, //   1.163  26.8897
      {   379.2,   1.347,  33.6270}, //   1.329  26.9200
      {   398.2,   1.392,  33.6579}, //   1.372  26.9418
      {   419.2,   1.506,  33.6988}, //   1.485  26.9669
      {   438.9,   1.621,  33.7356}, //   1.598  26.9884
      {   459.2,   1.624,  33.7355}, //   1.600  26.9882
      {   468.5,   1.626,  33.7360}, //   1.602  26.9885
      {   499.0,   1.700,  33.7250}, //   1.674  26.9745
      {   549.4,   1.841,  33.8090}, //   1.811  27.0318
      {   599.0,   2.004,  33.9060}, //   1.970  27.0975
      {   649.3,   2.136,  33.9890}, //   2.099  27.1540
      {   699.3,   2.223,  34.0580}, //   2.182  27.2027
      {   749.1,   2.281,  34.1140}, //   2.236  27.2432
      {   799.4,   2.310,  34.1520}, //   2.262  27.2715
      {   849.4,   2.331,  34.1860}, //   2.279  27.2973
      {   899.2,   2.349,  34.2340}, //   2.293  27.3346
      {   949.4,   2.348,  34.2780}, //   2.289  27.3701
      {   999.2,   2.340,  34.3210}, //   2.277  27.4055
      {  1049.1,   2.322,  34.3510}, //   2.256  27.4313
      {  1099.2,   2.297,  34.3780}, //   2.228  27.4552
      {  1148.9,   2.268,  34.4080}, //   2.195  27.4818
      {  1199.2,   2.235,  34.4300}, //   2.159  27.5024
      {  1249.2,   2.210,  34.4450}, //   2.130  27.5167
      {  1299.3,   2.185,  34.4580}, //   2.102  27.5294
      {  1348.8,   2.160,  34.4710}, //   2.073  27.5421
      {  1399.2,   2.139,  34.4820}, //   2.049  27.5528
      {  1449.5,   2.119,  34.4910}, //   2.025  27.5619
      {  1499.4,   2.105,  34.4980}, //   2.007  27.5689
      {  1548.9,   2.087,  34.5050}, //   1.986  27.5762
      {  1599.0,   2.069,  34.5120}, //   1.964  27.5835
      {  1649.1,   2.050,  34.5200}, //   1.941  27.5917
      {  1653.8,   2.050,  34.5190}, //   1.941  27.5910
   };
   unsigned int n = sizeof(pts)/sizeof(HydroObs);
   
   // make sure there are at least 3 points in the profile
   if (n<3)
   {
      swifterr("error in OkhotskSeaIceHydrography::OkhotskSeaIceHydrography() ... "
               "Hydrographic profile must contain at least 3 points\n");
   }
   
   // make sure the profile starts at the surface
   if (pts[0].p!=0)
   {
      swifterr("error in OkhotskSeaIceHydrography::OkhotskSeaIceHydrography() ... "
               "First observation in profile must be at surface.\n");
   }
   
   // make sure the pressure increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (pts[i].p<=pts[i-1].p)
      {
         swifterr("error in OkhotskSeaIceHydrography::OkhotskSeaIceHydrography() ... "
                  "Hydrographic profile not monotonically increasing in pressure.\n");
      }
   }

   // load the profiles into the linear spline objects
   for (unsigned int i=0; i<n; i++)
   {
      t.Append(pts[i].p,pts[i].t); s.Append(pts[i].p,pts[i].s);
   }

   // seek extremes in the profiles
   t.SeekExtremes(); s.SeekExtremes();
   
   // make sure the density increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (Rho(pts[i].p)<=Rho(pts[i-1].p))
      {
         swifterr("error in OkhotskSeaIceHydrography::OkhotskSeaIceHydrography() ... "
                  "Hydrographic profile not monotonically increasing in density.\n");
      }
   }
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
RossSeaHydrography::RossSeaHydrography(void)
{
   HydroObs pts[]=
   {
      //     lat     lon       date    stnid 
      //  -62.37  219.82 10/06/2005 2019.023 
      {    0.0, -1.866, 33.905},
      {    4.5, -1.866, 33.900},
      {   10.0, -1.740, 33.932}, //  -1.740  27.3111
      {   23.8, -1.735, 33.936}, //  -1.735  27.3142
      {   30.9, -1.722, 33.942}, //  -1.723  27.3187
      {   45.6, -1.703, 33.949}, //  -1.704  27.3239
      {   59.5, -1.698, 33.950}, //  -1.699  27.3246
      {   75.4, -1.676, 33.958}, //  -1.678  27.3305
      {   99.0, -1.175, 34.063}, //  -1.178  27.4003
      {  123.3, -0.963, 34.103}, //  -0.966  27.4251
      {  139.4, -0.947, 34.106}, //  -0.951  27.4270
      {  147.2, -0.935, 34.108}, //  -0.939  27.4281
      {  200.6,  0.153, 34.386}, //   0.145  27.6029
      {  210.4,  0.319, 34.464}, //   0.311  27.6566
      {  221.4,  0.495, 34.511}, //   0.486  27.6844
      {  232.3,  0.626, 34.537}, //   0.616  27.6975
      {  244.2,  0.696, 34.558}, //   0.685  27.7102
      {  256.2,  0.841, 34.586}, //   0.829  27.7237
      {  269.9,  1.080, 34.623}, //   1.067  27.7379
      {  284.3,  1.212, 34.648}, //   1.198  27.7491
      {  297.9,  1.365, 34.672}, //   1.350  27.7577
      {  313.2,  1.435, 34.686}, //   1.419  27.7641
      {  330.0,  1.461, 34.697}, //   1.444  27.7711
      {  347.2,  1.515, 34.707}, //   1.497  27.7753
      {  364.2,  1.509, 34.712}, //   1.490  27.7798
      {  383.5,  1.518, 34.718}, //   1.498  27.7840
      {  403.3,  1.493, 34.717}, //   1.472  27.7851
      {  423.1,  1.485, 34.720}, //   1.463  27.7882
      {  445.3,  1.492, 34.724}, //   1.469  27.7910
      {  468.1,  1.466, 34.725}, //   1.442  27.7938
      {  492.1,  1.450, 34.727}, //   1.424  27.7966
      {  517.1,  1.437, 34.728}, //   1.410  27.7985
      {  544.3,  1.436, 34.730}, //   1.407  27.8002
      {  571.8,  1.395, 34.729}, //   1.365  27.8025
      {  601.1,  1.381, 34.730}, //   1.349  27.8044
      {  632.1,  1.360, 34.730}, //   1.327  27.8060
      {  665.3,  1.331, 34.730}, //   1.296  27.8082
      {  699.0,  1.312, 34.730}, //   1.275  27.8096
      {  735.4,  1.287, 34.729}, //   1.248  27.8107
      {  772.2,  1.261, 34.729}, //   1.220  27.8127
      {  812.4,  1.238, 34.729}, //   1.195  27.8144
      {  854.0,  1.212, 34.728}, //   1.167  27.8156
      {  898.3,  1.192, 34.727}, //   1.144  27.8163
      {  944.2,  1.161, 34.726}, //   1.110  27.8178
      {  991.9,  1.132, 34.725}, //   1.079  27.8191
      {  997.5,  1.102, 34.724}, //   1.049  27.8204
      { 1043.1,  1.080, 34.723}, //   1.024  27.8212
      { 1097.2,  1.050, 34.723}, //   0.991  27.8234
      { 1153.1,  1.013, 34.721}, //   0.951  27.8245
      { 1212.2,  0.984, 34.720}, //   0.918  27.8258
      { 1274.2,  0.954, 34.718}, //   0.884  27.8264
      { 1339.8,  0.922, 34.718}, //   0.848  27.8287
      { 1408.4,  0.885, 34.716}, //   0.807  27.8297
      { 1481.4,  0.848, 34.715}, //   0.766  27.8316
      { 1557.2,  0.815, 34.713}, //   0.728  27.8324
      { 1636.2,  0.780, 34.712}, //   0.688  27.8341
      { 1720.2,  0.752, 34.711}, //   0.654  27.8353
      { 1809.0,  0.718, 34.709}, //   0.615  27.8362
      { 1900.8,  0.685, 34.708}, //   0.575  27.8378
      { 2000.1,  0.646, 34.707}, //   0.530  27.8397
   };
   unsigned int n = sizeof(pts)/sizeof(HydroObs);
   
   // make sure there are at least 3 points in the profile
   if (n<3)
   {
      swifterr("error in RossSeaHydrography::RossSeaHydrography() ... "
               "Hydrographic profile must contain at least 3 points\n");
   }
   
   // make sure the profile starts at the surface
   if (pts[0].p!=0)
   {
      swifterr("error in RossSeaHydrography::RossSeaHydrography() ... "
               "First observation in profile must be at surface.\n");
   }
   
   // make sure the pressure increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (pts[i].p<=pts[i-1].p)
      {
         swifterr("error in RossSeaHydrography::RossSeaHydrography() ... "
                  "Hydrographic profile not monotonically increasing in pressure.\n");
      }
   }

   // load the profiles into the linear spline objects
   for (unsigned int i=0; i<n; i++)
   {
      t.Append(pts[i].p,pts[i].t); s.Append(pts[i].p,pts[i].s);
   }

   // seek extremes in the profiles
   t.SeekExtremes(); s.SeekExtremes();
   
   // make sure the density increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (Rho(pts[i].p)<=Rho(pts[i-1].p))
      {
         swifterr("error in RossSeaHydrography::RossSeaHydrography() ... "
                  "Hydrographic profile not monotonically increasing in density.\n");
      }
   }
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
RossSeaIceHydrography::RossSeaIceHydrography(void)
{
   HydroObs pts[]=
   {
      //     lat     lon       date   stnid
      //  -73.04  171.17 07/11/2001 476.052
      {    0.0, -1.866, 34.337}, //  -1.866  27.6437
      {   39.4, -1.863, 34.337}, //  -1.864  27.6437
      {   59.5, -1.862, 34.342}, //  -1.863  27.6436
      {  256.2,  0.841, 34.586}, //   0.829  27.7237
      {  297.9,  1.365, 34.672}, //   1.350  27.7577
      {  347.2,  1.515, 34.707}, //   1.497  27.7753
      {  364.2,  1.509, 34.712}, //   1.490  27.7798
      {  383.5,  1.518, 34.718}, //   1.498  27.7840
      {  403.3,  1.493, 34.717}, //   1.472  27.7851
      {  423.1,  1.485, 34.720}, //   1.463  27.7882
      {  445.3,  1.492, 34.724}, //   1.469  27.7910
      {  468.1,  1.466, 34.725}, //   1.442  27.7938
      {  492.1,  1.450, 34.727}, //   1.424  27.7966
      {  517.1,  1.437, 34.728}, //   1.410  27.7985
      {  544.3,  1.436, 34.730}, //   1.407  27.8002
      {  571.8,  1.395, 34.729}, //   1.365  27.8025
      {  601.1,  1.381, 34.730}, //   1.349  27.8044
      {  632.1,  1.360, 34.730}, //   1.327  27.8060
      {  665.3,  1.331, 34.730}, //   1.296  27.8082
      {  699.0,  1.312, 34.730}, //   1.275  27.8096
      {  735.4,  1.287, 34.729}, //   1.248  27.8107
      {  772.2,  1.261, 34.729}, //   1.220  27.8127
      {  812.4,  1.238, 34.729}, //   1.195  27.8144
      {  854.0,  1.212, 34.728}, //   1.167  27.8156
      {  898.3,  1.192, 34.727}, //   1.144  27.8163
      {  944.2,  1.161, 34.726}, //   1.110  27.8178
      {  991.9,  1.132, 34.725}, //   1.079  27.8191
      {  997.5,  1.102, 34.724}, //   1.049  27.8204
      { 1043.1,  1.080, 34.723}, //   1.024  27.8212
      { 1097.2,  1.050, 34.723}, //   0.991  27.8234
      { 1153.1,  1.013, 34.721}, //   0.951  27.8245
      { 1212.2,  0.984, 34.720}, //   0.918  27.8258
      { 1274.2,  0.954, 34.718}, //   0.884  27.8264
      { 1339.8,  0.922, 34.718}, //   0.848  27.8287
      { 1408.4,  0.885, 34.716}, //   0.807  27.8297
      { 1481.4,  0.848, 34.715}, //   0.766  27.8316
      { 1557.2,  0.815, 34.713}, //   0.728  27.8324
      { 1636.2,  0.780, 34.712}, //   0.688  27.8341
      { 1720.2,  0.752, 34.711}, //   0.654  27.8353
      { 1809.0,  0.718, 34.709}, //   0.615  27.8362
      { 1900.8,  0.685, 34.708}, //   0.575  27.8378
      { 2200.1,  0.600, 34.708},
   };
   unsigned int n = sizeof(pts)/sizeof(HydroObs);
   
   // make sure there are at least 3 points in the profile
   if (n<3)
   {
      swifterr("error in RossSeaIceHydrography::RossSeaIceHydrography() ... "
               "Hydrographic profile must contain at least 3 points\n");
   }
   
   // make sure the profile starts at the surface
   if (pts[0].p!=0)
   {
      swifterr("error in RossSeaIceHydrography::RossSeaIceHydrography() ... "
               "First observation in profile must be at surface.\n");
   }
   
   // make sure the pressure increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (pts[i].p<=pts[i-1].p)
      {
         swifterr("error in RossSeaIceHydrography::RossSeaIceHydrography() ... "
                  "Hydrographic profile not monotonically increasing in pressure.\n");
      }
   }

   // load the profiles into the linear spline objects
   for (unsigned int i=0; i<n; i++)
   {
      t.Append(pts[i].p,pts[i].t); s.Append(pts[i].p,pts[i].s);
   }

   // seek extremes in the profiles
   t.SeekExtremes(); s.SeekExtremes();
   
   // make sure the density increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (Rho(pts[i].p)<=Rho(pts[i-1].p))
      {
         swifterr("error in RossSeaIceHydrography::RossSeaIceHydrography() ... "
                  "Hydrographic profile not monotonically increasing in density.\n");
      }
   }
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
SouthPacificNoppHydrography::SouthPacificNoppHydrography(void)
{
   HydroObs pts[]=
   {
      //     lat     lon       date   time  zmax   stnid  n
      //  -12.10  230.24 11/14/2000  1.593  2002 421.001 72
      //     p        t        s        theta    sigma
      {    0.0,  26.483,  35.688}, //  26.482  23.4029
      {    9.5,  26.493,  35.690}, //  26.491  23.4017
      {   19.1,  26.431,  35.689}, //  26.427  23.4212
      {   29.2,  26.366,  35.689}, //  26.359  23.4424
      {   39.3,  26.354,  35.691}, //  26.345  23.4484
      {   49.5,  26.348,  35.690}, //  26.337  23.4503
      {   59.1,  25.689,  35.769}, //  25.676  23.7165
      {   69.3,  25.507,  35.809}, //  25.492  23.8037
      {   79.1,  25.154,  35.869}, //  25.137  23.9582
      {   89.1,  25.074,  35.999}, //  25.055  24.0816
      {   99.1,  24.932,  36.093}, //  24.910  24.1967
      {  119.7,  24.277,  36.283}, //  24.251  24.5397
      {  139.0,  22.670,  36.199}, //  22.642  24.9482
      {  159.1,  21.862,  36.099}, //  21.830  25.1023
      {  179.2,  21.323,  36.006}, //  21.288  25.1823
      {  199.3,  20.402,  35.824}, //  20.364  25.2947
      {  259.2,  15.191,  34.961}, //  15.151  25.9093
      {  299.3,  11.959,  34.643}, //  11.920  26.3276
      {  349.4,  10.261,  34.666}, //  10.220  26.6538
      {  398.9,   9.256,  34.646}, //   9.212  26.8071
      {  449.5,   8.324,  34.611}, //   8.277  26.9268
      {  499.3,   7.675,  34.586}, //   7.625  27.0042
      {  549.1,   7.257,  34.567}, //   7.204  27.0495
      {  599.2,   6.861,  34.555}, //   6.804  27.0953
      {  649.3,   6.485,  34.540}, //   6.425  27.1343
      {  699.1,   6.041,  34.524}, //   5.979  27.1794
      {  749.0,   5.720,  34.517}, //   5.655  27.2143
      {  799.2,   5.477,  34.514}, //   5.409  27.2419
      {  849.5,   5.192,  34.511}, //   5.121  27.2737
      {  899.1,   4.923,  34.514}, //   4.849  27.3074
      {  949.1,   4.672,  34.519}, //   4.596  27.3398
      {  999.5,   4.460,  34.525}, //   4.381  27.3681
      { 1099.5,   4.090,  34.537}, //   4.005  27.4174
      { 1199.3,   3.798,  34.551}, //   3.707  27.4589
      { 1299.3,   3.502,  34.565}, //   3.406  27.4998
      { 1399.1,   3.258,  34.576}, //   3.156  27.5323
      { 1499.3,   3.005,  34.589}, //   2.897  27.5664
      { 1599.0,   2.787,  34.599}, //   2.673  27.5943
      { 1699.5,   2.668,  34.606}, //   2.547  27.6109
      { 1799.6,   2.485,  34.616}, //   2.358  27.6349
      { 1899.6,   2.337,  34.626}, //   2.204  27.6557
      { 1999.4,   2.197,  34.638}, //   2.057  27.6771
      { 2001.7,   2.194,  34.639}, //   2.054  27.6782
      { 2500.0,   2.194,  34.639}
   };
   unsigned int n = sizeof(pts)/sizeof(HydroObs);
   
   // make sure there are at least 3 points in the profile
   if (n<3)
   {
      swifterr("error in SouthPacificNoppHydrography::SouthPacificNoppHydrography() ... "
               "Hydrographic profile must contain at least 3 points\n");
   }
   
   // make sure the profile starts at the surface
   if (pts[0].p!=0)
   {
      swifterr("error in SouthPacificNoppHydrography::SouthPacificNoppHydrography() ... "
               "First observation in profile must be at surface.\n");
   }
   
   // make sure the pressure increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (pts[i].p<=pts[i-1].p)
      {
         swifterr("error in SouthPacificNoppHydrography::SouthPacificNoppHydrography() ... "
                  "Hydrographic profile not monotonically increasing in pressure.\n");
      }
   }

   // load the profiles into the linear spline objects
   for (unsigned int i=0; i<n; i++)
   {
      t.Append(pts[i].p,pts[i].t); s.Append(pts[i].p,pts[i].s);
   }

   // seek extremes in the profiles
   t.SeekExtremes(); s.SeekExtremes();
   
   // make sure the density increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (Rho(pts[i].p)<=Rho(pts[i-1].p))
      {
         swifterr("error in SouthPacificNoppHydrography::SouthPacificNoppHydrography() ... "
                  "Hydrographic profile not monotonically increasing in density.\n");
      }
   }
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
SargassoHydrography::SargassoHydrography(void)
{
   HydroObs pts[]=
   {
      //    lat     lon       date   time  zmax   stnid   n
      //  32.56  295.77 09/08/2000 20.298  2005 422.001  72
      //     p       t       s        theta    sigma
      {    0.0, 27.077, 36.351}, //  27.076  23.7135
      {    9.8, 27.076, 36.352}, //  27.074  23.7149
      {   19.4, 27.010, 36.355}, //  27.006  23.7391
      {   29.7, 25.042, 36.537}, //  25.035  24.4943
      {   39.8, 23.518, 36.637}, //  23.510  25.0283
      {   49.5, 21.962, 36.685}, //  21.952  25.5138
      {   59.4, 21.218, 36.693}, //  21.206  25.7280
      {   69.3, 20.792, 36.672}, //  20.779  25.8293
      {   79.4, 20.426, 36.658}, //  20.411  25.9183
      {   89.5, 19.738, 36.604}, //  19.721  26.0609
      {   99.4, 19.433, 36.602}, //  19.415  26.1398
      {  119.6, 19.264, 36.603}, //  19.242  26.1855
      {  139.1, 18.943, 36.597}, //  18.918  26.2647
      {  159.3, 18.804, 36.596}, //  18.775  26.3004
      {  179.5, 18.712, 36.586}, //  18.680  26.3172
      {  199.4, 18.655, 36.579}, //  18.619  26.3272
      {  249.3, 18.508, 36.565}, //  18.464  26.3560
      {  299.1, 18.319, 36.545}, //  18.266  26.3905
      {  349.3, 18.035, 36.506}, //  17.974  26.4336
      {  399.3, 17.579, 36.434}, //  17.510  26.4927
      {  449.5, 16.959, 36.325}, //  16.884  26.5606
      {  499.5, 16.106, 36.174}, //  16.025  26.6462
      {  549.4, 15.151, 36.017}, //  15.066  26.7427
      {  599.2, 13.839, 35.806}, //  13.751  26.8634
      {  649.4, 12.387, 35.592}, //  12.299  26.9918
      {  699.3, 11.653, 35.488}, //  11.561  27.0523
      {  749.2, 10.235, 35.305}, //  10.144  27.1658
      {  798.9,  9.095, 35.202}, //   9.005  27.2760
      {  849.2,  8.353, 35.156}, //   8.261  27.3570
      {  899.5,  7.405, 35.103}, //   7.314  27.4559
      {  949.4,  6.821, 35.100}, //   6.728  27.5354
      {  999.2,  6.171, 35.068}, //   6.078  27.5966
      { 1099.1,  5.535, 35.070}, //   5.437  27.6787
      { 1199.5,  5.118, 35.060}, //   5.014  27.7214
      { 1299.0,  4.832, 35.046}, //   4.722  27.7440
      { 1399.5,  4.536, 35.023}, //   4.419  27.7596
      { 1499.3,  4.323, 35.010}, //   4.199  27.7732
      { 1599.0,  4.099, 34.988}, //   3.968  27.7801
      { 1699.3,  3.958, 34.981}, //   3.820  27.7899
      { 1799.1,  3.838, 34.974}, //   3.692  27.7974
      { 1899.1,  3.738, 34.969}, //   3.584  27.8043
      { 2004.6,  3.641, 34.968}, //   3.478  27.8139
      { 2500.0,  3.641, 34.968}
   };
   unsigned int n = sizeof(pts)/sizeof(HydroObs);
   
   // make sure there are at least 3 points in the profile
   if (n<3)
   {
      swifterr("error in SargassoHydrography::SargassoHydrography() ... "
               "Hydrographic profile must contain at least 3 points\n");
   }
   
   // make sure the profile starts at the surface
   if (pts[0].p!=0)
   {
      swifterr("error in SargassoHydrography::SargassoHydrography() ... "
               "First observation in profile must be at surface.\n");
   }
   
   // make sure the pressure increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (pts[i].p<=pts[i-1].p)
      {
         swifterr("error in SargassoHydrography::SargassoHydrography() ... "
                  "Hydrographic profile not monotonically increasing in pressure.\n");
      }
   }

   // load the profiles into the linear spline objects
   for (unsigned int i=0; i<n; i++)
   {
      t.Append(pts[i].p,pts[i].t); s.Append(pts[i].p,pts[i].s);
   }

   // seek extremes in the profiles
   t.SeekExtremes(); s.SeekExtremes();
   
   // make sure the density increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (Rho(pts[i].p)<=Rho(pts[i-1].p))
      {
         swifterr("error in SargassoHydrography::SargassoHydrography() ... "
                  "Hydrographic profile not monotonically increasing in density.\n");
      }
   }
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
SargassoModeWaterHydrography::SargassoModeWaterHydrography(void)
{
   HydroObs pts[]=
   {
      //    lat     lon       date   time  zmax    stnid  n
      //  34.67  295.25 03/10/2001 11.247  2001 0422.018 72
      {    0.0,  18.416,  36.628},
      {    5.5,  18.416,  36.628}, //  18.415  26.4166
      {    9.4,  18.415,  36.629}, //  18.413  26.4178
      {   18.9,  18.425,  36.628}, //  18.422  26.4149
      {   29.2,  18.426,  36.627}, //  18.421  26.4143
      {   39.0,  18.427,  36.628}, //  18.420  26.4153
      {   49.4,  18.429,  36.628}, //  18.420  26.4152
      {   59.0,  18.432,  36.628}, //  18.422  26.4149
      {   69.4,  18.434,  36.627}, //  18.422  26.4141
      {   79.5,  18.436,  36.628}, //  18.422  26.4148
      {   89.4,  18.438,  36.628}, //  18.422  26.4147
      {   99.4,  18.439,  36.628}, //  18.421  26.4149
      {  109.5,  18.441,  36.628}, //  18.422  26.4149
      {  119.5,  18.441,  36.628}, //  18.420  26.4153
      {  129.2,  18.443,  36.628}, //  18.420  26.4153
      {  139.5,  18.444,  36.628}, //  18.419  26.4155
      {  149.2,  18.447,  36.628}, //  18.421  26.4151
      {  159.5,  18.448,  36.628}, //  18.420  26.4154
      {  169.4,  18.450,  36.628}, //  18.420  26.4153
      {  179.5,  18.452,  36.628}, //  18.420  26.4152
      {  189.5,  18.452,  36.629}, //  18.418  26.4165
      {  199.0,  18.455,  36.628}, //  18.420  26.4154
      {  209.0,  18.457,  36.627}, //  18.420  26.4145
      {  218.9,  18.459,  36.627}, //  18.420  26.4145
      {  229.2,  18.461,  36.627}, //  18.420  26.4144
      {  238.9,  18.462,  36.628}, //  18.420  26.4154
      {  249.5,  18.464,  36.627}, //  18.420  26.4146
      {  259.3,  18.466,  36.627}, //  18.420  26.4145
      {  269.0,  18.468,  36.628}, //  18.420  26.4152
      {  279.1,  18.470,  36.627}, //  18.421  26.4144
      {  289.4,  18.471,  36.628}, //  18.420  26.4154
      {  299.1,  18.463,  36.625}, //  18.410  26.4155
      {  309.0,  18.469,  36.626}, //  18.414  26.4152
      {  319.2,  18.443,  36.619}, //  18.386  26.4169
      {  329.3,  18.438,  36.618}, //  18.380  26.4178
      {  339.2,  18.446,  36.619}, //  18.386  26.4170
      {  349.4,  18.451,  36.619}, //  18.389  26.4162
      {  359.5,  18.449,  36.618}, //  18.385  26.4164
      {  379.6,  18.444,  36.616}, //  18.377  26.4171
      {  399.2,  18.459,  36.620}, //  18.388  26.4172
      {  449.2,  18.411,  36.607}, //  18.331  26.4216
      {  499.1,  17.626,  36.441}, //  17.540  26.4909
      {  549.4,  17.154,  36.360}, //  17.061  26.5450
      {  599.2,  16.516,  36.247}, //  16.417  26.6111
      {  649.3,  15.812,  36.129}, //  15.708  26.6844
      {  699.5,  14.772,  35.959}, //  14.665  26.7862
      {  749.3,  13.905,  35.820}, //  13.794  26.8652
      {  799.5,  12.624,  35.627}, //  12.513  26.9768
      {  849.4,  11.338,  35.447}, //  11.228  27.0825
      {  899.2,  10.267,  35.315}, //  10.157  27.1713
      {  949.2,   9.101,  35.201}, //   8.993  27.2772
      {  999.0,   8.163,  35.132}, //   8.056  27.3695
      { 1049.0,   7.193,  35.085}, //   7.087  27.4738
      { 1099.5,   6.592,  35.080}, //   6.486  27.5525
      { 1149.5,   6.092,  35.063}, //   5.985  27.6047
      { 1199.3,   5.636,  35.054}, //   5.528  27.6550
      { 1249.6,   5.346,  35.041}, //   5.235  27.6801
      { 1299.3,   5.100,  35.032}, //   4.987  27.7024
      { 1349.0,   4.921,  35.029}, //   4.805  27.7210
      { 1399.4,   4.714,  35.016}, //   4.595  27.7345
      { 1449.4,   4.583,  35.009}, //   4.461  27.7438
      { 1499.1,   4.449,  34.998}, //   4.324  27.7501
      { 1549.4,   4.310,  34.986}, //   4.182  27.7559
      { 1599.4,   4.255,  34.984}, //   4.123  27.7607
      { 1649.2,   4.173,  34.977}, //   4.037  27.7642
      { 1699.1,   4.073,  34.969}, //   3.933  27.7686
      { 1749.0,   3.983,  34.962}, //   3.840  27.7727
      { 1799.6,   3.936,  34.961}, //   3.789  27.7772
      { 1849.1,   3.903,  34.959}, //   3.752  27.7794
      { 1899.4,   3.816,  34.951}, //   3.661  27.7822
      { 1949.3,   3.739,  34.945}, //   3.580  27.7855
      { 1999.7,   3.699,  34.943}, //   3.536  27.7883
      { 2000.6,   3.699,  34.944}, //   3.536  27.7891
      { 2500.0,   3.699,  34.944}
   };
   unsigned int n = sizeof(pts)/sizeof(HydroObs);
   
   // make sure there are at least 3 points in the profile
   if (n<3)
   {
      swifterr("error in SargassoModeWaterHydrography::SargassoModeWaterHydrography() ... "
               "Hydrographic profile must contain at least 3 points\n");
   }
   
   // make sure the profile starts at the surface
   if (pts[0].p!=0)
   {
      swifterr("error in SargassoModeWaterHydrography::SargassoModeWaterHydrography() ... "
               "First observation in profile must be at surface.\n");
   }
   
   // make sure the pressure increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (pts[i].p<=pts[i-1].p)
      {
         swifterr("error in SargassoModeWaterHydrography::SargassoModeWaterHydrography() ... "
                  "Hydrographic profile not monotonically increasing in pressure.\n");
      }
   }

   // load the profiles into the linear spline objects
   for (unsigned int i=0; i<n; i++)
   {
      t.Append(pts[i].p,pts[i].t); s.Append(pts[i].p,pts[i].s);
   }

   // seek extremes in the profiles
   t.SeekExtremes(); s.SeekExtremes();
   
   // make sure the density increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (Rho(pts[i].p)<=Rho(pts[i-1].p))
      {
         swifterr("error in SargassoModeWaterHydrography::SargassoModeWaterHydrography() ... "
                  "Hydrographic profile not monotonically increasing in density.\n");
      }
   }
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
SubtropicalNePacificHydrography::SubtropicalNePacificHydrography(void)
{
   HydroObs pts[]=
   {
      //    lat     lon       date   time  zmax   stnid 
      //  36.60  236.89 07/20/2001 10.387  1999 544.009 
      //     p       t        s   //  theta    sigma
      {    0.0, 14.299,  33.611}, // 14.298  25.0522
      {    9.6, 14.295,  33.610}, // 14.294  25.0523
      {   19.5, 13.841,  33.609}, // 13.838  25.1464
      {   29.6, 12.132,  33.568}, // 12.128  25.4533
      {   39.2, 10.028,  33.493}, // 10.024  25.7717
      {   49.6,  9.967,  33.592}, //  9.961  25.8595
      {   59.5,  9.740,  33.732}, //  9.733  26.0068
      {   69.6,  9.558,  33.762}, //  9.550  26.0604
      {   79.4,  9.329,  33.796}, //  9.320  26.1245
      {   89.2,  9.108,  33.867}, //  9.098  26.2156
      {   99.4,  9.076,  33.926}, //  9.065  26.2671
      {  109.2,  8.996,  33.958}, //  8.984  26.3050
      {  119.5,  8.912,  33.977}, //  8.899  26.3333
      {  129.2,  8.811,  34.002}, //  8.797  26.3689
      {  139.3,  8.645,  34.029}, //  8.630  26.4160
      {  149.0,  8.519,  34.039}, //  8.504  26.4434
      {  159.3,  8.387,  34.057}, //  8.371  26.4779
      {  169.5,  8.303,  34.069}, //  8.286  26.5002
      {  179.6,  8.237,  34.078}, //  8.219  26.5173
      {  189.4,  8.069,  34.082}, //  8.050  26.5457
      {  199.4,  7.961,  34.084}, //  7.941  26.5634
      {  209.2,  7.787,  34.091}, //  7.766  26.5945
      {  219.3,  7.713,  34.098}, //  7.692  26.6109
      {  229.2,  7.621,  34.119}, //  7.599  26.6408
      {  239.3,  7.537,  34.127}, //  7.514  26.6593
      {  249.1,  7.509,  34.132}, //  7.485  26.6673
      {  259.1,  7.455,  34.133}, //  7.430  26.6759
      {  269.0,  7.417,  34.135}, //  7.391  26.6830
      {  279.5,  7.333,  34.145}, //  7.306  26.7029
      {  289.4,  7.269,  34.152}, //  7.242  26.7175
      {  299.2,  7.211,  34.153}, //  7.183  26.7265
      {  309.0,  7.138,  34.150}, //  7.109  26.7344
      {  318.9,  6.887,  34.128}, //  6.858  26.7515
      {  329.2,  6.860,  34.137}, //  6.830  26.7624
      {  339.2,  6.738,  34.127}, //  6.707  26.7710
      {  349.4,  6.580,  34.136}, //  6.549  26.7992
      {  359.6,  6.340,  34.125}, //  6.308  26.8220
      {  379.1,  6.056,  34.135}, //  6.023  26.8664
      {  399.3,  5.970,  34.156}, //  5.936  26.8940
      {  449.2,  5.718,  34.198}, //  5.680  26.9589
      {  499.5,  5.570,  34.227}, //  5.528  27.0003
      {  549.5,  5.385,  34.258}, //  5.340  27.0474
      {  599.2,  5.213,  34.281}, //  5.164  27.0863
      {  649.2,  5.087,  34.309}, //  5.034  27.1236
      {  699.4,  4.880,  34.348}, //  4.824  27.1785
      {  749.4,  4.651,  34.375}, //  4.592  27.2259
      {  799.6,  4.473,  34.394}, //  4.411  27.2607
      {  849.4,  4.339,  34.411}, //  4.274  27.2890
      {  899.2,  4.157,  34.431}, //  4.089  27.3244
      {  949.5,  4.030,  34.446}, //  3.958  27.3499
      {  999.4,  3.934,  34.454}, //  3.859  27.3664
      { 1007.2,  3.881,  34.462}, //  3.806  27.3782
      { 1049.3,  3.793,  34.473}, //  3.715  27.3961
      { 1099.5,  3.634,  34.483}, //  3.553  27.4201
      { 1149.3,  3.490,  34.494}, //  3.406  27.4431
      { 1199.3,  3.392,  34.500}, //  3.305  27.4576
      { 1249.4,  3.304,  34.506}, //  3.214  27.4710
      { 1299.2,  3.186,  34.515}, //  3.093  27.4895
      { 1349.1,  3.037,  34.525}, //  2.941  27.5113
      { 1399.5,  2.956,  34.534}, //  2.857  27.5261
      { 1449.2,  2.861,  34.537}, //  2.759  27.5372
      { 1499.2,  2.773,  34.544}, //  2.668  27.5508
      { 1549.0,  2.711,  34.548}, //  2.602  27.5597
      { 1599.4,  2.626,  34.555}, //  2.514  27.5729
      { 1649.4,  2.545,  34.561}, //  2.430  27.5849
      { 1699.3,  2.482,  34.566}, //  2.364  27.5944
      { 1749.1,  2.393,  34.574}, //  2.272  27.6085
      { 1799.1,  2.329,  34.579}, //  2.205  27.6180
      { 1849.4,  2.264,  34.584}, //  2.136  27.6275
      { 1899.2,  2.181,  34.589}, //  2.050  27.6384
      { 1949.5,  2.127,  34.595}, //  1.993  27.6478
      { 2001.0,  2.077,  34.602}, //  1.939  27.6576
      { 2500.0,  2.077,  34.602}
   };
   unsigned int n = sizeof(pts)/sizeof(HydroObs);
   
   // make sure there are at least 3 points in the profile
   if (n<3)
   {
      swifterr("error in SubtropicalNePacificHydrography::SubtropicalNePacificHydrography() ... "
               "Hydrographic profile must contain at least 3 points\n");
   }
   
   // make sure the profile starts at the surface
   if (pts[0].p!=0)
   {
      swifterr("error in SubtropicalNePacificHydrography::SubtropicalNePacificHydrography() ... "
               "First observation in profile must be at surface.\n");
   }
   
   // make sure the pressure increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (pts[i].p<=pts[i-1].p)
      {
         swifterr("error in SubtropicalNePacificHydrography::SubtropicalNePacificHydrography() ... "
                  "Hydrographic profile not monotonically increasing in pressure.\n");
      }
   }

   // load the profiles into the linear spline objects
   for (unsigned int i=0; i<n; i++)
   {
      t.Append(pts[i].p,pts[i].t); s.Append(pts[i].p,pts[i].s);
   }

   // seek extremes in the profiles
   t.SeekExtremes(); s.SeekExtremes();
   
   // make sure the density increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (Rho(pts[i].p)<=Rho(pts[i-1].p))
      {
         swifterr("error in SubtropicalNePacificHydrography::SubtropicalNePacificHydrography() ... "
                  "Hydrographic profile not monotonically increasing in density.\n");
      }
   }
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
TropicalAtlanticHydrography::TropicalAtlanticHydrography(void)
{
   HydroObs pts[]=
   {
      //     lat     lon     date   time  zbot  zmax sh co           stnid     n
      //   -0.23    2.33 11/09/58  7.400 *****  4415  * 31  obs,831,299241    24
      //     p       t       s       theta  sigma     O2
      {    0.0, 26.530, 35.066}, // 26.530 22.919  4.380
      {   45.1, 23.060, 35.741}, // 23.051 24.483  4.270
      {   95.2, 17.210, 35.809}, // 17.194 26.090  3.120
      {  190.7, 13.950, 35.420}, // 13.922 26.529  3.210
      {  286.2, 11.510, 35.105}, // 11.474 26.771  1.530
      {  381.7,  8.330, 34.757}, //  8.290 27.039  1.940
      {  477.3,  7.320, 34.653}, //  7.274 27.107  2.450
      {  573.0,  6.230, 34.560}, //  6.179 27.182  2.820
      {  668.7,  5.390, 34.512}, //  5.334 27.249  2.980
      {  769.6,  4.660, 34.520}, //  4.599 27.340  3.200
      {  961.3,  4.330, 34.624}, //  4.255 27.460  3.530
      { 1158.2,  4.360, 34.746}, //  4.267 27.556  3.770
      { 1360.4,  4.200, 34.925}, //  4.090 27.717  4.670
      { 1557.8,  4.010, 34.962}, //  3.884 27.768  5.160
      { 1806.0,  3.760, 34.965}, //  3.615 27.798  5.310
      { 1998.7,  3.440, 34.959}, //  3.281 27.826  5.460
      { 2196.6,  3.250, 34.949}, //  3.075 27.838  5.350
      { 2491.4,  2.950, 34.939}, //  2.752 27.859  5.330
      { 2791.6,  2.790, 34.922}, //  2.565 27.862  5.390
      { 3087.1,  2.670, 34.915}, //  2.417 27.869  5.230
      { 3383.0,  2.540, 34.908}, //  2.259 27.877  5.320
      { 3986.3,  2.380, 34.894}, //  2.037 27.884  5.310
      { 4283.4,  2.340, 34.887}, //  1.963 27.884  5.330
      { 4483.4,  2.290, 34.883}, //  1.891 27.887  5.260
   };
   unsigned int n = sizeof(pts)/sizeof(HydroObs);
   
   // make sure there are at least 3 points in the profile
   if (n<3)
   {
      swifterr("error in TropicalAtlanticHydrography::TropicalAtlanticHydrography() ... "
               "Hydrographic profile must contain at least 3 points\n");
   }
   
   // make sure the profile starts at the surface
   if (pts[0].p!=0)
   {
      swifterr("error in TropicalAtlanticHydrography::TropicalAtlanticHydrography() ... "
               "First observation in profile must be at surface.\n");
   }
   
   // make sure the pressure increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (pts[i].p<=pts[i-1].p)
      {
         swifterr("error in TropicalAtlanticHydrography::TropicalAtlanticHydrography() ... "
                  "Hydrographic profile not monotonically increasing in pressure.\n");
      }
   }

   // load the profiles into the linear spline objects
   for (unsigned int i=0; i<n; i++)
   {
      t.Append(pts[i].p,pts[i].t); s.Append(pts[i].p,pts[i].s);
   }

   // seek extremes in the profiles
   t.SeekExtremes(); s.SeekExtremes();
   
   // make sure the density increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (Rho(pts[i].p)<=Rho(pts[i-1].p))
      {
         swifterr("error in TropicalAtlanticHydrography::TropicalAtlanticHydrography() ... "
                  "Hydrographic profile not monotonically increasing in density.\n");
      }
   }
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
TropicalPacificHydrography::TropicalPacificHydrography(void)
{
   HydroObs pts[]=
   {
      //     lat     lon     date   time  zbot  zmax sh co           stnid     n
      //   -1.52  221.16 06/01/2004 19.361     *  1125  *  *        1528.001     71
      //     p       t       s       theta  sigma     O2
      {    0.0, 27.379, 35.317}, //  27.378  22.8373
      {    4.4, 27.379, 35.317}, //  27.378  22.8373
      {    6.2, 27.378, 35.318}, //  27.377  22.8385
      {   10.4, 27.379, 35.318}, //  27.377  22.8385
      {   14.4, 27.379, 35.317}, //  27.376  22.8380
      {   19.1, 27.379, 35.317}, //  27.375  22.8384
      {   24.5, 27.380, 35.318}, //  27.374  22.8392
      {   29.3, 27.381, 35.318}, //  27.374  22.8393
      {   33.9, 27.382, 35.318}, //  27.374  22.8393
      {   38.9, 27.382, 35.318}, //  27.373  22.8397
      {   44.3, 27.384, 35.318}, //  27.374  22.8394
      {   49.4, 27.384, 35.318}, //  27.373  22.8398
      {   54.2, 27.384, 35.317}, //  27.371  22.8394
      {   59.5, 27.386, 35.317}, //  27.372  22.8392
      {   64.3, 27.374, 35.316}, //  27.359  22.8426
      {   69.4, 27.332, 35.317}, //  27.316  22.8573
      {   74.4, 27.160, 35.336}, //  27.143  22.9272
      {   79.4, 27.107, 35.342}, //  27.089  22.9491
      {   84.4, 26.927, 35.356}, //  26.908  23.0175
      {   89.8, 26.036, 35.509}, //  26.016  23.4144
      {   94.7, 25.717, 35.515}, //  25.696  23.5185
      {   99.7, 24.112, 35.688}, //  24.091  24.1370
      {  104.5, 23.650, 35.654}, //  23.628  24.2482
      {  109.5, 21.798, 35.664}, //  21.776  24.7866
      {  115.5, 21.152, 35.632}, //  21.130  24.9411
      {  121.5, 19.086, 35.478}, //  19.064  25.3713
      {  127.5, 18.078, 35.416}, //  18.056  25.5780
      {  133.7, 17.291, 35.343}, //  17.269  25.7142
      {  140.5, 15.732, 35.237}, //  15.710  25.9969
      {  147.4, 15.045, 35.175}, //  15.023  26.1027
      {  155.2, 14.182, 35.087}, //  14.159  26.2214
      {  163.5, 13.524, 35.010}, //  13.501  26.2994
      {  171.4, 12.895, 34.946}, //  12.872  26.3774
      {  180.4, 12.645, 34.929}, //  12.621  26.4140
      {  190.4, 12.525, 34.918}, //  12.500  26.4293
      {  200.4, 12.290, 34.892}, //  12.263  26.4551
      {  210.2, 12.112, 34.875}, //  12.084  26.4764
      {  221.3, 12.075, 34.873}, //  12.046  26.4822
      {  232.3, 12.018, 34.869}, //  11.988  26.4903
      {  244.0, 11.909, 34.857}, //  11.877  26.5019
      {  255.8, 11.867, 34.851}, //  11.834  26.5055
      {  269.8, 11.857, 34.849}, //  11.822  26.5062
      {  283.9, 11.806, 34.842}, //  11.769  26.5107
      {  297.9, 11.395, 34.814}, //  11.357  26.5658
      {  313.9, 11.217, 34.805}, //  11.178  26.5918
      {  330.0, 11.143, 34.799}, //  11.102  26.6010
      {  346.9, 10.948, 34.789}, //  10.905  26.6288
      {  364.3, 10.549, 34.769}, //  10.505  26.6844
      {  383.4, 10.017, 34.736}, //   9.972  26.7509
      {  403.1,  9.315, 34.688}, //   9.270  26.8305
      {  423.9,  8.943, 34.664}, //   8.897  26.8718
      {  445.3,  8.564, 34.645}, //   8.517  26.9167
      {  468.0,  8.367, 34.636}, //   8.318  26.9402
      {  492.4,  8.032, 34.625}, //   7.981  26.9824
      {  517.9,  7.993, 34.623}, //   7.940  26.9870
      {  544.2,  7.891, 34.617}, //   7.836  26.9978
      {  572.3,  7.499, 34.600}, //   7.442  27.0416
      {  601.2,  7.321, 34.591}, //   7.262  27.0602
      {  632.5,  6.888, 34.574}, //   6.828  27.1071
      {  665.4,  6.616, 34.565}, //   6.554  27.1369
      {  698.8,  6.382, 34.558}, //   6.318  27.1626
      {  734.8,  6.015, 34.551}, //   5.949  27.2045
      {  773.2,  5.629, 34.545}, //   5.562  27.2479
      {  812.2,  5.447, 34.545}, //   5.378  27.2702
      {  854.3,  5.216, 34.546}, //   5.144  27.2987
      {  898.3,  4.960, 34.548}, //   4.886  27.3301
      {  944.4,  4.778, 34.548}, //   4.701  27.3510
      {  991.8,  4.486, 34.548}, //   4.407  27.3835
      { 1001.4,  4.440, 34.554}, //   4.361  27.3933
      { 1042.7,  4.232, 34.542}, //   4.151  27.4062
      { 1097.2,  4.124, 34.561}, //   4.039  27.4330
      { 1125.0,  4.032, 34.566}, //   3.945  27.4467
      { 1148.9,  3.926, 34.572}, //   3.838  27.4624
      { 1199.3,  3.833, 34.575}, //   3.742  27.4746
      { 1249.4,  3.679, 34.580}, //   3.585  27.4942
      { 1299.5,  3.536, 34.586}, //   3.439  27.5133
      { 1349.3,  3.394, 34.591}, //   3.294  27.5312
      { 1399.4,  3.248, 34.597}, //   3.146  27.5500
      { 1449.4,  3.129, 34.603}, //   3.024  27.5661
      { 1499.3,  3.004, 34.608}, //   2.896  27.5817
      { 1549.0,  2.880, 34.613}, //   2.769  27.5971
      { 1599.0,  2.790, 34.618}, //   2.676  27.6093
      { 1649.0,  2.689, 34.623}, //   2.572  27.6223
      { 1699.6,  2.610, 34.629}, //   2.490  27.6342
      { 1749.5,  2.555, 34.632}, //   2.431  27.6415
      { 1799.4,  2.498, 34.635}, //   2.371  27.6490
      { 1849.3,  2.430, 34.639}, //   2.300  27.6582
      { 1898.8,  2.351, 34.643}, //   2.218  27.6682
      { 1949.0,  2.283, 34.648}, //   2.146  27.6780
      { 1999.0,  2.238, 34.651}, //   2.098  27.6843
      { 3500.0,  2.238, 34.651}, //   2.098  27.6843
   };
   unsigned int n = sizeof(pts)/sizeof(HydroObs);
   
   // make sure there are at least 3 points in the profile
   if (n<3)
   {
      swifterr("error in TropicalPacificHydrography::TropicalPacificHydrography() ... "
               "Hydrographic profile must contain at least 3 points\n");
   }
   
   // make sure the profile starts at the surface
   if (pts[0].p!=0)
   {
      swifterr("error in TropicalPacificHydrography::TropicalPacificHydrography() ... "
               "First observation in profile must be at surface.\n");
   }
   
   // make sure the pressure increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (pts[i].p<=pts[i-1].p)
      {
         swifterr("error in TropicalPacificHydrography::TropicalPacificHydrography() ... "
                  "Hydrographic profile not monotonically increasing in pressure.\n");
      }
   }

   // load the profiles into the linear spline objects
   for (unsigned int i=0; i<n; i++)
   {
      t.Append(pts[i].p,pts[i].t); s.Append(pts[i].p,pts[i].s);
   }

   // seek extremes in the profiles
   t.SeekExtremes(); s.SeekExtremes();
   
   // make sure the density increases monotonically
   for (unsigned int i=1; i<n; i++)
   {
      if (Rho(pts[i].p)<=Rho(pts[i-1].p))
      {
         swifterr("error in TropicalPacificHydrography::TropicalPacificHydrography() ... "
                  "Hydrographic profile not monotonically increasing in density.\n");
      }
   }
}

/*------------------------------------------------------------------------*/
/* function to compute the insitu density at a given pressure             */
/*------------------------------------------------------------------------*/
double Hydrography::Rho(float p)
{
   double Rho = 1 + eqstate(S(p),T(p),p)/1000;

   return Rho;
}

/*------------------------------------------------------------------------*/
/* function to compute the salinity at a given pressure                   */
/*------------------------------------------------------------------------*/
double Hydrography::S(float p) 
{
   double S=NaN();
   
   if (inCRange(s.xmin,p,s.xmax)) {S=s(p);}
   else swifterr("error in Hydrography::S() ... "
                 "pressure (%g) out of range: [%g, %g]\n",p,s.xmin,s.xmax);

   return S;
}

/*------------------------------------------------------------------------*/
/* function to compute the temperature at a given pressure                */
/*------------------------------------------------------------------------*/
double Hydrography::T(float p) 
{
   double T=NaN();
   
   if (inCRange(t.xmin,p,t.xmax)) {T=t(p);}
   else swifterr("error in Hydrography::T() ... "
                 "pressure (%g) out of range: [%g, %g]\n",p,t.xmin,t.xmax);

   return T;
}

#endif // HYDROOBS_CPP
#endif // HYDROOBS_OOP
