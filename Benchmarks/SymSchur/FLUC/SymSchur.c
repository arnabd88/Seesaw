#include "daed_builtins.h"
#include <math.h>
int main(void)
{
	double err1  ;
	double err2  ;
	double a_p_p ;
	double a_p_q ;
	double a_q_q ;


 err1  	=	DBETWEEN_WITH_ULP(-0.01, 0.02)  ;
 err2  	=	DBETWEEN_WITH_ULP(-0.01, 0.02)  ;
 a_p_p 	=	DBETWEEN_WITH_ULP(2.5 - err1, 3.5 + err1 ) ;
 a_p_q 	=	DBETWEEN_WITH_ULP(4.5 - err2, 5.5 + err2 ) ;
 a_q_q 	=	DBETWEEN_WITH_ULP(0.24,5.0 ) ;


	double r, c, s, t ;
	
	if (( a_p_q > 0 && a_p_q > 0.0001 ) || ( a_p_q < 0 && -1*a_p_q > 0.0001)) {
		
		r = (a_q_q - a_p_p) / (2.0 * a_p_q) ;

		if ( r >= 0.0 ) {
			t = 1.0 / ( r + sqrt(1.0 + r*r));
		} else {
			t = -1*(1.0 / (sqrt(1.0 + r*r) - r));
		}

		c = 1.0 / (sqrt(1.0 + t*t)) ;
		s = t * c ;
	} else {
		c = 1.0 ;
		s = 0.0 ;
	}

	DSENSITIVITY(c);

return 0;

}

