#ifndef PSENSOREMULATOR_OOP
#define PSENSOREMULATOR_OOP

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * $Id: PSensorEmulator.cpp,v 1.1.1.1 2010/07/13 17:33:54 swift Exp $
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
 * $Log: PSensorEmulator.cpp,v $
 * Revision 1.1.1.1  2010/07/13 17:33:54  swift
 * This distribution contains the source code for the Float Mission Simulator
 * used to simulate, debug, and test float firmware.
 *
 * \end{verbatim}
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define PSensorEmulatorChangeLog "$RCSfile: PSensorEmulator.cpp,v $  $Revision: 1.1.1.1 $  $Date: 2010/07/13 17:33:54 $"

#include <MessageLogger.oop>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <regex.h>
#include <assert.h>
#include <math.h>

extern "C"
{
   #include <defs.p>
}

#define LEADER  "Pressure Sensor Emulator [SwiftWare]"
#define VERSION "$Revision: 1.1.1.1 $  $Date: 2010/07/13 17:33:54 $"

/// typedefs to improve readibility
typedef int Port;

/*========================================================================*/
/*                                                                        */
/*========================================================================*/
class PSensorEmulator
{
   // data members
   private:

      /// Typedef of a file descriptor to improve readibility
      typedef int fdes;
      
      /// define a file descriptor for the com port
      fdes fd;

      /// define a structure to hold termio parameters
      termios ioport;

      /// define a streambuffer for the serial port
      FILE *stream;

      /// define a buffer for receiving responses from the D/A convertor
      char buf[MAXSTRLEN+1];

      /// define scaling parameters
      const float mAScale,PScale;
      
   // function members
   private:

      // function to compute the checksum of a buffer
      unsigned char checksum(const char *buf) const;

      // function to close connection to serial port
      void close(void) {if (open()) ::close(fd);}

      // function to set up the DGH D/A convertor
      bool DghSetup(void) const;
      
      // function to connect to a serial port
      bool open(Port com);

      // function to determine if the serial port is open
      bool open(void) const {return (fd>=0);}

      // function to read bytes from the serial port
      bool read(char *buf, int *len, int size, long msec=250) const;

      // function to write bytes to the serial port
      bool write(const char *buf) const;
      
   public:

      // initialization constructor
      PSensorEmulator(Port psensor);

      // destructor for PSensorEmulator class
      ~PSensorEmulator(void) {close();}


      bool operator()(float p) const;
      
      // function to flush the input and output buffers
      bool FlushIO(void) const;
      
      // function to flush the input buffer
      bool FlushRXBuffer(void) const;

      // function to flush the output buffer
      bool FlushTXBuffer(void) const;

      // function to read the voltage from the D/A convertor
      bool milliamps(float mA) const;

      // function to read the number of bytes in the receive buffer
      int RXSpaceUsed(void) const;
};

#ifdef PSENSOREMULATOR_CPP
#include <signal.h>

/*------------------------------------------------------------------------*/
/* initialization constructor for the PSensorEmulator class                  */
/*------------------------------------------------------------------------*/
PSensorEmulator::PSensorEmulator(Port psensor):  fd(-1), stream(0), mAScale(15), PScale(2000)
{
   // log the software LEADER
   msg("PSensorEmulator::PSensorEmulator()",LEADER);

   // log the software revision
   msg("PSensorEmulator::PSensorEmulator()",VERSION);

   // open a connection to the serial port attached to the SpyStream interface
   if (!open(psensor)) exit(1);
}

/*------------------------------------------------------------------------*/
/* overloaded function-call operator to specify the pressure output       */
/*------------------------------------------------------------------------*/
bool PSensorEmulator::operator()(float p) const
{
   float mA = mAScale*p/PScale;

   return milliamps(mA);
}

/*------------------------------------------------------------------------*/
/* function to compute the checksum of a buffer                           */
/*------------------------------------------------------------------------*/
unsigned char PSensorEmulator::checksum(const char *buf) const
{
   unsigned char checksum=0;

   if (buf) {for (unsigned int i=0; i<strlen(buf); i++) {checksum += buf[i];}}

   return checksum;
}

