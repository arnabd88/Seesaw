

#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>


#define _low  0.0
#define _high 100.0


using namespace std ;

double _r_E ;

template<class T>
void init() {
	_r_E = _low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(_high - _low))) ;
}

template<class T>
T execute_spec_precision()
{

	T r_E = _r_E ;
	T res ;

	if ( r_E < ((-703687441776639.0) / 140737488355328.0)) {
		res = r_E * (9.0/4.0) ;
	} else { 
		if (r_E >= (703687441776641.0 / 140737488355328.0)) {
			if (r_E < (3518437208883199.0 / 140737488355328.0)) {
				res = (((r_E - 5.0) * (2476979795053773.0 / 2251799813685248.0)) + (5.0 * (9.0 / 4.0))) ;
			} else {
				if (r_E >= (3518437208883201 / 140737488355328)) {
					res = ((5.0 * (9.0 / 4.0)) + (20.0 * (2476979795053773.0 / 2251799813685248.0))) ;
				} else {
					res = 0 ;
				}
			}
		} else {
			res = 0 ;
		}
	}

	return res ;
}



int main(int argc, char** argv)

{

	srand(time(0));

	FILE *fp ;
	int N;
	sscanf(argv[1], "%d", &N);
	fp = fopen("interpolator_profile.csv", "w+");

	__float80 val_dp = 0;
	__float80 val_qp = 0;
	__float80 err_qp_dp = 0;

	__float80 maxerrdp = 0.0 ;

	for(int i=0; i<N; i++) {
		init<double>();
		__float80 val_dp = (__float80) execute_spec_precision<double>();
		__float80 val_qp = (__float80) execute_spec_precision<__float128>();

		err_qp_dp += fabs(val_qp - val_dp);

		if ( maxerrdp < fabs(val_qp - val_dp)) maxerrdp = fabs(val_qp - val_dp) ;
	}

	fclose(fp);

	cout << "Avg Error in DP -> " << err_qp_dp/N << endl ;
	cout << "Max Error in DP -> " << maxerrdp << endl ;


	return 1;

}
