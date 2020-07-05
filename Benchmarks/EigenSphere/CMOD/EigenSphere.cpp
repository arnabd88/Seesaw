#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include<cmath>
#include <quadmath.h>
#include <time.h>

#define px0_low  0.9
#define px0_high 1.1
#define py0_low  0.9
#define py0_high 1.1
#define pz0_low  0.9
#define pz0_high 1.1
#define px1_low  2.4
#define px1_high 2.6
#define py1_low  2.4
#define py1_high 2.6
#define pz1_low  2.4
#define pz1_high 2.6
#define px2_low  1.4
#define px2_high 1.6
#define py2_low  1.4
#define py2_high 1.6
#define pz2_low  1.4
#define pz2_high 1.6
#define px3_low  3.1
#define px3_high 3.3
#define py3_low  3.1
#define py3_high 3.3
#define pz3_low  3.1
#define pz3_high 3.3
#define px4_low  2.1
#define px4_high 2.3
#define py4_low  2.1
#define py4_high 2.3
#define pz4_low  2.1
#define pz4_high 2.3

using namespace std ;


double  _px0;
double  _py0;
double  _pz0;
double  _px1;
double  _py1;
double  _pz1;
double  _px2;
double  _py2;
double  _pz2;
double  _px3;
double  _py3;
double  _pz3;
double  _px4;
double  _py4;
double  _pz4;

template<class T>
void init() {

  _px0	=	px0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(px0_high - px0_low))) ;
  _py0	=	py0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(py0_high - py0_low))) ;
  _pz0	=	pz0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pz0_high - pz0_low))) ;
  _px1	=	px1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(px1_high - px1_low))) ;
  _py1	=	py1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(py1_high - py1_low))) ;
  _pz1	=	pz1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pz1_high - pz1_low))) ;
  _px2	=	px1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(px2_high - px2_low))) ;
  _py2	=	py1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(py2_high - py2_low))) ;
  _pz2	=	pz1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pz2_high - pz2_low))) ;
  _px3	=	px1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(px3_high - px3_low))) ;
  _py3	=	py1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(py3_high - py3_low))) ;
  _pz3	=	pz1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pz3_high - pz3_low))) ;
  _px4	=	px1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(px4_high - px4_low))) ;
  _py4	=	py1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(py4_high - py4_low))) ;
  _pz4	=	pz1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(pz4_high - pz4_low))) ;

}

