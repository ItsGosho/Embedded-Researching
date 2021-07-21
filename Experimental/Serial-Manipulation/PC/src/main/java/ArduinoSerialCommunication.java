import com.fazecast.jSerialComm.SerialPort;
import org.apache.commons.lang3.time.StopWatch;

import java.io.InputStream;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;

public class ArduinoSerialCommunication {

    public static final Integer SYNCHRONIZATION_TIMEOUT_MS = 2000;
    public static final Integer SYNCHRONIZATION_RETRIES = 2;
    public static final String PORT_NAME = "COM3";

    private SerialPort arduinoSerial;

    public void start() {
        this.arduinoSerial = SerialPort.getCommPort(PORT_NAME);
        this.arduinoSerial.setComPortTimeouts(SerialPort.TIMEOUT_READ_SEMI_BLOCKING, 0, 0);
        this.arduinoSerial.openPort();

        //Wait to receive if it is ready


        this.synchronize();
        Thread dataReaderThread = new Thread(() -> {
            while (true) {
                String line = this.readLine();

                System.out.println(line);
            }
        });
        dataReaderThread.setName("Arduino Serial Data Reader");
        dataReaderThread.start();

        this.sendLine("Goshko");
        this.sendLine("-Roshko!");
/*
        for (int i = 0; i < 101; i++) {
            this.sendLine(i + "=> " + "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
            Thread.sleep(50);
        }*/
    }

    /**
     * Will finish, when the SYN character is received.
     * It is indication that the embedded device can receive messages.
     */
    private void synchronize() {
        StopWatch synchronizationTime = StopWatch.createStarted();
        SequenceFinder<Integer> sequenceFinder = new SequenceFinder<>(22, 13, 10);

        int retryCounter = 1;
        while (true) {
            int value = this.readByte();

            if (sequenceFinder.insert(value)) {
                System.out.println("Synchronization finished in " + synchronizationTime.toString());
                synchronizationTime.stop();
                break;
            }

            if (synchronizationTime.getTime(TimeUnit.MILLISECONDS) >= SYNCHRONIZATION_TIMEOUT_MS * retryCounter) {

                System.out.println(String.format("Synchronization attempt %d/%d has timed out.", retryCounter, SYNCHRONIZATION_RETRIES));

                if (retryCounter >= SYNCHRONIZATION_RETRIES)
                    throw new SynchronizationTimedOutException(SYNCHRONIZATION_TIMEOUT_MS);

                retryCounter++;
            }
        }

    }


    private Byte readByte() {
        byte[] bytes = new byte[1];
        this.arduinoSerial.readBytes(bytes, 1);

        return bytes[0];
    }

    private String readLine() {
        InputStream inputStream = this.arduinoSerial.getInputStream();
        Scanner scanner = new Scanner(inputStream);

        while (true) {

            if (scanner.hasNextLine())
                return scanner.nextLine();
        }
    }

    public void sendLine(String line) {
        byte[] messageBytes = line
                .concat("\n")
                .getBytes();

        int result = this.arduinoSerial.writeBytes(messageBytes, messageBytes.length);

        if (result == -1)
            System.out.println("Error writing to the serial port!");
    }

}
