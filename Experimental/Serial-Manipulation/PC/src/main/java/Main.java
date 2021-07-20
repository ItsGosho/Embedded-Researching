import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Main {

    boolean hasSynchronizationFinished = false;

    public static void main(String[] args) throws InterruptedException, IOException {

        ArduinoSerialCommunication serialCommunication = new ArduinoSerialCommunication();
        serialCommunication.start();

    /*    ASCIISequence asciiSequence = new ASCIISequence();


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
        }*/

    }

    /**
     * Responsible for finding a ASCII Sequence.
     */
    private static class ASCIISequence {

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

            if(!expectedAtPosition.equals(characterCode)) {
                this.sequence.clear();
                return false;
            }

            return this.sequence.size() == this.expected.size();
        }
    }
}
