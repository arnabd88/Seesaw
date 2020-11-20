#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <quadmath.h>
#include <time.h>
#include <fstream>
#include <sstream>

#define U_0_1_low 0
#define U_0_1_high 1
#define U_0_2_low 0
#define U_0_2_high 1
#define U_0_3_low 0
#define U_0_3_high 1
#define U_0_4_low 0
#define U_0_4_high 1
#define U_0_5_low 0
#define U_0_5_high 1
#define U_0_6_low 0
#define U_0_6_high 1
#define U_0_7_low 0
#define U_0_7_high 1
#define U_0_8_low 0
#define U_0_8_high 1

#define U_1_0_low 0
#define U_1_0_high 1
#define U_1_1_low 0.005133704202909505
#define U_1_1_high 0.025133704202909505
#define U_1_2_low 0.06557737496709567
#define U_1_2_high 0.08557737496709567
#define U_1_3_low 0.21627683382165126
#define U_1_3_high 0.23627683382165126
#define U_1_4_low 0.5014514548947724
#define U_1_4_high 0.5214514548947724
#define U_1_5_low 0.9642355402612368
#define U_1_5_high 0.9842355402612368
#define U_1_6_low 1.6463251928653044
#define U_1_6_high 1.6663251928653044
#define U_1_7_low 2.5876324841579714
#define U_1_7_high 2.6076324841579714
#define U_1_8_low 0.3726834323650898
#define U_1_8_high 0.3926834323650898

#define U_2_0_low -0.01
#define U_2_0_high 0.01
#define U_2_1_low 0.06557737496709567
#define U_2_1_high 0.08557737496709567
#define U_2_2_low 0.23068303759753992
#define U_2_2_high 0.25068303759753992
#define U_2_3_low 0.5719520947905122
#define U_2_3_high 0.5919520947905122
#define U_2_4_low 1.1702919025920224
#define U_2_4_high 1.1902919025920224
#define U_2_5_low 2.0981637491355285
#define U_2_5_high 2.1181637491355285
#define U_2_6_low 3.417036510577816
#define U_2_6_high 3.437036510577816
#define U_2_7_low 5.175065151849399
#define U_2_7_high 5.195065151849399
#define U_2_8_low 0.6971067811865475
#define U_2_8_high 0.7171067811865475

#define U_3_0_low 0
#define U_3_0_high 1
#define U_3_1_low -0.273723166
#define U_3_1_high 0.72627683382165126
#define U_3_2_low 0.0819520947905122
#define U_3_2_high 1.0819520947905122
#define U_3_3_low 0.686818646451536
#define U_3_3_high 1.686818646451536
#define U_3_4_low 1.641897819111135
#define U_3_4_high 2.641897819111135
#define U_3_5_low 3.02113627118546
#define U_3_5_high 4.02113627118546
#define U_3_6_low 4.864356746357229
#define U_3_6_high 5.864356746357229
#define U_3_7_low 7.171806870680292
#define U_3_7_high 8.171806870680292
#define U_3_8_low 0.4238795325112867
#define U_3_8_high 1.4238795325112867

#define U_4_0_low -0.5
#define U_4_0_high 0
#define U_4_1_low 0.0114514548947724
#define U_4_1_high 1.0114514548947724
#define U_4_2_low 0.6802919025920224
#define U_4_2_high 1.6802919025920224
#define U_4_3_low 1.641897819111135
#define U_4_3_high 2.641897819111135
#define U_4_4_low 2.9894320998194392
#define U_4_4_high 3.9894320998194392
#define U_4_5_low 4.7571456553606835
#define U_4_5_high 5.7571456553606835
#define U_4_6_low 6.908639468871691
#define U_4_6_high 7.908639468871691
#define U_4_7_low 9.331212137491248
#define U_4_7_high 10.331212137491248
#define U_4_8_low 0.5
#define U_4_8_high 1.5

#define U_5_0_low -0.5
#define U_5_0_high 0.5
#define U_5_1_low 0.4742355402612368
#define U_5_1_high 1.4742355402612368
#define U_5_2_low 1.6081637491355285
#define U_5_2_high 2.6081637491355285
#define U_5_3_low 3.02113627118546
#define U_5_3_high 4.02113627118546
#define U_5_4_low 4.7571456553606835
#define U_5_4_high 5.7571456553606835
#define U_5_5_low 6.759896444960865
#define U_5_5_high 7.759896444960865
#define U_5_6_low 8.861669578967348
#define U_5_6_high 9.861669578967348
#define U_5_7_low 10.788215341859273
#define U_5_7_high 11.788215341859273
#define U_5_8_low 0.4238795325112867
#define U_5_8_high 1.4238795325112867

#define U_6_0_low -0.5
#define U_6_0_high 0
#define U_6_1_low 1.1563251928653044
#define U_6_1_high 2.1563251928653044
#define U_6_2_low 2.927036510577816
#define U_6_2_high 3.927036510577816
#define U_6_3_low 4.864356746357229
#define U_6_3_high 5.864356746357229
#define U_6_4_low 6.908639468871691
#define U_6_4_high 7.908639468871691
#define U_6_5_low 8.861669578967348
#define U_6_5_high 9.861669578967348
#define U_6_6_low 10.389958059990306
#define U_6_6_high 11.389958059990306
#define U_6_7_low 11.060284208160615
#define U_6_7_high 12.060284208160615
#define U_6_8_low 0.2071067811865476
#define U_6_8_high 1.2071067811865476

#define U_7_0_low -0.5
#define U_7_0_high 0
#define U_7_1_low 2.0976324841579714
#define U_7_1_high 3.0976324841579714
#define U_7_2_low 4.685065151849399
#define U_7_2_high 5.685065151849399
#define U_7_3_low 7.171806870680292
#define U_7_3_high 8.171806870680292
#define U_7_4_low 9.331212137491248
#define U_7_4_high 10.331212137491248
#define U_7_5_low 10.788215341859273
#define U_7_5_high 11.788215341859273
#define U_7_6_low 11.060284208160615
#define U_7_6_high 12.060284208160615
#define U_7_7_low 9.649157487534564
#define U_7_7_high 10.649157487534564
#define U_7_8_low -0.117316568
#define U_7_8_high 0.8826834323650899

#define U_8_0_low -0.5
#define U_8_0_high 0
#define U_8_1_low -0.117316568
#define U_8_1_high 0.8826834323650898
#define U_8_2_low 0.2071067811865475
#define U_8_2_high 1.2071067811865475
#define U_8_3_low 0.4238795325112867
#define U_8_3_high 1.4238795325112867
#define U_8_4_low 0.5
#define U_8_4_high 1.5
#define U_8_5_low 0.4238795325112867
#define U_8_5_high 1.4238795325112867
#define U_8_6_low 0.2071067811865476
#define U_8_6_high 1.2071067811865476
#define U_8_7_low -0.117316568
#define U_8_7_high 0.8826834323650899
#define U_8_8_low 0.7246467991473532e-16
#define U_8_8_high 1.7246467991473532e-16


using namespace std ;

double _U_0_1 ;
double _U_0_2 ;
double _U_0_3 ;
double _U_0_4 ;
double _U_0_5 ;
double _U_0_6 ;
double _U_0_7 ;
double _U_0_8 ;

double _U_1_0 ;
double _U_1_1 ;
double _U_1_2 ;
double _U_1_3 ;
double _U_1_4 ;
double _U_1_5 ;
double _U_1_6 ;
double _U_1_7 ;
double _U_1_8 ;

double _U_2_0 ;
double _U_2_1 ;
double _U_2_2 ;
double _U_2_3 ;
double _U_2_4 ;
double _U_2_5 ;
double _U_2_6 ;
double _U_2_7 ;
double _U_2_8 ;

double _U_3_0 ;
double _U_3_1 ;
double _U_3_2 ;
double _U_3_3 ;
double _U_3_4 ;
double _U_3_5 ;
double _U_3_6 ;
double _U_3_7 ;
double _U_3_8 ;

double _U_4_0 ;
double _U_4_1 ;
double _U_4_2 ;
double _U_4_3 ;
double _U_4_4 ;
double _U_4_5 ;
double _U_4_6 ;
double _U_4_7 ;
double _U_4_8 ;

double _U_5_0 ;
double _U_5_1 ;
double _U_5_2 ;
double _U_5_3 ;
double _U_5_4 ;
double _U_5_5 ;
double _U_5_6 ;
double _U_5_7 ;
double _U_5_8 ;

double _U__0 ;
double _U__1 ;
double _U__2 ;
double _U__3 ;
double _U__4 ;
double _U__5 ;
double _U__6 ;
double _U__7 ;
double _U__8 ;

double _U_6_0 ;
double _U_6_1 ;
double _U_6_2 ;
double _U_6_3 ;
double _U_6_4 ;
double _U_6_5 ;
double _U_6_6 ;
double _U_6_7 ;
double _U_6_8 ;

double _U_7_0 ;
double _U_7_1 ;
double _U_7_2 ;
double _U_7_3 ;
double _U_7_4 ;
double _U_7_5 ;
double _U_7_6 ;
double _U_7_7 ;
double _U_7_8 ;

double _U_8_0 ;
double _U_8_1 ;
double _U_8_2 ;
double _U_8_3 ;
double _U_8_4 ;
double _U_8_5 ;
double _U_8_6 ;
double _U_8_7 ;
double _U_8_8 ;

