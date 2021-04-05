import java.util.Arrays;

public class Data {
    public static int[][] inputMatrix(int n, int num) {
        int[][] resultMatrix = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                resultMatrix[i][j] = num;
            }
        }
        return resultMatrix;
    }

    public static int[] inputVector(int n, int num) {
        int[] resultVector = new int[n];
        for (int i = 0; i < n; i++) {
            resultVector[i] = num;
        }
        return resultVector;
    }

    private static int[][] productMatrix(int[][] mx1, int[][] mx2, int n, int m, int pos) {
        int[][] resultMatrix = new int[n][m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < m; k++) {
                    resultMatrix[i][j] += mx1[pos + i][k] * mx2[k][j];
                }
            }
        }
        return resultMatrix;
    }

    private static void sumVector(int[] v1, int[] v2, int n, int pos) {
        for (int i = 0; i < n; i++) {
            v2[i] += v1[pos + i];
        }
    }

    private static int[] productMatrixVector(int[][] mx, int[] v, int n, int m) {
        int[] resultVector = new int[n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                resultVector[i] += mx[i][j] * v[j];
            }
        }
        return resultVector;
    }

    private static void productVectorNumber(int[] v, int number, int n, int pos) {
        for (int i = 0; i < n; i++) {
            v[pos + i] *= number;
        }
    }

    public static int[] sorts(int[] v1, int[] v2, int n) {
        System.out.println("i am here");
        System.out.println(Arrays.toString(v1));
        System.out.println(Arrays.toString(v2));
        int[] resultVector = new int[2 * n];
        int i = 0;
        int j = 0;
        int k = 0;
        boolean flag = true;
        while (flag) {
            while (v1[i] >= v2[j]) {
                resultVector[k] = v2[j];
                j++;
                k++;
                if (j == n) {
                    while (i < n) {
                        resultVector[k] = v1[i];
                        i++;
                        k++;
                    }
                    flag = false;
                    break;
                }
            }
            if (!flag) break;
            while (v1[i] < v2[j]) {
                resultVector[k] = v1[i];
                i++;
                k++;
                if (i == n) {
                    while (j < n) {
                        resultVector[k] = v2[j];
                        j++;
                        k++;
                    }
                    flag = false;
                    break;
                }
            }
        }
        System.out.println("i finish my work");
        return resultVector;
    }

    public static int[] sort(int d, int[] B, int[] Z, int[][] MM, int[][] MX, int n, int m, int start) {
        // n - dimension like nxn for matrix
        // m - number of rows to take
        productVectorNumber(B, d, m, start);
        System.out.println(Arrays.toString(B));
        int[][] prodMatrix = productMatrix(MM, MX, m, n, start);
        System.out.println(Arrays.deepToString(prodMatrix));
        int[] prodVector = productMatrixVector(prodMatrix, Z, m, n);
        System.out.println(Arrays.toString(prodVector));
        sumVector(B, prodVector, m, start);
        System.out.println(Arrays.toString(prodVector));
        Arrays.sort(prodVector);
        return prodVector;
    }

}
