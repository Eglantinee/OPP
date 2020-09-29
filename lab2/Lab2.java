public class Lab2 {
    public static int N = 1000;
    public static void main(String[] args) throws InterruptedException {
        Task1 T1 = new Task1();
        Task2 T2 = new Task2();
        Task3 T3 = new Task3();
        T1.setPriority(2);
        T2.setPriority(5);
        T3.setPriority(8);
        T1.start();
        T2.start();
        T3.start();
        T3.join();
        T2.join();
        T1.join();
    }
}
