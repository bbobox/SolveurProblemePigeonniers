# SolveurProblemePigeonniers
@BOKA Yao
@IBRIR Yassine
M1 Info



-Compilation du solveur sur CPU:
	*acceder au dossier "/pigeons_cpu" et faire :
		-lancer le makefile : make
		-lancer l'excutable "satisfy_cpu.exe": ./satisfy_cpu.exe param1 param2
			Param1: nombre de pigeons
			param2: nombre de pigeonniers

		-NB: Possibilité de cacher l'affichage des combinaisons en commentant les lignes 98 et 100 du code source (satisfy.cpp)


-Compilation du solveur sur GPU: ( probleme au niveau de la compilation)
	*acceder au dossier "/pigeons_cpu" et faire :
		-lancer le makefile : make

	Probleme rencontré de la compilation: ( Appel de Kernel recursif (à  ligne 85 mis en commententaire satisfy_para.cu ) provoquant l'erreur suivante
		-"nvlink error   : Undefined reference to 'cudaGetParameterBufferV2' in 'obj/debug/satisfy_para.o' (target: sm_35)
			nvlink error   : Undefined reference to 'cudaLaunchDeviceV2' in 'obj/debug/satisfy_para.o' (target: sm_35)
			nvlink error   : Undefined reference to 'cudaDeviceSynchronize' in 'obj/debug/satisfy_para.o' (target: sm_35)
			makefile:72 : la recette pour la cible « bin/debug/satisfy_para.exe » a échouée
			make: *** [bin/debug/satisfy_para.exe] Erreur 255 "


	
		

Fichier de script de test: (/script/tester.sh):
	Permet  d'excuter les deux programme (CPU/GPU) et faire un comparif du temps d'executer pour le nombre de pigeons et de pigeonniers allant de 1 à 9  /n=p)
	-ResutatS obtenus dans les ficherS:
		-script/solveurPigeonniersBacktrack.txt
		-script/-kernelsolveurPigeonniersBacktrack.txt
		-script/graph_mesure_de_temps.pdf
	
