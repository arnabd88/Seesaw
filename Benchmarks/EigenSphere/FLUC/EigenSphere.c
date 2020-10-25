#include "daed_builtins.h"
#include <math.h>
int main(void)
{
	double err ;
	double px0 ;
	double py0 ;
	double pz0 ;
	double px1 ;
	double py1 ;
	double pz1 ;
	double px2 ;
	double py2 ;
	double pz2 ;
	double px3 ;
	double py3 ;
	double pz3 ;
	double px4 ;
	double py4 ;
	double pz4 ;


 err	=	DBETWEEN_WITH_ULP( -0.1, 0.1) ; 
 px0	=	DBETWEEN_WITH_ULP(1.0 - err, 1.0 + err ) ; 
 py0	=	DBETWEEN_WITH_ULP(1.0 - err, 1.0 + err ) ; 
 pz0	=	DBETWEEN_WITH_ULP(1.0 - err, 1.0 + err ) ; 
 px1	=	DBETWEEN_WITH_ULP(2.5 - err, 2.5 + err ) ; 
 py1	=	DBETWEEN_WITH_ULP(2.5 - err, 2.5 + err ) ; 
 pz1	=	DBETWEEN_WITH_ULP(2.5 - err, 2.5 + err ) ; 
 px2	=	DBETWEEN_WITH_ULP(1.5 - err, 1.5 + err ) ; 
 py2	=	DBETWEEN_WITH_ULP(1.5 - err, 1.5 + err ) ; 
 pz2	=	DBETWEEN_WITH_ULP(1.5 - err, 1.5 + err ) ; 
 px3	=	DBETWEEN_WITH_ULP(3.2 - err, 3.2 + err ) ; 
 py3	=	DBETWEEN_WITH_ULP(3.2 - err, 3.2 + err ) ; 
 pz3	=	DBETWEEN_WITH_ULP(3.2 - err, 3.2 + err ) ; 
 px4	=	DBETWEEN_WITH_ULP(2.1, 2.3 ) ; 
 py4	=	DBETWEEN_WITH_ULP(2.1, 2.3 ) ; 
 pz4	=	DBETWEEN_WITH_ULP(2.1, 2.3 ) ;




	int numPts = 5 ; double eigen_radius ;
	double cx = (px0 + px1 + px2 + px3 + px4)/numPts ;
	double cy = (py0 + py1 + py2 + py3 + py4)/numPts ;
	double cz = (pz0 + pz1 + pz2 + pz3 + pz4)/numPts ;
	double e00 = 0.0 ; double e11 = 0.0 ; double e22 = 0.0 ; double e01 = 0.0 ; double e02 = 0.0 ; double e12 = 0.0 ;

	double px = px0 - cx ;
	double py = py0 - cy ;
	double pz = pz0 - cz ;
	e00 = e00 + px*px ;
	e11 = e11 + py*py ;
	e22 = e22 + pz*pz ;
	e01 = e01 + px*py ;
	e02 = e02 + px*pz ;
	e12 = e12 + py*pz ;

	px = px1 - cx ;
	py = py1 - cy ;
	pz = pz1 - cz ;
	e00 = e00 + px*px ;
	e11 = e11 + py*py ;
	e22 = e22 + pz*pz ;
	e01 = e01 + px*py ;
	e02 = e02 + px*pz ;
	e12 = e12 + py*pz ;

	px = px2 - cx ;
	py = py2 - cy ;
	pz = pz2 - cz ;
	e00 = e00 + px*px ;
	e11 = e11 + py*py ;
	e22 = e22 + pz*pz ;
	e01 = e01 + px*py ;
	e02 = e02 + px*pz ;
	e12 = e12 + py*pz ;

	px = px3 - cx ;
	py = py3 - cy ;
	pz = pz3 - cz ;
	e00 = e00 + px*px ;
	e11 = e11 + py*py ;
	e22 = e22 + pz*pz ;
	e01 = e01 + px*py ;
	e02 = e02 + px*pz ;
	e12 = e12 + py*pz ;

	px = px4 - cx ;
	py = py4 - cy ;
	pz = pz4 - cz ;
	e00 = e00 + px*px ;
	e11 = e11 + py*py ;
	e22 = e22 + pz*pz ;
	e01 = e01 + px*py ;
	e02 = e02 + px*pz ;
	e12 = e12 + py*pz ;

	double	m_0_0 = e00 / numPts ;
	double	m_1_1 = e11 / numPts ;
	double	m_2_2 = e22 / numPts ;
	double	m_0_1 = e01 / numPts ;
	double	m_1_0 = e01 / numPts ;
	double	m_0_2 = e02 / numPts ;
	double	m_2_0 = e02 / numPts ;
	double	m_1_2 = e12 / numPts ;
	double	m_2_1 = e12 / numPts ;

	double	v_0_0 = 1.0;
	double	v_0_1 = 0.0;
	double	v_0_2 = 0.0;
	double	v_1_0 = 0.0;
	double	v_1_1 = 1.0;
	double	v_1_2 = 0.0;
	double	v_2_0 = 0.0;
	double	v_2_1 = 0.0;
	double	v_2_2 = 1.0;

	double t, c, s ;

	if (( m_1_2 > 0 && m_1_2 > 0.0001 ) || ( m_1_2 < 0 && -1*m_1_2 > 0.0001))  {
		
		double r = (m_2_2 - m_1_1) / (2.0 * m_1_2) ;

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

	double	J_0_0 = 1.0;
	double	J_0_1 = 0.0;
	double	J_0_2 = 0.0;
	double	J_1_0 = 0.0;
	double	J_1_1 = 1.0;
	double	J_1_2 = 0.0;
	double	J_2_0 = 0.0;
	double	J_2_1 = 0.0;
	double	J_2_2 = 1.0;

	J_1_1 = c ;
	J_1_2 = s ;
	J_2_1 = -1*s ;
	J_2_2 = c ;

	// vl = v * J
	v_0_0 = v_0_0 * J_0_0 + v_0_1 * J_1_0 + v_0_2 * J_2_0 ;
	v_0_1 = v_0_0 * J_0_1 + v_0_1 * J_1_1 + v_0_2 * J_2_1 ;
	v_0_2 = v_0_0 * J_0_2 + v_0_1 * J_1_2 + v_0_2 * J_2_2 ;
	v_1_0 = v_1_0 * J_0_0 + v_1_1 * J_1_0 + v_1_2 * J_2_0 ;
	v_1_1 = v_1_0 * J_0_1 + v_1_1 * J_1_1 + v_1_2 * J_2_1 ;
	v_1_2 = v_1_0 * J_0_2 + v_1_1 * J_1_2 + v_1_2 * J_2_2 ;
	v_2_0 = v_2_0 * J_0_0 + v_2_1 * J_1_0 + v_2_2 * J_2_0 ;
	v_2_1 = v_2_0 * J_0_1 + v_2_1 * J_1_1 + v_2_2 * J_2_1 ;
	v_2_2 = v_2_0 * J_0_2 + v_2_1 * J_1_2 + v_2_2 * J_2_2 ;

	double	jtm_0_0 = J_0_0 * m_0_0 + J_1_0 * m_1_0 + J_2_0 * m_2_0 ;
	double	jtm_0_1 = J_0_0 * m_0_1 + J_1_0 * m_1_1 + J_2_0 * m_2_1 ;
	double	jtm_0_2 = J_0_0 * m_0_2 + J_1_0 * m_1_2 + J_2_0 * m_2_2 ;
	double	jtm_1_0 = J_0_1 * m_0_0 + J_1_1 * m_1_0 + J_2_1 * m_2_0 ;
	double	jtm_1_1 = J_0_1 * m_0_1 + J_1_1 * m_1_1 + J_2_1 * m_2_1 ;
	double	jtm_1_2 = J_0_1 * m_0_2 + J_1_1 * m_1_2 + J_2_1 * m_2_2 ;
	double	jtm_2_0 = J_0_2 * m_0_0 + J_1_2 * m_1_0 + J_2_2 * m_2_0 ;
	double	jtm_2_1 = J_0_2 * m_0_1 + J_1_2 * m_1_1 + J_2_2 * m_2_1 ;
	double	jtm_2_2 = J_0_2 * m_0_2 + J_1_2 * m_1_2 + J_2_2 * m_2_2 ;

	m_0_0 = jtm_0_0 * J_0_0 + jtm_0_1 * J_1_0 + jtm_0_2 * J_2_0 ;
	m_0_1 = jtm_0_0 * J_0_1 + jtm_0_1 * J_1_1 + jtm_0_2 * J_2_1 ;
	m_0_2 = jtm_0_0 * J_0_2 + jtm_0_1 * J_1_2 + jtm_0_2 * J_2_2 ;
	m_1_0 = jtm_1_0 * J_0_0 + jtm_1_1 * J_1_0 + jtm_1_2 * J_2_0 ;
	m_1_1 = jtm_1_0 * J_0_1 + jtm_1_1 * J_1_1 + jtm_1_2 * J_2_1 ;
	m_1_2 = jtm_1_0 * J_0_2 + jtm_1_1 * J_1_2 + jtm_1_2 * J_2_2 ;
	m_2_0 = jtm_2_0 * J_0_0 + jtm_2_1 * J_1_0 + jtm_2_2 * J_2_0 ;
	m_2_1 = jtm_2_0 * J_0_1 + jtm_2_1 * J_1_1 + jtm_2_2 * J_2_1 ;
	m_2_2 = jtm_2_0 * J_0_2 + jtm_2_1 * J_1_2 + jtm_2_2 * J_2_2 ;

	double	off = m_0_1 * m_0_1 + m_0_2 * m_0_2 + m_1_0 * m_1_0 + m_1_2 * m_1_2 + m_2_0 * m_2_0 + m_2_1 * m_2_1 ;

	double maxf_0, maxf_1, maxf_2 ;
	double maxe_0, maxe_1, maxe_2 ;

	if ( m_0_0 >= 0.0 ) {
		maxf_0 = m_0_0 ; maxe_0 = m_0_0 ;
	} else {
		maxf_0 = -1.0*m_0_0; maxe_0 = -1.0*m_0_0;
	}

	if ( m_1_1 >= 0.0 ) {
		maxf_1 = m_1_1 ; maxe_1 = m_1_1 ;
	} else {
		maxf_1 = -1.0*m_1_1; maxe_1 = -1.0*m_1_1;
	}

	if ( m_2_2 >= 0.0 ) {
		maxf_2 = m_2_2 ; maxe_2 = m_2_2 ;
	} else {
		maxf_2 = -1.0*m_2_2; maxe_2 = -1.0*m_2_2;
	}

	double e_0, e_1, e_2 ;

	if ( maxf_1 > maxe_0 ) {
		e_0 = v_0_1 ;
		e_1 = v_1_1 ;
		e_2 = v_2_1 ;
	} else {
		if ( maxf_2 > m_0_0 ) {
			e_0 = v_0_2 ;
			e_1 = v_1_2 ;
			e_2 = v_2_2 ;
		} else {
			e_0 = v_0_0 ;
			e_1 = v_1_0 ;
			e_2 = v_2_0 ;
		}
	}


	double minproj = 2.2250738585072014e-308 ;
	double maxproj = 1.7976931348623158e+308 ;

	double minPt_x = px0 ; double minPt_y = py0 ; double minPt_z = pz0 ;
	double maxPt_x = px2 ; double maxPt_y = py2 ; double maxPt_z = pz2 ;


	double proj0 = (px0 * e_0) + (py0 * e_1) + (pz0 * e_2) ;

	if ( proj0 < minproj ) {
		minproj = proj0 ;
		minPt_x = px0 ; minPt_y = py0 ; minPt_z = pz0 ;
	}
	if ( proj0 > maxproj ) {
		maxproj = proj0 ;
		maxPt_x = px0 ; maxPt_y = py0 ; maxPt_z = pz0 ;
	}

	double proj1 = (px1 * e_0) + (py1 * e_1) + (pz1 * e_2) ;

	if ( proj1 < minproj ) {
		minproj = proj1 ;
		minPt_x = px1 ; minPt_y = py1 ; minPt_z = pz1 ;
	}
	if (proj1 > maxproj) {
		maxproj = proj1 ;
		maxPt_x = px1 ; maxPt_y = py1 ; maxPt_z = pz1 ;
	}

	double proj2 = (px2 * e_0) + (py2 * e_1) + (pz2 * e_2) ;

	if ( proj2 < minproj ) {
		minproj = proj2 ;
		minPt_x = px2 ; minPt_y = py2 ; minPt_z = pz2 ;
	}
	if (proj2 > maxproj) {
		maxproj = proj2 ;
		maxPt_x = px2 ; maxPt_y = py2 ; maxPt_z = pz2 ;
	}

	double	DX = (maxPt_x - minPt_x)	;
	double	DY = (maxPt_y - minPt_y)	;
	double	DZ = (maxPt_z - minPt_z)	;

	double	dist = sqrt((double) (DX*DX + DY*DY + DZ*DZ)) ;

	eigen_radius = dist + 0.5 ;

	DSENSITIVITY(eigen_radius);

}

