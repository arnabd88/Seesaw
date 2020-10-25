

#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>
#include <cassert>
#include <fstream>

#define s0_cx_low  -2.0
#define s0_cx_high 1.0
#define s0_cy_low  9.0
#define s0_cy_high 12.0
#define s0_cz_low  1.0
#define s0_cz_high 3.0
#define s0_r_low  1.0
#define s0_r_high 4.0
#define s1_cx_low  5.0
#define s1_cx_high 10.0
#define s1_cy_low  9.0
#define s1_cy_high 11.0
#define s1_cz_low  0.0
#define s1_cz_high 2.0
#define s1_r_low   10.0
#define s1_r_high  13.0


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
T execute_spec_precision(int conditions[])
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
	    conditions[0] = 1;
//	    cout << rdist2 << "," << dist2 <<"," << conditions[0]<<endl;
		if (s1_r >= s0_r ) {
		    conditions[1] = 1;
			s_cx = s1_cx ;
			s_cy = s1_cy ;
			s_cz = s1_cz ;
			s_r  = s1_r ;
		} else {
		    conditions[1] = 0;
			s_cx = s0_cx ;
			s_cy = s0_cy ;
			s_cz = s0_cz ;
			s_r  = s0_r ;
		}
	} else {
	    conditions[0] = 0;
		T dist = sqrt((double) dist2);
		s_r = (dist + s0_r + s1_r)*0.5 ;
		s_cx = s0_cx ; s_cy = s0_cy ; s_cz = s0_cz ;
		conditions[2] = dist > 0.01;
		if (dist > 0.01) {
		    conditions[2] = 1;
			s_cx = s_cx + ((s_r - s0_r)/dist) * dx ;
			s_cy = s_cy + ((s_r - s0_r)/dist) * dy ;
			s_cz = s_cz + ((s_r - s0_r)/dist) * dz ;
		} else {
		   conditions[2] = 0;
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
	ofstream fp_divergence_inputs;
	fp_divergence_inputs.open("enclosingsphere_divergence_inputs.csv", ios::out | ios::app);

	__float80 val_dp = 0;
	__float80 val_qp = 0;
	__float80 err_qp_lp = 0;
	__float80 err_qp_dp = 0;

    __float80 maxerrlp = 0.0;
	__float80 maxerrdp = 0.0 ;
	int num_predicates = 3;
	int conditions_lp[num_predicates];
	int conditions_dp[num_predicates];
	int conditions_qp[num_predicates];


	for(int i=0; i<N; i++) {
	    for(int j = 0; j < num_predicates; j++) {
            conditions_lp[j] = -1;
            conditions_dp[j] = -1;
            conditions_qp[j] = -1;
        }
		init<double>();
		__float80 val_lp = (__float80) execute_spec_precision<float>(conditions_lp);
		__float80 val_dp = (__float80) execute_spec_precision<double>(conditions_dp);
		__float80 val_qp = (__float80) execute_spec_precision<__float128>(conditions_qp);

        err_qp_lp += fabs(val_dp - val_lp);
		err_qp_dp += fabs(val_qp - val_dp);

		if ( maxerrlp < fabs(val_dp - val_lp)) maxerrlp = fabs(val_dp - val_lp) ;
		if ( maxerrdp < fabs(val_qp - val_dp)) maxerrdp = fabs(val_qp - val_dp) ;
		for(int j = 0; j < num_predicates; j++) {
            if(conditions_lp[j] != conditions_dp[j] && conditions_lp[j] != -1 && conditions_dp[j] != -1) {
//                ",instability_lp:" + to_string(abs(val_dp - val_lp)) +
                string str = "Pred:" + to_string(j) + ",_s0_cx:" + to_string(_s0_cx) + ",_s0_cy:" + to_string(_s0_cy) + ",_s0_cz:" + to_string(_s0_cz) + ",_s0_r:" + to_string(_s0_r) + ",_s1_cx:" + to_string(_s1_cx) + ",_s1_cy:" + to_string(_s1_cy) + ",_s1_cz:" + to_string(_s1_cz) + ",_s1_r:" + to_string(_s1_r) + "\n";
                fp_divergence_inputs << str;
                cout << "instability_lp:" << abs(val_dp - val_lp) << "," << str;
            }
            if(conditions_dp[j] != conditions_qp[j] && conditions_dp[j] != -1 && conditions_qp[j] != -1) {
//                ",instability_dp:" + to_string(fabs(val_qp - val_dp)) +
                string str = "Pred:" + to_string(j) + ",_s0_cx:" + to_string(_s0_cx) + ",_s0_cy:" + to_string(_s0_cy) + ",_s0_cz:" + to_string(_s0_cz) + ",_s0_r:" + to_string(_s0_r) + ",_s1_cx:" + to_string(_s1_cx) + ",_s1_cy:" + to_string(_s1_cy) + ",_s1_cz:" + to_string(_s1_cz) + ",_s1_r:" + to_string(_s1_r) + "\n";
                fp_divergence_inputs << str;
                cout << "instability_dp:" << abs(val_qp - val_dp) << "," << str;
            }
        }
	}

	fclose(fp);
	fp_divergence_inputs.close();

    cout << "Avg Error in LP -> " << err_qp_lp/N << endl ;
	cout << "Max Error in LP -> " << maxerrlp << endl ;
	cout << "Avg Error in DP -> " << err_qp_dp/N << endl ;
	cout << "Max Error in DP -> " << maxerrdp << endl ;

	return 1;

}
