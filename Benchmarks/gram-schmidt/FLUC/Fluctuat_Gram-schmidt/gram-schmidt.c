#include "daed_builtins.h"

#include "daed_builtins.h"
#include <math.h>

int main(void)
{


	double Q11;
	double Q22;
	double Q12;
	double Q13;
	double Q21;
	double Q23;
	double Q31;
	double Q32;
	double Q33;

	Q11 = DBETWEEN_WITH_ULP(1.0/7.0, 1.0);
	Q22 = DBETWEEN_WITH_ULP(1.0/25.0, 1.0);
	Q12 = 0.0;
	Q13 = 0.0;
	Q21 = 0.0;
	Q23 = 0.0;
	Q31 = DBETWEEN_WITH_ULP(1.0/2592.0, 1.0/2592.0);
	Q32 = DBETWEEN_WITH_ULP(1.0/2601.0, 1.0/2601.0);
	Q33 = DBETWEEN_WITH_ULP(1.0/2583.0, 1.0/2583.0);

	double e_1, e_2, e_3, e_4, e_5, e_6, e_7, e_8, e_9;

	double eps = 0.000005;
	double h1 = 0.0;
	double h2 = 0.0;
	double h3 = 0.0;
	double qj1 = Q31;
	double qj2 = Q32;
	double qj3 = Q33;
	double r1 = 0.0;
	double r2 = 0.0;
	double r3 = 0.0;
	double r = (((qj1 * qj1) + (qj2 * qj2)) + (qj3 * qj3));
	double rjj = 0.0;
	double e = 10.0;
	double rold = sqrt(r);
	double temp = 0.0;


	if (e > eps) {
		double h1_1 = (((Q11 * qj1) + (Q21 * qj2)) + (Q31 * qj3));
		double h2_1 = (((Q12 * qj1) + (Q22 * qj2)) + (Q32 * qj3));
		double h3_1 = (((Q13 * qj1) + (Q23 * qj2)) + (Q33 * qj3));
		double qj1_1 = (qj1 - (((Q11 * h1_1) + (Q12 * h2_1)) + (Q13 * h3_1)));
		double qj2_1 = (qj2 - (((Q21 * h1_1) + (Q22 * h2_1)) + (Q23 * h3_1)));
		double qj3_1 = (qj3 - (((Q31 * h1_1) + (Q32 * h2_1)) + (Q33 * h3_1)));
		double r1_1 = (r1 + h1_1);
		double r2_1 = (r2 + h2_1);
		double r3_1 = (r3 + h3_1);
		double r_1 = (((qj1_1 * qj1_1) + (qj2_1 * qj2_1)) + (qj3_1 * qj3_1));
		double rjj_1 = sqrt(r_1);
		double res1 = (1.0 - (rjj_1 / rold)) ;
		if ( res1 >= 0.0) {
			e_1 = res1 ;
		} else {
			e_1 = -1.0*res1 ;
		}
		double rold_1 = rjj_1;
		double temp_1 = 0.0;
		if (e_1 > eps) {
			double h1_2 = (((Q11 * qj1_1) + (Q21 * qj2_1)) + (Q31 * qj3_1));
			double h2_2 = (((Q12 * qj1_1) + (Q22 * qj2_1)) + (Q32 * qj3_1));
			double h3_2 = (((Q13 * qj1_1) + (Q23 * qj2_1)) + (Q33 * qj3_1));
			double qj1_2 = (qj1_1 - (((Q11 * h1_2) + (Q12 * h2_2)) + (Q13 * h3_2)));
			double qj2_2 = (qj2_1 - (((Q21 * h1_2) + (Q22 * h2_2)) + (Q23 * h3_2)));
			double qj3_2 = (qj3_1 - (((Q31 * h1_2) + (Q32 * h2_2)) + (Q33 * h3_2)));
			double r1_2 = (r1_1 + h1_2);
			double r2_2 = (r2_1 + h2_2);
			double r3_2 = (r3_1 + h3_2);
			double r_2 = (((qj1_2 * qj1_2) + (qj2_2 * qj2_2)) + (qj3_2 * qj3_2));
			double rjj_2 = sqrt(r_2);
			double res2 = ((1.0 - (rjj_2 / rold_1)));
			if ( res2 >= 0.0 ) {
				e_2 = res2 ;
			} else {
				e_2 = -1.0*res2 ;
			}
			double rold_2 = rjj_2;
			double temp_2 = 0.0;
			if (e_2 > eps) {
				double h1_3 = (((Q11 * qj1_2) + (Q21 * qj2_2)) + (Q31 * qj3_2));
				double h2_3 = (((Q12 * qj1_2) + (Q22 * qj2_2)) + (Q32 * qj3_2));
				double h3_3 = (((Q13 * qj1_2) + (Q23 * qj2_2)) + (Q33 * qj3_2));
				double qj1_3 = (qj1_2 - (((Q11 * h1_3) + (Q12 * h2_3)) + (Q13 * h3_3)));
				double qj2_3 = (qj2_2 - (((Q21 * h1_3) + (Q22 * h2_3)) + (Q23 * h3_3)));
				double qj3_3 = (qj3_2 - (((Q31 * h1_3) + (Q32 * h2_3)) + (Q33 * h3_3)));
				double r1_3 = (r1_2 + h1_3);
				double r2_3 = (r2_2 + h2_3);
				double r3_3 = (r3_2 + h3_3);
				double r_3 = (((qj1_3 * qj1_3) + (qj2_3 * qj2_3)) + (qj3_3 * qj3_3));
				double rjj_3 = sqrt(r_3);
				double res3 = ((1.0 - (rjj_3 / rold_2)));
				if ( res3 >= 0.0 ) {
					e_3 = res3 ;
				} else {
					e_3 = -1.0*res3 ;
				}
				double rold_3 = rjj_3;
				double temp_3 = 0.0;
				if (e_3 > eps) {
					double h1_4 = (((Q11 * qj1_3) + (Q21 * qj2_3)) + (Q31 * qj3_3));
					double h2_4 = (((Q12 * qj1_3) + (Q22 * qj2_3)) + (Q32 * qj3_3));
					double h3_4 = (((Q13 * qj1_3) + (Q23 * qj2_3)) + (Q33 * qj3_3));
					double qj1_4 = (qj1_3 - (((Q11 * h1_4) + (Q12 * h2_4)) + (Q13 * h3_4)));
					double qj2_4 = (qj2_3 - (((Q21 * h1_4) + (Q22 * h2_4)) + (Q23 * h3_4)));
					double qj3_4 = (qj3_3 - (((Q31 * h1_4) + (Q32 * h2_4)) + (Q33 * h3_4)));
					double r1_4 = (r1_3 + h1_4);
					double r2_4 = (r2_3 + h2_4);
					double r3_4 = (r3_3 + h3_4);
					double r_4 = (((qj1_4 * qj1_4) + (qj2_4 * qj2_4)) + (qj3_4 * qj3_4));
					double rjj_4 = sqrt(r_4);
					double res4 = (1.0 - (rjj_4 / rold_3));
					if (res4 >= 0.0) {
						e_4 = res4 ;
					} else {
						e_4 = -1.0*res4 ;
					}
					double rold_4 = rjj_4;
					double temp_4 = 0.0;
					if (e_4 > eps) {
						double h1_5 = (((Q11 * qj1_4) + (Q21 * qj2_4)) + (Q31 * qj3_4));
						double h2_5 = (((Q12 * qj1_4) + (Q22 * qj2_4)) + (Q32 * qj3_4));
						double h3_5 = (((Q13 * qj1_4) + (Q23 * qj2_4)) + (Q33 * qj3_4));
						double qj1_5 = (qj1_4 - (((Q11 * h1_5) + (Q12 * h2_5)) + (Q13 * h3_5)));
						double qj2_5 = (qj2_4 - (((Q21 * h1_5) + (Q22 * h2_5)) + (Q23 * h3_5)));
						double qj3_5 = (qj3_4 - (((Q31 * h1_5) + (Q32 * h2_5)) + (Q33 * h3_5)));
						double r1_5 = (r1_4 + h1_5);
						double r2_5 = (r2_4 + h2_5);
						double r3_5 = (r3_4 + h3_5);
						double r_5 = (((qj1_5 * qj1_5) + (qj2_5 * qj2_5)) + (qj3_5 * qj3_5));
						double rjj_5 = sqrt(r_5);
						double res5 = (1.0 - (rjj_5 / rold_4)) ;
						if (res5 >= 0.0) {
							e_5 = res5 ;
						} else {
							e_5 = -1.0*res5 ;
						}
						double rold_5 = rjj_5;
						double temp_5 = 0.0;
						if (e_5 > eps) {
							double h1_6 = (((Q11 * qj1_5) + (Q21 * qj2_5)) + (Q31 * qj3_5));
							double h2_6 = (((Q12 * qj1_5) + (Q22 * qj2_5)) + (Q32 * qj3_5));
							double h3_6 = (((Q13 * qj1_5) + (Q23 * qj2_5)) + (Q33 * qj3_5));
							double qj1_6 = (qj1_5 - (((Q11 * h1_6) + (Q12 * h2_6)) + (Q13 * h3_6)));
							double qj2_6 = (qj2_5 - (((Q21 * h1_6) + (Q22 * h2_6)) + (Q23 * h3_6)));
							double qj3_6 = (qj3_5 - (((Q31 * h1_6) + (Q32 * h2_6)) + (Q33 * h3_6)));
							double r1_6 = (r1_5 + h1_6);
							double r2_6 = (r2_5 + h2_6);
							double r3_6 = (r3_5 + h3_6);
							double r_6 = (((qj1_6 * qj1_6) + (qj2_6 * qj2_6)) + (qj3_6 * qj3_6));
							double rjj_6 = sqrt(r_6);
							double res6 = (1.0 - (rjj_6 / rold_5));
							if ( res6 >= 0.0) {
								e_6 = res6 ;
							} else {
								e_6 = -1.0*res6 ;
							}
							double rold_6 = rjj_6;
							double temp_6 = qj1_6 ;
							if ((e_6 > eps)) {
								double h1_7 = (((Q11 * qj1_6) + (Q21 * qj2_6)) + (Q31 * qj3_6));
								double h2_7 = (((Q12 * qj1_6) + (Q22 * qj2_6)) + (Q32 * qj3_6));
								double h3_7 = (((Q13 * qj1_6) + (Q23 * qj2_6)) + (Q33 * qj3_6));
								double qj1_7 = (qj1_6 - (((Q11 * h1_7) + (Q12 * h2_7)) + (Q13 * h3_7)));
								double qj2_7 = (qj2_6 - (((Q21 * h1_7) + (Q22 * h2_7)) + (Q23 * h3_7)));
								double qj3_7 = (qj3_6 - (((Q31 * h1_7) + (Q32 * h2_7)) + (Q33 * h3_7)));
								double r1_7 = (r1_6 + h1_7);
								double r2_7 = (r2_6 + h2_7);
								double r3_7 = (r3_6 + h3_7);
								double r_7 = (((qj1_7 * qj1_7) + (qj2_7 * qj2_7)) + (qj3_7 * qj3_7));
								double rjj_7 = sqrt(r_7);
								double res7 = (1.0 - (rjj_7 / rold_6));
								if ( res7 >= 0.0 ) {
									e_7 = res7 ;
								} else {
									e_7 = -1.0*res7 ;
								}
								double rold_7 = rjj_7;
								double temp_7=  qj1_7;
								if (e_7 > eps) {
									double h1_8 = (((Q11 * qj1_7) + (Q21 * qj2_7)) + (Q31 * qj3_7));
									double h2_8 = (((Q12 * qj1_7) + (Q22 * qj2_7)) + (Q32 * qj3_7));
									double h3_8 = (((Q13 * qj1_7) + (Q23 * qj2_7)) + (Q33 * qj3_7));
									double qj1_8 = (qj1_7 - (((Q11 * h1_8) + (Q12 * h2_8)) + (Q13 * h3_8)));
									double qj2_8 = (qj2_7 - (((Q21 * h1_8) + (Q22 * h2_8)) + (Q23 * h3_8)));
									double qj3_8 = (qj3_7 - (((Q31 * h1_8) + (Q32 * h2_8)) + (Q33 * h3_8)));
									double r1_8 = (r1_7 + h1_8);
									double r2_8 = (r2_7 + h2_8);
									double r3_8 = (r3_7 + h3_8);
									double r_8 = (((qj1_8 * qj1_8) + (qj2_8 * qj2_8)) + (qj3_8 * qj3_8));
									double rjj_8 = sqrt(r_8);
									double res8 = (1.0 - (rjj_8 / rold_7));
									if ( res8 >= 0.0) {
										e_8 = res8 ;
									} else {
										e_8 = -1.0*res8 ;
									}
									double rold_8 = rjj_8;
									double temp_8 = qj1_8;
									if (e_8 > eps) {
										double h1_9 = (((Q11 * qj1_8) + (Q21 * qj2_8)) + (Q31 * qj3_8));
										double h2_9 = (((Q12 * qj1_8) + (Q22 * qj2_8)) + (Q32 * qj3_8));
										double h3_9 = (((Q13 * qj1_8) + (Q23 * qj2_8)) + (Q33 * qj3_8));
										double qj1_9 = (qj1_8 - (((Q11 * h1_9) + (Q12 * h2_9)) + (Q13 * h3_9)));
										double qj2_9 = (qj2_8 - (((Q21 * h1_9) + (Q22 * h2_9)) + (Q23 * h3_9)));
										double qj3_9 = (qj3_8 - (((Q31 * h1_9) + (Q32 * h2_9)) + (Q33 * h3_9)));
										double r1_9 = (r1_8 + h1_9);
										double r2_9 = (r2_8 + h2_9);
										double r3_9 = (r3_8 + h3_9);
										double r_9 = (((qj1_9 * qj1_9) + (qj2_9 * qj2_9)) + (qj3_9 * qj3_9));
										double rjj_9 = sqrt(r_9);
										double res9 = (1.0 - (rjj_9 / rold_8));
										if ( res9 >= 0.0 ) {
											e_9 = res9 ;
										} else {
											e_9 = -1.0*res9 ;
										}
										double rold_9 = rjj_9;
										double temp_9 = qj1_9;
										if (e_9 > eps) {
											double h1_10 = (((Q11 * qj1_9) + (Q21 * qj2_9)) + (Q31 * qj3_9));
											double h2_10 = (((Q12 * qj1_9) + (Q22 * qj2_9)) + (Q32 * qj3_9));
											double h3_10 = (((Q13 * qj1_9) + (Q23 * qj2_9)) + (Q33 * qj3_9));
											double qj1_10 = (qj1_9 - (((Q11 * h1_9) + (Q12 * h2_9)) + (Q13 * h3_9)));
											double qj2_10 = (qj2_9 - (((Q21 * h1_9) + (Q22 * h2_9)) + (Q23 * h3_9)));
											double qj3_10 = (qj3_9 - (((Q31 * h1_9) + (Q32 * h2_9)) + (Q33 * h3_9)));
											double r1_10 = (r1_9 + h1_9);
											double r2_10 = (r2_9 + h2_9);
											double r3_10 = (r3_9 + h3_9);
											double r_10 = (((qj1_9 * qj1_9) + (qj2_9 * qj2_9)) + (qj3_9 * qj3_9));
											double temp_9 = qj1_10;
										} else {
											temp_9 = qj1_9;
										}
										temp_8 = temp_9;
									} else {
										temp_8 = qj1_8;
									}
									temp_7 = temp_8;
								} else {
									temp_7 = qj1_7;
								}
								temp_6 = temp_7;
							} else {
								temp_6 = qj1_6;
							}
							temp_5 = temp_6;
						 } else {
							temp_5 = qj1_5;
						}
						temp_4 = temp_5;
					 } else {
						temp_4 = qj1_4;
					}
					temp_3 = temp_4;
				 } else {
					temp_3 = qj1_3;
				}
				temp_2 = temp_3;
			 } else {
				temp_2 = qj1_2;
			}
			temp_1 = temp_2;
		 } else {
			temp_1 = qj1_1;
		}
		temp = temp_1;
	 } else {
		temp = qj1;
	}

 DSENSITIVITY(temp);

}
