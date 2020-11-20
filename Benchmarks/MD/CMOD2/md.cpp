

#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>
#include <fstream>
#include <sstream>

#define pos_0_0_low  0.01
#define pos_0_0_high 1
#define pos_0_1_low  0.02
#define pos_0_1_high 0.1
#define pos_0_2_low  2
#define pos_0_2_high 3.1
#define pos_1_0_low  2.5
#define pos_1_0_high 3.5
#define pos_1_1_low  4.05
#define pos_1_1_high 4.15
#define pos_1_2_low  4.5
#define pos_1_2_high 5.5
#define pos_2_0_low  2.01
#define pos_2_0_high 4
#define pos_2_1_low  3.02
#define pos_2_1_high 3.5
#define pos_2_2_low  2.24
#define pos_2_2_high 5.26



using namespace std ;

 double _pos_0_0 ;
 double _pos_0_1 ;
 double _pos_0_2 ;
 double _pos_1_0 ;
 double _pos_1_1 ;
 double _pos_1_2 ;
 double _pos_2_0 ;
 double _pos_2_1 ;
 double _pos_2_2 ;

template<class T>
void init() {
	_pos_0_0 =	pos_0_0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pos_0_0_high - pos_0_0_low))) ;
	_pos_0_1 =	pos_0_1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pos_0_1_high - pos_0_1_low))) ;
	_pos_0_2 =	pos_0_2_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pos_0_2_high - pos_0_2_low))) ;
	_pos_1_0 =	pos_1_0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pos_1_0_high - pos_1_0_low))) ;
	_pos_1_1 =	pos_1_1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pos_1_1_high - pos_1_1_low))) ;
	_pos_1_2 =	pos_1_2_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pos_1_2_high - pos_1_2_low))) ;
	_pos_2_0 =	pos_2_0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pos_2_0_high - pos_2_0_low))) ;
	_pos_2_1 =	pos_2_1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pos_2_1_high - pos_2_1_low))) ;
	_pos_2_2 =	pos_2_2_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pos_2_2_high - pos_2_2_low))) ;
}


