import serial.ArduinoSerial;

import java.io.IOException;

public class Main {


    public static void main(String[] args) throws InterruptedException, IOException {

        ArduinoSerial serialCommunication = new ArduinoSerial()
                .builder()
                .withReadyTimeoutMS(1500)
                .disableWaitUntilDeviceIsReady()
                .build()
                .start();

        //serialCommunication.sendLine("Cat!");

        while (true) {
            System.out.println(serialCommunication.readLine());
        }
    }
}
