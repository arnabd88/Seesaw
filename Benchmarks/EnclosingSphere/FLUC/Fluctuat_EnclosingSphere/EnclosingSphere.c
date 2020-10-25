#include "daed_builtins.h"

#include "daed_builtins.h"
#include <math.h>


int main(void)
{

	double s0_cx ;
	double s0_cy ;
	double s0_cz ;
	double s0_r  ;
	double s1_cx ;
	double s1_cy ;
	double s1_cz ;
	double s1_r  ;

	s0_cx	=	DBETWEEN_WITH_ULP( -2.0, 1.0);
	s0_cy	=	DBETWEEN_WITH_ULP(  8.0, 12.0);
	s0_cz	=	DBETWEEN_WITH_ULP(  1.0, 3.0);
	s0_r 	=	DBETWEEN_WITH_ULP(  1.0, 4.0);
	s1_cx	=	DBETWEEN_WITH_ULP(  5.0, 10.0);
	s1_cy	=	DBETWEEN_WITH_ULP(  9.0, 11.0);
	s1_cz	=	DBETWEEN_WITH_ULP( -1.0, 2.0);
	s1_r 	=	DBETWEEN_WITH_ULP(  5.0, 6.0 );

	double s_cx, s_cy, s_cz, s_r ;

	double dx = s1_cx - s0_cx ;
	double dy = s1_cy - s0_cy ;
	double dz = s1_cz - s0_cz ;

	double dist2 = dx*dx + dy*dy + dz*dz ;

	double rdist2 = ((s1_r - s0_r) * (s1_r - s0_r));

	if ( rdist2 >= dist2 ) {
		if (s1_r >= s0_r) {
			s_cx = s1_cx ;
			s_cy = s1_cy ;
			s_cz = s1_cz ;
			s_r  = s1_r  ;
		} else {
			s_cx = s0_cx ;
			s_cy = s0_cy ;
			s_cz = s0_cz ;
			s_r  = s0_r  ;
		}
	} else {
		double dist = sqrt(dist2);
		s_r = (dist + s0_r + s1_r)*0.5 ;
		s_cx = s0_cx;
		s_cy = s0_cy;
		s_cz = s0_cz;
		if (dist > 0.01) {
			s_cx = s_cx + ((s_r - s0_r)/dist) * dx ;
			s_cy = s_cx + ((s_r - s0_r)/dist) * dy ;
			s_cz = s_cx + ((s_r - s0_r)/dist) * dz ;
		}
	}

	DSENSITIVITY(s_r);

}
	
