#ifndef MESSAGELOGGER_OOP
#define MESSAGELOGGER_OOP

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * $Id: MessageLogger.cpp,v 1.1.1.1 2010/07/13 17:33:54 swift Exp $
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
 * $Log: MessageLogger.cpp,v $
 * Revision 1.1.1.1  2010/07/13 17:33:54  swift
 * This distribution contains the source code for the Float Mission Simulator
 * used to simulate, debug, and test float firmware.
 *
 * \end{verbatim}
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define MessageLoggerChangeLog "$RCSfile: MessageLogger.cpp,v $  $Revision: 1.1.1.1 $   $Date: 2010/07/13 17:33:54 $"

#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

/*========================================================================*/
/* class to log messages                                                  */
/*========================================================================*/
/**
   This class implements a facility for logging run-time messages.  The only
   public method (aside from initialization constructors) is the overloaded
   function-call operator that is used to enter a run-time message into the
   log file.  This class is intended to facilitate debugging systems that
   are bound for embedded applications --- the class should be neutered to
   be effectively a no-op when software is actually cross-compiled for
   embedded applications.

   written by Dana Swift
*/
class MessageLogger
{
   // data members
   private:

      /// A pointer to the logging message stream.
      FILE *dest;
      
   // function members
   private:
      
      /// Function to open the log file for storing run-time messages.
      void open(const char *fname,const char *mode);
      
   public:

      /// Default initialization constructor
      MessageLogger(void);
      
      /// initialization constructor 
      MessageLogger(const char *basepath);
      
      /// initialization constructor 
      MessageLogger(const char *fname,const char *mode);

      /// This destructor simply closes the log file
      ~MessageLogger(void);
      
      /// This overloaded function-call operator prints a message to the log file.
      void operator()(const char *function_name,const char *format,...) const;

      /// This function prints a properly formed SBE41 response the log file.
      void Sbe41Response(const char *function_name,const char *buf,int len,const char *trm="]\n") const;

      void Entry(const char *function_name,const char *buf,int len) const;

      /// This function prints a message to the log file.
      void Add(const char *format,...) const;
      void Add(const char *buf,int len,const char *trm) const;
};

/// Declare the message logger as a global variable.
extern MessageLogger msg;

#ifdef MESSAGELOGGER_CPP

/*------------------------------------------------------------------------*/
/* initialization constructor to use stdout as log stream                 */
/*------------------------------------------------------------------------*/
MessageLogger::MessageLogger(void)
{
   dest=stdout;
   
   // make a log entry
   (*this)("MessageLogger::MessageLogger()",
           "Enabling logging functions.\n");
}

/*------------------------------------------------------------------------*/
/* initialization constructor to automatically select log file name.      */
/*------------------------------------------------------------------------*/
MessageLogger::MessageLogger(const char *fname,const char *mode)
{
   // open the log file with the specified mode
   open(fname,mode);
   
   // make a log entry
   (*this)("MessageLogger::MessageLogger()",
           "Enabling logging functions.\n");
}

/*------------------------------------------------------------------------*/
/* initialization constructor to automatically select log file name.      */
/*------------------------------------------------------------------------*/
MessageLogger::MessageLogger(const char *basepath)
{
   // set the maximum length for the logfile name
   const size_t MAXLEN = 1023;

   // make room for the logfile name
   char fname[MAXLEN+1];
         
   // validate the directory
   if (!basepath || strlen(basepath)>(MAXLEN-20)) basepath="./msglog";

   // create the base-path
   sprintf(fname,"%s.",basepath);

   // compute the length of the logfile directory string
   unsigned int len = strlen(fname);

   // get the current local time
   time_t t=time(NULL); 
         
   // create the logfile name
   strftime(fname+len,MAXLEN-len,"%b%d-%H:%M",gmtime(&t));

   // open the logfile
   open(fname,"w");

   // make a log entry
   (*this)("MessageLogger::MessageLogger()",
           "Enabling logging functions.\n");
}

/*------------------------------------------------------------------------*/
/* This destructor simply closes the log file                             */
/*------------------------------------------------------------------------*/
MessageLogger::~MessageLogger(void)
{
   // check if the log stream is stderr
   if (dest!=stderr)
   {
      // write the closing message to the log file
      (*this)("MessageLogger::~MessageLogger()",
              "Disabling logging functions.\n");

      // close the logfile
      fclose(dest);
   }
}
      
/*------------------------------------------------------------------------*/
/* Overloaded function-call operator to print a message to the log file.  */
/*------------------------------------------------------------------------*/
void MessageLogger::operator()(const char *function_name,const char *format,...) const
{
   va_list arg_pointer;
   char buf[1024];
   timeval t; gettimeofday(&t,NULL);
         
   // get the date & time
   strftime(buf,1023,"%b %d %H:%M:%S",gmtime(&t.tv_sec));

   // print the date and time
   fprintf(dest,"(%s.%03ld) ",buf,t.tv_usec/1000);
         
   // print the function identifier
   if (function_name) fprintf(dest,"%s ... ",function_name);
         
   /* get the format argument from the argument list */
   va_start(arg_pointer,format);
         
   /* print the message */
   if (format) vfprintf(dest,format,arg_pointer);

   // add a carriage return if needed
   if (format && format[strlen(format)-1]!='\n') fprintf(dest,"\n");
         
   /* clean up call */
   va_end(arg_pointer);
         
   /* flush the output */
   fflush(dest);
}
      
