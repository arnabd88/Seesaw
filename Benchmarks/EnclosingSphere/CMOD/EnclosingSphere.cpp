

#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>


#define s0_cx_low  -2.0
#define s0_cx_high 1.0
#define s0_cy_low  8.0
#define s0_cy_high 12.0
#define s0_cz_low  1.0
#define s0_cz_high 3.0
#define s0_r_low  1.0
#define s0_r_high 4.0
#define s1_cx_low  5.0
#define s1_cx_high 10.0
#define s1_cy_low  9.0
#define s1_cy_high 11.0
#define s1_cz_low  -1.0
#define s1_cz_high 2.0
#define s1_r_low   5.0
#define s1_r_high  6.0


using namespace std ;

 double _s0_cx ; 
 double _s0_cy ; 
 double _s0_cz ; 
 double _s0_r  ;
 double _s1_cx ; 
 double _s1_cy ; 
 double _s1_cz ; 
 double _s1_r  ; 


template<class T>
void init() {

	_s0_cx	=	s0_cx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(s0_cx_high - s0_cx_low))) ;
	_s0_cy	=	s0_cy_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(s0_cy_high - s0_cy_low))) ;
	_s0_cz	=	s0_cz_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(s0_cz_high - s0_cz_low))) ;
	_s0_r 	=	s0_r_low  + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(s0_r_high  - s0_r_low))) ;
	_s1_cx	=	s1_cx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(s1_cx_high - s1_cx_low))) ;
	_s1_cy	=	s1_cy_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(s1_cy_high - s1_cy_low))) ;
	_s1_cz	=	s1_cz_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(s1_cz_high - s1_cz_low))) ;
	_s1_r 	=	s1_r_low  + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(s1_r_high  - s1_r_low))) ;
	
}


template<class T>
T execute_spec_precision()
{


 T	 s0_cx =	(T)	_s0_cx; 
 T	 s0_cy =	(T)	_s0_cy; 
 T	 s0_cz =	(T)	_s0_cz; 
 T	 s0_r  =	(T)	_s0_r ;
 T	 s1_cx =	(T)	_s1_cx; 
 T	 s1_cy =	(T)	_s1_cy; 
 T	 s1_cz =	(T)	_s1_cz; 
 T	 s1_r  =	(T)	_s1_r ; 


	T dx = s1_cx - s0_cx ;
	T dy = s1_cy - s0_cy ;
	T dz = s1_cz - s0_cz ;

	T dist2 = dx*dx + dy*dy + dz*dz ;

	T rdist2 = ((s1_r - s0_r)*(s1_r - s0_r));

	T s_cx, s_cy, s_cz, s_r ;

	if ( rdist2 >= dist2 ) {
		if (s1_r >= s0_r ) {
			s_cx = s1_cx ;
			s_cy = s1_cy ;
			s_cz = s1_cz ;
			s_r  = s1_r ;
		} else {
			s_cx = s0_cx ;
			s_cy = s0_cy ;
			s_cz = s0_cz ;
			s_r  = s0_r ;
		}
	} else {
		T dist = sqrt((double) dist2);
		s_r = (dist + s0_r + s1_r)*0.5 ;
		s_cx = s0_cx ; s_cy = s0_cy ; s_cz = s0_cz ;
		if (dist > 0.01) {
			s_cx = s_cx + ((s_r - s0_r)/dist) * dx ;
			s_cy = s_cy + ((s_r - s0_r)/dist) * dy ;
			s_cz = s_cz + ((s_r - s0_r)/dist) * dz ;
		}
	}

	return s_r ;

}


int main(int argc, char** argv)

{

	srand(time(0));

	FILE *fp ;
	int N;
	sscanf(argv[1], "%d", &N);
	fp = fopen("enclosingsphere_profile.csv", "w+");

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
