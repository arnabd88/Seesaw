
import Globals
import math
import sympy as sym
import symengine as seng
from collections import defaultdict
from SymbolTable import *


def getProbeList():
	#print(Globals.GS[0]._symTab.keys())
	return [Globals.GS[0]._symTab[outVar] for outVar in Globals.outVars]


def parse_cond(cond):
	tcond = cond
	if tcond not in (True,False):
		free_syms = tcond.free_symbols
		for fsym in free_syms:
			symNode = Globals.predTable[fsym]
			#print(fsym," |-> ", symNode.rec_eval(symNode))
			subcond =  Globals.condExprBank.get(fsym, symNode.rec_eval(symNode))
			Globals.condExprBank[fsym] = subcond
		#tcond = tcond.subs({fsym:subcond})
		tcond = tcond.subs({fsym: Globals.condExprBank[fsym] for fsym in free_syms})
		#print("Cond, :-> ", tcond)
		return tcond
	return tcond


def dfs_expression_builder(node, reachable, parent_dict, cond):

	for child in node.children:
		if not reachable[child.depth].__contains__(child):
			dfs_expression_builder(child, reachable, parent_dict, cond=Globals.__T__)

		parent_dict[child].append(node)

	#print(type(node).__name__, node.token)
	fexpr = node.eval(node)
	#print(node.depth, type(node).__name__, node.cond)
	#print(fexpr,"\n")
	node.set_expression(fexpr)
	reachable[node.depth].add(node)



def expression_builder(probeList):

	parent_dict = defaultdict(list)
	reachable = defaultdict(set)

	for node in probeList:
		if not reachable[node.depth].__contains__(node):
			dfs_expression_builder(node, reachable, parent_dict, cond=Globals.__T__)

	del reachable
	
	return parent_dict

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

	#rhstbl = {}
	#print("\n\n", Globals.GS[0]._symTab[seng.var('g')])
	#glift = Globals.GS[0]._symTab[seng.var('g')][0][0]
	#for child in glift.children:
	#	print(child)


	#for k,v in Globals.GS[0]._symTab.items():
	#	rhstbl[v] = k
		#if(k == seng.var('radius') or k==seng.var('newRadius')):
		#	nodeout = v[0][0]
		#	print(k, nodeout, nodeout.depth, nodeout.f_expression)

	for nodeList in probeList:
		assert(len(nodeList)==1)
		[node,cond] = nodeList[0]
		if not reachable[node.depth].__contains__(node):
			pretraverse(node, reachable)
			#assert(node==nodeout)
			#assert(reachable[node.depth].__contains__(node))

	print("Pre :", len(Globals.GS[0]._symTab.keys()))
	#print([(nodeCondList, syms) for nodeCondList,syms in rhstbl.items()])
	Globals.GS[0]._symTab = {syms: tuple(set(n for n in nodeCondList \
										if reachable[n[0].depth].__contains__(n[0]))) \
										for syms,nodeCondList in Globals.GS[0]._symTab.items() }
	print("Post :", len(Globals.GS[0]._symTab.keys()))
	#print(Globals.GS[0]._symTab[seng.var('g')])
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


def filterCandidate(bdmin, bdmax, dmax):
	#workList =  [[v[0] for v in nodeList if v[0].depth!=0]\
	#            for k,nodeList in Globals.GS[0]._symTab.items()]
	workList =  [[v for v in nodeList if v.depth!=0]\
	            for k,nodeList in Globals.depthTable.items()]
	
	workList = list(set(reduce(lambda x,y : x+y, workList, [])))
	#print("workList=",len(workList), [v.depth for v in workList])
	#print(bdmin, bdmax)


	return list(filter( lambda x:x.depth >= bdmin and x.depth <= bdmax ,\
								workList))
							   #[[v for v in nodeList if v.depth!=0] for k,nodeList in Globals.GS[0]._symTab.items()]
	                           #[v for k,v in Globals.GS[0]._symTab.items() if v.depth!=0]\
							 #))


def selectCandidateNodes(maxdepth, bound_mindepth, bound_maxdepth):
	
	PreCandidateList = filterCandidate(bound_mindepth, bound_maxdepth, maxdepth)

	loc_bdmax = bound_maxdepth
	while( len(PreCandidateList) <= 0 and loc_bdmax <= maxdepth):
		loc_bdmax += 5
		PreCandidateList = filterCandidate(bound_mindepth, loc_bdmax, maxdepth)

	#print(PreCandidateList)
	if(len(PreCandidateList) <= 0):
		return []
	else:
		f = lambda x : float(x.depth)/(loc_bdmax) + 0.1
		g = lambda x, y : (-1)*y*math.log(y,2)*(len(x.parents)+ \
		                       (len(x.children) if type(x).__name__ == "LiftOp" else 0))

		cost_list = list(map( lambda x : [x.depth, g(x, f(x))], \
		                 PreCandidateList \
						))

		sum_depth_cost = [(depth, sum(list(map(lambda x:x[1] if x[0]==depth\
		                     else 0, cost_list)))) \
							 for depth in range(bound_mindepth, loc_bdmax)]
		#print(sum_depth_cost)
		sum_depth_cost.sort(key=lambda x:(-x[1], x[0]))
		abs_depth = sum_depth_cost[0][0]


		## Obtain all candidate list at this level
		CandidateList = Globals.depthTable[abs_depth]

		print("CURRENT AST_DEPTH = : {ast_depth}".format(ast_depth=maxdepth))
		print("ABSTRACTION_DEPTH : {abs_depth}".format(abs_depth=abs_depth))

		return [abs_depth, CandidateList]

