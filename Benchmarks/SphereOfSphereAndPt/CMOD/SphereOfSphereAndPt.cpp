
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>


#define px0_low  (21.77 - 0.1)
#define px0_high (21.77 + 0.1)
#define py0_low  (21.77 - 0.1)
#define py0_high (21.77 + 0.1)
#define pz0_low  (20.0 - 0.1)
#define pz0_high (20. + 0.1)
#define px1_low  (22.02 - 0.1)
#define px1_high (22.02 + 0.1)
#define py1_low  (21.46 - 0.1)
#define py1_high (21.46 + 0.1)
#define pz1_low  (20.0 - 0.1)
#define pz1_high (20.0 + 0.1)
#define px2_low  (21.04 - 0.1)
#define px2_high (21.04 + 0.1)
#define py2_low  (21.04 - 0.1)
#define py2_high (21.04 + 0.1)
#define pz2_low  (22.02 - 0.1)
#define pz2_high (22.02 + 0.1)
#define cx0_low  (20.0 - 0.1)
#define cx0_high (20.0 + 0.1)
#define cy0_low  (20.0 - 0.1)
#define cy0_high (20.0 + 0.1)
#define cz0_low  (20.0 - 0.1)
#define cz0_high (20.0 + 0.1)

using namespace std ;

 double _px0 ;
 double _py0 ;
 double _pz0 ;
 double _px1 ;
 double _py1 ;
 double _pz1 ;
 double _px2 ;
 double _py2 ;
 double _pz2 ;
 double _cx0 ;
 double _cy0 ;
 double _cz0 ;


template<class T>
void init() {

	_px0	=	px0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(px0_high - px0_low))) ;
	_py0	=	py0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(py0_high - py0_low))) ;
	_pz0	=	pz0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pz0_high - pz0_low))) ;
	_px1	=	px1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(px1_high - px1_low))) ;
	_py1	=	py1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(py1_high - py1_low))) ;
	_pz1	=	pz1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pz1_high - pz1_low))) ;
	_px2	=	px1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(px2_high - px2_low))) ;
	_py2	=	py1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(py2_high - py2_low))) ;
	_pz2	=	pz1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pz2_high - pz2_low))) ;
	_cx0	=	cx0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(cx0_high - cx0_low))) ;
	_cy0	=	cy0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(cy0_high - cy0_low))) ;
	_cz0	=	cz0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(cz0_high - cz0_low))) ;

}

template<class T>
T execute_spec_precision()
{

 T	 px0 =	(T)	_px0;
 T	 py0 =	(T)	_py0;
 T	 pz0 =	(T)	_pz0;
 T	 px1 =	(T)	_px1;
 T	 py1 =	(T)	_py1;
 T	 pz1 =	(T)	_pz1;
 T	 px2 =	(T)	_px2;
 T	 py2 =	(T)	_py2;
 T	 pz2 =	(T)	_pz2;
 T	 cx0 =	(T)	_cx0;
 T	 cy0 =	(T)	_cy0;
 T	 cz0 =	(T)	_cz0;


 	T radius = 2.5 ;
	T cx = cx0 ;
	T cy = cy0 ;
	T cz = cz0 ;

	T dx = px0 - cx ;
	T dy = py0 - cy ;
	T dz = pz0 - cz ;

	T dist2 = dx*dx + dy*dy + dz*dz ;

	if (dist2 > (radius*radius) ) {
		T dist = sqrt((double) dist2) ;
		T newRadius = (radius + dist) * 0.5 ;
		T k = (newRadius - radius)/dist ;
		cx = cx + dx*k ;
		cy = cy + dy*k ;
		cz = cz + dz*k ;
		radius = newRadius ;
	}

	dx = px1 - cx ;
	dy = py1 - cy ;
	dz = pz1 - cz ;

	dist2 = dx*dx + dy*dy + dz*dz ;

	if (dist2 > (radius*radius) ) {
		T dist = sqrt((double) dist2) ;
		T newRadius = (radius + dist) * 0.5 ;
		T k = (newRadius - radius)/dist ;
		cx = cx + dx*k ;
		cy = cy + dy*k ;
		cz = cz + dz*k ;
		radius = newRadius ;
	}

	dx = px2 - cx ;
	dy = py2 - cy ;
	dz = pz2 - cz ;

	dist2 = dx*dx + dy*dy + dz*dz ;

	if (dist2 > (radius*radius)) {
		T dist = sqrt((double) dist2) ;
		T newRadius = (radius + dist) * 0.5 ;
		T k = (newRadius - radius)/dist ;
		cx = cx + dx*k ;
		cy = cy + dy*k ; 
		cz = cz + dz*k ;
		radius = newRadius ;
	}

	return radius ;

}



int main(int argc, char** argv)

{

	srand(time(0));

	FILE *fp ;
	int N;
	sscanf(argv[1], "%d", &N);
	fp = fopen("sphereofsphereandpoint_profile.csv", "w+");

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