/*------------------------------------------------------------------------*/
/* function to set up the DGH D/A convertor                               */
/*------------------------------------------------------------------------*/
bool PSensorEmulator::DghSetup(void) const
{
   bool status=false;
   int n,len;
   char buf[MAXSTRLEN];
   re_pattern_buffer regex;
   re_registers regs={0,NULL,NULL};

   // define the setup string
   const char *setup = "31020052";
       
   // initialize some regex structure elements
   regex.translate=0; regex.fastmap=0; regex.buffer=0; regex.allocated=0;
   
   // set the features of the regex engine
   re_syntax_options = RE_SYNTAX_EMACS | RE_INTERVALS | RE_NO_BK_BRACES |
      RE_NO_BK_PARENS;

   // define the regex pattern
   const char *pattern = "^(*1SU([0-9A-F]{8}))([0-9A-F]{2})$";

   // compile the option pattern  
   assert(!re_compile_pattern(pattern,strlen(pattern),&regex)); 

   // log the attempt to initialize the DGH D/A convertor
   msg("PSensorEmulator::DghSetup()","Enabling write-mode on DGH device.\n");

   // put the DGH device in write-enable mode
   write("#1WEF0");

   // read the response from the device
   while (read(buf,&len,MAXSTRLEN,250))
   {
      if (!strcmp("*1WEF7",buf)) {status=true; break;}
      else msg("PSensorEmulator::DghSetup()","Nonmatching response string: \"%s\".",buf);
   }

   // check for failure of write-enable and make a log entry
   if (!status) {msg("PSensorEmulator::DghSetup()","Write-enable failed."); goto Err;}
   else {FlushIO();}

   // log the attempt to initialize the DGH D/A convertor
   msg("PSensorEmulator::DghSetup()","Configuring DGH device: %s.\n",setup);

   // write the setup string and the checksum to the serial port
   sprintf(buf,"#1SU%s",setup); sprintf(buf+strlen(buf),"%02X",checksum(buf)); write(buf);
   
   while (read(buf,&len,MAXSTRLEN,250))
   {
      // check if the regex matches the buffer
      if ((n=re_match(&regex,buf,len,0,&regs))>0)
      {
         // extract the checksum from the response string
         unsigned char chksum1 = strtoul(extract(buf,regs.start[3]+1,regs.end[3]-regs.start[3]),NULL,16);

         // compute the checksum of the response string
         unsigned char chksum2 = checksum(extract(buf,regs.start[1]+1,regs.end[1]-regs.start[1]));

         // check for matching checksum
         if (chksum1==chksum2) {status=true; break;}
         else {msg("PSensorEmulator::DghSetup()","Response checksum failed.");}
      }

      else if (n==-1)
      {
         msg("PSensorEmulator::DghSetup()","Response string \"%s\" "
             "doesn't match regex.",buf);
      }
       
      // check for an internal error 
      else if (n==-2)
      {
         msg("PSensorEmulator::DghSetup()","Internal error in re_match().");
         break;
      }
   }

   // collection point
   Err: FlushIO();

   // make a log entry that the setup attempt failed
   if (!status) {msg("PSensorEmulator::DghSetup()","DGH configuration failed.");}

   // make a log entry that the setup attempt worked
   else {msg("PSensorEmulator::DghSetup()","DGH configuration successful.");} 
      
   // clean up the regex pattern buffer & registers
   regfree(&regex); if (regs.start) free(regs.start); if(regs.end) free(regs.end);

   return status;
}

/*------------------------------------------------------------------------*/
/* function to flush the input \& output buffers                          */
/*------------------------------------------------------------------------*/
/**
   This function flushes both the input and output queues of the serial port.
*/
bool PSensorEmulator::FlushIO(void) const
{
   // send command to flush the receive \& transmit buffers
   if (tcflush(fd,TCIOFLUSH)<0)
   {
      msg("PSensorEmulator::FlushIO()",strerror(errno));
      return false;
   }
   else msg("PSensorEmulator::FlushIO()","IO buffers flushed.\n");

   return true;
}

/*------------------------------------------------------------------------*/
/* function to flush the input buffer                                     */
/*------------------------------------------------------------------------*/
/**
   This function flushes the input queue of the serial port.
*/
bool PSensorEmulator::FlushRXBuffer(void) const
{
   // send command to flush the receive buffer
   if (tcflush(fd,TCIFLUSH)<0)
   {
      msg("PSensorEmulator::FlushRXBuffer()",strerror(errno));
      return false;
   }
   else msg("PSensorEmulator::FlushRXBuffer()","Receive buffer flushed.\n");
      
   return true;
}

/*------------------------------------------------------------------------*/
/* function to flush the output buffer                                    */
/*------------------------------------------------------------------------*/
/**
   This function flushes the output queue of the serial port.
*/
bool PSensorEmulator::FlushTXBuffer(void) const
{
   // send command to flush the transmit buffer
   if (tcflush(fd,TCOFLUSH)<0)
   {
      msg("PSensorEmulator::FlushTXBuffer()",strerror(errno));
      return false;
   }
   else msg("PSensorEmulator::FlushTXBuffer()","Transmit buffer flushed.\n");

   return true;
}

