import java.io.IOException;

public class Main {

    boolean hasSynchronizationFinished = false;

    public static void main(String[] args) throws InterruptedException, IOException {

        ArduinoSerialCommunication serialCommunication = new ArduinoSerialCommunication();
        serialCommunication.start();

    }
}
