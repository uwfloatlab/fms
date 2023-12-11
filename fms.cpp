#include <ApexSbe.oop>
#include <HydroObs.oop>
#include <regex.h>
#include <assert.h>
#include <PSensorEmulator.oop>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * $Id: fms.cpp,v 1.1.1.1 2010/07/13 17:33:54 swift Exp $
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Copyright (C) 2001 Dana Swift.   Written by Dana Swift.
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
* $Log: fms.cpp,v $
 * Revision 1.1.1.1  2010/07/13 17:33:54  swift
 * This distribution contains the source code for the Float Mission Simulator
 * used to simulate, debug, and test float firmware.
 * \end{verbatim}
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define FmsChangeLog "$RCSfile: fms.cpp,v $  $Revision: 1.1.1.1 $  $Date: 2010/07/13 17:33:54 $"

#define LEADER  "Float Mission Simulator [SwiftWare]"
#define VERSION "$Revision: 1.1.1.1 $  $Date: 2010/07/13 17:33:54 $"

// create the log file
MessageLogger msg("fms.out","a");

// function prototypes
bool Email(const char *addr,const char *subject,const char *body);
bool AnalyzeSbeResponse(const char *&buf, int &len, ApexSbe &apexsbe,
                        Hydrography &sea, const char *email, const char *id,
                        PSensorEmulator *druck);

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
int main(int argc,char *argv[])
{
   enum {id_,email_,M_,Pbot_,P_,Po_,Co_,dLnVdp_,dVdC_,C0_,mV0_,C1_,mV1_,port_,NCMD};
   MetaCmd cmd[NCMD]=
   {
      {"id=","     Float identifier."},
      {"email=","  Email address of float watcher. [aadu@uw.edu]"},
      {"M=","      Float mass (g). [25700g]"},
      {"Pbot=","   Set the pressure at the bottom of the ocean (dbar). [NaN]"},
      {"P=","      Set the initial float pressure (dbar). [neutal-buoyancy]"},
      {"Po=","     Profile pressure (dbar). [2000dbar]"}, 
      {"Co=","     Piston position at profile pressure (counts). [16 counts]"},
      {"dLnVdp="," Compressibility of the float (per dbar). [-2.50e-6 per dbar]"},
      {"dVdC=","   Buoyancy generation per A/D count (ml/count). [1.157 ml/count]"},
      {"C0=","     Ballast Piston Position. [16 counts]"},
      {"mV0=","    DGH voltage associated with ballast piston position. [151mV]"},
      {"C1=","     Full Piston Extension. [235 counts]"},
      {"mV1=","    DGH voltage associated with full piston extension. [1479mV]"},
      {"port=","   Serial port to use for pressure sensor emulation (eg., 1-6)."},
   };
   
   const char *buf;
   int len;
   bool status;

   // check for usage query
   check_cmd_line(1,make_usage(cmd,NCMD));

   // link command line arguments with metacommands
   link_meta_cmds(cmd,NCMD,argc,argv);

   // initialize the float id
   const char *id = (cmd[id_].arg) ? cmd[id_].arg : "(undefined)";

   // initialize the email respondent
   const char *email = (cmd[email_].arg) ? cmd[email_].arg : "aadu@uw.edu";

   // initialize the mass of the float
   const float M = (cmd[M_].arg) ? atof(cmd[M_].arg) : 25700;

   // initialize the bottom pressure of the ocean
   const float Pbot = (cmd[Pbot_].arg) ? atof(cmd[Pbot_].arg) : NaN();

   // initialize the profile pressure of the float
   const float Po = (cmd[Po_].arg) ? atof(cmd[Po_].arg) : 2000;

   // initialize the piston position at the profile pressure of the float
   const int Co = (cmd[Co_].arg) ? atoi(cmd[Co_].arg) : 16;
   
   // initialize the compressibility of the float
   const float dLnVdp = (cmd[dLnVdp_].arg) ? atof(cmd[dLnVdp_].arg) : -2.50e-6; 
   
   // initialize the buoyancy generation per unit A/D count
   const float dVdC = (cmd[dVdC_].arg) ? atof(cmd[dVdC_].arg) : 1.157;
   
   // initialize the ballast piston position
   const int C0 = (cmd[C0_].arg) ? atoi(cmd[C0_].arg) : 16;
   
   // initialize the DGH voltage associated with ballast piston position
   const float mV0 = (cmd[mV0_].arg) ? atof(cmd[mV0_].arg) : 151;
   
   // initialize the full piston extension
   const int C1 = (cmd[C1_].arg) ? atoi(cmd[C1_].arg) : 235;
    
   // initialize the DGH voltage associated with full piston extension
   const float mV1 = (cmd[mV1_].arg) ? atof(cmd[mV1_].arg) : 1479;

   // define a Druck pressure sensor emulator
   PSensorEmulator *druck=NULL;

   // initialize the (optional) Druck pressure sensor emulator 
   if (cmd[port_].arg) {static PSensorEmulator pse(atoi(cmd[port_].arg)); druck=&pse;}
   
   // log the software LEADER
   msg(argv[0],LEADER);

   // log the software revision
   msg(argv[0],VERSION);

   // reconstruct the command line
   strcpy(scrbuf,"Cmd Line:");
   for (int i=0; i<argc; i++) {strcat(scrbuf," "); strcat(scrbuf,argv[i]);}

   // log the command line
   msg(argv[0],scrbuf);
   
   // define the ocean in which the float is deployed
   SubtropicalNePacificHydrography sea;

   // extract the hydrographic properties at the park pressure
   float To=sea.T(Po), So=sea.S(Po);
   
   // define the drifter properties
   ApexSbe apexsbe(M,Po,To,So,dLnVdp,dVdC,Co,Pbot);

   // initialize the current pressure of the float
   if (cmd[P_].arg) apexsbe.P(atof(cmd[P_].arg));

   // initialize the piston sensor calibration
   apexsbe.Calibrate(C0,mV0,C1,mV1);
   
   // circulate in a loop
   while (1)
   {    
      // wait for the next response string from the SBE41
      if ((status=apexsbe.Read(buf,&len)))
      {
         AnalyzeSbeResponse(buf,len,apexsbe,sea,email,id,druck);
      }
      else
      {
         // create the message body
         sprintf(scrbuf,"Ill-formed response string detected by SpyStream::Read().\n");

         // create the subject line
         char subject[128]; snprintf(subject,128,"Float %s",id);
         
         // notify the float-watcher
         Email(email,subject,scrbuf); 
      }

      // write the modified response string to the APFx controller
      apexsbe.Write(buf,len);
   }
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
bool AnalyzeSbeResponse(const char *&buf, int &len, ApexSbe &apexsbe,
                        Hydrography &sea, const char *email, const char *id,
                        PSensorEmulator *druck)
{
   float S,T,P=0.0,POffset=0.0;
   bool status=true;
   static re_pattern_buffer PtsFull_regex,PTSO_regex,PT_regex,P_regex,
      p_regex,t_regex,s_regex,o_regex,full_regex;
   static re_registers regs;
   static bool regex_compiled=false;
   static char obuf[MAXSTRLEN];
   char p[128],t[128],s[128],o[128],full[128];
   
   if (!regex_compiled)
   {
      regex_compiled=true;
      
      // initialize some regex structure elements
      PtsFull_regex.translate=0; PtsFull_regex.fastmap=0; PtsFull_regex.buffer=0; PtsFull_regex.allocated=0;
      PTSO_regex.translate=0; PTSO_regex.fastmap=0; PTSO_regex.buffer=0; PTSO_regex.allocated=0;
      PT_regex.translate=0;   PT_regex.fastmap=0;   PT_regex.buffer=0;   PT_regex.allocated=0;
      P_regex.translate=0;    P_regex.fastmap=0;    P_regex.buffer=0;    P_regex.allocated=0;
      p_regex.translate=0;    p_regex.fastmap=0;    p_regex.buffer=0;    p_regex.allocated=0;
      t_regex.translate=0;    t_regex.fastmap=0;    t_regex.buffer=0;    t_regex.allocated=0;
      s_regex.translate=0;    s_regex.fastmap=0;    s_regex.buffer=0;    s_regex.allocated=0;
      o_regex.translate=0;    o_regex.fastmap=0;    o_regex.buffer=0;    o_regex.allocated=0;
   
      // set the features of the regex engine
      re_syntax_options = RE_SYNTAX_EMACS | RE_INTERVALS | RE_NO_BK_BRACES |
                          RE_NO_BK_PARENS;

      #define FLOAT "([ ]{0,5}-?[0-9]+\\.[0-9]+)"
      #define P     "([ ]{0,5}-?[0-9]{1,4}\\.[0-9]{1,2})"
      #define T     "([ ]{0,5}-?[0-9]{1,2}\\.[0-9]{1,4})"
      #define S     "([ ]{0,5}-?[0-9]{1,2}\\.[0-9]{1,4})"
      #define O     "([ ]{1,2}[0-9]{1,5})"
      #define Full  "([ +-.0123456789]+,[ +-.0123456789]+,[ +-.0123456789]+,[ +-.0123456789]+)"
      
      // define the PtsFull pattern
      const char *PtsFull_pattern = "^" FLOAT "," FLOAT "," FLOAT "," Full "\r$";
        
      // compile the PtsFull pattern 
      assert(!re_compile_pattern(PtsFull_pattern,strlen(PtsFull_pattern),&PtsFull_regex));

      // define the PTSO pattern
      const char *PTSO_pattern = "^" FLOAT "," FLOAT "," FLOAT "(," O ")?\r$";

      // compile the PTSO pattern 
      assert(!re_compile_pattern(PTSO_pattern,strlen(PTSO_pattern),&PTSO_regex));

      // define the PT pattern
      const char *PT_pattern = "^" FLOAT "," FLOAT "\r$";
      
      // compile the PT pattern 
      assert(!re_compile_pattern(PT_pattern,strlen(PT_pattern),&PT_regex));
 
      // define the P pattern
      const char *P_pattern = "^" FLOAT "\r$";
      
      // compile the p pattern 
      assert(!re_compile_pattern(P_pattern,strlen(P_pattern),&P_regex));

      // define the p pattern
      const char *p_pattern = P;
      
      // compile the s pattern 
      assert(!re_compile_pattern(p_pattern,strlen(p_pattern),&p_regex));

      // define the t pattern
      const char *t_pattern = T;
      
      // compile the t pattern 
      assert(!re_compile_pattern(t_pattern,strlen(t_pattern),&t_regex));

      // define the s pattern
      const char *s_pattern = S;
      
      // compile the s pattern 
      assert(!re_compile_pattern(s_pattern,strlen(s_pattern),&s_regex));

      // define the o pattern
      const char *o_pattern = O;
      
      // compile the O pattern 
      assert(!re_compile_pattern(o_pattern,strlen(o_pattern),&o_regex));

      // define the non-PTS pattern
      const char *full_pattern = Full;
      
      // compile the non-PTS pattern 
      assert(!re_compile_pattern(full_pattern,strlen(full_pattern),&full_regex));

      #undef P
      #undef T
      #undef S
      #undef O
      #undef FULL
   }
  
   // get and validate the model pressure
   if (!finite(P=apexsbe.P(sea)) && inCRange(sea.Pmin(),P,sea.Pmax()))
   {
      msg("AnalyzeSbeResponse()","Invalid model pressure (%g), substituting P=0 dbar.");

      P=0; status=false;
   }

   // check if the buffer satisfies the PTS[O] response
   if (re_match(&PTSO_regex,buf,len,0,&regs)>0)
   {
      // get the salinity and make sure it's finite
      if (!finite(S=sea.S(P)))
      {
         msg("AnalyzeSbeResponse()","Invalid model salinity (%g), substituting S=0 PSU.\n");

         S=0; status=false;
      } 

      // get the temperature and make sure it's finite
      if (!finite(T=sea.T(P)))
      {
         msg("AnalyzeSbeResponse()","Invalid model temperature (%g), substituting T=0 C.\n");

         T=0; status=false;
      }
      
      // extract the pressure from the PTS[O]-response string
      strcpy(p,extract(buf,regs.start[1]+1,regs.end[1]-regs.start[1]));

      // make sure the pressure is well formed
      if (re_match(&p_regex,p,len,0,NULL)<=0)
      {
         // construct the subject line of the email
         char subject[32]; sprintf(subject,"Float %s",id);

         // construct the body of the email
         char body[128]; sprintf(body,"Ill-formed pressure \"%s\" in PTS[O]-response string.\n",t);

         // send the email notification
         Email(email,subject,body);

         // make the log entry
         msg("AnalyzeSbeResponse()",body);
      }
      else {sprintf(p,"%8.2f",P+POffset);}
           
      // extract the temperature from the buffer
      strcpy(t,extract(buf,regs.start[2]+1,regs.end[2]-regs.start[2]));

      // make sure the temperature is well formed
      if (re_match(&t_regex,t,len,0,NULL)<=0)
      {
         // construct the subject line of the email
         char subject[32]; sprintf(subject,"Float %s",id);

         // construct the body of the email
         char body[128]; sprintf(body,"Ill-formed temperature \"%s\" in "
                                 "PTS[O]-response string.\n",t);

         // send the email notification
         Email(email,subject,body);

         // make the log entry
         msg("AnalyzeSbeResponse()",body);
      }
      else {sprintf(t,"%8.4f",T);}
 
      // extract the salinity from the buffer
      strcpy(s,extract(buf,regs.start[3]+1,regs.end[3]-regs.start[3]));

      // make sure the salinity is well formed
      if (re_match(&s_regex,s,len,0,NULL)<=0)
      {
         // construct the subject line of the email
         char subject[32]; sprintf(subject,"Float %s",id);

         // construct the body of the email
         char body[128]; sprintf(body,"Ill-formed salinity \"%s\" in PTS[O]-response string.\n",s);

         // send the email notification
         Email(email,subject,body);

         // make the log entry
         msg("AnalyzeSbeResponse()",body);
      }

      // make sure the salinity is nonzero (zero indicates stopped oscillation)
      else if (!atof(s)) 
      {
         // construct the subject line of the email
         char subject[32]; sprintf(subject,"Float %s",id);

         // construct the body of the email
         char body[128]; sprintf(body,"Salinity (%s) out-of-range in PTS[O]-response string.\n",s);

         // send the email notification
         Email(email,subject,body);

         // make the log entry
         msg("AnalyzeSbeResponse()",body);
      }
      else {sprintf(s,"%8.4f",S);}

      if (regs.start[4]!=-1 && regs.end[4]!=-1)
      {
         // extract the oxygen from the buffer
         strcpy(o,extract(buf,regs.start[5]+1,regs.end[5]-regs.start[5]));

         // make sure the oxygen is well formed
         if (re_match(&o_regex,o,len,0,NULL)<=0)
         {
            // construct the subject line of the email
            char subject[32]; sprintf(subject,"Float %s",id);

            // construct the body of the email
            char body[128]; sprintf(body,"Ill-formed oxygen \"%s\" in PTS[O]-response string.\n",s);

            // send the email notification
            Email(email,subject,body);

            // make the log entry
            msg("AnalyzeSbeResponse()",body);
         }
         
         // create a valid SBE PTSO-response string
         sprintf(obuf,"%s,%s,%s,%s\r\n",p,t,s,o);
      }

      // create a valid SBE PTSO-response string
      else sprintf(obuf,"%s,%s,%s\r\n",p,t,s);
      
      // reset the buffer pointer and compute the buffer length
      buf=obuf; len=strlen(buf);
   }

   // check if the buffer satisfies the PtsFull response
   else if (re_match(&PtsFull_regex,buf,len,0,&regs)>0)
   {
      // get the salinity and make sure it's finite
      if (!finite(S=sea.S(P)))
      {
         msg("AnalyzeSbeResponse()","Invalid model salinity (%g), substituting S=0 PSU.\n");

         S=0; status=false;
      } 

      // get the temperature and make sure it's finite
      if (!finite(T=sea.T(P)))
      {
         msg("AnalyzeSbeResponse()","Invalid model temperature (%g), substituting T=0 C.\n");

         T=0; status=false;
      }
      
      // extract the pressure from the PtsFull-response string
      strcpy(p,extract(buf,regs.start[1]+1,regs.end[1]-regs.start[1]));

      // make sure the pressure is well formed
      if (re_match(&p_regex,p,len,0,NULL)<=0)
      {
         // construct the subject line of the email
         char subject[32]; sprintf(subject,"Float %s",id);

         // construct the body of the email
         char body[128]; sprintf(body,"Ill-formed pressure \"%s\" in PtsFull-response string.\n",p);

         // send the email notification
         Email(email,subject,body);

         // make the log entry
         msg("AnalyzeSbeResponse()",body);
      }
      else {sprintf(p,"%8.2f",P+POffset);}
           
      // extract the temperature from the buffer
      strcpy(t,extract(buf,regs.start[2]+1,regs.end[2]-regs.start[2]));

      // make sure the temperature is well formed
      if (re_match(&t_regex,t,len,0,NULL)<=0)
      {
         // construct the subject line of the email
         char subject[32]; sprintf(subject,"Float %s",id);

         // construct the body of the email
         char body[128]; sprintf(body,"Ill-formed temperature \"%s\" in "
                                 "PtsFull-response string.\n",t);

         // send the email notification
         Email(email,subject,body);

         // make the log entry
         msg("AnalyzeSbeResponse()",body);
      }
      else {sprintf(t,"%8.4f",T);}
 
      // extract the salinity from the buffer
      strcpy(s,extract(buf,regs.start[3]+1,regs.end[3]-regs.start[3]));

      // make sure the salinity is well formed
      if (re_match(&s_regex,s,len,0,NULL)<=0)
      {
         // construct the subject line of the email
         char subject[32]; sprintf(subject,"Float %s",id);

         // construct the body of the email
         char body[128]; sprintf(body,"Ill-formed salinity \"%s\" in PtsDull-response string.\n",s);

         // send the email notification
         Email(email,subject,body);

         // make the log entry
         msg("AnalyzeSbeResponse()",body);
      }

      // make sure the salinity is nonzero (zero indicates stopped oscillation)
      else if (!atof(s)) 
      {
         // construct the subject line of the email
         char subject[32]; sprintf(subject,"Float %s",id);

         // construct the body of the email
         char body[128]; sprintf(body,"Salinity (%s) out-of-range in PtsFull-response string.\n",s);

         // send the email notification
         Email(email,subject,body);

         // make the log entry
         msg("AnalyzeSbeResponse()",body);
      }
      else {sprintf(s,"%8.4f",S);}

      // extract the non-PTS from the buffer
      strcpy(full,extract(buf,regs.start[4]+1,regs.end[4]-regs.start[4]));
         
      // create a valid SBE PtsFull-response string
      sprintf(obuf,"%s,%s,%s,%s\r\n",p,t,s,full);
      
      // reset the buffer pointer and compute the buffer length
      buf=obuf; len=strlen(buf);
   }

   // check if the buffer satisfies the PT response
   else if (re_match(&PT_regex,buf,len,0,&regs)>0)
   {
      // get the temperature and make sure it's finite
      if (!finite(T=sea.T(P)))
      {
         msg("AnalyzeSbeResponse()","Invalid model temperature (%g), substituting T=0 C.\n");

         T=0; status=false;
      }
      
      // extract the pressure from the PT-response string
      strcpy(p,extract(buf,regs.start[1]+1,regs.end[1]-regs.start[1]));

      // make sure the pressure is well formed
      if (re_match(&p_regex,p,len,0,NULL)<=0)
      {
         // construct the subject line of the email
         char subject[32]; sprintf(subject,"Float %s",id);

         // construct the body of the email
         char body[128]; sprintf(body,"Ill-formed pressure \"%s\" in PT-response string.\n",t);

         // send the email notification
         Email(email,subject,body);

         // make the log entry
         msg("AnalyzeSbeResponse()",body);
      }
      else {sprintf(p,"%8.2f",P+POffset);}
           
      // extract the temperature from the buffer
      strcpy(t,extract(buf,regs.start[2]+1,regs.end[2]-regs.start[2]));

      // make sure the temperature is well formed
      if (re_match(&t_regex,t,len,0,NULL)<=0)
      {
         // construct the subject line of the email
         char subject[32]; sprintf(subject,"Float %s",id);

         // construct the body of the email
         char body[128]; sprintf(body,"Ill-formed temperature \"%s\" in "
                                 "PT-response string.\n",t);

         // send the email notification
         Email(email,subject,body);

         // make the log entry
         msg("AnalyzeSbeResponse()",body);
      }
      else {sprintf(t,"%8.4f",T);}
 
      // create a valid SBE PT-response string
      sprintf(obuf,"%s,%s\r\n",p,t);
      
      // reset the buffer pointer and compute the buffer length
      buf=obuf; len=strlen(buf);
   }

   // check if the buffer satisfies the P response
   else if (re_match(&P_regex,buf,len,0,&regs)>0)
   {
      // extract the pressure from the P-response string
      strcpy(p,extract(buf,regs.start[1]+1,regs.end[1]-regs.start[1]));

      // make sure the pressure is well formed
      if (re_match(&p_regex,p,len,0,NULL)<=0)
      {
         // construct the subject line of the email
         char subject[32]; sprintf(subject,"Float %s",id);

         // construct the body of the email
         char body[128]; sprintf(body,"Ill-formed pressure \"%s\" in P-response string.\n",t);

         // send the email notification
         Email(email,subject,body);

         // make the log entry
         msg("AnalyzeSbeResponse()",body);
      }
      else {sprintf(p,"%8.2f",P+POffset);}

      // create a valid SBE P-response string
      sprintf(obuf,"%s\r\n",p);

      // reset the buffer pointer and compute the buffer length
      buf=obuf; len=strlen(buf);
   }

   // make a log entry that this function was mis-applied
   else
   {
      // construct the subject line of the email
      char subject[32]; sprintf(subject,"Float %s",id);

      // construct the body of the email
      char body[128]; sprintf(body,"SBE response is not a PTS[O], PT, "
                              "or P response.\n");

      // send the email notification
      Email(email,subject,body);
      
      // make the log entry
      msg("AnalyzeSbeResponse()",body);

      status=false;
   }

   if (druck) (*druck)(P+POffset); 
      
   return status;
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
bool Email(const char *addr, const char *subject, const char *body)
{
   bool status=false;
   const time_t OneMinute=60;
   static time_t last_email=0;

   // get the time
   time_t t=time(NULL);
   
   if (!addr) msg("Email()","Nonexistent email address.");
   else if (!subject) msg("Email()","Nonexistent subject line.");
   else if (!body) msg("Email()","Nonexistent message.");
   else if ((t-last_email)>OneMinute)
   {
      // create the template for the temporary file
      int fd; char fname[32]; strcpy(fname,"/var/tmp/EmailXXXXXX");

      // make a buffer for the subject line
      char subjectline[MAXSTRLEN]; 

      // write the date & time to the subject line
      strftime(subjectline,32,"[%b %d %H:%M:%S] ",gmtime(&t));

      // concatenate the subject to the date
      strcat(subjectline,subject);
      
      // create a temporary file and write the message body to it
      if ((fd=mkstemp(fname))<0 || !write(fd,body,strlen(body)))
      {
         // make a log entry of the failure
         msg("Email()","Attempt to write email message "
             "body to a temporary file failed."); 
      }
      else
      {
         // log an entry that an email is being sent
         msg("Email()","To: %s   Subject: \"%s\"   Body:",addr,subject);

         // log the body of the email message
         for (const char *p=body; *p; p++) 
         {
            // create a left margin
            if (p==body || ((*(p-1)=='\n' && (*p)))) msg.Add("                         ");

            // log the next character of the email body
            msg.Add("%c",(*p));
         }
         
         // create the command to email the 
         sprintf(scrbuf,"/bin/mail -s \"%s\" %s < %s",subjectline,addr,fname);
 
         // send the email
         system(scrbuf);

         // record the current time
         last_email=t;

         status=true;
      }

      // delete the temporary file
      unlink(fname);
   }
   
   return status;
}

/*------------------------------------------------------------------------*/
/* function to numerically invert the Fofonoff's sal78 relation           */
/*------------------------------------------------------------------------*/
double InvertSal78(double p,double t,double s)
{
   double R=NaN();
   
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
            R=NaN(); break;
         }
      }
   }
   
   return R;
}

#undef LEADER
#undef VERSION
