#ifndef LIQUID_CRYSTAL_CUSTOM_CURSORDIRECTION_H
#define LIQUID_CRYSTAL_CUSTOM_CURSORDIRECTION_H

/**
 * Instruction bit name - I/D
 *
 * When a new character is written, where the cursor will go.
 * INCREMENT -
 * DECREMENT -
 */
enum class CursorDirection {
    DECREMENT = 0,
    INCREMENT = 1
};

#endif //LIQUID_CRYSTAL_CUSTOM_CURSORDIRECTION_H
