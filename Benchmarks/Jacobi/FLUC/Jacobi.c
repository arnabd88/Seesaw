
#include "daed_builtins.h"
#include <math.h>

int main(void)
{

	double a_0_0;
	double a_0_1;
	double a_0_2;
	double a_1_0;
	double a_1_1;
	double a_1_2;
	double a_2_0;
	double a_2_1;
	double a_2_2;

	a_0_0	=	DBETWEEN_WITH_ULP(0.01, 1.0);
	a_0_1	=	DBETWEEN_WITH_ULP(0.01, 0.1);
	a_0_2	=	DBETWEEN_WITH_ULP(2.0, 3.1);
	a_1_0	=	DBETWEEN_WITH_ULP(2.5, 3.5);
	a_1_1	=	DBETWEEN_WITH_ULP(4.05, 4.15);
	a_1_2	=	DBETWEEN_WITH_ULP(4.5, 5.5);
	a_2_0	=	DBETWEEN_WITH_ULP(2.01, 4.0);
	a_2_1	=	DBETWEEN_WITH_ULP(3.02, 3.5);
	a_2_2	=	DBETWEEN_WITH_ULP(2.24, 5.26);

	double v_0_0 = 1.0;
	double v_0_1 = 0.0;
	double v_0_2 = 0.0;
	double v_1_0 = 0.0;
	double v_1_1 = 1.0;
	double v_1_2 = 0.0;
	double v_2_0 = 0.0;
	double v_2_1 = 0.0;
	double v_2_2 = 1.0;

	double r ;
	double t ;
	double c ;
	double s ;



	if (( a_1_2 > 0 && a_1_2 > 0.0001 ) || ( a_1_2 < 0 && -1*a_1_2 > 0.0001)) {

		r = (a_2_2 - a_1_1) / (2.0 * a_1_2) ;

		if ( r >= 0.0 ) {
			t = 1.0 / ( r + sqrt(1.0 + r*r));
		} else {
			t = -1.0*(1.0 / (sqrt(1.0 + r*r) - r));
		}

		c = 1.0 / (sqrt(1.0 + t*t)) ;
		s = t * c ;
	} else {
		c = 1.0 ;
		s = 0.0 ;
	}

	double J_0_0 = 1.0;
	double J_0_1 = 0.0;
	double J_0_2 = 0.0;
	double J_1_0 = 0.0;
	double J_1_1 = 1.0;
	double J_1_2 = 0.0;
	double J_2_0 = 0.0;
	double J_2_1 = 0.0;
	double J_2_2 = 1.0;

	J_1_1 = c ;
	J_1_2 = s ;
	J_2_1 = -1*s ;
	J_2_2 = c ;

	// vl = v * J
	v_0_0 = v_0_0 * J_0_0 + v_0_1 * J_1_0 + v_0_2 * J_2_0 ;
	v_0_1 = v_0_0 * J_0_1 + v_0_1 * J_1_1 + v_0_2 * J_2_1 ;
	v_0_2 = v_0_0 * J_0_2 + v_0_1 * J_1_2 + v_0_2 * J_2_2 ;
	v_1_0 = v_1_0 * J_0_0 + v_1_1 * J_1_0 + v_1_2 * J_2_0 ;
	v_1_1 = v_1_0 * J_0_1 + v_1_1 * J_1_1 + v_1_2 * J_2_1 ;
	v_1_2 = v_1_0 * J_0_2 + v_1_1 * J_1_2 + v_1_2 * J_2_2 ;
	v_2_0 = v_2_0 * J_0_0 + v_2_1 * J_1_0 + v_2_2 * J_2_0 ;
	v_2_1 = v_2_0 * J_0_1 + v_2_1 * J_1_1 + v_2_2 * J_2_1 ;
	v_2_2 = v_2_0 * J_0_2 + v_2_1 * J_1_2 + v_2_2 * J_2_2 ;

	// jta = (J.transpose() * a)
	double jta_0_0 = J_0_0 * a_0_0 + J_1_0 * a_1_0 + J_2_0 * a_2_0 ;
	double jta_0_1 = J_0_0 * a_0_1 + J_1_0 * a_1_1 + J_2_0 * a_2_1 ;
	double jta_0_2 = J_0_0 * a_0_2 + J_1_0 * a_1_2 + J_2_0 * a_2_2 ;
	double jta_1_0 = J_0_1 * a_0_0 + J_1_1 * a_1_0 + J_2_1 * a_2_0 ;
	double jta_1_1 = J_0_1 * a_0_1 + J_1_1 * a_1_1 + J_2_1 * a_2_1 ;
	double jta_1_2 = J_0_1 * a_0_2 + J_1_1 * a_1_2 + J_2_1 * a_2_2 ;
	double jta_2_0 = J_0_2 * a_0_0 + J_1_2 * a_1_0 + J_2_2 * a_2_0 ;
	double jta_2_1 = J_0_2 * a_0_1 + J_1_2 * a_1_1 + J_2_2 * a_2_1 ;
	double jta_2_2 = J_0_2 * a_0_2 + J_1_2 * a_1_2 + J_2_2 * a_2_2 ;

	//## rot_a = jta * J
	double rot_a_0_0 = jta_0_0 * J_0_0 + jta_0_1 * J_1_0 + jta_0_2 * J_2_0 ;
	double rot_a_0_1 = jta_0_0 * J_0_1 + jta_0_1 * J_1_1 + jta_0_2 * J_2_1 ;
	double rot_a_0_2 = jta_0_0 * J_0_2 + jta_0_1 * J_1_2 + jta_0_2 * J_2_2 ;
	double rot_a_1_0 = jta_1_0 * J_0_0 + jta_1_1 * J_1_0 + jta_1_2 * J_2_0 ;
	double rot_a_1_1 = jta_1_0 * J_0_1 + jta_1_1 * J_1_1 + jta_1_2 * J_2_1 ;
	double rot_a_1_2 = jta_1_0 * J_0_2 + jta_1_1 * J_1_2 + jta_1_2 * J_2_2 ;
	double rot_a_2_0 = jta_2_0 * J_0_0 + jta_2_1 * J_1_0 + jta_2_2 * J_2_0 ;
	double rot_a_2_1 = jta_2_0 * J_0_1 + jta_2_1 * J_1_1 + jta_2_2 * J_2_1 ;
	double rot_a_2_2 = jta_2_0 * J_0_2 + jta_2_1 * J_1_2 + jta_2_2 * J_2_2 ;


	double off = rot_a_0_1 * rot_a_0_1 + rot_a_0_2 * rot_a_0_2 + rot_a_1_0 * rot_a_1_0 + rot_a_1_2 * rot_a_1_2 + rot_a_2_0 * rot_a_2_0 + rot_a_2_1 * rot_a_2_1 ;

	DSENSITIVITY(off);


}