/*------------------------------------------------------------------------*/
/* Function to print an Sbe41 response string to the log file.            */
/*------------------------------------------------------------------------*/
void MessageLogger::Sbe41Response(const char *function_name,const char *buf,int len,const char *trm) const
{
   char date[1024];
   timeval t; gettimeofday(&t,NULL);

   // validate pointer
   if (!buf) {buf="error in MessageLogger::operator() ... NULL pointer"; len=strlen(buf);}
   
   // validate pointer to the function name
   if (!function_name) function_name="";
            
   // get the date & time
   strftime(date,1023,"%b %d %H:%M:%S",gmtime(&t.tv_sec));
   
   // write the time stamp
   fprintf(dest,"(%s.%03ld) %s [",date,t.tv_usec/1000,function_name);

   // write each byte to the log file
   for (int i=0; i<len; i++)
   {
      if (buf[i]=='\r') fprintf(dest,"\\r");
      else if (buf[i]=='\n') fprintf(dest,"\\n");
      else if (buf[i]<32 || buf[i]&0x80) fprintf(dest,"[0x%02x]",(unsigned char)buf[i]);
      else fprintf(dest,"%c",buf[i]);
   } 
   if (trm && *trm) fprintf(dest,trm);

   /* flush the output */
   fflush(dest);
}
      
/*------------------------------------------------------------------------*/
/* Function to print an Sbe41 response string to the log file.            */
/*------------------------------------------------------------------------*/
void MessageLogger::Add(const char *buf,int len,const char *trm) const
{
   // validate pointer
   if (!buf) {buf="error in MessageLogger::Add() ... NULL pointer"; len=strlen(buf);}

   // write each byte to the log file
   for (int i=0; i<len; i++)
   {
      if (buf[i]=='\r') fprintf(dest,"\\r");
      else if (buf[i]=='\n') fprintf(dest,"\\n\n");
      else if (buf[i]<32 || buf[i]&0x80) fprintf(dest,"[0x%02x]",(unsigned char)buf[i]);
      else fprintf(dest,"%c",buf[i]);
   } 
   if (trm && *trm) fprintf(dest,trm);
   
   /* flush the output */
   fflush(dest);
}
      
/*------------------------------------------------------------------------*/
/* Function to print an Sbe41 response string to the log file.            */
/*------------------------------------------------------------------------*/
void MessageLogger::Entry(const char *function_name,const char *buf,int len) const
{
   char date[1024];
   timeval t; gettimeofday(&t,NULL);

   // validate pointer
   if (!buf) {buf="error in MessageLogger::Entry() ... NULL pointer"; len=strlen(buf);}
   
   // validate pointer to the function name
   if (!function_name) function_name="";
            
   // get the date & time
   strftime(date,1023,"%b %d %H:%M:%S",gmtime(&t.tv_sec));
   
   // write the time stamp
   fprintf(dest,"(%s.%03ld) %s ",date,t.tv_usec/1000,function_name);

   // write each byte to the log file
   for (int i=0; i<len; i++)
   {
      if (buf[i]=='\r') fprintf(dest,"\\r");
      else if (buf[i]=='\n') fprintf(dest,"\\n\n");
      else if (buf[i]<32 || buf[i]&0x80) fprintf(dest,"[0x%02x]",(unsigned char)buf[i]);
      else fprintf(dest,"%c",buf[i]);
   }
   
   /* flush the output */
   fflush(dest);
}

/*------------------------------------------------------------------------*/
/* Function to print a message to the log file.                           */
/*------------------------------------------------------------------------*/
void MessageLogger::Add(const char *format,...) const
{
   va_list arg_pointer;
   
   /* get the format argument from the argument list */
   va_start(arg_pointer,format);
         
   /* print the message */
   if (format) vfprintf(dest,format,arg_pointer);
         
   /* clean up call */
   va_end(arg_pointer);
   
   /* flush the output */
   fflush(dest);
}
      
/*------------------------------------------------------------------------*/
/* Function to open the log file for storing run-time messages.           */
/*------------------------------------------------------------------------*/
void MessageLogger::open(const char *fname,const char *mode)
{
   // default attachment stream is stderr
   dest=stderr;

   // open the log file
   if (mode && fname && !(dest=fopen(fname,mode)))
   {
      // open failed - reattach the stderr stream
      dest=stderr;
      
      // make a log entry about the failed attempt to open the log file
      (*this)("MessageLogger::open()",
              "Unable to open \"%s\" using mode \"%s\".",fname,mode);
   }
}

#endif // MESSAGELOGGER_CPP
#endif // MESSAGELOGGER_OOP

