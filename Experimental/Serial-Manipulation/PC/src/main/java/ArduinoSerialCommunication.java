import com.fazecast.jSerialComm.SerialPort;
import org.apache.commons.lang3.time.StopWatch;

import java.io.InputStream;
import java.util.NoSuchElementException;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;

public class ArduinoSerialCommunication {

    public static final Integer WAIT_READY_CHECK_TIMEOUT_MS = 5000;
    public static final String PORT_NAME = "COM3";
    public static final String WAIT_READY_FLAG = "Ready";

    private SerialPort arduinoSerial;

    public void start() throws InterruptedException {
        this.arduinoSerial = SerialPort.getCommPort(PORT_NAME);
        //this.arduinoSerial.setComPortTimeouts(SerialPort.TIMEOUT_READ_SEMI_BLOCKING, 0, 0);
        this.arduinoSerial.openPort();

        this.waitUntilDeviceIsReady();


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
     * Will wait until the device returns "Ready"
     * The idea is that if the device is ready it can receive the send messages from us otherwise they are lose
     * <p>
     * Note that if the device is not reset when opening a serial port, the check will be fast, otherwise it will take time, because
     * the device is resetting and the serial is not yet ready to accept messages.
     *
     * @throws SynchronizationTimedOutException if the given time for execution is exceeded
     */
    private void waitUntilDeviceIsReady() throws InterruptedException {
        StopWatch synchronizationTime = StopWatch.createStarted();

        while (true) {
            this.sendLine(WAIT_READY_FLAG);

            String line = this.readLineNonBlocking();

            if (WAIT_READY_FLAG.equals(line)) {
                System.out.println(String.format("Ready check finished in %s!", synchronizationTime.toString()));
                synchronizationTime.stop();
                break;
            }

            if (this.isSynchronizationTimedOut(synchronizationTime)) {
                throw new SynchronizationTimedOutException("Ready check timed out!");
            }
        }
    }

    private boolean isSynchronizationTimedOut(StopWatch synchronizationTime) {
        return synchronizationTime.getTime(TimeUnit.MILLISECONDS) >= WAIT_READY_CHECK_TIMEOUT_MS;
    }

    private String readLine() {
        InputStream arduinoInputStream = this.arduinoSerial.getInputStream();

        StringBuilder sequence = new StringBuilder();

        while (true)
            try {

                if (arduinoInputStream.available() <= 0)
                    continue;

                char next = (char) arduinoInputStream.read();

                boolean isTerminator = next == '\n' || next == '\r';
                boolean isLineFinished = isTerminator && sequence.length() > 0;

                if (!isTerminator)
                    sequence.append(next);
                else if (isLineFinished)
                    return sequence.toString();

            } catch (Exception ex) {
                ex.printStackTrace();
            }
    }

    private String readLineNonBlocking() {
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
        this.delay(10);

        return result;
    }

    private void delay(int milliseconds) {
        try {
            Thread.sleep(milliseconds);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

}
