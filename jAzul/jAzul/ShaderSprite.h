#ifndef SHADERSPRITE_H
#define SHADERSPRITE_H

#include "ShaderBase.h"

struct jAzulRect;
struct ID3D11Buffer;
struct ID3D11Device;

/// Manages a sprite shader.
/// 
/// This class provides functionality to manage a sprite shader, including setting camera matrices,
/// sending world and image data, and setting the shader to the context.
class ShaderSprite : public ShaderBase
{
public:
    ShaderSprite() = delete;
    ShaderSprite(const ShaderSprite& other) = default;
    ShaderSprite& operator=(const ShaderSprite& other) = default;
    ShaderSprite(ShaderSprite&& other) = default;
    ShaderSprite& operator=(ShaderSprite&& other) = default;
    ~ShaderSprite();

    ShaderSprite(ID3D11Device* device);

    virtual void SetToContext(ID3D11DeviceContext* devcon) override;

    /// Set the screen size for the shader.
    /// @param width The screen width.
    /// @param height The screen height.
    void SetScreenSize(const unsigned int width, const unsigned int height);

    /// Send the camera matrices to the shader.
    /// @param view The view matrix.
    /// @param proj The projection matrix.
    void SendCamMatrices(const Matrix& view, const Matrix& proj);

    /// Send the world and image data to the shader.
    /// @param world The world matrix.
    /// @param texWidth The texture width.
    /// @param texHeight The texture height.
    /// @param imgRect The image rectangle.
    void SendWorld(const Matrix& world, float texWidth, float texHeight, const jAzulRect& imgRect);

private:
    struct CamMatrices
    {
        Matrix View;
        Matrix Projection;
    };

    struct Data_World
    {
        Matrix World;
        float texW = 0.0f;
        float texH = 0.0f;
        float imgW = 0.0f;
        float imgH = 0.0f;
        float imgX = 0.0f;
        float imgY = 0.0f;
    };

    Matrix ScreenOffset;

    ID3D11Buffer* mpBufferCamMatrices;
    ID3D11Buffer* mpBuffWorld;
};

#endif // SHADERSPRITE_H
