#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include "ErrorLogger.h"

class WindowContainer;

/// @brief Manages the window.
/// 
/// This class provides functionality to create, initialize, and manage the game window, including handling window messages and updating the window title.
class RenderWindow
{
public:
    RenderWindow(); ///< Default constructor.
    RenderWindow(const RenderWindow& other) = default; ///< Copy constructor.
    RenderWindow& operator=(const RenderWindow& other) = default; ///< Copy assignment operator.
    RenderWindow(RenderWindow&& other) = default; ///< Move constructor.
    RenderWindow& operator=(RenderWindow&& other) = default; ///< Move assignment operator.
    ~RenderWindow(); ///< Destructor.

    /// @brief Initialize the game window.
    /// @param _hInstance Handle to the application instance.
    /// @param pWinContainer Pointer to the window container.
    /// @param _window_title Title of the window.
    /// @param _window_class Class name of the window.
    /// @param _width Width of the window.
    /// @param _height Height of the window.
    /// @return True if initialization is successful, false otherwise.
    bool Initialize(HINSTANCE _hInstance, WindowContainer* pWinContainer, std::string _window_title, std::string _window_class, int _width, int _height);

    /// @brief Process window messages.
    /// @return True if messages are processed, false otherwise.
    bool ProcessMessages();

    /// @brief Set the name of the window.
    /// @param _window_title The name of the window.
    void SetWindowName(std::string _window_title);

    /// @brief Update the window title.
    /// @param _window_title The new window title.
    void UpdateWindowText(std::string _window_title);

    /// @brief Get the handle of the window.
    /// @return The handle of the window.
    HWND GetHandle() const;

    /// @brief Get the width of the window.
    /// @return The width of the window.
    const int GetWidth() const;

    /// @brief Get the height of the window.
    /// @return The height of the window.
    const int GetHeight() const;

private:
    /// @brief Register the window class.
    void RegisterWindowClass();

    HWND handle; ///< Handle to the window.
    HINSTANCE hInstance; ///< Handle to the application instance.
    std::string window_title; ///< Title of the window.
    std::wstring window_title_wide; ///< Wide string version of the window title.
    std::string window_class; ///< Class name of the window.
    std::wstring window_class_wide; ///< Wide string version of the window class name.
    int width; ///< Width of the window.
    int height; ///< Height of the window.
};

#endif // RENDERWINDOW_H
