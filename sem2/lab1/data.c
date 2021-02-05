#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
int  *sorts(int *v1, int *v2, int N);
// voids and functions to deal with Matrixes
void mx_product(int **mx1, int **mx2, int **res_mx, int N){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            res_mx[i][j] = 0;
            for (int k = 0; k < N; k++){
                res_mx[i][j] += mx1[i][k] * mx2[k][j];
            }
        }
    }
}

void fill_mx(int **mx, int N, int num){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            mx[i][j] = num;
        }
    }
}
// Voids and functions to deal with Vectors
void vect_sum(int v1[], int v2[], int N){
    for (int i = 0; i < N; i++){
        v1[i] += v2[i];
    }
}

void fill_vect(int v1[], int N, int num){
    for (int i = 0; i < N; i++){
        v1[i] = num;
    }
}
// Void to deal with product of Matrix and Vector
void product(int **mx, int v1[], int res_vect[], int N){
    for (int i = 0; i < N; i++){
        res_vect[i] = 0;
        for (int j = 0; j < N; j++){
            res_vect[i] += mx[i][j] * v1[j];
        }
    }
}

//Free memory which is used by matrixes
void clear_mx(int **mx, int N){
    for (int i = 0; i < N; ++i){
        free(mx[i]);
    }
    free(mx);
}
// A utility function to swap two elements
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int  *sort(int d, int *B, int *Z, int **MM, int N){

    int *vect1 = (int *)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++){
        B[i] *= d;
    }

    product(MM, Z, vect1, N);
    vect_sum(B, vect1, N);
    quickSort(B, 0, N);
    fill_vect(Z, N, 3);
    int *F = sorts(Z, B, N);
    printf("************************************\n");
    for (int i = 0; i < 2 * N; i++){
        printf("%d ", F[i]);
    }
    printf("\n************************************\n");

    return B;
}

void random_mx(int **mx, int N){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            mx[i][j] = rand() % N;
        }
    }
}

int  *sorts(int *v1, int *v2, int N){
    int *result_vector = (int *)malloc(2 * N * sizeof(int));
    int i = 0;
    int j = 0;
    int k = 0;
    bool flag = true;
    while (flag){
        while (v1[i] >= v2[j]){
            result_vector[k] = v2[j];
            printf("here we go %d, %d\n", i, j);
            if (j == N - 1){
                while (i < N){
                    result_vector[k + 1] = v1[i];
                    i++;
                    k++;
                }
                flag = false;
            }
            j++;
            k++;
        }
        printArray(result_vector, k);
        printf("%d %d %d\n", i, j, k);
        while (v1[i] < v2[j]){
            result_vector[k] = v1[i];
            if (i == N - 1){
                while (j < N){
                    result_vector[k + 1] = v2[j];
                    j++;
                    k++;
                }
                flag = false;
            }
            i++;
            k++;
        }
    }
    return result_vector;
}
