
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>


#define t_low 0.0
#define t_high 1.0
#define k1_low 0.0
#define k1_high 1.0
#define k2_low 0.0
#define k2_high 1.0


using namespace std ;

double _t ;
double _k1 ;
double _k2 ;

template<class T>

void init() {


	_t = t_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(t_high - t_low))) ;
	_k1 = k1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(k1_high - k1_low))) ;
	_k2 = k2_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(k2_high - k2_low))) ;

}


template<class T>
T execute_spec_precision()
{

	T t	=	(T) _t ;
	T k1 =	(T) _k1 ;
	T k2 =	(T) _k2 ;


	T kHalfPI     = 1.570796326794896619231321 ;
	
	T kHalfPIrecip = 1.0/kHalfPI ;

	T f = k1*kHalfPIrecip + k2 - k1 + (1.0 - k2)*kHalfPIrecip;

	T result ;

	if ( t < k1) {
		result = k1*kHalfPIrecip*(sin((double) (t/k1*kHalfPI-kHalfPI)) + 1.0);
	} else {
		if ( t > k2 ) {
			result = k1*kHalfPIrecip + k2 - k1 + (1.0 - k2)*kHalfPIrecip*sin((double) (((t-k2)/(1.0-k2))*kHalfPI));
		} else {
			result = k1*kHalfPIrecip + t - k1;
		}
	}

	return result ;

}



int main(int argc, char** argv)

{

	srand(time(0));

	FILE *fp ;
	int N;
	sscanf(argv[1], "%d", &N);
	fp = fopen("distsinusoid_profile.csv", "w+");

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
