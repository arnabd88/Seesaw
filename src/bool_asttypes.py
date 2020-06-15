

from bool_tokens import *
import bool_ops


class bool_ast(object):

	__slots__ = ['depth', 'f_expression', 'children' \
	             ]

	def __init__(self):
		self.depth = 0
		self.f_expression = None
		self.children = ()
		#self.parents = ()
		#self.f_expression = self.eval(self)

	def eval(obj, inv=False):
		return obj.f_expression

	def set_expression(self, expr):
		self.f_expression = expr









class bool_empty(bool_ast):
	pass









class bool_Num(bool_ast):

	__slots__ = ['token']
	def __init__(self, token):
		super().__init__()
		self.token = token
		self.f_expression = self.eval(self)

	@staticmethod
	def eval(obj, inv=False):
		return obj.token.value








class bool_Var(bool_ast):
	
	__slots__ = ['token']

	def __init__(self, token):
		super().__init__()
		self.token = token
		self.f_expression = self.eval(self)

	@staticmethod
	def eval(obj, inv=False):
		name = str(obj.token.value)
		return obj.token.value
		## look-up is not necessary here since pre-defs are not required
		## this is only a one-time read for expressions



class bool_BinOp(bool_ast):

	__slots__ = ['token']

	def __init__(self, left, token, right):
		super().__init__()
		assert(type(left).__name__ in ("bool_BinOp", "bool_Constraint"))
		assert(type(right).__name__ in ("bool_BinOp", "bool_Constraint"))
		self.token = token
		self.children = (left, right)
		#left.parents += (self,)
		#right.parents += (self,)
		#self.f_expression = self.eval(self)

	@staticmethod
	def eval(obj, inv=False):
		if inv:
			lexpr = False if obj.token.type==BTRUE else \
			        True if obj.token.type==BFALSE else \
					bool_ops._BINARY_OPS[ops.invert[obj.token.type]]([child.self.eval(obj.child, inv=True) for child in obj.children])
		else:
			#print(obj.children[0].f_expression)
			#print(obj.children[1].f_expression)
			lexpr = True if obj.token.type==BTRUE else \
			        False if obj.token.type==BFALSE else \
					bool_ops._BINARY_OPS[obj.token.type]([child.f_expression for child in obj.children])
		return lexpr






class arith_TransOp(bool_ast):

	__slots__ = ['token']
	def __init__(self, right, token):
		super().__init__()
		self.token = token
		self.depth = right.depth+1
		self.children = (right,)
		#self.children[0].parents += (self,)
		self.f_expression = self.eval(self)

	@staticmethod
	def eval(obj, inv=False):
		lexpr = bool_ops._ARITH_OPS[obj.token.type]([obj.children[0].f_expression])
		obj.depth = obj.children[0].depth +1

		return lexpr






class arith_BinOp(bool_ast):

	__slots__ = ['token']
	def __init__(self, left, token, right):
		super().__init__()
		self.token = token
		self.children = (left, right)
		self.depth = max(left.depth, right.depth) +1
		#left.parents += (self,)
		#right.parents += (self,)
		self.f_expression = self.eval(self)

	@staticmethod
	def eval(obj,inv=False):
		lexpr = bool_ops._ARITH_OPS[obj.token.type]([child.f_expression for child in obj.children])
		obj.depth = max([child.depth for child in obj.children]) +1
		return lexpr











class bool_Constraint(bool_ast):

	__slots__ = ['token','CID']

	def __init__(self, left, token, right, cid):
		#if token.type in (LEQ, LT):
		#	self.children = (left, right)
		#	self.token = token
		#	self.token.type = LEQ
		#elif token.type in (GEQ, GT):
		#	self.children = (right, left)
		#	self.token = token
		#	self.token.type = LEQ
		#elif token.type in (EQ, NEQ):
		#	self.children = (left, right)
		#	self.token = token
		#else:
		#	self.error()
		self.children = (left, right)
		self.token = token
		self.depth = max([child.depth for child in self.children]) +1
		#left.parents += (self,)
		#right.parents += (self,)
		self.f_expression = self.eval(self)
		self.CID = cid

	@staticmethod
	def eval(obj,inv=False):

		opList = [child.f_expression for child in obj.children]
		if inv:
			opList.reverse()
			lexpr = False if obj.token.type==BTRUE else \
			        True if obj.token.type==BFALSE else \
					bool_ops._INEQ_OPS[obj.token.type](opList)
			obj.depth = max([child.depth for child in obj.children]) +1
		else:
			lexpr = True if obj.token.type==BTRUE else \
			        False if obj.token.type==BFALSE else \
					bool_ops._INEQ_OPS[obj.token.type](opList)
			obj.depth = max([child.depth for child in obj.children]) +1
		#print("BCR:", lexpr, [child.f_expression for child in obj.children])
		return lexpr
		
		

		