template<class T>
T execute_spec_precision(int conditions[])
{

 T pos_0_0 = (T) _pos_0_0;
 T pos_0_1 = (T) _pos_0_1;
 T pos_0_2 = (T) _pos_0_2;
 T pos_1_0 = (T) _pos_1_0;
 T pos_1_1 = (T) _pos_1_1;
 T pos_1_2 = (T) _pos_1_2;
 T pos_2_0 = (T) _pos_2_0;
 T pos_2_1 = (T) _pos_2_1;
 T pos_2_2 = (T) _pos_2_2;

 T potential021 = 0;

 T d_num = 3;
 T p_num = 10;
 T step_num = 2;
 T dt = 0.1;
 T mass = 1.0;
 T pi_by2 = 1.5707963267948966;

    T r001_0 = pos_0_0 - pos_0_1 ;
    T r001_1 = pos_1_0 - pos_1_1 ;
    T r001_2 = pos_2_0 - pos_2_1 ;

    T d001 = r001_0*r001_0 + r001_1*r001_1 + r001_2*r001_2 ;
    T d001_sq_temp = sqrt((double)d001) ;
    T d001_sq = 0;
    if ( d001_sq_temp >= pi_by2 ) {
        conditions[0] = 1;
        d001_sq = pi_by2 ;
    } else {
        conditions[0] = 0;
        d001_sq = d001_sq_temp ;
    }

    T potential001 = 0.5 * sin((double)d001_sq) * sin((double)d001_sq) ;

    T force001_00 = 0.0 - r001_0 * sin((double) (2.0 * d001_sq))/d001 ;
    T force001_10 = 0.0 - r001_1 * sin((double) (2.0 * d001_sq))/d001 ;
    T force001_20 = 0.0 - r001_2 * sin((double) (2.0 * d001_sq))/d001 ;

    T r002_0 = pos_0_0 - pos_0_2 ;
    T r002_1 = pos_1_0 - pos_1_2 ;
    T r002_2 = pos_2_0 - pos_2_2 ;
    T d002 = r002_0*r002_0 + r002_1*r002_1 + r002_2*r002_2 ;
    T d002_sq_temp = sqrt((double) d002) ;
    T d002_sq = 0;
    if ( d002_sq_temp >= pi_by2 ) {
        conditions[1] = 1;
        d002_sq = pi_by2 ;
    } else {
        conditions[1] = 0;
        d002_sq = d002_sq_temp ;
    }

    T potential002 = potential001 + 0.5 * sin((double) d002_sq) * sin((double)d002_sq) ;
    T force002_00 = force001_00 - r002_0 * sin((double) (2.0 * d002_sq))/d002 ;
    T force002_10 = force001_10 - r002_1 * sin((double) (2.0 * d002_sq))/d002 ;
    T force002_20 = force001_20 - r002_2 * sin((double) (2.0 * d002_sq))/d002 ;

    T r010_0 = pos_0_1 - pos_0_0 ;
    T r010_1 = pos_1_1 - pos_1_0 ;
    T r010_2 = pos_2_1 - pos_2_0 ;
    T d010 = r010_0*r010_0 + r010_1*r010_1 + r010_2*r010_2 ;
    T d010_sq_temp = sqrt((double) d010) ;
    T d010_sq = 0;
    if ( d010_sq_temp >= pi_by2 ) {
        conditions[2] = 1;
        d010_sq = pi_by2 ;
    } else {
        conditions[2] = 0;
        d010_sq = d010_sq_temp ;
    }

    T potential010 = potential002 + 0.5 * sin((double)d010_sq) * sin((double)d010_sq) ;
    T force010_01 = 0.0 - r010_0 * sin((double) (2.0 * d010_sq))/d010 ;
    T force010_11 = 0.0 - r010_1 * sin((double) (2.0 * d010_sq))/d010 ;
    T force010_21 = 0.0 - r010_2 * sin((double) (2.0 * d010_sq))/d010 ;

    T r012_0 = pos_0_1 - pos_0_2 ;
    T r012_1 = pos_1_1 - pos_1_2 ;
    T r012_2 = pos_2_1 - pos_2_2 ;
    T d012 = r012_0*r012_0 + r012_1*r012_1 + r012_2*r012_2 ;
    T d012_sq_temp = sqrt((double) d012) ;
    T d012_sq = 0;
    if ( d012_sq_temp >= pi_by2 ) {
        conditions[3] = 1;
        d012_sq = pi_by2 ;
    } else {
        conditions[3] = 0;
        d012_sq = d012_sq_temp ;
    }


    T potential012 = potential010 + 0.5 * sin((double)d012_sq) * sin((double)d012_sq) ;
    T force012_01 = force010_01 - r012_0 * sin((double) (2.0 * d012_sq))/d012 ;
    T force012_11 = force010_11 - r012_1 * sin((double) (2.0 * d012_sq))/d012 ;
    T force012_21 = force010_21 - r012_2 * sin((double) (2.0 * d012_sq))/d012 ;

    T r020_0 = pos_0_2 - pos_0_0 ;
    T r020_1 = pos_1_2 - pos_1_0 ;
    T r020_2 = pos_2_2 - pos_2_0 ;
    T d020 = r020_0*r020_0 + r020_1*r020_1 + r020_2*r020_2 ;
    T d020_sq_temp = sqrt((double) d020) ;
    T d020_sq = 0;
    if ( d020_sq_temp >= pi_by2 ) {
        conditions[4] = 1;
        d020_sq = pi_by2 ;
    } else {
        conditions[4] = 0;
        d020_sq = d020_sq_temp ;
    }

    T potential020 = potential012 + 0.5 * sin((double)d020_sq) * sin((double)d020_sq) ;
    T force020_02 = 0.0 - r020_0 * sin((double) (2.0 * d020_sq))/d020 ;
    T force020_12 = 0.0 - r020_1 * sin((double) (2.0 * d020_sq))/d020 ;
    T force020_22 = 0.0 - r020_2 * sin((double) (2.0 * d020_sq))/d020 ;

    T r021_0 = pos_0_2 - pos_0_1 ;
    T r021_1 = pos_1_2 - pos_1_1 ;
    T r021_2 = pos_2_2 - pos_2_1 ;
    T d021 = r021_0*r021_0 + r021_1*r021_1 + r021_2*r021_2 ;
    T d021_sq_temp = sqrt((double)d021) ;
    T d021_sq = 0;
    if (  d021_sq_temp >= pi_by2 ) {
        conditions[5] = 1;
        d021_sq = pi_by2 ;
    } else {
        conditions[5] = 0;
        d021_sq = d021_sq_temp ;
    }


    potential021 = potential020 + 0.5 * sin((double)d021_sq) * sin((double)d021_sq) ;
    T force021_02 = force020_02 - r020_0 * sin((double) (2.0 * d020_sq))/d020 ;
    T force021_12 = force020_12 - r020_1 * sin((double) (2.0 * d020_sq))/d020 ;
    T force021_22 = force020_22 - r020_2 * sin((double) (2.0 * d020_sq))/d020 ;

 return potential021 ;
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
	fp = fopen("md_profile.csv", "w+");
	ofstream fp_divergence_inputs;
	fp_divergence_inputs.open("md_divergence_inputs.csv", ios::out | ios::app);

    __float80 val_lp = 0;
	__float80 val_dp = 0;
	__float80 val_qp = 0;
	__float80 err_dp_lp = 0;
	__float80 err_qp_dp = 0;

    __float80 maxerrlp = 0.0;
	__float80 maxerrdp = 0.0 ;


    int num_predicates = 6;
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
                string str = "instability_lp:" + to_string_with_precision(val_dp - val_lp, 16) + ",Pred:" + to_string(j) + ",_pos_0_0:" + to_string_with_precision(_pos_0_0, 16) + ",_pos_0_1:" + to_string_with_precision(_pos_0_1, 16) + ",_pos_0_2:" + to_string_with_precision(_pos_0_2, 16) + ",_pos_1_0:" + to_string_with_precision(_pos_1_0, 16) + ",_pos_1_1:" + to_string_with_precision(_pos_1_1, 16) + ",_pos_1_2:" + to_string_with_precision(_pos_1_2, 16) + ",_pos_2_0:" + to_string_with_precision(_pos_2_0, 16) + ",_pos_2_1:" + to_string_with_precision(_pos_2_1, 16) + ",_pos_2_2:" + to_string_with_precision(_pos_2_2, 16) + "\n";
                fp_divergence_inputs << str;
                cout << str;
                numinstability_lp[j]++;
                instability_dp_lp[j] += fabs(val_dp - val_lp);
                if ( maxinstabilitylp[j] < fabs(val_dp - val_lp)) maxinstabilitylp[j] = fabs(val_dp - val_lp) ;
            }
            if(conditions_dp[j] != conditions_qp[j] && conditions_dp[j] != -1 && conditions_qp[j] != -1) {
                string str = "instability_dp:" + to_string_with_precision(val_qp - val_dp, 16) + "Pred:" + to_string(j) + ",_pos_0_0:" + to_string_with_precision(_pos_0_0, 16) + ",_pos_0_1:" + to_string_with_precision(_pos_0_1, 16) + ",_pos_0_2:" + to_string_with_precision(_pos_0_2, 16) + ",_pos_1_0:" + to_string_with_precision(_pos_1_0, 16) + ",_pos_1_1:" + to_string_with_precision(_pos_1_1, 16) + ",_pos_1_2:" + to_string_with_precision(_pos_1_2, 16) + ",_pos_2_0:" + to_string_with_precision(_pos_2_0, 16) + ",_pos_2_1:" + to_string_with_precision(_pos_2_1, 16) + ",_pos_2_2:" + to_string_with_precision(_pos_2_2, 16) + "\n";
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