/*------------------------------------------------------------------------*/
/* function to write the output to the D/A convertor                      */
/*------------------------------------------------------------------------*/
bool PSensorEmulator::milliamps(float mA) const
{
   bool status=false;
   char buf[MAXSTRLEN];
   
   // flush the IO buffers
   FlushIO();

   snprintf(buf,sizeof(buf)-1,"$1AO+%08.2f\n",mA);

   write(buf);
   
   return status;
}

/*------------------------------------------------------------------------*/
/* function to connect to a serial port                                   */
/*------------------------------------------------------------------------*/
/**
   This function opens the serial port for communications.  For information
   on the control flags see the man pages on tcgetattr() and tcsetattr().
   The libc info documents fully describe the general configuration of
   serial ports.
*/
bool PSensorEmulator::open(Port com)
{
   bool status=true;
   const char *port;
      
   // close the port if it's already open
   if (open()) close();

   // select the serial port
   switch (com)
   {
     case  1: {port = "/dev/com1"; break;}
     case  2: {port = "/dev/com2"; break;}        
     case  3: {port = "/dev/com3"; break;}        
     case  4: {port = "/dev/com4"; break;}        
     case  5: {port = "/dev/com5"; break;}        
     case  6: {port = "/dev/com6"; break;}        
     default:
     {
        msg("PSensorEmulator::open()","Unknown port(%d).\n",com);
        status = false;
     }
   }

   // open a connection to the serial port
   if (status && (fd=::open(port,O_RDWR|O_NONBLOCK))<0)
   {
      // print error message
      msg("PSensorEmulator::open()","Attempt to open connection failed.  %s\n",
          strerror(errno));
      status = false;
   }

   // set exclusive-use mode for the serial port
   else if (ioctl(fd,TIOCEXCL))
   {
      msg("PSensorEmulator::open()","Unable to open in exclusive-use mode.\n");
      status = false;
   }

   // set asychronous communications mode for the serial port
   else if (fcntl(fd,F_SETFL,FASYNC)<0)
   {
      msg("PSensorEmulator::open()","Unable to open serial port in asynchronous mode.\n");
      status = false;
   }
   else
   {
      signal(SIGPOLL,SIG_IGN);
      
      // get termio parms
      tcgetattr(fd,&ioport);

      // set the flags that control the serial port behavior
      ioport.c_oflag &= ~( OPOST );
      ioport.c_cflag &= ~( HUPCL | CSTOPB | PARENB | CSIZE | CRTSCTS );
      ioport.c_cflag |=  ( CLOCAL | CREAD | CS8 );
      ioport.c_lflag &= ~( ICANON | ECHO | ECHONL | ISIG | IEXTEN | FLUSHO );
      ioport.c_lflag |=  ( NOFLSH );
      ioport.c_iflag &= ~( INPCK   | IGNPAR | PARMRK | ISTRIP | IGNBRK | BRKINT |
                           IGNCR   | ICRNL  | INLCR  | IXOFF  | IXON   | IXANY  |
                           IMAXBEL );

      // initialize input mode read() transfer parameters
      ioport.c_cc[VMIN]=0; ioport.c_cc[VTIME]=0;

      // set the speed to 9600 baud
      cfsetspeed(&ioport,B9600);
      
      // flush the IO buffers
      if (!FlushIO())
      {
         msg("PSensorEmulator::open()","Unable to flush IO buffer: %s\n",strerror(errno));
         status = false;
      }

      // reprogram the serial port
      else if (tcsetattr(fd,TCSANOW,&ioport)<0)
      {
         msg("PSensorEmulator::open()","tcsetattr() failed: %s\n",strerror(errno));
         status = false;
      }

      // initialize the streambuffer pointer
      stream=NULL;

      // associate a streambuffer with the serial port's file descriptor
      if (!(stream=fdopen(fd,"w+")))
      {
         msg("PSensorEmulator::open()","Unable to create the serial port's stream buffer.\n");
         status=false;
      }

      // initialize the DGH D/A convertor
      else {status=DghSetup();}
   }
   
   return status; 
}

