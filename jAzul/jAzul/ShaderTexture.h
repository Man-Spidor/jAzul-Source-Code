#ifndef SHADERTEXTURE_H
#define SHADERTEXTURE_H

#include <d3d11.h>
#include <Matrix.h>
#include "ShaderBase.h"
#include "FogParamData.h"

/// Manages a texture shader.
/// 
/// This class provides functionality to manage a texture shader, including setting camera matrices,
/// sending world and fog data, and setting the shader to the context.
class ShaderTexture : public ShaderBase
{
public:
    ShaderTexture() = delete;
    ShaderTexture(const ShaderTexture& other) = default;
    ShaderTexture& operator=(const ShaderTexture& other) = default;
    ShaderTexture(ShaderTexture&& other) = default;
    ShaderTexture& operator=(ShaderTexture&& other) = default;
    ~ShaderTexture();

    ShaderTexture(ID3D11Device* device);

    virtual void SetToContext(ID3D11DeviceContext* devcon) override;

    /// Send the camera matrices to the shader.
    /// @param view The view matrix.
    /// @param proj The projection matrix.
    void SendCamMatrices(const Matrix& view, const Matrix& proj);

    /// Send the world matrix to the shader.
    /// @param world The world matrix.
    void SendWorld(const Matrix& world);

    /// Send the fog data to the shader.
    void SendFogData();

    /// Set the fog data.
    /// @param FogStart The start distance of the fog.
    /// @param FogRange The range of the fog.
    /// @param FogColor The color of the fog.
    void SetFogData(const float FogStart, const float FogRange, const Vect& FogColor);

    /// Set the eye position.
    /// @param eyePos The eye position vector.
    void SetEyePos(const Vect& eyePos);

    /// Set the fog scale.
    /// @param scale The fog scale.
    void SetFogScale(const float scale);

private:
    struct CamMatrices
    {
        Vect eyePos;
        Matrix View;
        Matrix Projection;
    };

    struct Data_World
    {
        Matrix World;
        Matrix WorldInv;
    };

    FogData fogData;
    Vect eyePos;
    ID3D11Buffer* mpBufferCamMatrices;
    ID3D11Buffer* mpBuffWorld;
    ID3D11Buffer* mpBuffFog;
};

#endif // SHADERTEXTURE_H
