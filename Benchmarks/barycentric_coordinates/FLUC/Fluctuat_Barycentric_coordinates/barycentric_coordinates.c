#include "daed_builtins.h"

#include "daed_builtins.h"



int main(void)
{

	double ax;
	double ay;
	double az;
	double bx;
	double by;
	double bz;
	double cx;
	double cy;
	double cz;
	double px;
	double py;
	double pz;

	ax = DBETWEEN_WITH_ULP(-4.157, -3.157 );
	ay = DBETWEEN_WITH_ULP(4.93, 5.93 );
	az = DBETWEEN_WITH_ULP(-6.73, -5.73 );
	bx = DBETWEEN_WITH_ULP(7.393, 8.393 );
	by = DBETWEEN_WITH_ULP(-7.17, -6.17 );
	bz = DBETWEEN_WITH_ULP(8.42, 9.42 );
	cx = DBETWEEN_WITH_ULP(3.941, 4.941 );
	cy = DBETWEEN_WITH_ULP(7.84, 8.84 );
	cz = DBETWEEN_WITH_ULP(-3.85, -2.85 );
	px = DBETWEEN_WITH_ULP(1.5, 2.5 );
	py = DBETWEEN_WITH_ULP(2.5, 3.5 );
	pz = DBETWEEN_WITH_ULP(4.5, 5.5 );

	double bax = bx - ax ;
	double bay = by - ay ; 
	double baz = bz - az ;
	double cax = cx - ax ; 
	double cay = cy - ay ; 
	double caz = cz - az ;
	double mx  = bay*caz - baz*cay;
	double my = baz*cax - bax*caz;
	double mz = bax*cay - bay*cax;

	double nu , nv, ood, u, v, w ;

	if(( ((mx >= 0) && (my >= 0) && (mx >= my)) || ((mx < 0) && (my >= 0) && (mx+my <= 0)) || 
	    ((mx >= 0) && (my < 0) && (mx + my >= 0)) || ((mx < 0) && (my < 0) && (mx - my <= 0))
		 ) && ( ((mx >= 0) && (mz >= 0) && (mx >= mz)) || ((mx < 0) && (mz >= 0) && (mx+mz <= 0)) || 
	    ((mx >= 0) && (mz < 0) && (mx + mz >= 0)) || ((mx < 0) && (mz < 0) && (mx - mz <= 0))
		 )) {
		nu = (py-by)*(bz-cz) - (by-cy)*(pz-bz);
		nv = (py-cy)*(cz-az) - (cy-ay)*(pz-cz);
		ood = 1.0/mx ;
	}	else {

		if(( ((my >= 0) && (mx >= 0) && (my >= mx)) || ((my < 0) && (mx >= 0) && (my+mx <= 0)) || 
		    ((my >= 0) && (mx < 0) && (my + mx >= 0)) || ((my < 0) && (mx < 0) && (my - mx <= 0))
			 ) && ( ((my >= 0) && (mz >= 0) && (my >= mz)) || ((my < 0) && (mz >= 0) && (my+mz <= 0)) || 
		    ((my >= 0) && (mz < 0) && (my + mz >= 0)) || ((my < 0) && (mz < 0) && (my - mz <= 0))
			 )) {
			nu = (px - bx)*(bz - cz) - (bx - cx)*(pz-bz);
			nv = (px - cx)*(cz - az) - (cx-ax)*(pz-cz);
			ood = 1.0/(-1.0*my);
		} else {
			nu = (px-bx)*(by-cy) - (bx-cx)*(py-by);
			nv = (px - cx)*(cy-ay) - (cx - ax)*(py - cy);
			ood = 1.0/mz ;			
		}
		
	}

	u = nu * ood ;
	v = nv * ood ;
	w = 1.0 - u - v ;

	DSENSITIVITY(w);

	return 0;

}

