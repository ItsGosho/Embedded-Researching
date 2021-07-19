import com.fazecast.jSerialComm.SerialPort;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

public class Main {

    private final Logger LOGGER = LogManager.getLogger();

    public static void main(String[] args) {

        SerialPort[] serialPorts = SerialPort.getCommPorts();
        SerialPort arduinoSerial = SerialPort.getCommPort("COM3");
        //SerialPort arduinoPortFromAvailable = serialPorts[0];

        arduinoSerial.openPort();

        arduinoSerial.addDataListener(new DataListener());

       /* byte[] bytes = new byte[10];
        while (arduinoSerial.bytesAvailable() > 0) {
            arduinoSerial.readBytes(bytes, 10);
            int test = 5;
        }*/

        int a = 5;
    }
}
