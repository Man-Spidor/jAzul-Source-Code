#ifndef MOUSEPOINT_H
#define MOUSEPOINT_H

/// @brief Represents a point on the screen with x and y coordinates.
/// 
/// This structure contains the x and y coordinates of a point, typically used for mouse events.
struct MousePoint
{
    /// @brief Parameterized constructor to initialize the mouse point with specific coordinates.
    /// @param _x The x-coordinate of the point.
    /// @param _y The y-coordinate of the point.
    MousePoint(const int _x, const int _y) : x(_x), y(_y) { };

    int x; ///< The x-coordinate of the point.
    int y; ///< The y-coordinate of the point.
};

#endif // MOUSEPOINT_H
