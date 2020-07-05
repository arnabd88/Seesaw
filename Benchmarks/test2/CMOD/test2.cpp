#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>


#define _low 0.01
#define _high 1.0

using namespace std ;

double _x1 ;
double _x2 ;
double _x3 ;
double _x4 ;


template<class T>
void init() 
{
	_x1 = _low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_high - _low))) ;
	_x2 = _low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_high - _low))) ;
	_x3 = _low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_high - _low))) ;
	_x4 = _low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_high - _low))) ;
}



template<class T>
T execute_spec_precision()
{


	T	x1 =	(T)	_x1;
	T	x2 =	(T)	_x2;
	T	x3 =	(T)	_x3;
	T	x4 =	(T)	_x4;

	T h  = (x2/x1) + x3 ;
	T g  = x1 + x1*x2 ;

	if ( x1-x2 < 0.4 ) {
		 g  = 1 + 1/g ;
		h  = x3 + x4 ;
	} else {
		if (( x3*x3 > 0.25 ) && (x4*h <= x1*x1)) {
			g  = h + x2*x3 ;
		}
	}

	T y  = g + x4 ;

	return y;

}

int main(int argc, char** argv)

{

	srand(time(0));

	FILE *fp ;
	int N;
	sscanf(argv[1], "%d", &N);
	fp = fopen("test2_profile.csv", "w+");

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

