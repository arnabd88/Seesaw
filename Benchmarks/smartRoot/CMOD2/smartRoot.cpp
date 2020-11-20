

#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>
#include <fstream>
#include <sstream>

#define a_low  -3
#define a_high 3
#define b_low  -3.5
#define b_high 3.5
#define c_low  -2
#define c_high 2


using namespace std ;

 double _a ;
 double _b ;
 double _c  ;


template<class T>
void init() {

	_a =	a_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(a_high - a_low))) ;
	_b =	b_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(b_high - b_low))) ;
	_c =	c_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(c_high - c_low))) ;

}


template<class T>
T execute_spec_precision(int conditions[])
{

 T   a = (T) _a;
 T	 b = (T) _b;
 T	 c = (T) _c;

 T	 discr = (b * b) - ((a*c) * 4);
 T	 temp = 0;
 T   temp_1 = 0;
 T   temp_2 = 0;

	if (b*b-a*c > 10) {
	    conditions[0] = 1;
	    temp_1 = 0;
	    if (b+1>1){
	        conditions[1] = 1;
	        temp_1 = (c*2)/(-1*b - sqrt((double) discr));
	    }
	    else {
	        conditions[1] = 0;
	        if (b+1<1) {
	            conditions[2] = 1;
	            temp_2 = ((-1*b + sqrt((double) discr)) / (a * 2.0));
	        }
	        else {
	            conditions[2] = 0;
	            temp_2 = ((-1*b + sqrt((double) discr)) / (a * 2.0));
	        }

	        temp_1=temp_2;
	    }
	    temp = temp_1;
	} else {
        conditions[0] = 0;
        temp = ((-1*b + sqrt((double) discr)) / (a * 2.0));
	}

	return temp ;
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
	fp = fopen("smartRoot_profile.csv", "w+");
	ofstream fp_divergence_inputs;
	fp_divergence_inputs.open("smartRoot_divergence_inputs.csv", ios::out | ios::app);

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
                string str = "instability_lp:" + to_string_with_precision(fabs(val_dp - val_lp), 16) + ",Pred:" + to_string(j) + ",_a:" + to_string_with_precision(_a, 16) + ",_b:" + to_string_with_precision(_b, 16) + ",_c:" + to_string_with_precision(_c, 16) + "\n";
                fp_divergence_inputs << str;
                cout << str;
                numinstability_lp[j]++;
                instability_dp_lp[j] += fabs(val_dp - val_lp);
                if ( maxinstabilitylp[j] < fabs(val_dp - val_lp)) maxinstabilitylp[j] = fabs(val_dp - val_lp) ;
            }
            if(conditions_dp[j] != conditions_qp[j] && conditions_dp[j] != -1 && conditions_qp[j] != -1) {
                string str = "instability_dp:" + to_string_with_precision(fabs(val_qp - val_dp), 16) + "Pred:" + to_string(j) + ",_a:" + to_string_with_precision(_a, 16) + ",_b:" + to_string_with_precision(_b, 16) + ",_c:" + to_string_with_precision(_c, 16) + "\n";
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

