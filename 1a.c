#include<stdio.h>
#include<omp.h>
#include <stdlib.h>

int main(){
  double st,x,y,z;
  int c = 0;
  printf("it/th \t");
  for(int i=1;i<=8;i*=2)
    printf("pi \t %d\t",i);
  
  for(int i=1000;i<=1000000;i*=10){
    printf("\n %d \t",i);

    for(int nt = 1; nt<=8 ; nt*=2){
      st = omp_get_wtime();
      c = 0;
      srand(354127687);
      #pragma omp parallel for num_threads(nt)
      for(int k=1;k<i;k++){
        x = (double) rand()/RAND_MAX;
        y = (double) rand()/RAND_MAX;
        z = x*x + y*y;
        if(z <= 1) c++;
      }
      double pi = (double) c/i*4;
      printf("%lf\t%lf\t",pi,omp_get_wtime()-st);
    }
  }
}
