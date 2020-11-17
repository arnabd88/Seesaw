

#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>
#include <fstream>
#include <sstream>

#define _ax_low  -4.0
#define _ax_high -1.0
#define _ay_low  1.0
#define _ay_high 6.0
#define _az_low  -6.0
#define _az_high -4.0
#define _bx_low  7.0
#define _bx_high 10.0
#define _by_low  -7.0
#define _by_high -4.0
#define _bz_low  8.0
#define _bz_high 14.0
#define _cx_low  3.941
#define _cx_high 5.941
#define _cy_low  4.84
#define _cy_high 8.84
#define _cz_low  -9.85
#define _cz_high -2.85
#define _px_low  1.5
#define _px_high 2.5
#define _py_low  2.5
#define _py_high 3.5
#define _pz_low  4.5
#define _pz_high 5.5

using namespace std ;



double _ax ;
double _ay ;
double _az ;
double _bx ;
double _by ;
double _bz ;
double _cx ;
double _cy ;
double _cz ;
double _px ;
double _py ;
double _pz ;

template<class T>
void init() {
	_ax = _ax_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_ax_high - _ax_low))) ;
	_ay = _ay_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_ay_high - _ay_low))) ;
	_az = _az_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_az_high - _az_low))) ;
	_bx = _bx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_bx_high - _bx_low))) ;
	_by = _by_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_by_high - _by_low))) ;
	_bz = _bz_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_bz_high - _bz_low))) ;
	_cx = _cx_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_cx_high - _cx_low))) ;
	_cy = _cy_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_cy_high - _cy_low))) ;
	_cz = _cz_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_cz_high - _cz_low))) ;
	_px = _px_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_px_high - _px_low))) ;
	_py = _py_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_py_high - _py_low))) ;
	_pz = _pz_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_pz_high - _pz_low))) ;
}



template<class T>
T execute_spec_precision(int conditions[])
{

	T ax 	=	(T)	_ax;
	T ay 	=	(T)	_ay;
	T az 	=	(T)	_az;
	T bx 	=	(T)	_bx;
	T by 	=	(T)	_by;
	T bz 	=	(T)	_bz;
	T cx 	=	(T)	_cx;
	T cy 	=	(T)	_cy;
	T cz 	=	(T)	_cz;
	T px 	=	(T)	_px;
	T py 	=	(T)	_py;
	T pz 	=	(T)	_pz;

	// code
	T bax = bx - ax ;
	T bay = by - ay ;
	T baz = bz - az ;
	T cax = cx - ax ;
	T cay = cy - ay ;
	T caz = cz - az ;
	T mx  = bay*caz - baz*cay;
	T my = baz*cax - bax*caz;
	T mz = bax*cay - bay*cax;

	T nu , nv, ood, u, v, w ;

	if(( ((mx >= 0) && (my >= 0) && (mx >= my)) || ((mx < 0) && (my >= 0) && (mx+my <= 0)) ||
	    ((mx >= 0) && (my < 0) && (mx + my >= 0)) || ((mx < 0) && (my < 0) && (mx - my <= 0))
		 ) && ( ((mx >= 0) && (mz >= 0) && (mx >= mz)) || ((mx < 0) && (mz >= 0) && (mx+mz <= 0)) ||
	    ((mx >= 0) && (mz < 0) && (mx + mz >= 0)) || ((mx < 0) && (mz < 0) && (mx - mz <= 0))
		 )) {
		conditions[0] = 1;
		nu = (py-by)*(bz-cz) - (by-cy)*(pz-bz);
		nv = (py-cy)*(cz-az) - (cy-ay)*(pz-cz);
		ood = 1.0/mx ;
	}	else {
        conditions[0] = 0;
		if(( ((my >= 0) && (mx >= 0) && (my >= mx)) || ((my < 0) && (mx >= 0) && (my+mx <= 0)) ||
		    ((my >= 0) && (mx < 0) && (my + mx >= 0)) || ((my < 0) && (mx < 0) && (my - mx <= 0))
			 ) && ( ((my >= 0) && (mz >= 0) && (my >= mz)) || ((my < 0) && (mz >= 0) && (my+mz <= 0)) ||
		    ((my >= 0) && (mz < 0) && (my + mz >= 0)) || ((my < 0) && (mz < 0) && (my - mz <= 0))
			 )) {
			conditions[1] = 1;
			nu = (px - bx)*(bz - cz) - (bx - cx)*(pz-bz);
			nv = (px - cx)*(cz - az) - (cx-ax)*(pz-cz);
			ood = 1.0/(-1.0*my);
		} else {
		    conditions[1] = 0;
			nu = (px-bx)*(by-cy) - (bx-cx)*(py-by);
			nv = (px - cx)*(cy-ay) - (cx - ax)*(py - cy);
			ood = 1.0/mz ;
		}

	}

	u = nu * ood ;
	v = nv * ood ;
	w = 1.0 - u - v ;

	return w ;

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
	fp = fopen("barycentric_ccordinates_profile.csv", "w+");
	ofstream fp_divergence_inputs;
	fp_divergence_inputs.open("barycentric_coordinates_divergence_inputs.csv", ios::out | ios::app);

    __float80 val_lp = 0;
	__float80 val_dp = 0;
	__float80 val_qp = 0;
	__float80 err_dp_lp = 0;
	__float80 err_qp_dp = 0;

    __float80 maxerrlp = 0.0;
	__float80 maxerrdp = 0.0;
	

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
                string str = "instability_lp:" + to_string_with_precision(fabs(val_dp - val_lp), 16) + ",Pred:" + to_string(j) + ",_ax:" + to_string_with_precision(_ax, 16) + ",_ay:" + to_string_with_precision(_ay, 16) + ",_az:" + to_string_with_precision(_az, 16) + ",_bx:" + to_string_with_precision(_bx, 16) + ",_by:" + to_string_with_precision(_by, 16) + ",_bz:" + to_string_with_precision(_bz, 16) + ",_cx:" + to_string_with_precision(_cx, 16) + ",_cy:" + to_string_with_precision(_cy, 16) +  ",_cz:" + to_string_with_precision(_cz, 16) + ",_px:" + to_string_with_precision(_px, 16) + ",_py:" + to_string_with_precision(_py, 16) + ",_pz:" + to_string_with_precision(_pz, 16) + "\n";
                fp_divergence_inputs << str;
                cout << str;
                numinstability_lp[j]++;
                instability_dp_lp[j] += fabs(val_dp - val_lp);
                if ( maxinstabilitylp[j] < fabs(val_dp - val_lp)) maxinstabilitylp[j] = fabs(val_dp - val_lp) ;
            }
            if(conditions_dp[j] != conditions_qp[j] && conditions_dp[j] != -1 && conditions_qp[j] != -1) {
                string str = "instability_dp:" + to_string_with_precision(fabs(val_qp - val_dp), 16) + "Pred:" + to_string(j) + ",_ax:" + to_string_with_precision(_ax, 16) + ",_ay:" + to_string_with_precision(_ay, 16) + ",_az:" + to_string_with_precision(_az, 16) + ",_bx:" + to_string_with_precision(_bx, 16) + ",_by:" + to_string_with_precision(_by, 16) + ",_bz:" + to_string_with_precision(_bz, 16) + ",_cx:" + to_string_with_precision(_cx, 16) + ",_cy:" + to_string_with_precision(_cy, 16) +  ",_cz:" + to_string_with_precision(_cz, 16) + ",_px:" + to_string_with_precision(_px, 16) + ",_py:" + to_string_with_precision(_py, 16) + ",_pz:" + to_string_with_precision(_pz, 16) + "\n";
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
