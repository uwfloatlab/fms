#ifndef SPYSTREAM_OOP
#define SPYSTREAM_OOP

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * $Id: SpyStream.cpp,v 1.1.1.1 2010/07/13 17:33:54 swift Exp $
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
 * $Log: SpyStream.cpp,v $
 * Revision 1.1.1.1  2010/07/13 17:33:54  swift
 * This distribution contains the source code for the Float Mission Simulator
 * used to simulate, debug, and test float firmware.
 *
 * \end{verbatim}
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define SpyStreamChangeLog "$RCSfile: SpyStream.cpp,v $  $Revision: 1.1.1.1 $  $Date: 2010/07/13 17:33:54 $"

#include <MessageLogger.oop>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>

#define LEADER  "SBE41-APFx Serial Stream Analyzer [SwiftWare]"
#define VERSION "$Revision: 1.1.1.1 $  $Date: 2010/07/13 17:33:54 $"

/// typedefs to improve readibility
typedef int Port;

/*========================================================================*/
/* API for the SpyStream interface                                        */
/*========================================================================*/
class SpyStream
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

   // function members
   private:
 
      // function to close connection to serial port
      void close(void) {if (open()) ::close(fd);}
 
      /// return state of the clear-to-send line
      int CTS(void) const {return pinstate(TIOCM_CTS);}

      /// return state of the datat-set-ready line
      int DSR(void) const {return pinstate(TIOCM_DSR);}

      // function to connect to a serial port
      bool open(Port com);

      /// function to determine if the serial port is open
      bool open(void) {return (fd>=0);}

      // function to read state of modem control lines
      int pinstate(int iopin) const;

   public:

      /// initialization constructor for SpyStream class
      SpyStream(Port com);

      /// destructor for SpyStream class
      ~SpyStream(void) {close();}


      // function to flush the input and output buffers
      bool FlushIO(void) const;
      
      // function to flush the input buffer
      bool FlushRXBuffer(void) const;

      // function to flush the output buffer
      bool FlushTXBuffer(void) const;

      // function to determine if P-only mode is selected
      bool PMode(void) const;

      // function to determine if PTS mode is selected
      bool PtsMode(void) const;
         
      // function to read the next buffer from the serial port
      bool Read(const char *&buf,int *len) const;

      void Restart(void);
      
      // function to determine if anything is waiting in the input buffer
      size_t RXSpaceUsed(void) const;

      // function to write a buffer to the serial port
      ssize_t Write(const char *buf,int len) const;
};

#ifdef SPYSTREAM_CPP
#include <MessageLogger.oop>
#include <fcntl.h>
#include <errno.h>
#include <glob.h>
#include <regex.h>
#include <assert.h>
#include <signal.h>

// function prototypes
void yyrestart(FILE *input_file);

/*------------------------------------------------------------------------*/
/* initialization constructor for SpyStream class                         */
/*------------------------------------------------------------------------*/
SpyStream::SpyStream(Port com): fd(-1), stream(0)
{
   // log the software LEADER
   msg("SpyStream::SpyStream()",LEADER);

   // log the software revision
   msg("SpyStream::SpyStream()",VERSION);

   // open a connection to the serial port attached to the SpyStream interface
   if (!open(com)) exit(1);
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
void SpyStream::Restart(void) {yyrestart(stream);}

/*------------------------------------------------------------------------*/
/* function to flush the input \& output buffers                          */
/*------------------------------------------------------------------------*/
/**
   This function flushes both the input and output queues of the serial port.
*/
bool SpyStream::FlushIO(void) const
{
   // send command to flush the receive \& transmit buffers
   if (tcflush(fd,TCIOFLUSH)<0)
   {
      msg("SpyStream::FlushIO()",strerror(errno));
      return false;
   }
   else msg("SpyStream::FlushIO()","IO buffers flushed.\n");

   return true;
}

/*------------------------------------------------------------------------*/
/* function to flush the input buffer                                     */
/*------------------------------------------------------------------------*/
/**
   This function flushes the input queue of the serial port.
*/
bool SpyStream::FlushRXBuffer(void) const
{
   // send command to flush the receive buffer
   if (tcflush(fd,TCIFLUSH)<0)
   {
      msg("SpyStream::FlushRXBuffer()",strerror(errno));
      return false;
   }
   else msg("SpyStream::FlushRXBuffer()","Receive buffer flushed.\n");
      
   return true;
}

/*------------------------------------------------------------------------*/
/* function to flush the output buffer                                    */
/*------------------------------------------------------------------------*/
/**
   This function flushes the output queue of the serial port.
*/
bool SpyStream::FlushTXBuffer(void) const
{
   // send command to flush the transmit buffer
   if (tcflush(fd,TCOFLUSH)<0)
   {
      msg("SpyStream::FlushTXBuffer()",strerror(errno));
      return false;
   }
   else msg("SpyStream::FlushTXBuffer()","Transmit buffer flushed.\n");

   return true;
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
bool SpyStream::open(Port com)
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
     default:
     {
        msg("SpyStream::open()","Unknown port(%d).\n",com);
        status = false;
     }
   }

   // open a connection to the serial port
   if (status && (fd=::open(port,O_RDWR|O_NONBLOCK))<0)
   {
      // print error message
      msg("SpyStream::open()","Attempt to open connection failed.  %s\n",
          strerror(errno));
      status = false;
   }

   // set exclusive-use mode for the serial port
   else if (ioctl(fd,TIOCEXCL))
   {
      msg("SpyStream::open()","Unable to open in exclusive-use mode.\n");
      status = false;
   }

   // set asychronous communications mode for the serial port
   else if (fcntl(fd,F_SETFL,FASYNC)<0)
   {
      msg("SpyStream::open()","Unable to open serial port in asynchronous mode.\n");
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
      ioport.c_cc[VMIN]=1; ioport.c_cc[VTIME]=0;

      // set the speed to 9600 baud
      cfsetspeed(&ioport,B9600);
      
      // flush the IO buffers
      if (!FlushIO())
      {
         msg("SpyStream::open()","Unable to flush IO buffer: %s\n",strerror(errno));
         status = false;
      }

      // reprogram the serial port
      else if (tcsetattr(fd,TCSANOW,&ioport)<0)
      {
         msg("SpyStream::open()","tcsetattr() failed: %s\n",strerror(errno));
         status = false;
      }

      // initialize the streambuffer pointer
      stream=NULL;

      // associate a streambuffer with the serial port's file descriptor
      if (!(stream=fdopen(fd,"w+")))
      {
         msg("SpyStream::open()","Unable to create the serial port's stream buffer.\n");
         status=false;
      }

      // initialize the lexer to use the serial port as the input stream
      else yyrestart(stream);
   }
   
   return status; 
}

