import symengine as seng
import sympy as sym
import Globals


opLimit = 8000

class PredSymbol(object):

	__slots__ = ['exprCond']

	def __init__(self, expr, cond=Globals.__T__):
		self.exprCond = (expr, cond)

	def __add__(self, obj):
		symexpr = (self.exprCond[0] + obj.exprCond[0])
		return PredSymbol( symexpr.expand() if seng.count_ops(symexpr) > opLimit else symexpr , \
				 (self.exprCond[1] & obj.exprCond[1]).simplify())

	def __sub__(self, obj):
		symexpr = (self.exprCond[0] - obj.exprCond[0])
		return PredSymbol( symexpr.expand() if seng.count_ops(symexpr) > opLimit else symexpr , \
				 (self.exprCond[1] & obj.exprCond[1]).simplify())

	def __mul__(self, obj):
		symexpr = (self.exprCond[0] * obj.exprCond[0])
		return PredSymbol( symexpr.expand() if seng.count_ops(symexpr) > opLimit else symexpr , \
				 (self.exprCond[1] & obj.exprCond[1]).simplify())

	def __truediv__(self, obj):
		symexpr = (self.exprCond[0] / obj.exprCond[0])
		return PredSymbol( symexpr.expand() if seng.count_ops(symexpr) > opLimit else symexpr , \
				 (self.exprCond[1] & obj.exprCond[1]).simplify())

	def __floordiv__(self, obj):
		symexpr = (self.exprCond[0] // obj.exprCond[0])
		return PredSymbol( symexpr.expand() if seng.count_ops(symexpr) > opLimit else symexpr , \
				 (self.exprCond[1] &  obj.exprCond[1]).simplify())

	def __mod__(self, obj):
		return PredSymbol( (self.exprCond[0] % obj.exprCond[0]).expand() , \
				 (self.exprCond[1] & obj.exprCond[1]).simplify())

	def __cos__(self):
		return PredSymbol( (seng.cos(self.exprCond[0]),	\
							self.exprCond[1]) )

	def __sin__(self):
		return PredSymbol( (seng.sin(self.exprCond[0]),	\
							self.exprCond[1]) )

	def __exp__(self):
		return PredSymbol( (seng.exp(self.exprCond[0]),	\
							self.exprCond[1]) )

	def __and__(self, condSym):
		return PredSymbol( (self.exprCond[0], (exprCond[1] & condSym).simplify()) )

	def __str__(self):
		return '(Expr: {expr} , Cond: {cond})'.format( \
												expr = self.exprCond[0], \
												cond = self.exprCond[1] \
												)

	def __repr__(self):
		return self.__str__()


class PSList(list):
	def __init__(self, *args, **kwargs):
		super(PSList, self).__init__(args[0])

	def __add__(self, other):
		return PSList([self[i]+other[j] for i in range(len(self)) for j in range(len(other))])

	def __sub__(self, other):
		return PSList([self[i]-other[j] for i in range(len(self)) for j in range(len(other))])

	def __mul__(self, other):
		return PSList([self[i]*other[j] for i in range(len(self)) for j in range(len(other))])

	def __truediv__(self, other):
		return PSList([self[i]/other[j] for i in range(len(self)) for j in range(len(other))])

	def __floordiv__(self, other):
		return PSList([self[i]//other[j] for i in range(len(self)) for j in range(len(other))])

	def __mod__(self, other):
		return PSList([self[i]%other[j] for i in range(len(self)) for j in range(len(other))])

	def __cos__(self):
		return PSList([self[i].__cos__() for i in range(len(self))])

	def __sin__(self):
		return PSList([self[i].__sin__() for i in range(len(self))])

	def __exp__(self):
		return PSList([self[i].__exp__() for i in range(len(self))])

	def __and__(self, condSym):
		return PSList([self[i].__and__(condSym) for i in range(len(self))])

	def __concat__(self, other):
		return PSList(list(self) + list(other))
		



	def __str__(self):
		return '[ {exp_cond_list} ]'.format( \
							exp_cond_list = ','.join([self[i].__str__() for i in range(len(self))]) \
							)

	def __repr__(self):
		return self.__str__()




class Sym(object):

	def __init__(self, expr='', cond=Globals.__T__):
		self.exprCond = (expr, cond)

	def __add__(self, obj):
		symexpr = self.exprCond[0] + obj.exprCond[0]
		return Sym( seng.expand(symexpr) if seng.count_ops(symexpr) < 8000 else symexpr	,\
				(self.exprCond[1] & obj.exprCond[1]).simplify() )

	def __sub__(self, obj):
		symexpr = self.exprCond[0] - obj.exprCond[0]
		return Sym( seng.expand(symexpr) if seng.count_ops(symexpr) < 8000 else symexpr ,\
				(self.exprCond[1] & obj.exprCond[1]).simplify() )

	def __mul__(self, obj):
		symexpr = self.exprCond[0] * obj.exprCond[0]
		return Sym( seng.expand(symexpr) if seng.count_ops(symexpr) < 8000 else symexpr	,\
				(self.exprCond[1] & obj.exprCond[1]).simplify() )

	def __truediv__(self, obj):
		symexpr = self.exprCond[0] / obj.exprCond[0]
		return Sym( seng.expand(symexpr) if seng.count_ops(symexpr) < 8000 else symexpr	,\
				(self.exprCond[1] & obj.exprCond[1]).simplify() )

	def __floordiv__(self, obj):
		symexpr = self.exprCond[0] // obj.exprCond[0]
		return Sym( seng.expand(symexpr) if seng.count_ops(symexpr) < 8000 else symexpr	,\
				(self.exprCond[1] & obj.exprCond[1]).simplify() )

	def __mod__(self, obj):
		symexpr = self.exprCond[0] % obj.exprCond[0]
		return Sym( seng.expand(symexpr) if seng.count_ops(symexpr) < 8000 else symexpr	,\
				(self.exprCond[1] & obj.exprCond[1]).simplify() )

	def __cos__(self):
		return Sym( seng.cos(self.exprCond[0])	,\
				self.exprCond[1]  )

	def __sin__(self):
		return Sym( seng.sin(self.exprCond[0])	,\
				self.exprCond[1] )

	def __exp__(self):
		return Sym( seng.exp(self.exprCond[0])	,\
				self.exprCond[1] )

	def __and__(self, condSym):
		return Sym( self.exprCond[0], (self.exprCond[1] & condSym) )

	def __eq__(self, other):
		return True if(self.exprCond[1]==other.exprCond[1] and \
			           self.exprCond[0]==other.exprCond[0] \
			            ) \
			         else False

	def __lt__(self, other):
		assert(self.exprCond[1]==other.exprCond[1])
		return (self.exprCond[0] < other.exprCond[0]) 
		

	def __leq__(self, other):
		assert(self.exprCond[1]==other.exprCond[1])
		return (self.exprCond[0] <= other.exprCond[0])

	def __hash__(self):
		return hash(tuple(self.exprCond))



	def __str__(self):
		return '(Expr: {expr} , Cond : {cond})'.format( \
												expr = self.exprCond[0], \
												cond = self.exprCond[1] \
											)

	def __repr__(self):
		return self.__str__()

class SymTup(tuple):
	def __new__(self, tup):
		return tuple.__new__(SymTup, tup)

	def __add__(self, obj):
		return  SymTup((fl+sl for fl in self for sl in obj))

	def __sub__(self, obj):
		return  SymTup((fl-sl for fl in self for sl in obj))

	def __mul__(self, obj):
		return  SymTup((fl*sl for fl in self for sl in obj))

	def __truediv__(self, obj):
		return  SymTup((fl/sl for fl in self for sl in obj))

	def __floordiv__(self, obj):
		return  SymTup((fl//sl for fl in self for sl in obj))

	def __mod__(self, obj):
		return  SymTup((fl%sl for fl in self for sl in obj))

	def __cos__(self):
		return  SymTup((fl.__cos__() for fl in self))

	def __sin__(self):
		return  SymTup((fl.__sin__() for fl in self))

	def __exp__(self):
		return  SymTup((fl.__exp__() for fl in self))

	def __and__(self, condSym):
		return SymTup((fl.__and__(condSym) for fl in self))

	
	def __concat__(self, other):
		return SymTup(tuple(self) + tuple(other))
	

	def __str__(self):
		return 'Tup( {expr_cond_list} )'.format( \
				expr_cond_list = ','.join([self[i].__str__() for i in range(len(self))]) \
				)

	def __repr__(self):
		return self.__str__()


def	SymConcat(t1, t2):
	## atleast either t1 or t2 must be non-empry
	return t1 if len(t2)==0 else t2 if len(t1)==0 else SymTup(tuple(t1) + tuple(t2))


def lambda_add():
	return lambda x : x[0] + x[1]

if __name__ == "__main__":
	x = sym.symbols('x')
	y = sym.symbols('y')
	z = sym.symbols('z')

	a1 = PredSymbol((x+y)*(x-y), ~x & y)
	a2 = PredSymbol((x+y-z*x), (~y | ~x))
	a3 = PredSymbol((3.5), (~z | ~x))

	l1 = PSList([a1,a2])
	l2 = PSList([a3])

	res = lambda_add()
	print("a1 :", a1)
	#print("overload-sym:", res([a1,a2]))
	print("overload-sym:", a1/a2)
	#print(type(l1), type(l2))
	print("overload symList:", ((l1+l2)/(l1*l2)))
	#print("carry forward symList:", (l1+l2)+(l1))
	print("type:", type(l1+l2))
	
