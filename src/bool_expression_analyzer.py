
from bool_lexer import bool_lexer
from bool_parser import bool_parser
import bool_Globals

from bool_tokens import *

import bool_ops as ops

import symengine as seng
from sympy.logic.boolalg import to_cnf, is_cnf
from sympy.logic import simplify_logic
from functools import reduce

from collections import defaultdict
import time
import sys

# 1. generate parse tree
# 2. generate the boolean literal expression
# 3. convert to CNF


class bool_expression_analyzer(object):


	def __init__(self, constraintStr):
		lexer = bool_lexer()
		parser = bool_parser(lexer)
		print("Bool_expr_ans:", constraintStr)
		self.root = parser.parse(constraintStr)

	def error(self):
		raise Exception('Invalid Operational Syntax reached')

	def build_boolean_expression(self, node, reachable=set()):
		
		if type(node).__name__ == "bool_Constraint":
			if node.token.type in (BTRUE, BFALSE):
				node.set_expression(node.eval(node))
			else:
				node.set_expression(node.CID)
				reachable.add(node)
			return
		
		#print(node==self.root, type(node))#, node.children)
		for child in node.children:
			if not reachable.__contains__(child):
				self.build_boolean_expression(child, reachable)

		node.set_expression(node.eval(node))
		reachable.add(node)


	def traverse(self, cnf_expression):

		# reached a leaf boolean node
		print(cnf_expression)
		if cnf_expression==True or cnf_expression==False or len(cnf_expression.args)==0 or type(cnf_expression).__name__ == "Not":
			node = bool_Globals.ConstraintToObject.get(cnf_expression)
			#print(cnf_expression)
			if node is None:
				return (cnf_expression,)
			if node.token.type in (LT, LEQ):
				exprStr = ((node.children[0].f_expression - node.children[1].f_expression),)
			elif node.token.type in (GT, GEQ):
				exprStr = ((node.children[1].f_expression - node.children[0].f_expression),)
			else:
				self.error()
			#print("Leaf: ", cnf_expression, exprStr)
			return exprStr
		exprList = ()
		for arg in cnf_expression.args:
			exprList += (self.traverse(arg),)

		if type(cnf_expression).__name__ == 'Or':
			#exprList = [seng.Min(exprList[0][0], exprList[1][0])]
			exprList = tuple(map(lambda xxc : xxc[0], exprList))
			exprList = exprList if len(exprList)==1 else (reduce(lambda x,y : seng.Min(x,y), exprList),)
		elif type(cnf_expression).__name__ == 'And':
			#exprList = exprList[0]+exprList[1]
			exprList = reduce(lambda x,y : x+y, exprList, tuple())
		else:
			self.error()

		return exprList
			

	def updateConstraintToObject(self):
		bool_Globals.ConstraintToObject =  {v.CID : v for k,v in bool_Globals.ExprPosConstr.items()}
		bool_Globals.ConstraintToObject.update({v.CID : v for k,v in bool_Globals.ExprNegConstr.items()})

	def get_cnf_expression(self, expr):
		return expr if is_cnf(expr) else to_cnf(expr)

	def compose_rp_constraint(self, exprList):
		#print(len(exprList), exprList)
		if len(exprList)==1 and exprList[0] in (True, False):
			return str(exprList[0])
		else:
			exprList = [str(i)+" <= 0" for i in exprList]
			return (",".join(exprList)+";")
	
	def create_rp_constraint(self):
		reachable = set()
		self.build_boolean_expression(self.root, reachable)
		cnf_expression = self.get_cnf_expression(self.root.f_expression)
		self.updateConstraintToObject()
		exprList = self.traverse(cnf_expression)
		rpConstraint = self.compose_rp_constraint(exprList)
		#print("To RP:", rpConstraint)
		return rpConstraint
		
		

## return types:
## 1: Queue of boxes
## 2: True
## 3: False

	def start(self):
		
		self.rpConstraint = self.create_rp_constraint()
		return self.rpConstraint

if __name__ == "__main__":
	start_parse_time = time.time()
	text = open(sys.argv[1], 'r').read()
	#lexer = bool_lexer()
	#parser = bool_parser(lexer)
	#root = parser.parse(text)
	#end_parse_time = time.time()
	#print("Parsing time -> {parse_time}\n".format(parse_time=end_parse_time-start_parse_time))
	#print(bool_Globals.ExprPosConstr)
	#print("\n\n")
	#print(bool_Globals.ExprNegConstr)


	analyzer = bool_expression_analyzer(text)
	analyzer.start()
	end_analysis_time = time.time()
	print("Analysis time -> {analysis_time}\n".format(analysis_time=end_analysis_time-start_parse_time))
