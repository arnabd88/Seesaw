#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>


#define _low -5.0
#define _high 5.0

using namespace std ;

double _r_X ;
double _r_Y ;

template<class T>
void init() 
{
	_r_X = _low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_high - _low))) ;
	_r_Y = _low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_high - _low))) ;
}

template<class T>
T execute_spec_precision()
{


	T r_X = (T) _r_X ;
	T r_Y = (T) _r_Y ;
	T res ;

	if ( r_Y <= 0) {
		if ( r_X <= 0) {
			res = -1.4717 + 2.83079*r_X + 0.786996*r_X*r_X + 2.83079*r_Y - 1.07939e-16*r_X*r_Y + 0.786996*r_Y*r_Y;
		} else {
			res = -1.4717 - 2.33079*r_X + 0.786996*r_X*r_X + 2.83079*r_Y + 9.1748e-16*r_X*r_Y + 0.786996*r_Y*r_Y;
		}
	} else {
		if ( r_X <= 0) {
			res = -1.4717 + 2.83079*r_X + 0.786996*r_X*r_X - 2.33079*r_Y + 3.23816e-16*r_X*r_Y + 0.786996*r_Y*r_Y;
		} else {
			res = -1.4717 - 2.33079*r_X + 0.786996*r_X*r_X - 2.33079*r_Y + 1.72702e-15*r_X*r_Y + 0.786996*r_Y*r_Y;
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
	fp = fopen("styblinski_profile.csv", "w+");

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
