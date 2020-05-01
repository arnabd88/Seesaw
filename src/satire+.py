
import  sys
import time
import argparse
import symengine as seng

import Globals
from gtokens import *
from lexer import Slex
from parser import Sparser

from collections import defaultdict

from ASTtypes import *

import helper



def parseArguments():
	parser = argparse.ArgumentParser()
	parser.add_argument('--file', help='Test file name', required=True)
	parser.add_argument('--parallel', help='Enable parallel optimizer queries:use for large ASTs',\
							default=False, action='store_true')
	parser.add_argument('--enable-abstraction', help='Enable abstraction of internal node defintions,\
													  value indiactes level\
													  of abstraction. By default enabled to level-1. \
													  To disable pass 0', default=False, action='store_true')
	parser.add_argument('--mindepth', help='Min depth for abstraction. Default is 10',\
									  default=20, type=int)
	parser.add_argument('--maxdepth', help='Max depth for abstraction. Limiting to 40', \
									  default=40, type=int)
	#parser.add_argument('--fixdepth', help='Fix the abstraction depth. Default is -1(disabled)', \
	#								  default=-1, type=int)
	#parser.add_argument('--alg', help='Heuristic level for abstraction(default 0), \
	#									0 -> Optimal depth within mindepth and maxdepth(may loose correlation), \
	#									1 -> User defined fixed depth, \
	#									2 -> User Tagged nodes or only lhs nodes', \
	#									default=0, type=int)
	parser.add_argument('--simplify', help='Simplify expression -> could be costly for very large expressions',
										default=False, action='store_true')
	parser.add_argument('--logfile', help='Python logging file name -> default is default.log', default='default.log')
	parser.add_argument('--outfile', help='Name of the output file to write error info', default='outfile.txt')
	parser.add_argument('--std', help='Print the result to stdout', default=False, action='store_true')
	parser.add_argument('--sound', help='Turn on analysis for higher order errors', default=False, action='store_true')
	parser.add_argument('--compress', help='Perform signature matching to reduce optimizer calls using hashing and md5 signature', default=False, action='store_true')
	parser.add_argument('--force', help='Sideline additional tricks used for non-linear examples. Use this option for linear examples', default=False, action='store_true')
	                                  

	result = parser.parse_args()
	return result


def full_analysis(probeList, argList, maxdepth):
	helper.expression_builder(probeList)
	

def ErrorAnalysis(argList):

	probeList = helper.getProbeList()
	maxdepth = max([max([n[0].depth for n in nodeList])  for nodeList in probeList])
	print("maxdepth = ", maxdepth)

	full_analysis(probeList, argList, maxdepth)



if __name__ == "__main__":
	start_exec_time = time.time()
	argList = parseArguments()
	sys.setrecursionlimit(10**6)
	print(argList)
	text = open(argList.file, 'r').read()
	fout = open(argList.outfile, 'w')



	start_parse_time = time.time()
	lexer = Slex()
	parser = Sparser(lexer)
	parser.parse(text)
	del parser
	del lexer
	end_parse_time = time.time()
	parse_time = end_parse_time - start_parse_time

	helper.PreProcessAST()

	ErrorAnalysis(argList)


	end_exec_time = time.time()
	print("Full time : {full_time}".format(full_time = end_exec_time - start_exec_time))
