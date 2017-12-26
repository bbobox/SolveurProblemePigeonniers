#include <iostream>
#include <stdlib.h>
#include <cstdint>
#include <cstring>
#include <time.h>
#include <math.h> 

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
  std::cout<<"Duree du calcul : "<<hours<<" h "<<min<<" min "<<sec<<" sec"<<std::endl;
}



/**

 Verifie s'il est possible d'ajouter un pigeon i dans le pigeionniers j
*/
bool ajoutPossible(int *solution[],int pigeonier_j, int piegeon_i, int PIGEONS){
	bool ok=true;
	int i=0;
	while (i<PIGEONS && ok==true){
		if(solution[i][pigeonier_j]==1){
			ok=false;
		}
		i=i+1;
	}
	return ok;
}



/**  
  affichage d'une solution
*/

void affichage(int *solution[], int PIGEONS, int PIGEONNIERS){
	for(int i=0; i<PIGEONS;++i ){
		for(int j=0; j<PIGEONNIERS;++j){
			std::cout<<" "<<solution[i][j];
		}
		std::cout<<std::endl;

	}
	std::cout<<std::endl;
}

/**
 Initialisation de la solution
*/

void pigeonniers_vide(int *solution[],int PIGEONS, int PIGEONNIERS){
	
	for (int i=0;i<PIGEONS;++i){
		solution[i]=new int[PIGEONNIERS];
		
	}
	for (int i=0;i<PIGEONS;++i){
		for(int j=0;j<p;++j){
			solution[i][j]=0;
		}
		
	}
	
}
/*
  	Matrcie representé par un tableau de vecteur
*/

void solution_initial(int* solution){
	for (int i=0;i<n*p;++i){

		solution[i]=0;
	}


}

/**
	Affichage de la solution 
*/


int val_case(int i,int j, int* solution){
	return (solution[p*i+j]);
	
}

int indice_case(int i,int j,int* solution){

	return p*i+j;
}


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
bool ajoutPossible2(int *solution,int pigeonier_j, int piegeon_i){
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
    resolution pigeonniers: remplissage des pigeoniers
*/
void resolution2(int *solution,int piegeon){

	//std::cout<<"taille de sol:"<<n*p*sizeof(solution)<<std::endl;
	//affichage(solution,n,p); std::cout<<"-------"<<std::endl;
	if (piegeon==n){
		affichage_solution(solution);  
		nb_tot=nb_tot+1;
		//free(solution);
		std::cout<<""<<std::endl;
		
		
	}
	else{
		for(int j=0;j<p;++j){
		 	int* solI=new int[n*p];
			solution_initial(solI);
			/*if ((p-n)>2){
				s=(n*p)+4;
			}else{
				s=(n+1)*(p+1);
			}*/
			
			//std::memcpy(*solI,*solution,( (((n+1)*(p+1)))*sizeof(int)));*n*n*n
			std::memcpy(solI,solution,(n*p)*sizeof(int));
			// solI=(int*[])malloc(s * sizeof(int)+4);
			//solI=(int*)malloc(solution);
			/*std::cout<<"	case="<<j<<std::endl;
			std::cout<<"solution est: "<<std::endl;
			affichage(solution,n,p);
			std::cout<<"solution copié est: "<<std::endl;
			affichage(solI,n,p);*/
	
			if(ajoutPossible2(solI,j,piegeon)==true){
				//std::cout<<"		vrai"<<std::endl;
				//std::cout<<"bon ->>"<<j<<std::endl;
				//affichage(solI,n,p);
				//affichage(solI,n,p);
				solI[indice_case(piegeon,j,solution)]=1;
				//std::cout<<"après mise à jour"<<std::endl;
				//std::cout<<j<<std::endl;
				//affichage(solI,n,p);
				//std::cout<<" -------"<<std::endl;
				//if (i==2){affichage(solI,n,p);}
				resolution2(solI,piegeon+1);
				//solI=NULL;
			}
			
			/*else{
			std::cout<<"		faux"<<std::endl;
			}*/
			
			//delete solI;
			//delete solI;
			//delete solI;
			/*for(int k=0;k<n;++k){
				delete solI[k];
			}*/
			
		}
		
		
	}
	//delete solution;
	//free(solution);

}







/**
    resolution pigeonniers: remplissage des pigeoniers
*/
void resolution(int *solution[],int piegeon){

	//std::cout<<"taille de sol:"<<n*p*sizeof(solution)<<std::endl;
	//affichage(solution,n,p); std::cout<<"-------"<<std::endl;
	if (piegeon==n){
		//affichage(solution,n,p);  
		nb_tot=nb_tot+1;
		//free(solution);
		//std::cout<<""<<std::endl;
		
		
	}
	else{
		for(int j=0;j<p;++j){
		 	int* solI[n];
			for(int i=0;i<n;++i){
				solI[i]= new int[p]();
				//solI[i]=*solution[i];	
				//std::cout<<"i"<<i<<std::endl;
				//affichage(solI,n,p);
				//solI[i]=(int*)malloc((p+1) * sizeof(int*));
			}
			
			int s=((n)*(p));
			
			
			
			/*if ((p-n)>2){
				s=(n*p)+4;
			}else{
				s=(n+1)*(p+1);
			}*/
			
			//std::memcpy(*solI,*solution,( (((n+1)*(p+1)))*sizeof(int)));*n*n*n
			std::memmove(*solI,*solution,/*(sizeof(int)*/s*sizeof(int**)-8);
			// solI=(int*[])malloc(s * sizeof(int)+4);
			//solI=(int*)malloc(solution);
			/*std::cout<<"	case="<<j<<std::endl;
			std::cout<<"solution est: "<<std::endl;
			affichage(solution,n,p);
			std::cout<<"solution copié est: "<<std::endl;
			affichage(solI,n,p);*/
	
			if(ajoutPossible(solI,j,piegeon,n)==true){
				//std::cout<<"		vrai"<<std::endl;
				//std::cout<<"bon ->>"<<j<<std::endl;
				//affichage(solI,n,p);
				//affichage(solI,n,p);
				solI[piegeon][j]=1;
				//std::cout<<"après mise à jour"<<std::endl;
				//std::cout<<j<<std::endl;
				//affichage(solI,n,p);
				//std::cout<<" -------"<<std::endl;
				//if (i==2){affichage(solI,n,p);}
				resolution(solI,piegeon+1);
				//solI=NULL;
			}
			
			/*else{
			std::cout<<"		faux"<<std::endl;
			}*/
			
			//delete solI;
			//delete solI;
			//delete solI;
			/*for(int k=0;k<n;++k){
				delete solI[k];
			}*/
			
		}
		
		
	}
	//delete solution;
	//free(solution);

}





int main(int argc, char *argv[]){
	if (argv[1]!=NULL && argv[2]!=NULL){
		 	n=atoi(argv[1]);
			p=atoi(argv[2]);
	//

	
		int* sol[n];
		//pigeonniers_vide(sol,n,p);
		//affichage(sol,n,p);
		/* sol[0]=new int[4];
		 sol[1]=new int[4];
		 sol[2]=new int[4];*/


		//std::cout<<ajoutPossible(sol,0,0,n)<<std::endl;

		/*time_t begin=time(NULL);
		resolution(sol,0);
		time_t end=time(NULL);

		duree(begin,end);

		std::cout<<"nombre de solutions= "<<nb_tot<<std::endl;*/
		int* sol_init= new int[n*p];
		//solution_initial(sol_init);
		//affichage_solution(sol_init);
		resolution2(sol_init,0); std::cout<<"nombre de solutions= "<<nb_tot<<std::endl;
	}
	
return 0;
}
