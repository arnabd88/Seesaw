#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>
#include <fstream>
#include <sstream>

#define Q11_low  (1.0/7.0)
#define Q11_high 1.0
#define Q22_low  (1.0/25.0)
#define Q22_high 1.0
#define Q12_low   0.0
#define Q12_high  0.5
#define Q13_low   0.0
#define Q13_high  0.5
#define Q21_low   0.0
#define Q21_high  0.5
#define Q23_low   0.0
#define Q23_high  0.5
#define Q31_low   (1.0/2592 - 1.0/2592000)
#define Q31_high  (1.0/2592 + 1.0/2592000)
#define Q32_low   (1.0/2601 - 1.0/2601000)
#define Q32_high  (1.0/2601 + 1.0/2601000)
#define Q33_low   (1.0/2583 - 1.0/2583000)
#define Q33_high  (1.0/2583 + 1.0/2583000)


using namespace std ;

 	double _Q11 ; 
 	double _Q12 ; 
 	double _Q13 ; 
 	double _Q21 ; 
 	double _Q22 ; 
 	double _Q23 ; 
 	double _Q31 ; 
 	double _Q32 ; 
 	double _Q33 ; 


template<class T>
void init() {
	_Q11 = Q11_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(Q11_high - Q11_low))) ;
	_Q12 = Q11_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(Q12_high - Q12_low))) ;
	_Q13 = Q11_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(Q13_high - Q13_low))) ;
	_Q21 = Q21_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(Q21_high - Q21_low))) ;
	_Q22 = Q21_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(Q22_high - Q22_low))) ;
	_Q23 = Q21_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(Q23_high - Q23_low))) ;
	_Q31 = Q31_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(Q31_high - Q31_low))) ;
	_Q32 = Q31_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(Q32_high - Q32_low))) ;
	_Q33 = Q31_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(Q33_high - Q33_low))) ;
}

