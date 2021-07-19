import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortDataListener;
import com.fazecast.jSerialComm.SerialPortEvent;

public class DataListener implements SerialPortDataListener {

    public int getListeningEvents() {
        return SerialPort.LISTENING_EVENT_DATA_RECEIVED;
    }

    public void serialEvent(SerialPortEvent serialPortEvent) {

        byte[] newData = serialPortEvent.getReceivedData();
        for (int i = 0; i < newData.length; ++i)
            System.out.print((char) newData[i]);
    }
}
