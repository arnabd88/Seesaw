#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>
#include <fstream>
#include <sstream>

#define r_X_low -0.001
#define r_X_high 0.001
#define r_Y_low -0.001
#define r_Y_high 0.001

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


	T r_X = (T) _r_X ;
	T r_Y = (T) _r_Y ;
	T res ;

	if ( r_Y+1 <= 1) {
	conditions[0] = 1;
		if ( r_X+1 <= 1) {
		    conditions[1] = 1;
			res = -1.4717 + 2.83079*r_X + 0.786996*r_X*r_X + 2.83079*r_Y - 1.07939e-16*r_X*r_Y + 0.786996*r_Y*r_Y;
		} else {
		    conditions[1] = 0;
			res = -1.4717 - 2.33079*r_X + 0.786996*r_X*r_X + 2.83079*r_Y + 9.1748e-16*r_X*r_Y + 0.786996*r_Y*r_Y;
		}
	} else {
	    conditions[0] = 0;
		if ( r_X+1 <= 1) {
		    conditions[2] = 1;
			res = -1.4717 + 2.83079*r_X + 0.786996*r_X*r_X - 2.33079*r_Y + 3.23816e-16*r_X*r_Y + 0.786996*r_Y*r_Y;
		} else {
		    conditions[2] = 0;
			res = -1.4717 - 2.33079*r_X + 0.786996*r_X*r_X - 2.33079*r_Y + 1.72702e-15*r_X*r_Y + 0.786996*r_Y*r_Y;
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
	fp = fopen("styblinski_profile.csv", "w+");
ofstream fp_divergence_inputs;
	fp_divergence_inputs.open("styblinski_divergence_inputs.csv", ios::out | ios::app);

    __float80 val_lp = 0;
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
