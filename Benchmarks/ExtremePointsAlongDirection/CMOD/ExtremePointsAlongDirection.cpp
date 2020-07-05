
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>

#define dirx_low  (3.0-0.1)
#define dirx_high (3.0+0.1)
#define diry_low  (4.0-0.1)
#define diry_high (4.0+0.1)
#define dirz_low  (4.0-0.1)
#define dirz_high (4.0+0.1)
#define px0_low  1.0
#define px0_high 2.0
#define py0_low  1.0
#define py0_high 2.0
#define pz0_low  1.0
#define pz0_high 2.0
#define px1_low  2.5
#define px1_high 3.0
#define py1_low  2.5
#define py1_high 3.0
#define pz1_low  2.5
#define pz1_high 3.0
#define px2_low  2.5
#define px2_high 3.0
#define py2_low  2.5
#define py2_high 3.0
#define pz2_low  2.5
#define pz2_high 3.0
#define px3_low  3.2
#define px3_high 4.5
#define py3_low  3.2
#define py3_high 4.5
#define pz3_low  3.2
#define pz3_high 4.5
#define px4_low  0.1
#define px4_high 0.5
#define py4_low  0.1
#define py4_high 0.5
#define pz4_low  0.1
#define pz4_high 0.5
#define px5_low  9.1
#define px5_high 10.5
#define py5_low  9.1
#define py5_high 10.5
#define pz5_low  9.1
#define pz5_high 10.5

using namespace std ;

 double _dirx ;
 double _diry ;
 double _dirz ;
 double _px0  ;
 double _py0  ;
 double _pz0  ;
 double _px1  ;
 double _py1  ;
 double _pz1  ;
 double _px2  ;
 double _py2  ;
 double _pz2  ;
 double _px3  ;
 double _py3  ;
 double _pz3  ;
 double _px4  ;
 double _py4  ;
 double _pz4  ;
 double _px5  ;
 double _py5  ;
 double _pz5  ;


template<class T>
void init() {

	_dirx	=	dirx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(dirx_high - dirx_low))) ;
	_diry	=	dirx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(diry_high - diry_low))) ;
	_dirz	=	dirx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(dirz_high - dirz_low))) ;
	_px0	=	px0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(px0_high - px0_low))) ;
	_py0	=	py0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(py0_high - py0_low))) ;
	_pz0	=	pz0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pz0_high - pz0_low))) ;
	_px1	=	px1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(px1_high - px1_low))) ;
	_py1	=	py1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(py1_high - py1_low))) ;
	_pz1	=	pz1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pz1_high - pz1_low))) ;
	_px2	=	px2_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(px2_high - px2_low))) ;
	_py2	=	py2_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(py2_high - py2_low))) ;
	_pz2	=	pz2_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pz2_high - pz2_low))) ;
	_px3	=	px3_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(px3_high - px3_low))) ;
	_py3	=	py3_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(py3_high - py3_low))) ;
	_pz3	=	pz3_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pz3_high - pz3_low))) ;
	_px4	=	px4_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(px4_high - px4_low))) ;
	_py4	=	py4_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(py4_high - py4_low))) ;
	_pz4	=	pz4_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pz4_high - pz4_low))) ;
	_px5	=	px5_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(px5_high - px5_low))) ;
	_py5	=	py5_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(py5_high - py5_low))) ;
	_pz5	=	pz5_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pz5_high - pz5_low))) ;

}


template<class T>
T execute_spec_precision ()
{

 T	dirx 	=	(T)	_dirx;
 T	diry 	=	(T)	_diry;
 T	dirz 	=	(T)	_dirz;
 T	px0  	=	(T)	_px0 ;
 T	py0  	=	(T)	_py0 ;
 T	pz0  	=	(T)	_pz0 ;
 T	px1  	=	(T)	_px1 ;
 T	py1  	=	(T)	_py1 ;
 T	pz1  	=	(T)	_pz1 ;
 T	px2  	=	(T)	_px1 ;
 T	py2  	=	(T)	_py1 ;
 T	pz2  	=	(T)	_pz1 ;
 T	px3  	=	(T)	_px3 ;
 T	py3  	=	(T)	_py3 ;
 T	pz3  	=	(T)	_pz3 ;
 T	px4  	=	(T)	_px4 ;
 T	py4  	=	(T)	_py4 ;
 T	pz4  	=	(T)	_pz4 ;
 T	px5  	=	(T)	_px5 ;
 T	py5  	=	(T)	_py5 ;
 T	pz5  	=	(T)	_pz5 ;

 T minproj = 2.2250738585072014e-308 ;
 T maxproj = 1.7976931348623158e+308 ;

 	T proj = (px0 * dirx) + (py0 * diry) + (pz0 * dirz) ;
	if ( proj < minproj ) {
		minproj = proj ;
	} 
	if ( proj > maxproj ) {
		maxproj = proj ;
	}

	//
	proj = (px1 * dirx) + (py1 * diry) + (pz1 * dirz) ;
	if ( proj < minproj ) {
		minproj = proj ;
	}
	if ( proj > maxproj ) {
		maxproj = proj ;
	}


	//
	proj = (px2 * dirx) + (py2 * diry) + (pz2 * dirz) ;

	if ( proj < minproj ) {
		minproj = proj ;
	}
	if ( proj > maxproj ) {
		maxproj = proj ;
	}


	//
	proj = (px3 * dirx) + (py3 * diry) + (pz3 * dirz) ;

	if ( proj < minproj ) {
		minproj = proj ;
	}
	if ( proj > maxproj ) {
		maxproj = proj ;
	}


	//
	proj = (px4 * dirx) + (py4 * diry) + (pz4 * dirz) ;

	if ( proj < minproj ) {
		minproj = proj ;
	}
	if ( proj > maxproj ) {
		maxproj = proj ;
	}

	//
	proj = (px5 * dirx) + (py5 * diry) + (pz5 * dirz) ;

	if ( proj < minproj ) {
		minproj = proj ;
	}
	if ( proj > maxproj ) {
		maxproj = proj ;
	}

	return maxproj ;

}



int main(int argc, char** argv)

{

	srand(time(0));

	FILE *fp ;
	int N;
	sscanf(argv[1], "%d", &N);
	fp = fopen("extremepointsalongdirection_profile.csv", "w+");

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
