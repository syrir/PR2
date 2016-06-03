

#include "stdio.h"
#include "stdlib.h"
#include "iostream"
#include <conio.h>

using namespace std;


int main()
{


	srand(0);
	int ** mat;
	int n,s,k=3;
	n=50;
	s=49;
	mat=new int*[n];
	for (int i=0;i<n;i++)
	{
		mat[i]=new int[n];
		for(int j=0;j<n;j++)
		{
			mat[i][j]=rand()%9+1;
		}
	}
	int n1=n-k;

	int i, j, ioff, joff, off_cnt;

	off_cnt = n - k + 1;
	for (ioff = 0; ioff < off_cnt; ioff++)
	{
		for (joff = 0; joff < off_cnt; joff++) 
		{
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
			if(sum==s)
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



	cin.get();
	system("pause");


}

