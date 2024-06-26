/*
Q.2 Write an MPI program to find the min number from randomly generated 1000
numbers (stored in array) on a cluster (Hint: Use MPI_Reduce) [15] 
*/


#include<stdio.h>
#include<stdlib.h> 
#include<mpi.h> 

#define MAX 1000
int main(int argc , char *argv[])
{
    int size,rank;
    int local_min = MAX;
    int local_arr[MAX];
    int global_min = MAX;

    MPI_Init(&argc , &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    srand(rank);
    for(int i =0; i<MAX; i++)
    {
        local_arr[i] = rand()%100;
        if(local_min > local_arr[i])
        {
            local_min = local_arr[i];
        }
    }

    MPI_Reduce(&local_min , &global_min , 1 , MPI_INT , MPI_MIN ,0, MPI_COMM_WORLD);
    printf("Process : %d local min %d \n" , rank , local_min);

    if(rank == 0)
    {
        printf("Global min %d " , global_min);
    }
    MPI_Finalize();
    return 0;

}
