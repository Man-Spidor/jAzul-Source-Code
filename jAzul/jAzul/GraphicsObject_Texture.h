#ifndef GRAPHICSOBJECT_TEXTURE_H
#define GRAPHICSOBJECT_TEXTURE_H

#include "GraphicObject_Base.h"

class Texture;

/// Represents a textured graphics object.
/// 
/// This class defines a graphics object with a texture applied.
class GraphicsObject_Texture : public GraphicsObject_Base
{
public:
    /// Default constructor (deleted).
    GraphicsObject_Texture() = delete;

    /// Copy constructor.
    GraphicsObject_Texture(const GraphicsObject_Texture& other) = default;

    /// Copy assignment operator.
    GraphicsObject_Texture& operator=(const GraphicsObject_Texture& other) = default;

    /// Move constructor.
    GraphicsObject_Texture(GraphicsObject_Texture&& other) = default;

    /// Move assignment operator.
    GraphicsObject_Texture& operator=(GraphicsObject_Texture&& other) = default;

    /// Destructor.
    virtual ~GraphicsObject_Texture();

    /// Constructor to initialize the graphics object with a model.
    /// @param _pModel Pointer to the model.
    GraphicsObject_Texture(Model* _pModel);

    /// Set the scale of the graphics object.
    /// @param scale The scale factor.
    void SetScale(const float scale);

    /// Set the texture of the graphics object.
    /// @param pTexture Pointer to the texture.
    void SetTexture(Texture* pTexture);

    /// Set the texture of a specific mesh in the graphics object.
    /// @param meshnum The index of the mesh.
    /// @param pTexture Pointer to the texture.
    void SetTexture(const unsigned int meshnum, Texture* pTexture);

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
    Texture** MeshTextures; ///< Array of textures for each mesh.
    float scale; ///< Scale factor of the graphics object.
};

#endif // GRAPHICSOBJECT_TEXTURE_H
