import serial.ArduinoSerial;

import java.io.IOException;

public class Main {


    public static void main(String[] args) throws InterruptedException, IOException {

        ArduinoSerial serialCommunication = new ArduinoSerial()
                .builder()
                .withReadyTimeout(1500)
                .build()
                .start();

        serialCommunication.sendLine("Cat!");
        System.out.println(serialCommunication.readLine());
    }
}
