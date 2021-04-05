//----------------------------------------------------------------
//        --  Лабортаторна робота №5 Варіант 24
//        --  Шкардибарда І. ІВ-82
// 		  --  МU= MD*MC *d + max(Z)*MR
//        --  Дата 22.13.2021
//----------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "data.h"
void t1(int N);
void t2(int N);
void t3(int N);
int **MU;
int **MD;
int **MC;
int d;
int *Z;
int **MR;
int main(int argc, char **argv){
    int N = 4;
    int P = 4;
    int z = 0;
    MU = (int **)malloc(N * sizeof(int **));
    for (int i = 0; i < N; ++i)
		MU[i] = (int *)malloc(N * sizeof(int *));
	omp_set_num_threads(4);
    #pragma omp parallel 
    {
		printf("%d\n", omp_get_thread_num());
		//Потік Т1:
		if (omp_get_thread_num() == 1)
		{
			printf("T1 started\n");
			//Введення d.
			d = 1;
		}
		//Потік Т2:
		if (omp_get_thread_num() == 2)
		{
			printf("T2 started\n");
		}
		//Потік Т3:
		if (omp_get_thread_num() == 3)
		{
			printf("T3 started\n");
			//Введення MC, MR.
			MC = inputMatrix(N, 3);
			MR = inputMatrix(N, 3);
		}
		//Потік Т4:
		if (omp_get_thread_num() == 4)
		{
			printf("T4 started\n");
			//Введення Z, MD.
			MD = inputMatrix(N, 4);
			Z = inputVector(N, 4);
		}
		//Чекати на введення даних іншими потоками
		#pragma omp barrier
		if (omp_get_thread_num() == 1)
		{
			//Обчислення z1 = max(Zh)
			int z1 = vect_max(Z, N / P, 0);
			#pragma omp critical(max)
			{
				//Обчислення z = max(z, z1)
				z = max(z, z1);
			}
		}
		if (omp_get_thread_num() == 2)
		{
			//Обчислення z2 = max(Zh)
			int z2 = vect_max(Z, N / P, N/P);
			#pragma omp critical(max)
			{
				//Обчислення z = max(z, z2)
				z = max(z, z2);
			}
		}
		if (omp_get_thread_num() == 3)
		{
			//Обчислення z3 = max(Zh)
			int z3 = vect_max(Z, N / P, 2*N/P);
			#pragma omp critical(max)
			{
				//Обчислення z = max(z, z3)
				z = max(z, z3);
			}
		}
		if (omp_get_thread_num() == 4)
		{
			//Обчислення z4 = max(Zh)
			int z4 = vect_max(Z, N / P, 3*N/P);
			#pragma omp critical(max)
			{
				//Обчислення z = max(z, z4)
				z = max(z, z4);
			}
		}
		//Чекати на обчислення даних іншими потоками
		#pragma omp barrier
		if (omp_get_thread_num() == 1)
		{
			int **MD1; 
			int d1;
			int z1;
			//Копіювання даних у локальні змінні:
			#pragma omp critical ( copy )
			{
				MD1 = copyMatrix(MD, N, N , 0);
				d1 = d;
				z1 = z;
			}
			//Обчислення MUh = MD1 * MCh * d1 + z1 * MRh
			calculations(MU, MD1, MC, d1, z1, MR, N, 0, N/P);
		}
		if (omp_get_thread_num() == 2)
		{
			int **MD2; 
			int d2;
			int z2;
			//Копіювання даних у локальні змінні:
			#pragma omp critical ( copy )
			{
				MD2 = copyMatrix(MD, N, N , 0);
				d2 = d;
				z2 = z;
			}
			//Обчислення MUh = MD2 * MCh * d2 + z2* MRh
			calculations(MU, MD2, MC, d2, z2, MR, N, N/P, N/P);
		}
		if (omp_get_thread_num() == 3)
		{
			int **MD3; 
			int d3;
			int z3;
			//Копіювання даних у локальні змінні:
			#pragma omp critical ( copy )
			{
				MD3 = copyMatrix(MD, N, N , 0);
				d3 = d;
				z3 = z;
			}
			//Обчислення MUh = MD3 * MCh * d3 + z3 * MRh
			calculations(MU, MD3, MC, d3, z3, MR, N, 2*N/P, N/P);
		}
		if (omp_get_thread_num() == 4)
		{
			int **MD4; 
			int d4;
			int z4;
			//Копіювання даних у локальні змінні:
			#pragma omp critical ( copy )
			{
				MD4 = copyMatrix(MD, N, N , 0);
				d4 = d;
				z4 = z;
			}
			//Обчислення MUh = MD4 * MCh * d4 + z4 * MRh
			calculations(MU, MD4, MC, d4, z4, MR, N, 3*N /P, N/P);
		}
		//Чекати на обчислення даних іншими потоками
		#pragma omp barrier
		if (omp_get_thread_num() == 3)
		{
			//Виведення MU.
			printMatrix(MU, N, N);
		}
    }
    return 0;
}
