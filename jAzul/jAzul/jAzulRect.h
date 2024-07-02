#ifndef JAZULRECT_H
#define JAZULRECT_H

/// Represents a rectangle with floating-point coordinates and dimensions.
/// 
/// This structure defines a rectangle with x and y coordinates for the top-left corner,
/// and width (w) and height (h) dimensions. It is used when working with sprites to define
/// the UV mapping area of the sprite.
struct jAzulRect
{
    /// Default constructor.
    jAzulRect();

    /// Copy constructor.
    jAzulRect(const jAzulRect& other) = default;

    /// Copy assignment operator.
    jAzulRect& operator=(const jAzulRect& other) = default;

    /// Move constructor.
    jAzulRect(jAzulRect&& other) = default;

    /// Move assignment operator.
    jAzulRect& operator=(jAzulRect&& other) = default;

    /// Destructor.
    ~jAzulRect() = default;

    /// Parameterized constructor to initialize the rectangle with specific values.
    /// @param _x The x-coordinate of the top-left corner.
    /// @param _y The y-coordinate of the top-left corner.
    /// @param _w The width of the rectangle.
    /// @param _h The height of the rectangle.
    jAzulRect(float _x, float _y, float _w, float _h);

    /// Equality operator.
    /// @param other The other jAzulRect to compare with.
    /// @return True if the rectangles are equal, false otherwise.
    bool operator==(const jAzulRect& other) const;

    /// Inequality operator.
    /// @param other The other jAzulRect to compare with.
    /// @return True if the rectangles are not equal, false otherwise.
    bool operator!=(const jAzulRect& other) const;

    /// Check if the rectangle contains a point.
    /// @param px The x-coordinate of the point.
    /// @param py The y-coordinate of the point.
    /// @return True if the rectangle contains the point, false otherwise.
    bool Contains(float px, float py) const;

    /// Get the area of the rectangle.
    /// @return The area of the rectangle.
    float Area() const;

    /// Get the perimeter of the rectangle.
    /// @return The perimeter of the rectangle.
    float Perimeter() const;

    float x; ///< The x-coordinate of the top-left corner.
    float y; ///< The y-coordinate of the top-left corner.
    float w; ///< The width of the rectangle.
    float h; ///< The height of the rectangle.
};

#endif // JAZULRECT_H
