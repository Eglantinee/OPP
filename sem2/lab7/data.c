#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
// voids and functions to deal with Matrixes
int *mx_product(int *mx1, int *mx2, int rows, int columns)
{
    int *result = (int *)malloc(rows * columns * sizeof(int));
    //for (int i = 0; i < columns; i++)
    //{
        //result[i] = (int *)malloc(columns * sizeof(int));
    //}
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
			result[i * j + j] = 0;
            for (int k = 0; k < columns; k++)
            {
                result[i * j + j] += mx1[i * k + k] * mx2[k * i + j];
            }
        }
    }
    return result;
}
int *vect_and_mx_product(int *vect, int *mx, int rows, int columns)
{
	int *res_vect = (int *)malloc(rows * sizeof(int));
    for (int i = 0; i < rows; i++)
    {
		res_vect[i] = 0;
        for (int j = 0; j < columns; j++)
        {
            res_vect[i] += mx[i * j + j] * vect[j];
        }
    }
    return res_vect;
}

void fill_mx(int **mx, int N, int num){
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			mx[i][j] = num;
		}
	}
}
int vect_max(int *v1, int n){
	int res = v1[0];
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
void vect_and_const_production(int *vect, int constant, int arr_size)
{
	for (int i = 0; i < arr_size; ++i)
		vect[i] *= constant;
}
int *calculations(int a, int *E, int *MA, int *MBh, int d, int arr_size, int part_size)
{
	// part_size -> number of elements to take == N/P
	// arr_size -> number of elements in whole array == N
	// start_index -> position whom which to start calculations == 0, N/P?, 2*N/P etc
	int *part_mx = mx_product(MA, MBh, part_size, arr_size);
	int *new_vector = vect_and_mx_product(E, part_mx, part_size, arr_size);
	vect_and_const_production(new_vector, d, part_size);
	vect_and_const_production(new_vector, a, part_size);
	return new_vector;
}
int *inputMatrix(int rows, int columns, int number){
    int *mx = (int *)malloc(rows * columns * sizeof(int));
    for (int i = 0; i < rows*columns; i++)
    {
       mx[i] = number;
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

//int *copyVector(int *vect, int m, int pos)
//{
    //int *result = (int *)malloc(m * sizeof(int));
    //for (int i = 0; i < m; i++)
    //{
        //result[i] = vect[pos+i];
    //}
    //return result;
//}

//int **create_matrix(int rows, int columns)
//{
	//int **new_matrix = (int **)malloc(rows * sizeof(int *));
	//for (int i = 0; i < rows; ++i)
		//new_matrix[i] = (int *)malloc(columns * sizeof(int));
	//return new_matrix;
//}

//int *transform_to_array(int **mx, int rows, int columns)
//{
	//int *result_arr = (int *)malloc(rows*columns * sizeof(int));
	//for (int i = 0; i < rows; ++i)
	//{
		//for (int j = 0; j < columns; ++j)
		//{
			//result_arr[i * columns + j] = mx[i][j];
		//}
	//}
	//return result_arr;
//}

//int **transfrom_to_matrix(int *arr, int rows, int columns)
//{
	//int **result_mx = (int **)malloc(rows * sizeof(int *));
	//for (int i = 0; i < rows; i++)
	//{
		//result_mx[i] = (int *)malloc(columns * sizeof(int));
	//}
	//for (int i = 0; i < rows; ++i)
	//{
		//for (int j = 0; j < columns; ++j)
		//{
			//result_mx[i][j] = arr[i*j+j];
		//}
	//}
	//return NULL;
//}
			
	










