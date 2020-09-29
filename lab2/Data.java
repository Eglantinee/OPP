public class Data {
    static int N = Lab2.N;
    private static int[][] mx_product(int[][] mx1, int[][] mx2) {
        int[][] res_mx = new int[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                res_mx[i][j] = 0;
                for (int k = 0; k < N; k++) {
                    res_mx[i][j] += mx1[i][j] * mx2[k][j];
                }
            }
        }
        return res_mx;
    }
    private static int[][] mx_sum(int[][] mx1, int[][] mx2) {
        int[][] res_mx = new int[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                res_mx[i][j] = mx1[i][j] + mx2[i][j];
            }
        }
        return res_mx;
    }
    private static int mx_min(int[][] mx) {
        int res = mx[0][0];
        for (int i = 1; i < N; i++) {
            for (int j = 1; j < N; j++) {
                if (mx[i][j] < res) {
                    res = mx[i][j];
                }
            }
        }
        return res;
    }
    private static int mx_max(int[][] mx) {
        int res = mx[0][0];
        for (int i = 1; i < N; i++) {
            for (int j = 1; j < N; j++) {
                if (mx[i][j] > res) {
                    res = mx[i][j];
                }
            }
        }
        return res;
    }
    private static int[] vect_sum(int[] v1, int[] v2) {
        int[] res_vect = new int[N];
        for (int i = 0; i < N; i++) {
            res_vect[i] = v1[i] + v2[i];
        }
        return res_vect;
    }
    private static int vect_max(int[] v1) {
        int res = v1[0];
        for (int i = 1; i < N; i++) {
            if (v1[i] > res) {
                res = v1[i];
            }
        }
        return res;
    }
    private static int vect_min(int[] v1) {
        int res = v1[0];
        for (int i = 1; i < N; i++) {
            if (v1[i] < res) {
                res = v1[i];
            }
        }
        return res;
    }
    private static int[] product(int[][] mx, int[] v1) {
        int[] res_vect = new int[N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                res_vect[i] += mx[i][j] * v1[j];
            }
        }
        return res_vect;
    }
    public static void fill_mx(int[][] mx, int num) {
        for (int i = 0; i < mx.length; i++) {
            for (int j = 0; j < mx.length; j++) {
                mx[i][j] = num;
            }
        }
    }
    public static void fill_vect(int[] v1, int num) {
        for (int i = 0; i < N; i++) {
            v1[i] = num;
        }
    }
    public static int F1(
            int[][] mx1,
            int[][] mx2,
            int[] A,
            int[] B,
            int[] C
    ) {
        int res;
        int[] tmp_vect;
        int[][] tmp_mx;
        tmp_vect = vect_sum(B, C);
        res = vect_max(tmp_vect);
        tmp_mx = mx_product(mx1, mx2);
        tmp_vect = product(tmp_mx, B);
        tmp_vect = vect_sum(tmp_vect, A);
        res += vect_min(tmp_vect);
        return res;
    }
    public static int F2(
            int[][] mx1,
            int[][] mx2,
            int[][] mx3,
            int[][] mx4
    ) {
        int res;
        int[][] tmp_mx1;
        int[][] tmp_mx2;
        tmp_mx1 = mx_product(mx1, mx2);
        tmp_mx2 = mx_sum(mx3, mx4);
        res = mx_max(tmp_mx1);
        res -= mx_min(tmp_mx2);
        return res;
    }
    public static int[] F3(
            int[][] mx1,
            int[][] mx2,
            int[] v1,
            int[] v2
    ){
        int[] res_vect;
        int[][] tmp_mx;
        tmp_mx = mx_product(mx1, mx2);
        res_vect = product(tmp_mx, v1);
        res_vect = vect_sum(res_vect, v2);
        return res_vect;
    }
}
