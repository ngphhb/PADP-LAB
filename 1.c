#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

int main(){

	int dim, i, j, count=0, sum =0, k;
	printf("\n Enter the dimensions : ");
	scanf("%d",&dim);

	int **arr1 = (int **)malloc(dim * sizeof(int *));

	for (i=0; i<dim; i++)
		arr1[i] = (int *)malloc(dim * sizeof(int));
	int **arr2 = (int **)malloc(dim * sizeof(int *));
	for (i=0; i<dim; i++)
		arr2[i] = (int *)malloc(dim * sizeof(int));
	int **arr3 = (int **)malloc(dim * sizeof(int *));
	for (i=0; i<dim; i++)
		arr3[i] = (int *)malloc(dim * sizeof(int));

	for(i = 0;i < dim; i++)
		for(j = 0;j < dim; j++)
			arr1[i][j] = count++;

	for(i = 0;i < dim; i++)
		for(j = 0;j < dim; j++)
			arr2[i][j] = count++;
	int t;
	printf("Enter the num of threads : ");
	scanf("%d",&t);

	//Extra piece of code for parallelization
	double x = omp_get_wtime();
	omp_set_num_threads(t);
	#pragma omp parallel for private(j, k)
	for(i = 0;i < dim; i++)
		for(j = 0;j < dim; j++)
			for(k = 0;k < dim; k++)
				arr3[i][j] += arr1[i][k] * arr2[k][j];  //Main multiplication operation

	double y = omp_get_wtime();

	printf("Time for %d threads %lf\n",t,y-x);

	return 0;
}
