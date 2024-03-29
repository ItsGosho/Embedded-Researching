package serial;

public class ArduinoSerialBuilder {

    private String port;
    private String readyKeyword;
    private Integer readyTimeoutMS;
    private Integer baudRate;
    private Integer dataBits;
    private Integer stopBits;
    private Integer parity;
    private Integer sendLineDebouncingMS;
    private boolean isWaitUntilDeviceIsReadyDisabled;

    public ArduinoSerialBuilder withPort(String port) {
        this.port = port;
        return this;
    }

    public ArduinoSerialBuilder withReadyKeyword(String readyKeyword) {
        this.readyKeyword = readyKeyword;
        return this;
    }

    public ArduinoSerialBuilder withReadyTimeoutMS(Integer readyTimeoutMS) {
        this.readyTimeoutMS = readyTimeoutMS;
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

    public ArduinoSerialBuilder withSendLineDebouncingMS(Integer sendLineDebouncingMS) {
        this.sendLineDebouncingMS = sendLineDebouncingMS;
        return this;
    }

    public ArduinoSerialBuilder disableWaitUntilDeviceIsReady() {
        this.isWaitUntilDeviceIsReadyDisabled = true;
        return this;
    }

    public ArduinoSerial build() {
        return new ArduinoSerial(this);
    }

    public String getPort() {
        return this.port;
    }

    public String getReadyKeyword() {
        return this.readyKeyword;
    }

    public Integer getReadyTimeoutMS() {
        return this.readyTimeoutMS;
    }

    public Integer getBaudRate() {
        return this.baudRate;
    }

    public Integer getDataBits() {
        return this.dataBits;
    }

    public Integer getStopBits() {
        return this.stopBits;
    }

    public Integer getParity() {
        return this.parity;
    }

    public Integer getSendLineDebouncingMS() {
        return this.sendLineDebouncingMS;
    }

    public boolean isWaitUntilDeviceIsReadyDisabled() {
        return this.isWaitUntilDeviceIsReadyDisabled;
    }
}
