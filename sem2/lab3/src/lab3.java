//----------------------------------------------------------------
//        --  Лабортаторна робота №3 Варіант 23
//        --  X = sort(d*B + Z*(MM*MX))
//        --  Шкардибарда І. ІВ-82
//        --  Дата 09.03.2021
//----------------------------------------------------------------
public class lab3 {
    private static final int N = 8;
    private static final int P = 4;
    private static final Monitor monitor = new Monitor();
    public static void main(String[] args) {
        Task1 T1 = new Task1(N, P, monitor);
        Task2 T2 = new Task2(N, P, monitor);
        Task3 T3 = new Task3(N, P, monitor);
        Task4 T4 = new Task4(N, P, monitor);
        T1.start();
        T2.start();
        T3.start();
        T4.start();
        try {
            T1.join();
            T2.join();
            T3.join();
            T4.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
