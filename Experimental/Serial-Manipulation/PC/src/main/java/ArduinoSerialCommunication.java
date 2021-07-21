import com.fazecast.jSerialComm.SerialPort;
import org.apache.commons.lang3.time.StopWatch;

import java.io.IOException;
import java.io.InputStream;
import java.util.*;

public class ArduinoSerialCommunication {

    public static final String PORT_NAME = "COM3";
    public static final Byte SYNC_ASCII_SYMBOL = 22;

    private SerialPort arduinoSerial;

    public void start() throws IOException, InterruptedException {
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
     *
     */
    private void synchronize() {
        StopWatch stopWatch = StopWatch.createStarted();
        SequenceFinder<Integer> sequenceFinder = new SequenceFinder<>(22, 13, 10);

        while (true) {
            int value = this.readByte();

            if (sequenceFinder.insert(value)) {
                System.out.println("Synchronization finished in " + stopWatch.toString());
                stopWatch.stop();
                break;
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
