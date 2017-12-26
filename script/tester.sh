#!/bin/bash

rm *txt *temps
rm *.png

# mesure du temps sur GPU
cptargs=0;
echo " Echo cal sur GPU "
for n_p in `seq  1 9`
do
 	
	nvprof --normalized-time-unit s --log-file $n_p".txt"  --unified-memory-profiling off ./../pigeons_gpu/bin/debug/satisfy_para.exe  $n_p  $n_p;
		#if [ $methode = 1 ]
	cptargs=`expr $cptargs + 1`;
	nbligne=`grep -c [k] $n_p".txt"`;

	for idligne in `seq 1 $nbligne`
	do
		
		action=`grep [[k]  $n_p".txt"| sed -n $idligne'p' | awk -F "  " '{print  $NF }'|  awk -F "(" '{print  $1 }'| sed s/[]]/""/ | sed s/[[]/""/ | sed s/[\(][.]*/""/`;
		temps=`grep [k] $n_p".txt" |sed -n $idligne'p' | awk '{ print $2}' | sed s/[e][+][.]*/*e"("/ |sed s/$/")"/ |sed s/[e][-][.]*/*e"(-"/ |  bc -l | sed  s/^[.]/0./`;
		
		if [ $cptargs = 1 ]
		then
			echo "#n=p temps  " > $action".txt"
		fi

		bw=`echo "$temps" | bc -l`
		echo "$n_p $temps " >> $action".txt"

	done;


done;


# mesure du temps sur CPU
echo " Echo cal sur GPU "

cpt=0;
for n_p in `seq  1 9`
do
 	
	(time ./../pigeons_cpu/satisfy_cpu.exe $n_p  $n_p) 2> $n_p"_temps";
	s=`grep [r][e][a] $n_p"_temps" | awk '{print  $NF }' | cut -d'm' -f2 | cut -d's' -f1`;
	m=`grep [r][e][a] $n_p"_temps" | awk '{print  $NF }' | cut -d'm' -f1`;
	cpt=`expr $cpt + 1`;

	if [ $cpt = 1 ]
	then
		echo "#n=p temps " > "solveurPigeonniersBacktrack.txt"
	fi
	temps=`echo "($m*60)+$s" | bc -l`;
	echo "$n_p $temps " >> "solveurPigeonniersBacktrack.txt"
done;


gnuplot <<- EOF
        set xlabel " nombre de pigeons/pigeonniers (n=p)"
        set ylabel "temps en seconde"
        set title "Comparatif du temps d execution (n/s) entre le CPU et GPU"   
        set term pdf
        set output "graph_mesure_de_temps.pdf"
        plot 'solveurPigeonniersBacktrack.txt' u 1:2 w l , 'kernelsolveurPigeonniersBacktrack.txt' u 1:2 w l
EOF


