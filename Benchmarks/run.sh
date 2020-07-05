

DIRS="barycentric_coordinates\
	 SymSchur\
	 Interpolator\
	 EnclosingSphere\
	 cubicspline\
	 linearfit\
	 jetapprox\
	 SqDistPointSegment\
	 styblinski\
	 test2\
	 gram-schmidt\
	 ClosestPtPointSegment2\
	 ExtremePointsAlongDirection\
	 SphereOfSphereAndPt\
     EigenSphere"


	 #squareRoot3\
	 #smartRoot\
	 #lead-lag\
	 #Jacobi\
	 #MD"


set -x

SAT_STAT_FILE="emp_stat.dat"

if [[ -f $SAT_STAT_FILE ]]; then
	rm -rf $SAT_STAT_FILE
fi

for d in $DIRS
do
	cd $d/CMOD
	echo "Begining test $d" >> $SAT_STAT_FILE
	echo $PWD >> $SAT_STAT_FILE
	bash run.sh
	./emp 1000000 > emp.log
	echo "Finished test $d \n\n" >> $SAT_STAT_FILE
	cd ../../
done
