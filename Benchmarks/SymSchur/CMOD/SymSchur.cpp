
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>


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
T execute_spec_precision()
{

  T	a_p_p =	(T) _a_p_p;
  T	a_p_q =	(T) _a_p_q;
  T	a_q_q =	(T) _a_q_q;

  T c, s ;
  	
	if (( a_p_q > 0 && a_p_q > 0.0001 ) || ( a_p_q < 0 && -1*a_p_q > 0.0001)) {
		
		T r = (a_q_q - a_p_p) / (2.0 * a_p_q) ;
		T t ;
		if ( r >= 0.0 ) {
			t = 1.0 / ( r + sqrt((double) (1.0 + r*r)));
		} else {
			t = -1*(1.0 / (sqrt((double) ((1.0 + r*r) - r))));
		}

		c = 1.0 / (sqrt((double) (1.0 + t*t))) ;
		s = t * c ;
	} else {
		c = 1.0 ;
		s = 0.0 ;
	}

	return c ;

}





int main(int argc, char** argv)

{

	srand(time(0));

	FILE *fp ;
	int N;
	sscanf(argv[1], "%d", &N);
	fp = fopen("SymSchurr_profile.csv", "w+");

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
