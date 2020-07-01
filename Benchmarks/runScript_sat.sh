

DIRS="barycentric_coordinates\
	 SymSchur\
	 SqDistPointSegment\
	 squareRoot3\
	 styblinski\
	 smartRoot\
	 test2\
	 lead-lag\
	 gram-schmidt\
	 ClosestPtPointSegment2\
	 ExtremePointsAlongDirection\
	 SphereOfSphereAndPt\
	 Jacobi\
     EigenSphere\
	 MD"


set -x

for d in $DIRS
do
	cd $d/SAT
	echo $PWD
	bash runScript_sat.sh
	cd ../../
done
