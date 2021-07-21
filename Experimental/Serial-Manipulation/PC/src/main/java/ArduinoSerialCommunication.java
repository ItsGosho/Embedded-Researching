import com.fazecast.jSerialComm.SerialPort;
import org.apache.commons.lang3.time.StopWatch;

import java.io.InputStream;
import java.util.NoSuchElementException;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;

public class ArduinoSerialCommunication {

    public static final Integer SYNCHRONIZATION_TIMEOUT_MS = 5000;
    public static final String PORT_NAME = "COM3";

    private SerialPort arduinoSerial;

    public void start() throws InterruptedException {
        this.arduinoSerial = SerialPort.getCommPort(PORT_NAME);
        //this.arduinoSerial.setComPortTimeouts(SerialPort.TIMEOUT_READ_SEMI_BLOCKING, 0, 0);
        this.arduinoSerial.openPort();

        //Wait to receive if it is ready


        this.synchronize();
   /*     Thread dataReaderThread = new Thread(() -> {
            while (true) {
                String line = this.readLine();

                System.out.println(line);
            }
        });
        dataReaderThread.setName("Arduino Serial Data Reader");
        dataReaderThread.start();

        this.sendLine("Goshko");
        this.sendLine("-Roshko!");*/
/*
        for (int i = 0; i < 101; i++) {
            this.sendLine(i + "=> " + "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
            Thread.sleep(50);
        }*/
    }

    /**
     * Will finish, when the SYN character is received.
     * It is indication that the embedded device can receive messages.
     * <p>
     * Each given attempt is counted when the given timeout is exceeded.
     *
     * @throws SynchronizationTimedOutException if the attempts are exceeded
     */
    private void synchronize() throws InterruptedException {
        StopWatch synchronizationTime = StopWatch.createStarted();
        //SequenceFinder<Integer> sequenceFinder = new SequenceFinder<>(22, 13, 10);
        SequenceFinder<String> sequenceFinder = new SequenceFinder<>("S", "Y", "N");

        while (true) {
            this.sendLine("SYN");

            String line = this.readLineNonBlocking();

            if ("SYN".equals(line)) {
                System.out.println(String.format("Synchronization finished in %s!", synchronizationTime.toString()));
                synchronizationTime.stop();
                break;
            }

            if (this.isSynchronizationTimedOut(synchronizationTime)) {
                throw new SynchronizationTimedOutException("Synchronization timed out!");
            }
        }
    }

    private boolean isSynchronizationTimedOut(StopWatch synchronizationTime) {
        return synchronizationTime.getTime(TimeUnit.MILLISECONDS) >= SYNCHRONIZATION_TIMEOUT_MS;
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

    private String readLineNonBlocking() {
        StopWatch stopWatch = StopWatch.createStarted();

        InputStream inputStream = this.arduinoSerial.getInputStream();
        Scanner scanner = new Scanner(inputStream);

        while (true) {
            try {
                return scanner.nextLine();
            } catch (NoSuchElementException noSuchElementException) {
                return null;
            }
        }
    }

    public int sendLine(String line) {
        byte[] messageBytes = line
                .concat("\n")
                .getBytes();

        int result = this.arduinoSerial.writeBytes(messageBytes, messageBytes.length);

        //TODO: refactor
        try {
            Thread.sleep(10);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        return result;
    }

}
