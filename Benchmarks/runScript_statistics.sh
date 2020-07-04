

DIRS="barycentric_coordinates\
	 Interpolator\
	 cubicspline\
	 linearfit\
	 EnclosingSphere\
	 jetapprox\
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

SAT_STAT_FILE="sat_stat.dat"


if [[ -f $SAT_STAT_FILE ]]; then
	rm -rf $SAT_STAT_FILE
fi


for d in $DIRS
do
	cd $d/SAT
	echo "Begining test $d" >> $SAT_STAT_FILE
	echo $PWD >> $SAT_STAT_FILE
	echo $PWD
	bash runScript_statistics.sh
	echo "Finished test $d \n\n" >> $SAT_STAT_FILE
	cd ../../
done
