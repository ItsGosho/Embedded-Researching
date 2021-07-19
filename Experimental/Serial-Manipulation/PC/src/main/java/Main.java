import com.fazecast.jSerialComm.SerialPort;
import org.apache.commons.lang3.time.StopWatch;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.apache.logging.log4j.spi.LoggerContextFactory;

public class Main {

    boolean hasSynchronizationFinished = false;

    public static void main(String[] args) throws InterruptedException {
        SerialPort[] serialPorts = SerialPort.getCommPorts();
        SerialPort arduinoSerial = SerialPort.getCommPort("COM3");
        //SerialPort arduinoPortFromAvailable = serialPorts[0];

        //arduinoSerial.setComPortTimeouts(SerialPort.TIMEOUT_READ_SEMI_BLOCKING, 1, 0);
        arduinoSerial.openPort();

        StopWatch stopWatch = StopWatch.createStarted();

        while (true) {
            sendMessage(arduinoSerial, (byte) 22);

            /*TODO: Защо трябва да не го зоря толкова иначе не минава?!*/
            Thread.sleep(25);

            byte[] readBuffer = new byte[4];
            arduinoSerial.readBytes(readBuffer, readBuffer.length);

            if (readBuffer[0] == 50 && readBuffer[1] == 50 && readBuffer[2] == 13 && readBuffer[3] == 10) {
                stopWatch.stop();
                System.out.println("Synchronization Finished in " + stopWatch.toString());
                break;
            }

            //arduinoSerial.addDataListener(new DataListener());
        }

        //comPort.closePort();

    }

    public static void sendMessage(SerialPort serialPort, byte message) {
        byte[] messageBytes = new byte[1];
        messageBytes[0] = message;

        int result = serialPort.writeBytes(messageBytes, messageBytes.length);
    }

    public static void sendMessage(SerialPort serialPort, String message) {
        byte[] messageBytes = message.getBytes();

        int result = serialPort.writeBytes(messageBytes, messageBytes.length);
    }
}
