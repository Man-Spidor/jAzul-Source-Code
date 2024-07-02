#ifndef MOUSE_H
#define MOUSE_H

#include "MouseEvent.h"
#include <queue>

/// @brief Manages mouse input.
/// 
/// This class provides functionality to handle mouse events, store mouse states, and retrieve mouse events and position.
class Mouse
{
public:
    Mouse(); ///< Default constructor.
    Mouse(const Mouse& other) = default; ///< Copy constructor.
    Mouse& operator=(const Mouse& other) = default; ///< Copy assignment operator.
    Mouse(Mouse&& other) = default; ///< Move constructor.
    Mouse& operator=(Mouse&& other) = default; ///< Move assignment operator.
    ~Mouse() = default; ///< Destructor.

    // WINDOW PROC FUNCTIONS
    void OnLeftPressed(int x, int y);
    void OnLeftReleased(int x, int y);
    void OnRightPressed(int x, int y);
    void OnRightReleased(int x, int y);
    void OnMiddlePressed(int x, int y);
    void OnMiddleReleased(int x, int y);
    void OnWheelUp(int x, int y);
    void OnWheelDown(int x, int y);
    void OnMouseMove(int x, int y);
    void OnMouseMoveRaw(int x, int y);

    /// @brief Check if the left mouse button is pressed.
    /// @return True if the left mouse button is pressed, false otherwise.
    bool IsLeftDown() const;

    /// @brief Check if the middle mouse button is pressed.
    /// @return True if the middle mouse button is pressed, false otherwise.
    bool IsMiddleDown() const;

    /// @brief Check if the right mouse button is pressed.
    /// @return True if the right mouse button is pressed, false otherwise.
    bool IsRightDown() const;

    /// @brief Get the x-coordinate of the mouse position.
    /// @return The x-coordinate of the mouse position.
    int GetPosX() const;

    /// @brief Get the y-coordinate of the mouse position.
    /// @return The y-coordinate of the mouse position.
    int GetPosY() const;

    /// @brief Get the mouse position.
    /// @return The mouse position.
    MousePoint GetPos() const;

    /// @brief Check if the event buffer is empty.
    /// @return True if the event buffer is empty, false otherwise.
    bool EventBufferIsEmpty();

    /// @brief Read the next mouse event from the buffer.
    /// @return The next mouse event.
    MouseEvent ReadEvent();

private:
    std::queue<MouseEvent> eventBuffer; ///< Queue to store mouse events.
    static bool leftDown; ///< State of the left mouse button.
    static bool rightDown; ///< State of the right mouse button.
    static bool middleDown; ///< State of the middle mouse button.
    static MousePoint pos; ///< Position of the mouse.
};

#endif // MOUSE_H
