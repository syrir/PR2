#include "stdio.h"
#include "stdlib.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>


#define END 5
#define WYNIK 6


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
	
void find_subs_seq(int** mat,int ssum,int size,int k)
{
	int n1=size-k;
	int licznik=0;
	int i, j, ioff, joff, off_cnt;
	off_cnt = size - k + 1;
		for (ioff = 0; ioff < off_cnt; ioff++)
		{
			
	
			for (joff = 0; joff < off_cnt; joff++) 
			{
				licznik++;
				int sum=0;
			
				for (i = 0; i < k; i++) 
				{
					for (j = 0; j < k; j++) 
					{
						sum+=mat[i+ioff][j+joff];
						//printf("%3d ", mat[i+ioff][j+joff]);
					}
					//printf("\n");

				}
				//printf("suma podmacierzy = %d\n",sum);
				if(sum==ssum)
				{
						for (i = 0; i < k; i++) 
				{
					for (j = 0; j < k; j++) 
					{
						printf("%3d ", mat[i+ioff][j+joff]);
					}
					printf("\n");

				}
				printf("suma podmacierzy = %d\n",sum);
				}
			}
		}
		printf("ilosc podmacierzy: %d\n",licznik);

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


