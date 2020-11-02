

from symengine import *
#import symengine as seng
import math as mt
import sys

from bool_tokens import *

_ARITH_OPS = { PLUS : lambda L : L[0]+L[1]	,\
		  MINUS : lambda L : L[0]-L[1]	,\
		  MUL :	lambda L : L[0]*L[1]	,\
		  DIV : lambda L : L[0]/L[1]	,\
		  POW1	:	lambda L : L[0]**L[1], \
		  SQRT: lambda L : sqrt(L[0])	,\
		  POW2	:	lambda L : L[0]**L[1] \
		  #SIN : lambda L : sin(L[0]),\
		  #COS : lambda L : cos(L[0]),\
		  #LOG :	lambda L : log(L[0]),\
		  #IDEN  : lambda L : L[0], \
		  #EXP : lambda L : exp(L[0]), \
		  #TAN : lambda L : tan(L[0]), \
		  #COT : lambda L : cot(L[0]), \
		  #COSH : lambda L : cosh(L[0]), \
		  #SINH : lambda L : sinh(L[0]), \
		 }

invert = {	\
			LT		:	GEQ	,\
			GT		:	LEQ	,\
			LEQ		:	GT	,\
			GEQ		:	LT	,\
			EQ		:	NEQ	,\
			NEQ		:	EQ ,\
			AND		:	OR	,\
			OR		:	AND \
}

_INEQ_OPS = { \
		LEQ		:	lambda L	:	L[0] <= L[1] ,\
		LT		:	lambda L	:	L[0] < L[1] ,\
		GEQ		:	lambda L	:	L[1] <= L[0] ,\
		GT		:	lambda L	:	L[1] < L[0] \
}

_BINARY_OPS = { \
		AND		:	lambda L	:	L[0] & L[1]	, \
		OR		:	lambda L	:	L[0] | L[1] \
}
