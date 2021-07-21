public class SynchronizationTimedOutException extends RuntimeException {

    public SynchronizationTimedOutException() {
    }

    public SynchronizationTimedOutException(Integer timeLimitMS) {
        this(String.format("Synchronization time limit (%d ms) exceeded.", timeLimitMS));
    }

    public SynchronizationTimedOutException(String message) {
        super(message);
    }

    public SynchronizationTimedOutException(String message, Throwable cause) {
        super(message, cause);
    }

    public SynchronizationTimedOutException(Throwable cause) {
        super(cause);
    }

    public SynchronizationTimedOutException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }
}