template<class T>
T execute_spec_precision (int conditions[])
{


 	T	Q11 	=	(T)	_Q11; 
 	T	Q12 	=	(T)	_Q12; 
 	T	Q13 	=	(T)	_Q13; 
 	T	Q21 	=	(T)	_Q21; 
 	T	Q22 	=	(T)	_Q22; 
 	T	Q23 	=	(T)	_Q23; 
 	T	Q31 	=	(T)	_Q31; 
 	T	Q32 	=	(T)	_Q32; 
 	T	Q33 	=	(T)	_Q33; 

	T eps = 0.000005;
	T h1 = 0.0;
	T h2 = 0.0;
	T h3 = 0.0;
	T qj1 = Q31;
	T qj2 = Q32;
	T qj3 = Q33;
	T r1 = 0.0;
	T r2 = 0.0;
	T r3 = 0.0;
	T r = (((qj1 * qj1) + (qj2 * qj2)) + (qj3 * qj3));
	T rjj = 0.0;
	T e = 10.0;
	T rold = sqrt((double) r);
	T temp = 0.0;
	if (e > eps) {
	    conditions[0] = 1;
		T h1_1 = (((Q11 * qj1) + (Q21 * qj2)) + (Q31 * qj3));
		T h2_1 = (((Q12 * qj1) + (Q22 * qj2)) + (Q32 * qj3));
		T h3_1 = (((Q13 * qj1) + (Q23 * qj2)) + (Q33 * qj3));
		T qj1_1 = (qj1 - (((Q11 * h1_1) + (Q12 * h2_1)) + (Q13 * h3_1)));
		T qj2_1 = (qj2 - (((Q21 * h1_1) + (Q22 * h2_1)) + (Q23 * h3_1)));
		T qj3_1 = (qj3 - (((Q31 * h1_1) + (Q32 * h2_1)) + (Q33 * h3_1)));
		T r1_1 = (r1 + h1_1);
		T r2_1 = (r2 + h2_1);
		T r3_1 = (r3 + h3_1);
		T r_1 = (((qj1_1 * qj1_1) + (qj2_1 * qj2_1)) + (qj3_1 * qj3_1));
		T rjj_1 = sqrt((double) r_1);
		T res1 = (1.0 - (rjj_1 / rold)) ;
		T e_1 ;
		if ( res1 >= 0.0) {
		    conditions[1] = 1;
			e_1 = res1 ;
		} else {
		    conditions[1] = 0;
			e_1 = -1.0*res1 ;
		}
		T rold_1 = rjj_1;
		T temp_1 = 0.0;
		if (e_1 > eps) {
		    conditions[2] = 1;
			T h1_2 = (((Q11 * qj1_1) + (Q21 * qj2_1)) + (Q31 * qj3_1));
			T h2_2 = (((Q12 * qj1_1) + (Q22 * qj2_1)) + (Q32 * qj3_1));
			T h3_2 = (((Q13 * qj1_1) + (Q23 * qj2_1)) + (Q33 * qj3_1));
			T qj1_2 = (qj1_1 - (((Q11 * h1_2) + (Q12 * h2_2)) + (Q13 * h3_2)));
			T qj2_2 = (qj2_1 - (((Q21 * h1_2) + (Q22 * h2_2)) + (Q23 * h3_2)));
			T qj3_2 = (qj3_1 - (((Q31 * h1_2) + (Q32 * h2_2)) + (Q33 * h3_2)));
			T r1_2 = (r1_1 + h1_2);
			T r2_2 = (r2_1 + h2_2);
			T r3_2 = (r3_1 + h3_2);
			T r_2 = (((qj1_2 * qj1_2) + (qj2_2 * qj2_2)) + (qj3_2 * qj3_2));
			T rjj_2 = sqrt((double) r_2);
			T res2 = ((1.0 - (rjj_2 / rold_1)));
			T e_2 ;
			if ( res2 >= 0.0 ) {
			    conditions[3] = 1;
				e_2 = res2 ;
			} else {
			    conditions[3] = 0;
				e_2 = -1.0*res2 ;
			}
			T rold_2 = rjj_2;
			T temp_2 = 0.0;
			if (e_2 > eps) {
			    conditions[4] = 1;
				T h1_3 = (((Q11 * qj1_2) + (Q21 * qj2_2)) + (Q31 * qj3_2));
				T h2_3 = (((Q12 * qj1_2) + (Q22 * qj2_2)) + (Q32 * qj3_2));
				T h3_3 = (((Q13 * qj1_2) + (Q23 * qj2_2)) + (Q33 * qj3_2));
				T qj1_3 = (qj1_2 - (((Q11 * h1_3) + (Q12 * h2_3)) + (Q13 * h3_3)));
				T qj2_3 = (qj2_2 - (((Q21 * h1_3) + (Q22 * h2_3)) + (Q23 * h3_3)));
				T qj3_3 = (qj3_2 - (((Q31 * h1_3) + (Q32 * h2_3)) + (Q33 * h3_3)));
				T r1_3 = (r1_2 + h1_3);
				T r2_3 = (r2_2 + h2_3);
				T r3_3 = (r3_2 + h3_3);
				T r_3 = (((qj1_3 * qj1_3) + (qj2_3 * qj2_3)) + (qj3_3 * qj3_3));
				T rjj_3 = sqrt((double) r_3);
				T res3 = ((1.0 - (rjj_3 / rold_2)));
				T e_3 ;
				if ( res3 >= 0.0 ) {
				    conditions[5] = 1;
					e_3 = res3 ;
				} else {
				    conditions[5] = 0;
					e_3 = -1.0*res3 ;
				}
				T rold_3 = rjj_3;
				T temp_3 = 0.0;
				if (e_3 > eps) {
				    conditions[6] = 1;
					T h1_4 = (((Q11 * qj1_3) + (Q21 * qj2_3)) + (Q31 * qj3_3));
					T h2_4 = (((Q12 * qj1_3) + (Q22 * qj2_3)) + (Q32 * qj3_3));
					T h3_4 = (((Q13 * qj1_3) + (Q23 * qj2_3)) + (Q33 * qj3_3));
					T qj1_4 = (qj1_3 - (((Q11 * h1_4) + (Q12 * h2_4)) + (Q13 * h3_4)));
					T qj2_4 = (qj2_3 - (((Q21 * h1_4) + (Q22 * h2_4)) + (Q23 * h3_4)));
					T qj3_4 = (qj3_3 - (((Q31 * h1_4) + (Q32 * h2_4)) + (Q33 * h3_4)));
					T r1_4 = (r1_3 + h1_4);
					T r2_4 = (r2_3 + h2_4);
					T r3_4 = (r3_3 + h3_4);
					T r_4 = (((qj1_4 * qj1_4) + (qj2_4 * qj2_4)) + (qj3_4 * qj3_4));
					T rjj_4 = sqrt((double) r_4);
					T e_4 ; //= fabsf((1.0 - (rjj_4 / rold_3)));
					T res4 = (1.0 - (rjj_4 / rold_3));
					if (res4 >= 0.0) {
					    conditions[7] = 1;
						e_4 = res4 ;
					} else {
					    conditions[7] = 0;
						e_4 = -1.0*res4 ;
					}
					T rold_4 = rjj_4;
					T temp_4 = 0.0;
					if (e_4 > eps) {
					    conditions[8] = 1;
						T h1_5 = (((Q11 * qj1_4) + (Q21 * qj2_4)) + (Q31 * qj3_4));
						T h2_5 = (((Q12 * qj1_4) + (Q22 * qj2_4)) + (Q32 * qj3_4));
						T h3_5 = (((Q13 * qj1_4) + (Q23 * qj2_4)) + (Q33 * qj3_4));
						T qj1_5 = (qj1_4 - (((Q11 * h1_5) + (Q12 * h2_5)) + (Q13 * h3_5)));
						T qj2_5 = (qj2_4 - (((Q21 * h1_5) + (Q22 * h2_5)) + (Q23 * h3_5)));
						T qj3_5 = (qj3_4 - (((Q31 * h1_5) + (Q32 * h2_5)) + (Q33 * h3_5)));
						T r1_5 = (r1_4 + h1_5);
						T r2_5 = (r2_4 + h2_5);
						T r3_5 = (r3_4 + h3_5);
						T r_5 = (((qj1_5 * qj1_5) + (qj2_5 * qj2_5)) + (qj3_5 * qj3_5));
						T rjj_5 = sqrt((double) r_5);
						T e_5 ; //= fabsf((1.0 - (rjj_5 / rold_4)));
						T res5 = (1.0 - (rjj_5 / rold_4)) ;
						if (res5 >= 0.0) {
						    conditions[9] = 1;
							e_5 = res5 ;
						} else {
						    conditions[9] = 0;
							e_5 = -1.0*res5 ;
						}
						T rold_5 = rjj_5;
						T temp_5 = 0.0;
						if (e_5 > eps) {
						    conditions[10] = 1;
							T h1_6 = (((Q11 * qj1_5) + (Q21 * qj2_5)) + (Q31 * qj3_5));
							T h2_6 = (((Q12 * qj1_5) + (Q22 * qj2_5)) + (Q32 * qj3_5));
							T h3_6 = (((Q13 * qj1_5) + (Q23 * qj2_5)) + (Q33 * qj3_5));
							T qj1_6 = (qj1_5 - (((Q11 * h1_6) + (Q12 * h2_6)) + (Q13 * h3_6)));
							T qj2_6 = (qj2_5 - (((Q21 * h1_6) + (Q22 * h2_6)) + (Q23 * h3_6)));
							T qj3_6 = (qj3_5 - (((Q31 * h1_6) + (Q32 * h2_6)) + (Q33 * h3_6)));
							T r1_6 = (r1_5 + h1_6);
							T r2_6 = (r2_5 + h2_6);
							T r3_6 = (r3_5 + h3_6);
							T r_6 = (((qj1_6 * qj1_6) + (qj2_6 * qj2_6)) + (qj3_6 * qj3_6));
							T rjj_6 = sqrt((double) r_6);
							T e_6 ; //= fabsf((1.0 - (rjj_6 / rold_5)));
							T res6 = (1.0 - (rjj_6 / rold_5));
							if ( res6 >= 0.0) {
							    conditions[11] = 1;
								e_6 = res6 ;
							} else {
							    conditions[11] = 0;
								e_6 = -1.0*res6 ;
							}
							T rold_6 = rjj_6;
							T temp_6 = qj1_6 ;
							if ((e_6 > eps)) {
							    conditions[12] = 1;
								T h1_7 = (((Q11 * qj1_6) + (Q21 * qj2_6)) + (Q31 * qj3_6));
								T h2_7 = (((Q12 * qj1_6) + (Q22 * qj2_6)) + (Q32 * qj3_6));
								T h3_7 = (((Q13 * qj1_6) + (Q23 * qj2_6)) + (Q33 * qj3_6));
								T qj1_7 = (qj1_6 - (((Q11 * h1_7) + (Q12 * h2_7)) + (Q13 * h3_7)));
								T qj2_7 = (qj2_6 - (((Q21 * h1_7) + (Q22 * h2_7)) + (Q23 * h3_7)));
								T qj3_7 = (qj3_6 - (((Q31 * h1_7) + (Q32 * h2_7)) + (Q33 * h3_7)));
								T r1_7 = (r1_6 + h1_7);
								T r2_7 = (r2_6 + h2_7);
								T r3_7 = (r3_6 + h3_7);
								T r_7 = (((qj1_7 * qj1_7) + (qj2_7 * qj2_7)) + (qj3_7 * qj3_7));
								T rjj_7 = sqrt((double) r_7);
								T e_7 ; //= fabsf((1.0 - (rjj_7 / rold_6)));
								T res7 = (1.0 - (rjj_7 / rold_6));
								if ( res7 >= 0.0 ) {
								    conditions[13] = 1;
									e_7 = res7 ;
								} else {
								    conditions[13] = 0;
									e_7 = -1.0*res7 ;
								}
								T rold_7 = rjj_7;
								T temp_7=  qj1_7;
								if (e_7 > eps) {
								    conditions[14] = 1;
									T h1_8 = (((Q11 * qj1_7) + (Q21 * qj2_7)) + (Q31 * qj3_7));
									T h2_8 = (((Q12 * qj1_7) + (Q22 * qj2_7)) + (Q32 * qj3_7));
									T h3_8 = (((Q13 * qj1_7) + (Q23 * qj2_7)) + (Q33 * qj3_7));
									T qj1_8 = (qj1_7 - (((Q11 * h1_8) + (Q12 * h2_8)) + (Q13 * h3_8)));
									T qj2_8 = (qj2_7 - (((Q21 * h1_8) + (Q22 * h2_8)) + (Q23 * h3_8)));
									T qj3_8 = (qj3_7 - (((Q31 * h1_8) + (Q32 * h2_8)) + (Q33 * h3_8)));
									T r1_8 = (r1_7 + h1_8);
									T r2_8 = (r2_7 + h2_8);
									T r3_8 = (r3_7 + h3_8);
									T r_8 = (((qj1_8 * qj1_8) + (qj2_8 * qj2_8)) + (qj3_8 * qj3_8));
									T rjj_8 = sqrt((double) r_8);
									T e_8 ; //= fabsf((1.0 - (rjj_8 / rold_7)));
									T res8 = (1.0 - (rjj_8 / rold_7));
									if ( res8 >= 0.0) {
									    conditions[15] = 1;
										e_8 = res8 ;
									} else {
									    conditions[15] = 0;
										e_8 = -1.0*res8 ;
									}
									T rold_8 = rjj_8;
									T temp_8 = qj1_8;
									if (e_8 > eps) {
									    conditions[16] = 1;
										T h1_9 = (((Q11 * qj1_8) + (Q21 * qj2_8)) + (Q31 * qj3_8));
										T h2_9 = (((Q12 * qj1_8) + (Q22 * qj2_8)) + (Q32 * qj3_8));
										T h3_9 = (((Q13 * qj1_8) + (Q23 * qj2_8)) + (Q33 * qj3_8));
										T qj1_9 = (qj1_8 - (((Q11 * h1_9) + (Q12 * h2_9)) + (Q13 * h3_9)));
										T qj2_9 = (qj2_8 - (((Q21 * h1_9) + (Q22 * h2_9)) + (Q23 * h3_9)));
										T qj3_9 = (qj3_8 - (((Q31 * h1_9) + (Q32 * h2_9)) + (Q33 * h3_9)));
										T r1_9 = (r1_8 + h1_9);
										T r2_9 = (r2_8 + h2_9);
										T r3_9 = (r3_8 + h3_9);
										T r_9 = (((qj1_9 * qj1_9) + (qj2_9 * qj2_9)) + (qj3_9 * qj3_9));
										T rjj_9 = sqrt((double) r_9);
										T e_9 ; // = fabsf((1.0 - (rjj_9 / rold_8)));
										T res9 = (1.0 - (rjj_9 / rold_8));
										if ( res9 >= 0.0 ) {
										    conditions[17] = 1;
											e_9 = res9 ;
										} else {
										    conditions[17] = 0;
											e_9 = -1.0*res9 ;
										}
										T rold_9 = rjj_9;
										T temp_9 = qj1_9;
										if (e_9 > eps) {
										    conditions[18] = 1;
											T h1_10 = (((Q11 * qj1_9) + (Q21 * qj2_9)) + (Q31 * qj3_9));
											T h2_10 = (((Q12 * qj1_9) + (Q22 * qj2_9)) + (Q32 * qj3_9));
											T h3_10 = (((Q13 * qj1_9) + (Q23 * qj2_9)) + (Q33 * qj3_9));
											T qj1_10 = (qj1_9 - (((Q11 * h1_9) + (Q12 * h2_9)) + (Q13 * h3_9)));
											T qj2_10 = (qj2_9 - (((Q21 * h1_9) + (Q22 * h2_9)) + (Q23 * h3_9)));
											T qj3_10 = (qj3_9 - (((Q31 * h1_9) + (Q32 * h2_9)) + (Q33 * h3_9)));
											T r1_10 = (r1_9 + h1_9);
											T r2_10 = (r2_9 + h2_9);
											T r3_10 = (r3_9 + h3_9);
											T r_10 = (((qj1_9 * qj1_9) + (qj2_9 * qj2_9)) + (qj3_9 * qj3_9));
											T temp_9 = qj1_10;
										} else {
										    conditions[18] = 0;
											temp_9 = qj1_9;
										}
										temp_8 = temp_9;
									} else {
									    conditions[16] = 0;
										temp_8 = qj1_8;
									}
									temp_7 = temp_8;
								} else {
								    conditions[14] = 0;
									temp_7 = qj1_7;
								}
								temp_6 = temp_7;
							} else {
							    conditions[12] = 0;
								temp_6 = qj1_6;
							}
							temp_5 = temp_6;
						 } else {
						    conditions[10] = 0;
							temp_5 = qj1_5;
						}
						temp_4 = temp_5;
					 } else {
					    conditions[8] = 0;
						temp_4 = qj1_4;
					}
					temp_3 = temp_4;
				 } else {
				    conditions[6] = 0;
					temp_3 = qj1_3;
				}
				temp_2 = temp_3;
			 } else {
			    conditions[4] = 0;
				temp_2 = qj1_2;
			}
			temp_1 = temp_2;
		 } else {
		    conditions[2] = 0;
			temp_1 = qj1_1;
		}
		temp = temp_1;
	 } else {
	    conditions[0] = 0;
		temp = qj1;
	}
	return temp;

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
	fp = fopen("gram-schmidt_profile.csv", "w+");
    ofstream fp_divergence_inputs;
	fp_divergence_inputs.open("gram-schmidt_divergence_inputs.csv", ios::out | ios::app);

    __float80 val_lp = 0;
	__float80 val_dp = 0;
	__float80 val_qp = 0;
	__float80 err_dp_lp = 0;
	__float80 err_qp_dp = 0;

    __float80 maxerrlp = 0.0;
	__float80 maxerrdp = 0.0 ;

    int num_predicates = 19;
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
                string str = "instability_lp:" + to_string_with_precision(fabs(val_dp - val_lp), 16) + ",Pred:" + to_string(j) + ",_Q11:" + to_string_with_precision(_Q11, 16) + ",_Q12:" + to_string_with_precision(_Q12, 16) + ",_Q13:" + to_string_with_precision(_Q13, 16) + ",_Q21:" + to_string_with_precision(_Q21, 16) + ",_Q22:" + to_string_with_precision(_Q22, 16) + ",_Q23:" + to_string_with_precision(_Q23, 16) + ",_Q31:" + to_string_with_precision(_Q31, 16) + ",_Q32:" + to_string_with_precision(_Q32, 16) +  ",_Q33:" + to_string_with_precision(_Q33, 16) + "\n";
                fp_divergence_inputs << str;
                cout << str;
                numinstability_lp[j]++;
                instability_dp_lp[j] += fabs(val_dp - val_lp);
                if ( maxinstabilitylp[j] < fabs(val_dp - val_lp)) maxinstabilitylp[j] = fabs(val_dp - val_lp) ;
            }
            if(conditions_dp[j] != conditions_qp[j] && conditions_dp[j] != -1 && conditions_qp[j] != -1) {
                string str = "instability_dp:" + to_string_with_precision(fabs(val_qp - val_dp), 16) + ",Pred:" + to_string(j) + ",_Q11:" + to_string_with_precision(_Q11, 16) + ",_Q12:" + to_string_with_precision(_Q12, 16) + ",_Q13:" + to_string_with_precision(_Q13, 16) + ",_Q21:" + to_string_with_precision(_Q21, 16) + ",_Q22:" + to_string_with_precision(_Q22, 16) + ",_Q23:" + to_string_with_precision(_Q23, 16) + ",_Q31:" + to_string_with_precision(_Q31, 16) + ",_Q32:" + to_string_with_precision(_Q32, 16) +  ",_Q33:" + to_string_with_precision(_Q33, 16) + "\n";
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
