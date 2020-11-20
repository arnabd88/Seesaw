

#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>
#include <fstream>
#include <sstream>

#define y_low  0
#define y_high 50
#define yd_low 0
#define yd_high 50

using namespace std ;

 double _y ;
 double _yd ;


template<class T>
void init() {

	_y =	y_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(y_high - y_low))) ;
    _yd =   yd_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(yd_high - yd_low))) ;
}


template<class T>
T execute_spec_precision(int conditions[])
{
 T y = (T) _y;
 T yd = (T) _yd;
 T  e = 1.0 ;
 T	eps = 0.01 ;
 T	xc0 = 0.0;
 T	xc1 = 0.0 ;
 T	Cc0 = 564.48 ;
 T	Cc1 = 0.0;
 T	Dc  = -1280.0;
 T	Ac00 = 0.499;
 T	Ac01 = -0.05;
 T	Ac10 = 0.01;
 T	Ac11 = 1.0;
 T	Bc0 = 1.0 ;
 T	Bc1 = 0.0 ;
 T  v = 0;
 T  temp_1 = 0;
 T  temp_2 = 0;
 T  e_2 = 0;
 T  v_2 = 0;
 T  temp_4 = 0;
 T  temp_5 = 0;
 T  temp_6 = 0;
 T  yc_2 = 0;
 T  u_2 = 0;
 T  xc0_2 = 0;
 T  xc1_2 = 0;
 T  temp_7 = 0;
 T  temp_8 = 0;
 T  yc_3 = 0;
 T  u_3 = 0;
 T  xc0_3 = 0;
 T  xc1_3 = 0;
 T  e_3 = 0;
 T  e_1 = 0;
 T  v_1 = 0;
 T temp = 0;
	if (e > eps) {
	    conditions[0] = 1;
	    v = y-yd;
	    temp_1 = 0;
	    if(v<-1) {
	        conditions[1] = 1;
	        temp_1 = -1;
	    } else {
	        conditions[1] = 0;
	        temp_2 = 0;
	        if(v>1){
	            conditions[2] = 1;
	            temp_2 = 1;
	        } else {
	            conditions[2] = 0;
	            temp_2 = v;
	        }
	        temp_1 = temp_2;
	    }
        T yc_1 = temp_1;
        T u_1 = ((Cc0 * xc0) + ((Cc1 * xc1) + (Dc * yc_1)));
        T xc0_1 = ((Ac00 * xc0) + ((Ac01 * xc1) + (Bc0 * yc_1)));
		T xc1_1 = ((Ac10 * xc0_1) + ((Ac11 * xc1) + (Bc1 * yc_1)));
		if ( yc_1 - xc1_1 >= 0.0) {
		    conditions[3] = 1;
		    e_1 = yc_1 - xc1_1 ;
		} else {
		    conditions[3] = 0;
		    e_1 = xc1_1 - yc_1 ;
		}
		T temp_3 = 0.0 ;
		if ( e_1 > eps ) {
		    conditions[4] = 1;
		    v_1 = y - yd;
		    temp_4 = 0;
		    if (v_1 < -1) {
		        conditions[5] = 1;
		        temp_4 = -1;
		    } else {
		        conditions[5] = 0;
		        temp_5 = 0;
		        if (v_1 > 1) {
		            conditions[6] = 1;
		            temp_5 = 1;
		        } else {
		            conditions[6] = 0;
		            temp_5 = v_1;
		        }
		        temp_4 = temp_5;
		    }
		    yc_2 = temp_4;
		    u_2 = ((Cc0 * xc0_1) + ((Cc1 * xc1_1) + (Dc * yc_2)));
		    xc0_2 = ((Ac00 * xc0_1) + ((Ac01 * xc1_1) + (Bc0 * yc_2)));
			xc1_2 = ((Ac10 * xc0_2) + ((Ac11 * xc1_1) + (Bc1 * yc_2)));
			if (yc_2 - xc1_2 >= 0.0) {
			    conditions[7] = 1;
			    e_2 = yc_2 - xc1_2 ;
			} else {
			    conditions[7] = 0;
			    e_2 = xc1_2 - yc_2 ;
			}
            temp_6 = 0;
            if ( e_2 > eps ) {
                conditions[8] = 1;
                v_2 = (y-yd);
                temp_7 = 0;
                if(v_2 < -1.0) {
                    conditions[9] = 1;
                    temp_7 = 1;
                } else {
                    conditions[9] = 0;
                    temp_8 = 0;
                    if(v_2 > 1.0) {
                        conditions[10] = 1;
                        temp_8 = 1;
                    } else {
                        conditions[10] = 0;
                        temp_8 = v_2;
                    }
                    temp_7 = temp_8;
                }
                yc_3 = temp_7;
                u_3 = ((Cc0 * xc0_2) + ((Cc1 * xc1_2) + (Dc * yc_3)));
                xc0_3 = ((Ac00 * xc0_2) + ((Ac01 * xc1_2) + (Bc0 * yc_3)));
				xc1_3 = ((Ac10 * xc0_3) + ((Ac11 * xc1_2) + (Bc1 * yc_3)));
				if (yc_3 - xc1_3 >= 0.0) {
				    conditions[11] = 1;
				    e_3 = yc_3 - xc1_3 ;
				} else {
				    conditions[11] = 0;
				    e_3 = xc1_3 - yc_3 ;
				}
				temp_6 = temp_7;
            } else {
                conditions[8] = 0;
                temp_6 = xc1_2;
            }
            temp_3 = temp_6;
		} else {
		    conditions[4] = 0;
		    temp_3 = xc1_1;
		}
		temp = temp_3;
	} else {
	    conditions[0] = 0;
	    temp = xc1;
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
	fp = fopen("lead_lag_profile.csv", "w+");
	ofstream fp_divergence_inputs;
	fp_divergence_inputs.open("lead_lag_divergence_inputs.csv", ios::out | ios::app);

    __float80 val_lp = 0;
	__float80 val_dp = 0;
	__float80 val_qp = 0;
	__float80 err_dp_lp = 0;
	__float80 err_qp_dp = 0;

    __float80 maxerrlp = 0.0;
	__float80 maxerrdp = 0.0 ;


    int num_predicates = 12;
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
                string str = "instability_lp:" + to_string_with_precision(fabs(val_dp - val_lp), 16) + ",Pred:" + to_string(j) + ",_y:" + to_string_with_precision(_y, 16) + ",_yd:" + to_string_with_precision(_yd, 16) + "\n";
                fp_divergence_inputs << str;
                cout << str;
                numinstability_lp[j]++;
                instability_dp_lp[j] += fabs(val_dp - val_lp);
                if ( maxinstabilitylp[j] < fabs(val_dp - val_lp)) maxinstabilitylp[j] = fabs(val_dp - val_lp) ;
            }
            if(conditions_dp[j] != conditions_qp[j] && conditions_dp[j] != -1 && conditions_qp[j] != -1) {
                string str = "instability_dp:" + to_string_with_precision(fabs(val_qp - val_dp), 16) + "Pred:" + to_string(j) + ",_y:" + to_string_with_precision(_y, 16) + ",_yd:" + to_string_with_precision(_yd, 16) + "\n";
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

