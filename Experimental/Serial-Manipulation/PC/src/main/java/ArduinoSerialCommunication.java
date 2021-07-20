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


        this.synchronizeNew();
        Thread dataReaderThread = new Thread(() -> {
            while (true) {
                String line = this.readLine();

                System.out.println(line);
            }
        });
        dataReaderThread.setName("Arduino Serial Data Reader");
        dataReaderThread.start();
/*
        for (int i = 0; i < 101; i++) {
            this.sendLine(i + "=> " + "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
            Thread.sleep(50);
        }*/
    }

    /**
     * Responsible for finding a ASCII Sequence.
     */
    private class ASCIISequence {

        private List<Integer> sequence;
        private List<Integer> expected;

        public ASCIISequence(Integer... characterCodes) {
            this.expected = Arrays.asList(characterCodes);
            this.sequence = new ArrayList<>();
        }

        /**
         * Will insert character to the current sequence.
         * If the character fails the pattern, then the current sequence will be reset.
         *
         * @return true/false depending if the sequence was completed
         */
        public boolean insert(int characterCode) {

            this.sequence.add(characterCode);

            Integer expectedAtPosition = this.expected.get(this.sequence.size() - 1);

            if (!expectedAtPosition.equals(characterCode)) {
                this.sequence.clear();
                return false;
            }

            return this.sequence.size() == this.expected.size();
        }
    }

    /**
     * Will finish, when the SYN character is received.
     * It is indication that the embedded device has started
     *
     * @return
     */
    private boolean synchronizeNew() {
        StopWatch stopWatch = StopWatch.createStarted();
        ASCIISequence asciiSequence = new ASCIISequence(22, 13, 10);

        while (true) {
            Byte value = this.readByte();

            if (asciiSequence.insert(value)) {
                System.out.println("Synchronization finished in " + stopWatch.toString());
                stopWatch.stop();
                return true;
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
