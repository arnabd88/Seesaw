import numpy as np

import sys
import time
import copy
import Globals
from gtokens import *
import symengine as seng
import ops_def as ops

from collections import defaultdict
import utils
import helper

from functools import reduce
from PredicatedSymbol import Sym, SymTup, SymConcat

import logging

logger = logging.getLogger(__name__)

##-- Description of the data structures involved
##-- workList, next_workList -> workList for the BFS traversal
##-- parentTracker 		 -> node -> parent information post trimming
##-- completed1			 -> completed list for bfs traversal
##-- completed2			 -> reachable list for dfs traversal (keeping both for consistency check)
##-- bwdDeriv			 -> Dictionary with derivative information
##-- externConstraints   -> Constraints from "REQUIRES" pragmas
##-- externFreeSymbols   -> Free symbols used in external constraints
##-- results 			 -> dictionary of results to be returned


class AnalyzeNode_Cond(object):

	def initialize(self):
		self.workList = []
		self.next_workList = []
		self.parentTracker = defaultdict(int)
		self.completed1 = defaultdict(set)
		self.completed2 = defaultdict(set)
		#self.Accumulator = defaultdict(int)
		self.Accumulator = {} 
		self.InstabilityAccumulator = {}
		self.results = {}
		self.bwdDeriv = {}
		self.externConstraints = ""
		self.externFreeSymbols = set()
		self.cond_syms = set()
		self.truthTable = set()

	def __init__(self, probeNodeList, argList, maxdepth):
		self.initialize()
		self.probeList = probeNodeList
		self.trimList = probeNodeList
		self.argList = argList
		self.maxdepth = maxdepth
		(self.parent_dict, self.cond_syms) = helper.expression_builder(probeNodeList)
		print("Expression builder condsyms:", self.cond_syms)

	def __setup_condexpr__(self):
		for csym in self.cond_syms:
			# Fill in both csym and ~csym for delta substitution
			symNode = Globals.predTable[csym]
			Globals.condExprBank[csym] = Globals.condExprBank.get(csym) if csym in Globals.condExprBank.keys()\
			else helper.handleConditionals([symNode], etype=True, inv=False)
			# debug prints
			(expr, FSYM, CSYM) = Globals.condExprBank[csym]
			if "True" in expr or "False" in expr:
				print("SETUP_CONDEXPR:", expr, type(expr), csym)
				self.truthTable.add(csym)

			Globals.condExprBank[~csym] = Globals.condExprBank.get(~csym) if ~csym in Globals.condExprBank.keys()\
			else helper.handleConditionals([symNode], etype=True, inv=True)


	def __setup_outputs__(self):
		for node in self.trimList:
			self.bwdDeriv[node] = {node: SymTup((Sym(1,Globals.__T__), ))}
			self.parentTracker[node] = len(self.parent_dict[node])

	def __init_workStack__(self):
		max_depth = max(list(map(lambda x: x.depth, self.trimList))) 
		#print(max_depth)
		it1, it2 = utils.partition(self.trimList, lambda x:x.depth==max_depth)
		self.next_workList = list(it1)
		self.workList = list(it2)

	def __externConstraints__(self):
		(subcond,free_symbols,cond_symbols) = helper.handleConditionals( [v for k,v in Globals.externPredTable.items()], etype=False)
		self.externConstraints = subcond 
		self.externFreeSymbols = free_symbols
		print("Ext Constraints: ", subcond)
	#	self.externConstraints = "( " + " && ".join(["("+str(n.f_expression)+")" for n in Globals.externPredTable.keys()]) + " )"

		
	def converge_parents(self, node):
		#print(node.depth, len(node.f_expression))
		#print(type(node).__name__, node.depth, self.parentTracker[node], len(node.parents) , len(self.parent_dict[node]))#, node.f_expression)
		return True if self.parentTracker[node] >= len(self.parent_dict[node]) else False




	def visit_node_deriv(self, node):
		st = time.time()
		outList = self.bwdDeriv[node].keys()
		if(len(node.children) <= 0):
			pass
		else:
			if(type(node).__name__ == "LiftOp"):
				opList = [(n[0].f_expression, n[1]) for n in node.nodeList]
				for i, child_node in enumerate(node.children):
					for outVar in outList:
						sti = time.time()
						self.bwdDeriv[child_node] = self.bwdDeriv.get(child_node, {})
						self.bwdDeriv[child_node][outVar] = self.condmerge(self.bwdDeriv[child_node].get(outVar, SymTup((Sym(0.0, Globals.__F__),))).__concat__( \
							self.bwdDeriv[node][outVar] * \
							SymTup((Sym(1.0, node.nodeList[i][1]),)),trim=True))
						eti = time.time()
						#print("Lift-op:One bak prop time = ", eti-sti)
					self.next_workList.append(child_node)
					self.parentTracker[child_node] += 1						
			else:
				DerivFunc = ops._DFOPS[node.token.type]
				opList = [child.f_expression for child in node.children]
				for i, child_node in enumerate(node.children):
					for outVar in outList:
						sti = time.time()
						self.bwdDeriv[child_node] = self.bwdDeriv.get(child_node, {})
						self.bwdDeriv[child_node][outVar] = self.condmerge(self.bwdDeriv[child_node].get(outVar, SymTup((Sym(0.0, Globals.__F__),))).__concat__( \
								self.bwdDeriv[node][outVar] * \
								(SymTup((Sym(0.0, Globals.__T__),)) \
								 if utils.isConst(child_node) else \
								 DerivFunc[i](opList)), trim=True))
						eti = time.time()
						#print("One bak prop time = ", eti-sti)
					self.next_workList.append(child_node)
					self.parentTracker[child_node] += 1
		self.completed1[node.depth].add(node)
		et = time.time()
		#print("@node",node.depth, node.f_expression)
		#print("Time taken =", et-st,"\n\n")



	def traverse_ast(self):
		next_workList = []
		curr_depth = 0
		next_depth = -1
		while(len(self.workList) > 0):
			node = self.workList.pop()
			curr_depth = node.depth
			next_depth = curr_depth - 1
			if (utils.isConst(node)):
				self.completed1[node.depth].add(node)
			elif self.completed1[node.depth].__contains__(node):
				pass
			elif (self.converge_parents(node)):
				self.visit_node_deriv(node)
			else:
				self.workList.append(node)

			if(len(self.workList)==0 and next_depth!=-1 and len(self.next_workList)!=0):
				nextIter, currIter = utils.partition(self.next_workList,\
													lambda x: x.depth==next_depth)
				self.workList = list(set(currIter))
				self.next_workList = list(set(nextIter))

	## merge the error terms 
	def merge_discontinuities(self, acc, opLimit):
		racc = acc
		constCond = Globals.__T__
		constAcc = [0.0]
		temp_racc = []
		temp_dict = {}
		res_avg_maxres = (0,0)
		lim = 100 if (len(racc) > 20) else opLimit 
		for els in racc:
			(expr, cond) = els.exprCond
			#print("lim:", seng.count_ops(expr), lim, len(racc))
			if seng.count_ops(expr)==0:
				constCond = constCond | cond
				constAcc.append(abs(expr))
			elif seng.count_ops(expr) > lim:
				#print("lim:", expr, lim, len(racc))
				(cond_expr,free_symbols) = self.parse_cond(cond)
				print("Query2: ", seng.count_ops(expr))
				#print("COND-EXPR:", cond_expr)
				res_avg_maxres = utils.get_statistics(expr)
				errIntv = utils.generate_signature(expr,\
												   cond_expr, \
												   self.externConstraints, \
												   free_symbols.union(self.externFreeSymbols))
				err = max([abs(i) for i in errIntv])
				print("STAT: SP:{err}, maxres:{maxres}, avg={avg}".format(\
					err = err, maxres = res_avg_maxres[1], avg = res_avg_maxres[0] \
				))
				print(type(err), res_avg_maxres[1]*pow(2,-53))
				if(err == np.inf):
					err = res_avg_maxres[1]
				temp_racc.append(Sym(err, cond))
			else:
				temp_racc.append(els)
		#print(constAcc)
		#temp_racc.append(Sym(max(constAcc), constCond))
		s = SymTup(els for els in temp_racc).__concat__(SymTup((Sym(max(constAcc), constCond),)),trim=True)
		#print("****Merge difference\n")
		#print("MaxConst = ", max(constAcc))
		#print(racc==s, len(racc), len(s))
		#print([ac for ac in acc])
		#print([rc for rc in racc])
		#print([si for si in s])
		#print("\n")
		return s ;
				
	def add_instability_error(self, expr_solve):
		temp_list = [0]
		if len(expr_solve) > 1:
			print("INSTABILITY COMPRESSION LIST:", len(expr_solve))
			unstable_cands = list(filter(lambda x: bool(helper.freeCondSymbols(x).difference(self.truthTable)), \
							  expr_solve))
			print("Candidates for instability:", len(unstable_cands))
			for i in range(0, len(unstable_cands)):
				for j in range(i+1, len(unstable_cands)):
					expr_diff = (unstable_cands[i].exprCond[0] - unstable_cands[j].exprCond[0]).__abs__()
					#cond = (unstable_cands[i].exprCond[1] & unstable_cands[j].exprCond[1]).simplify()
					(cond1_expr, free_symbols1) = self.parse_cond(unstable_cands[i].exprCond[1])
					(cond2_expr, free_symbols2) = self.parse_cond(unstable_cands[j].exprCond[1])
					cond_expr =  cond1_expr  & cond2_expr 
					free_symbols = free_symbols1.union(free_symbols2)
					#(cond_expr, free_symbols) = self.parse_cond(cond)
					errIntv = utils.generate_signature(expr_diff, \
													   cond_expr, \
													   self.externConstraints, \
													   free_symbols.union(self.externFreeSymbols))
					err = max([abs(i) for i in errIntv])
					temp_list.append(err)
					

		return max(temp_list)
		


	def propagate_symbolic(self, node):
		for outVar in self.bwdDeriv[node].keys():
			#print(node.depth)
			expr_solve = self.condmerge(\
							((self.bwdDeriv[node][outVar]) * \
							(node.get_noise(node)) * node.get_rounding())\
							).__abs__()
			acc = self.Accumulator.get(outVar, SymTup((Sym(0.0, Globals.__T__),)))
			#print("ACC:", len(acc), acc.__countops__())
			if(len(acc) > 10):
				acc = self.merge_discontinuities(self.condmerge(acc), 4000)

			instability_error = 0 if not Globals.argList.report_instability else self.add_instability_error(expr_solve)
			self.InstabilityAccumulator[outVar] = self.InstabilityAccumulator.get(outVar, 0.0) +\
													instability_error
			expr_solve = self.merge_discontinuities(expr_solve, 1000)
			#expr_solve = self.merge_discontinuities(self.condmerge(expr_solve), 1000)
			#else:
			#acc = self.merge_discontinuities(acc)
			#print("RACC:", len(acc), acc.__countops__())
			#print("\n------------------------")
			#print(expr_solve)
			#print(node.get_noise(node))
			#print((self.bwdDeriv[node][outVar]))
			#print("------------------------\n")
			val = acc.__concat__(expr_solve, trim=True)
			#print("==========================")
			#print("expr_solve:", expr_solve)
			#print("val:", val)
			#print("Merge:", self.condmerge(val))
			#print("\n==========================\n\n")

			self.Accumulator[outVar] = val




	def visit_node_ferror(self, node):

		#print(node.depth, type(node).__name__, "Out of there\n")
		for child in node.children:
			if not self.completed2[child.depth].__contains__(child):
				self.visit_node_ferror(child)

		if(self.completed1[node.depth].__contains__(node)):
			self.propagate_symbolic(node)
		self.completed2[node.depth].add(node)


	def condmerge(self, tupleList):
		ld = {}
		for els in tupleList:
			(expr,cond) = els.exprCond
			ld[cond] = ld.get(cond, SymTup((Sym(0.0,Globals.__T__),))) + SymTup((els,))
		
		#for k,v in ld.items():
		#	print("//-- Cond =", k)
		#	print(v,"\n")
		#print("Size,", len(tupleList))

		return reduce(lambda x,y : x.__concat__(y,trim=True), [v for k,v in ld.items()], SymTup((Sym(0.0,Globals.__T__),)))


	def parse_cond(self, cond):
		tcond = cond
		print("\n ******** Parsing Conditional = {pcond}".format(pcond=tcond))
		logger.info("\n Parsing Conditional = {pcond}".format(pcond=tcond))
		set_free_symbols = set()
		if tcond not in (True,False):
			free_syms = tcond.free_symbols
			for fsym in free_syms:
				symNode = Globals.predTable[fsym]
				print("Handling Condtional {symID}".format(symID=fsym))
				logger.info("Handling Condtional {symID}".format(symID=fsym))
				dict_element = Globals.condExprBank.get(fsym) 
				assert(dict_element is not None)
				(subcond,free_symbols, cond_symbols) =  dict_element
				#(subcond,free_symbols, cond_symbols) =  Globals.condExprBank.get(fsym) if fsym in Globals.condExprBank.keys()\
				#														 else helper.handleConditionals([symNode], etype=True)
				#subcond = subcondList[0]
				print("SubCond: {symID} : {SubCond}\n\n".format(symID=fsym, SubCond=subcond))
				logger.info("SubCond:{symID} : {SubCond}\n\n".format(symID=fsym, SubCond=subcond))
				Globals.condExprBank[fsym] = (subcond,free_symbols, cond_symbols)
				set_free_symbols.union(free_symbols)
			symDict = {fsym: Globals.condExprBank[fsym][0] for fsym in free_syms}
			inv_symDict = {~fsym: Globals.condExprBank[~fsym][0] for fsym,v in symDict.items() if v not in ('(True)', 'True', '(False)', 'False', True, False)}
			inv_symDict.update(symDict)
			print("Inside parsing conditionals -> cond sub dict : {sdict}".format(sdict=inv_symDict))
			#print("Inside parsing conditionals -> total cond : {total_cond}".format(total_cond=tcond))
			tcond = tcond.subs(inv_symDict)
			#tcond = tcond.subs({fsym: Globals.condExprBank[fsym][0] for fsym in free_syms})
			print("Finished parsing -> {cond} : {cexpr}\n".format(cond=cond, cexpr=tcond))
			logger.info("Finished parsing -> {cond} : {cexpr}".format(cond=cond, cexpr=tcond))
			#print("tcond:", tcond)
			return (tcond, set_free_symbols)
		return (tcond, set_free_symbols)


	def first_order_error(self):

		for node in self.trimList:
			if not self.completed2[node.depth].__contains__(node):
				self.visit_node_ferror(node)
		self.Accumulator = {k : self.condmerge(v) for k,v in self.Accumulator.items()}

		## Placeholder for gelpia invocation
		res_avg_maxres = (0,0)
		for node, tupleList in self.Accumulator.items():
			errList = []
			funcList = []
			for els in tupleList:
				expr, cond = els.exprCond
				(cond_expr,free_symbols) = self.parse_cond(cond)
				print("Query1: ", seng.count_ops(expr))
				#print("COND-EXPR:", cond_expr)
				res_avg_maxres = utils.get_statistics(expr)				
				#print("cond_expr", cond_expr)
				#errIntv = utils.generate_signature(expr,cond_expr, free_symbols)
				errIntv = utils.generate_signature(expr,\
												   cond_expr, \
												   self.externConstraints, \
												   free_symbols.union(self.externFreeSymbols))
				err = max([abs(i) for i in errIntv])
				print("STAT: SP:{err}, maxres:{maxres}, avg:{avg}".format(\
					err = err, maxres = res_avg_maxres[1], avg = res_avg_maxres[0] \
				))
				print(type(err), res_avg_maxres[1]*pow(2,-53))
				if(err == np.inf):
					err = res_avg_maxres[1]
				errList.append(err)

			ret_intv = None
			for exprTup in node.f_expression:
				expr, cond = exprTup.exprCond
				#print("Query: ", seng.count_ops(expr), cond)
				#print("f_expr", expr)
				(cond_expr,free_symbols) = self.parse_cond(cond)
				#print("COND-EXPR:", cond_expr)
				#fintv = utils.generate_signature(expr,cond_expr, free_symbols)
				fintv = utils.generate_signature(expr,\
												   cond_expr, \
												   self.externConstraints, \
												   free_symbols.union(self.externFreeSymbols))
				ret_intv = fintv if ret_intv is None else [min(ret_intv[0],fintv[0]), max(ret_intv[1], fintv[1])]
			#print(node.f_expression)
			self.results[node] = {"ERR" : max(errList), \
								  "SERR" : 0.0, \
								  "INSTABILITY": self.InstabilityAccumulator[node], \
								  "INTV" : ret_intv \
								  }

			#print("MaxError:", max(errList)*pow(2,-53), fintv)
			logger.info(" > MaxError:\n {error} ; {fintv}\n".format(error=max(errList)*pow(2,-53), fintv=ret_intv))
			print(" > MaxError:\n {error} ; {fintv}\n".format(error=max(errList)*pow(2,-53), fintv=ret_intv))
			print(" > Instability:\n {instab} ;".format(instab=self.InstabilityAccumulator[node]))

		return self.results


	def start(self):
		self.__init_workStack__()
		self.__setup_outputs__()
		self.__externConstraints__()
		self.__setup_condexpr__()
		print("CondExpr:", Globals.condExprBank.keys())

		dt1 = time.time()
		print(" > Begin building derivatives....")
		logger.info(" > Begin building derivatives....")
		self.traverse_ast()
		dt2 = time.time()
		print(" > Finished in {duration} secs\n".format(duration=dt2-dt1))
		logger.info(" > Finished in {duration} secs\n".format(duration=dt2-dt1))

		#self.completed.clear()
		fe1 = time.time()
		#print("//----------------------------//")
		print(" > Analyzing error for the current abstraction block...\n")
		logger.info("Analyzing error for the current abstraction block...\n")
		res = self.first_order_error()
		fe2 = time.time()
		print(" > Finished in {duration} secs\n".format(duration=fe2-fe1))
		logger.info("Finished in {duration} secs\n".format(duration=fe2-fe1))

		return res
		
