#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>


#define _x1_low 0.2
#define _x1_high 0.7
#define _x2_low 0.01
#define _x2_high 0.4

using namespace std ;

double _x1 ;
double _x2 ;


template<class T>
void init() 
{
	_x1 = _x1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_x1_high - _x1_low))) ;
	_x2 = _x2_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_x2_high - _x2_low))) ;
}



template<class T>
T execute_spec_precision()
{


	T	x1 =	(T)	_x1;
	T	x2 =	(T)	_x2;

	T h  = (x2/x1) + x1 ;
	T g  = x1 + x1*x2 ;

	if ( x1-x2 < 0.4 ) {
		 g  = 1 + 1/g ;
		h  = x2 - x1;
	} else {
		if (( x1*x1 > 0.25 ) && (x2*h <= x1*x1)) {
			g  = h + x2*x1 ;
		}
	}

	T y  = g + x2 ;

	return y;

}

int main(int argc, char** argv)

{

	srand(time(0));

	FILE *fp ;
	int N;
	sscanf(argv[1], "%d", &N);
	fp = fopen("mod-test2_profile.csv", "w+");

	__float80 val_dp = 0;
	__float80 val_qp = 0;
	__float80 err_qp_dp = 0;

	__float80 maxerrdp = 0.0 ;

	for(int i=0; i<N; i++) {
		init<double>();
		__float80 val_dp = (__float80) execute_spec_precision<double>();
		__float80 val_qp = (__float80) execute_spec_precision<__float128>();

		__float80 local_err_dp = fabs(val_qp - val_dp);
		err_qp_dp += local_err_dp;

		if ( maxerrdp < fabs(val_qp - val_dp)) maxerrdp = fabs(val_qp - val_dp) ;
		fprintf(fp, "%0.50f, %0.5f, %0.50llf, %0.50llf\n", _x1, _x2, val_dp, local_err_dp); 
	}

	fclose(fp);

	cout << "Avg Error in DP -> " << err_qp_dp/N << endl ;
	cout << "Max Error in DP -> " << maxerrdp << endl ;


	return 1;

}