/*------------------------------------------------------------------------*/
/* function to return the state of a single modem control line            */
/*------------------------------------------------------------------------*/
/**
   This function determines the state of any of the modem control lines.  On
   failure the function returns -1 and errno is set appropriately.  On
   success, the function returns 1 if the line is asserted and 0 if it is
   not.              
*/
int SpyStream::pinstate(int iopin) const
{
   int status;

   switch (iopin)
   {
      case TIOCM_DTR: // Data terminal ready
      case TIOCM_RTS: // request to send
      case TIOCM_CTS: // clear to send
      case TIOCM_CAR: // carrier detect
      case TIOCM_RNG: // ring
      case TIOCM_DSR: // data set ready
      {
         if (ioctl(fd,TIOCMGET,&status)<0)
         {
            msg("SpyStream::pinstate()","%s.\n",strerror(errno));
            return -1;
         }
         break;
      }
     default:
     {
        msg("SpyStream::pinstate()","Undefined IO pin(0x%03X).\n",iopin);
        return -1;
     }
   }
   
   return ((status&iopin) ? 1 : 0);
}

/*------------------------------------------------------------------------*/
/* function to determine if PTS mode is selected                          */
/*------------------------------------------------------------------------*/
bool SpyStream::PMode(void) const
{
   bool PMode = (CTS()) ? true : false;

   return PMode;
}
 
/*------------------------------------------------------------------------*/
/* function to determine if PTS mode is selected                          */
/*------------------------------------------------------------------------*/
bool SpyStream::PtsMode(void) const
{
   bool PtsMode = (CTS()) ? false : true;

   return PtsMode;
}
 
/*------------------------------------------------------------------------*/
/* function to determine if anything is waiting in the input buffer       */
/*------------------------------------------------------------------------*/
size_t SpyStream::RXSpaceUsed(void) const
{
   int i=0;

   // use ioctl() to determine the number of bytes waiting in the input queue
   if (ioctl(fd,FIONREAD, &i)<0)
   {
      // log the failure
      i=-1; msg("SpyStream::RXSpaceUsed()",strerror(errno));
   }
   
   return i;
}

/*------------------------------------------------------------------------*/
/* function to write a buffer to the serial port                          */
/*------------------------------------------------------------------------*/
ssize_t SpyStream::Write(const char *buf,int len) const
{
   // make a log entry of what's being written
   msg.Sbe41Response("SpyStream::Write()  ",buf,len);

   // write the buffer to the serial port
   return write(fd,buf,len);
}
 
#endif // SPYSTREAM_CPP
#endif // SPYSTREAM_OOP
#undef LEADER
#undef VERSION

#ifdef SPYSTREAMLEXER_L
$ arc_header: SpyStreamLexer.l
%option caseless pointer perf-report 

%{
#include <SpyStream.oop>
#include <MessageLogger.oop>
   
/*========================================================================*/
/* Flex specification section                                             */
/*========================================================================*/
/*
   WARNING: The file SpyStreamLexer.l is automatically generated.
   Modifications made to SpyStreamLexer.l will be lost so permanent changes
   made to this lexer specification should be made at the bottom of the file
   Sbe41.cpp.
*/
   
/* change the lexer declarator */
#define YY_DECL bool SpyStream::Read(const char *&buf,int *len) const

/* inhibit unused extraneous functions that cause compiler warnings */ 
#define YY_NO_UNPUT

/* macro to get lexer input one character at a time */
#define YY_INPUT(buf,result,max_size) \
{\
   int c; c=getc(yyin); \
   result = (c==EOF) ? YY_NULL : ((*buf)=c,1); \
}
%}

