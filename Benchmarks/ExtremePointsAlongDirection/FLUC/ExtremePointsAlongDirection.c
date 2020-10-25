
#include "daed_builtins.h"

#include <math.h>

int main(void) 
{


	double dirx ;
	double diry ;
	double dirz ;

	double px0 ;
	double py0 ;
	double pz0 ;
	double px1 ;
	double py1 ;
	double pz1 ;
	double px2 ;
	double py2 ;
	double pz2 ;
	double px3 ;
	double py3 ;
	double pz3 ;
	double px4 ;
	double py4 ;
	double pz4 ;
	double px5 ;
	double py5 ;
	double pz5 ;

	dirx = DBETWEEN_WITH_ULP(3.0, 3.0);
	diry = DBETWEEN_WITH_ULP(4.0, 4.0);
	dirz = DBETWEEN_WITH_ULP(4.0, 4.0);
	px0  = DBETWEEN_WITH_ULP(1.0, 2.0);
	py0  = DBETWEEN_WITH_ULP(1.0, 2.0);
	pz0  = DBETWEEN_WITH_ULP(1.0, 2.0);
	px1  = DBETWEEN_WITH_ULP(2.5, 3.0);
	py1  = DBETWEEN_WITH_ULP(2.5, 3.0);
	pz1  = DBETWEEN_WITH_ULP(2.5, 3.0);
	px2  = DBETWEEN_WITH_ULP(1.2, 2.0);
	py2  = DBETWEEN_WITH_ULP(1.2, 2.0);
	pz2  = DBETWEEN_WITH_ULP(1.2, 2.0);
	px3  = DBETWEEN_WITH_ULP(3.2, 4.5);
	py3  = DBETWEEN_WITH_ULP(3.2, 4.5);
	pz3  = DBETWEEN_WITH_ULP(3.2, 4.5);
	px4  = DBETWEEN_WITH_ULP(0.1, 0.5);
	py4  = DBETWEEN_WITH_ULP(0.1, 0.5);
	pz4  = DBETWEEN_WITH_ULP(0.1, 0.5);
	px5  = DBETWEEN_WITH_ULP(9.1, 10.5);
	py5  = DBETWEEN_WITH_ULP(9.1, 10.5);
	pz5  = DBETWEEN_WITH_ULP(9.1, 10.5);

	double minproj = 2.2250738585072014e-308 ;
	double maxproj = 1.7976931348623158e+308 ;

	double proj = (px0 * dirx) + (py0 * diry) + (pz0 * dirz);

	if ( proj < minproj)	minproj = proj ;
	if ( proj > maxproj)	maxproj = proj ;

	proj = (px1 * dirx) + (py1 * diry) + (pz1 * dirz);

	if (proj < minproj)	minproj = proj ;
	if (proj > maxproj) maxproj = proj ;

	proj = (px2 * dirx) + (py2 * diry) + (pz2 * dirz);

	if (proj < minproj)	minproj = proj ;
	if (proj > maxproj) maxproj = proj ;


	proj = (px3 * dirx) + (py3 * diry) + (pz3 * dirz);

	if (proj < minproj)	minproj = proj ;
	if (proj > maxproj) maxproj = proj ;

	proj = (px4 * dirx) + (py4 * diry) + (pz4 * dirz);

	if (proj < minproj)	minproj = proj ;
	if (proj > maxproj) maxproj = proj ;

	proj = (px5 * dirx) + (py5 * diry) + (pz5 * dirz);

	if (proj < minproj)	minproj = proj ;
	if (proj > maxproj) maxproj = proj ;

	DSENSITIVITY(minproj);
	DSENSITIVITY(maxproj);

}
