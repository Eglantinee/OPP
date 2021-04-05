public class Monitor {
    private static class Signal {
        public boolean signal;
        Signal(boolean value){
            this.signal = value;
        }
    }
    private int inputThreads = 0;
    Signal signal1 = new Signal(false);
    Signal signal2 = new Signal(false);
    Signal signal3 = new Signal(false);
    // Private variables
    private int d;
    private int[] Z;
    private int[][] MM;
    // Shared variables
    public int[] B;
    public int[][] MX;
    public int[] X1;
    public int[] X2;
    // Synchronized void
    public synchronized void put_d(int value) {
        this.d = value;
    }
    public synchronized void put_Z(int[] value) {
        this.Z = value;
    }
    public synchronized void put_MM(int[][] value) {
        this.MM = value;
    }
    public synchronized int get_d() {
        return this.d;
    }
    public synchronized int[] get_Z() {
        return this.Z;
    }
    public synchronized int[][] get_MM() {
        return this.MM;
    }
    public synchronized void wait_In() {
        while (inputThreads != 2) {
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
    public synchronized void signal_In() {
        ++inputThreads;
        notifyAll();
    }
    public synchronized void waitSignal(Signal obj){
        while (!obj.signal){
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        obj.signal = false;
    }
    public synchronized void sendSignal(Signal obj){
        obj.signal = true;
        notifyAll();
    }
}

