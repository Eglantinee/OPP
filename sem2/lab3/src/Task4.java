public class Task4 extends Thread{
    private final int n;
    private final int p;
    private final Monitor monitor;
    Task4(int N, int P, Monitor monitor1) {
        this.n = N;
        this.p = P;
        this.monitor = monitor1;
    }
    public void run() {
        System.out.println("T4 started");
        // введення MM, Z, d
        int d = 5;
        monitor.put_d(d);
        int[] Z = Data.inputVector(n, 1);
        monitor.put_Z(Z);
        int[][] MM = Data.inputMatrix(n, 1);
        monitor.put_MM(MM);
        // сигнал потокам Т1, Т3, Т2 про введення даних
        monitor.signal_In();
        // чекати на введення даних в потоці Т2
        monitor.wait_In();
        // копіювати введені дані у локальні змінні
        int d1 = monitor.get_d();
        int[] Z1 = monitor.get_Z();
        int[][] MM1 = monitor.get_MM();
        // обчислення Xh = sort(d4*Bh + Z4*(MM4*MXh))
        int[] Xh = Data.sort(d1, monitor.B, Z1, MM1, monitor.MX, n, n / p, 3 * n / p);
        monitor.X2 = Xh;
        // сигнал потоку Т3 про завершення обчислень
        monitor.sendSignal(monitor.signal2);
        System.out.println("T4 finished");
    }
}
