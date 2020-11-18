
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>
#include <fstream>
#include <sstream>

#define TC_00_low	26.95
#define TC_00_high	27.15
#define TC_01_low	1.4137
#define TC_01_high	1.6137
#define TC_02_low	62.6
#define TC_02_high	64.6
#define TC_03_low	0.4
#define TC_03_high	0.6
#define TC_10_low	-17.68
#define TC_10_high	-14.78
#define TC_11_low	0.9
#define TC_11_high	1.1
#define TC_12_low	0.9
#define TC_12_high	1.1
#define TC_13_low	0.03
#define TC_13_high	0.24

using namespace std ;


	double  _TC_00;
	double  _TC_01;
	double  _TC_02;
	double  _TC_03;
	double  _TC_10;
	double  _TC_11;
	double  _TC_12;
	double  _TC_13;


template<class T>
void init() {

	_TC_00 = TC_00_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(TC_00_high - TC_00_low))) ;
	_TC_01 = TC_01_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(TC_01_high - TC_01_low))) ;
	_TC_02 = TC_02_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(TC_02_high - TC_02_low))) ;
	_TC_03 = TC_03_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(TC_03_high - TC_03_low))) ;
	_TC_10 = TC_10_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(TC_10_high - TC_10_low))) ;
	_TC_11 = TC_11_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(TC_11_high - TC_11_low))) ;
	_TC_12 = TC_12_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(TC_12_high - TC_12_low))) ;
	_TC_13 = TC_13_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(TC_13_high - TC_13_low))) ;

}

