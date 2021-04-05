import java.util.Arrays;
public class Task3 extends Thread {
    private final int n;
    private final int p;
    private final Monitor monitor;

    Task3(int N, int P, Monitor monitor) {
        this.n = N;
        this.p = P;
        this.monitor = monitor;
    }
    public void run() {
        System.out.println("T3 started");
        // чекати на введення даних в потоці Т2
        // чекати на введення даних в потоці Т4
        monitor.wait_In();
        // копіювати введені дані у локальні змінні
        int d3 = monitor.get_d();
        int[] Z3 = monitor.get_Z();
        int[][] MM3 = monitor.get_MM();
        // обчислення Xh = sort(d3*Bh + Z3*(MM3*MXh))
        int[] Xh = Data.sort(d3, monitor.B, Z3, MM3, monitor.MX, n, n / p, 2 * n / p);
        // чекати сигналу про завершення обчислень у потоці Т4
        monitor.waitSignal(monitor.signal2);
        // обчислення X2h = sort*(X3, X4)
        int[] Xh2 = monitor.X2;
        int[] X2h = Data.sorts(Xh2, Xh, n / p);
        // чекати сигналу про завершення обчислень у потоці Т1
        monitor.waitSignal(monitor.signal3);
        // обчислення X = sort*(X21, X23)
        int[] X2h2 = monitor.X1;
        int[] X = Data.sorts(X2h, X2h2, 2 * n / p);
        // виведення результату X
        System.out.println(Arrays.toString(X));
        System.out.println("T3 finished");
    }
}
