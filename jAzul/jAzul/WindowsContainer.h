#ifndef WINDOWCONTAINER_H
#define WINDOWCONTAINER_H

#include "jAzul.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "RenderWindow.h"

/// @brief Manages the window and input devices.
/// 
/// This class provides functionality to handle window messages and manage input devices such as the keyboard and mouse.
/// 
/// @see Engine
class WindowContainer
{
public:
    WindowContainer(); ///< Default constructor.
    WindowContainer(const WindowContainer& other) = default; ///< Copy constructor.
    WindowContainer& operator=(const WindowContainer& other) = default; ///< Copy assignment operator.
    WindowContainer(WindowContainer&& other) = default; ///< Move constructor.
    WindowContainer& operator=(WindowContainer&& other) = default; ///< Move assignment operator.
    ~WindowContainer() = default; ///< Destructor.

    /// @brief Processes window messages.
    /// @param hwnd Handle to the window.
    /// @param uMsg The message.
    /// @param wParam Additional message information.
    /// @param lParam Additional message information.
    /// @return The result of the message processing.
    LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
    jAzul graphicsEngine; ///< The graphics engine.
    Keyboard kb; ///< The keyboard input device.
    RenderWindow windowRenderer; ///< The window renderer.
    Mouse mo; ///< The mouse input device.
};

#endif // WINDOWCONTAINER_H
