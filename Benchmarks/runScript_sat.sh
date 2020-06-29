

DIRS="barycentric_coordinates\
	 test2\
	 Jacobi\
	 lead-lag"


set -x

for d in $DIRS
do
	cd $d/SAT
	echo $PWD
	bash runScript_sat.sh
	cd ../../
done
