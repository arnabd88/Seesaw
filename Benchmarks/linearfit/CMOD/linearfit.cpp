
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>

#define X_low  -4.0 
#define X_high 4.0 
#define Y_low  -4.0 
#define Y_high 4.0 

using namespace std ;

double _r_X ;
double _r_Y ;

template<class T>
void init() {
	_r_X = X_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(X_high - X_low))) ;
	_r_Y = X_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(Y_high - Y_low))) ;
}


template<class T>
T execute_spec_precision()
{

	T r_X = (T) _r_X ;
	T r_Y = (T) _r_Y ;

	T res ;


	if (r_X <= -0.0000000000000004440892098500627) {
		if (r_Y <= -0.0000000000000004440892098500627 ) {
		 	res = (0.0958099 - ((0.0557219 * r_X) - (0.0557219 * r_Y))) ;
		} else if (r_Y >0.0000000000000004440892098500627 ) {
	           res = (-0.0958099 + ((0.0557219 * r_X) - (0.0557219 * r_Y)));
		} else {
			res = 0 ;
		}
	} else if (r_X >0.0000000000000004440892098500627 ) {
	    if (r_Y <=-0.0000000000000004440892098500627 ) {
	        res = (-0.0958099 - ((0.0557219 * r_X) + (0.0557219 * r_Y)));
		} else if (r_Y > 0.0000000000000004440892098500627) {
	        res = (0.0958099 + ((0.0557219 * r_X) + (0.0557219 * r_Y))) ;
		}  else {
			res = 0 ;
		}
	}	else {
		res = 0;
	}
	

	return res ;


}

int main(int argc, char** argv)

{

	srand(time(0));

	FILE *fp ;
	int N;
	sscanf(argv[1], "%d", &N);
	fp = fopen("barycentric_ccordinates_profile.csv", "w+");

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
