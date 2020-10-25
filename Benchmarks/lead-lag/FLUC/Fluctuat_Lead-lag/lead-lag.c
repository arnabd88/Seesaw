#include "daed_builtins.h"


#include "daed_builtins.h"

int main(void)
{

	double y;
	double yd;

	y  = DBETWEEN_WITH_ULP(0, 50.0);
	yd = DBETWEEN_WITH_ULP(0, 50.0);

	double e = 1.0 ;
	double eps = 0.01 ;
	double xc0 = 0.0;
	double xc1 = 0.0 ;
	double Cc0 = 564.48 ;
	double Cc1 = 0.0;
	double Dc  = -1280.0;
	double Ac00 = 0.499;
	double Ac01 = -0.05;
	double Ac10 = 0.01;
	double Ac11 = 1.0;
	double Bc0 = 1.0 ;
	double Bc1 = 0.0 ;

	double temp, temp_1, temp_2, temp_3, temp_4, temp_5, temp_6 ;
	double e_1, e_2, e_3, e_4, e_5 ;

	if ( e > eps ) {
		double v = y - yd ;
		temp_1 = 0.0;
		if ( v < -1.0) {
			temp_1 = -1.0;
		} else {
			temp_2 = 0.0;
			if ( v > 1.0) {
				temp_2 = 1.0;
			} else {
				temp_2 = v;
			}
			temp_1 = temp_2 ;
		}
		double yc_1 = temp_1 ;
		double u_1 = ((Cc0 * xc0) + ((Cc1 * xc1) + (Dc * yc_1)));
		double xc0_1 = ((Ac00 * xc0) + ((Ac01 * xc1) + (Bc0 * yc_1)));
		double xc1_1 = ((Ac10 * xc0_1) + ((Ac11 * xc1) + (Bc1 * yc_1)));
		if ( yc_1 - xc1_1 >= 0.0) {
		  e_1 = yc_1 - xc1_1 ;
		} else {
		  e_1 = xc1_1 - yc_1 ;
		}
		temp_3 = 0.0 ;

		if ( e_1 > eps ) {
			double v_1 = y - yd;
			temp_4 = 0.0 ;
			if ( v_1 < -1.0) {
				temp_4 = -1.0 ;
			} else {
				temp_5 = 0.0 ;
				if ( v_1 > 1.0) {
					temp_5 = 1.0;
				} else {
					temp_5 = v_1 ;
				}
				temp_4 = temp_5 ;
			}
			double yc_2 = temp_4 ;
			double u_2 = ((Cc0 * xc0_1) + ((Cc1 * xc1_1) + (Dc * yc_2)));
			double xc0_2 = ((Ac00 * xc0_1) + ((Ac01 * xc1_1) + (Bc0 * yc_2)));
			double xc1_2 = ((Ac10 * xc0_2) + ((Ac11 * xc1_1) + (Bc1 * yc_2)));
			if ( yc_2 - xc1_2 >= 0.0) {
				e_2 = yc_2 - xc1_2 ;
			} else {
				e_2 = xc1_2 - yc_2 ;
			}
			//#temp_6 = 0.0;
			//#if ( e_2 > eps ) {
			//#	v_2 = (y-yd) ;
			//#	temp_7 = 0.0;
			//#	if ( v_2 < -1.0) {
			//#		temp_7 = 01.0;
			//#	} else {
			//#		temp_8 = 0.0;
			//#		if (v_2 > 1.0) {
			//#			temp_8 = 1.0;
			//#		} else {
			//#			temp_8 = v_2 ;
			//#		}
			//#		temp_7 = temp_8;
			//#	}
			//#	yc_3 = temp_7 ;
			//#	u_3 = ((Cc0 * xc0_2) + ((Cc1 * xc1_2) + (Dc * yc_3)));
			//#	xc0_3 = ((Ac00 * xc0_2) + ((Ac01 * xc1_2) + (Bc0 * yc_3)));
			//#	xc1_3 = ((Ac10 * xc0_3) + ((Ac11 * xc1_2) + (Bc1 * yc_3)));
			//#	if ( yc_3 - xc1_3 >= 0.0 ) {
			//#		e_3 = yc_3 - xc1_3 ;
			//#	} else {
			//#		e_3 = xc1_3 - yc_3 ;
			//#	}
			//#	temp_6 = temp_7 ;
			//#} else {
			//#	temp_6 = xc1_2 ;
			//#}
			//#temp_3 = temp_6 ; 
			temp_3 = xc1_2; //#temp_6 ; 
		} else {
			temp_3 = xc1_1 ;
		}
		temp = temp_3 ;
	} else {
		temp = xc1 ;
	}

	DSENSITIVITY(temp);

}
