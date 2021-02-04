#include <stdlib.h>
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
void mx_sum(int **mx1, int **mx2, int **res_mx, int N){
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			res_mx[i][j] = mx1[i][j] + mx2[i][j];
		}
	}
}
int mx_min(int **mx, int N){
	int res = mx[0][0];
	for (int i = 1; i < N; i++)
	for (int j = 1; j < N; j++)
	if (mx[i][j] < res){
		res = mx[i][j];
	}
	return res;
}
int mx_max(int **mx, int N){
	int res = mx[0][0];
	for (int i = 1; i < N; i++)
	for (int j = 1; j < N; j++)
	if (mx[i][j] > res){
		res = mx[i][j];
	}
	return res;
}
void fill_mx(int **mx, int N, int num){
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			mx[i][j] = num;
		}
	}
}
// Voids and functions to deal with Vectors
void vect_sum(int v1[], int v2[], int res_vect[], int N){
	for (int i = 0; i < N; i++){
		res_vect[i] = v1[i] + v2[i];
	}
}
int vect_max(int v1[], int N){
	int res = v1[0];
	for (int i = 0; i < N; i++){
		if (v1[i] > res){
			res = v1[i];
		}
	}
	return res;
}
int vect_min(int v1[], int N){
	int res = v1[0];
	for (int i = 0; i < N; i++){
		if (v1[i] < res){
			res = v1[i];
		}
	}
	return res;
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
// Functions F1, F2, F3
int F1( int **mx1,
		int **mx2,
		int A[],
		int B[],
		int C[],
		int N
){
	int res;
	int tmp_vect[N];
	int tmp_vect2[N];
	int **tmp_mx = (int **)malloc(N * sizeof(int *));
	for (int i = 0; i < N; ++i){
		tmp_mx[i] = (int *)malloc(N * sizeof(int));
	}
	vect_sum(B, C, tmp_vect, N);
	res = vect_max(tmp_vect, N);
	mx_product(mx1, mx2, tmp_mx, N);
	product(tmp_mx, B, tmp_vect, N);
	vect_sum(tmp_vect, A, tmp_vect2, N);
	res += vect_min(tmp_vect2, N);
	clear_mx(tmp_mx, N);
	clear_mx(mx1, N);
	clear_mx(mx2, N);
	return res;
}
int F2( int **mx1,
		int **mx2,
		int **mx3,
		int **mx4,
		int N
){
	int res;
	int **tmp_mx1 = (int **)malloc(N * sizeof(int *));
	int **tmp_mx2 = (int **)malloc(N * sizeof(int *));
	for (int i = 0; i < N; ++i){
		tmp_mx1[i] = (int *)malloc(N * sizeof(int));
		tmp_mx2[i] = (int *)malloc(N * sizeof(int));
	}
	mx_product(mx1, mx2, tmp_mx1, N);
	mx_sum(mx3, mx4, tmp_mx2, N);
	res = mx_max(tmp_mx1, N);
	res -= mx_min(tmp_mx2, N);
	clear_mx(tmp_mx1, N);
	clear_mx(tmp_mx2, N);
	clear_mx(mx1, N);
	clear_mx(mx2, N);
	clear_mx(mx3, N);
	clear_mx(mx4, N);
	return res;
}
int *F3(int **mx1,
		int **mx2,
		int v1[],
		int v2[],
		int N
){
	int *res_vect;
	int **tmp_mx = (int **)malloc(N * sizeof(int *));
	for (int i = 0; i < N; ++i){
		tmp_mx[i] = (int *)malloc(N * sizeof(int));
	}
	res_vect = malloc(N * sizeof(int));
	if (res_vect == NULL){return NULL;}
	mx_product(mx1, mx2, tmp_mx, N);
	product(tmp_mx, v1, res_vect, N);
	vect_sum(res_vect, v2, res_vect, N);
	clear_mx(tmp_mx, N);
	clear_mx(mx1, N);
	clear_mx(mx2, N);
	return res_vect;
}













