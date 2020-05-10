import Globals 

import sympy as sym
import symengine as seng
import ops_def as ops

from gtokens import *

from functools import reduce
from PredicatedSymbol import Sym, SymTup, SymConcat


class CToken(object):
	'''
	Representation of a single token.
	'''
	__slots__ = ('type', 'value', 'lineno', 'index')
	def __init__(self, tp, value):
		self.type = tp
		self.value = value
		self.lineno = None
		self.index = None


##-- Base AST class
class AST(object):

	__slots__ = ['depth', 'f_expression', 'children', \
	             'parents', 'noise', 'rnd', 'cond', 'nodeList']

	def __init__(self, cond=Globals.__T__):
		self.depth = 0
		self.f_expression = None
		self.children = ()
		self.parents = ()
		self.noise = (0,0)
		self.rnd = 1.0
		self.cond = cond
		self.nodeList = []

	def set_expression(self, fexpr):
		self.f_expression = fexpr

	def eval(obj):
		return obj.f_expression

	@staticmethod
	def get_noise(obj):
		return obj.f_expression if obj.f_expression is not None else 0.0

	@staticmethod
	def rec_eval(obj):
		return obj.eval(obj)

	def set_rounding(self, rnd_type):
		self.rnd = ops._FP_RND[rnd_type]

	def get_rounding(self):
		return self.rnd * 1.0






##-- EmptyNode
class EmptyNode(AST):
	pass





##-- Numeric Node	
class Num(AST):
	__slots__ = ['token']

	def __init__(self, token, cond=Globals.__T__):
		super().__init__()
		self.token = token
		self.f_expression = self.eval(self)
		self.rnd = 0.0
		self.cond = cond

	@staticmethod
	def eval(obj):
		return  SymTup((Sym( obj.token.value, Globals.__T__),))
		#return obj.token.value

	@staticmethod
	def get_noise(obj):
		return 0.0





##-- FreeVariable
class FreeVar(AST):
	__slots__ = ['token']
	def __init__(self, token, cond=Globals.__T__):
		super().__init__()
		self.token = token
		self.cond = cond


	@staticmethod
	def eval(obj, round_mode="fl64"):
		name = str(obj.token.value)
		obj.depth = 0
		intv = Globals.inputVars.get(obj.token.value, None)
		if intv is not None and (intv["INTV"][0]==intv["INTV"][1]):
			return SymTup((Sym( intv["INTV"][0], Globals.__T__),))
			#return intv["INTV"][0]
		else:
			return SymTup((Sym(obj.token.value, Globals.__T__),))

	
	#@staticmethod
	#def get_noise(obj):
	#	return 0.0

	@staticmethod
	def set_noise(obj, value):
		obj.noise = value

	@staticmethod
	def get_noise(obj):
		return abs(obj.noise[0])


	def mutate_to_abstract(self, tvalue, tid):
		self.token.value = tvalue #SymTup((Sym(tvalue, Globals.__T__), ))
		self.token.type = tid ;







##-- Var Nodes
class Var(AST):
	__slots__ = ['token']
	def __init__(self, token, cond=Globals.__T__):
		super().__init__()
		self.token = token
		self.cond = cond

	@staticmethod
	def eval(obj, round_mode="fl64"):
		nodeList = Globals.GS[0]._symTab.get(obj.token.value, None)
		if nodeList is None:
			return SymTup((Sym(obj.token.value, Globals.__T__),))
		else:
			clist = [n[0].f_expression.__and__(n[1])  for n in obj.nodeList]
			f = lambda x, y: SymConcat(x,y)
			return reduce(f, clist)
			#return SymTup( n[0].f_expression.__and__(n[1])  for n in nodeList  )
			
			
			









##-- Creates a lifted node taking a list of (node, conds)
class LiftOp(AST):
	__slots__ = ['token']
	def __init__(self, nodeList, token, cond=Globals.__T__):
		super().__init__()
		self.token = CToken('IF', value=None)
