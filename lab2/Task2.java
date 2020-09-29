public class Task2 extends Thread{
    public void run(){
        int N = Lab2.N;
        int[][] MG = new int[N][N];
        int[][] MK = new int[N][N];
        int[][] ML = new int[N][N];
        int[][] MH = new int[N][N];
        int f;
        System.out.println("T2 is started");
        Data.fill_mx(MG, 2);
        Data.fill_mx(MK, 2);
        Data.fill_mx(ML, 2);
        Data.fill_mx(MH, 2);
        f = Data.F2(MG, MK, ML, MH);
        try {
            sleep(1500);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Result of F2 = " + f);
        System.out.println("T2 is finished");
    }
}