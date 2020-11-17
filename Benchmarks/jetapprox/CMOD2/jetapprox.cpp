
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>
#include <fstream>
#include <sstream>

#define r_X_low -1
#define r_X_high 1
#define r_Y_low -1
#define r_Y_high 1

using namespace std ;

double _r_X ;
double _r_Y ;

template<class T>
void init() 
{
	_r_X = r_X_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(r_X_high - r_X_low))) ;
	_r_Y = r_Y_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(r_Y_high - r_Y_low))) ;
}

template<class T>
T execute_spec_precision(int conditions[])
{

	T r_X = (T) _r_X;
	T r_Y = (T) _r_Y;

	T r_E = (4503599627370497.0 / 10141204801825835211973625643008.0) ;

	T res ;

	if (r_Y + 1 <= -1*r_E + 1) {
	    conditions[0] = 1;
		if (r_X + 1<= -1*(r_E) + 1) {
		    conditions[1] = 1;
			res = ((((T)-6766907038823601.0) / (T)72057594037927936.0) + ((((T)2820352245043009.0 / (T)9007199254740992.0) * r_X) + ((((T)3707903645206677.0 / (T)18014398509481984.0) * (r_X * r_X)) + ((((T)2572698220669995.0 / (T)2305843009213693952.0) * r_Y) - ((((T)2964535887833201.0 / (T)576460752303423488.0) * (r_X * r_Y)) + ((((T)4386589623867947.0 / (T)1152921504606846976.0) * (r_X * (r_X * r_Y))) - ((((T)5230463601635901.0 / (T)9223372036854775808.0) * (r_Y * r_Y)) + (((T)5248024901994073.0 / (T)9223372036854775808.0) * (r_X * (r_Y * r_Y))))))))));
		} else {
		    conditions[1] = 0;
			if (r_X + 1> r_E + 1) {
			    conditions[2] = 1;
				res = ((((T)-2733486815430287.0) / (T)36028797018963968.0) - ((((T)5410228275555705.0 / (T)18014398509481984.0) * r_X) + ((((T)6073482399877813.0 / (T)36028797018963968.0) * (r_X * r_X)) + ((((T)1825705966316411.0 / (T)288230376151711744.0) * r_Y) - ((((T)2623922523119677.0 / (T)288230376151711744.0) * (r_X * r_Y)) + ((((T)7213138101422277.0 / (T)576460752303423488.0) * (r_X * (r_X * r_Y))) + ((((T)5230463601635901.0 / (T)9223372036854775808.0) * (r_Y * r_Y)) + (((T)5248024901994073.0 / (T)9223372036854775808.0) * (r_X * (r_Y * r_Y))))))))));
			} else {
			    conditions[2] = 0;
				res = 0.0 ;
			}
		}
	} else {
	    conditions[0] = 0;
		if (r_Y + 1 > r_E + 1) {
		    conditions[3] = 1;
			if (r_X + 1 <= -1*(r_E) + 1) {
			    conditions[4] = 1;
				res = ((((T)-6766907038823601.0) / (T)72057594037927936.0) + ((((T)2820352245043009.0 / (T)9007199254740992.0) * r_X) + ((((T)3707903645206677.0 / (T)18014398509481984.0) * (r_X * r_X)) + ((((T)6965963260049615.0 / (T)1152921504606846976.0) * r_Y) + ((((T)4254712697563493.0 / (T)288230376151711744.0) * (r_X * r_Y)) + ((((T)5061786573825901.0 / (T)576460752303423488.0) * (r_X * (r_X * r_Y))) - ((((T)5230463601635901.0 / (T)9223372036854775808.0) * (r_Y * r_Y)) + (((T)5248024901994073.0 / (T)9223372036854775808.0) * (r_X * (r_Y * r_Y))))))))));
			} else {
			    conditions[4] = 0;
				if (r_X + 1 > r_E + 1) {
				    conditions[5] = 1;
					res = ((((T)-2733486815430287.0) / (T)36028797018963968.0) - ((((T)5410228275555705.0 / (T)18014398509481984.0) * r_X) + ((((T)6073482399877813.0 / (T)36028797018963968.0) * (r_X * r_X)) + ((((T)811604857775513.0 / (T)576460752303423488.0) * r_Y) + ((((T)1556530500332089.0 / (T)144115188075855872.0) * (r_X * r_Y)) + ((((T)4344663633352919.0 / (T)576460752303423488.0) * (r_X * (r_X * r_Y))) + ((((T)5230463601635901.0 / (T)9223372036854775808.0) * (r_Y * r_Y)) + (((T)5248024901994073.0 / (T)9223372036854775808.0) * (r_X * (r_Y * r_Y))))))))));
				} else {
				    conditions[5] = 0;
					res = 0.0;
				}
			}
		} else {
		    conditions[3] = 0;
			res = 0.0;
		}
	}

	return res ;

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
	fp = fopen("jetapprox_profile.csv", "w+");
    ofstream fp_divergence_inputs;
	fp_divergence_inputs.open("jetapprox_divergence_inputs.csv", ios::out | ios::app);

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
                string str = "instability_lp:" + to_string_with_precision(fabs(val_dp - val_lp), 16) + ",Pred:" + to_string(j) + ",_r_X:" + to_string_with_precision(_r_X, 16) + ",_r_Y:" + to_string_with_precision(_r_Y, 16) + "\n";
                fp_divergence_inputs << str;
                cout << str;
                numinstability_lp[j]++;
                instability_dp_lp[j] += fabs(val_dp - val_lp);
                if ( maxinstabilitylp[j] < fabs(val_dp - val_lp)) maxinstabilitylp[j] = fabs(val_dp - val_lp) ;
            }
            if(conditions_dp[j] != conditions_qp[j] && conditions_dp[j] != -1 && conditions_qp[j] != -1) {
                string str = "instability_dp:" + to_string_with_precision(fabs(val_qp - val_dp), 16) + ",Pred:" + to_string(j) + ",_r_X:" + to_string_with_precision(_r_X, 16) + ",_r_Y:" + to_string_with_precision(_r_Y, 16) + "\n";
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
