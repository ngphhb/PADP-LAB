#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

int main(){
  for(int d=250;d<=1400;d+=250){
    printf("\n Matrix of size %d \n",d);
    for(int nt=1;nt<=8;nt*=2){
      printf("\n Threads %d\n",nt);
      
      int **a = (int**) malloc(d*sizeof(int**));
      for(int j=0;j<d;j++)
      a[j] = (int*) malloc(d*sizeof(int*));

      int **b = (int**) malloc(d*sizeof(int**));
      for(int j=0;j<d;j++)
      b[j] = (int*) malloc(d*sizeof(int*));


      int **c = (int**) malloc(d*sizeof(int**));
      for(int j=0;j<d;j++)
      c[j] = (int*) malloc(d*sizeof(int*));

      int ct = 0;

      for(int i=0;i<d;i++)
        for(int j=0;j<d;j++)
          a[i][j] = ct++;
      
      for(int i=0;i<d;i++)
        for(int j=0;j<d;j++)
          b[i][j] = ct++;
      
      double t = omp_get_wtime();
      int i,j,k;
      #pragma omp parallel for private(j,k)
      for(i=0;i<d;i++)
        for(j=0;j<d;j++)
          for(k=0;k<d;k++)
            c[i][j]+=a[i][k]*b[k][j];
      
      t = omp_get_wtime()-t;
      printf("\n time : %lf",t);
    }
  }
}
