
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>

#define TC_00_low	26.95
#define TC_00_high	27.15
#define TC_01_low	1.4137
#define TC_01_high	1.6137
#define TC_02_low	62.6
#define TC_02_high	64.6
#define TC_03_low	0.4
#define TC_03_high	0.6
#define TC_10_low	-17.68
#define TC_10_high	-14.78
#define TC_11_low	0.9
#define TC_11_high	1.1
#define TC_12_low	0.9
#define TC_12_high	1.1
#define TC_13_low	0.03
#define TC_13_high	0.24

using namespace std ;


	double  _TC_00;
	double  _TC_01;
	double  _TC_02;
	double  _TC_03;
	double  _TC_10;
	double  _TC_11;
	double  _TC_12;
	double  _TC_13;


template<class T>
void init() {

	_TC_00 = TC_00_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(TC_00_high - TC_00_low))) ;
	_TC_01 = TC_01_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(TC_01_high - TC_01_low))) ;
	_TC_02 = TC_02_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(TC_02_high - TC_02_low))) ;
	_TC_03 = TC_03_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(TC_03_high - TC_03_low))) ;
	_TC_10 = TC_10_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(TC_10_high - TC_10_low))) ;
	_TC_11 = TC_11_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(TC_11_high - TC_11_low))) ;
	_TC_12 = TC_12_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(TC_12_high - TC_12_low))) ;
	_TC_13 = TC_13_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(TC_13_high - TC_13_low))) ;

}

template<class T> 
T execute_spec_precision() {
	T  TC_00	=	(T)	_TC_00;
	T  TC_01	=	(T)	_TC_01;
	T  TC_02	=	(T)	_TC_02;
	T  TC_03	=	(T)	_TC_03;
	T  TC_10	=	(T)	_TC_10;
	T  TC_11	=	(T)	_TC_11;
	T  TC_12	=	(T)	_TC_12;
	T  TC_13	=	(T)	_TC_13;

	T SPC_0 = 0.0 ;
	T SPC_1 = 7621.0;
	T SPC_2 = 6869.955;
	T SPC_3 = 6562.816;
	T SPC_4 = 5895.944;
	T SPC_5 = 5269.557;
	T SPC_6 = 4861.344;
	T SPC_7 = 4340.477;
	T SPC_8 = 3968.494;

	T axis_slope_angle = 0.0 ;



	T line_0 = 4 ;
	T rayh_0 = 2 ;

	T object_distance  = 0.0 ;
	T ray_height  = rayh_0 ;
	T from_index  = 1.0 ;


	int iter = 0;
	T radc  = TC_00 ;
	T to_index = TC_01 ;

	if (to_index > 1.0) {
		to_index  = to_index + ((SPC_4 - SPC_4) / (SPC_3 - SPC_6)) * ((TC_01 - 1.0)/(TC_02));
	}

	if (radc >= 0.01 || radc <= -0.01) {
		T iang_sin ;
		if (object_distance == 0) {
			axis_slope_angle = 0.0 ;
			iang_sin = ray_height / radc ;
		} else {
			iang_sin = ((object_distance - radc) / radc) * sin((double) axis_slope_angle) ;
		}

		T iang = asin((double) iang_sin);
		T rang_sin = (from_index / to_index) * iang_sin ;
		T old_axis_slope_angle = axis_slope_angle ;
		axis_slope_angle = axis_slope_angle + iang - asin((double) rang_sin) ;
		T sagitta = sin((double) ((old_axis_slope_angle + iang)/2)) ;
		sagitta = 2 * radc * sagitta * sagitta ;
		object_distance = ((radc * sin((double) (old_axis_slope_angle + iang))) * (1/tan((double) axis_slope_angle))) + sagitta ;
	} else {
		T rang = -1*asin((double) ((from_index/to_index) * sin((double) axis_slope_angle))) ;
		object_distance = object_distance * ((to_index * cos((double) (-1*rang)))/(from_index * cos((double) axis_slope_angle))) ;
		axis_slope_angle = -1*rang ;
	}
		
	from_index = to_index ;
	if (iter < 4) {
		object_distance = object_distance - TC_03 ;
	}
	
	iter = iter + 1 ;
	radc = TC_10 ;
	to_index = TC_11 ;
    
	if (to_index > 1.0) {
		to_index = to_index + ((SPC_4 - SPC_4)/(SPC_3 - SPC_6)) * ((TC_11 - 1.0) / (TC_12)) ;
	}
    
	if (radc >= 0.01 || radc <= -0.01) {
		T iang_sin ;
		if (object_distance == 0) {
			axis_slope_angle = 0.0 ;
			 iang_sin = ray_height / radc ;
		} else {
			 iang_sin = ((object_distance - radc) / radc) * sin((double) axis_slope_angle) ;
		}
    
		T iang = asin((double) iang_sin);
		T rang_sin = (from_index / to_index) * iang_sin ;
		T old_axis_slope_angle = axis_slope_angle ;
		axis_slope_angle = axis_slope_angle + iang - asin((double) rang_sin) ;
		T sagitta = sin((double) ((old_axis_slope_angle + iang)/2)) ;
		sagitta = 2 * radc * sagitta * sagitta ;
		object_distance = ((radc * sin((double) (old_axis_slope_angle + iang))) * (1/tan((double) axis_slope_angle))) + sagitta ;
	} else {
		T rang = -1*asin((double) ((from_index/to_index) * sin((double) axis_slope_angle))) ;
		object_distance = object_distance * ((to_index * cos((double) (-1*rang)))/(from_index * cos((double) axis_slope_angle))) ;
		axis_slope_angle = -1*rang ;
	}

	return axis_slope_angle ;

}







int main(int argc, char** argv)

{

	srand(time(0));

	FILE *fp ;
	int N;
	sscanf(argv[1], "%d", &N);
	fp = fopen("ray_tracing_profile.csv", "w+");

	__float80 val_dp = 0;
	__float80 val_qp = 0;
	__float80 err_qp_dp = 0;

	__float80 maxerrdp = 0.0 ;

	for(int i=0; i<N; i++) {
		init<double>();
		__float80 val_dp = (__float80) execute_spec_precision<double>();
		__float80 val_qp = (__float80) execute_spec_precision<__float128>();

		err_qp_dp += fabs(val_qp - val_dp);

		if ( maxerrdp < fabs(val_qp - val_dp)) maxerrdp = fabs(val_qp - val_dp) ;
	}

	fclose(fp);

	cout << "Avg Error in DP -> " << err_qp_dp/N << endl ;
	cout << "Max Error in DP -> " << maxerrdp << endl ;


	return 1;

}
