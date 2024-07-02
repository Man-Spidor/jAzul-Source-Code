#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include "MousePoint.h"

/// @brief Represents a mouse event.
/// 
/// This class provides functionality to store and retrieve information about mouse events, such as the event type and position.
class MouseEvent
{
public:
    /// @enum EventType
    /// @brief Enumerates the different types of mouse events.
    enum class EventType
    {
        LPress,    ///< Left button press.
        LRelease,  ///< Left button release.
        RPress,    ///< Right button press.
        RRelease,  ///< Right button release.
        MPress,    ///< Middle button press.
        MRelease,  ///< Middle button release.
        WheelUp,   ///< Mouse wheel up.
        WheelDown, ///< Mouse wheel down.
        Move,      ///< Mouse move.
        RAW_MOVE,  ///< Raw mouse move.
        Invalid    ///< Invalid event.
    };

public:
    MouseEvent(); ///< Default constructor.
    MouseEvent(const MouseEvent& other) = default; ///< Copy constructor.
    MouseEvent& operator=(const MouseEvent& other) = default; ///< Copy assignment operator.
    MouseEvent(MouseEvent&& other) = default; ///< Move constructor.
    MouseEvent& operator=(MouseEvent&& other) = default; ///< Move assignment operator.
    ~MouseEvent() = default; ///< Destructor.

    /// @brief Parameterized constructor to initialize the mouse event with specific values.
    /// @param type The type of the event.
    /// @param x The x-coordinate of the event.
    /// @param y The y-coordinate of the event.
    MouseEvent(const EventType type, const int x, const int y);

    /// @brief Get the type of the mouse event.
    /// @return The type of the event.
    const EventType GetType() const;

    /// @brief Get the position of the mouse event.
    /// @return The position of the event.
    const MousePoint GetPos() const;

    /// @brief Check if the event is valid.
    /// @return True if the event is valid, false otherwise.
    const bool IsValid() const;

    /// @brief Get the x-coordinate of the mouse event.
    /// @return The x-coordinate of the event.
    const int GetPosX() const;

    /// @brief Get the y-coordinate of the mouse event.
    /// @return The y-coordinate of the event.
    const int GetPosY() const;

private:
    EventType type; ///< Type of the mouse event.
    MousePoint pos; ///< Position of the mouse event.
};

#endif // MOUSEEVENT_H