#		self.token.type = IF
		self.depth = max([n[0].depth for n in nodeList]) +1
		self.nodeList = nodeList
		self.children = [n[0] for n in nodeList]
		self.cond = cond
		for n in nodeList:
			n[0].parents += (self, )
		#print(nodeList)

	@staticmethod
	def eval(obj):
		
		clist = [n[0].f_expression.__and__(n[1])  for n in obj.nodeList]
		f = lambda x, y: SymConcat(x,y)
		return reduce(f, clist)

		#return SymTup( n[0].f_expression.__and__(n[1])  for n in obj.nodeList  )

	@staticmethod
	def rec_eval(obj):
		
		obj.depth = max([n[0].depth for n in obj.nodeList]) +1
		clist = [n[0].rec_eval(n[0]).__and__(n[1])  for n in obj.nodeList]
		f = lambda x, y: SymConcat(x,y)
		return reduce(f, clist)


	@staticmethod
	def get_noise(obj):
		return 0.0











##-- Transcendental and special ops
class TransOp(AST):
	__slots__ = ['token']
	def __init__(self, right, token, cond=Globals.__T__):
		super().__init__()
		self.token = token
		self.cond = cond
		self.depth = right.depth+1
		self.children = (right, )
		right.parents += (self, )

	@staticmethod
	def eval(obj):
		lexpr = ops._FOPS[obj.token.type]([obj.children[0].f_expression])
		obj.depth = obj.children[0].depth +1
		obj.rnd = obj.children[0].rnd

		return lexpr

	@staticmethod
	def rec_eval(obj):
		lexpr = ops._FOPS[obj.token.type]([obj.children[0].rec_eval(obj.children[0])])
		obj.depth = obj.children[0].depth +1
		obj.rnd = obj.children[0].rnd
		return lexpr



	def get_rounding(self):
		return self.rnd * ops._ALLOC_ULP[self.token.type]









##-- corresponds to arith binary
class BinOp(AST):
	__slots__ = ['token']
	def __init__(self, left, token, right, cond=Globals.__T__):
		super().__init__()
		self.token = token
		self.cond=cond
		self.children = (left, right, )
		self.depth = max(left.depth, right.depth) +1
		left.parents += (self,)
		right.parents += (self, )

	@staticmethod
	def eval(obj):
		#print(obj.token.value, [child.f_expression for child in obj.children])
		lexpr = ops._FOPS[obj.token.type]([child.f_expression for child in obj.children])
		obj.depth = max([child.depth for child in obj.children])+1
		obj.rnd = max([min([child.rnd for child in obj.children]), 1.0])

		return lexpr


	@staticmethod
	def rec_eval(obj):
		lexpr = ops._FOPS[obj.token.type]([child.rec_eval(child) for child in obj.children])
		obj.depth = max([child.depth for child in obj.children])+1
		obj.rnd = max([min([child.rnd for child in obj.children]), 1.0])

		return lexpr
		

	def get_rounding(self):
		return self.rnd * ops._ALLOC_ULP[self.token.type]











##-- Binary Literal
class BinLiteral(AST):
	__slots__ = ['token']
	def __init__(self, left, token, right):
		super().__init__()
		self.token = token
		self.children = (left, right, )
		self.depth = max(left.depth, right.depth) +1
		left.parents += (self,)
		right.parents += (self,)

		#self.f_expression = self.eval(self)

