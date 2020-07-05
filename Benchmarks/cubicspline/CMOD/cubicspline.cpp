
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>

#define _low  -2.0 
#define _high 2.0 

using namespace std ;

double _r_X ;

template<class T>
void init() {
	_r_X = _low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_high - _low))) ;
}

template<class T>
T execute_spec_precision()
{

	T r_X = (T) _r_X ;
	T res ;
	
	if (r_X <= -1.00000000000000022204460492503136) {
		res = ((((1.0 / 4.0) * (r_X + 2.0)) * (r_X + 2.0)) * (r_X + 2.0)) ;
	} else {
		if (r_X <= -2.2204460492503136e-16) {
			res = ((1 / 4) * (((-3 * (r_X * (r_X * r_X))) - (6 * (r_X * r_X))) + 4)) ;
		 } else {
			if (r_X <= 0.9999999999999998) {
				res = ((1 / 4) * (((3 * (r_X * (r_X * r_X))) - (6 * (r_X * r_X))) + 4));
			} else {
				if (r_X > 1.00000000000000022204460492503136) {
					res = ((1 / 4) * ((2 - r_X) * ((2 - r_X) * (2 - r_X))));
				} else {
					res = 0 ;
				}
			}
		}
	}

	return res ;

}



int main(int argc, char** argv)

{

	srand(time(0));

	FILE *fp ;
	int N;
	sscanf(argv[1], "%d", &N);
	fp = fopen("cubicspline_profile.csv", "w+");

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
