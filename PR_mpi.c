#include "functions_mpi.c"




int main(int argc, char **argv)
{
 	MPI_Init(&argc, &argv);
	int size,rank; 
 	MPI_Comm_size(MPI_COMM_WORLD, &size);
    	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;
	srand(0);
	int size_of_submatrix=2;
	int size_of_matrix=6;
	int searched_sum=28;
	int **array;
	int **local;
	int **master;
	int **temp;
	int nor=size_of_matrix;
	int a=1;
	int ilosc=0;
	int finished=0;
		
	malloc2dfloat(&local, size_of_submatrix, size_of_matrix);
	malloc2dfloat(&master, size_of_submatrix, size_of_submatrix);
	malloc2dfloat(&array, size_of_matrix, size_of_matrix);	
	malloc2dfloat(&temp, size_of_submatrix, size_of_matrix);

	



	if(rank==0)
	{	populate_mpi(array,size_of_matrix);
		for(int i=0;i<size_of_matrix-size_of_submatrix+1;i++)
		{
			for(int j=0;j<size_of_submatrix;j++)
			{
				for(int k=0;k<size_of_matrix;k++)
				{	
					temp[j][k]=array[j+i][k];
				}
			}

			int adress=(i%(size-1))+1;
			//printf("rozmiar: %d adres wysylki: %d \n",size,adress);
			MPI_Send(&(temp[0][0]), size_of_submatrix*size_of_matrix, MPI_INT, (i%(size-1))+1, DATA, MPI_COMM_WORLD);
		}
		for(int i=1;i<size;i++)
		{
			MPI_Send(&(temp[0][0]), size_of_submatrix*size_of_matrix, MPI_INT, i, END, MPI_COMM_WORLD);
		}
	    	while(finished!=size-1)
		{
			MPI_Recv(&(master[0][0]),size_of_submatrix*size_of_submatrix , MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			switch (status.MPI_TAG)
			{
				case WYNIK:
					//printf("odebralem wynik id: %d \n",rank);
					show_mat(master,size_of_submatrix,size_of_submatrix);
					printf("\n");
					break;
				case END:
					//printf("odebralem end id: %d \n",rank);
					finished++;
					printf("KONIEC procesu : %d \n",status.MPI_SOURCE);
					break;
				default:
					break;
			}
		}
	}
	else
	{
		while(a)
		{
			MPI_Recv(&(local[0][0]), size_of_submatrix*size_of_matrix, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			switch (status.MPI_TAG)
			{
				case DATA:
					//printf("odebralem data id: %d \n",rank);
					find_subs_mpi(local,searched_sum,size_of_matrix,size_of_submatrix);
					//show_mat(local,size_of_submatrix,size_of_matrix);
					break;
				case END:
					//printf("odebralem end id: %d \n",rank);
					MPI_Send(&(local[0][0]), size_of_submatrix*size_of_submatrix, MPI_INT, 0, END, MPI_COMM_WORLD);
					a=0;
					break;
				default:
					break;
			}
		}
	
		
	    	
	}
	MPI_Finalize();
	free2dfloat(&local);
	free2dfloat(&master);
	free2dfloat(&array);
	free2dfloat(&temp);

}

