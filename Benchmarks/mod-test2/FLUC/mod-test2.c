#include "daed_builtins.h"
#include <math.h>

int main(void)
{
	
	double x1, x2;

	x1 = DBETWEEN_WITH_ULP(0.1, 10.0);
	x2 = DBETWEEN_WITH_ULP(0.1, 10.0);

	double res ;


	double h  = (x2/x1) + x1 ;
	double g  = x1 + x1*x2 ;

	if ( x1-x2 < 0.4 ) {
		g  = 1 + 1/g ;
		h  = x2 - x1 ;
	} else {
		if (( x1*x1 > 0.25 ) && (x2*h <= x1*x1)) {
			g  = h + x2*x1 ;
		}
	}

	res = g + x2 ;

	DSENSITIVITY(res);

}
