import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Responsible for finding a Integer Sequence.
 */
public class SequenceFinder<E> {

    private List<E> sequence;
    private List<E> expected;

    public SequenceFinder(E... elements) {
        this.expected = Arrays.asList(elements);
        this.sequence = new ArrayList<>();
    }

    /**
     * Will insert element to the current sequence.
     * If the element fails the pattern, then the current sequence will be reset.
     *
     * @return true/false depending if the sequence was completed
     */
    public boolean insert(E element) {

        this.sequence.add(element);

        E expectedAtPosition = this.expected.get(this.sequence.size() - 1);

        if (!expectedAtPosition.equals(element)) {
            this.sequence.clear();
            return false;
        }

        return this.sequence.size() == this.expected.size();
    }
}