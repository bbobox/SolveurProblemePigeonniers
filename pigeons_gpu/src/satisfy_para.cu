#include "my_cuda.h"
#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <cstdint>
#include <cstring>
#include <time.h>
#include <math.h>

using namespace std;


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




//__device__
void solution_initial(int* solution){
	for (int i=0;i<n*p;++i){

		solution[i]=0;
	}


}



__global__
void kernelsolveurPigeonniersBacktrack(int pigeon_id,int *solution,int n,int p){
	if (n>p){
		printf(" aucune solution  possible car la contrainte n<=p n'est pas satisfaite \n");
	}

	else{

		if(pigeon_id==n ){
			
		}
		else{
			if (threadIdx.y==pigeon_id && threadIdx.x<blockDim.x ){
				int idx=blockDim.x * threadIdx.y+ threadIdx.x;

				bool ok=true;
				int i=0;
				while (i<n && ok==true){
					if(solution[i*p+threadIdx.y]==1){
						ok=false;
					}
					i=i+1;
				}

				if (ok==true){
					int* solI=new int[n*p];
					for (int i=0;i<n*p;++i){

							solI[i]=0;
						}


					std::memcpy(solI,solution,(n*p)*sizeof(int));
					solI[idx]=1;


				 if (pigeon_id!=n){
					dim3 grid(1,1,1);
					dim3 block(p,n,1);
					printf(" n= %d et p= %d \n", n, p);
					//kernelsolveurPigeonniersBacktrack<<< grid,block >>> (pigeon_id+1,solI,n,p);
					//cudaDeviceSynchronize();
				}


				}

			}
		}
	}
}



int main(int argc, char *argv[]){
	if (argv[1]!=NULL && argv[2]!=NULL){
		 	n=atoi(argv[1]);
			p=atoi(argv[2]);
		int* sol_cpu= new int[n*p];
		solution_initial(sol_cpu);

		int* sol_gpu;

		cudaMalloc((void**)&sol_gpu,(n*p)*sizeof(int));

		cudaMemcpy(sol_gpu,sol_cpu,(n*p)*sizeof(int),cudaMemcpyHostToDevice);

		dim3 grid(1,1,1);
		dim3 block(p,n,1);

		kernelsolveurPigeonniersBacktrack<<< grid,block >>> (0,sol_gpu,n,p);
		cudaDeviceSynchronize();

		cudaFree(sol_gpu);


	}

return 0;
}

