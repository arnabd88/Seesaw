
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>
#include <fstream>
#include <sstream>

#define dirx_low  (-3.0-0.1)
#define dirx_high (3.0+0.1)
#define diry_low  (4.0-0.1)
#define diry_high (4.0+0.1)
#define dirz_low  (4.0-0.1)
#define dirz_high (4.0+0.1)
#define px0_low  1.0
#define px0_high 2.0
#define py0_low  1.0
#define py0_high 2.0
#define pz0_low  1.0
#define pz0_high 2.0
#define px1_low  2.5
#define px1_high 3.0
#define py1_low  2.5
#define py1_high 3.0
#define pz1_low  2.5
#define pz1_high 3.0
#define px2_low  2.5
#define px2_high 3.0
#define py2_low  2.5
#define py2_high 3.0
#define pz2_low  2.5
#define pz2_high 3.0
#define px3_low  3.2
#define px3_high 4.5
#define py3_low  3.2
#define py3_high 4.5
#define pz3_low  3.2
#define pz3_high 4.5
#define px4_low  0.1
#define px4_high 0.5
#define py4_low  0.1
#define py4_high 0.5
#define pz4_low  0.1
#define pz4_high 0.5
#define px5_low  9.1
#define px5_high 10.5
#define py5_low  9.1
#define py5_high 10.5
#define pz5_low  9.1
#define pz5_high 10.5

using namespace std ;

 double _dirx ;
 double _diry ;
 double _dirz ;
 double _px0  ;
 double _py0  ;
 double _pz0  ;
 double _px1  ;
 double _py1  ;
 double _pz1  ;
 double _px2  ;
 double _py2  ;
 double _pz2  ;
 double _px3  ;
 double _py3  ;
 double _pz3  ;
 double _px4  ;
 double _py4  ;
 double _pz4  ;
 double _px5  ;
 double _py5  ;
 double _pz5  ;


template<class T>
void init() {

	_dirx	=	dirx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(dirx_high - dirx_low))) ;
	_diry	=	dirx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(diry_high - diry_low))) ;
	_dirz	=	dirx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(dirz_high - dirz_low))) ;
	_px0	=	px0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(px0_high - px0_low))) ;
	_py0	=	py0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(py0_high - py0_low))) ;
	_pz0	=	pz0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pz0_high - pz0_low))) ;
	_px1	=	px1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(px1_high - px1_low))) ;
	_py1	=	py1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(py1_high - py1_low))) ;
	_pz1	=	pz1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pz1_high - pz1_low))) ;
	_px2	=	px2_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(px2_high - px2_low))) ;
	_py2	=	py2_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(py2_high - py2_low))) ;
	_pz2	=	pz2_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pz2_high - pz2_low))) ;
	_px3	=	px3_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(px3_high - px3_low))) ;
	_py3	=	py3_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(py3_high - py3_low))) ;
	_pz3	=	pz3_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pz3_high - pz3_low))) ;
	_px4	=	px4_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(px4_high - px4_low))) ;
	_py4	=	py4_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(py4_high - py4_low))) ;
	_pz4	=	pz4_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pz4_high - pz4_low))) ;
	_px5	=	px5_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(px5_high - px5_low))) ;
	_py5	=	py5_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(py5_high - py5_low))) ;
	_pz5	=	pz5_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pz5_high - pz5_low))) ;

}


