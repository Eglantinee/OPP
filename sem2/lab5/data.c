#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
// voids and functions to deal with Matrixes
int **mx_product(int **mx1, int **mx2, int n, int m, int from)
{
    int **result = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < m; i++)
    {
        result[i] = (int *)malloc(m * sizeof(int));
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int k = 0; k < m; k++)
            {
                result[i][j] += mx1[from + i][k] * mx2[k][j];
            }
        }
    }
    return result;
}
void mx_const_prodaction(int **mx, int n, int m, int from, int number)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			mx[from + i][j] *= number;
		}
	}
}
int  **mx_sum(int **mx1, int **mx2, int n, int m, int from)
{
	int **resMX = (int **)malloc(n * sizeof(int *));
	for (int i = 0; i < n; i++)
	{
		resMX[i] = (int *)malloc(m * sizeof(int **));
		for (int j = 0; j < m; j++)
		{
			resMX[i][j] = mx1[i][j] + mx2[from + i][j];
		}
	}
	return resMX;
}
void fill_mx(int **mx, int N, int num){
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			mx[i][j] = num;
		}
	}
}
int vect_max(int *v1, int n, int from){
	int res = v1[from];
	for (int i = 0; i < n; ++i){
		if (v1[i] > res){
			res = v1[i];
		}
	}
	return res;
}
int max(int num1, int num2)
{
	return (num1>=num2)? num1: num2;
}

void fill_vect(int *v1, int N, int num){
	for (int i = 0; i < N; i++){
		v1[i] = num;
	}
}
//Free memory which is used by matrixes
void clear_mx(int **mx, int N){
	#pragma omp parallel for
	for (int i = 0; i < N; ++i){
		free(mx[i]);
	}
	free(mx);
}
int **copyMatrix(int **mx, int n, int m, int start)
{
    int **result = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        result[i] = (int *)malloc(m * sizeof(int));
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            result[i][j] = mx[start + i][j];
        }

    }
    return result;
}
void copyToMatrix(int **mx1, int **mx2, int n, int m, int from)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; j++)
		{
			mx1[from + i][j] = mx2[i][j];
		}
	}
}
void calculations(int **resultMX, int **mx1, int **mx2, int num1, int num2, int **mx3, int n, int from, int amount)
{
	// amount -> number of elements to take == N/P
	// n -> number of elements in whole array == N
	// start -> position whom which to start calculations == 0, N/P?, 2*N/P etc
	int **firstMX = mx_product(mx1, mx2, amount, n, from);
	mx_const_prodaction(firstMX, amount, n, from, num1);
	mx_const_prodaction(mx3, amount, n, from, num2);
	int **result_mx = mx_sum(firstMX, mx3, amount, n, from);
	copyToMatrix(resultMX, result_mx, amount, n, from);
	printf("result -> %d\n", result_mx[0][0]);
}
int **inputMatrix(int N, int number){
    int **mx = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
    {
        mx[i] = (int *)malloc(N * sizeof(int));
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            mx[i][j] = number;
        }

    }
    return mx;
}
int *inputVector(int N, int number)
{
    int *vector = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
    {
        vector[i] = number;
    }
    return vector;
}
void printMatrix(int **mx, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d ", mx[i][j]);
        }
        printf("\n");
    }
}
int *copyVector(int *vect, int m, int pos)
{
    int *result = (int *)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++)
    {
        result[i] = vect[pos+i];
    }
    return result;
}

	
	










