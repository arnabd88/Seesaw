

#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>
#include <fstream>
#include <sstream>

#define s0_cx_low  -2.0
#define s0_cx_high 0.0
#define s0_cy_low  9.5
#define s0_cy_high 12.0
#define s0_r_low  1.9
#define s0_r_high 4.0
#define s1_cx_low  6.0
#define s1_cx_high 10.0
#define s1_cy_low  9.0
#define s1_cy_high 10.5
#define s1_r_low   10.5
#define s1_r_high  12.0


using namespace std ;

 double _s0_cx ;
 double _s0_cy ;
 double _s0_r  ;
 double _s1_cx ;
 double _s1_cy ;
 double _s1_r  ;


template<class T>
void init() {

	_s0_cx	=	s0_cx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(s0_cx_high - s0_cx_low))) ;
	_s0_cy	=	s0_cy_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(s0_cy_high - s0_cy_low))) ;
	_s0_r 	=	s0_r_low  + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(s0_r_high  - s0_r_low))) ;
	_s1_cx	=	s1_cx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(s1_cx_high - s1_cx_low))) ;
	_s1_cy	=	s1_cy_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(s1_cy_high - s1_cy_low))) ;
	_s1_r 	=	s1_r_low  + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(s1_r_high  - s1_r_low))) ;

}


template<class T>
T execute_spec_precision(int conditions[])
{


 T	 s0_cx =	(T)	_s0_cx;
 T	 s0_cy =	(T)	_s0_cy;
 T	 s0_r  =	(T)	_s0_r ;
 T	 s1_cx =	(T)	_s1_cx;
 T	 s1_cy =	(T)	_s1_cy;
 T	 s1_r  =	(T)	_s1_r ;


	T dx = s1_cx - s0_cx ;
	T dy = s1_cy - s0_cy ;

	T dist2 = dx*dx + dy*dy;

	T rdist2 = ((s1_r - s0_r)*(s1_r - s0_r));

	T s_cx, s_cy, s_r ;



	if ( rdist2 >= dist2 ) {
	    conditions[0] = 1;
//	    cout << rdist2 << "," << dist2 <<"," << conditions[0]<<endl;
		if (s1_r >= s0_r ) {
		    conditions[1] = 1;
			s_cx = s1_cx ;
			s_cy = s1_cy ;
			s_r  = s1_r ;
		} else {
		    conditions[1] = 0;
			s_cx = s0_cx ;
			s_cy = s0_cy ;
			s_r  = s0_r ;
		}
	} else {
	    conditions[0] = 0;
		T dist = sqrt((double) dist2);
		s_r = (dist + s0_r + s1_r)*0.5 ;
		s_cx = s0_cx ; s_cy = s0_cy ;
		conditions[2] = dist > 0.01;
		if (dist > 0.01) {
		    conditions[2] = 1;
			s_cx = s_cx + ((s_r - s0_r)/dist) * dx ;
			s_cy = s_cy + ((s_r - s0_r)/dist) * dy ;
		} else {
		   conditions[2] = 0;
		}
	}

	return s_r ;

}

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}


int main(int argc, char** argv)

