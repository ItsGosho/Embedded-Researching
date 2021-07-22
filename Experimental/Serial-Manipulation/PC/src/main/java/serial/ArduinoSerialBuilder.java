package serial;

public class ArduinoSerialBuilder {

    private String port;
    private String readyKeyword;
    private Integer readyTimeout;

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
}
