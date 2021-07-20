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
        this.arduinoSerial.openPort();
        this.arduinoSerial.setComPortTimeouts(SerialPort.TIMEOUT_READ_SEMI_BLOCKING, 0, 0);

        //Wait to receive if it is ready


        this.synchronizeNew();

        for (int i = 0; i < 100; i++) {
            this.sendLine(String.valueOf(i));
        }

        Thread.sleep(10000);
        while (true) {
            String line = this.readLine();

            System.out.println(line);
        }
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


    public void synchronize() {
        StopWatch stopWatch = StopWatch.createStarted();

        InputStream inputStream = this.arduinoSerial.getInputStream();
        Scanner scanner = new Scanner(inputStream);

        while (scanner.hasNextLine()) {

            String line = scanner.nextLine();

            if (this.isSYNLine(line)) {
                System.out.println("Synchronization finished in " + stopWatch.toString());
                stopWatch.stop();
                break;
            } else {
                System.out.println();
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

    private boolean isSYNLine(String line) {
        return (char) line.getBytes()[0] == 22;
    }

    public void sendLine(String line) {
        line = line.concat("\r\n");
        byte[] messageBytes = line.getBytes();

        int result = this.arduinoSerial.writeBytes(messageBytes, messageBytes.length);
    }

}
