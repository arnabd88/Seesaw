
import sympy
import symengine as seng

from collections import OrderedDict, defaultdict

# Global Flag, disable when expand seems to misbehave
simplify = True

deps = seng.var('eps')

inputVars = {eps : {"INTV" : [pow(2,53), pow(2,53)]}}
outVars = []

## SymbolTable Hierarchy Tracker
## GS[LEVEL-ID] = { T : SymtabObject,
##                  F : SymtabObject }
GS = dict()


depthTable = defaultdict(set)

hashBank = OrderedDict()

##-- For the conditional identifiers
# List of condiitonal identifiers
freeConds = []   
# Mapping from identifier to expressions
predTable = dict()
condTable = dict()
progTrace = dict() # LineNo -> node

condExprBank = dict()

externPredTable = dict()



## ID variables 
CSID = 0   ## branch identifiers
EID = 0  ## expression ID
gelpiaID = 0
FID = 0
scopeID = -1 # increment , then use

## Symbolic truth values
bvar = sympy.var('bv')
__T__ = (bvar).subs({bvar:True})
__F__ = (bvar).subs({bvar:False})
