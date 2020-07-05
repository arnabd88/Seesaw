

#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>


#define _ax_low  -4.157
#define _ax_high -3.157
#define _ay_low  4.93
#define _ay_high 5.93
#define _az_low  -6.73
#define _az_high -5.73
#define _bx_low  7.393
#define _bx_high 8.393
#define _by_low  -7.17
#define _by_high -6.17
#define _bz_low  8.42
#define _bz_high 9.42
#define _cx_low  3.941
#define _cx_high 4.941
#define _cy_low  7.84
#define _cy_high 8.84
#define _cz_low  -3.85
#define _cz_high -2.85
#define _px_low  1.5
#define _px_high 2.5
#define _py_low  2.5
#define _py_high 3.5
#define _pz_low  4.5
#define _pz_high 5.5


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
double _px ;
double _py ;
double _pz ;

template<class T>
void init() {
	_ax = _ax_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_ax_high - _ax_low))) ;
	_ay = _ay_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_ay_high - _ay_low))) ;
	_az = _az_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_az_high - _az_low))) ;
	_bx = _bx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_bx_high - _bx_low))) ;
	_by = _by_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_by_high - _by_low))) ;
	_bz = _bz_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_bz_high - _bz_low))) ;
	_cx = _cx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_cx_high - _cx_low))) ;
	_cy = _cy_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_cy_high - _cy_low))) ;
	_cz = _cz_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_cz_high - _cz_low))) ;
	_px = _px_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_px_high - _px_low))) ;
	_py = _py_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_py_high - _py_low))) ;
	_pz = _pz_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_pz_high - _pz_low))) ;
}



template<class T>
T execute_spec_precision()
{
	
	T ax 	=	(T)	_ax;
	T ay 	=	(T)	_ay;
	T az 	=	(T)	_az;
	T bx 	=	(T)	_bx;
	T by 	=	(T)	_by;
	T bz 	=	(T)	_bz;
	T cx 	=	(T)	_cx;
	T cy 	=	(T)	_cy;
	T cz 	=	(T)	_cz;
	T px 	=	(T)	_px;
	T py 	=	(T)	_py;
	T pz 	=	(T)	_pz;

	// code
	T bax = bx - ax ;
	T bay = by - ay ; 
	T baz = bz - az ;
	T cax = cx - ax ; 
	T cay = cy - ay ; 
	T caz = cz - az ;
	T mx  = bay*caz - baz*cay;
	T my = baz*cax - bax*caz;
	T mz = bax*cay - bay*cax;

	T nu , nv, ood, u, v, w ;

	if(( ((mx >= 0) && (my >= 0) && (mx >= my)) || ((mx < 0) && (my >= 0) && (mx+my <= 0)) || 
	    ((mx >= 0) && (my < 0) && (mx + my >= 0)) || ((mx < 0) && (my < 0) && (mx - my <= 0))
		 ) && ( ((mx >= 0) && (mz >= 0) && (mx >= mz)) || ((mx < 0) && (mz >= 0) && (mx+mz <= 0)) || 
	    ((mx >= 0) && (mz < 0) && (mx + mz >= 0)) || ((mx < 0) && (mz < 0) && (mx - mz <= 0))
		 )) {
		nu = (py-by)*(bz-cz) - (by-cy)*(pz-bz);
		nv = (py-cy)*(cz-az) - (cy-ay)*(pz-cz);
		ood = 1.0/mx ;
	}	else {

		if(( ((my >= 0) && (mx >= 0) && (my >= mx)) || ((my < 0) && (mx >= 0) && (my+mx <= 0)) || 
		    ((my >= 0) && (mx < 0) && (my + mx >= 0)) || ((my < 0) && (mx < 0) && (my - mx <= 0))
			 ) && ( ((my >= 0) && (mz >= 0) && (my >= mz)) || ((my < 0) && (mz >= 0) && (my+mz <= 0)) || 
		    ((my >= 0) && (mz < 0) && (my + mz >= 0)) || ((my < 0) && (mz < 0) && (my - mz <= 0))
			 )) {
			nu = (px - bx)*(bz - cz) - (bx - cx)*(pz-bz);
			nv = (px - cx)*(cz - az) - (cx-ax)*(pz-cz);
			ood = 1.0/(-1.0*my);
		} else {
			nu = (px-bx)*(by-cy) - (bx-cx)*(py-by);
			nv = (px - cx)*(cy-ay) - (cx - ax)*(py - cy);
			ood = 1.0/mz ;			
		}
		
	}

	u = nu * ood ;
	v = nv * ood ;
	w = 1.0 - u - v ;

	return w ;

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
