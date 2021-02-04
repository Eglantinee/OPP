public class Task1 extends Thread {
    public void run() {
        int N = Lab2.N;
        int[][] MA = new int[N][N];
        int[][] ME = new int[N][N];
        int[] A = new int[N];
        int[] B = new int[N];
        int[] C = new int[N];
        int d;
        System.out.println("T1 is started");
        Data.fill_mx(MA, 1);
        Data.fill_mx(ME, 1);
        Data.fill_vect(A, 1);
        Data.fill_vect(B, 1);
        Data.fill_vect(C, 1);
        d = Data.F1(MA, ME, A, B, C);
        try {
            sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Result of F1 = " + d);
        System.out.println("T1 is finished");
    }
}