#	@staticmethod
#	def eval(obj):
#		lexpr = ops._BOPS[obj.token.type]([obj.children[0].f_expression, obj.children[1].f_expression])
#		obj.depth = max([child.depth for child in obj.children])+1
#		return lexpr
#
#
#	@staticmethod
#	def rec_eval(obj):
#		lexpr = ops._BOPS[obj.token.type]([obj.children[0].rec_eval(obj.children[0]), obj.children[1].rec_eval(obj.children[1])])
#		obj.depth = max([child.depth for child in obj.children])+1
#		return lexpr


	@staticmethod
	def eval(obj):
		obj.depth = max([child.depth for child in obj.children])+1
		lstr = obj.children[0].f_expression
		rstr = obj.children[1].f_expression

		litexpr = ops._BOPS[obj.token.type]([lstr,rstr])

		return litexpr



	@staticmethod
	def rec_eval(obj):
		obj.depth = max([child.depth for child in obj.children])+1
		lstr = obj.children[0].rec_eval(obj.children[0])
		rstr = obj.children[1].rec_eval(obj.children[1])

		litexpr = ops._BOPS[obj.token.type]([lstr,rstr])

		return litexpr
		











##-- Comparison Operators
class ExprComp(AST):
	__slots__ = ['token', 'condSym']
	def __init__(self, left, token, right):
		super().__init__()
		self.token=token
		self.children = (left, right,)
		self.depth = max([left.depth, right.depth])+1
		left.parents += (self, )
		right.parents += (self, )
		self.condSym = sym.var("ES"+str(Globals.EID))
		Globals.EID += 1
		Globals.condTable[self.condSym] = self

		## have the f_expressions evaluted early for conds
		#self.f_expression = self.eval(self)

	@staticmethod
	def mod_eval(obj, err0, err1):
		obj.depth = max([child.depth for child in obj.children])+1
		lstrTup = obj.children[0].f_expression
		rstrTup = obj.children[1].f_expression
		free_syms = lstrTup.__freeSyms__().union(rstrTup.__freeSyms__())

		cexpr = tuple(set(ops._MCOPS[obj.token.type]([fl.exprCond[0],\
											 sl.exprCond[0], err0, err1]) \
											 for fl in lstrTup \
										     for sl in rstrTup))
		if ("(True)" in cexpr):
			return ("(True)",0)
		else:
			l1 = list(filter(lambda x: x!="(False)", cexpr))
			#free_syms = reduce(lambda x, y: x.union(y), [el.exprCond[0].free_symbols for el in l1 if (seng.count_ops(el.exprCond[0]) > 0)], set())
			return ("(False)",0) if len(l1)==0 else ("({comp_expr})".format( comp_expr = "|".join(l1)), free_syms)


		return "|".join(cexpr)

	@staticmethod
	def eval(obj):
		obj.depth = max([child.depth for child in obj.children])+1
		lstrTup = obj.children[0].f_expression
		rstrTup = obj.children[1].f_expression

		cexpr = tuple(set(ops._COPS[obj.token.type]([fl.exprCond[0],\
											 sl.exprCond[0]]) \
											 for fl in lstrTup \
										     for sl in rstrTup))

		return "|".join(cexpr)

	@staticmethod
	def rec_eval(obj):
		obj.depth = max([child.depth for child in obj.children])+1
		lstrTup = obj.children[0].rec_eval(obj.children[0])
		rstrTup = obj.children[1].rec_eval(obj.children[1])

		#print(lstrTup, rstrTup)

		cexpr = tuple(set(ops._COPS[obj.token.type]([fl.exprCond[0],\
											 sl.exprCond[0]]) \
											 for fl in lstrTup \
										     for sl in rstrTup))

		return "|".join(cexpr)


	#@staticmethod
	#def eval(obj):
	#	lexpr = ops._COPS[obj.token.type]([obj.children[0].f_expression, obj.children[1].f_expression])
	#	obj.depth = max([child.depth for child in obj.children])+1
	#	return lexpr

	#@staticmethod
	#def rec_eval(obj):
	#	lexpr = ops._COPS[obj.token.type]([obj.children[0].rec_eval(obj.children[0]), obj.children[1].rec_eval(obj.children[1])])
	#	obj.depth = max([child.depth for child in obj.children])+1
	#	return lexpr


