
import Globals
import math
import sympy as sym
import symengine as seng
from collections import defaultdict
from SymbolTable import *


def getProbeList():
	return [Globals.GS[0]._symTab[outVar] for outVar in Globals.outVars]


def dfs_expression_builder(node, reachable, parent_dict, cond):

	for child in node.children:
		if not reachable[node.depth].__contains__(child):
			dfs_expression_builder(child, reachable, parent_dict, cond=Globals.__T__)

		parent_dict[child].append(node)

	#print(type(node).__name__, node.token)
	fexpr = node.eval(node)
	print(node.depth, fexpr)
	node.set_expression(fexpr)



def expression_builder(probeList):

	parent_dict = defaultdict(list)
	reachable = defaultdict(set)

	for nodeList in probeList:
		assert(len(nodeList)==1)
		[node,cond] = nodeList[0]
		if not reachable[node.depth].__contains__(node):
			dfs_expression_builder(node, reachable, parent_dict, cond)
	

def pretraverse(node, reachable):
	
	for child in node.children:
		#print("child", child, type(node).__name__)
		if reachable[child.depth].__contains__(child):
			pass
		else:
			pretraverse(child, reachable)

	reachable[node.depth].add(node)


def PreProcessAST():

	probeList = getProbeList()
	reachable = defaultdict(set)

	rhstbl = {}
	#print("\n\n", Globals.GS[0]._symTab[seng.var('g')])
	#glift = Globals.GS[0]._symTab[seng.var('g')][0][0]
	#for child in glift.children:
	#	print(child)


	for k,v in Globals.GS[0]._symTab.items():
		rhstbl[v] = k

	for nodeList in probeList:
		assert(len(nodeList)==1)
		[node,cond] = nodeList[0]
		if not reachable[node.depth].__contains__(node):
			pretraverse(node, reachable)

	print("Pre :", len(Globals.GS[0]._symTab))
	Globals.GS[0]._symTab = {syms: tuple(n for n in nodeCondList \
										if reachable[n[0].depth].__contains__(n[0])) \
										for nodeCondList,syms in rhstbl.items() }
	print("Post :", len(Globals.GS[0]._symTab))
	print(Globals.GS[0]._symTab[seng.var('g')])
	prev_numNodes = sum([ len(Globals.depthTable[el]) for el in Globals.depthTable.keys() if el!=0] )
	Globals.depthTable = reachable
	curr_numNodes = sum([ len(Globals.depthTable[el]) for el in Globals.depthTable.keys() if el!=0] )
	print("Total number of nodes pre-processing: {prev}".format(prev=prev_numNodes))
	print("Total number of nodes post-processing: {curr}".format(curr=curr_numNodes))
	


def	parallelConcat(t1, t2):
	## atleast either t1 or t2 must be non-empry
	return t1 if len(t2)==0 else t2 if len(t1)==0 else t1+t2
	#return list(t1) if len(t2)==0 else list(t2) if len(t1)==0 else list(set(t1+t2))


##---------------------------------------
## First update each symtab internals with predicates
## Merge the symtabs for similar terms
## Lift the nodes with multiple options
##---------------------------------------

def parallel_merge(symTab1, symTab2, scope):

	assert(symTab1._symTab['_caller_'] == symTab2._symTab['_caller_'])

	_caller_ = symTab1._symTab['_caller_']
	f = lambda x,c : (x[0],x[1]&c)
	symTab1._symTab = {item : [f(x,symTab1._scopeCond) for x in symTab1._symTab[item]] for item in symTab1._symTab.keys() if item != '_caller_'}
	symTab2._symTab = {item : [f(x,symTab2._scopeCond) for x in symTab2._symTab[item]] for item in symTab2._symTab.keys() if item != '_caller_'}


	newtab = SymbolTable(scope, cond=Globals.__T__, \
	                    caller_symTab=_caller_)

	allkey = reduce(lambda x,y: x.union(y.keys()), \
	           [symTab1._symTab, symTab2._symTab], set())
	#allkey.remove('_caller_')

	g = lambda x, y: parallelConcat(x,y)
	newtab._symTab.update({k : g(symTab1._symTab.get(k,[]) , symTab2._symTab.get(k, [])) for k in allkey})

	## Now lift the nodes
	## it needs to be part of the parser then

	return newtab


	
