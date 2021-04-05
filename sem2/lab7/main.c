//----------------------------------------------------------------
//        --  Лабортаторна робота №6 Варіант 27
//        --  F1: d = MAX(B + C) + MIN(A + (MA * ME)*B)
//        --  F2: f = MAX(MG*MK) - MIN(ML + MН)
//        --  F3: O = (MP*MR)*S + V
//        --  Шкардибарда І. ІВ-82
//        --  Дата 23.11.2020
//----------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "data.h"


int main(int argc, char *argv[]){
    int N = 4;
    int P = 4;
    int rank;
    int nnodes = P;
    int index[4] = {2, 4, 6, 8};
    int edges[] = {2, 4 , 1, 3, 2, 4, 3, 1};
    int *MD;
    int *MB;
    int *W = (int *)malloc(N * sizeof(int));
    MPI_Comm comm_graph;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0){
        printf("Start T1\n");
        MPI_Graph_create(MPI_COMM_WORLD, nnodes, index, edges, 1, &comm_graph);
        
        
        int *C = (int *)malloc(N * sizeof(int));
        int *MD1 = (int *)malloc(N *sizeof(int));
        int a;
        int *E = (int *)malloc(N * sizeof(int));
        int *MA = (int *)malloc(N*N *sizeof(int));
        int *MB1 = (int *)malloc(N*N *sizeof(int));
        int d;
        MPI_Bcast(C, N, MPI_INT, 2, comm_graph);
        MPI_Scatter(MD, N, MPI_INT, MD1, N, MPI_INT, 3, comm_graph);
        int a1 = vect_max(vect_and_mx_product(C, MD1, N/P, N), N/P);
        MPI_Allreduce(&a1, &a, 1, MPI_INT, MPI_MAX, comm_graph);
        MPI_Bcast(E, N, MPI_INT, 1, comm_graph);
        MPI_Bcast(MA, N, MPI_INT, 2, comm_graph);
        MPI_Scatter(MB, N, MPI_INT, MB1, N, MPI_INT, 1, comm_graph);
        MPI_Recv(&d, 1, MPI_INT, 3, 0, comm_graph, NULL);
        int *W1 = calculations(a, E, MA, MB1, d, N, N/P);
        MPI_Gather(W1, N/P, MPI_INT, W, N/P, MPI_INT, 2, comm_graph);
        
    }
    if (rank == 1){
		printf("Start T2\n");
		MPI_Graph_create(MPI_COMM_WORLD, nnodes, index, edges, 1, &comm_graph);
        MB = inputMatrix(N, N, 2);
        int *E = inputVector(N, 2);
        
        
        int *C = (int *)malloc(N * sizeof(int));
        int *MD2 = (int *)malloc(N*N *sizeof(int));
        int a;
        int *MA = (int *)malloc(N*N *sizeof(int));
        int *MB2 = (int *)malloc(N*N *sizeof(int));
        int d;
        MPI_Bcast(C, N, MPI_INT, 2, comm_graph);
        MPI_Scatter(MD, N, MPI_INT, MD2, N, MPI_INT, 3, comm_graph);
        int a2 = vect_max(vect_and_mx_product(C, MD2, N/P, N), N/P);
        MPI_Allreduce(&a2, &a, 1, MPI_INT, MPI_MAX, comm_graph);
        MPI_Bcast(E, N, MPI_INT, 1, comm_graph);
        MPI_Bcast(MA, N, MPI_INT, 2, comm_graph);
        MPI_Scatter(MB, N, MPI_INT, MB2, N, MPI_INT, 1, comm_graph);
        MPI_Recv(&d, 1, MPI_INT, 3, 0, comm_graph, NULL);
        int *W2 = calculations(a, E, MA, MB2, d, N, N/P);
        MPI_Gather(W2, N/P, MPI_INT, W, N/P, MPI_INT, 2, comm_graph);
         
    }
    if (rank == 2){
		printf("Start T3\n");
		MPI_Graph_create(MPI_COMM_WORLD, nnodes, index, edges, 1, &comm_graph);
		int *C = inputVector(N, 3);
		int *MA = inputMatrix(N, N, 3);
		
		
        int *MD3 = (int *)malloc(N*N *sizeof(int));
        int a;
        int *E = (int *)malloc(N * sizeof(int));
        int *MB3 = (int *)malloc(N*N *sizeof(int));
        int d;
		MPI_Bcast(C, N, MPI_INT, 2, comm_graph);
		MPI_Scatter(MD, N, MPI_INT, MD3, N, MPI_INT, 3, comm_graph);
		int a3 = vect_max(vect_and_mx_product(C, MD3, N/P, N), N/P);
		MPI_Allreduce(&a3, &a, 1, MPI_INT, MPI_MAX, comm_graph);
		MPI_Bcast(E, N, MPI_INT, 1, comm_graph);
		MPI_Bcast(MA, N, MPI_INT, 2, comm_graph);
		MPI_Scatter(MB, N, MPI_INT, MB3, N, MPI_INT, 1, comm_graph);
		MPI_Recv(&d, 1, MPI_INT, 3, 0, comm_graph, NULL);
		int *W3 = calculations(a, E, MA, MB3, d, N, N/P);
		MPI_Gather(W3, N/P, MPI_INT, W, N/P, MPI_INT, 2, comm_graph);
		for (int i = 0; i < N; i++)
		{
			printf("%d ", W[i]);
		}
        
    }
    if (rank == 3){
		printf("Start T4\n");
		MPI_Graph_create(MPI_COMM_WORLD, nnodes, index, edges, 1, &comm_graph);
		int d = 4;
		MD = inputMatrix(N, N, 4);
		
		
		int *MD4 = (int *)malloc(N*N *sizeof(int));
		int *C = (int *)malloc(N * sizeof(int));
		int a;
		int *E = (int *)malloc(N * sizeof(int));
		int *MA = (int *)malloc(N*N *sizeof(int));
		int *MB4 = (int *)malloc(N*N *sizeof(int));
		MPI_Bcast(C, N, MPI_INT, 2, comm_graph);
		MPI_Scatter(MD, N, MPI_INT, MD4, N, MPI_INT, 3, comm_graph);
		int a4 = vect_max(vect_and_mx_product(C, MD4, N/P, N), N/P);
		MPI_Allreduce(&a4, &a, 1, MPI_INT, MPI_MAX, comm_graph);
		MPI_Bcast(E, N, MPI_INT, 1, comm_graph);
		MPI_Bcast(MA, N, MPI_INT, 2, comm_graph);
		MPI_Scatter(MB, N, MPI_INT, MB4, N, MPI_INT, 1, comm_graph);
		MPI_Send(&d, 1, MPI_INT, 0, 0, comm_graph);
		MPI_Send(&d, 1, MPI_INT, 1, 0, comm_graph);
		MPI_Send(&d, 1, MPI_INT, 2, 0, comm_graph);
		int *W4 = calculations(a, E, MA, MB4, d, N, N/P);
		MPI_Gather(W4, N/P, MPI_INT, W, N/P, MPI_INT, 2, comm_graph);
	}
    MPI_Finalize();
    return 0;
}
