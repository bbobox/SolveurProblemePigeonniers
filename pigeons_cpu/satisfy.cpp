#include <iostream>
#include <stdlib.h>
#include <cstdint>
#include <cstring>
#include <time.h>
#include <math.h> 
#include <chrono>


int n;
int p ;

int nb_tot=0;


 /* calcul de temps d'execution */
void duree(time_t _begin, time_t _end)
{
  double temp;
  double hours=0, min=0, sec=0;
  double dureeCalc = difftime(_end, _begin);
  temp = modf(dureeCalc/3600., &hours);
  temp = modf(temp*60., &min);
  temp = modf(temp*60., &sec);
  std::cout<<"Duree du calcul : "<<hours<<" h "<<min<<" min "<<dureeCalc<<" sec"<<std::endl;
}




/*
  	Matrice representé par un vecteur
*/

void solution_initial(int* solution){
	for (int i=0;i<n*p;++i){

		solution[i]=0;
	}


}



int val_case(int i,int j, int* solution){
	return (solution[p*i+j]);
	
}

int indice_case(int i,int j,int* solution){

	return p*i+j;
}


/**
	Affichage de la solution 
*/

void affichage_solution(int* solution){

	for (int i=0;i<n;++i){
		for(int j=0;j<p;++j){ 
			int x= val_case(i,j,solution);
			std::cout<<" "<<x;
		}
	std::cout<<std::endl;
	}
}


/**

 Verifie s'il est possible d'ajouter un pigeon i dans le pigeionniers j
*/
bool ajoutPossible(int *solution,int pigeonier_j, int piegeon_i){
	bool ok=true;
	int i=0;
	while (i<n && ok==true){
		if(val_case(i,pigeonier_j,solution)==1){
			ok=false;
		}
		i=i+1;
	}
	return ok;
}



/**
    resolution pigeonniers: remplissage des pigeoniers par backtracking
*/
void solveurPigeonniersBacktrack(int *solution,int piegeon){
	
	if (piegeon==n || n>p){
		affichage_solution(solution);  // commenter la ligne pour ne pas afficher les permutation possible
		nb_tot=nb_tot+1;
		std::cout<<""<<std::endl;
		if (n>p){
			std::cout<<" aucune solution  possible car la contrainte n<=p n'est pas satisfaite "<<std::endl;
		}
	
	
	}
	else{
		for(int j=0;j<p;++j){
		 	int* solI=new int[n*p];
			solution_initial(solI);
			std::memcpy(solI,solution,(n*p)*sizeof(int));

			if(ajoutPossible(solI,j,piegeon)==true){
				solI[indice_case(piegeon,j,solution)]=1;

				solveurPigeonniersBacktrack(solI,piegeon+1);
			}
		
		}
	}
		
		

}



int main(int argc, char *argv[]){
	if (argv[1]!=NULL && argv[2]!=NULL){
	 	n=atoi(argv[1]);
		p=atoi(argv[2]);

		int* sol_init= new int[n*p];
		solution_initial(sol_init);
		
		clock_t start_t, end_t;
	 	 double diff_t;
	   	time(&start_t);
	   	solveurPigeonniersBacktrack(sol_init,0); std::cout<<"nombre de solutions= "<<nb_tot<<std::endl; 
		time(&end_t);
	   	diff_t = difftime(end_t, start_t);
		printf("Duree du calcul = %f\n", diff_t);

		
		
	}
	
return 0;
}
