// voids and functions to deal with Matrixes
void mx_product(int N, int mx1[][N], int mx2[][N], int res_mx[][N]){
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			res_mx[i][j] = 0;
			for (int k = 0; k < N; k++){
				res_mx[i][j] += mx1[i][j] * mx2[k][j];
			}
		}
	}
}
void mx_sum(int N, int mx1[][N], int mx2[][N], int res_mx[][N]){
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			res_mx[i][j] = mx1[i][j] + mx2[i][j];
		}
	}
}
int mx_min(int N, int mx[][N]){
	int res = mx[0][0];
	for (int i = 1; i < N; i++)
	for (int j = 1; j < N; j++)
	if (mx[i][j] < res){
		res = mx[i][j];
	}
	return res;
}
int mx_max(int N, int mx[][N]){
	int res = mx[0][0];
	for (int i = 1; i < N; i++)
	for (int j = 1; j < N; j++)
	if (mx[i][j] > res){
		res = mx[i][j];
	}
	return res;
}
void fill_mx(int N, int mx[][N], int num){
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			mx[i][j] = num;
		}
	}
}
// Voids and functions to deal with Vectors
void vect_sum(int N, int v1[], int v2[], int res_vect[]){
	for (int i = 0; i < N; i++){
		res_vect[i] = v1[i] + v2[i];
	}
}
int vect_max(int N, int v1[]){
	int res = v1[0];
	for (int i = 0; i < N; i++){
		if (v1[i] > res){
			res = v1[i];
		}
	}
	return res;
}
int vect_min(int N, int v1[]){
	int res = v1[0];
	for (int i = 0; i < N; i++){
		if (v1[i] < res){
			res = v1[i];
		}
	}
	return res;
}
void fill_vect(int N, int v1[], int num){
	for (int i = 0; i < N; i++){
		v1[i] = num;
	}
}
// Void to deal with product of Matrix and Vector
void product(int N, int mx[][N], int v1[], int res_vect[]){
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			res_vect[i] += mx[i][j] * v1[j];
		}
	}
}
// Functions F1, F2, F3
int F1( int N,
		int mx1[][N],
		int mx2[][N],
		int A[],
		int B[],
		int C[]
){
	int res;
	int tmp_vect[N];
	int tmp_vect2[N];
	int tmp_mx[N][N];
	vect_sum(N, B, C, tmp_vect);
	res = vect_max(N, tmp_vect);
	mx_product(N, mx1, mx2, tmp_mx);
	product(N, tmp_mx, B, tmp_vect);
	vect_sum(N, tmp_vect, A, tmp_vect2);
	res += vect_min(N, tmp_vect2);
	return res;
}
int F2( int N,
		int mx1[][N],
		int mx2[][N],
		int mx3[][N],
		int mx4[][N]
){
	int res;
	int tmp_mx1[N][N];
	int tmp_mx2[N][N];
	mx_product(N, mx1, mx2, tmp_mx1);
	mx_sum(N, mx3, mx4, tmp_mx2);
	res = mx_max(N, tmp_mx1);
	res -= mx_min(N, tmp_mx2);
	return res;
}
int *F3(int N,
		int mx1[][N],
		int mx2[][N],
		int v1[],
		int v2[]
){
	int res_vect[N];
	int tmp_mx[N][N];
	mx_product(N, mx1, mx2, tmp_mx);
	product(N, tmp_mx, v1, res_vect);
	vect_sum(N, res_vect, v2, res_vect);
	return *res_vect;
}















