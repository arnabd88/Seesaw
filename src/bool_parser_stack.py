

from bool_tokens import *
from bool_lexer import bool_lexer
import bool_Globals
from bool_asttypes import *
from collections import deque

import sympy

import sys

import time

class bool_parser(object):

	tokens = bool_lexer.tokens

	__slots__ = ['lexer', 'current_token', 'constr_tbl', 'stack']

	def __init__(self, lexer):
		self.lexer = lexer
		self.current_token = None
		self.constr_tbl = dict()
		self.stack = deque()

	def error(self):
		raise Exception('Invalid Syntax while parsing')

	def consume(self, token_type):
		print(self.current_token.type, token_type, self.current_token.value)
		if self.current_token.type == token_type:
			self.current_token = self.lexer.get_next_token()
		else:
			self.error()


	def cond_expr(self):
		"""
		cond_expr : cond_term ((||) cond_term)*
		"""
		node = self.cond_term()

		while self.current_token is not None and self.current_token.type==OR:
			token = self.current_token
			self.consume(OR)

			node = bool_BinOp(left=node, token=token, right=self.cond_term())
		return node

	def cond_term(self):
		"""
		cond_term :  cond_factor ((&&) cond_factor)*
		"""

		node = self.cond_factor()

		while self.current_token is not None and self.current_token.type == AND:
			token = self.current_token
			self.consume(AND)

			node = bool_BinOp(left=node, token=token, right=self.cond_factor())
		return node

	def cond_factor(self):
		"""
		cond_factor : (Constraint) | (cond_expr)
		"""
		token = self.current_token
		if token.type in (ID,INTEGER,FLOAT):
			node = self.constraint_term()
			return node
		elif token.type == LPAREN:
			self.consume(LPAREN)
			self.stack.append(LPAREN)
			stk_len = len(self.stack)
			node = self.cond_expr()
			if stk_len == len(self.stack):
				self.consume(RPAREN)
				self.stack.pop()
			else:
				pass
			return node
		else:
			self.error()

	
	def constraint_term(self):
		node1 = self.arith_expr()
		
		# to handle matching right parenthesis
		if self.current_token.type == RPAREN:
			self.stack.pop()
			self.consume(RPAREN)

		if self.current_token.type in (LEQ, LT, GEQ, GT, EQ, NEQ):
			ineq_token = self.current_token
			self.consume(self.current_token.type)
		else:
			self.error()

		node2 = self.arith_expr()

		CID = sympy.var("CID_"+str(bool_Globals.ConstraintID))
		node = bool_Constraint(left=node1, token=ineq_token, right=node2, cid=CID)
		expr = node.f_expression
		inv_expr = node.eval(node,inv=True)
		#print("expr and inv-expr:", expr, inv_expr, id(node), type(node.f_expression))

		pos_ret_tup = bool_Globals.ExprPosConstr.get(expr)
		inv_pos_ret_tup = bool_Globals.ExprPosConstr.get(inv_expr)
		neg_ret_tup = bool_Globals.ExprNegConstr.get(expr)
		inv_neg_ret_tup = bool_Globals.ExprNegConstr.get(inv_expr)

		if pos_ret_tup is not None and inv_pos_ret_tup is not None:
			pass
		elif pos_ret_tup is not None and inv_pos_ret_tup is None:
			bool_Globals.ExprNegConstr[inv_expr] = bool_Constraint(left=node2, token=ineq_token, right=node1, cid=~(pos_ret_tup.CID))
		elif neg_ret_tup is  not None and inv_neg_ret_tup is not None:
			pass
		elif neg_ret_tup is not None and inv_neg_ret_tup is None:
			bool_Globals.ExprPosConstr[inv_expr] = bool_Constraint(left=node2, token=ineq_token, right=node1, cid=~(neg_ret_tup.CID))
		else:
			inv_node = bool_Constraint(left=node2, token=ineq_token, right=node1, cid=~CID)
			bool_Globals.ConstraintID += 1
			bool_Globals.ExprPosConstr[expr] = node
			bool_Globals.ExprNegConstr[inv_expr] = inv_node



		#if expr in bool_Globals.ExprPosConstr.keys():
		#	ret_tup = bool_Globals.ExprPosConstr[expr]  ## ret_tup -> ( obj, CID)
		#	if inv_expr in bool_Globals.ExprNegConstr.keys():
		#		pass
		#	else:
		#		bool_Globals.ExprNegConstr[inv_expr] = (bool_Constraint(left=node2, token=ineq_token, right=node1), \
		#		                                        ~(ret_tup[1]))
		#	node = ret_tup[0]
		#elif expr in bool_Globals.ExprNegConstr.keys():
		#	ret_tup = bool_Globals.ExprNegConstr[expr]
		#	if inv_expr in bool_Globals.ExprPosConstr.keys():
		#		pass
		#	else:
		#		bool_Globals.ExprPosConstr[inv_expr] = (bool_Constraint(left=node2, token=ineq_token, right=node1), \
		#												~(ret_tup[1]))
		#	node = ret_tup[0]
		#else:
		#	inv_node = bool_Constraint(left=node2, token=ineq_token, right=node1)
		#	CID = sympy.var("CID_"+str(bool_Globals.ConstraintID))
		#	bool_Globals.ConstraintID += 1
		#	bool_Globals.ExprPosConstr[expr] = (node, CID)
		#	bool_Globals.ExprNegConstr[inv_expr] = (inv_node, ~CID)


		return node

	
	def arith_expr(self):
		"""
		expr	:	term ( (PLUS|MINUS) term )*
		"""

		node = self.arith_term()
		if self.current_token is not None and self.current_token.type==RPAREN:
			self.consume(RPAREN)
			self.stack.pop()
		while self.current_token is not None and self.current_token.type in (PLUS, MINUS):
			token = self.current_token
			self.consume(token.type)
			node = arith_BinOp(left=node, token=token, right=self.arith_term())
		return node

	def arith_term(self):
		"""
		term	:	factor ( (MUL|DIV) factor )*
		"""

		node = self.arith_factor()
		if self.current_token is not None and self.current_token.type==RPAREN:
			self.consume(RPAREN)
			self.stack.pop()
		while self.current_token is not None and self.current_token.type in (MUL,DIV):
			token = self.current_token
			self.consume(token.type)
			node = arith_BinOp(left=node, token=token, right=self.arith_factor())
		return node

	def arith_factor(self):
		token = self.current_token
		if self.current_token is not None and token.type in (INTEGER, FLOAT):
			self.consume(token.type)
			return bool_Num(token)
		elif token.type == LPAREN:
			self.consume(LPAREN)
			self.stack.append(LPAREN)
			stk_len = len(self.stack)
			node = self.arith_expr()
			if stk_len == len(self.stack):
				self.consume(RPAREN)
				self.stack.pop()
			else:
				pass
			return node
		else:
			node = bool_Var(token)
			self.consume(ID)
			## Add logic for the power operator here
			if self.current_token.type in (POW1, POW2):
				local_token = self.current_token
				self.consume(local_token.type)
				node = arith_BinOp(left=node, token=local_token, right=self.arith_factor())
				#print("POW_WOW:", node.f_expression, type(node.children[1]))
			return node
		

	def program(self):
		return self.cond_expr()

	def parse(self, text):
		self.lexer.create_token_generator(text)
		self.current_token = self.lexer.get_next_token()
		return self.program()

if __name__ == "__main__":
	start_parse_time = time.time()
	text = open(sys.argv[1], 'r').read()
	lexer = bool_lexer()
	parser = bool_parser(lexer)
	root = parser.parse(text)
	end_parse_time = time.time()
	print("Parsing time -> {parse_time}\n".format(parse_time=end_parse_time-start_parse_time))
	print(bool_Globals.ExprPosConstr)
	print("\n\n")
	print(bool_Globals.ExprNegConstr)
