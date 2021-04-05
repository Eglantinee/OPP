public class Task2 extends Thread {
    private final int n;
    private final int p;
    private final Monitor monitor;
    Task2(int N, int P, Monitor monitor) {
        this.n = N;
        this.p = P;
        this.monitor = monitor;
    }
    public void run() {
        System.out.println("T2 started");
        // введення B, MX.
        monitor.B = Data.inputVector(n, 1);
        monitor.MX = Data.inputMatrix(n, 1);
        // сигнал потокам Т1, Т3, Т4 про введення даних
        monitor.signal_In();
        // чекати на введення даних в потоці Т4
        monitor.wait_In();
        // копіювання введених даних у локальні змінні
        int d2 = monitor.get_d();
        int[] Z2 = monitor.get_Z();
        int[][] MM2 = monitor.get_MM();
        // обчислення Xh = sort(d2*Bh + Z2*(MM2*MXh))
        int[] Xh = Data.sort(d2, monitor.B, Z2, MM2, monitor.MX, n, n / p, n / p);
        monitor.X1 = Xh;
        // надіслати сигнал про завершення обчислень потоку Т1
        monitor.sendSignal(monitor.signal1);
        System.out.println("T2 finished");
    }
}
