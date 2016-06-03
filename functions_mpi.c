#include "stdio.h"
#include "stdlib.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mpi.h>

#define END 5
#define WYNIK 6
#define DATA 7


int malloc2dfloat(int ***array, int n, int m) {

    /* allocate the n*m contiguous items */
    int *p = (int *)malloc(n*m*sizeof(int));
    if (!p) return -1;

    /* allocate the row pointers into the memory */
    (*array) = (int **)malloc(n*sizeof(int*));
    if (!(*array)) {
       free(p);
       return -1;
    }

    /* set up the pointers into the contiguous memory */
    for (int i=0; i<n; i++) 
       (*array)[i] = &(p[i*m]);

    return 0;
}

int free2dfloat(int ***array) {
    /* free the memory - the first element of the array is at the start */
    free(&((*array)[0][0]));

    /* free the pointers into the memory */
    free(*array);

    return 0;
}


int** create_mat(int size)
{
	int** mat=malloc(size*sizeof(int*));
	for(int i=0;i<size;i++)
		mat[i]=malloc(size*sizeof(int));
	return mat;
}
void destroy_mat(int** mat,int size)
{
	for(int i=0;i<size;i++)
	{
		free(mat[i]);
	}
	free(mat);
}

int** populate(int size)
{	
	int** mat=create_mat(size);
	for (int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
		{
			mat[i][j]=rand()%9+1;
		}
	}
	return mat;
}
void populate_mpi(int** mat,int size)
{	
	
	for (int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
		{
			mat[i][j]=rand()%9+1;
		}
	}
}
	
void find_subs_mpi(int** mat,int ssum,int size,int ssize)
{	
	int max_off=size-ssize+1;
	int **wynik;
	malloc2dfloat(&wynik,ssize,ssize);
	for (int o=0;o<max_off;o++)
	{	int sum=0;
		for (int i=0;i<ssize;i++)
		{
			for( int j=0;j<ssize;j++)
			{
				sum+=mat[i][j+o];
			}
		}
	
		if(sum==ssum)
		{
			for (int i = 0; i < ssize; i++) 
			{
				for (int j = 0; j < ssize; j++) 
				{
					wynik[i][j]=mat[i][j+o];
				}
			}
		 MPI_Send(&(wynik[0][0]), ssize*ssize, MPI_INT, 0, WYNIK, MPI_COMM_WORLD);
		}
			
	}
	free2dfloat(&wynik);
	

}

void show_mat(int**mat,int k)
{

				for (int i = 0; i < k; i++) 
				{
					for (int j = 0; j < k; j++) 
					{
						printf("%3d ", mat[i][j]);
					}
					printf("\n");
				}
				printf("End of Show \n");
}


