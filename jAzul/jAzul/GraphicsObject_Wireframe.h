#ifndef GRAPHICSOBJECTWF_H
#define GRAPHICSOBJECTWF_H

#include "GraphicObject_Base.h"

/// Represents a wireframe graphics object.
/// 
/// This class defines a graphics object rendered as a wireframe.
class GraphicsObject_Wireframe : public GraphicsObject_Base
{
public:
    /// Default constructor (deleted).
    GraphicsObject_Wireframe() = delete;

    /// Copy constructor.
    GraphicsObject_Wireframe(const GraphicsObject_Wireframe& other) = default;

    /// Copy assignment operator.
    GraphicsObject_Wireframe& operator=(const GraphicsObject_Wireframe& other) = default;

    /// Move constructor.
    GraphicsObject_Wireframe(GraphicsObject_Wireframe&& other) = default;

    /// Move assignment operator.
    GraphicsObject_Wireframe& operator=(GraphicsObject_Wireframe&& other) = default;

    /// Destructor.
    virtual ~GraphicsObject_Wireframe();

    /// Constructor to initialize the graphics object with a model.
    /// @param pModel Pointer to the model.
    GraphicsObject_Wireframe(Model* pModel);

    /// Set the color of the wireframe.
    /// @param col The color vector.
    void SetColor(const Vect& col);

    /// Get the color of the wireframe.
    /// @return The color vector.
    const Vect& GetColor() const;

    /// Set the world transformation matrix.
    /// @param m The transformation matrix.
    void SetWorld(const Matrix& m);

    /// Render the graphics object.
    /// 
    /// Function called by user to push Graphics Object to the DrawManager
    virtual void Render() override;

protected:
    /// Draw the graphics object.
    /// 
    /// Function called by the DrawManager to actually draw the graphics object to the screen
    virtual void Draw() override;

private:
    Vect* MeshColors; ///< Array of colors for each mesh.
};

#endif // GRAPHICSOBJECTWF_H
