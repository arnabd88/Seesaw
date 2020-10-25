#include "daed_builtins.h"

#include "daed_builtins.h"
#include <math.h>

int main(void)
{

	double err ;
	double TC_00 ;
	double TC_01 ;
	double TC_02 ;
	double TC_03 ;
	double TC_10 ;
	double TC_11 ;
	double TC_12 ;
	double TC_13 ;

	double SPC_0 ;	
	double SPC_1 ;	
	double SPC_2 ;	
	double SPC_3 ;	
	double SPC_4 ;	
	double SPC_5 ;	
	double SPC_6 ;	
	double SPC_7 ;	
	double SPC_8 ;	


	err = DBETWEEN_WITH_ULP(-1.0, 1.0);

	TC_00 = DBETWEEN_WITH_ULP(27.05 - err, 27.05 + err);
	TC_01 = DBETWEEN_WITH_ULP(1.5137 - err, 1.5137 + err);
	TC_02 = DBETWEEN_WITH_ULP(63.6  - err, 63.6 + err);
	TC_03 = DBETWEEN_WITH_ULP(0.52  - err, 0.52  + err);
	TC_10 = DBETWEEN_WITH_ULP(-16.68  - err, -16.68  + err);
	TC_11 = DBETWEEN_WITH_ULP(1.0  - err, 1.0 + err);
	TC_12 = DBETWEEN_WITH_ULP(1.0  - err, 1.0 + err);
	TC_13 = DBETWEEN_WITH_ULP(0.138  - err, 0.138 + err);

	SPC_0	= DBETWEEN_WITH_ULP(0.0,0.0);
	SPC_1	= DBETWEEN_WITH_ULP(7621.0,7621.0);
	SPC_2	= DBETWEEN_WITH_ULP(6869.955,6869.955);
	SPC_3	= DBETWEEN_WITH_ULP(6562.816,6562.816);
	SPC_4	= DBETWEEN_WITH_ULP(5895.944,5895.944);
	SPC_5	= DBETWEEN_WITH_ULP(5269.557,5269.557);
	SPC_6	= DBETWEEN_WITH_ULP(4861.344,4861.344);
	SPC_7	= DBETWEEN_WITH_ULP(4340.477,4340.477);
	SPC_8	= DBETWEEN_WITH_ULP(3968.494,3968.494);


	int niter = 0.0;
	double paraxial = 0.0;
	double axis_slope_angle = 0.0;

	double line_0 = 4.0;
	double rayh_0 = 2.0;
	double object_distance = 0.0;
	double ray_height = rayh_0;
	double from_index = 1.0;

	int iter = 0;
	double radc = TC_00;
	double to_index = TC_01 ;

	double iang_sin ;
	double iang ;
	double rang_sin;
	double rang ;
	double old_axis_slope_angle ;
	double sagitta ;

	if (to_index > 1.0) {
		to_index = to_index + ((SPC_4 - SPC_4) / (SPC_3 - SPC_6)) * ((TC_01 - 1.0)/(TC_02));
	}

	if (radc >= 0.01 || radc <= -0.01) {
		if (object_distance == 0.0) {
			axis_slope_angle = 0.0;
			iang_sin = ray_height / radc ;
		} else {
			iang_sin = ((object_distance - radc) / radc) * sin(axis_slope_angle) ;
		}

		iang = asin(iang_sin);
		rang_sin = (from_index / to_index) * iang_sin ;
		old_axis_slope_angle = axis_slope_angle ;
		axis_slope_angle = axis_slope_angle + iang - asin(rang_sin);
		sagitta = sin((old_axis_slope_angle + iang)/2) ;
		sagitta = 2.0 * radc * sagitta * sagitta ;
		object_distance = ((radc * sin(old_axis_slope_angle + iang)) * (1/tan(axis_slope_angle))) + sagitta ;
	} 
	else {
		rang = -1*asin((from_index/to_index) * sin(axis_slope_angle)) ;
		object_distance = object_distance * ((to_index * cos(-1*rang))/(from_index * cos(axis_slope_angle))) ;
		axis_slope_angle = -1.0*rang ;
	}

	from_index = to_index;

	if (iter < 4) {
		object_distance = object_distance - TC_03 ;
	}

	iter = iter + 1;
	radc = TC_10 ;
	to_index = TC_11 ;

	if (to_index > 1.0) {
		to_index = to_index + ((SPC_4 - SPC_4)/(SPC_3 - SPC_6)) * ((TC_11 - 1.0) / (TC_12)) ;
	}

	if (radc >= 0.01 || radc <= -0.01) {
		if (object_distance == 0) {
			axis_slope_angle = 0.0;
			iang_sin = ray_height / radc ;
		} else {
			iang_sin = ((object_distance - radc) / radc) * sin(axis_slope_angle) ;
		}

		iang = asin(iang_sin);
		rang_sin = (from_index / to_index) * iang_sin ;
		old_axis_slope_angle = axis_slope_angle ;
		axis_slope_angle = axis_slope_angle + iang - asin(rang_sin) ;
		sagitta = sin((old_axis_slope_angle + iang)/2) ;
		sagitta = 2 * radc * sagitta * sagitta ;
		object_distance = ((radc * sin(old_axis_slope_angle + iang)) * (1/tan(axis_slope_angle))) + sagitta ;
	} else {
		rang = -1*asin((from_index/to_index) * sin(axis_slope_angle)) ;
		object_distance = object_distance * ((to_index * cos(-1*rang))/(from_index * cos(axis_slope_angle))) ;
		axis_slope_angle = -1*rang ;
	}

	DSENSITIVITY(axis_slope_angle);


}
