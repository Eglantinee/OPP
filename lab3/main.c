//----------------------------------------------------------------
//        --  Лабортаторна робота №4 Варіант 27
//        --  F1: d = MAX(B + C) + MIN(A + (MA * ME)*B)
//        --  F2: f = MAX(MG*MK) - MIN(ML + MН)
//        --  F3: O = (MP*MR)*S + V
//        --  Шкардибарда І. ІВ-82
//        --  Дата 14.10.2020
//----------------------------------------------------------------
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>
#include "data.h"
pthread_attr_t change_atrr(int cpu, int prior);
void *t1(void *args);
void *t2(void *args);
void *t3(void *args);
bool suspend = true;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
	
int main(int argc, char **argv){
	int N = 4;
	pthread_t T1, T2, T3;
	pthread_attr_t attr;
	attr = change_atrr(3, 90);
	pthread_create(&T1, &attr, t1, (void *)&N);
	pthread_attr_destroy(&attr);
	attr = change_atrr(1, 60);
	pthread_create(&T2, &attr, t2, (void *)&N);
	pthread_attr_destroy(&attr);
	attr = change_atrr(5, 30);
	pthread_create(&T3, &attr, t3, (void *)&N);
	pthread_mutex_lock(&lock);
	suspend = false;
	pthread_mutex_unlock(&lock);
	pthread_cond_signal(&cond);
	printf("T2 resumed\n");
	pthread_join(T1, NULL);	
	pthread_join(T2, NULL);
	pthread_join(T3, NULL);
	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&lock);
	return 0;
}
pthread_attr_t change_atrr(int cpu, int prior){
	struct sched_param param;
	cpu_set_t cpuset;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	//clear cpuset need every time clear and set for each thread
	CPU_ZERO(&cpuset);
	CPU_SET(cpu, &cpuset);
	pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpuset);
	// changing priority of the thread	
	pthread_attr_setschedpolicy(&attr, SCHED_FIFO); 	
	pthread_attr_getschedparam(&attr, &param);
	param.sched_priority = prior;
	pthread_attr_setschedparam(&attr, &param);
	return attr;
}
void *t1(void *args){
	int *arg = (int *)args;
	int N = *arg;
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
	sleep(1.2);
	printf("Result of F1 is %d\n", d);
	printf("T1 is finished\n");
	return NULL;
}
void *t2(void *args){
	pthread_mutex_lock(&lock);
	while (suspend){
		printf("T2 suspended\n");
		pthread_cond_wait(&cond, &lock);
	}
	pthread_mutex_unlock(&lock);
	int *arg = (int *)args;
	int N = *arg;
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
	sleep(1.2);
	printf("Result of F2 is %d\n", f);
	printf("T2 is finished\n");
	return NULL;
}
void *t3(void *args){
	int *arg = (int *)args;
	int N = *arg;
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
	sleep(1.5);
	printf("Result of F3 is vect: ");
	for (int i = 0; i < N; i++){
		printf("%d ", O[i]);
	}
	printf("\nT3 is finished\n");
	free(O);	
	return NULL;
}