{

	srand(time(0));

	FILE *fp ;
	int N;
	sscanf(argv[1], "%d", &N);

	fp = fopen("enclosingsphere_profile.csv", "w+");
	ofstream fp_divergence_inputs;
	fp_divergence_inputs.open("enclosingcircle_divergence_inputs.csv", ios::out | ios::app);

	__float80 val_dp = 0;
	__float80 val_qp = 0;
	__float80 err_dp_lp = 0;
	__float80 err_qp_dp = 0;

    __float80 maxerrlp = 0.0;
	__float80 maxerrdp = 0.0 ;

	int num_predicates = 3;
	int conditions_lp[num_predicates];
	int conditions_dp[num_predicates];
	int conditions_qp[num_predicates];
    int numinstability_lp[num_predicates];
	int numinstability_dp[num_predicates];
	__float80 maxinstabilitylp[num_predicates];
	__float80 maxinstabilitydp[num_predicates];
	__float80 instability_qp_dp[num_predicates];
	__float80 instability_dp_lp[num_predicates];
	for(int j = 0; j < num_predicates; j++) {
	    numinstability_lp[j] = 0;
        numinstability_dp[j] = 0;
        maxinstabilitylp[j] = 0.0;
        maxinstabilitydp[j] = 0.0;
        instability_dp_lp[j] = 0.0;
        instability_qp_dp[j] = 0.0;
	}

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

        err_dp_lp += fabs(val_dp - val_lp);
		err_qp_dp += fabs(val_qp - val_dp);

		if ( maxerrlp < fabs(val_dp - val_lp)) maxerrlp = fabs(val_dp - val_lp) ;
		if ( maxerrdp < fabs(val_qp - val_dp)) maxerrdp = fabs(val_qp - val_dp) ;
		for(int j = 0; j < num_predicates; j++) {
            if(conditions_lp[j] != conditions_dp[j] && conditions_lp[j] != -1 && conditions_dp[j] != -1) {
                string str = "instability_lp:" + to_string_with_precision(fabs(val_dp - val_lp), 16) + "Pred:" + to_string(j) + ",_s0_cx:" + to_string_with_precision(_s0_cx, 16) + ",_s0_cy:" + to_string_with_precision(_s0_cy, 16) + ",_s0_r:" + to_string_with_precision(_s0_r, 16) + ",_s1_cx:" + to_string_with_precision(_s1_cx, 16) + ",_s1_cy:" + to_string_with_precision(_s1_cy, 16) + ",_s1_r:" + to_string_with_precision(_s1_r, 16) + "\n";
                fp_divergence_inputs << str;
                cout << str;
                numinstability_lp[j]++;
                instability_dp_lp[j] += fabs(val_dp - val_lp);
                if ( maxinstabilitylp[j] < fabs(val_dp - val_lp)) maxinstabilitylp[j] = fabs(val_dp - val_lp) ;
            }
            if(conditions_dp[j] != conditions_qp[j] && conditions_dp[j] != -1 && conditions_qp[j] != -1) {
                string str = "instability_dp:" + to_string_with_precision(fabs(val_qp - val_dp), 16) + "Pred:" + to_string(j) + ",_s0_cx:" + to_string_with_precision(_s0_cx, 16) + ",_s0_cy:" + to_string_with_precision(_s0_cy, 16) + ",_s0_r:" + to_string_with_precision(_s0_r, 16) + ",_s1_cx:" + to_string_with_precision(_s1_cx, 16) + ",_s1_cy:" + to_string_with_precision(_s1_cy, 16) + ",_s1_r:" + to_string_with_precision(_s1_r, 16) + "\n";
                fp_divergence_inputs << str;
                cout << str;
                numinstability_dp[j]++;
                instability_qp_dp[j] += fabs(val_qp - val_dp);
                if ( maxinstabilitydp[j] < fabs(val_qp - val_dp)) maxinstabilitydp[j] = fabs(val_qp - val_dp) ;
            }
        }
	}

	fclose(fp);
	fp_divergence_inputs.close();

    cout << "Avg Error in LP -> " << err_dp_lp/N << endl ;
	cout << "Max Error in LP -> " << maxerrlp << endl ;
	cout << "Avg Error in DP -> " << err_qp_dp/N << endl ;
	cout << "Max Error in DP -> " << maxerrdp << endl ;
	for(int j = 0; j < num_predicates; j++) {
	    if(numinstability_lp[j] != 0) {
	        cout << "Max Instability in LP due to predicate -> (" << to_string(j) << ", " << maxinstabilitylp[j] << ")" << endl ;
	        cout << "Avg Instability in LP due to predicate -> (" << to_string(j) << ", " << instability_dp_lp[j]/numinstability_lp[j] << ")" << endl ;
	    }
        if(numinstability_dp[j] != 0) {
            cout << "Max Instability in DP due to predicate -> (" << to_string(j) << ", " << maxinstabilitydp[j] << ")" << endl ;
            cout << "Avg Instability in DP due to predicate -> (" << to_string(j) << ", " << instability_qp_dp[j]/numinstability_dp[j] << ")" << endl ;
        }
    }

	return 1;

}
