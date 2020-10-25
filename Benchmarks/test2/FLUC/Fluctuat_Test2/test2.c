#include "daed_builtins.h"
#include "daed_builtins.h"
#include <math.h>

int main(void)
{

	double x1 ;
	double x2 ;
	double x3 ;
	double x4 ;

	x1 = DBETWEEN_WITH_ULP(0.01, 1.0);
	x2 = DBETWEEN_WITH_ULP(0.01, 1.0);
	x3 = DBETWEEN_WITH_ULP(0.01, 1.0);
	x4 = DBETWEEN_WITH_ULP(0.01, 1.0);

	double h, g, y;

	h = (x2/x1) + x3 ;
	g = x1 + x1*x2 ;

	if ( x1-x2 < 0.4 ) {
		g = 1 + 1/g ;
		h = x3 + x4 ;
	} else {
		if ( (x3*x3 > 0.25) && (x4*h <= x1*x1) ) {
			g = h + x2*x3 ;
		}
	}

	y = g + sin(x4);

	DSENSITIVITY(y);

}

