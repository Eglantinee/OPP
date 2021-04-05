public class Task1 extends Thread {
    private final int n;
    private final int p;
    private final Monitor monitor;
    Task1(int N, int P, Monitor monitor) {
        this.n = N;
        this.p = P;
        this.monitor = monitor;
    }
    public void run() {
        System.out.println("T1 started");
        // чекати на введення даних в потоці Т2
        // чекати на введення даних в потоці Т4
        monitor.wait_In();
        // копіювання введених даних у локальні змінні
        int d1 = monitor.get_d();
        int[] Z1 = monitor.get_Z();
        int[][] MM1 = monitor.get_MM();
        // обчислення Xh = sort(d1*Bh + Z1*(MM1*MXh))
        int[] Xh = Data.sort(d1, monitor.B, Z1, MM1, monitor.MX, n, n / p, 0);
        // чекати сигналу про завершення обчислень у потоці Т2
        monitor.waitSignal(monitor.signal1);
        // обчислення X2h = sort*(Xh, Xh)
        int[] Xh2 = monitor.X1;
        int[] X2h = Data.sorts(Xh2, Xh, n / p);
        monitor.X1 = X2h;
        // надіслати сигнал про завершення обчислень потоку Т3
        monitor.sendSignal(monitor.signal3);
        System.out.println("T1 finished");
    }
}
