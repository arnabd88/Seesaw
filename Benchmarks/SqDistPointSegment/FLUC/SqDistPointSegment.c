
#include "daed_builtins.h"

int main(void)
{	

	double ax;
	double ay;
	double az;
	double bx;
	double by;
	double bz;
	double cx;
	double cy;
	double cz;

	ax = DBETWEEN_WITH_ULP(4.0, 5.0);
	ay = DBETWEEN_WITH_ULP(4.0, 5.0);
	az = DBETWEEN_WITH_ULP(4.0, 5.0);
	bx = DBETWEEN_WITH_ULP(0.0, 2.0);
	by = DBETWEEN_WITH_ULP(0.0, 2.0);
	bz = DBETWEEN_WITH_ULP(0.0, 2.0);
	cx = DBETWEEN_WITH_ULP(3.0, 7.0);
	cy = DBETWEEN_WITH_ULP(3.0, 7.0);
	cz = DBETWEEN_WITH_ULP(3.0, 7.0);

	double abx = bx - ax ;
	double aby = by - ay ;
	double abz = bz - az ;

	double acx = cx - ax ;
	double acy = cy - ay ;
	double acz = cz - az ;

	double bcx = bx - cx ;
	double bcy = by - cy ;
	double bcz = bz - cz ;

	double e = acx*abx + acy*aby + acz*abz ;

	double res = 0.0;

	if ( e <= 0.0 ) {
		res = acx*acx + acy*acy + acz*acz ;
	}

	double f = abx*abx + aby*aby + abz*abz ;

	if (e >= f) {
		double e2 = acx*acx + acy*acy + acz*acz ;
		res = e2 - ((e*e)/f) ;
	}

	DSENSITIVITY(res);

}