template<class T>
T execute_spec_precision() {

  T	px0	=	(T)	_px0;
  T	py0	=	(T)	_py0;
  T	pz0	=	(T)	_pz0;
  T	px1	=	(T)	_px1;
  T	py1	=	(T)	_py1;
  T	pz1	=	(T)	_pz1;
  T	px2	=	(T)	_px2;
  T	py2	=	(T)	_py2;
  T	pz2	=	(T)	_pz2;
  T	px3	=	(T)	_px3;
  T	py3	=	(T)	_py3;
  T	pz3	=	(T)	_pz3;
  T	px4	=	(T)	_px4;
  T	py4	=	(T)	_py4;
  T	pz4	=	(T)	_pz4;

	int numPts = 5 ;
	T cx = (px0 + px1 + px2 + px3 + px4)/numPts ;
	T cy = (py0 + py1 + py2 + py3 + py4)/numPts ;
	T cz = (pz0 + pz1 + pz2 + pz3 + pz4)/numPts ;
	T e00 = 0.0 ; T e11 = 0.0 ; T e22 = 0.0 ; T e01 = 0.0 ; T e02 = 0.0 ; T e12 = 0.0 ;

	T px = px0 - cx ;
	T py = py0 - cy ;
	T pz = pz0 - cz ;
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

	T	m_0_0 = e00 / numPts ;
	T	m_1_1 = e11 / numPts ;
	T	m_2_2 = e22 / numPts ;
	T	m_0_1 = e01 / numPts ;
	T	m_1_0 = e01 / numPts ;
	T	m_0_2 = e02 / numPts ;
	T	m_2_0 = e02 / numPts ;
	T	m_1_2 = e12 / numPts ;
	T	m_2_1 = e12 / numPts ;

	T	v_0_0 = 1.0;
	T	v_0_1 = 0.0;
	T	v_0_2 = 0.0;
	T	v_1_0 = 0.0;
	T	v_1_1 = 1.0;
	T	v_1_2 = 0.0;
	T	v_2_0 = 0.0;
	T	v_2_1 = 0.0;
	T	v_2_2 = 1.0;

	T t, c, s ;

	if (( m_1_2 > 0 && m_1_2 > 0.0001 ) || ( m_1_2 < 0 && -1*m_1_2 > 0.0001))  {
		
		T r = (m_2_2 - m_1_1) / (2.0 * m_1_2) ;

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

	T	J_0_0 = 1.0;
	T	J_0_1 = 0.0;
	T	J_0_2 = 0.0;
	T	J_1_0 = 0.0;
	T	J_1_1 = 1.0;
	T	J_1_2 = 0.0;
	T	J_2_0 = 0.0;
	T	J_2_1 = 0.0;
	T	J_2_2 = 1.0;

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

	T	jtm_0_0 = J_0_0 * m_0_0 + J_1_0 * m_1_0 + J_2_0 * m_2_0 ;
	T	jtm_0_1 = J_0_0 * m_0_1 + J_1_0 * m_1_1 + J_2_0 * m_2_1 ;
	T	jtm_0_2 = J_0_0 * m_0_2 + J_1_0 * m_1_2 + J_2_0 * m_2_2 ;
	T	jtm_1_0 = J_0_1 * m_0_0 + J_1_1 * m_1_0 + J_2_1 * m_2_0 ;
	T	jtm_1_1 = J_0_1 * m_0_1 + J_1_1 * m_1_1 + J_2_1 * m_2_1 ;
	T	jtm_1_2 = J_0_1 * m_0_2 + J_1_1 * m_1_2 + J_2_1 * m_2_2 ;
	T	jtm_2_0 = J_0_2 * m_0_0 + J_1_2 * m_1_0 + J_2_2 * m_2_0 ;
	T	jtm_2_1 = J_0_2 * m_0_1 + J_1_2 * m_1_1 + J_2_2 * m_2_1 ;
	T	jtm_2_2 = J_0_2 * m_0_2 + J_1_2 * m_1_2 + J_2_2 * m_2_2 ;

	m_0_0 = jtm_0_0 * J_0_0 + jtm_0_1 * J_1_0 + jtm_0_2 * J_2_0 ;
	m_0_1 = jtm_0_0 * J_0_1 + jtm_0_1 * J_1_1 + jtm_0_2 * J_2_1 ;
	m_0_2 = jtm_0_0 * J_0_2 + jtm_0_1 * J_1_2 + jtm_0_2 * J_2_2 ;
	m_1_0 = jtm_1_0 * J_0_0 + jtm_1_1 * J_1_0 + jtm_1_2 * J_2_0 ;
	m_1_1 = jtm_1_0 * J_0_1 + jtm_1_1 * J_1_1 + jtm_1_2 * J_2_1 ;
	m_1_2 = jtm_1_0 * J_0_2 + jtm_1_1 * J_1_2 + jtm_1_2 * J_2_2 ;
	m_2_0 = jtm_2_0 * J_0_0 + jtm_2_1 * J_1_0 + jtm_2_2 * J_2_0 ;
	m_2_1 = jtm_2_0 * J_0_1 + jtm_2_1 * J_1_1 + jtm_2_2 * J_2_1 ;
	m_2_2 = jtm_2_0 * J_0_2 + jtm_2_1 * J_1_2 + jtm_2_2 * J_2_2 ;

	T	off = m_0_1 * m_0_1 + m_0_2 * m_0_2 + m_1_0 * m_1_0 + m_1_2 * m_1_2 + m_2_0 * m_2_0 + m_2_1 * m_2_1 ;

	T maxf_0, maxf_1, maxf_2 ;
	T maxe_0, maxe_1, maxe_2 ;

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

	T e_0, e_1, e_2 ;

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


	T minproj = 2.2250738585072014e-308 ;
	T maxproj = 1.7976931348623158e+308 ;

	T minPt_x = px0 ; T minPt_y = py0 ; T minPt_z = pz0 ;
	T maxPt_x = px2 ; T maxPt_y = py2 ; T maxPt_z = pz2 ;


	T proj0 = (px0 * e_0) + (py0 * e_1) + (pz0 * e_2) ;

	if ( proj0 < minproj ) {
		minproj = proj0 ;
		minPt_x = px0 ; minPt_y = py0 ; minPt_z = pz0 ;
	}
	if ( proj0 > maxproj ) {
		maxproj = proj0 ;
		maxPt_x = px0 ; maxPt_y = py0 ; maxPt_z = pz0 ;
	}

	T proj1 = (px1 * e_0) + (py1 * e_1) + (pz1 * e_2) ;

	if ( proj1 < minproj ) {
		minproj = proj1 ;
		minPt_x = px1 ; minPt_y = py1 ; minPt_z = pz1 ;
	}
	if (proj1 > maxproj) {
		maxproj = proj1 ;
		maxPt_x = px1 ; maxPt_y = py1 ; maxPt_z = pz1 ;
	}

	T proj2 = (px2 * e_0) + (py2 * e_1) + (pz2 * e_2) ;

	if ( proj2 < minproj ) {
		minproj = proj2 ;
		minPt_x = px2 ; minPt_y = py2 ; minPt_z = pz2 ;
	}
	if (proj2 > maxproj) {
		maxproj = proj2 ;
		maxPt_x = px2 ; maxPt_y = py2 ; maxPt_z = pz2 ;
	}

	T	DX = (maxPt_x - minPt_x)	;
	T	DY = (maxPt_y - minPt_y)	;
	T	DZ = (maxPt_z - minPt_z)	;

	T	dist = sqrt((double) (DX*DX + DY*DY + DZ*DZ)) ;

	return dist + 0.5 ;


}




int main(int argc, char** argv)

{

	srand(time(0));

	FILE *fp ;
	int N;
	sscanf(argv[1], "%d", &N);
	fp = fopen("barycentric_ccordinates_profile.csv", "w+");

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
