
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>
#include <fstream>
#include <sstream>

#define a_p_p_low  2.3
#define a_p_p_high 3.6
#define a_p_q_low  4.4
#define a_p_q_high 5.6
#define a_q_q_low  0.1
#define a_q_q_high 5.2

using namespace std ;

 double _a_p_p ;
 double _a_p_q ;
 double _a_q_q ;


template<class T>
void init() {

	_a_p_p = a_p_p_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(a_p_p_high - a_p_p_low))) ;
	_a_p_q = a_p_q_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(a_p_q_high - a_p_q_low))) ;
	_a_q_q = a_q_q_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(a_q_q_high - a_q_q_low))) ;

}

template<class T>
T execute_spec_precision(int conditions[])
{

  T	a_p_p =	(T) _a_p_p;
  T	a_p_q =	(T) _a_p_q;
  T	a_q_q =	(T) _a_q_q;

  T c, s ;
  	
	if (( a_p_q > 0 && a_p_q > 0.0001 ) || ( a_p_q < 0 && -1*a_p_q > 0.0001)) {
		conditions[0] = 1;
		T r = (a_q_q - a_p_p) / (2.0 * a_p_q) ;
		T t ;
		if ( r >= 0.0 ) {
		    conditions[1] = 1;
			t = 1.0 / ( r + sqrt((double) (1.0 + r*r)));
		} else {
		    conditions[1] = 0;
			t = -1*(1.0 / (sqrt((double) ((1.0 + r*r) - r))));
		}

		c = 1.0 / (sqrt((double) (1.0 + t*t))) ;
		s = t * c ;
	} else {
	    conditions[0] = 0;
		c = 1.0 ;
		s = 0.0 ;
	}

	return c ;

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
	fp = fopen("SymSchurr_profile.csv", "w+");
ofstream fp_divergence_inputs;
	fp_divergence_inputs.open("SymSchurr_divergence_inputs.csv", ios::out | ios::app);

    __float80 val_lp = 0;
	__float80 val_dp = 0;
	__float80 val_qp = 0;
	__float80 err_qp_lp = 0;
	__float80 err_qp_dp = 0;

    __float80 maxerrlp = 0.0;
	__float80 maxerrdp = 0.0 ;

    int num_predicates = 2;
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
                string str = "instability_lp:" + to_string_with_precision(fabs(val_dp - val_lp), 16) + ",Pred:" + to_string(j) + ",_a_p_p:" + to_string_with_precision(_a_p_p, 16) + ",_a_p_q:" + to_string_with_precision(_a_p_q, 16) + ",_a_q_q:"  + to_string_with_precision(_a_q_q, 16) + "\n";
                fp_divergence_inputs << str;
                cout << str;
            }
            if(conditions_dp[j] != conditions_qp[j] && conditions_dp[j] != -1 && conditions_qp[j] != -1) {
                string str = "instability_dp:" + to_string_with_precision(fabs(val_qp - val_dp), 16) + ",Pred:" + to_string(j) + ",_a_p_p:" + to_string_with_precision(_a_p_p, 16) + ",_a_p_q:" + to_string_with_precision(_a_p_q, 16) + ",_a_q_q:"  + to_string_with_precision(_a_q_q, 16) + "\n";
                fp_divergence_inputs << str;
                cout << str;
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
