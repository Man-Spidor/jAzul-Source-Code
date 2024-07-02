#ifndef GRAPHICSOBJECT_TEXTURELIGHT_H
#define GRAPHICSOBJECT_TEXTURELIGHT_H

#include "GraphicObject_Base.h"

struct Material;

class Texture;
class ShaderTextureLight;

/// Represents a textured graphics object with lighting.
/// 
/// This class defines a graphics object with a texture and lighting effects.
class GraphicsObject_TextureLight : public GraphicsObject_Base
{
public:
    /// Default constructor (deleted).
    GraphicsObject_TextureLight() = delete;

    /// Copy constructor.
    GraphicsObject_TextureLight(const GraphicsObject_TextureLight& other) = default;

    /// Copy assignment operator.
    GraphicsObject_TextureLight& operator=(const GraphicsObject_TextureLight& other) = default;

    /// Move constructor.
    GraphicsObject_TextureLight(GraphicsObject_TextureLight&& other) = default;

    /// Move assignment operator.
    GraphicsObject_TextureLight& operator=(GraphicsObject_TextureLight&& other) = default;

    /// Destructor.
    virtual ~GraphicsObject_TextureLight();

    /// Constructor to initialize the graphics object with a model.
    /// @param mod Pointer to the model.
    GraphicsObject_TextureLight(Model* mod);

    /// Set the scale of the graphics object.
    /// @param _scale The scale factor.
    void SetScale(const float _scale);

    /// Set the texture of the graphics object.
    /// @param pTexture Pointer to the texture.
    void SetTexture(Texture* pTexture);

    /// Set the texture of a specific mesh in the graphics object.
    /// @param meshnum The index of the mesh.
    /// @param pTexture Pointer to the texture.
    void SetTexture(const unsigned int meshnum, Texture* pTexture);

    /// Set the material properties of the graphics object.
    /// @param amb The ambient color vector.
    /// @param diff The diffuse color vector.
    /// @param sp The specular color vector.
    void SetMaterial(const Vect& amb, const Vect& diff, const Vect& sp);

    /// Set the material properties of a specific mesh in the graphics object.
    /// @param meshNum The index of the mesh.
    /// @param amb The ambient color vector.
    /// @param diff The diffuse color vector.
    /// @param sp The specular color vector.
    void SetMaterial(const unsigned int meshNum, const Vect& amb, const Vect& diff, const Vect& sp);

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
    Material* MeshColors; ///< Array of material properties for each mesh.
    Texture** MeshTextures; ///< Array of textures for each mesh.
    float scale; ///< Scale factor of the graphics object.
};

#endif // GRAPHICSOBJECT_TEXTURELIGHT_H
