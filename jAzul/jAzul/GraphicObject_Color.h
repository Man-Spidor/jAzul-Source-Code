#ifndef _GraphicObject_Color
#define _GraphicObject_Color

#include "GraphicObject_Base.h"

/// @class GraphicsObject_Color
/// Represents a colored graphics object.
/// 
/// This class defines a graphics object with a single color or multiple colors for each mesh.
class GraphicsObject_Color : public GraphicsObject_Base
{
public:
    /// Default constructor (deleted).
    GraphicsObject_Color() = delete;

    /// Copy constructor.
    GraphicsObject_Color(const GraphicsObject_Color&) = default;

    /// Move constructor.
    GraphicsObject_Color(GraphicsObject_Color&&) = default;

    /// Copy assignment operator.
    GraphicsObject_Color& operator=(const GraphicsObject_Color&) & = default;

    /// Move assignment operator.
    GraphicsObject_Color& operator=(GraphicsObject_Color&&) & = default;

    /// Destructor.
    virtual ~GraphicsObject_Color();

    /// Constructor to initialize the graphics object with a model.
    /// @param mod Pointer to the model.
    GraphicsObject_Color(Model* mod);

    /// Set the color of the graphics object.
    /// @param col The color vector.
    void SetColor(const Vect& col);

    /// Set the color of a specific mesh in the graphics object.
    /// @param col The color vector.
    /// @param meshnum The index of the mesh.
    void SetColor(const Vect& col, int meshnum);

    /// Set the world transformation matrix.
    /// @param m The transformation matrix.
    void SetWorld(const Matrix& m);

    /// Render the graphics object.
    virtual void Render() override;

    /// Draw the graphics object.
    virtual void Draw() override;

private:
    Vect* MeshColors; ///< Array of colors for each mesh.
};

#endif _GraphicObject_Color
