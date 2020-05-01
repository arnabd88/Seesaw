
import Globals
import sympy 
import symengine as seng

from PredicatedSymbol import Sym, SymTup, SymConcat
from functools import reduce


class SymbolTable(object):

	__slots__ = ['_symTab', '_scope', '_scopeCond']

	def __init__(self, scope=0, cond=Globals.__T__, caller_symTab=None):
		self._scope = scope
		self._symTab = {}
		self._scopeCond = cond
		self._symTab['_caller_'] = caller_symTab

	def insert(self, symbol, nodeCondTup):
		self._symTab[symbol] = nodeCondTup

	def lookup(self, symbol):
		if self._symTab['_caller_'] is None:
			return self._symTab.get(symbol)
			
		return self._symTab.get(symbol, self._symTab['_caller_'].lookup(symbol))
