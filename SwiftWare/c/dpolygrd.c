/****************************************/
/*       member of math library         */
/****************************************/
#include <defs.p>

/*========================================================================*/
/* function to evaluate the gradient of an n(th) order polynimial         */
/*========================================================================*/
double dswiftpoly_gradient(double x,const double coeff[],int n)
{
   int i;
   double dP_dx=n*coeff[n];

   for (i=n-1; i>0; i--)
   {
      dP_dx *= x;
      dP_dx += i*coeff[i];
   }

   return dP_dx;
}
