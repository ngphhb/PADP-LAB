#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char* argv[]){
  int r,c=0,rc,i=1000000,ri;
  double t,x,y,z,pi;
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&r);

  if(r==0)
    t = MPI_Wtime();
  
  if(r>0){
    // c = 0; doing it here gives wrong pi value becoz for P0 c will have junk value
    srand(37621961);
    for(int j=0;j<i;j++){
      x = (double) rand()/RAND_MAX;
      y = (double) rand()/RAND_MAX;
      z = x*x + y*y - 1;
      if(z<=0) c++;
    }
  }

  MPI_Reduce(&c,&rc,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
  MPI_Reduce(&i,&ri,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
  ri = ri - i;
  if(r==0){
    t = MPI_Wtime() - t;
    pi = (double) rc / (double) ri * 4;
    printf("\n pi : %lf time : %lf \n",pi,t);
  }
  MPI_Finalize();
  return 0;
}