template<class T>
T execute_spec_precision (int conditions[])
{

 T	dirx 	=	(T)	_dirx;
 T	diry 	=	(T)	_diry;
 T	dirz 	=	(T)	_dirz;
 T	px0  	=	(T)	_px0 ;
 T	py0  	=	(T)	_py0 ;
 T	pz0  	=	(T)	_pz0 ;
 T	px1  	=	(T)	_px1 ;
 T	py1  	=	(T)	_py1 ;
 T	pz1  	=	(T)	_pz1 ;
 T	px2  	=	(T)	_px1 ;
 T	py2  	=	(T)	_py1 ;
 T	pz2  	=	(T)	_pz1 ;
 T	px3  	=	(T)	_px3 ;
 T	py3  	=	(T)	_py3 ;
 T	pz3  	=	(T)	_pz3 ;
 T	px4  	=	(T)	_px4 ;
 T	py4  	=	(T)	_py4 ;
 T	pz4  	=	(T)	_pz4 ;
 T	px5  	=	(T)	_px5 ;
 T	py5  	=	(T)	_py5 ;
 T	pz5  	=	(T)	_pz5 ;

 T maxproj = 2.2250738585072014e-308 ;
 T minproj = 1.7976931348623158e+308 ;

 	T proj = (px0 * dirx) + (py0 * diry) + (pz0 * dirz) ;
	if ( proj < minproj ) {
	    conditions[0] = 1;
		minproj = proj ;
	} else {
	    conditions[0] = 0;
	}
	if ( proj > maxproj ) {
	    conditions[1] = 1;
		maxproj = proj ;
	} else {
	    conditions[1] = 0;
	}

	//
	proj = (px1 * dirx) + (py1 * diry) + (pz1 * dirz) ;
	if ( proj < minproj ) {
	    conditions[2] = 1;
		minproj = proj ;
	} else {
	    conditions[2] = 0;
	}
	if ( proj > maxproj ) {
	    conditions[3] = 1;
		maxproj = proj ;
	} else {
	    conditions[3] = 0;
	}


	//
	proj = (px2 * dirx) + (py2 * diry) + (pz2 * dirz) ;

	if ( proj < minproj ) {
	    conditions[4] = 1;
		minproj = proj ;
	} else {
	    conditions[4] = 0;
	}
	if ( proj > maxproj ) {
	    conditions[5] = 1;
		maxproj = proj ;
	} else {
	    conditions[5] = 0;
	}


	//
	proj = (px3 * dirx) + (py3 * diry) + (pz3 * dirz) ;

	if ( proj < minproj ) {
	    conditions[6] = 1;
		minproj = proj ;
	} else {
	    conditions[6] = 0;
	}
	if ( proj > maxproj ) {
	    conditions[7] = 1;
		maxproj = proj ;
	} else {
	    conditions[7] = 0;
	}


	//
	proj = (px4 * dirx) + (py4 * diry) + (pz4 * dirz) ;

	if ( proj < minproj ) {
	    conditions[8] = 1;
		minproj = proj ;
	} else {
	    conditions[8] = 0;
	}
	if ( proj > maxproj ) {
	    conditions[9] = 1;
		maxproj = proj ;
	} else {
	    conditions[9] = 0;
	}

	//
	proj = (px5 * dirx) + (py5 * diry) + (pz5 * dirz) ;

	if ( proj < minproj ) {
	    conditions[10] = 1;
		minproj = proj ;
	} else {
	    conditions[10] = 0;
	}
	if ( proj > maxproj ) {
	    conditions[11] = 1;
		maxproj = proj ;
	} else {
	    conditions[11] = 0;
	}

	return minproj ;

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
	fp = fopen("extremepointsalongdirection_profile.csv", "w+");
	ofstream fp_divergence_inputs;
	fp_divergence_inputs.open("extremepointsalongdirection_divergence_inputs.csv", ios::out | ios::app);

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
                string str = "instability_lp:" + to_string_with_precision(fabs(val_dp - val_lp), 16) + ",Pred:" + to_string(j) + ",_dirx:" + to_string_with_precision(_dirx, 16) + ",_diry:" + to_string_with_precision(_diry, 16) + ",_dirz:" + to_string_with_precision(_dirz, 16) + ",_px0:" + to_string_with_precision(_px0, 16) + ",_py0:" + to_string_with_precision(_py0, 16) + ",_pz0:" + to_string_with_precision(_pz0, 16) + ",_px1:" + to_string_with_precision(_px1, 16) + ",_py1:" + to_string_with_precision(_py1, 16) + ",_pz1:" + to_string_with_precision(_pz1, 16) + ",_px2:" + to_string_with_precision(_px2, 16) + ",_py2:" + to_string_with_precision(_py2, 16) +  ",_pz2:" + to_string_with_precision(_pz2, 16) + ",_px3:" + to_string_with_precision(_px3, 16) + ",_py3:" + to_string_with_precision(_py3, 16) + ",_pz3:" + to_string_with_precision(_pz3, 16) + ",_px4:" + to_string_with_precision(_px4, 16) + ",_py4:" + to_string_with_precision(_py4, 16) + ",_pz4:" + to_string_with_precision(_pz4, 16) + ",_px5:" + to_string_with_precision(_px5, 16) + ",_py5:" + to_string_with_precision(_py5, 16) + ",_pz5:" + to_string_with_precision(_pz5, 16) + "\n";
                fp_divergence_inputs << str;
                cout << str;
                numinstability_lp[j]++;
                instability_dp_lp[j] += fabs(val_dp - val_lp);
                if ( maxinstabilitylp[j] < fabs(val_dp - val_lp)) maxinstabilitylp[j] = fabs(val_dp - val_lp) ;
            }
            if(conditions_dp[j] != conditions_qp[j] && conditions_dp[j] != -1 && conditions_qp[j] != -1) {
                string str = "instability_dp:" + to_string_with_precision(fabs(val_qp - val_dp), 16) + ",Pred:" + to_string(j) + ",_dirx:" + to_string_with_precision(_dirx, 16) + ",_diry:" + to_string_with_precision(_diry, 16) + ",_dirz:" + to_string_with_precision(_dirz, 16) + ",_px0:" + to_string_with_precision(_px0, 16) + ",_py0:" + to_string_with_precision(_py0, 16) + ",_pz0:" + to_string_with_precision(_pz0, 16) + ",_px1:" + to_string_with_precision(_px1, 16) + ",_py1:" + to_string_with_precision(_py1, 16) + ",_pz1:" + to_string_with_precision(_pz1, 16) + ",_px2:" + to_string_with_precision(_px2, 16) + ",_py2:" + to_string_with_precision(_py2, 16) +  ",_pz2:" + to_string_with_precision(_pz2, 16) + ",_px3:" + to_string_with_precision(_px3, 16) + ",_py3:" + to_string_with_precision(_py3, 16) + ",_pz3:" + to_string_with_precision(_pz3, 16) + ",_px4:" + to_string_with_precision(_px4, 16) + ",_py4:" + to_string_with_precision(_py4, 16) + ",_pz4:" + to_string_with_precision(_pz4, 16) + ",_px5:" + to_string_with_precision(_px5, 16) + ",_py5:" + to_string_with_precision(_py5, 16) + ",_pz5:" + to_string_with_precision(_pz5, 16) + "\n";
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
