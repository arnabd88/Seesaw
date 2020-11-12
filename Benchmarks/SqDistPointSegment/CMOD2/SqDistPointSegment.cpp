
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>
#include <fstream>
#include <sstream>

#define bx_low  4.0
#define bx_high 5.0
#define by_low  4.0
#define by_high 5.0
#define bz_low  4.0
#define bz_high 5.0
#define ax_low  0.0
#define ax_high 2.0
#define ay_low  0.0
#define ay_high 2.0
#define az_low  0.0
#define az_high 2.0
#define cx_low  3.0
#define cx_high 7.0
#define cy_low  3.0
#define cy_high 7.0
#define cz_low  3.0
#define cz_high 7.0

using namespace std ;

 double _bx ;
 double _by ;
 double _bz ;
 double _ax ;
 double _ay ;
 double _az ;
 double _cx ;
 double _cy ;
 double _cz ;


template<class T>
void init() {
	_bx = bx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(bx_high - bx_low))) ;
	_by = bx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(by_high - by_low))) ;
	_bz = bx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(bz_high - bz_low))) ;
	_ax = ax_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(ax_high - ax_low))) ;
	_ay = ax_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(ay_high - ay_low))) ;
	_az = ax_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(az_high - az_low))) ;
	_cx = cx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(cx_high - cx_low))) ;
	_cy = cx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(cy_high - cy_low))) ;
	_cz = cx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(cz_high - cz_low))) ;
}

template<class T>
T execute_spec_precision(int conditions[])
{

 T	bx =	(T)	_bx;
 T	by =	(T)	_by;
 T	bz =	(T)	_bz;
 T	ax =	(T)	_ax;
 T	ay =	(T)	_ay;
 T	az =	(T)	_az;
 T	cx =	(T)	_cx;
 T	cy =	(T)	_cy;
 T	cz =	(T)	_cz;

	T abx = bx - ax ;
	T aby = by - ay ;
	T abz = bz - az ;

	T acx = cx - ax ;
	T acy = cy - ay ;
	T acz = cz - az ;

	T bcx = bx - cx ;
	T bcy = by - cy ;
	T bcz = bz - cz ;

	T e = acx*abx + acy*aby + acz*abz ;

	T res = 0.0 ;

	if(e <= 0.0) {
	    conditions[0] = 1;
		res = acx*acx + acy*acy + acz*acz ;
	} else {
	    conditions[0] = 0;
	}

	T f = abx*abx + aby*aby + abz*abz ;
	if(e >= f) {
	    conditions[1] = 1;
		T e2 = acx*acx + acy*acy + acz *acz ;
		res = e2 - ((e*e)/f) ;
	} else {
	    conditions[1] = 0;
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
	fp = fopen("sqdistpointsegment_profile.csv", "w+");
ofstream fp_divergence_inputs;
	fp_divergence_inputs.open("sqdistpointsegment_divergence_inputs.csv", ios::out | ios::app);

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
                string str = "instability_lp:" + to_string_with_precision(fabs(val_dp - val_lp), 16) + ",Pred:" + to_string(j) + ",_ax:" + to_string_with_precision(_ax, 16) + ",_ay:" + to_string_with_precision(_ay, 16) + ",_az:" + to_string_with_precision(_az, 16) + ",_bx:" + to_string_with_precision(_bx, 16) + ",_by:" + to_string_with_precision(_by, 16) + ",_bz:" + to_string_with_precision(_bz, 16) + ",_cx:" + to_string_with_precision(_cx, 16) + ",_cy:" + to_string_with_precision(_cy, 16) +  ",_cz:" + to_string_with_precision(_cz, 16) + "\n";
                fp_divergence_inputs << str;
                cout << str;
                numinstability_lp[j]++;
                instability_dp_lp[j] += fabs(val_dp - val_lp);
                if ( maxinstabilitylp[j] < fabs(val_dp - val_lp)) maxinstabilitylp[j] = fabs(val_dp - val_lp) ;
            }
            if(conditions_dp[j] != conditions_qp[j] && conditions_dp[j] != -1 && conditions_qp[j] != -1) {
                string str = "instability_dp:" + to_string_with_precision(fabs(val_qp - val_dp), 16) + "Pred:" + to_string(j) + ",_ax:" + to_string_with_precision(_ax, 16) + ",_ay:" + to_string_with_precision(_ay, 16) + ",_az:" + to_string_with_precision(_az, 16) + ",_bx:" + to_string_with_precision(_bx, 16) + ",_by:" + to_string_with_precision(_by, 16) + ",_bz:" + to_string_with_precision(_bz, 16) + ",_cx:" + to_string_with_precision(_cx, 16) + ",_cy:" + to_string_with_precision(_cy, 16) +  ",_cz:" + to_string_with_precision(_cz, 16) + "\n";
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
