
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>


#define bx_low  -4.1 
#define bx_high -3.9
#define by_low  3.0
#define by_high 4.1
#define bz_low  2.9
#define bz_high 3.1
#define ax_low  -1.1
#define ax_high -0.9
#define ay_low  1.9
#define ay_high 2.1
#define az_low  1.4
#define az_high 1.6
#define cx_low  -3.1
#define cx_high -2.9
#define cy_low  1.05
#define cy_high 1.25
#define cz_low  -2.97
#define cz_high -2.77

using namespace std ;

double _ax ;
double _ay ;
double _az ;
double _bx ;
double _by ;
double _bz ;
double _cx ;
double _cy ;
double _cz ;

template<class T>
void init() {
	_ax = ax_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(ax_high - ax_low))) ;
	_ay = ay_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(ay_high - ay_low))) ;
	_az = az_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(az_high - az_low))) ;
	_bx = bx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(bx_high - bx_low))) ;
	_by = by_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(by_high - by_low))) ;
	_bz = bz_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(bz_high - bz_low))) ;
	_cx = cx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(cx_high - cx_low))) ;
	_cy = cy_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(cy_high - cy_low))) ;
	_cz = cz_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(cz_high - cz_low))) ;
}


template<class T>
T execute_spec_precision()
{

	
	T	ax  =	(T)	_ax ;
	T	ay  =	(T)	_ay ;
	T	az  =	(T)	_az ;
	T	bx  =	(T)	_bx ;
	T	by  =	(T)	_by ;
	T	bz  =	(T)	_bz ;
	T	cx  =	(T)	_cx ;
	T	cy  =	(T)	_cy ;
	T	cz  =	(T)	_cz ;


	T	abx = bx - ax ;
	T	aby = by - ay ;
	T	abz = bz - az ;

	T	acx = cx - ax ;
	T	acy = cy - ay ;
	T	acz = cz - az ;

	T t = acx * abx + acy * aby + acz * abz ;

	T dx, dy, dz ;

	if ( t <= 0.0 ) {
		t = 0.0 ;
		dx = ax ;
		dy = ay ;
		dz = az ;
	} else {
		T denom = abx * abx + aby * aby + abz * abz ;
		if ( t >= denom ) {
			t = 1.0 ;
			dx = bx ;
			dy = by ;
			dz = bz ;
		} else {
			t = t / denom ;
			dx = ax + t * abx ;
			dy = ay + t * aby ;
			dz = az + t * abz ;
			printf("Never Cmae here") ;
		}
	}


	return dx ;
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
