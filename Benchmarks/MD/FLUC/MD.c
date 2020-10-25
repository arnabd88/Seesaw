
#include "daed_builtins.h"
#include <math.h>

int main(void)
{


	double pos_0_0 ;
	double pos_0_1 ;
	double pos_0_2 ;
	double pos_1_0 ;
	double pos_1_1 ;
	double pos_1_2 ;
	double pos_2_0 ;
	double pos_2_1 ;
	double pos_2_2 ;

	double potential001, potential002, potential010, potential012, potential020, potential021 ;

	double d001_sq, d002_sq, d010_sq, d012_sq, d020_sq, d021_sq ;

	pos_0_0 = DBETWEEN_WITH_ULP(2.96576467 - 0.1, 2.96576467 + 0.1) ;
	pos_0_1 = DBETWEEN_WITH_ULP(1.55554506 - 0.1, 1.55554506 + 0.1) ;
	pos_0_2 = DBETWEEN_WITH_ULP(8.7318717  - 0.1, 8.7318717  + 0.1) ;
	pos_1_0 = DBETWEEN_WITH_ULP(7.79206138 - 0.1, 7.79206138 + 0.1) ;
	pos_1_1 = DBETWEEN_WITH_ULP(1.06761128 - 0.1, 1.06761128 + 0.1) ;
	pos_1_2 = DBETWEEN_WITH_ULP(4.73776373 - 0.1, 4.73776373 + 0.1) ;
	pos_2_0 = DBETWEEN_WITH_ULP(2.02297642 - 0.1, 2.02297642 + 0.1) ;
	pos_2_1 = DBETWEEN_WITH_ULP(1.98961114 - 0.1, 1.98961114 + 0.1) ;
	pos_2_2 = DBETWEEN_WITH_ULP(4.15677104 - 0.1, 4.15677104 + 0.1) ;

	double d_num = 3.0 ;
	double p_num = 10 ;
	double step_num = 2 ;
	double dt = 0.1 ;
	double mass = 1.0 ;
	double pi_by2 = 1.5707963267948966 ;


	double r001_0 = pos_0_0 - pos_0_1 ;
	double r001_1 = pos_1_0 - pos_1_1 ;
	double r001_2 = pos_2_0 - pos_2_1 ;

	double d001 = r001_0*r001_0 + r001_1*r001_1 + r001_2*r001_2 ;
	double d001_sq_temp = sqrt(d001) ;
	if ( d001_sq_temp >= pi_by2 ) {
		d001_sq = pi_by2 ;
	} else {
		d001_sq = d001_sq_temp ;
	}


	potential001 = 0.5 * sin(d001_sq) * sin(d001_sq) ;

	double force001_00 = 0.0 - r001_0 * sin(2.0 * d001_sq)/d001 ;
	double force001_10 = 0.0 - r001_1 * sin(2.0 * d001_sq)/d001 ;
	double force001_20 = 0.0 - r001_2 * sin(2.0 * d001_sq)/d001 ;


	double r002_0 = pos_0_0 - pos_0_2 ;
	double r002_1 = pos_1_0 - pos_1_2 ;
	double r002_2 = pos_2_0 - pos_2_2 ;
	double d002 = r002_0*r002_0 + r002_1*r002_1 + r002_2*r002_2 ;
	double d002_sq_temp = sqrt(d002) ;
	if ( d002_sq_temp >= pi_by2 ) {
		d002_sq = pi_by2 ;
	} else {
		d002_sq = d002_sq_temp ;
	}

	potential002 = potential001 + 0.5 * sin(d002_sq) * sin(d002_sq) ;

	double force002_00 = force001_00 - r002_0 * sin(2.0 * d002_sq)/d002 ;
	double force002_10 = force001_10 - r002_1 * sin(2.0 * d002_sq)/d002 ;
	double force002_20 = force001_20 - r002_2 * sin(2.0 * d002_sq)/d002 ;


	double r010_0 = pos_0_1 - pos_0_0 ;
	double r010_1 = pos_1_1 - pos_1_0 ;
	double r010_2 = pos_2_1 - pos_2_0 ;
	double d010 = r010_0*r010_0 + r010_1*r010_1 + r010_2*r010_2 ;
	double d010_sq_temp = sqrt(d010) ;
	if ( d010_sq_temp >= pi_by2 ) {
		d010_sq = pi_by2 ;
	} else {
		d010_sq = d010_sq_temp ;
	}

	potential010 = potential002 + 0.5 * sin(d010_sq) * sin(d010_sq) ;

	double force010_01 = 0.0 - r010_0 * sin(2.0 * d010_sq)/d010 ;
	double force010_11 = 0.0 - r010_1 * sin(2.0 * d010_sq)/d010 ;
	double force010_21 = 0.0 - r010_2 * sin(2.0 * d010_sq)/d010 ;

	double r012_0 = pos_0_1 - pos_0_2 ;
	double r012_1 = pos_1_1 - pos_1_2 ;
	double r012_2 = pos_2_1 - pos_2_2 ;
	double d012 = r012_0*r012_0 + r012_1*r012_1 + r012_2*r012_2 ;
	double d012_sq_temp = sqrt(d012) ;
	if ( d012_sq_temp >= pi_by2 ) {
		d012_sq = pi_by2 ;
	} else {
		d012_sq = d012_sq_temp ;
	}


	potential012 = potential010 + 0.5 * sin(d012_sq) * sin(d012_sq) ;

	double force012_01 = force010_01 - r012_0 * sin(2.0 * d012_sq)/d012 ;
	double force012_11 = force010_11 - r012_1 * sin(2.0 * d012_sq)/d012 ;
	double force012_21 = force010_21 - r012_2 * sin(2.0 * d012_sq)/d012 ;

	double r020_0 = pos_0_2 - pos_0_0 ;
	double r020_1 = pos_1_2 - pos_1_0 ;
	double r020_2 = pos_2_2 - pos_2_0 ;
	double d020 = r020_0*r020_0 + r020_1*r020_1 + r020_2*r020_2 ;
	d020_sq = sqrt(d020) ;

	potential020 = potential012 + 0.5 * sin(d020_sq) * sin(d020_sq) ;

	double force020_02 = 0.0 - r020_0 * sin(2.0 * d020_sq)/d020 ;
	double force020_12 = 0.0 - r020_1 * sin(2.0 * d020_sq)/d020 ;
	double force020_22 = 0.0 - r020_2 * sin(2.0 * d020_sq)/d020 ;

	double r021_0 = pos_0_2 - pos_0_1 ;
	double r021_1 = pos_1_2 - pos_1_1 ;
	double r021_2 = pos_2_2 - pos_2_1 ;
	double d021 = r021_0*r021_0 + r021_1*r021_1 + r021_2*r021_2 ;
	d021_sq = sqrt(d021) ;


	potential021 = potential020 + 0.5 * sin(d021_sq) * sin(d021_sq) ;

	double force021_02 = force020_02 - r020_0 * sin(2.0 * d020_sq)/d020 ;
	double force021_12 = force020_12 - r020_1 * sin(2.0 * d020_sq)/d020 ;
	double force021_22 = force020_22 - r020_2 * sin(2.0 * d020_sq)/d020 ;

	DSENSITIVITY(potential021);

}
