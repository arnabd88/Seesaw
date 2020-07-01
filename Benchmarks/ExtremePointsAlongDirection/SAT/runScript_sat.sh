
testname="ExtremePointsAlongDirection.txt"

# Different run configurations
# Confiig : Basic Solver + instability
python3 ../../../src/satire+.py  \
        --std \
		--file ${testname} \
		--logfile basic.log \
		--outfile basic.out

# Confiig : Basic Solver + instability + realpaver
python3 ../../../src/satire+.py  \
        --std \
		--file ${testname} \
		--realpaver \
		--logfile basic_RP.log \
		--outfile basic_RP.out


# Confiig : Basic Solver + instability
python3 ../../../src/satire+.py  \
        --std \
        --report-instability \
		--file ${testname} \
		--logfile basic_instab.log \
		--outfile basic_instab.out


# Confiig : Basic Solver + instability + realpaver
python3 ../../../src/satire+.py  \
        --std \
        --report-instability \
		--file ${testname} \
		--realpaver \
		--logfile basic_instab_RP.log \
		--outfile basic_instab_RP.out



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

# Confiig : Constrained Solver + instability + realpaver
python3 ../../../src/satire+.py  \
        --std \
		--file ${testname} \
		--enable-constr \
		--useZ3 \
		--realpaver \
		--logfile Z3_Constrained_RP.log \
		--outfile Z3_Constrained_RP.out


# Confiig : Constrained Solver + instability
python3 ../../../src/satire+.py  \
        --std \
        --report-instability \
		--file ${testname} \
		--enable-constr \
		--useZ3 \
		--logfile Z3_Constrained_instab.log \
		--outfile Z3_Constrained_instab.out


# Confiig : Constrained Solver + instability + realpaver
python3 ../../../src/satire+.py  \
        --std \
        --report-instability \
		--file ${testname} \
		--enable-constr \
		--useZ3 \
		--realpaver \
		--logfile Z3_Constrained_instab_RP.log \
		--outfile Z3_Constrained_instab_RP.out



##---------------------------------------------------------
##
## ---------  Constrained solver with Dreal ------------
##
##---------------------------------------------------------

# Confiig : Constrained Solver + instability
python3 ../../../src/satire+.py  \
        --std \
		--file ${testname} \
		--enable-constr \
		--logfile Constrained.log \
		--outfile Constrained.out

# Confiig : Constrained Solver + instability + realpaver
python3 ../../../src/satire+.py  \
        --std \
		--file ${testname} \
		--enable-constr \
		--realpaver \
		--logfile Constrained_RP.log \
		--outfile Constrained_RP.out


# Confiig : Constrained Solver + instability
python3 ../../../src/satire+.py  \
        --std \
        --report-instability \
		--file ${testname} \
		--enable-constr \
		--logfile Constrained_instab.log \
		--outfile Constrained_instab.out


# Confiig : Constrained Solver + instability + realpaver
python3 ../../../src/satire+.py  \
        --std \
        --report-instability \
		--file ${testname} \
		--enable-constr \
		--realpaver \
		--logfile Constrained_instab_RP.log \
		--outfile Constrained_instab_RP.out

