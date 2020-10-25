#include "daed_builtins.h"
#include "daed_builtins.h"
#include <math.h>
int main(void)
{

	double px0 ;
	double py0 ;
	double pz0 ;
	double px1 ;
	double py1 ;
	double pz1 ;
	double px2 ;
	double py2 ;
	double pz2 ;
	double cx0 ;
	double cy0 ;
	double cz0 ;

	 px0	=	DBETWEEN_WITH_ULP(21.759999999999998, 21.78 ) ; 
     py0	=	DBETWEEN_WITH_ULP(21.759999999999998, 21.78 ) ; 
     pz0	=	DBETWEEN_WITH_ULP(19.999, 20.001 ) ; 
     px1	=	DBETWEEN_WITH_ULP(22.017, 22.026999999999997 ) ; 
     py1	=	DBETWEEN_WITH_ULP(20.96, 21.96 ) ; 
     pz1	=	DBETWEEN_WITH_ULP(19.99, 20.01 ) ; 
     px2	=	DBETWEEN_WITH_ULP(20.939999999999998, 21.14 ) ; 
     py2	=	DBETWEEN_WITH_ULP(20.84, 21.24 ) ; 
     pz2	=	DBETWEEN_WITH_ULP(21.99, 22.05 ) ; 
     cx0	=	DBETWEEN_WITH_ULP(20.0, 20.0 ) ; 
     cy0	=	DBETWEEN_WITH_ULP(20.0, 20.0 ) ; 
     cz0	=	DBETWEEN_WITH_ULP(20.0, 20.0 ) ;

	//double dist, newRadius, k;

	double radius = 2.5 ;
	double cx = cx0 ;
	double cy = cy0 ;
	double cz = cz0 ;

	double dx = px0 - cx ;
	double dy = py0 - cy ;
	double dz = pz0 - cz ;

	double dist2 = dx*dx + dy*dy + dz*dz ;

	if (dist2 > (radius*radius) ) {
		double dist = sqrt(dist2) ;
		double newRadius = (radius + dist) * 0.5 ;
		double k = (newRadius - radius)/dist ;
		cx = cx + dx*k ;
		cy = cy + dy*k ;
		cz = cz + dz*k ;
		radius = newRadius ;
	}

	dx = px1 - cx ;
	dy = py1 - cy ;
	dz = pz1 - cz ;

	dist2 = dx*dx + dy*dy + dz*dz ;

	if (dist2 > (radius*radius) ) {
		double dist = sqrt((double) dist2) ;
		double newRadius = (radius + dist) * 0.5 ;
		double k = (newRadius - radius)/dist ;
		cx = cx + dx*k ;
		cy = cy + dy*k ;
		cz = cz + dz*k ;
		radius = newRadius ;
	}

	dx = px2 - cx ;
	dy = py2 - cy ;
	dz = pz2 - cz ;

	dist2 = dx*dx + dy*dy + dz*dz ;

	if (dist2 > (radius*radius)) {
		double dist = sqrt((double) dist2) ;
		double newRadius = (radius + dist) * 0.5 ;
		double k = (newRadius - radius)/dist ;
		cx = cx + dx*k ;
		cy = cy + dy*k ; 
		cz = cz + dz*k ;
		radius = newRadius ;
	}

	DSENSITIVITY(radius);

}
