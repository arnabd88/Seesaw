
import symengine as seng
from bool_tokens import *
from sly import Lexer
import numpy as np

class bool_lexer(Lexer):

	tokens = { INTEGER, FLOAT, MINF, PINF, PLUS, MINUS, POW1, POW2, SQRT,\
			   MUL, DIV, EQ, NEQ, ASSIGN, LPAREN, RPAREN, \
			   SEMICOLON, ID, AND, OR, NOT, \
			   LEQ, LT, GEQ, GT, \
			   LANG, RANG, \
			   BTRUE, BFALSE \
			 }

	ignore = ' \t'
	ignore_comment = r'\#.*'

	# regular expressions
	PLUS		=	r'\+'
	POW1		=	r'\*\*'
	POW2		=	r'\^'
	MUL			=	r'\*'
	DIV			=	r'\/'
	EQ			=	r'\=='
	NEQ			=	r'\!='
	ASSIGN		=	r'\='
	LPAREN		=	r'\('
	RPAREN		=	r'\)'
	SEMICOLON	=	r'\;'
	AND			=	r'\&&'
	OR			=	r'\|\|'
	NOT			=	r'\~'
	LANG		=	r'\<\<'
	RANG		=	r'\>\>'
	LEQ			=	r'\<='
	LT			=	r'\<'
	GEQ			=	r'\>='
	GT			=	r'\>'

	PINF		= 	r'inf(\.\d)?'

	ID			=	r'[a-zA-Z_][a-zA-Z0-9_]*'
	ID['TRUE']	=	BTRUE
	ID['True']	=	BTRUE
	ID['true']	=	BTRUE
	ID['FALSE'] =	BFALSE
	ID['False'] =	BFALSE
	ID['false'] =	BFALSE
	ID['sqrt']	=	SQRT

	current_token = None
	tok = None

	def ID(self, t):
		t.value = seng.var(t.value)
		return t

	@_(r'-inf(\.\d)?')
	def MINF(self, t):
		t.value = -np.inf
		t.type = FLOAT
		return t

	@_(r'inf(\.\d)?')
	def PINF(self, t):
		t.value = np.inf
		t.type = FLOAT
		return t

	@_(r'[\-]?\d+[\.]?\d+([eE][-+]?\d+)?')
	def FLOAT(self, t):
		t.value = float(t.value)
		return t

#	@_(r'[\-]?\d+[eE]([-+]?\d+)?')
#	def FLOAT(self, t):
#		t.value = float(t.value)
#		return t


	#@_(r'[\-]?\d+')
	@_(r'[\-]?\d+([eE][-+]?\d+)?')
	def INTEGER(self, t):
		t.value = int(t.value)
		t.type = INTEGER
		return t	

	MINUS	=	r'\-'


	@_(r'\n+')
	def ignore_newline(self, t):
		self.lineno += t.value.count('\n')

	def error(self, t):
		print('Line %d: Bad character %r' % (self.lineno, t.value[0]), t)
		raise Exception("Incorrect Lexing")

	def create_token_generator(self, text):
		self.tok = self.tokenize(text)

	def get_current_token(self):
		return self.current_token

	def get_next_token(self):
		try:
			return self.tok.__next__()
		except StopIteration:
			return None


if __name__ == "__main__":
	import sys
	text = open(sys.argv[1], 'r').read()
	lexer = bool_lexer()

	tok = lexer.tokenize(text)

	cnt = 0
	while(1):
		try:
			x = tok.__next__()
			print(x)
			cnt += 1
		except StopIteration:
			print(None)
			break
	print('Token count =', cnt)
	print('Num Lines =', lexer.lineno)




