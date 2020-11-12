#include "daed_builtins.h"
#include <math.h>
#include <assert.h>

int main(void)
{

	
	double t, k1, k2, result ;

	t = DBETWEEN_WITH_ULP(0.0, 1.0);
	k1 = DBETWEEN_WITH_ULP(0.0, 1.0);
	k2 = DBETWEEN_WITH_ULP(0.0, 1.0);


	double kHalfPI     = 1.570796326794896619231321 ;
	
	double kHalfPIrecip = 1.0/kHalfPI ;

	double f = k1*kHalfPIrecip + k2 - k1 + (1.0 - k2)*kHalfPIrecip;

//	if ( k1 > k2) {

	if ( t < k1) {
		result = k1*kHalfPIrecip*(sin( (t/k1*kHalfPI-kHalfPI)) + 1.0);
	} else {
		if ( t > k2 ) {
			result = k1*kHalfPIrecip + k2 - k1 + (1.0 - k2)*kHalfPIrecip*sin( (((t-k2)/(1.0-k2))*kHalfPI));
		} else {
			result = k1*kHalfPIrecip + t - k1;
		}
	}
//}
	

	DSENSITIVITY(result) ;


}
