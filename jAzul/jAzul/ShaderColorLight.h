#ifndef _ShaderColorLight
#define _ShaderColorLight

#include "ShaderBase.h"
#include "FogParamData.h"
#include "LightParamData.h"

struct ID3D11Buffer;
struct ID3D11Device;

/// Manages a color shader with lighting.
/// 
/// This class provides functionality to manage a color shader with lighting, including setting light parameters,
/// sending camera matrices, world and material data, and setting the shader to the context.
class ShaderColorLight : public ShaderBase
{
public:
    ShaderColorLight(const ShaderColorLight&) = delete; // Copy constructor
    ShaderColorLight(ShaderColorLight&&) = default; // Move constructor
    ShaderColorLight& operator=(const ShaderColorLight&) & = default; // Copy assignment operator
    ShaderColorLight& operator=(ShaderColorLight&&) & = default; // Move assignment operator
    ~ShaderColorLight(); // Destructor

    ShaderColorLight(ID3D11Device* device);

    virtual void SetToContext(ID3D11DeviceContext* devcon) override;

    /// Set the directional light parameters.
    /// @param ln The light number.
    /// @param dir The direction vector.
    /// @param amb The ambient color vector.
    /// @param dif The diffuse color vector.
    /// @param sp The specular color vector.
    void SetDirectionalLightParameters(LIGHTNUM ln, const Vect& dir, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));

    /// Set the point light parameters.
    /// @param ln The light number.
    /// @param pos The position vector.
    /// @param r The radius.
    /// @param att The attenuation vector.
    /// @param amb The ambient color vector.
    /// @param dif The diffuse color vector.
    /// @param sp The specular color vector.
    void SetPointLightParameters(LIGHTNUM ln, const Vect& pos, float r, const Vect& att, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));

    /// Set the spot light parameters.
    /// @param ln The light number.
    /// @param pos The position vector.
    /// @param r The radius.
    /// @param att The attenuation vector.
    /// @param dir The direction vector.
    /// @param spotExp The spotlight exponent.
    /// @param amb The ambient color vector.
    /// @param dif The diffuse color vector.
    /// @param sp The specular color vector.
    void SetSpotLightParameters(LIGHTNUM ln, const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));

    /// Set the fog data.
    /// @param FogStart The start distance of the fog.
    /// @param FogRange The range of the fog.
    /// @param FogColor The color of the fog.
    void SetFogData(const float FogStart, const float FogRange, const Vect& FogColor);

    /// Set the fog scale.
    /// @param scale The fog scale.
    void SetFogScale(const float scale);

    /// Send the camera matrices to the shader.
    /// @param view The view matrix.
    /// @param proj The projection matrix.
    void SendCamMatrices(const Matrix& view, const Matrix& proj);

    /// Send the light parameters to the shader.
    /// @param eyepos The eye position vector.
    void SendLightParameters(const Vect& eyepos);

    /// Send the world and material data to the shader.
    /// @param world The world matrix.
    /// @param amb The ambient color vector.
    /// @param dif The diffuse color vector.
    /// @param sp The specular color vector.
    /// @param scale The scale factor.
    void SendWorldAndMaterial(const Matrix& world, const Vect& amb = Vect(.5f, .5f, .5f), const Vect& dif = Vect(.5f, .5f, .5f), const Vect& sp = Vect(.5f, .5f, .5f), const float scale = 1.0f);

    /// Send the fog data to the shader.
    void SendFogData();

private:
    DirectionalLight DirLightData[MAX_DIR_LIGHTS];
    PointLight PointLightData[MAX_POINT_LIGHTS];
    SpotLight SpotLightData[MAX_SPOT_LIGHTS];

    struct CamMatrices
    {
        Matrix View;
        Matrix Projection;
    };

    FogData FogParamData;
    ID3D11Buffer* mpBufferCamMatrices;
    ID3D11Buffer* mpBuffWordAndMaterial;
    ID3D11Buffer* mpBufferLightParams;
    ID3D11Buffer* mpBufferFogParams;
};

#endif // _ShaderColorLight
