

#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>
#include <fstream>
#include <sstream>

#define a_0_0_low  0.01
#define a_0_0_high 1
#define a_0_1_low  0.02
#define a_0_1_high 0.1
#define a_0_2_low  2
#define a_0_2_high 3.1
#define a_1_0_low  2.5
#define a_1_0_high 3.5
#define a_1_1_low  4.05
#define a_1_1_high 4.15
#define a_1_2_low  4.5
#define a_1_2_high 5.5
#define a_2_0_low  2.01
#define a_2_0_high 4
#define a_2_1_low  3.02
#define a_2_1_high 3.5
#define a_2_2_low  2.24
#define a_2_2_high 5.26



using namespace std ;

 double _a_0_0 ;
 double _a_0_1 ;
 double _a_0_2 ;
 double _a_1_0 ;
 double _a_1_1 ;
 double _a_1_2 ;
 double _a_2_0 ;
 double _a_2_1 ;
 double _a_2_2 ;

template<class T>
void init() {
	_a_0_0 =	a_0_0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(a_0_0_high - a_0_0_low))) ;
	_a_0_1 =	a_0_1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(a_0_1_high - a_0_1_low))) ;
	_a_0_2 =	a_0_2_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(a_0_2_high - a_0_2_low))) ;
	_a_1_0 =	a_1_0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(a_1_0_high - a_1_0_low))) ;
	_a_1_1 =	a_1_1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(a_1_1_high - a_1_1_low))) ;
	_a_1_2 =	a_1_2_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(a_1_2_high - a_1_2_low))) ;
	_a_2_0 =	a_2_0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(a_2_0_high - a_2_0_low))) ;
	_a_2_1 =	a_2_1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(a_2_1_high - a_2_1_low))) ;
	_a_2_2 =	a_2_2_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(a_2_2_high - a_2_2_low))) ;
}


