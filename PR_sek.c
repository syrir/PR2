#include "functions.c"







int main()
{


	srand(0);
	int ** mat;
	int size_of_submatrix=2;
	int size_of_matrix=6;
	int searched_sum=28;
	mat=populate(size_of_matrix);
	show_mat(mat,size_of_matrix);
	find_subs_seq(mat,searched_sum,size_of_matrix,size_of_submatrix);
	destroy_mat(mat,size_of_matrix);
	
	

	
}

