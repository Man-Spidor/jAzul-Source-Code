#ifndef GRAPHICSOBJECT_TEXTUREALPHA_H
#define GRAPHICSOBJECT_TEXTUREALPHA_H

#include "GraphicsObject_TextureLight.h"

/// Represents a textured graphics object with alpha transparency.
/// 
/// This class defines a textured graphics object with alpha transparency.
/// This class extends GraphicsObject_TextureLight as they act in the same way, the only difference is the order they are rendered in
/// 
/// @see GraphicsObject_TextureLight
class GraphicsObject_TextureAlpha : public GraphicsObject_TextureLight
{
public:
    /// Default constructor (deleted).
    GraphicsObject_TextureAlpha() = delete;
    GraphicsObject_TextureAlpha(const GraphicsObject_TextureAlpha& other) = default;
    GraphicsObject_TextureAlpha& operator=(const GraphicsObject_TextureAlpha& other) = default;
    GraphicsObject_TextureAlpha(GraphicsObject_TextureAlpha&& other) = default;
    GraphicsObject_TextureAlpha& operator=(GraphicsObject_TextureAlpha&& other) = default;
    ~GraphicsObject_TextureAlpha() = default;
    GraphicsObject_TextureAlpha(Model* mod);

    /// Render the graphics object.
    /// 
    /// Function called by user to push Graphics Object to the DrawManager
    virtual void Render() override;
};

#endif // GRAPHICSOBJECT_TEXTUREALPHA_H
