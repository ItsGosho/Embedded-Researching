package serial;

public class ArduinoSerialBuilder {

    private String port;
    private String readyKeyword;
    private Integer readyTimeout;
    private Integer baudRate;
    private Integer dataBits;
    private Integer stopBits;
    private Integer parity;
    private Integer sendLineDebouncing;

    public ArduinoSerialBuilder withPort(String port) {
        this.port = port;
        return this;
    }

    public ArduinoSerialBuilder withReadyKeyword(String readyKeyword) {
        this.readyKeyword = readyKeyword;
        return this;
    }

    public ArduinoSerialBuilder withReadyTimeout(Integer readyTimeout) {
        this.readyTimeout = readyTimeout;
        return this;
    }

    public ArduinoSerialBuilder withBaudRate(Integer baudRate) {
        this.baudRate = baudRate;
        return this;
    }

    public ArduinoSerialBuilder withDataBits(Integer dataBits) {
        this.dataBits = dataBits;
        return this;
    }

    public ArduinoSerialBuilder withStopBits(Integer stopBits) {
        this.stopBits = stopBits;
        return this;
    }

    public ArduinoSerialBuilder withParity(Integer parity) {
        this.parity = parity;
        return this;
    }

    public ArduinoSerialBuilder withSendLineDebouncing(Integer sendLineDebouncing) {
        this.sendLineDebouncing = sendLineDebouncing;
        return this;
    }

    public ArduinoSerial build() {
        return new ArduinoSerial(this);
    }

    public String getPort() {
        return port;
    }

    public String getReadyKeyword() {
        return readyKeyword;
    }

    public Integer getReadyTimeout() {
        return readyTimeout;
    }

    public Integer getBaudRate() {
        return baudRate;
    }

    public Integer getDataBits() {
        return dataBits;
    }

    public Integer getStopBits() {
        return stopBits;
    }

    public Integer getParity() {
        return parity;
    }

    public Integer getSendLineDebouncing() {
        return sendLineDebouncing;
    }
}
