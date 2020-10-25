#include "daed_builtins.h"
int main(void)
{

	double bx ;
	double by ;
	double bz ;
	double ax ;
	double ay ;
	double az ;
	double cx ;
	double cy ;
	double cz ;
	double err ;

	err =	DBETWEEN_WITH_ULP(-0.01, 0.01) ;
	bx 	=	DBETWEEN_WITH_ULP(-4.1 - err, -3.9 + err) ;
	by 	=	DBETWEEN_WITH_ULP(3.0, 4.1 ) ;
	bz 	=	DBETWEEN_WITH_ULP(2.9, 3.1 ) ;
	ax 	=	DBETWEEN_WITH_ULP(-1.1, -0.9 ) ;
	ay 	=	DBETWEEN_WITH_ULP(1.9, 2.1 ) ;
	az 	=	DBETWEEN_WITH_ULP(1.4, 1.6 ) ;
	cx 	=	DBETWEEN_WITH_ULP(-3.1, -2.9 ) ;
	cy 	=	DBETWEEN_WITH_ULP(1.05, 1.25 ) ;
	cz 	=	DBETWEEN_WITH_ULP(-2.97, -2.77 ) ;

	double	abx = bx - ax ;
	double	aby = by - ay ;
	double	abz = bz - az ;

	double	acx = cx - ax ;
	double	acy = cy - ay ;
	double	acz = cz - az ;

	double t = acx * abx + acy * aby + acz * abz ;

	double dx, dy, dz ;

	if ( t <= 0.0 ) {
		t = 0.0 ;
		dx = ax ;
		dy = ay ;
		dz = az ;
	} else {
		double denom = abx * abx + aby * aby + abz * abz ;
		if ( t >= denom ) {
			t = 1.0 ;
			dx = bx ;
			dy = by ;
			dz = bz ;
		} else {
			t = t / denom ;
			dx = ax + t * abx ;
			dy = ay + t * aby ;
			dz = az + t * abz ;
			printf("Never Cmae here") ;
		}
	}


	DSENSITIVITY(dx);

}
