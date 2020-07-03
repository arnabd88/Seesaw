
testname="SphereOfSphereAndPt.txt"

##---------------------------------------------------------
##
## ---------  Constrained solver with Z3 ------------
##
##---------------------------------------------------------
# Confiig : Constrained Solver + instability
python3 ../../../src/satire+.py  \
        --std \
		--file ${testname} \
		--enable-constr \
		--useZ3 \
		--logfile Z3_Constrained.log \
		--outfile Z3_Constrained.out

# Confiig : Constrained Solver + instability
python3 ../../../src/satire+.py  \
        --std \
        --report-instability \
		--file ${testname} \
		--enable-constr \
		--useZ3 \
		--logfile Z3_Constrained_instab.log \
		--outfile Z3_Constrained_instab.out


