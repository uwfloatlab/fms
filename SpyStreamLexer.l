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

