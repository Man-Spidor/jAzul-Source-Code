#ifndef GRAPHICSOBJECT_SPRITE_H
#define GRAPHICSOBJECT_SPRITE_H

#include "GraphicObject_Base.h"

class Model;
class Image;

struct jAzulRect;

/// Represents a sprite graphics object.
/// 
/// This class defines a graphics object rendered as a sprite.
class GraphicsObject_Sprite : public GraphicsObject_Base
{
public:
    /// Default constructor (deleted).
    GraphicsObject_Sprite() = delete;

    /// Copy constructor.
    GraphicsObject_Sprite(const GraphicsObject_Sprite& other) = default;

    /// Copy assignment operator.
    GraphicsObject_Sprite& operator=(const GraphicsObject_Sprite& other) = default;

    /// Move constructor.
    GraphicsObject_Sprite(GraphicsObject_Sprite&& other) = default;

    /// Move assignment operator.
    GraphicsObject_Sprite& operator=(GraphicsObject_Sprite&& other) = default;

    /// Destructor.
    virtual ~GraphicsObject_Sprite() = default;

    /// Constructor to initialize the graphics object with a model, image, and rectangle.
    /// @param pMod Pointer to the model.
    /// @param _pImage Pointer to the image.
    /// @param _pRect Pointer to the rectangle.
    GraphicsObject_Sprite(Model* pMod, Image* _pImage, jAzulRect* _pRect);

    /// Get the image of the sprite.
    /// @return Reference to the image.
    Image& GetImage() const;

    /// Set the world transformation matrix.
    /// @param w The transformation matrix.
    void SetWorld(const Matrix& w);

    /// Render the graphics object.
    virtual void Render() override;

protected:
    /// Draw the graphics object.
    virtual void Draw() override;

private:
    Image* pImage; ///< Pointer to the image.
    jAzulRect* pRect; ///< Pointer to the rectangle.
};

#endif // GRAPHICSOBJECT_SPRITE_H
