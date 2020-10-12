#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>
#include "test.h"
pthread_attr_t change_atrr(int cpu, int prior);
void *t1(void *args);
void *t2(void *args);
void *t3(void *args);	
int main(int argc, char **argv){
	int N = 4;
	pthread_t T1, T2, T3;
	pthread_attr_t attr;
	attr = change_atrr(1, 5);
	pthread_create(&T1, &attr, t1, (void *)&N);
	attr = change_atrr(2, 7);
	pthread_create(&T2, &attr, t2, (void *)&N);
	printf("T2 is stopped\n");
	pthread_kill(T2, SIGSTOP);
	pthread_kill(T2, SIGCONT);
	printf("T2 is resumed\n");
	attr = change_atrr(3, 9);
	pthread_create(&T3, &attr, t3, (void *)&N);
	pthread_join(T1, NULL);	
	pthread_join(T2, NULL);
	pthread_join(T3, NULL);
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
	pthread_attr_getschedparam(&attr, &param);
	param.sched_priority = prior;
	pthread_attr_setschedparam(&attr, &param);
	return attr;
}
void *t1(void *args){
	int *arg = (int *)args;
	int N = *arg;
	int MA[N][N];
	int ME[N][N];
	int A[N];
	int B[N];
	int C[N];
	int d;
	printf("T1 is started:\n");
	fill_mx(N, MA, 1);
	fill_mx(N, ME, 1);
	fill_vect(N, A, 1);
	fill_vect(N, B, 1);
	fill_vect(N, C, 1);
	d = F1(N, MA, ME, A, B, C);
	sleep(1.2);
	printf("Result of F1 is %d\n", d);
	printf("T1 is finished\n");
	pthread_exit(0);
}
void *t2(void *args){
	int *arg = (int *)args;
	int N = *arg;
	int MG[N][N];
	int MK[N][N];
	int ML[N][N];
	int MH[N][N];
	int f;
	printf("T2 is started:\n");
	fill_mx(N, MG, 2);
	fill_mx(N, MK, 2);
	fill_mx(N, ML, 2);
	fill_mx(N, MH, 2);
	f = F2(N, MG, MK, ML, MH);
	sleep(1.2);
	printf("Result of F2 is %d\n", f);
	printf("T2 is finished\n");
	pthread_exit(0);
}
void *t3(void *args){
	int *arg = (int *)args;
	int N = *arg;
	int MP[N][N];
	int MR[N][N];
	int S[N];
	int V[N];
	int *O;
	printf("T3 is started:\n");
	fill_mx(N, MP, 3);
	fill_mx(N, MR, 3);
	fill_vect(N, S, 3);
	fill_vect(N, V, 3);
	O = F3(N, MP, MR, S, V);
	sleep(1.5);
	printf("Result of F3 is vect: ");
	for (int i = 0; i < N; i++){
		printf("%d ", O[i]);
	}
	printf("\nT3 is finished\n");
	free(O);	
	pthread_exit(0);
}
	
	
	
	
	
	
	
	
	
	
	
	