w   [ ]
d   [0-9]
h   [0-9A-F]
s   -

P   [ ]{0,5}-?[0-9]{1,4}\.[0-9]{1,2}
T   [ ]{0,5}-?[0-9]{1,2}\.[0-9]{3,4}
S   [ ]{0,5}-?[0-9]{1,2}\.[0-9]{3,4}
F   [ .+-0123456789]+

%%

<INITIAL>
{
   /* define all possible well-formed P responses by the SBE41 */
   ^{w}{w}{w}{s}{d}\.{d}{d}(\r\n|,.*\r\n) |
   ^{w}{w}{w}{w}{d}\.{d}{d}(\r\n|,.*\r\n) |
   ^{w}{w}{w}{d}{d}\.{d}{d}(\r\n|,.*\r\n) |
   ^{w}{w}{d}{d}{d}\.{d}{d}(\r\n|,.*\r\n) |
   ^{w}{d}{d}{d}{d}\.{d}{d}(\r\n|,.*\r\n) {
      buf=yytext; *len=yyleng;
      const char *title = (PtsMode())?"SpyStream::Read(PTS)":"SpyStream::Read(P)  ";
      msg.Sbe41Response(title,buf,*len);
      return true;
   }

   /* define a navis Pts/sbe{63,83} response string */
   ^{P},{T},{S},{F},{F},{F},{F}\r\n {
      buf=yytext; *len=yyleng;
      const char *title = "SpyStream::Read(PtsFull)";
      msg.Sbe41Response(title,buf,*len);
      return true;
   }
   
   /* define elements of an STS profile */
   ^{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}\r\n |
   ^{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}\r\n {
      buf=yytext; *len=yyleng;
      const char *title = "SpyStream::Read()   ";
      msg.Sbe41Response(title,buf,*len);
      return false;
   }

   /* define elements of the continuous profile */
   ^{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}\r\n |
   ^{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}\r\n {
      buf=yytext; *len=yyleng;
      const char *title = "SpyStream::Read()   ";
      msg.Sbe41Response(title,buf,*len);
      return false;
   }

   /* define elements of the continuous profile */
   ^{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}\r\n |
   ^{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}{h}\r\n {
      buf=yytext; *len=yyleng;
      const char *title = "SpyStream::Read()   ";
      msg.Sbe41Response(title,buf,*len);
      return false;
   }
   
   "qsr\r\n" |
   "dah\r\n" |
   "ds\r\n" |   
   "dc\r\n" |   
   "real-time output is PTS\r\n" |
   "powering down\r\n" |
   "profile stopped\r\n" |
   "binaverage\r\n" |
   "startprofile".*"\r\n" |
   "SBE 41".*"\r\n" |
   "profile started, pump delay".*"\r\n" |
   "samples ="[ 0-9]+", " |
   "maxPress =".*", " |
   "nbins ="[ 0-9]+.*"\r\n" |
   "bad:".*"\r\n" |
   "avg:"[ 0-9]+.*"\r\n" |
   "int:"[ 0-9]+.*"\r\n" |
   "done\r\n" |
   "upload complete\r\n" |
   "rd:"[ 0-9]+"\r\n" {
      buf=yytext; *len=yyleng;
      const char *title = "SpyStream::Read()   ";
      msg.Sbe41Response(title,buf,*len);
      return false;
   }
 
   "stop profile when pressure is less than".*"\r\n" |
   "automatic bin averaging when p <".*"\r\n" |
   "number of samples =".*"\r\n" |
   "number of bins =".*"\r\n" |
   "top bin interval =".*"\r\n" |
   "top bin size =".*"\r\n" |
   "top bin max =".*"\r\n" |
   "middle bin interval =".*"\r\n" |
   "middle bin size =".*"\r\n" |
   "middle bin max =".*"\r\n" |
   "bottom bin interval =".*"\r\n" |
   "bottom bin size =".*"\r\n" |
   "bottom bin max =".*"\r\n" |
   "do not include two transition bins\r\n" |
   "include samples per bin\r\n" |
   "oxygen frequency multiplier =".*"\r\n" |
   "take sample wait time =".*"\r\n" {
      buf=yytext; *len=yyleng;
      const char *title = "SpyStream::Read()   ";
      msg.Sbe41Response(title,buf,*len);
      return false;
   }

   /* trap prompts */
   "S>" {
      buf="S>"; *len=strlen(buf);
      const char *title = "SpyStream::Read()   ";
      msg.Sbe41Response(title,buf,*len);
      yyrestart(stream);
      return false;
   }

   /* ignore NULL bytes */
   \000 {}
 
   /* default rule for ill-formed responses by the SBE41 */
   .|\n|"\r\n" {
      buf=yytext; *len=yyleng;
      const char *title = (PtsMode())?"SpyStream::Read(PTS) ":"SpyStream::Read(P)  ";
      msg.Sbe41Response(title,buf,*len);
      return false;
   }
}

%%

$ arc_EOF: SpyStreamLexer.l
#endif // SPYSTREAMLEXER_L