template<class T>
void init() {
	_U_0_1 = U_0_1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_0_1_high - U_0_1_low))) ;
	_U_0_2 = U_0_2_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_0_2_high - U_0_2_low))) ;
	_U_0_3 = U_0_3_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_0_3_high - U_0_3_low))) ;
	_U_0_4 = U_0_4_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_0_4_high - U_0_4_low))) ;
	_U_0_5 = U_0_5_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_0_5_high - U_0_5_low))) ;
	_U_0_6 = U_0_6_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_0_6_high - U_0_6_low))) ;
	_U_0_7 = U_0_7_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_0_7_high - U_0_7_low))) ;
	_U_0_8 = U_0_8_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_0_8_high - U_0_8_low))) ;

	_U_1_0 = U_1_0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_1_0_high - U_1_0_low))) ;
	_U_1_1 = U_1_1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_1_1_high - U_1_1_low))) ;
	_U_1_2 = U_1_2_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_1_2_high - U_1_2_low))) ;
	_U_1_3 = U_1_3_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_1_3_high - U_1_3_low))) ;
	_U_1_4 = U_1_4_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_1_4_high - U_1_4_low))) ;
	_U_1_5 = U_1_5_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_1_5_high - U_1_5_low))) ;
	_U_1_6 = U_1_6_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_1_6_high - U_1_6_low))) ;
	_U_1_7 = U_1_7_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_1_7_high - U_1_7_low))) ;
	_U_1_8 = U_1_8_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_1_8_high - U_1_8_low))) ;

	_U_2_0 = U_2_0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_2_0_high - U_2_0_low))) ;
	_U_2_1 = U_2_1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_2_1_high - U_2_1_low))) ;
	_U_2_2 = U_2_2_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_2_2_high - U_2_2_low))) ;
	_U_2_3 = U_2_3_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_2_3_high - U_2_3_low))) ;
	_U_2_4 = U_2_4_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_2_4_high - U_2_4_low))) ;
	_U_2_5 = U_2_5_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_2_5_high - U_2_5_low))) ;
	_U_2_6 = U_2_6_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_2_6_high - U_2_6_low))) ;
	_U_2_7 = U_2_7_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_2_7_high - U_2_7_low))) ;
	_U_2_8 = U_2_8_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_2_8_high - U_2_8_low))) ;

	_U_3_0 = U_3_0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_3_0_high - U_3_0_low))) ;
	_U_3_1 = U_3_1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_3_1_high - U_3_1_low))) ;
	_U_3_2 = U_3_2_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_3_2_high - U_3_2_low))) ;
	_U_3_3 = U_3_3_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_3_3_high - U_3_3_low))) ;
	_U_3_4 = U_3_4_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_3_4_high - U_3_4_low))) ;
	_U_3_5 = U_3_5_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_3_5_high - U_3_5_low))) ;
	_U_3_6 = U_3_6_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_3_6_high - U_3_6_low))) ;
	_U_3_7 = U_3_7_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_3_7_high - U_3_7_low))) ;
	_U_3_8 = U_3_8_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_3_8_high - U_3_8_low))) ;

	_U_4_0 = U_4_0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_4_0_high - U_4_0_low))) ;
	_U_4_1 = U_4_1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_4_1_high - U_4_1_low))) ;
	_U_4_2 = U_4_2_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_4_2_high - U_4_2_low))) ;
	_U_4_3 = U_4_3_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_4_3_high - U_4_3_low))) ;
	_U_4_4 = U_4_4_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_4_4_high - U_4_4_low))) ;
	_U_4_5 = U_4_5_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_4_5_high - U_4_5_low))) ;
	_U_4_6 = U_4_6_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_4_6_high - U_4_6_low))) ;
	_U_4_7 = U_4_7_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_4_7_high - U_4_7_low))) ;
	_U_4_8 = U_4_8_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_4_8_high - U_4_8_low))) ;

	_U_5_0 = U_5_0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_5_0_high - U_5_0_low))) ;
	_U_5_1 = U_5_1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_5_1_high - U_5_1_low))) ;
	_U_5_2 = U_5_2_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_5_2_high - U_5_2_low))) ;
	_U_5_3 = U_5_3_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_5_3_high - U_5_3_low))) ;
	_U_5_4 = U_5_4_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_5_4_high - U_5_4_low))) ;
	_U_5_5 = U_5_5_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_5_5_high - U_5_5_low))) ;
	_U_5_6 = U_5_6_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_5_6_high - U_5_6_low))) ;
	_U_5_7 = U_5_7_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_5_7_high - U_5_7_low))) ;
	_U_5_8 = U_5_8_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_5_8_high - U_5_8_low))) ;

	_U_6_0 = U_6_0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_6_0_high - U_6_0_low))) ;
	_U_6_1 = U_6_1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_6_1_high - U_6_1_low))) ;
	_U_6_2 = U_6_2_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_6_2_high - U_6_2_low))) ;
	_U_6_3 = U_6_3_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_6_3_high - U_6_3_low))) ;
	_U_6_4 = U_6_4_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_6_4_high - U_6_4_low))) ;
	_U_6_5 = U_6_5_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_6_5_high - U_6_5_low))) ;
	_U_6_6 = U_6_6_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_6_6_high - U_6_6_low))) ;
	_U_6_7 = U_6_7_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_6_7_high - U_6_7_low))) ;
	_U_6_8 = U_6_8_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_6_8_high - U_6_8_low))) ;

	_U_7_0 = U_7_0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_7_0_high - U_7_0_low))) ;
	_U_7_1 = U_7_1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_7_1_high - U_7_1_low))) ;
	_U_7_2 = U_7_2_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_7_2_high - U_7_2_low))) ;
	_U_7_3 = U_7_3_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_7_3_high - U_7_3_low))) ;
	_U_7_4 = U_7_4_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_7_4_high - U_7_4_low))) ;
	_U_7_5 = U_7_5_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_7_5_high - U_7_5_low))) ;
	_U_7_6 = U_7_6_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_7_6_high - U_7_6_low))) ;
	_U_7_7 = U_7_7_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_7_7_high - U_7_7_low))) ;
	_U_7_8 = U_7_8_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_7_8_high - U_7_8_low))) ;

	_U_8_0 = U_8_0_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_8_0_high - U_8_0_low))) ;
	_U_8_1 = U_8_1_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_8_1_high - U_8_1_low))) ;
	_U_8_2 = U_8_2_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_8_2_high - U_8_2_low))) ;
	_U_8_3 = U_8_3_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_8_3_high - U_8_3_low))) ;
	_U_8_4 = U_8_4_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_8_4_high - U_8_4_low))) ;
	_U_8_5 = U_8_5_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_8_5_high - U_8_5_low))) ;
	_U_8_6 = U_8_6_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_8_6_high - U_8_6_low))) ;
	_U_8_7 = U_8_7_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_8_7_high - U_8_7_low))) ;
	_U_8_8 = U_8_8_low + static_cast<T> (rand())/(static_cast<T>(RAND_MAX/(U_8_8_high - U_8_8_low))) ;
}

