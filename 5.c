#include<stdio.h>
#include<mpi.h>
#include<string.h>


void main(int argc, char** argv){

int r,t,n;

char msg[3][20]={"HELLO","CSE","RVCE"},buff[20];

MPI_Status status;

MPI_Init(&argc,&argv);

MPI_Comm_rank(MPI_COMM_WORLD,&r);
MPI_Comm_size(MPI_COMM_WORLD,&n);

if(r!=0){
strcpy(buff,msg[r-1]);
MPI_Send(&buff,20,MPI_CHAR,0,0,MPI_COMM_WORLD);
}
else{
for(t=1;t<n;t++){
MPI_Recv(&buff,20,MPI_CHAR,t,0,MPI_COMM_WORLD,&status);
printf("\nP %d recvd %s from P %d\n",r,buff,t);
}
}


MPI_Finalize();

}