template<class T>
T execute_spec_precision(int conditions[])
{

 T a_0_0 = (T) _a_0_0;
 T a_0_1 = (T) _a_0_1;
 T a_0_2 = (T) _a_0_2;
 T a_1_0 = (T) _a_1_0;
 T a_1_1 = (T) _a_1_1;
 T a_1_2 = (T) _a_1_2;
 T a_2_0 = (T) _a_2_0;
 T a_2_1 = (T) _a_2_1;
 T a_2_2 = (T) _a_2_2;

 T v_0_0 = 1.0;
 T v_0_1 = 0.0;
 T v_0_2 = 0.0;
 T v_1_0 = 0.0;
 T v_1_1 = 1.0;
 T v_1_2 = 0.0;
 T v_2_0 = 0.0;
 T v_2_1 = 0.0;
 T v_2_2 = 1.0;

 T c = 0;
 T s = 0;

    if (( a_1_2 > 0 && a_1_2 > 0.0001 ) || ( a_1_2 < 0 && -1*a_1_2 > 0.0001)) {
        conditions[0] = 1;
        T r = (a_2_2 - a_1_1) / (2.0 * a_1_2) ;
        T t = 0;
		if ( r >= 0.0 ) {
		    conditions[1] = 1;
		    t = 1.0 / ( r + sqrt((double)(1.0 + r*r)));
		} else {
		    conditions[1] = 0;
		    t = -1*(1.0 / (sqrt((double)(1.0 + r*r)) - r));
		}
		c = 1.0 / (sqrt((double)(1.0 + t*t))) ;
		s = t * c ;
    } else {
        conditions[0] = 1;
        c = 1.0 ;
		s = 0.0 ;
    }

	T J_0_0 = 1.0;
	T J_0_1 = 0.0;
	T J_0_2 = 0.0;
	T J_1_0 = 0.0;
	T J_2_0 = 0.0;
	T J_1_1 = c ;
	T J_1_2 = s ;
	T J_2_1 = -1*s ;
	T J_2_2 = c ;

	v_0_0 = v_0_0 * J_0_0 + v_0_1 * J_1_0 + v_0_2 * J_2_0 ;
	v_0_1 = v_0_0 * J_0_1 + v_0_1 * J_1_1 + v_0_2 * J_2_1 ;
	v_0_2 = v_0_0 * J_0_2 + v_0_1 * J_1_2 + v_0_2 * J_2_2 ;
	v_1_0 = v_1_0 * J_0_0 + v_1_1 * J_1_0 + v_1_2 * J_2_0 ;
	v_1_1 = v_1_0 * J_0_1 + v_1_1 * J_1_1 + v_1_2 * J_2_1 ;
	v_1_2 = v_1_0 * J_0_2 + v_1_1 * J_1_2 + v_1_2 * J_2_2 ;
	v_2_0 = v_2_0 * J_0_0 + v_2_1 * J_1_0 + v_2_2 * J_2_0 ;
	v_2_1 = v_2_0 * J_0_1 + v_2_1 * J_1_1 + v_2_2 * J_2_1 ;
	v_2_2 = v_2_0 * J_0_2 + v_2_1 * J_1_2 + v_2_2 * J_2_2 ;

	T jta_0_0 = J_0_0 * a_0_0 + J_1_0 * a_1_0 + J_2_0 * a_2_0 ;
	T jta_0_1 = J_0_0 * a_0_1 + J_1_0 * a_1_1 + J_2_0 * a_2_1 ;
	T jta_0_2 = J_0_0 * a_0_2 + J_1_0 * a_1_2 + J_2_0 * a_2_2 ;
	T jta_1_0 = J_0_1 * a_0_0 + J_1_1 * a_1_0 + J_2_1 * a_2_0 ;
	T jta_1_1 = J_0_1 * a_0_1 + J_1_1 * a_1_1 + J_2_1 * a_2_1 ;
	T jta_1_2 = J_0_1 * a_0_2 + J_1_1 * a_1_2 + J_2_1 * a_2_2 ;
	T jta_2_0 = J_0_2 * a_0_0 + J_1_2 * a_1_0 + J_2_2 * a_2_0 ;
	T jta_2_1 = J_0_2 * a_0_1 + J_1_2 * a_1_1 + J_2_2 * a_2_1 ;
	T jta_2_2 = J_0_2 * a_0_2 + J_1_2 * a_1_2 + J_2_2 * a_2_2 ;

	T rot_a_0_0 = jta_0_0 * J_0_0 + jta_0_1 * J_1_0 + jta_0_2 * J_2_0 ;
	T rot_a_0_1 = jta_0_0 * J_0_1 + jta_0_1 * J_1_1 + jta_0_2 * J_2_1 ;
	T rot_a_0_2 = jta_0_0 * J_0_2 + jta_0_1 * J_1_2 + jta_0_2 * J_2_2 ;
	T rot_a_1_0 = jta_1_0 * J_0_0 + jta_1_1 * J_1_0 + jta_1_2 * J_2_0 ;
	T rot_a_1_1 = jta_1_0 * J_0_1 + jta_1_1 * J_1_1 + jta_1_2 * J_2_1 ;
	T rot_a_1_2 = jta_1_0 * J_0_2 + jta_1_1 * J_1_2 + jta_1_2 * J_2_2 ;
	T rot_a_2_0 = jta_2_0 * J_0_0 + jta_2_1 * J_1_0 + jta_2_2 * J_2_0 ;
	T rot_a_2_1 = jta_2_0 * J_0_1 + jta_2_1 * J_1_1 + jta_2_2 * J_2_1 ;
	T rot_a_2_2 = jta_2_0 * J_0_2 + jta_2_1 * J_1_2 + jta_2_2 * J_2_2 ;

	T off = rot_a_0_1 * rot_a_0_1 + rot_a_0_2 * rot_a_0_2 + rot_a_1_0 * rot_a_1_0 + rot_a_1_2 * rot_a_1_2 + rot_a_2_0 * rot_a_2_0 + rot_a_2_1 * rot_a_2_1 ;
	return off ;
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
	fp = fopen("Jacobi_profile.csv", "w+");
	ofstream fp_divergence_inputs;
	fp_divergence_inputs.open("Jacobi_divergence_inputs.csv", ios::out | ios::app);

    __float80 val_lp = 0;
	__float80 val_dp = 0;
	__float80 val_qp = 0;
	__float80 err_dp_lp = 0;
	__float80 err_qp_dp = 0;

    __float80 maxerrlp = 0.0;
	__float80 maxerrdp = 0.0 ;


    int num_predicates = 2;
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
                string str = "instability_lp:" + to_string_with_precision(fabs(val_dp - val_lp), 16) + ",Pred:" + to_string(j) + ",_a_0_0:" + to_string_with_precision(_a_0_0, 16) + ",_a_0_1:" + to_string_with_precision(_a_0_1, 16) + ",_a_0_2:" + to_string_with_precision(_a_0_2, 16) + ",_a_1_0:" + to_string_with_precision(_a_1_0, 16) + ",_a_1_1:" + to_string_with_precision(_a_1_1, 16) + ",_a_1_2:" + to_string_with_precision(_a_1_2, 16) + ",_a_2_0:" + to_string_with_precision(_a_2_0, 16) + ",_a_2_1:" + to_string_with_precision(_a_2_1, 16) + ",_a_2_2:" + to_string_with_precision(_a_2_2, 16) + "\n";
                fp_divergence_inputs << str;
                cout << str;
                numinstability_lp[j]++;
                instability_dp_lp[j] += fabs(val_dp - val_lp);
                if ( maxinstabilitylp[j] < fabs(val_dp - val_lp)) maxinstabilitylp[j] = fabs(val_dp - val_lp) ;
            }
            if(conditions_dp[j] != conditions_qp[j] && conditions_dp[j] != -1 && conditions_qp[j] != -1) {
                string str = "instability_dp:" + to_string_with_precision(fabs(val_qp - val_dp), 16) + "Pred:" + to_string(j) + ",_a_0_0:" + to_string_with_precision(_a_0_0, 16) + ",_a_0_1:" + to_string_with_precision(_a_0_1, 16) + ",_a_0_2:" + to_string_with_precision(_a_0_2, 16) + ",_a_1_0:" + to_string_with_precision(_a_1_0, 16) + ",_a_1_1:" + to_string_with_precision(_a_1_1, 16) + ",_a_1_2:" + to_string_with_precision(_a_1_2, 16) + ",_a_2_0:" + to_string_with_precision(_a_2_0, 16) + ",_a_2_1:" + to_string_with_precision(_a_2_1, 16) + ",_a_2_2:" + to_string_with_precision(_a_2_2, 16) + "\n";
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