template<class T> 
T execute_spec_precision(int conditions[]) {
	T  TC_00	=	(T)	_TC_00;
	T  TC_01	=	(T)	_TC_01;
	T  TC_02	=	(T)	_TC_02;
	T  TC_03	=	(T)	_TC_03;
	T  TC_10	=	(T)	_TC_10;
	T  TC_11	=	(T)	_TC_11;
	T  TC_12	=	(T)	_TC_12;
	T  TC_13	=	(T)	_TC_13;

	T SPC_0 = 0.0 ;
	T SPC_1 = 7621.0;
	T SPC_2 = 6869.955;
	T SPC_3 = 6562.816;
	T SPC_4 = 5895.944;
	T SPC_5 = 5269.557;
	T SPC_6 = 4861.344;
	T SPC_7 = 4340.477;
	T SPC_8 = 3968.494;

	T axis_slope_angle = 0.0 ;



	T line_0 = 4 ;
	T rayh_0 = 2 ;

	T object_distance  = 0.0 ;
	T ray_height  = rayh_0 ;
	T from_index  = 1.0 ;


	int iter = 0;
	T radc  = TC_00 ;
	T to_index = TC_01 ;

	if (to_index > 1.0) {
	    conditions[0] = 1;
		to_index  = to_index + ((SPC_4 - SPC_4) / (SPC_3 - SPC_6)) * ((TC_01 - 1.0)/(TC_02));
	} else {
	    conditions[0] = 0;
	}

	if (radc >= 0.01 || radc <= -0.01) {
		conditions[1] = 1;
		T iang_sin ;
		if (object_distance == 0) {
		    conditions[2] = 1;
			axis_slope_angle = 0.0 ;
			iang_sin = ray_height / radc ;
		} else {
		    conditions[2] = 0;
			iang_sin = ((object_distance - radc) / radc) * sin((double) axis_slope_angle) ;
		}

		T iang = asin((double) iang_sin);
		T rang_sin = (from_index / to_index) * iang_sin ;
		T old_axis_slope_angle = axis_slope_angle ;
		axis_slope_angle = axis_slope_angle + iang - asin((double) rang_sin) ;
		T sagitta = sin((double) ((old_axis_slope_angle + iang)/2)) ;
		sagitta = 2 * radc * sagitta * sagitta ;
		object_distance = ((radc * sin((double) (old_axis_slope_angle + iang))) * (1/tan((double) axis_slope_angle))) + sagitta ;
	} else {
	    conditions[1] = 0;
		T rang = -1*asin((double) ((from_index/to_index) * sin((double) axis_slope_angle))) ;
		object_distance = object_distance * ((to_index * cos((double) (-1*rang)))/(from_index * cos((double) axis_slope_angle))) ;
		axis_slope_angle = -1*rang ;
	}
		
	from_index = to_index ;
	if (iter < 4) {
	    conditions[3] = 1;
		object_distance = object_distance - TC_03 ;
	} else {
	    conditions[3] = 0;
	}
	
	iter = iter + 1 ;
	radc = TC_10 ;
	to_index = TC_11 ;
    
	if (to_index > 1.0) {
	    conditions[4] = 1;
		to_index = to_index + ((SPC_4 - SPC_4)/(SPC_3 - SPC_6)) * ((TC_11 - 1.0) / (TC_12)) ;
	} else {
	    conditions[4] = 0;
	}
    
	if (radc >= 0.01 || radc <= -0.01) {
		conditions[5] = 1;
		T iang_sin ;
		if (object_distance == 0) {
		    conditions[6] = 1;
			axis_slope_angle = 0.0 ;
			 iang_sin = ray_height / radc ;
		} else {
		    conditions[6] = 0;
			 iang_sin = ((object_distance - radc) / radc) * sin((double) axis_slope_angle) ;
		}
    
		T iang = asin((double) iang_sin);
		T rang_sin = (from_index / to_index) * iang_sin ;
		T old_axis_slope_angle = axis_slope_angle ;
		axis_slope_angle = axis_slope_angle + iang - asin((double) rang_sin) ;
		T sagitta = sin((double) ((old_axis_slope_angle + iang)/2)) ;
		sagitta = 2 * radc * sagitta * sagitta ;
		object_distance = ((radc * sin((double) (old_axis_slope_angle + iang))) * (1/tan((double) axis_slope_angle))) + sagitta ;
	} else {
	    conditions[5] = 0;
		T rang = -1*asin((double) ((from_index/to_index) * sin((double) axis_slope_angle))) ;
		object_distance = object_distance * ((to_index * cos((double) (-1*rang)))/(from_index * cos((double) axis_slope_angle))) ;
		axis_slope_angle = -1*rang ;
	}

	return axis_slope_angle ;

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
	fp = fopen("ray_tracing_profile.csv", "w+");
    ofstream fp_divergence_inputs;
	fp_divergence_inputs.open("ray_tracing_divergence_inputs.csv", ios::out | ios::app);

    __float80 val_lp = 0;
	__float80 val_dp = 0;
	__float80 val_qp = 0;
	__float80 err_dp_lp = 0;
	__float80 err_qp_dp = 0;

    __float80 maxerrlp = 0.0;
	__float80 maxerrdp = 0.0 ;

    int num_predicates = 7;
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
                string str = "instability_lp:" + to_string_with_precision(fabs(val_dp - val_lp), 16) + ",Pred:" + to_string(j) + ",_TC_00:" + to_string_with_precision(_TC_00, 16) + ",_TC_01:" + to_string_with_precision(_TC_01, 16) + ",_TC_02:" + to_string_with_precision(_TC_02, 16) + ",_TC_03:" + to_string_with_precision(_TC_03, 16) + ",_TC_10:" + to_string_with_precision(_TC_10, 16) + ",_TC_11:" + to_string_with_precision(_TC_11, 16) + ",_TC_12:" + to_string_with_precision(_TC_12, 16) + ",_TC_13:" + to_string_with_precision(_TC_13, 16) + "\n";
                fp_divergence_inputs << str;
                cout << str;
                numinstability_lp[j]++;
                instability_dp_lp[j] += fabs(val_dp - val_lp);
                if ( maxinstabilitylp[j] < fabs(val_dp - val_lp)) maxinstabilitylp[j] = fabs(val_dp - val_lp) ;
            }
            if(conditions_dp[j] != conditions_qp[j] && conditions_dp[j] != -1 && conditions_qp[j] != -1) {
                string str = "instability_dp:" + to_string_with_precision(fabs(val_qp - val_dp), 16) + ",Pred:" + to_string(j) + ",_TC_00:" + to_string_with_precision(_TC_00, 16) + ",_TC_01:" + to_string_with_precision(_TC_01, 16) + ",_TC_02:" + to_string_with_precision(_TC_02, 16) + ",_TC_03:" + to_string_with_precision(_TC_03, 16) + ",_TC_10:" + to_string_with_precision(_TC_10, 16) + ",_TC_11:" + to_string_with_precision(_TC_11, 16) + ",_TC_12:" + to_string_with_precision(_TC_12, 16) + ",_TC_13:" + to_string_with_precision(_TC_13, 16) + "\n";
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
