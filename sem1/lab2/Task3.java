public class Task3 extends Thread{
    public void run(){
        int N = Lab2.N;
        int[][] MP = new int[N][N];
        int[][] MR = new int[N][N];
        int[] S = new int[N];
        int[] V = new int[N];
        int[] O;
        System.out.println("T3 is started");
        Data.fill_mx(MP, 3);
        Data.fill_mx(MR, 3);
        Data.fill_vect(S, 3);
        Data.fill_vect(V, 3);
        O = Data.F3(MP, MR, S, V);
        try {
            sleep(2000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.print("Res of F3 = ");
        for (int i = 0; i < N; i++) {
            System.out.print(O[i] + " ");
        }
        System.out.println("\nT3 is finished");
    }
}