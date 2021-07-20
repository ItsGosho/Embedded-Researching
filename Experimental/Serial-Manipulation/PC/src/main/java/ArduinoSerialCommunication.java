import com.fazecast.jSerialComm.SerialPort;
import org.apache.commons.lang3.time.StopWatch;

import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class ArduinoSerialCommunication {

    public static final String PORT_NAME = "COM3";
    public static final Byte SYNC_ASCII_SYMBOL = 22;

    private SerialPort arduinoSerial;

    public void start() throws IOException, InterruptedException {
        this.arduinoSerial = SerialPort.getCommPort(PORT_NAME);
        this.arduinoSerial.openPort();
        this.arduinoSerial.setComPortTimeouts(SerialPort.TIMEOUT_READ_SEMI_BLOCKING, 0, 0);

        /*TODO: да де но сега пък не работи синхронизацията с това блокиране!?*/

        /*TODO: On simple sync just start*/
        //Thread.sleep(1500);


        InputStream inputStream = this.arduinoSerial.getInputStream();
        Scanner scanner = new Scanner(inputStream);

        while (scanner.hasNextLine()) {

            String line = scanner.nextLine();

            boolean test = (char) line.getBytes()[0] == 22;

            if(test) {
                this.sendMessage("Salam!5");
            }

            System.out.println(scanner.nextLine());

        }

    }

    public void synchronize() {
        StopWatch stopWatch = StopWatch.createStarted();

        while (true) {
            this.sendMessage(SYNC_ASCII_SYMBOL);

            try {
                Thread.sleep(50);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            byte[] readBuffer = new byte[4];
            this.arduinoSerial.readBytes(readBuffer, readBuffer.length);

            if (readBuffer[0] == 50 && readBuffer[1] == 50 && readBuffer[2] == 13 && readBuffer[3] == 10) {
                stopWatch.stop();
                System.out.println("Synchronization Finished in " + stopWatch.toString());
                break;
            }

            //arduinoSerial.addDataListener(new DataListener());
        }
    }

    public String readLine() {
        StringBuilder line = new StringBuilder();
        boolean isCRPrevious = false;

        while (true) {
            char character = (char) this.readByte();

            if (character == 0)
                continue;

            if (character == '\r') {
                isCRPrevious = true;
                line.append(character);
            } else if (character == '\n' && isCRPrevious) {
                line.deleteCharAt(line.length() - 1);
                return line.toString();
            } else {
                line.append(character);
            }
        }
    }

    private byte readByte() {
        byte[] readBuffer = new byte[1];
        this.arduinoSerial.readBytes(readBuffer, readBuffer.length);

        return readBuffer[0];
    }

    public void sendMessage(byte message) {
        byte[] messageBytes = new byte[1];
        messageBytes[0] = message;

        int result = this.arduinoSerial.writeBytes(messageBytes, messageBytes.length);
    }

    public void sendMessage(String message) {
        byte[] messageBytes = message.getBytes();

        int result = this.arduinoSerial.writeBytes(messageBytes, messageBytes.length);
    }

}
