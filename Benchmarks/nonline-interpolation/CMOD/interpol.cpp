#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>

#define x_low  0.0 
#define x_high 10.0 


using namespace std ;


double _x ;

template<class T>
void init() {
	_x = x_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(x_high - x_low))) ;
}

template<class T>
T execute_spec_precision()
{
	T x = (T) _x ;

	T y ;

	y = x*x - x ;
	if ( y >= 0.0 ) {
		y = x / 10.0 ;
	} else {
		y = x*x + 2.0 ;
	}

	return y ;
}



int main(int argc, char** argv)

{

	srand(time(0));

	FILE *fp ;
	int N;
	sscanf(argv[1], "%d", &N);
	fp = fopen("interpol_profile.csv", "w+");

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
