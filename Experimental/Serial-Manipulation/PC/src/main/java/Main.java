import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Main {

    boolean hasSynchronizationFinished = false;

    public static void main(String[] args) throws InterruptedException, IOException {

        ArduinoSerialCommunication serialCommunication = new ArduinoSerialCommunication();
        //serialCommunication.start();

        SequenceFinder<Integer> asciiSequence = new SequenceFinder<>(22, 13, 14);


        List<Integer> characterTests = new ArrayList<>();
        characterTests.add(10);
        characterTests.add(22);
        characterTests.add(13);
        characterTests.add(10);
        characterTests.add(3);

        for (int i = 0; i < 5; i++) {
            int characterCode = characterTests.get(i);

            if (asciiSequence.insert(characterCode)) {
                System.out.println("FOUND!");
                break;
            }
        }

    }
}
