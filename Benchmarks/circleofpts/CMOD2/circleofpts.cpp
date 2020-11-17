

#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>
#include <fstream>
#include <sstream>

#define eps_low  -0.002
#define eps_high 0.002
#define px0_low  0
#define px0_high 12
#define py0_low  0
#define py0_high 10
#define cx0_low  2.0
#define cx0_high 2.0
#define cy0_low  3.0
#define cy0_high 3.0
#define radius_low   10.0
#define radius_high  10.0


using namespace std ;

 double _eps ;
 double _px0 ;
 double _py0  ;
 double _cx0 ;
 double _cy0 ;
 double _radius  ;


template<class T>
void init() {

	_eps =	eps_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(eps_high - eps_low))) ;
	_px0 =	(px0_low - _eps) + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/((px0_high + _eps) - (px0_low - _eps)))) ;
	_py0 =	(py0_low - _eps) + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/((py0_high + _eps) - (py0_low - _eps)))) ;
	_cx0 =	cx0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(cx0_high - cx0_low))) ;
	_cy0 =	cy0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(cy0_high - cy0_low))) ;
	_radius =	radius_low  + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(radius_high  - radius_low))) ;

}


template<class T>
T execute_spec_precision(int conditions[])
{

 T   final_radius = (T) _radius;
 T	 cx =	(T)	_cx0;
 T	 cy =	(T)	_cy0;

 T	 dx0  =	(T)	(_px0 - _cx0);
 T	 dy0 =	(T)	(_py0 - _cy0);

	T dist2 = dx0*dx0 + dy0*dy0;
    T newRadius;

	if (dist2 > (final_radius*final_radius)) {
	    conditions[0] = 1;
	    T dist = sqrt((double) dist2);
	    newRadius = (final_radius + dist) * 0.5 ;
	    T k = (newRadius - _radius)/dist ;
	    cx = _cx0 + dx0*k;
		cy = _cy0 + dy0*k;
		final_radius = newRadius ;
	} else {
        conditions[0] = 0;
	}

	return final_radius ;
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
	fp = fopen("circleofpts_profile.csv", "w+");
	ofstream fp_divergence_inputs;
	fp_divergence_inputs.open("circleofpts_divergence_inputs.csv", ios::out | ios::app);

    __float80 val_lp = 0;
	__float80 val_dp = 0;
	__float80 val_qp = 0;
	__float80 err_dp_lp = 0;
	__float80 err_qp_dp = 0;

    __float80 maxerrlp = 0.0;
	__float80 maxerrdp = 0.0 ;


    int num_predicates = 1;
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
                string str = "instability_lp:" + to_string_with_precision(fabs(val_dp - val_lp), 16) + ",Pred:" + to_string(j) + ",_eps:" + to_string_with_precision(_eps, 16) + ",px0:" + to_string_with_precision(_px0, 16) + ",_py0:" + to_string_with_precision(_py0, 16) + ",_cx0:" + to_string_with_precision(_cx0, 16) + ",_cy0:" + to_string_with_precision(_cy0, 16) + ",_radius:" + to_string_with_precision(_radius, 16) + "\n";
                fp_divergence_inputs << str;
                cout << str;
                numinstability_lp[j]++;
                instability_dp_lp[j] += fabs(val_dp - val_lp);
                if ( maxinstabilitylp[j] < fabs(val_dp - val_lp)) maxinstabilitylp[j] = fabs(val_dp - val_lp) ;
            }
            if(conditions_dp[j] != conditions_qp[j] && conditions_dp[j] != -1 && conditions_qp[j] != -1) {
                string str = "instability_dp:" + to_string_with_precision(fabs(val_qp - val_dp), 16) + "Pred:" + to_string(j) + ",_eps:" + to_string_with_precision(_eps, 16) + ",px0:" + to_string_with_precision(_px0, 16) + ",_py0:" + to_string_with_precision(_py0, 16) + ",_cx0:" + to_string_with_precision(_cx0, 16) + ",_cy0:" + to_string_with_precision(_cy0, 16) + ",_radius:" + to_string_with_precision(_radius, 16) + "\n";
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

