
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>

#define bx_low  4.0
#define bx_high 5.0
#define by_low  4.0
#define by_high 5.0
#define bz_low  4.0
#define bz_high 5.0
#define ax_low  0.0
#define ax_high 2.0
#define ay_low  0.0
#define ay_high 2.0
#define az_low  0.0
#define az_high 2.0
#define cx_low  3.0
#define cx_high 7.0
#define cy_low  3.0
#define cy_high 7.0
#define cz_low  3.0
#define cz_high 7.0

using namespace std ;

 double _bx ;
 double _by ;
 double _bz ;
 double _ax ;
 double _ay ;
 double _az ;
 double _cx ;
 double _cy ;
 double _cz ;


template<class T>
void init() {
	_bx = bx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(bx_high - bx_low))) ;
	_by = bx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(by_high - by_low))) ;
	_bz = bx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(bz_high - bz_low))) ;
	_ax = ax_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(ax_high - ax_low))) ;
	_ay = ax_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(ay_high - ay_low))) ;
	_az = ax_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(az_high - az_low))) ;
	_cx = cx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(cx_high - cx_low))) ;
	_cy = cx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(cy_high - cy_low))) ;
	_cz = cx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(cz_high - cz_low))) ;
}

template<class T>
T execute_spec_precision()
{

 T	bx =	(T)	_bx;
 T	by =	(T)	_by;
 T	bz =	(T)	_bz;
 T	ax =	(T)	_ax;
 T	ay =	(T)	_ay;
 T	az =	(T)	_az;
 T	cx =	(T)	_cx;
 T	cy =	(T)	_cy;
 T	cz =	(T)	_cz;

	T abx = bx - ax ;
	T aby = by - ay ;
	T abz = bz - az ;

	T acx = cx - ax ;
	T acy = cy - ay ;
	T acz = cz - az ;

	T bcx = bx - cx ;
	T bcy = by - cy ;
	T bcz = bz - cz ;

	T e = acx*abx + acy*aby + acz*abz ;

	T res = 0.0 ;

	if(e <= 0.0) {
		res = acx*acx + acy*acy + acz*acz ;
	}

	T f = abx*abx + aby*aby + abz*abz ;
	if(e >= f) {
		T e2 = acx*acx + acy*acy + acz *acz ;
		res = e2 - ((e*e)/f) ;
	}

	return res ;


}





int main(int argc, char** argv)

{

	srand(time(0));

	FILE *fp ;
	int N;
	sscanf(argv[1], "%d", &N);
	fp = fopen("sqdistpointsegment_profile.csv", "w+");

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
