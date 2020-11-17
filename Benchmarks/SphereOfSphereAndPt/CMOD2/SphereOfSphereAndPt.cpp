
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>
#include <fstream>
#include <sstream>


#define px0_low  (21.77 - 0.1)
#define px0_high (21.77 + 0.1)
#define py0_low  (21.77 - 0.1)
#define py0_high (21.77 + 0.1)
#define pz0_low  (20.0 - 0.1)
#define pz0_high (20. + 0.1)
#define px1_low  (22.02 - 0.1)
#define px1_high (22.02 + 0.1)
#define py1_low  (21.46 - 0.1)
#define py1_high (21.46 + 0.1)
#define pz1_low  (20.0 - 0.1)
#define pz1_high (20.0 + 0.1)
#define px2_low  (21.04 - 0.1)
#define px2_high (21.04 + 0.1)
#define py2_low  (21.04 - 0.1)
#define py2_high (21.04 + 0.1)
#define pz2_low  (22.02 - 0.1)
#define pz2_high (22.02 + 0.1)
#define cx0_low  (20.0 - 0.1)
#define cx0_high (20.0 + 0.1)
#define cy0_low  (20.0 - 0.1)
#define cy0_high (20.0 + 0.1)
#define cz0_low  (20.0 - 0.1)
#define cz0_high (20.0 + 0.1)

using namespace std ;

 double _px0 ;
 double _py0 ;
 double _pz0 ;
 double _px1 ;
 double _py1 ;
 double _pz1 ;
 double _px2 ;
 double _py2 ;
 double _pz2 ;
 double _cx0 ;
 double _cy0 ;
 double _cz0 ;


template<class T>
void init() {

	_px0	=	px0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(px0_high - px0_low))) ;
	_py0	=	py0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(py0_high - py0_low))) ;
	_pz0	=	pz0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pz0_high - pz0_low))) ;
	_px1	=	px1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(px1_high - px1_low))) ;
	_py1	=	py1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(py1_high - py1_low))) ;
	_pz1	=	pz1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pz1_high - pz1_low))) ;
	_px2	=	px1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(px2_high - px2_low))) ;
	_py2	=	py1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(py2_high - py2_low))) ;
	_pz2	=	pz1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pz2_high - pz2_low))) ;
	_cx0	=	cx0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(cx0_high - cx0_low))) ;
	_cy0	=	cy0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(cy0_high - cy0_low))) ;
	_cz0	=	cz0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(cz0_high - cz0_low))) ;

}

template<class T>
T execute_spec_precision(int conditions[])
{

 T	 px0 =	(T)	_px0;
 T	 py0 =	(T)	_py0;
 T	 pz0 =	(T)	_pz0;
 T	 px1 =	(T)	_px1;
 T	 py1 =	(T)	_py1;
 T	 pz1 =	(T)	_pz1;
 T	 px2 =	(T)	_px2;
 T	 py2 =	(T)	_py2;
 T	 pz2 =	(T)	_pz2;
 T	 cx0 =	(T)	_cx0;
 T	 cy0 =	(T)	_cy0;
 T	 cz0 =	(T)	_cz0;


 	T radius = 2.5 ;
	T cx = cx0 ;
	T cy = cy0 ;
	T cz = cz0 ;

	T dx = px0 - cx ;
	T dy = py0 - cy ;
	T dz = pz0 - cz ;

	T dist2 = dx*dx + dy*dy + dz*dz ;

	if (dist2 > (radius*radius) ) {
	    conditions[0] = 1;
		T dist = sqrt((double) dist2) ;
		T newRadius = (radius + dist) * 0.5 ;
		T k = (newRadius - radius)/dist ;
		cx = cx + dx*k ;
		cy = cy + dy*k ;
		cz = cz + dz*k ;
		radius = newRadius ;
	} else {
	    conditions[0] = 0;
	}

	dx = px1 - cx ;
	dy = py1 - cy ;
	dz = pz1 - cz ;

	dist2 = dx*dx + dy*dy + dz*dz ;

	if (dist2 > (radius*radius) ) {
	    conditions[1] = 1;
		T dist = sqrt((double) dist2) ;
		T newRadius = (radius + dist) * 0.5 ;
		T k = (newRadius - radius)/dist ;
		cx = cx + dx*k ;
		cy = cy + dy*k ;
		cz = cz + dz*k ;
		radius = newRadius ;
	} else {
	    conditions[1] = 0;
	}

	dx = px2 - cx ;
	dy = py2 - cy ;
	dz = pz2 - cz ;

	dist2 = dx*dx + dy*dy + dz*dz ;

	if (dist2 > (radius*radius)) {
	    conditions[2] = 1;
		T dist = sqrt((double) dist2) ;
		T newRadius = (radius + dist) * 0.5 ;
		T k = (newRadius - radius)/dist ;
		cx = cx + dx*k ;
		cy = cy + dy*k ; 
		cz = cz + dz*k ;
		radius = newRadius ;
	} else {
	    conditions[2] = 0;
	}

	return radius ;

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
	fp = fopen("sphereofsphereandpoint_profile.csv", "w+");
    ofstream fp_divergence_inputs;
	fp_divergence_inputs.open("sphereofsphereandpoint_divergence_inputs.csv", ios::out | ios::app);

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
                string str = "instability_lp:" + to_string_with_precision(fabs(val_dp - val_lp), 16) + ",Pred:" + to_string(j) + ",_px0:" + to_string_with_precision(_px0, 16) + ",_py0:" + to_string_with_precision(_py0, 16) + ",_pz0:" + to_string_with_precision(_pz0, 16) + ",_px1:" + to_string_with_precision(_px1, 16) + ",_py1:" + to_string_with_precision(_py1, 16) + ",_pz1:" + to_string_with_precision(_pz1, 16) + ",_px2:" + to_string_with_precision(_px2, 16) + ",_py2:" + to_string_with_precision(_py2, 16) +  ",_pz2:" + to_string_with_precision(_pz2, 16) + ",_cx0:" + to_string_with_precision(_cx0, 16) + ",_cy0:" + to_string_with_precision(_cy0, 16) + ",_cz0:" + to_string_with_precision(_cz0, 16) + "\n";
                fp_divergence_inputs << str;
                cout << str;
                numinstability_lp[j]++;
                instability_dp_lp[j] += fabs(val_dp - val_lp);
                if ( maxinstabilitylp[j] < fabs(val_dp - val_lp)) maxinstabilitylp[j] = fabs(val_dp - val_lp) ;
            }
            if(conditions_dp[j] != conditions_qp[j] && conditions_dp[j] != -1 && conditions_qp[j] != -1) {
                string str = "instability_dp:" + to_string_with_precision(fabs(val_qp - val_dp), 16) + ",Pred:" + to_string(j) + ",_px0:" + to_string_with_precision(_px0, 16) + ",_py0:" + to_string_with_precision(_py0, 16) + ",_pz0:" + to_string_with_precision(_pz0, 16) + ",_px1:" + to_string_with_precision(_px1, 16) + ",_py1:" + to_string_with_precision(_py1, 16) + ",_pz1:" + to_string_with_precision(_pz1, 16) + ",_px2:" + to_string_with_precision(_px2, 16) + ",_py2:" + to_string_with_precision(_py2, 16) +  ",_pz2:" + to_string_with_precision(_pz2, 16) + ",_cx0:" + to_string_with_precision(_cx0, 16) + ",_cy0:" + to_string_with_precision(_cy0, 16) + ",_cz0:" + to_string_with_precision(_cz0, 16) + "\n";
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