template<class T>
T execute_spec_precision(int conditions[])
{
    T	res;

	T U_0_1 = (T) _U_0_1;
	T U_0_2 = (T) _U_0_2;
	T U_0_3 = (T) _U_0_3;
	T U_0_4 = (T) _U_0_4;
	T U_0_5 = (T) _U_0_5;
	T U_0_6 = (T) _U_0_6;
	T U_0_7 = (T) _U_0_7;
	T U_0_8 = (T) _U_0_8;

	T U_1_0 = (T) _U_1_0;
	T U_1_1 = (T) _U_1_1;
	T U_1_2 = (T) _U_1_2;
	T U_1_3 = (T) _U_1_3;
	T U_1_4 = (T) _U_1_4;
	T U_1_5 = (T) _U_1_5;
	T U_1_6 = (T) _U_1_6;
	T U_1_7 = (T) _U_1_7;
	T U_1_8 = (T) _U_1_8;

	T U_2_0 = (T) _U_2_0;
	T U_2_1 = (T) _U_2_1;
	T U_2_2 = (T) _U_2_2;
	T U_2_3 = (T) _U_2_3;
	T U_2_4 = (T) _U_2_4;
	T U_2_5 = (T) _U_2_5;
	T U_2_6 = (T) _U_2_6;
	T U_2_7 = (T) _U_2_7;
	T U_2_8 = (T) _U_2_8;

	T U_3_0 = (T) _U_3_0;
	T U_3_1 = (T) _U_3_1;
	T U_3_2 = (T) _U_3_2;
	T U_3_3 = (T) _U_3_3;
	T U_3_4 = (T) _U_3_4;
	T U_3_5 = (T) _U_3_5;
	T U_3_6 = (T) _U_3_6;
	T U_3_7 = (T) _U_3_7;
	T U_3_8 = (T) _U_3_8;

	T U_4_0 = (T) _U_4_0;
	T U_4_1 = (T) _U_4_1;
	T U_4_2 = (T) _U_4_2;
	T U_4_3 = (T) _U_4_3;
	T U_4_4 = (T) _U_4_4;
	T U_4_5 = (T) _U_4_5;
	T U_4_6 = (T) _U_4_6;
	T U_4_7 = (T) _U_4_7;
	T U_4_8 = (T) _U_4_8;

	T U_5_0 = (T) _U_5_0;
	T U_5_1 = (T) _U_5_1;
	T U_5_2 = (T) _U_5_2;
	T U_5_3 = (T) _U_5_3;
	T U_5_4 = (T) _U_5_4;
	T U_5_5 = (T) _U_5_5;
	T U_5_6 = (T) _U_5_6;
	T U_5_7 = (T) _U_5_7;
	T U_5_8 = (T) _U_5_8;

	T U_6_0 = (T) _U_6_0;
	T U_6_1 = (T) _U_6_1;
	T U_6_2 = (T) _U_6_2;
	T U_6_3 = (T) _U_6_3;
	T U_6_4 = (T) _U_6_4;
	T U_6_5 = (T) _U_6_5;
	T U_6_6 = (T) _U_6_6;
	T U_6_7 = (T) _U_6_7;
	T U_6_8 = (T) _U_6_8;

	T U_7_0 = (T) _U_7_0;
	T U_7_1 = (T) _U_7_1;
	T U_7_2 = (T) _U_7_2;
	T U_7_3 = (T) _U_7_3;
	T U_7_4 = (T) _U_7_4;
	T U_7_5 = (T) _U_7_5;
	T U_7_6 = (T) _U_7_6;
	T U_7_7 = (T) _U_7_7;
	T U_7_8 = (T) _U_7_8;

	T U_8_0 = (T) _U_8_0;
	T U_8_1 = (T) _U_8_1;
	T U_8_2 = (T) _U_8_2;
	T U_8_3 = (T) _U_8_3;
	T U_8_4 = (T) _U_8_4;
	T U_8_5 = (T) _U_8_5;
	T U_8_6 = (T) _U_8_6;
	T U_8_7 = (T) _U_8_7;
	T U_8_8 = (T) _U_8_8;

	T tolerance = 0.000001;

    T F_0_0 = 0.0;
    T F_0_1 = 0.0;
    T F_0_2 = 0.0;
    T F_0_3 = 0.0;
    T F_0_4 = 0.0;

    T F_0_5 = 0.0;
    T F_0_6 = 0.0;
    T F_0_7 = 0.0;
    T F_0_8 = 0.0;

    T F_1_0 = 0.0;
    T F_1_1 = 0.015133704202909505;
    T F_1_2 = 0.07557737496709567;
    T F_1_3 = 0.22627683382165126;
    T F_1_4 = 0.5114514548947724;
    T F_1_5 = 0.9742355402612368;
    T F_1_6 = 1.6563251928653044;
    T F_1_7 = 2.5976324841579714;
    T F_1_8 = 0.3826834323650898;

    T F_2_0 = 0.0;
    T F_2_1 = 0.07557737496709567;
    T F_2_2 = 0.24068303759753992;
    T F_2_3 = 0.5819520947905122;
    T F_2_4 = 1.1802919025920224;
    T F_2_5 = 2.1081637491355285;
    T F_2_6 = 3.427036510577816;
    T F_2_7 = 5.185065151849399;
    T F_2_8 = 0.7071067811865475;


    T F_3_0 = 0.0;
    T F_3_1 = 0.22627683382165126;
    T F_3_2 = 0.5819520947905122;
    T F_3_3 = 1.186818646451536;
    T F_3_4 = 2.141897819111135;
    T F_3_5 = 3.52113627118546;
    T F_3_6 = 5.364356746357229;
    T F_3_7 = 7.671806870680292;
    T F_3_8 = 0.9238795325112867;

    T F_4_0 = 0.0;
    T F_4_1 = 0.5114514548947724;
    T F_4_2 = 1.1802919025920224;
    T F_4_3 = 2.141897819111135;
    T F_4_4 = 3.4894320998194392;
    T F_4_5 = 5.2571456553606835;
    T F_4_6 = 7.408639468871691;
    T F_4_7 = 9.831212137491248;
    T F_4_8 = 1.0;

    T F_5_0 = 0.0;
    T F_5_1 = 0.9742355402612368;
    T F_5_2 = 2.1081637491355285;
    T F_5_3 = 3.52113627118546;
    T F_5_4 = 5.2571456553606835;
    T F_5_5 = 7.259896444960865;
    T F_5_6 = 9.361669578967348;
    T F_5_7 = 11.288215341859273;
    T F_5_8 = 0.9238795325112867;

    T F_6_0 = 0.0;
    T F_6_1 = 1.6563251928653044;
    T F_6_2 = 3.427036510577816;
    T F_6_3 = 5.364356746357229;
    T F_6_4 = 7.408639468871691;
    T F_6_5 = 9.361669578967348;
    T F_6_6 = 10.889958059990306;
    T F_6_7 = 11.560284208160615;
    T F_6_8 = 0.7071067811865476;

    T F_7_0 = 0.0;
    T F_7_1 = 2.5976324841579714;
    T F_7_2 = 5.185065151849399;
    T F_7_3 = 7.671806870680292;
    T F_7_4 = 9.831212137491248;
    T F_7_5 = 11.288215341859273;
    T F_7_6 = 11.560284208160615;
    T F_7_7 = 10.149157487534564;
    T F_7_8 = 0.3826834323650899;

    T F_8_0 = 0.0;
    T F_8_1 = 0.3826834323650898;
    T F_8_2 = 0.7071067811865475;
    T F_8_3 = 0.9238795325112867;
    T F_8_4 = 1.0;
    T F_8_5 = 0.9238795325112867;
    T F_8_6 = 0.7071067811865476;
    T F_8_7 = 0.3826834323650899;
    T F_8_8 = 1.2246467991473532e-16;


    // Set the UEXACT solution
    T uexact_0_0 = 0.0;
    T uexact_0_1 = 0.0;
    T uexact_0_2 = 0.0;
    T uexact_0_3 = 0.0;
    T uexact_0_4 = 0.0;
    T uexact_0_5 = 0.0;
    T uexact_0_6 = 0.0;
    T uexact_0_7 = 0.0;
    T uexact_0_8 = 0.0;

    T uexact_1_0 = 0.0;
    T uexact_1_1 = 0.049067674327418015;
    T uexact_1_2 = 0.0980171403295606;
    T uexact_1_3 = 0.14673047445536175;
    T uexact_1_4 = 0.19509032201612825;
    T uexact_1_5 = 0.24298017990326387;
    T uexact_1_6 = 0.29028467725446233;
    T uexact_1_7 = 0.33688985339222005;
    T uexact_1_8 = 0.3826834323650898;

    T uexact_2_0 = 0.0;
    T uexact_2_1 = 0.0980171403295606;
    T uexact_2_2 = 0.19509032201612825;
    T uexact_2_3 = 0.29028467725446233;
    T uexact_2_4 = 0.3826834323650898;
    T uexact_2_5 = 0.47139673682599764;
    T uexact_2_6 = 0.5555702330196022;
    T uexact_2_7 = 0.6343932841636455;
    T uexact_2_8 = 0.7071067811865475;

    T uexact_3_0 = 0.0;
    T uexact_3_1 = 0.14673047445536175;
    T uexact_3_2 = 0.29028467725446233;
    T uexact_3_3 = 0.4275550934302821;
    T uexact_3_4 = 0.5555702330196022;
    T uexact_3_5 = 0.6715589548470183;
    T uexact_3_6 = 0.773010453362737;
    T uexact_3_7 = 0.8577286100002721;
    T uexact_3_8 = 0.9238795325112867;

    T uexact_4_0 = 0.0;
    T uexact_4_1 = 0.19509032201612825;
    T uexact_4_2 = 0.3826834323650898;
    T uexact_4_3 = 0.5555702330196022;
    T uexact_4_4 = 0.7071067811865475;
    T uexact_4_5 = 0.8314696123025452;
    T uexact_4_6 = 0.9238795325112867;
    T uexact_4_7 = 0.9807852804032304;
    T uexact_4_8 = 1.0;

    T uexact_5_0 = 0.0;
    T uexact_5_1 = 0.24298017990326387;
    T uexact_5_2 = 0.47139673682599764;
    T uexact_5_3 = 0.6715589548470183;
    T uexact_5_4 = 0.8314696123025452;
    T uexact_5_5 = 0.9415440651830208;
    T uexact_5_6 = 0.9951847266721968;
    T uexact_5_7 = 0.989176509964781;
    T uexact_5_8 = 0.9238795325112867;

    T uexact_6_0 = 0.0;
    T uexact_6_1 = 0.29028467725446233;
    T uexact_6_2 = 0.5555702330196022;
    T uexact_6_3 = 0.773010453362737;
    T uexact_6_4 = 0.9238795325112867;
    T uexact_6_5 = 0.9951847266721968;
    T uexact_6_6 = 0.9807852804032304;
    T uexact_6_7 = 0.881921264348355;
    T uexact_6_8 = 0.7071067811865476;

    T uexact_7_0 = 0.0;
    T uexact_7_1 = 0.33688985339222005;
    T uexact_7_2 = 0.6343932841636455;
    T uexact_7_3 = 0.8577286100002721;
    T uexact_7_4 = 0.9807852804032304;
    T uexact_7_5 = 0.989176509964781;
    T uexact_7_6 = 0.881921264348355;
    T uexact_7_7 = 0.6715589548470186;
    T uexact_7_8 = 0.3826834323650899;

    T uexact_8_0 = 0.0;
    T uexact_8_1 = 0.3826834323650898;
    T uexact_8_2 = 0.7071067811865475;
    T uexact_8_3 = 0.9238795325112867;
    T uexact_8_4 = 1.0;
    T uexact_8_5 = 0.9238795325112867;
    T uexact_8_6 = 0.7071067811865476;
    T uexact_8_7 = 0.3826834323650899;
    T uexact_8_8 = 1.2246467991473532e-16;



    // first sweep

    T U_0_0_1 = F_0_0;
    T U_1_0_1 = F_1_0;
    T U_2_0_1 = F_2_0;
    T U_3_0_1 = F_3_0;
    T U_4_0_1 = F_4_0;
    T U_5_0_1 = F_5_0;
    T U_6_0_1 = F_6_0;
    T U_7_0_1 = F_7_0;
    T U_8_0_1 = F_8_0;
    T U_0_1_1 = F_0_1;
    T U_1_1_1 = 0.25*( U_2_1 + U_1_2 + U_0_1 + U_1_0 + F_1_1*0.125*0.125 );
    T U_2_1_1 = 0.25*( U_3_1 + U_2_2 + U_1_1 + U_2_0 + F_2_1*0.125*0.125 );
    T U_3_1_1 = 0.25*( U_4_1 + U_3_2 + U_2_1 + U_3_0 + F_3_1*0.125*0.125 );
    T U_4_1_1 = 0.25*( U_5_1 + U_4_2 + U_3_1 + U_4_0 + F_4_1*0.125*0.125 );
    T U_5_1_1 = 0.25*( U_6_1 + U_5_2 + U_4_1 + U_5_0 + F_5_1*0.125*0.125 );
    T U_6_1_1 = 0.25*( U_7_1 + U_6_2 + U_5_1 + U_6_0 + F_6_1*0.125*0.125 );
    T U_7_1_1 = 0.25*( U_8_1 + U_7_2 + U_6_1 + U_7_0 + F_7_1*0.125*0.125 );
    T U_8_1_1 = F_8_1;
    T U_0_2_1 = F_0_2;
    T U_1_2_1 = 0.25*( U_2_2 + U_1_3 + U_0_2 + U_1_1 + F_1_2*0.125*0.125 );
    T U_2_2_1 = 0.25*( U_3_2 + U_2_3 + U_1_2 + U_2_1 + F_2_2*0.125*0.125 );
    T U_3_2_1 = 0.25*( U_4_2 + U_3_3 + U_2_2 + U_3_1 + F_3_2*0.125*0.125 );
    T U_4_2_1 = 0.25*( U_5_2 + U_4_3 + U_3_2 + U_4_1 + F_4_2*0.125*0.125 );
    T U_5_2_1 = 0.25*( U_6_2 + U_5_3 + U_4_2 + U_5_1 + F_5_2*0.125*0.125 );
    T U_6_2_1 = 0.25*( U_7_2 + U_6_3 + U_5_2 + U_6_1 + F_6_2*0.125*0.125 );
    T U_7_2_1 = 0.25*( U_8_2 + U_7_3 + U_6_2 + U_7_1 + F_7_2*0.125*0.125 );
    T U_8_2_1 = F_8_2;
    T U_0_3_1 = F_0_3;
    T U_1_3_1 = 0.25*( U_2_3 + U_1_4 + U_0_3 + U_1_2 + F_1_3*0.125*0.125 );
    T U_2_3_1 = 0.25*( U_3_3 + U_2_4 + U_1_3 + U_2_2 + F_2_3*0.125*0.125 );
    T U_3_3_1 = 0.25*( U_4_3 + U_3_4 + U_2_3 + U_3_2 + F_3_3*0.125*0.125 );
    T U_4_3_1 = 0.25*( U_5_3 + U_4_4 + U_3_3 + U_4_2 + F_4_3*0.125*0.125 );
    T U_5_3_1 = 0.25*( U_6_3 + U_5_4 + U_4_3 + U_5_2 + F_5_3*0.125*0.125 );
    T U_6_3_1 = 0.25*( U_7_3 + U_6_4 + U_5_3 + U_6_2 + F_6_3*0.125*0.125 );
    T U_7_3_1 = 0.25*( U_8_3 + U_7_4 + U_6_3 + U_7_2 + F_7_3*0.125*0.125 );
    T U_8_3_1 = F_8_3;
    T U_0_4_1 = F_0_4;
    T U_1_4_1 = 0.25*( U_2_4 + U_1_5 + U_0_4 + U_1_3 + F_1_4*0.125*0.125 );
    T U_2_4_1 = 0.25*( U_3_4 + U_2_5 + U_1_4 + U_2_3 + F_2_4*0.125*0.125 );
    T U_3_4_1 = 0.25*( U_4_4 + U_3_5 + U_2_4 + U_3_3 + F_3_4*0.125*0.125 );
    T U_4_4_1 = 0.25*( U_5_4 + U_4_5 + U_3_4 + U_4_3 + F_4_4*0.125*0.125 );
    T U_5_4_1 = 0.25*( U_6_4 + U_5_5 + U_4_4 + U_5_3 + F_5_4*0.125*0.125 );
    T U_6_4_1 = 0.25*( U_7_4 + U_6_5 + U_5_4 + U_6_3 + F_6_4*0.125*0.125 );
    T U_7_4_1 = 0.25*( U_8_4 + U_7_5 + U_6_4 + U_7_3 + F_7_4*0.125*0.125 );
    T U_8_4_1 = F_8_4;
    T U_0_5_1 = F_0_5;
    T U_1_5_1 = 0.25*( U_2_5 + U_1_6 + U_0_5 + U_1_4 + F_1_5*0.125*0.125 );
    T U_2_5_1 = 0.25*( U_3_5 + U_2_6 + U_1_5 + U_2_4 + F_2_5*0.125*0.125 );
    T U_3_5_1 = 0.25*( U_4_5 + U_3_6 + U_2_5 + U_3_4 + F_3_5*0.125*0.125 );
    T U_4_5_1 = 0.25*( U_5_5 + U_4_6 + U_3_5 + U_4_4 + F_4_5*0.125*0.125 );
    T U_5_5_1 = 0.25*( U_6_5 + U_5_6 + U_4_5 + U_5_4 + F_5_5*0.125*0.125 );
    T U_6_5_1 = 0.25*( U_7_5 + U_6_6 + U_5_5 + U_6_4 + F_6_5*0.125*0.125 );
    T U_7_5_1 = 0.25*( U_8_5 + U_7_6 + U_6_5 + U_7_4 + F_7_5*0.125*0.125 );
    T U_8_5_1 = F_8_5;
    T U_0_6_1 = F_0_6;
    T U_1_6_1 = 0.25*( U_2_6 + U_1_7 + U_0_6 + U_1_5 + F_1_6*0.125*0.125 );
    T U_2_6_1 = 0.25*( U_3_6 + U_2_7 + U_1_6 + U_2_5 + F_2_6*0.125*0.125 );
    T U_3_6_1 = 0.25*( U_4_6 + U_3_7 + U_2_6 + U_3_5 + F_3_6*0.125*0.125 );
    T U_4_6_1 = 0.25*( U_5_6 + U_4_7 + U_3_6 + U_4_5 + F_4_6*0.125*0.125 );
    T U_5_6_1 = 0.25*( U_6_6 + U_5_7 + U_4_6 + U_5_5 + F_5_6*0.125*0.125 );
    T U_6_6_1 = 0.25*( U_7_6 + U_6_7 + U_5_6 + U_6_5 + F_6_6*0.125*0.125 );
    T U_7_6_1 = 0.25*( U_8_6 + U_7_7 + U_6_6 + U_7_5 + F_7_6*0.125*0.125 );
    T U_8_6_1 = F_8_6;
    T U_0_7_1 = F_0_7;
    T U_1_7_1 = 0.25*( U_2_7 + U_1_8 + U_0_7 + U_1_6 + F_1_7*0.125*0.125 );
    T U_2_7_1 = 0.25*( U_3_7 + U_2_8 + U_1_7 + U_2_6 + F_2_7*0.125*0.125 );
    T U_3_7_1 = 0.25*( U_4_7 + U_3_8 + U_2_7 + U_3_6 + F_3_7*0.125*0.125 );
    T U_4_7_1 = 0.25*( U_5_7 + U_4_8 + U_3_7 + U_4_6 + F_4_7*0.125*0.125 );
    T U_5_7_1 = 0.25*( U_6_7 + U_5_8 + U_4_7 + U_5_6 + F_5_7*0.125*0.125 );
    T U_6_7_1 = 0.25*( U_7_7 + U_6_8 + U_5_7 + U_6_6 + F_6_7*0.125*0.125 );
    T U_7_7_1 = 0.25*( U_8_7 + U_7_8 + U_6_7 + U_7_6 + F_7_7*0.125*0.125 );
    T U_8_7_1 = F_8_7;
    T U_0_8_1 = F_0_8;
    T U_1_8_1 = F_1_8;
    T U_2_8_1 = F_2_8;
    T U_3_8_1 = F_3_8;
    T U_4_8_1 = F_4_8;
    T U_5_8_1 = F_5_8;
    T U_6_8_1 = F_6_8;
    T U_7_8_1 = F_7_8;
    T U_8_8_1 = F_8_8;

    T norm_1 = ((U_0_0_1 - uexact_0_0)*(U_0_0_1 - uexact_0_0) + (U_1_0_1 - uexact_1_0)*(U_1_0_1 - uexact_1_0) + (U_2_0_1 - uexact_2_0)*(U_2_0_1 - uexact_2_0) + (U_3_0_1 - uexact_3_0)*(U_3_0_1 - uexact_3_0) + (U_4_0_1 - uexact_4_0)*(U_4_0_1 - uexact_4_0) + (U_5_0_1 - uexact_5_0)*(U_5_0_1 - uexact_5_0) + (U_6_0_1 - uexact_6_0)*(U_6_0_1 - uexact_6_0) + (U_7_0_1 - uexact_7_0)*(U_7_0_1 - uexact_7_0) + (U_8_0_1 - uexact_8_0)*(U_8_0_1 - uexact_8_0) + (U_0_1_1 - uexact_0_1)*(U_0_1_1 - uexact_0_1) + (U_1_1_1 - uexact_1_1)*(U_1_1_1 - uexact_1_1) + (U_2_1_1 - uexact_2_1)*(U_2_1_1 - uexact_2_1) + (U_3_1_1 - uexact_3_1)*(U_3_1_1 - uexact_3_1) + (U_4_1_1 - uexact_4_1)*(U_4_1_1 - uexact_4_1) + (U_5_1_1 - uexact_5_1)*(U_5_1_1 - uexact_5_1) + (U_6_1_1 - uexact_6_1)*(U_6_1_1 - uexact_6_1) + (U_7_1_1 - uexact_7_1)*(U_7_1_1 - uexact_7_1) + (U_8_1_1 - uexact_8_1)*(U_8_1_1 - uexact_8_1) + (U_0_2_1 - uexact_0_2)*(U_0_2_1 - uexact_0_2) + (U_1_2_1 - uexact_1_2)*(U_1_2_1 - uexact_1_2) + (U_2_2_1 - uexact_2_2)*(U_2_2_1 - uexact_2_2) + (U_3_2_1 - uexact_3_2)*(U_3_2_1 - uexact_3_2) + (U_4_2_1 - uexact_4_2)*(U_4_2_1 - uexact_4_2) + (U_5_2_1 - uexact_5_2)*(U_5_2_1 - uexact_5_2) + (U_6_2_1 - uexact_6_2)*(U_6_2_1 - uexact_6_2) + (U_7_2_1 - uexact_7_2)*(U_7_2_1 - uexact_7_2) + (U_8_2_1 - uexact_8_2)*(U_8_2_1 - uexact_8_2) + (U_0_3_1 - uexact_0_3)*(U_0_3_1 - uexact_0_3) + (U_1_3_1 - uexact_1_3)*(U_1_3_1 - uexact_1_3) + (U_2_3_1 - uexact_2_3)*(U_2_3_1 - uexact_2_3) + (U_3_3_1 - uexact_3_3)*(U_3_3_1 - uexact_3_3) + (U_4_3_1 - uexact_4_3)*(U_4_3_1 - uexact_4_3) + (U_5_3_1 - uexact_5_3)*(U_5_3_1 - uexact_5_3) + (U_6_3_1 - uexact_6_3)*(U_6_3_1 - uexact_6_3) + (U_7_3_1 - uexact_7_3)*(U_7_3_1 - uexact_7_3) + (U_8_3_1 - uexact_8_3)*(U_8_3_1 - uexact_8_3) + (U_0_4_1 - uexact_0_4)*(U_0_4_1 - uexact_0_4) + (U_1_4_1 - uexact_1_4)*(U_1_4_1 - uexact_1_4) + (U_2_4_1 - uexact_2_4)*(U_2_4_1 - uexact_2_4) + (U_3_4_1 - uexact_3_4)*(U_3_4_1 - uexact_3_4) + (U_4_4_1 - uexact_4_4)*(U_4_4_1 - uexact_4_4) + (U_5_4_1 - uexact_5_4)*(U_5_4_1 - uexact_5_4) + (U_6_4_1 - uexact_6_4)*(U_6_4_1 - uexact_6_4) + (U_7_4_1 - uexact_7_4)*(U_7_4_1 - uexact_7_4) + (U_8_4_1 - uexact_8_4)*(U_8_4_1 - uexact_8_4) + (U_0_5_1 - uexact_0_5)*(U_0_5_1 - uexact_0_5) + (U_1_5_1 - uexact_1_5)*(U_1_5_1 - uexact_1_5) + (U_2_5_1 - uexact_2_5)*(U_2_5_1 - uexact_2_5) + (U_3_5_1 - uexact_3_5)*(U_3_5_1 - uexact_3_5) + (U_4_5_1 - uexact_4_5)*(U_4_5_1 - uexact_4_5) + (U_5_5_1 - uexact_5_5)*(U_5_5_1 - uexact_5_5) + (U_6_5_1 - uexact_6_5)*(U_6_5_1 - uexact_6_5) + (U_7_5_1 - uexact_7_5)*(U_7_5_1 - uexact_7_5) + (U_8_5_1 - uexact_8_5)*(U_8_5_1 - uexact_8_5) + (U_0_6_1 - uexact_0_6)*(U_0_6_1 - uexact_0_6) + (U_1_6_1 - uexact_1_6)*(U_1_6_1 - uexact_1_6) + (U_2_6_1 - uexact_2_6)*(U_2_6_1 - uexact_2_6) + (U_3_6_1 - uexact_3_6)*(U_3_6_1 - uexact_3_6) + (U_4_6_1 - uexact_4_6)*(U_4_6_1 - uexact_4_6) + (U_5_6_1 - uexact_5_6)*(U_5_6_1 - uexact_5_6) + (U_6_6_1 - uexact_6_6)*(U_6_6_1 - uexact_6_6) + (U_7_6_1 - uexact_7_6)*(U_7_6_1 - uexact_7_6) + (U_8_6_1 - uexact_8_6)*(U_8_6_1 - uexact_8_6) + (U_0_7_1 - uexact_0_7)*(U_0_7_1 - uexact_0_7) + (U_1_7_1 - uexact_1_7)*(U_1_7_1 - uexact_1_7) + (U_2_7_1 - uexact_2_7)*(U_2_7_1 - uexact_2_7) + (U_3_7_1 - uexact_3_7)*(U_3_7_1 - uexact_3_7) + (U_4_7_1 - uexact_4_7)*(U_4_7_1 - uexact_4_7) + (U_5_7_1 - uexact_5_7)*(U_5_7_1 - uexact_5_7) + (U_6_7_1 - uexact_6_7)*(U_6_7_1 - uexact_6_7) + (U_7_7_1 - uexact_7_7)*(U_7_7_1 - uexact_7_7) + (U_8_7_1 - uexact_8_7)*(U_8_7_1 - uexact_8_7) + (U_0_8_1 - uexact_0_8)*(U_0_8_1 - uexact_0_8) + (U_1_8_1 - uexact_1_8)*(U_1_8_1 - uexact_1_8) + (U_2_8_1 - uexact_2_8)*(U_2_8_1 - uexact_2_8) + (U_3_8_1 - uexact_3_8)*(U_3_8_1 - uexact_3_8) + (U_4_8_1 - uexact_4_8)*(U_4_8_1 - uexact_4_8) + (U_5_8_1 - uexact_5_8)*(U_5_8_1 - uexact_5_8) + (U_6_8_1 - uexact_6_8)*(U_6_8_1 - uexact_6_8) + (U_7_8_1 - uexact_7_8)*(U_7_8_1 - uexact_7_8) + (U_8_8_1 - uexact_8_8)*(U_8_8_1 - uexact_8_8)/(9*9)) ;

    if (norm_1 <= tolerance ) {
        conditions[0] = 1;
        res = U_6_1_1 ;
    } else {
        conditions[0] = 0;
        T U_0_0_2 = F_0_0;
        T U_1_0_2 = F_1_0;
        T U_2_0_2 = F_2_0;
        T U_3_0_2 = F_3_0;
        T U_4_0_2 = F_4_0;
        T U_5_0_2 = F_5_0;
        T U_6_0_2 = F_6_0;
        T U_7_0_2 = F_7_0;
        T U_8_0_2 = F_8_0;
        T U_0_1_2 = F_0_1;
        T U_1_1_2 = 0.25*( U_2_1_1 + U_1_2_1 + U_0_1_1 + U_1_0_1 + F_1_1*0.125*0.125 );
        T U_2_1_2 = 0.25*( U_3_1_1 + U_2_2_1 + U_1_1_1 + U_2_0_1 + F_2_1*0.125*0.125 );
        T U_3_1_2 = 0.25*( U_4_1_1 + U_3_2_1 + U_2_1_1 + U_3_0_1 + F_3_1*0.125*0.125 );
        T U_4_1_2 = 0.25*( U_5_1_1 + U_4_2_1 + U_3_1_1 + U_4_0_1 + F_4_1*0.125*0.125 );
        T U_5_1_2 = 0.25*( U_6_1_1 + U_5_2_1 + U_4_1_1 + U_5_0_1 + F_5_1*0.125*0.125 );
        T U_6_1_2 = 0.25*( U_7_1_1 + U_6_2_1 + U_5_1_1 + U_6_0_1 + F_6_1*0.125*0.125 );
        T U_7_1_2 = 0.25*( U_8_1_1 + U_7_2_1 + U_6_1_1 + U_7_0_1 + F_7_1*0.125*0.125 );
        T U_8_1_2 = F_8_1;
        T U_0_2_2 = F_0_2;
        T U_1_2_2 = 0.25*( U_2_2_1 + U_1_3_1 + U_0_2_1 + U_1_1_1 + F_1_2*0.125*0.125 );
        T U_2_2_2 = 0.25*( U_3_2_1 + U_2_3_1 + U_1_2_1 + U_2_1_1 + F_2_2*0.125*0.125 );
        T U_3_2_2 = 0.25*( U_4_2_1 + U_3_3_1 + U_2_2_1 + U_3_1_1 + F_3_2*0.125*0.125 );
        T U_4_2_2 = 0.25*( U_5_2_1 + U_4_3_1 + U_3_2_1 + U_4_1_1 + F_4_2*0.125*0.125 );
        T U_5_2_2 = 0.25*( U_6_2_1 + U_5_3_1 + U_4_2_1 + U_5_1_1 + F_5_2*0.125*0.125 );
        T U_6_2_2 = 0.25*( U_7_2_1 + U_6_3_1 + U_5_2_1 + U_6_1_1 + F_6_2*0.125*0.125 );
        T U_7_2_2 = 0.25*( U_8_2_1 + U_7_3_1 + U_6_2_1 + U_7_1_1 + F_7_2*0.125*0.125 );
        T U_8_2_2 = F_8_2;
        T U_0_3_2 = F_0_3;
        T U_1_3_2 = 0.25*( U_2_3_1 + U_1_4_1 + U_0_3_1 + U_1_2_1 + F_1_3*0.125*0.125 );
        T U_2_3_2 = 0.25*( U_3_3_1 + U_2_4_1 + U_1_3_1 + U_2_2_1 + F_2_3*0.125*0.125 );
        T U_3_3_2 = 0.25*( U_4_3_1 + U_3_4_1 + U_2_3_1 + U_3_2_1 + F_3_3*0.125*0.125 );
        T U_4_3_2 = 0.25*( U_5_3_1 + U_4_4_1 + U_3_3_1 + U_4_2_1 + F_4_3*0.125*0.125 );
        T U_5_3_2 = 0.25*( U_6_3_1 + U_5_4_1 + U_4_3_1 + U_5_2_1 + F_5_3*0.125*0.125 );
        T U_6_3_2 = 0.25*( U_7_3_1 + U_6_4_1 + U_5_3_1 + U_6_2_1 + F_6_3*0.125*0.125 );
        T U_7_3_2 = 0.25*( U_8_3_1 + U_7_4_1 + U_6_3_1 + U_7_2_1 + F_7_3*0.125*0.125 );
        T U_8_3_2 = F_8_3;
        T U_0_4_2 = F_0_4;
        T U_1_4_2 = 0.25*( U_2_4_1 + U_1_5_1 + U_0_4_1 + U_1_3_1 + F_1_4*0.125*0.125 );
        T U_2_4_2 = 0.25*( U_3_4_1 + U_2_5_1 + U_1_4_1 + U_2_3_1 + F_2_4*0.125*0.125 );
        T U_3_4_2 = 0.25*( U_4_4_1 + U_3_5_1 + U_2_4_1 + U_3_3_1 + F_3_4*0.125*0.125 );
        T U_4_4_2 = 0.25*( U_5_4_1 + U_4_5_1 + U_3_4_1 + U_4_3_1 + F_4_4*0.125*0.125 );
        T U_5_4_2 = 0.25*( U_6_4_1 + U_5_5_1 + U_4_4_1 + U_5_3_1 + F_5_4*0.125*0.125 );
        T U_6_4_2 = 0.25*( U_7_4_1 + U_6_5_1 + U_5_4_1 + U_6_3_1 + F_6_4*0.125*0.125 );
        T U_7_4_2 = 0.25*( U_8_4_1 + U_7_5_1 + U_6_4_1 + U_7_3_1 + F_7_4*0.125*0.125 );
        T U_8_4_2 = F_8_4;
        T U_0_5_2 = F_0_5;
        T U_1_5_2 = 0.25*( U_2_5_1 + U_1_6_1 + U_0_5_1 + U_1_4_1 + F_1_5*0.125*0.125 );
        T U_2_5_2 = 0.25*( U_3_5_1 + U_2_6_1 + U_1_5_1 + U_2_4_1 + F_2_5*0.125*0.125 );
        T U_3_5_2 = 0.25*( U_4_5_1 + U_3_6_1 + U_2_5_1 + U_3_4_1 + F_3_5*0.125*0.125 );
        T U_4_5_2 = 0.25*( U_5_5_1 + U_4_6_1 + U_3_5_1 + U_4_4_1 + F_4_5*0.125*0.125 );
        T U_5_5_2 = 0.25*( U_6_5_1 + U_5_6_1 + U_4_5_1 + U_5_4_1 + F_5_5*0.125*0.125 );
        T U_6_5_2 = 0.25*( U_7_5_1 + U_6_6_1 + U_5_5_1 + U_6_4_1 + F_6_5*0.125*0.125 );
        T U_7_5_2 = 0.25*( U_8_5_1 + U_7_6_1 + U_6_5_1 + U_7_4_1 + F_7_5*0.125*0.125 );
        T U_8_5_2 = F_8_5;
        T U_0_6_2 = F_0_6;
        T U_1_6_2 = 0.25*( U_2_6_1 + U_1_7_1 + U_0_6_1 + U_1_5_1 + F_1_6*0.125*0.125 );
        T U_2_6_2 = 0.25*( U_3_6_1 + U_2_7_1 + U_1_6_1 + U_2_5_1 + F_2_6*0.125*0.125 );
        T U_3_6_2 = 0.25*( U_4_6_1 + U_3_7_1 + U_2_6_1 + U_3_5_1 + F_3_6*0.125*0.125 );
        T U_4_6_2 = 0.25*( U_5_6_1 + U_4_7_1 + U_3_6_1 + U_4_5_1 + F_4_6*0.125*0.125 );
        T U_5_6_2 = 0.25*( U_6_6_1 + U_5_7_1 + U_4_6_1 + U_5_5_1 + F_5_6*0.125*0.125 );
        T U_6_6_2 = 0.25*( U_7_6_1 + U_6_7_1 + U_5_6_1 + U_6_5_1 + F_6_6*0.125*0.125 );
        T U_7_6_2 = 0.25*( U_8_6_1 + U_7_7_1 + U_6_6_1 + U_7_5_1 + F_7_6*0.125*0.125 );
        T U_8_6_2 = F_8_6;
        T U_0_7_2 = F_0_7;
        T U_1_7_2 = 0.25*( U_2_7_1 + U_1_8_1 + U_0_7_1 + U_1_6_1 + F_1_7*0.125*0.125 );
        T U_2_7_2 = 0.25*( U_3_7_1 + U_2_8_1 + U_1_7_1 + U_2_6_1 + F_2_7*0.125*0.125 );
        T U_3_7_2 = 0.25*( U_4_7_1 + U_3_8_1 + U_2_7_1 + U_3_6_1 + F_3_7*0.125*0.125 );
        T U_4_7_2 = 0.25*( U_5_7_1 + U_4_8_1 + U_3_7_1 + U_4_6_1 + F_4_7*0.125*0.125 );
        T U_5_7_2 = 0.25*( U_6_7_1 + U_5_8_1 + U_4_7_1 + U_5_6_1 + F_5_7*0.125*0.125 );
        T U_6_7_2 = 0.25*( U_7_7_1 + U_6_8_1 + U_5_7_1 + U_6_6_1 + F_6_7*0.125*0.125 );
        T U_7_7_2 = 0.25*( U_8_7_1 + U_7_8_1 + U_6_7_1 + U_7_6_1 + F_7_7*0.125*0.125 );
        T U_8_7_2 = F_8_7;
        T U_0_8_2 = F_0_8;
        T U_1_8_2 = F_1_8;
        T U_2_8_2 = F_2_8;
        T U_3_8_2 = F_3_8;
        T U_4_8_2 = F_4_8;
        T U_5_8_2 = F_5_8;
        T U_6_8_2 = F_6_8;
        T U_7_8_2 = F_7_8;
        T U_8_8_2 = F_8_8;

        T norm_2 = ((U_0_0_2 - uexact_0_0)*(U_0_0_2 - uexact_0_0) + (U_1_0_2 - uexact_1_0)*(U_1_0_2 - uexact_1_0) + (U_2_0_2 - uexact_2_0)*(U_2_0_2 - uexact_2_0) + (U_3_0_2 - uexact_3_0)*(U_3_0_2 - uexact_3_0) + (U_4_0_2 - uexact_4_0)*(U_4_0_2 - uexact_4_0) + (U_5_0_2 - uexact_5_0)*(U_5_0_2 - uexact_5_0) + (U_6_0_2 - uexact_6_0)*(U_6_0_2 - uexact_6_0) + (U_7_0_2 - uexact_7_0)*(U_7_0_2 - uexact_7_0) + (U_8_0_2 - uexact_8_0)*(U_8_0_2 - uexact_8_0) + (U_0_1_2 - uexact_0_1)*(U_0_1_2 - uexact_0_1) + (U_1_1_2 - uexact_1_1)*(U_1_1_2 - uexact_1_1) + (U_2_1_2 - uexact_2_1)*(U_2_1_2 - uexact_2_1) + (U_3_1_2 - uexact_3_1)*(U_3_1_2 - uexact_3_1) + (U_4_1_2 - uexact_4_1)*(U_4_1_2 - uexact_4_1) + (U_5_1_2 - uexact_5_1)*(U_5_1_2 - uexact_5_1) + (U_6_1_2 - uexact_6_1)*(U_6_1_2 - uexact_6_1) + (U_7_1_2 - uexact_7_1)*(U_7_1_2 - uexact_7_1) + (U_8_1_2 - uexact_8_1)*(U_8_1_2 - uexact_8_1) + (U_0_2_2 - uexact_0_2)*(U_0_2_2 - uexact_0_2) + (U_1_2_2 - uexact_1_2)*(U_1_2_2 - uexact_1_2) + (U_2_2_2 - uexact_2_2)*(U_2_2_2 - uexact_2_2) + (U_3_2_2 - uexact_3_2)*(U_3_2_2 - uexact_3_2) + (U_4_2_2 - uexact_4_2)*(U_4_2_2 - uexact_4_2) + (U_5_2_2 - uexact_5_2)*(U_5_2_2 - uexact_5_2) + (U_6_2_2 - uexact_6_2)*(U_6_2_2 - uexact_6_2) + (U_7_2_2 - uexact_7_2)*(U_7_2_2 - uexact_7_2) + (U_8_2_2 - uexact_8_2)*(U_8_2_2 - uexact_8_2) + (U_0_3_2 - uexact_0_3)*(U_0_3_2 - uexact_0_3) + (U_1_3_2 - uexact_1_3)*(U_1_3_2 - uexact_1_3) + (U_2_3_2 - uexact_2_3)*(U_2_3_2 - uexact_2_3) + (U_3_3_2 - uexact_3_3)*(U_3_3_2 - uexact_3_3) + (U_4_3_2 - uexact_4_3)*(U_4_3_2 - uexact_4_3) + (U_5_3_2 - uexact_5_3)*(U_5_3_2 - uexact_5_3) + (U_6_3_2 - uexact_6_3)*(U_6_3_2 - uexact_6_3) + (U_7_3_2 - uexact_7_3)*(U_7_3_2 - uexact_7_3) + (U_8_3_2 - uexact_8_3)*(U_8_3_2 - uexact_8_3) + (U_0_4_2 - uexact_0_4)*(U_0_4_2 - uexact_0_4) + (U_1_4_2 - uexact_1_4)*(U_1_4_2 - uexact_1_4) + (U_2_4_2 - uexact_2_4)*(U_2_4_2 - uexact_2_4) + (U_3_4_2 - uexact_3_4)*(U_3_4_2 - uexact_3_4) + (U_4_4_2 - uexact_4_4)*(U_4_4_2 - uexact_4_4) + (U_5_4_2 - uexact_5_4)*(U_5_4_2 - uexact_5_4) + (U_6_4_2 - uexact_6_4)*(U_6_4_2 - uexact_6_4) + (U_7_4_2 - uexact_7_4)*(U_7_4_2 - uexact_7_4) + (U_8_4_2 - uexact_8_4)*(U_8_4_2 - uexact_8_4) + (U_0_5_2 - uexact_0_5)*(U_0_5_2 - uexact_0_5) + (U_1_5_2 - uexact_1_5)*(U_1_5_2 - uexact_1_5) + (U_2_5_2 - uexact_2_5)*(U_2_5_2 - uexact_2_5) + (U_3_5_2 - uexact_3_5)*(U_3_5_2 - uexact_3_5) + (U_4_5_2 - uexact_4_5)*(U_4_5_2 - uexact_4_5) + (U_5_5_2 - uexact_5_5)*(U_5_5_2 - uexact_5_5) + (U_6_5_2 - uexact_6_5)*(U_6_5_2 - uexact_6_5) + (U_7_5_2 - uexact_7_5)*(U_7_5_2 - uexact_7_5) + (U_8_5_2 - uexact_8_5)*(U_8_5_2 - uexact_8_5) + (U_0_6_2 - uexact_0_6)*(U_0_6_2 - uexact_0_6) + (U_1_6_2 - uexact_1_6)*(U_1_6_2 - uexact_1_6) + (U_2_6_2 - uexact_2_6)*(U_2_6_2 - uexact_2_6) + (U_3_6_2 - uexact_3_6)*(U_3_6_2 - uexact_3_6) + (U_4_6_2 - uexact_4_6)*(U_4_6_2 - uexact_4_6) + (U_5_6_2 - uexact_5_6)*(U_5_6_2 - uexact_5_6) + (U_6_6_2 - uexact_6_6)*(U_6_6_2 - uexact_6_6) + (U_7_6_2 - uexact_7_6)*(U_7_6_2 - uexact_7_6) + (U_8_6_2 - uexact_8_6)*(U_8_6_2 - uexact_8_6) + (U_0_7_2 - uexact_0_7)*(U_0_7_2 - uexact_0_7) + (U_1_7_2 - uexact_1_7)*(U_1_7_2 - uexact_1_7) + (U_2_7_2 - uexact_2_7)*(U_2_7_2 - uexact_2_7) + (U_3_7_2 - uexact_3_7)*(U_3_7_2 - uexact_3_7) + (U_4_7_2 - uexact_4_7)*(U_4_7_2 - uexact_4_7) + (U_5_7_2 - uexact_5_7)*(U_5_7_2 - uexact_5_7) + (U_6_7_2 - uexact_6_7)*(U_6_7_2 - uexact_6_7) + (U_7_7_2 - uexact_7_7)*(U_7_7_2 - uexact_7_7) + (U_8_7_2 - uexact_8_7)*(U_8_7_2 - uexact_8_7) + (U_0_8_2 - uexact_0_8)*(U_0_8_2 - uexact_0_8) + (U_1_8_2 - uexact_1_8)*(U_1_8_2 - uexact_1_8) + (U_2_8_2 - uexact_2_8)*(U_2_8_2 - uexact_2_8) + (U_3_8_2 - uexact_3_8)*(U_3_8_2 - uexact_3_8) + (U_4_8_2 - uexact_4_8)*(U_4_8_2 - uexact_4_8) + (U_5_8_2 - uexact_5_8)*(U_5_8_2 - uexact_5_8) + (U_6_8_2 - uexact_6_8)*(U_6_8_2 - uexact_6_8) + (U_7_8_2 - uexact_7_8)*(U_7_8_2 - uexact_7_8) + (U_8_8_2 - uexact_8_8)*(U_8_8_2 - uexact_8_8)/(9*9)) ;

        if (norm_2 <= tolerance) {
            conditions[1] = 1;
            res = U_6_1_2 ;
        }
        else {
            conditions[1] = 0;
            T U_0_0_3 = F_0_0;
            T U_1_0_3 = F_1_0;
            T U_2_0_3 = F_2_0;
            T U_3_0_3 = F_3_0;
            T U_4_0_3 = F_4_0;
            T U_5_0_3 = F_5_0;
            T U_6_0_3 = F_6_0;
            T U_7_0_3 = F_7_0;
            T U_8_0_3 = F_8_0;
            T U_0_1_3 = F_0_1;
            T U_1_1_3 = 0.25*( U_2_1_2 + U_1_2_2 + U_0_1_2 + U_1_0_2 + F_1_1*0.125*0.125 );
            T U_2_1_3 = 0.25*( U_3_1_2 + U_2_2_2 + U_1_1_2 + U_2_0_2 + F_2_1*0.125*0.125 );
            T U_3_1_3 = 0.25*( U_4_1_2 + U_3_2_2 + U_2_1_2 + U_3_0_2 + F_3_1*0.125*0.125 );
            T U_4_1_3 = 0.25*( U_5_1_2 + U_4_2_2 + U_3_1_2 + U_4_0_2 + F_4_1*0.125*0.125 );
            T U_5_1_3 = 0.25*( U_6_1_2 + U_5_2_2 + U_4_1_2 + U_5_0_2 + F_5_1*0.125*0.125 );
            T U_6_1_3 = 0.25*( U_7_1_2 + U_6_2_2 + U_5_1_2 + U_6_0_2 + F_6_1*0.125*0.125 );
            T U_7_1_3 = 0.25*( U_8_1_2 + U_7_2_2 + U_6_1_2 + U_7_0_2 + F_7_1*0.125*0.125 );
            T U_8_1_3 = F_8_1;
            T U_0_2_3 = F_0_2;
            T U_1_2_3 = 0.25*( U_2_2_2 + U_1_3_2 + U_0_2_2 + U_1_1_2 + F_1_2*0.125*0.125 );
            T U_2_2_3 = 0.25*( U_3_2_2 + U_2_3_2 + U_1_2_2 + U_2_1_2 + F_2_2*0.125*0.125 );
            T U_3_2_3 = 0.25*( U_4_2_2 + U_3_3_2 + U_2_2_2 + U_3_1_2 + F_3_2*0.125*0.125 );
            T U_4_2_3 = 0.25*( U_5_2_2 + U_4_3_2 + U_3_2_2 + U_4_1_2 + F_4_2*0.125*0.125 );
            T U_5_2_3 = 0.25*( U_6_2_2 + U_5_3_2 + U_4_2_2 + U_5_1_2 + F_5_2*0.125*0.125 );
            T U_6_2_3 = 0.25*( U_7_2_2 + U_6_3_2 + U_5_2_2 + U_6_1_2 + F_6_2*0.125*0.125 );
            T U_7_2_3 = 0.25*( U_8_2_2 + U_7_3_2 + U_6_2_2 + U_7_1_2 + F_7_2*0.125*0.125 );
            T U_8_2_3 = F_8_2;
            T U_0_3_3 = F_0_3;
            T U_1_3_3 = 0.25*( U_2_3_2 + U_1_4_2 + U_0_3_2 + U_1_2_2 + F_1_3*0.125*0.125 );
            T U_2_3_3 = 0.25*( U_3_3_2 + U_2_4_2 + U_1_3_2 + U_2_2_2 + F_2_3*0.125*0.125 );
            T U_3_3_3 = 0.25*( U_4_3_2 + U_3_4_2 + U_2_3_2 + U_3_2_2 + F_3_3*0.125*0.125 );
            T U_4_3_3 = 0.25*( U_5_3_2 + U_4_4_2 + U_3_3_2 + U_4_2_2 + F_4_3*0.125*0.125 );
            T U_5_3_3 = 0.25*( U_6_3_2 + U_5_4_2 + U_4_3_2 + U_5_2_2 + F_5_3*0.125*0.125 );
            T U_6_3_3 = 0.25*( U_7_3_2 + U_6_4_2 + U_5_3_2 + U_6_2_2 + F_6_3*0.125*0.125 );
            T U_7_3_3 = 0.25*( U_8_3_2 + U_7_4_2 + U_6_3_2 + U_7_2_2 + F_7_3*0.125*0.125 );
            T U_8_3_3 = F_8_3;
            T U_0_4_3 = F_0_4;
            T U_1_4_3 = 0.25*( U_2_4_2 + U_1_5_2 + U_0_4_2 + U_1_3_2 + F_1_4*0.125*0.125 );
            T U_2_4_3 = 0.25*( U_3_4_2 + U_2_5_2 + U_1_4_2 + U_2_3_2 + F_2_4*0.125*0.125 );
            T U_3_4_3 = 0.25*( U_4_4_2 + U_3_5_2 + U_2_4_2 + U_3_3_2 + F_3_4*0.125*0.125 );
            T U_4_4_3 = 0.25*( U_5_4_2 + U_4_5_2 + U_3_4_2 + U_4_3_2 + F_4_4*0.125*0.125 );
            T U_5_4_3 = 0.25*( U_6_4_2 + U_5_5_2 + U_4_4_2 + U_5_3_2 + F_5_4*0.125*0.125 );
            T U_6_4_3 = 0.25*( U_7_4_2 + U_6_5_2 + U_5_4_2 + U_6_3_2 + F_6_4*0.125*0.125 );
            T U_7_4_3 = 0.25*( U_8_4_2 + U_7_5_2 + U_6_4_2 + U_7_3_2 + F_7_4*0.125*0.125 );
            T U_8_4_3 = F_8_4;
            T U_0_5_3 = F_0_5;
            T U_1_5_3 = 0.25*( U_2_5_2 + U_1_6_2 + U_0_5_2 + U_1_4_2 + F_1_5*0.125*0.125 );
            T U_2_5_3 = 0.25*( U_3_5_2 + U_2_6_2 + U_1_5_2 + U_2_4_2 + F_2_5*0.125*0.125 );
            T U_3_5_3 = 0.25*( U_4_5_2 + U_3_6_2 + U_2_5_2 + U_3_4_2 + F_3_5*0.125*0.125 );
            T U_4_5_3 = 0.25*( U_5_5_2 + U_4_6_2 + U_3_5_2 + U_4_4_2 + F_4_5*0.125*0.125 );
            T U_5_5_3 = 0.25*( U_6_5_2 + U_5_6_2 + U_4_5_2 + U_5_4_2 + F_5_5*0.125*0.125 );
            T U_6_5_3 = 0.25*( U_7_5_2 + U_6_6_2 + U_5_5_2 + U_6_4_2 + F_6_5*0.125*0.125 );
            T U_7_5_3 = 0.25*( U_8_5_2 + U_7_6_2 + U_6_5_2 + U_7_4_2 + F_7_5*0.125*0.125 );
            T U_8_5_3 = F_8_5;
            T U_0_6_3 = F_0_6;
            T U_1_6_3 = 0.25*( U_2_6_2 + U_1_7_2 + U_0_6_2 + U_1_5_2 + F_1_6*0.125*0.125 );
            T U_2_6_3 = 0.25*( U_3_6_2 + U_2_7_2 + U_1_6_2 + U_2_5_2 + F_2_6*0.125*0.125 );
            T U_3_6_3 = 0.25*( U_4_6_2 + U_3_7_2 + U_2_6_2 + U_3_5_2 + F_3_6*0.125*0.125 );
            T U_4_6_3 = 0.25*( U_5_6_2 + U_4_7_2 + U_3_6_2 + U_4_5_2 + F_4_6*0.125*0.125 );
            T U_5_6_3 = 0.25*( U_6_6_2 + U_5_7_2 + U_4_6_2 + U_5_5_2 + F_5_6*0.125*0.125 );
            T U_6_6_3 = 0.25*( U_7_6_2 + U_6_7_2 + U_5_6_2 + U_6_5_2 + F_6_6*0.125*0.125 );
            T U_7_6_3 = 0.25*( U_8_6_2 + U_7_7_2 + U_6_6_2 + U_7_5_2 + F_7_6*0.125*0.125 );
            T U_8_6_3 = F_8_6;
            T U_0_7_3 = F_0_7;
            T U_1_7_3 = 0.25*( U_2_7_2 + U_1_8_2 + U_0_7_2 + U_1_6_2 + F_1_7*0.125*0.125 );
            T U_2_7_3 = 0.25*( U_3_7_2 + U_2_8_2 + U_1_7_2 + U_2_6_2 + F_2_7*0.125*0.125 );
            T U_3_7_3 = 0.25*( U_4_7_2 + U_3_8_2 + U_2_7_2 + U_3_6_2 + F_3_7*0.125*0.125 );
            T U_4_7_3 = 0.25*( U_5_7_2 + U_4_8_2 + U_3_7_2 + U_4_6_2 + F_4_7*0.125*0.125 );
            T U_5_7_3 = 0.25*( U_6_7_2 + U_5_8_2 + U_4_7_2 + U_5_6_2 + F_5_7*0.125*0.125 );
            T U_6_7_3 = 0.25*( U_7_7_2 + U_6_8_2 + U_5_7_2 + U_6_6_2 + F_6_7*0.125*0.125 );
            T U_7_7_3 = 0.25*( U_8_7_2 + U_7_8_2 + U_6_7_2 + U_7_6_2 + F_7_7*0.125*0.125 );
            T U_8_7_3 = F_8_7;
            T U_0_8_3 = F_0_8;
            T U_1_8_3 = F_1_8;
            T U_2_8_3 = F_2_8;
            T U_3_8_3 = F_3_8;
            T U_4_8_3 = F_4_8;
            T U_5_8_3 = F_5_8;
            T U_6_8_3 = F_6_8;
            T U_7_8_3 = F_7_8;
            T U_8_8_3 = F_8_8;

            T norm_3 = ((U_0_0_3 - uexact_0_0)*(U_0_0_3 - uexact_0_0) + (U_1_0_3 - uexact_1_0)*(U_1_0_3 - uexact_1_0) + (U_2_0_3 - uexact_2_0)*(U_2_0_3 - uexact_2_0) + (U_3_0_3 - uexact_3_0)*(U_3_0_3 - uexact_3_0) + (U_4_0_3 - uexact_4_0)*(U_4_0_3 - uexact_4_0) + (U_5_0_3 - uexact_5_0)*(U_5_0_3 - uexact_5_0) + (U_6_0_3 - uexact_6_0)*(U_6_0_3 - uexact_6_0) + (U_7_0_3 - uexact_7_0)*(U_7_0_3 - uexact_7_0) + (U_8_0_3 - uexact_8_0)*(U_8_0_3 - uexact_8_0) + (U_0_1_3 - uexact_0_1)*(U_0_1_3 - uexact_0_1) + (U_1_1_3 - uexact_1_1)*(U_1_1_3 - uexact_1_1) + (U_2_1_3 - uexact_2_1)*(U_2_1_3 - uexact_2_1) + (U_3_1_3 - uexact_3_1)*(U_3_1_3 - uexact_3_1) + (U_4_1_3 - uexact_4_1)*(U_4_1_3 - uexact_4_1) + (U_5_1_3 - uexact_5_1)*(U_5_1_3 - uexact_5_1) + (U_6_1_3 - uexact_6_1)*(U_6_1_3 - uexact_6_1) + (U_7_1_3 - uexact_7_1)*(U_7_1_3 - uexact_7_1) + (U_8_1_3 - uexact_8_1)*(U_8_1_3 - uexact_8_1) + (U_0_2_3 - uexact_0_2)*(U_0_2_3 - uexact_0_2) + (U_1_2_3 - uexact_1_2)*(U_1_2_3 - uexact_1_2) + (U_2_2_3 - uexact_2_2)*(U_2_2_3 - uexact_2_2) + (U_3_2_3 - uexact_3_2)*(U_3_2_3 - uexact_3_2) + (U_4_2_3 - uexact_4_2)*(U_4_2_3 - uexact_4_2) + (U_5_2_3 - uexact_5_2)*(U_5_2_3 - uexact_5_2) + (U_6_2_3 - uexact_6_2)*(U_6_2_3 - uexact_6_2) + (U_7_2_3 - uexact_7_2)*(U_7_2_3 - uexact_7_2) + (U_8_2_3 - uexact_8_2)*(U_8_2_3 - uexact_8_2) + (U_0_3_3 - uexact_0_3)*(U_0_3_3 - uexact_0_3) + (U_1_3_3 - uexact_1_3)*(U_1_3_3 - uexact_1_3) + (U_2_3_3 - uexact_2_3)*(U_2_3_3 - uexact_2_3) + (U_3_3_3 - uexact_3_3)*(U_3_3_3 - uexact_3_3) + (U_4_3_3 - uexact_4_3)*(U_4_3_3 - uexact_4_3) + (U_5_3_3 - uexact_5_3)*(U_5_3_3 - uexact_5_3) + (U_6_3_3 - uexact_6_3)*(U_6_3_3 - uexact_6_3) + (U_7_3_3 - uexact_7_3)*(U_7_3_3 - uexact_7_3) + (U_8_3_3 - uexact_8_3)*(U_8_3_3 - uexact_8_3) + (U_0_4_3 - uexact_0_4)*(U_0_4_3 - uexact_0_4) + (U_1_4_3 - uexact_1_4)*(U_1_4_3 - uexact_1_4) + (U_2_4_3 - uexact_2_4)*(U_2_4_3 - uexact_2_4) + (U_3_4_3 - uexact_3_4)*(U_3_4_3 - uexact_3_4) + (U_4_4_3 - uexact_4_4)*(U_4_4_3 - uexact_4_4) + (U_5_4_3 - uexact_5_4)*(U_5_4_3 - uexact_5_4) + (U_6_4_3 - uexact_6_4)*(U_6_4_3 - uexact_6_4) + (U_7_4_3 - uexact_7_4)*(U_7_4_3 - uexact_7_4) + (U_8_4_3 - uexact_8_4)*(U_8_4_3 - uexact_8_4) + (U_0_5_3 - uexact_0_5)*(U_0_5_3 - uexact_0_5) + (U_1_5_3 - uexact_1_5)*(U_1_5_3 - uexact_1_5) + (U_2_5_3 - uexact_2_5)*(U_2_5_3 - uexact_2_5) + (U_3_5_3 - uexact_3_5)*(U_3_5_3 - uexact_3_5) + (U_4_5_3 - uexact_4_5)*(U_4_5_3 - uexact_4_5) + (U_5_5_3 - uexact_5_5)*(U_5_5_3 - uexact_5_5) + (U_6_5_3 - uexact_6_5)*(U_6_5_3 - uexact_6_5) + (U_7_5_3 - uexact_7_5)*(U_7_5_3 - uexact_7_5) + (U_8_5_3 - uexact_8_5)*(U_8_5_3 - uexact_8_5) + (U_0_6_3 - uexact_0_6)*(U_0_6_3 - uexact_0_6) + (U_1_6_3 - uexact_1_6)*(U_1_6_3 - uexact_1_6) + (U_2_6_3 - uexact_2_6)*(U_2_6_3 - uexact_2_6) + (U_3_6_3 - uexact_3_6)*(U_3_6_3 - uexact_3_6) + (U_4_6_3 - uexact_4_6)*(U_4_6_3 - uexact_4_6) + (U_5_6_3 - uexact_5_6)*(U_5_6_3 - uexact_5_6) + (U_6_6_3 - uexact_6_6)*(U_6_6_3 - uexact_6_6) + (U_7_6_3 - uexact_7_6)*(U_7_6_3 - uexact_7_6) + (U_8_6_3 - uexact_8_6)*(U_8_6_3 - uexact_8_6) + (U_0_7_3 - uexact_0_7)*(U_0_7_3 - uexact_0_7) + (U_1_7_3 - uexact_1_7)*(U_1_7_3 - uexact_1_7) + (U_2_7_3 - uexact_2_7)*(U_2_7_3 - uexact_2_7) + (U_3_7_3 - uexact_3_7)*(U_3_7_3 - uexact_3_7) + (U_4_7_3 - uexact_4_7)*(U_4_7_3 - uexact_4_7) + (U_5_7_3 - uexact_5_7)*(U_5_7_3 - uexact_5_7) + (U_6_7_3 - uexact_6_7)*(U_6_7_3 - uexact_6_7) + (U_7_7_3 - uexact_7_7)*(U_7_7_3 - uexact_7_7) + (U_8_7_3 - uexact_8_7)*(U_8_7_3 - uexact_8_7) + (U_0_8_3 - uexact_0_8)*(U_0_8_3 - uexact_0_8) + (U_1_8_3 - uexact_1_8)*(U_1_8_3 - uexact_1_8) + (U_2_8_3 - uexact_2_8)*(U_2_8_3 - uexact_2_8) + (U_3_8_3 - uexact_3_8)*(U_3_8_3 - uexact_3_8) + (U_4_8_3 - uexact_4_8)*(U_4_8_3 - uexact_4_8) + (U_5_8_3 - uexact_5_8)*(U_5_8_3 - uexact_5_8) + (U_6_8_3 - uexact_6_8)*(U_6_8_3 - uexact_6_8) + (U_7_8_3 - uexact_7_8)*(U_7_8_3 - uexact_7_8) + (U_8_8_3 - uexact_8_8)*(U_8_8_3 - uexact_8_8)/(9*9)) ;

            if (norm_3 <= tolerance) {
                conditions[2] = 1;
                res = U_6_1_3 ;
            } else {
                conditions[2] = 0;
                res = U_6_1 ;
            }
        }
    }

    return res;
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
	fp = fopen("Poisson_profile.csv", "w+");
    ofstream fp_divergence_inputs;
	fp_divergence_inputs.open("Poisson_divergence_inputs.csv", ios::out | ios::app);

	__float80 val_lp = 0;
	__float80 val_dp = 0;
	__float80 val_qp = 0;
	__float80 err_dp_lp = 0;
	__float80 err_qp_dp = 0;

	__float80 maxerrlp = 0.0;
	__float80 maxerrdp = 0.0;

	int num_predicates = 3;
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
                string str = "instability_lp:" + to_string_with_precision(fabs(val_dp - val_lp), 16) + ",Pred:" + to_string(j) + ",_U_0_1:" + to_string_with_precision(_U_0_1, 16) + ",_U_0_2:" + to_string_with_precision(_U_0_2, 16) + ",_U_0_3:" + to_string_with_precision(_U_0_3, 16) + ",_U_0_4:" + to_string_with_precision(_U_0_4, 16) + ",_U_0_5:" + to_string_with_precision(_U_0_5, 16) + ",_U_0_6:" + to_string_with_precision(_U_0_6, 16) + ",_U_0_7:" + to_string_with_precision(_U_0_7, 16) + ",_U_0_8:" + to_string_with_precision(_U_0_8, 16) + ",_U_1_0:" + to_string_with_precision(_U_1_0, 16) + ",_U_1_1:" + to_string_with_precision(_U_1_1, 16) + ",_U_1_2:" + to_string_with_precision(_U_1_2, 16) + ",_U_1_3:" + to_string_with_precision(_U_1_3, 16) + ",_U_1_4:" + to_string_with_precision(_U_1_4, 16) + ",_U_1_5:" + to_string_with_precision(_U_1_5, 16) + ",_U_1_6:" + to_string_with_precision(_U_1_6, 16) + ",_U_1_7:" + to_string_with_precision(_U_1_7, 16) + ",_U_1_8:" + to_string_with_precision(_U_1_8, 16) + ",_U_2_0:" + to_string_with_precision(_U_2_0, 16) + ",_U_2_1:" + to_string_with_precision(_U_2_1, 16) + ",_U_2_2:" + to_string_with_precision(_U_2_2, 16) + ",_U_2_3:" + to_string_with_precision(_U_2_3, 16) + ",_U_2_4:" + to_string_with_precision(_U_2_4, 16) + ",_U_2_5:" + to_string_with_precision(_U_2_5, 16) + ",_U_2_6:" + to_string_with_precision(_U_2_6, 16) + ",_U_2_7:" + to_string_with_precision(_U_2_7, 16) + ",_U_2_8:" + to_string_with_precision(_U_2_8, 16) + ",_U_3_0:" + to_string_with_precision(_U_3_0, 16) + ",_U_3_1:" + to_string_with_precision(_U_3_1, 16) + ",_U_3_2:" + to_string_with_precision(_U_3_2, 16) + ",_U_3_3:" + to_string_with_precision(_U_3_3, 16) + ",_U_3_4:" + to_string_with_precision(_U_3_4, 16) + ",_U_3_5:" + to_string_with_precision(_U_3_5, 16) + ",_U_3_6:" + to_string_with_precision(_U_3_6, 16) + ",_U_3_7:" + to_string_with_precision(_U_3_7, 16) + ",_U_3_8:" + to_string_with_precision(_U_3_8, 16) + ",_U_4_0:" + to_string_with_precision(_U_4_0, 16) + ",_U_4_1:" + to_string_with_precision(_U_4_1, 16) + ",_U_4_2:" + to_string_with_precision(_U_4_2, 16) + ",_U_4_3:" + to_string_with_precision(_U_4_3, 16) + ",_U_4_4:" + to_string_with_precision(_U_4_4, 16) + ",_U_4_5:" + to_string_with_precision(_U_4_5, 16) + ",_U_4_6:" + to_string_with_precision(_U_4_6, 16) + ",_U_4_7:" + to_string_with_precision(_U_4_7, 16) + ",_U_4_8:" + to_string_with_precision(_U_4_8, 16) + ",_U_5_0:" + to_string_with_precision(_U_5_0, 16) + ",_U_5_1:" + to_string_with_precision(_U_5_1, 16) + ",_U_5_2:" + to_string_with_precision(_U_5_2, 16) + ",_U_5_3:" + to_string_with_precision(_U_5_3, 16) + ",_U_5_4:" + to_string_with_precision(_U_5_4, 16) + ",_U_5_5:" + to_string_with_precision(_U_5_5, 16) + ",_U_5_6:" + to_string_with_precision(_U_5_6, 16) + ",_U_5_7:" + to_string_with_precision(_U_5_7, 16) + ",_U_5_8:" + to_string_with_precision(_U_5_8, 16) + ",_U_6_0:" + to_string_with_precision(_U_6_0, 16) + ",_U_6_1:" + to_string_with_precision(_U_6_1, 16) + ",_U_6_2:" + to_string_with_precision(_U_6_2, 16) + ",_U_6_3:" + to_string_with_precision(_U_6_3, 16) + ",_U_6_4:" + to_string_with_precision(_U_6_4, 16) + ",_U_6_5:" + to_string_with_precision(_U_6_5, 16) + ",_U_6_6:" + to_string_with_precision(_U_6_6, 16) + ",_U_6_7:" + to_string_with_precision(_U_6_7, 16) + ",_U_6_8:" + to_string_with_precision(_U_6_8, 16) + ",_U_7_0:" + to_string_with_precision(_U_7_0, 16) + ",_U_7_1:" + to_string_with_precision(_U_7_1, 16) + ",_U_7_2:" + to_string_with_precision(_U_7_2, 16) + ",_U_7_3:" + to_string_with_precision(_U_7_3, 16) + ",_U_7_4:" + to_string_with_precision(_U_7_4, 16) + ",_U_7_5:" + to_string_with_precision(_U_7_5, 16) + ",_U_7_6:" + to_string_with_precision(_U_7_6, 16) + ",_U_7_7:" + to_string_with_precision(_U_7_7, 16) + ",_U_7_8:" + to_string_with_precision(_U_7_8, 16) + ",_U_8_0:" + to_string_with_precision(_U_8_0, 16) + ",_U_8_1:" + to_string_with_precision(_U_8_1, 16) + ",_U_8_2:" + to_string_with_precision(_U_8_2, 16) + ",_U_8_3:" + to_string_with_precision(_U_8_3, 16) + ",_U_8_4:" + to_string_with_precision(_U_8_4, 16) + ",_U_8_5:" + to_string_with_precision(_U_8_5, 16) + ",_U_8_6:" + to_string_with_precision(_U_8_6, 16) + ",_U_8_7:" + to_string_with_precision(_U_8_7, 16) + ",_U_8_8:" + to_string_with_precision(_U_8_8, 16) + "\n";
                fp_divergence_inputs << str;
                cout << str;
                numinstability_lp[j]++;
                instability_dp_lp[j] += fabs(val_dp - val_lp);
                if ( maxinstabilitylp[j] < fabs(val_dp - val_lp)) maxinstabilitylp[j] = fabs(val_dp - val_lp) ;
            }
            if(conditions_dp[j] != conditions_qp[j] && conditions_dp[j] != -1 && conditions_qp[j] != -1) {
                string str = "instability_dp:" + to_string_with_precision(fabs(val_qp - val_dp), 16) + ",Pred:" + to_string(j) + ",_U_0_1:" + to_string_with_precision(_U_0_1, 16) + ",_U_0_2:" + to_string_with_precision(_U_0_2, 16) + ",_U_0_3:" + to_string_with_precision(_U_0_3, 16) + ",_U_0_4:" + to_string_with_precision(_U_0_4, 16) + ",_U_0_5:" + to_string_with_precision(_U_0_5, 16) + ",_U_0_6:" + to_string_with_precision(_U_0_6, 16) + ",_U_0_7:" + to_string_with_precision(_U_0_7, 16) + ",_U_0_8:" + to_string_with_precision(_U_0_8, 16) + ",_U_1_0:" + to_string_with_precision(_U_1_0, 16) + ",_U_1_1:" + to_string_with_precision(_U_1_1, 16) + ",_U_1_2:" + to_string_with_precision(_U_1_2, 16) + ",_U_1_3:" + to_string_with_precision(_U_1_3, 16) + ",_U_1_4:" + to_string_with_precision(_U_1_4, 16) + ",_U_1_5:" + to_string_with_precision(_U_1_5, 16) + ",_U_1_6:" + to_string_with_precision(_U_1_6, 16) + ",_U_1_7:" + to_string_with_precision(_U_1_7, 16) + ",_U_1_8:" + to_string_with_precision(_U_1_8, 16) + ",_U_2_0:" + to_string_with_precision(_U_2_0, 16) + ",_U_2_1:" + to_string_with_precision(_U_2_1, 16) + ",_U_2_2:" + to_string_with_precision(_U_2_2, 16) + ",_U_2_3:" + to_string_with_precision(_U_2_3, 16) + ",_U_2_4:" + to_string_with_precision(_U_2_4, 16) + ",_U_2_5:" + to_string_with_precision(_U_2_5, 16) + ",_U_2_6:" + to_string_with_precision(_U_2_6, 16) + ",_U_2_7:" + to_string_with_precision(_U_2_7, 16) + ",_U_2_8:" + to_string_with_precision(_U_2_8, 16) + ",_U_3_0:" + to_string_with_precision(_U_3_0, 16) + ",_U_3_1:" + to_string_with_precision(_U_3_1, 16) + ",_U_3_2:" + to_string_with_precision(_U_3_2, 16) + ",_U_3_3:" + to_string_with_precision(_U_3_3, 16) + ",_U_3_4:" + to_string_with_precision(_U_3_4, 16) + ",_U_3_5:" + to_string_with_precision(_U_3_5, 16) + ",_U_3_6:" + to_string_with_precision(_U_3_6, 16) + ",_U_3_7:" + to_string_with_precision(_U_3_7, 16) + ",_U_3_8:" + to_string_with_precision(_U_3_8, 16) + ",_U_4_0:" + to_string_with_precision(_U_4_0, 16) + ",_U_4_1:" + to_string_with_precision(_U_4_1, 16) + ",_U_4_2:" + to_string_with_precision(_U_4_2, 16) + ",_U_4_3:" + to_string_with_precision(_U_4_3, 16) + ",_U_4_4:" + to_string_with_precision(_U_4_4, 16) + ",_U_4_5:" + to_string_with_precision(_U_4_5, 16) + ",_U_4_6:" + to_string_with_precision(_U_4_6, 16) + ",_U_4_7:" + to_string_with_precision(_U_4_7, 16) + ",_U_4_8:" + to_string_with_precision(_U_4_8, 16) + ",_U_5_0:" + to_string_with_precision(_U_5_0, 16) + ",_U_5_1:" + to_string_with_precision(_U_5_1, 16) + ",_U_5_2:" + to_string_with_precision(_U_5_2, 16) + ",_U_5_3:" + to_string_with_precision(_U_5_3, 16) + ",_U_5_4:" + to_string_with_precision(_U_5_4, 16) + ",_U_5_5:" + to_string_with_precision(_U_5_5, 16) + ",_U_5_6:" + to_string_with_precision(_U_5_6, 16) + ",_U_5_7:" + to_string_with_precision(_U_5_7, 16) + ",_U_5_8:" + to_string_with_precision(_U_5_8, 16) + ",_U_6_0:" + to_string_with_precision(_U_6_0, 16) + ",_U_6_1:" + to_string_with_precision(_U_6_1, 16) + ",_U_6_2:" + to_string_with_precision(_U_6_2, 16) + ",_U_6_3:" + to_string_with_precision(_U_6_3, 16) + ",_U_6_4:" + to_string_with_precision(_U_6_4, 16) + ",_U_6_5:" + to_string_with_precision(_U_6_5, 16) + ",_U_6_6:" + to_string_with_precision(_U_6_6, 16) + ",_U_6_7:" + to_string_with_precision(_U_6_7, 16) + ",_U_6_8:" + to_string_with_precision(_U_6_8, 16) + ",_U_7_0:" + to_string_with_precision(_U_7_0, 16) + ",_U_7_1:" + to_string_with_precision(_U_7_1, 16) + ",_U_7_2:" + to_string_with_precision(_U_7_2, 16) + ",_U_7_3:" + to_string_with_precision(_U_7_3, 16) + ",_U_7_4:" + to_string_with_precision(_U_7_4, 16) + ",_U_7_5:" + to_string_with_precision(_U_7_5, 16) + ",_U_7_6:" + to_string_with_precision(_U_7_6, 16) + ",_U_7_7:" + to_string_with_precision(_U_7_7, 16) + ",_U_7_8:" + to_string_with_precision(_U_7_8, 16) + ",_U_8_0:" + to_string_with_precision(_U_8_0, 16) + ",_U_8_1:" + to_string_with_precision(_U_8_1, 16) + ",_U_8_2:" + to_string_with_precision(_U_8_2, 16) + ",_U_8_3:" + to_string_with_precision(_U_8_3, 16) + ",_U_8_4:" + to_string_with_precision(_U_8_4, 16) + ",_U_8_5:" + to_string_with_precision(_U_8_5, 16) + ",_U_8_6:" + to_string_with_precision(_U_8_6, 16) + ",_U_8_7:" + to_string_with_precision(_U_8_7, 16) + ",_U_8_8:" + to_string_with_precision(_U_8_8, 16) + "\n";
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