#ifndef _GraphicObject_Base
#define _GraphicObject_Base

#include "Matrix.h"

class Model;
class ShaderMeshData;
class ShaderBase;

struct ID3D11DeviceContext;

/// Base class for all graphics objects.
/// 
/// This abstract class provides a common interface for all graphics objects, including methods to set the model,
/// set the world transformation matrix, and render the object.
class GraphicsObject_Base : public Align16
{
    friend class GraphicsAttorney;

public:
    /// Default constructor (deleted).
    GraphicsObject_Base() = delete;

    /// Copy constructor.
    GraphicsObject_Base(const GraphicsObject_Base&) = default;

    /// Move constructor.
    GraphicsObject_Base(GraphicsObject_Base&&) = default;

    /// Copy assignment operator.
    GraphicsObject_Base& operator=(const GraphicsObject_Base&) & = default;

    /// Move assignment operator.
    GraphicsObject_Base& operator=(GraphicsObject_Base&&) & = default;

    /// Destructor.
    virtual ~GraphicsObject_Base() = default;

    /// Constructor to initialize the graphics object with a model.
    /// @param _pModel Pointer to the model.
    GraphicsObject_Base(Model* _pModel);

    /// Set the model for the graphics object.
    /// @param mod Pointer to the model.
    void SetModel(Model* mod);

    /// Get the model of the graphics object.
    /// @return Pointer to the model.
    Model* GetModel() const;

    /// Set the world transformation matrix.
    /// @param _world The transformation matrix.
    void SetWorld(const Matrix& _world);

    /// Get the world transformation matrix.
    /// @return The transformation matrix.
    const Matrix& GetWorld() const;

    /// Render the graphics object (pure virtual).
    virtual void Render() = 0;

protected:
    /// Draw the graphics object (pure virtual).
    virtual void Draw() = 0;

    Matrix world; ///< The world transformation matrix.
    Model* pModel; ///< Pointer to the model.
};

#endif _GraphicObject_Base
