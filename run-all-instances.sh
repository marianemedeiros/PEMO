#!/bin/bash
ALGO=$1
LS=$2
DIFF=0
if [[ $LS == "" ]]; then
	LS=3
fi 

ITERATIONS=30
GPROF_FILE="gmon.out"

#make clean
#make clean_log
#make

mkdir logs_gprof/$ALGO/
mkdir logs_perf/$ALGO/

function func1() {
   echo "Stop Criteria: $SC"
   for ((i = 1; i <= $ITERATIONS; i++ ))
	do  
		if [ $i == 1 ]; then
			cd logs_gprof/$ALGO/
			mkdir $FILE
			cd ../../

			cd logs_perf/$ALGO/
			mkdir $FILE
			cd ../../
		fi
		START=$(date +%s)
		#./main -f $FILE -i $i -a $ALGO -s $SC -l $LS -w 1
		#-e bpf-output
		perf stat -e branch-instructions -e branch-misses -e bus-cycles -e cache-misses -e cache-references -e cpu-cycles -e instructions -e ref-cycles -e stalled-cycles-frontend -e alignment-faults -e context-switches -e cpu-clock -e cpu-migrations -e dummy -e emulation-faults -e major-faults -e minor-faults -e page-faults -e task-clock -o "logs_perf/$ALGO/$FILE/${FILE}_${i}.perf" ./main -f $FILE -i $i -a $ALGO -l $LS -d 0 -w 1
		END=$(date +%s)
		DIFF=$(( $END - $START ))
		

		#if [ $i == 1 ] && [ "$FILE" == "V_TCCC130" ]; then
		#	estimate_time
		#fi
		echo "$FILE $ALGO $i $DIFF"
		mv $GPROF_FILE "gmon_${i}.out"
		mv "gmon_${i}.out" logs_gprof/$ALGO/$FILE/
	done
}

A_START=$(date +%s)

# echo "File: V_TCCC130..."
# FILE=V_TCCC130
# SC=10120
# func1

 echo ""
 echo "File: V_TCCC251..."
 FILE=V_TCCC251
# SC=18920
 func1

#echo ""
#echo "File: V_TCCC412..."
#FILE=V_TCCC412
#SC=31680
#func1

echo ""
echo "File: V_TCCC512..."
FILE=V_TCCC512
# SC=34760
func1

#echo ""
#echo "File: V_TCCC761..."
#FILE=V_TCCC761
# SC=49720
#func1

#echo ""
# echo "File: V_TCCC1000..."
# FILE=V_TCCC1000
 #SC=64729
# func1

 echo ""
 echo "File: V_TCCC1253..."
 FILE=V_TCCC1253
 #SC=81922
 func1

 #echo ""
 #echo "File: V_TCCC1517..."
 #FILE=V_TCCC1517
 #SC=99160
 #func1

 #echo ""
 #echo "File: V_TCCC2010..."
 #FILE=V_TCCC2010
 #SC=130200
 #func1

 echo ""
 echo "File: V_TCCC2313..."
 FILE=V_TCCC2313
# SC=149450
 func1

 #echo ""
 #echo "File: V_TCCC3478..."
 #FILE=V_TCCC3478
# SC=217506
 #func1

A_END=$(date +%s)
A_DIFF=$(( $A_END - $A_START ))
a_h=$(( $A_DIFF / 3600))

echo "Time to run all instances $ITERATIONS times is: $a_h h ($A_DIFF s)"
