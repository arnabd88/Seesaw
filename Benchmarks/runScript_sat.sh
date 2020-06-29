

DIRS="barycentric_coordinates\
	 ClosestPtPointSegment2\
     EigenSphere\
	 ExtremePointsAlongDirection\
	 gram-schmidt\
	 MD\
	 smartRoot\
	 SphereOfSphereAndPt\
	 SqDistPointSegment\
	 squareRoot3\
	 styblinski\
	 test2\
	 SymSchur\
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
