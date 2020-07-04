

DIRS="barycentric_coordinates\
	 SymSchur\
	 Interpolator\
	 EnclosingSphere\
	 cubicspline\
	 linearfit\
	 jetapprox\
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

SAT_STAT_FILE="sat_stat.dat"

if [[ -f $SAT_STAT_FILE ]]; then
	rm -rf $SAT_STAT_FILE
fi

for d in $DIRS
do
	cd $d/SAT
	echo "Begining test $d" >> $SAT_STAT_FILE
	echo $PWD >> $SAT_STAT_FILE
	bash runScript_sat.sh
	echo "Finished test $d \n\n" >> $SAT_STAT_FILE
	cd ../../
done