/*------------------------------------------------------------------------*/
/* function to read bytes from the serial port                            */
/*------------------------------------------------------------------------*/
/**
   This function reads bytes from the serial port until an end-of-line
   character is received or else a timeout period has expired.
*/
bool PSensorEmulator::read(char *buf,int *len,int size,long msec) const
{
   // initialize the return value
   bool status=false;
   
   // define a buffer to hold one byte of data
   unsigned char byte;
      
   // initialize the current time in seconds and microseconds
   timeval t0; struct timezone tz={0,0}; gettimeofday(&t0,&tz);

   // validate pointer to buffer
   if (!buf) {msg("PSensorEmulator::read()","buf=NULL."); goto Err;}

   // validate pointer to len
   if (!len) {msg("PSensorEmulator::read()","len=NULL."); goto Err;}

   // make sure the buffer can hold at least one byte plus the NULL terminator
   if (size<2) {msg("PSensorEmulator::read()","buffer is too small."); goto Err;}

   // initialize the buffer
   (*len)=0; buf[0]=0;
      
   for (int n=0;;)
   {
      if ((n=::read(fd,&byte,1))>0)
      {
         // ignore line-feed characters
         if (byte=='\n') continue;

         // ignore NULL characters
         if (byte==0) continue;
            
         // a carriage return completes the read attempt
         if (byte=='\r') break;

         // add the current byte to the buffer
         buf[*len]=byte; (*len)++; buf[*len]=0; status=true;

         // check to see if the buffer has been filled already
         if ((*len)>=size-1) {msg("PSensorEmulator::read()","buffer full before "
                                  "termination character (\\r) received.");}

         // reset the timeout clock
         gettimeofday(&t0,&tz);
      }
      else if (n<0)
      {
         switch (errno)
         {
            // check for interrupted operation during the read attempt
            case EINTR: {break;}

            // check of no data were available
            case EAGAIN: {break;}

            // check for I/O error
            case EIO:
            {
               msg("PSensorEmulator::read()","I/O error encountered, ignored."); break;
            }

            // check for bad file descriptor
            case EBADF: 
            {
               msg("PSensorEmulator::read()","Bad file descriptor.\n");

               status=false; goto Err;
            }
               
            case EISDIR: // fd refers to a directory
            case EINVAL: // fd is attached to an object which is unsuitable for reading.
            case EFAULT: // buf is outside your accessible address space
            {
               msg("PSensorEmulator::read()","Check logic, assertable error: %s",
                   strerror(errno));
               goto Err;
            }

            // anything else is undefined
            default: msg("PSensorEmulator::read()","Undefined error.");
         }
      }
       
      // get the current time in seconds and microseconds
      timeval t; gettimeofday(&t,&tz);

      // compute the number of milliseconds spent so far during the reading attempt
      long int dt= (t.tv_sec-t0.tv_sec)*1000 + (t.tv_usec-t0.tv_usec)/1000;

      // check to see if timeout period has been exceeded
      if (dt>msec) {msg("PSensorEmulator::read()","Time-out period exceeded."); break;}
   }

   // return from nonexceptional condition
   return status;
   
   // make a log entry and return from exceptional condition
   Err: msg("PSensorEmulator::read()","Bailing out due to exceptional condition.");
   return status;
}

/*------------------------------------------------------------------------*/
/* function to check if input is waiting to be read                       */
/*------------------------------------------------------------------------*/
int PSensorEmulator::RXSpaceUsed(void) const
{
   long i=0;

   // use ioctl() to determine the number of bytes waiting in the input queue
   ioctl(fd,FIONREAD, &i); 
   
   return (int)i;
}

/*------------------------------------------------------------------------*/
/* function to write bytes to the serial port                             */
/*------------------------------------------------------------------------*/
bool PSensorEmulator::write(const char *buf) const
{
   int len;
   
   // initialize the return value
   bool status=true;
   
   // validate pointer to buffer
   if (!buf) {msg("PSensorEmulator::write()","buf=NULL."); status=false; goto Err;}

   // compute the length of the buffer
   len=strlen(buf);

   // check for zero length buffer
   if (!len) {msg("PSensorEmulator::write()","buffer has zero length.");}

   // write the buffer to the serial port
   if (::write(fd,buf,len)<len || ::write(fd,&"\r",1)<1)
   {
      msg("PSensorEmulator::write()","Too few bytes written to serial port.");
   }

   // return from nonexceptional condition
   return status;
   
   // make a log entry and return from exceptional condition
   Err: msg("PSensorEmulator::write()","Bailing out due to exceptional condition.");
   return status;
}

#endif // PSENSOREMULATOR_CPP
#endif // PSENSOREMULATOR_OOP
#undef LEADER
#undef VERSION
