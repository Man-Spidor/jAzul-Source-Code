#ifndef KEYBOARDEVENT_H
#define KEYBOARDEVENT_H

/// @brief Enumerates the different key codes.
enum class JAZUL_KEY
{
    KEY_SPACE = VK_SPACE,
    KEY_APOSTROPHE = VK_OEM_7,  /* ' */
    KEY_COMMA = VK_OEM_COMMA,  /* , */
    KEY_MINUS = VK_OEM_MINUS,  /* - */
    KEY_PERIOD = VK_OEM_PERIOD,  /* . */
    KEY_SLASH = VK_OEM_2,  /* / */
    KEY_0 = 0x30,
    KEY_1 = 0x31,
    KEY_2 = 0x32,
    KEY_3 = 0x33,
    KEY_4 = 0x34,
    KEY_5 = 0x35,
    KEY_6 = 0x36,
    KEY_7 = 0x37,
    KEY_8 = 0x38,
    KEY_9 = 0x39,
    KEY_SEMICOLON = VK_OEM_1,  /* ; */
    KEY_A = 0x41,
    KEY_B = 0x42,
    KEY_C = 0x43,
    KEY_D = 0x44,
    KEY_E = 0x45,
    KEY_F = 0x46,
    KEY_G = 0x47,
    KEY_H = 0x48,
    KEY_I = 0x49,
    KEY_J = 0x4A,
    KEY_K = 0x4B,
    KEY_L = 0x4C,
    KEY_M = 0x4D,
    KEY_N = 0x4E,
    KEY_O = 0x4F,
    KEY_P = 0x50,
    KEY_Q = 0x51,
    KEY_R = 0x52,
    KEY_S = 0x53,
    KEY_T = 0x54,
    KEY_U = 0x55,
    KEY_V = 0x56,
    KEY_W = 0x57,
    KEY_X = 0x58,
    KEY_Y = 0x59,
    KEY_Z = 0x5A,
    KEY_LEFT_BRACKET = VK_OEM_4,  /* [ */
    KEY_BACKSLASH = VK_OEM_5,  /* \ */
    KEY_RIGHT_BRACKET = VK_OEM_6,  /* ] */
    KEY_GRAVE_ACCENT = VK_OEM_3,  /* ` */

    KEY_ARROW_UP = VK_UP,
    KEY_ARROW_DOWN = VK_DOWN,
    KEY_ARROW_LEFT = VK_LEFT,
    KEY_ARROW_RIGHT = VK_RIGHT,

    // Function keys
    KEY_ESCAPE = VK_ESCAPE,
    KEY_ENTER = VK_RETURN,
    KEY_TAB = VK_TAB,
    KEY_BACKSPACE = VK_BACK,
    KEY_INSERT = VK_INSERT,
    KEY_DELETE = VK_DELETE,
    KEY_PAGE_UP = VK_PRIOR,
    KEY_PAGE_DOWN = VK_NEXT,
    KEY_HOME = VK_HOME,
    KEY_END = VK_END,
    KEY_CAPS_LOCK = VK_CAPITAL,
    KEY_SCROLL_LOCK = VK_SCROLL,
    KEY_NUM_LOCK = VK_NUMLOCK,
    KEY_PAUSE = VK_PAUSE,
    KEY_F1 = VK_F1,
    KEY_F2 = VK_F2,
    KEY_F3 = VK_F3,
    KEY_F4 = VK_F4,
    KEY_F5 = VK_F5,
    KEY_F6 = VK_F6,
    KEY_F7 = VK_F7,
    KEY_F8 = VK_F8,
    KEY_F9 = VK_F9,
    KEY_F10 = VK_F10,
    KEY_F11 = VK_F11,
    KEY_F12 = VK_F12,
    KEY_F13 = VK_F13,
    KEY_F14 = VK_F14,
    KEY_F15 = VK_F15,
    KEY_F16 = VK_F16,
    KEY_F17 = VK_F17,
    KEY_F18 = VK_F18,
    KEY_F19 = VK_F19,
    KEY_F20 = VK_F20,
    KEY_F21 = VK_F21,
    KEY_F22 = VK_F22,
    KEY_F23 = VK_F23,
    KEY_F24 = VK_F24,
    KEY_KP_0 = VK_NUMPAD0,
    KEY_KP_1 = VK_NUMPAD1,
    KEY_KP_2 = VK_NUMPAD2,
    KEY_KP_3 = VK_NUMPAD3,
    KEY_KP_4 = VK_NUMPAD4,
    KEY_KP_5 = VK_NUMPAD5,
    KEY_KP_6 = VK_NUMPAD6,
    KEY_KP_7 = VK_NUMPAD7,
    KEY_KP_8 = VK_NUMPAD8,
    KEY_KP_9 = VK_NUMPAD9,
    KEY_KP_DECIMAL = VK_DECIMAL,
    KEY_KP_DIVIDE = VK_DIVIDE,
    KEY_KP_MULTIPLY = VK_MULTIPLY,
    KEY_KP_SUBTRACT = VK_SUBTRACT,
    KEY_KP_ADD = VK_ADD,
    KEY_LEFT_SHIFT = 0x10,
    KEY_LEFT_CONTROL = 0x11,
    KEY_LEFT_ALT = VK_LMENU,
    KEY_RIGHT_SHIFT = VK_RSHIFT,
    KEY_RIGHT_CONTROL = VK_RCONTROL,
    KEY_RIGHT_ALT = VK_RMENU,
    KEY_MENU = VK_MENU,
};

/// @brief Represents a keyboard event.
/// 
/// This class provides functionality to store and retrieve information about keyboard events, such as the event type and key code.
class KeyboardEvent
{
public:
    /// @enum EventType
    /// @brief Enumerates the different types of keyboard events.
    enum class EventType
    {
        Press,    ///< Key press event.
        Release,  ///< Key release event.
        Invalid   ///< Invalid event.
    };

public:
    KeyboardEvent(); ///< Default constructor.
    KeyboardEvent(const KeyboardEvent& other) = default; ///< Copy constructor.
    KeyboardEvent& operator=(const KeyboardEvent& other) = default; ///< Copy assignment operator.
    KeyboardEvent(KeyboardEvent&& other) = default; ///< Move constructor.
    KeyboardEvent& operator=(KeyboardEvent&& other) = default; ///< Move assignment operator.
    ~KeyboardEvent() = default; ///< Destructor.

    /// @brief Parameterized constructor to initialize the keyboard event with specific values.
    /// @param _type The type of the event.
    /// @param _key The key code.
    KeyboardEvent(const EventType _type, const unsigned char _key);

    /// @brief Check if the event is a key press event.
    /// @return True if the event is a key press event, false otherwise.
    const bool isPress() const;

    /// @brief Check if the event is a key release event.
    /// @return True if the event is a key release event, false otherwise.
    const bool isRelease() const;

    /// @brief Check if the event is valid.
    /// @return True if the event is valid, false otherwise.
    const bool isValid() const;

    /// @brief Get the key code of the event.
    /// @return The key code.
    const unsigned char GetKeyCode() const;

private:
    EventType type; ///< Type of the keyboard event.
    unsigned char key; ///< Key code of the event.
};

#endif // KEYBOARDEVENT_H
