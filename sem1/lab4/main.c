//----------------------------------------------------------------
//        --  Лабортаторна робота №5 Варіант 27
//        --  F1: d = MAX(B + C) + MIN(A + (MA * ME)*B)
//        --  F2: f = MAX(MG*MK) - MIN(ML + MН)
//        --  F3: O = (MP*MR)*S + V
//        --  Шкардибарда І. ІВ-82
//        --  Дата 11.11.2020
//----------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "data.h"
void t1(int N);
void t2(int N);
void t3(int N);	
int main(int argc, char **argv){
	// GOMP_CPU_AFFINITY="1 2 3" ./main -> bind thread to CPU
	// OMP_STACKSIZE=10M ./main -> set new stecksize
	// sleep() -> sleep for some time
	int N = 4;
	omp_set_nested(1);
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			t1(N);
		}
		#pragma omp section
		{
			t2(N);
		}
		#pragma omp section
		{
			t3(N);
		}
	}	
	return 0;
}
void t1(int N){
	int **MA = (int **)malloc(N * sizeof(int *));
	int **ME = (int **)malloc(N * sizeof(int *));
	int A[N];
	int B[N];
	int C[N];
	int d;
	for (int i = 0; i < N; ++i){
		MA[i] = malloc(N * sizeof(int));
		ME[i] = malloc(N * sizeof(int));
	}
	printf("T1 is started:\n");
	fill_mx(MA, N, 1);
	fill_mx(ME, N, 1);
	fill_vect(A, N, 1);
	fill_vect(B, N, 1);
	fill_vect(C, N, 1);
	d = F1(MA, ME, A, B, C, N);
	#pragma omp critical
	{
		printf("Result of F1 is %d\n", d);
		printf("T1 is finished\n");
	}
}
void t2(int N){
	int **MG = (int **)malloc(N * sizeof(int *));
	int **MK = (int **)malloc(N * sizeof(int *));
	int **ML = (int **)malloc(N * sizeof(int *));
	int **MH = (int **)malloc(N * sizeof(int *));
	int f;
	for (int i = 0; i < N; ++i){
		MG[i] = malloc(N * sizeof(int));
		MK[i] = malloc(N * sizeof(int));
		ML[i] = malloc(N * sizeof(int));
		MH[i] = malloc(N * sizeof(int));
	}
	printf("T2 is started:\n");
	fill_mx(MG, N, 2);
	fill_mx(ML, N, 2);
	fill_mx(MK, N, 2);
	fill_mx(MH, N, 2);
	f = F2(MG, MK, ML, MH, N);
	#pragma omp critical 
	{
		printf("Result of F2 is %d\n", f);
		printf("T2 is finished\n");
	}
}
void t3(int N){
	int **MP = (int **)malloc(N * sizeof(int *));
	int **MR = (int **)malloc(N * sizeof(int *));
	int S[N];
	int V[N];
	int *O;
	for (int i = 0; i < N; ++i){
		MP[i] = malloc(N * sizeof(int));
		MR[i] = malloc(N * sizeof(int));
	}
	printf("T3 is started:\n");
	fill_mx(MP, N, 3);
	fill_mx(MR, N, 3);
	fill_vect(S, N, 3);
	fill_vect(V, N, 3);
	O = F3(MP, MR, S, V, N);
	#pragma omp critical
	{
		printf("Result of F3 is vect: ");
		for (int i = 0; i < N; i++){
			printf("%d ", O[i]);
		}
		printf("\nT3 is finished\n");
	}
	free(O);	
}
