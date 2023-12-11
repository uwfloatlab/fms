/****************************************/
/*       member of math library         */
/****************************************/
#include <defs.p>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * $Id: dpoly.c,v 1.2 2008/02/29 17:13:45 swift Exp $
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * RCS Log:
 *
 * $Log: dpoly.c,v $
 * Revision 1.2  2008/02/29 17:13:45  swift
 * Declared explicit function prototype.
 *
 * Revision 1.1  1996/06/15 16:12:17  swift
 * Initial revision
 *
 *========================================================================*/
/* function to evaluate an n(th) order polynimial                         */
/*========================================================================*/
/*
   This function evaluates an (n)th order polynomial at a specified
   point (x) using Horner's algorthm.  The polynomial has the form:

           y = A0 + x(A1 + x(A2 + x(A3 + ... + x(An))))

      Input:
         x.........The point where the polynomial is evaluated.
         coeff[]...An array of coefficients: coeff[]={A0,A1,A2,...,An}. 
                   Beware: An (n)th order polynomial requires an array
                   with (n+1) elements.  
         n.........The order of the polynomial to be evaluated.

   written by Dana Swift 3/10/88
*/
double dswiftpoly(double x,const double coeff[],int n)
{
   int i;
   double P=coeff[n];

   /* evaluate the (n)th order polynomial using Horner's algorithm */
   for (i=n; i>0; i--)
   {
      P *= x;
      P += coeff[i-1];
   }

   return P;
}
