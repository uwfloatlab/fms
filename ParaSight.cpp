#ifndef PARASIGHT_OOP
#define PARASIGHT_OOP
  
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * $Id: ParaSight.cpp,v 1.1.1.1 2010/07/13 17:33:54 swift Exp $
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
 * $Log: ParaSight.cpp,v $
 * Revision 1.1.1.1  2010/07/13 17:33:54  swift
 * This distribution contains the source code for the Float Mission Simulator
 * used to simulate, debug, and test float firmware.
 *
 * \end{verbatim}
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define ParaSightChangeLog "$RCSfile: ParaSight.cpp,v $  $Revision: 1.1.1.1 $  $Date: 2010/07/13 17:33:54 $"

#include <SpyStream.oop>
#include <PistonSensor.oop>

#define LEADER  "Float Mission Simulator Interface [SwiftWare]"
#define VERSION "$Revision: 1.1.1.1 $  $Date: 2010/07/13 17:33:54 $"

/*========================================================================*/
/* API for the ParaSight interface                                        */
/*========================================================================*/
class ParaSight: public SpyStream, public PistonSensor
{
   // data members
   private:

      // linear calibration parameters
      int C0,C1; float mV0,mV1;
      
   // function members
   public:

      /// initialization constructor for ParaSight class
      ParaSight(Port spystream=1, Port pistonsensor=2);

      // function to set calibration parameters
      void Calibrate(int C0,float mV0,int C1,float mV1);
      
      // function to return the piston extension
      int PistonExtension(void) const;
};

#ifdef PARASIGHT_CPP

/*------------------------------------------------------------------------*/
/* initialization constructor for ParaSight class                         */
/*------------------------------------------------------------------------*/
ParaSight::ParaSight(Port spystream, Port pistonsensor):
      SpyStream(spystream), PistonSensor(pistonsensor),
      C0(0), C1(256), mV0(0.0), mV1(1611.0)
{
   // log the software LEADER
   msg("ParaSight::ParaSight()",LEADER);
   
   // log the software revision
   msg("ParaSight::ParaSight()",VERSION);
}

/*------------------------------------------------------------------------*/
/* function to set calibration parameters                                 */
/*------------------------------------------------------------------------*/
void ParaSight::Calibrate(int C0,float mV0,int C1,float mV1)
{
   // set the calibration parameters
   this->C0=C0; this->mV0=mV0; this->C1=C1; this->mV1=mV1;
}

/*------------------------------------------------------------------------*/
/* function to return the piston extension                                */
/*------------------------------------------------------------------------*/
int ParaSight::PistonExtension(void) const
{
   float mV;

   // initialize the return value
   int count = 255;

   for (int i=0; i<3; i++)
   {
      // read the piston sensor
      if (PistonSensor::millivolts(&mV) && !isnan(mV))
      {
         // compute counts for an 8-bit A/D
         count = (int)((C1-C0)*(mV-mV0)/(mV1-mV0) + C0);
         break;
      }

      // make a log entry
      else msg("ParaSight::PistonExtension()",
               "Attempt to measure piston extension failed.\n");

      // pause for 1 second and try again
      sleep(1);
   }
   
   // make a log entry
   msg("ParaSight::PistonExtension()","PistonExtension: %d",count);
   
   return count;
}
 
#endif // PARASIGHT_CPP
#endif // PARASIGHT_OOP
#undef LEADER
#undef VERSION
