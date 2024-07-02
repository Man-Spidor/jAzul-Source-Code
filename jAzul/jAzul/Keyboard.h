#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <queue>
#include "KeyboardEvent.h"

/// @class Keyboard
/// @brief Manages keyboard input.
/// 
/// This class provides functionality to handle keyboard events, store key states, and retrieve key and character events.
class Keyboard
{
    friend class InputAttorney;

public:
    static const unsigned int KeyStatesLength = 256; ///< Length of the key states array.

public:
    Keyboard(); ///< Default constructor.
    Keyboard(const Keyboard& other) = default; ///< Copy constructor.
    Keyboard& operator=(const Keyboard& other) = default; ///< Copy assignment operator.
    Keyboard(Keyboard&& other) = default; ///< Move constructor.
    Keyboard& operator=(Keyboard&& other) = default; ///< Move assignment operator.
    ~Keyboard() = default; ///< Destructor.

    /// @brief Check if the key buffer is empty.
    /// @return True if the key buffer is empty, false otherwise.
    bool KeyBufferIsEmpty();

    /// @brief Check if the character buffer is empty.
    /// @return True if the character buffer is empty, false otherwise.
    bool CharBufferIsEmpty();

    /// @brief Read the next key event from the buffer.
    /// @return The next key event.
    KeyboardEvent ReadKey();

    /// @brief Read the next character from the buffer.
    /// @return The next character.
    unsigned char ReadChar();

    /// @brief Handle key press events.
    /// @param key The key code.
    void OnKeyPressed(const unsigned char key);

    /// @brief Handle key release events.
    /// @param key The key code.
    void OnKeyReleased(const unsigned char key);

    /// @brief Handle character input events.
    /// @param key The character code.
    void OnChar(const unsigned char key);

public:
    /// @brief Get the state of a specific key.
    /// @param c The character representing the key.
    /// @return True if the key is pressed, false otherwise.
    static bool GetKeyState(const char c);

    /// @brief Get the state of a specific key.
    /// @param key The key code.
    /// @return True if the key is pressed, false otherwise.
    static bool GetKeyState(JAZUL_KEY key);

private:
    static bool keyStates[KeyStatesLength]; ///< Array to store the state of each key.
    std::queue<KeyboardEvent> keyBuffer; ///< Queue to store key events.
    std::queue<unsigned char> charBuffer; ///< Queue to store character events.
};

#endif // KEYBOARD_H
