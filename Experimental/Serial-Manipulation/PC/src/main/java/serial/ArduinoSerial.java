package serial;

import com.fazecast.jSerialComm.SerialPort;
import org.apache.commons.lang3.time.StopWatch;

import java.io.InputStream;
import java.util.NoSuchElementException;
import java.util.Optional;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;

public class ArduinoSerial {

    public static final String DEFAULT_PORT = "COM3";
    public static final String DEFAULT_READY_KEYWORD = "Ready";
    public static final Integer DEFAULT_READY_TIMEOUT = 1000;


    private SerialPort arduinoSerial;
    private String port;
    private String readyKeyword;
    private Integer readyTimeout;

    public ArduinoSerial start() {
        this.arduinoSerial = SerialPort.getCommPort(this.port);
        this.arduinoSerial.openPort();

        this.waitUntilDeviceIsReady();

        return this;
    }

    public ArduinoSerial() {
        this.setPort(DEFAULT_PORT);
        this.setReadyKeyword(DEFAULT_READY_KEYWORD);
        this.setReadyTimeout(DEFAULT_READY_TIMEOUT);
    }

    public ArduinoSerial(ArduinoSerialBuilder builder) {
        this();
        this.setPort(builder.getPort());
        this.setReadyKeyword(builder.getReadyKeyword());
        this.setReadyTimeout(builder.getReadyTimeout());
    }

    public ArduinoSerialBuilder builder() {
        return new ArduinoSerialBuilder();
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
    private void waitUntilDeviceIsReady() {
        StopWatch synchronizationTime = StopWatch.createStarted();

        while (true) {
            this.sendLine(this.readyKeyword);

            String line = this.readLineNonBlocking();

            if (this.readyKeyword.equals(line)) {
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
        return synchronizationTime.getTime(TimeUnit.MILLISECONDS) >= this.readyTimeout;
    }

    public String readLine() {
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

    public void setPort(String port) {
        this.port = Optional.ofNullable(port).orElse(DEFAULT_PORT);
    }

    public void setReadyKeyword(String readyKeyword) {
        this.readyKeyword = Optional.ofNullable(readyKeyword).orElse(DEFAULT_READY_KEYWORD);
    }

    public void setReadyTimeout(Integer readyTimeout) {
        this.readyTimeout = Optional.ofNullable(readyTimeout).orElse(DEFAULT_READY_TIMEOUT);
    }
}
