#ifndef SHADERCONTEXTMANAGER_H
#define SHADERCONTEXTMANAGER_H

#include "ShaderType.h"
#include "LightParamData.h"

class Matrix;
class ShaderColor;
class ShaderColorLight;
class ShaderTexture;
class ShaderTextureLight;
class ShaderSprite;

struct jAzulRect;
struct ID3D11Device;
struct ID3D11DeviceContext;

/// Manages the context for different shaders.
/// 
/// This singleton class provides functionality to initialize, update, and shutdown all shaders.
/// It also manages sending various parameters to the shaders and setting them to the context.
class ShaderContextManager
{
    friend class GraphicsAttorney;
public:
    ShaderContextManager() = default;
    ShaderContextManager(const ShaderContextManager& other) = delete;
    ShaderContextManager& operator=(const ShaderContextManager& other) = delete;
    ShaderContextManager(ShaderContextManager&& other) = delete;
    ShaderContextManager& operator=(ShaderContextManager&& other) = delete;
    ~ShaderContextManager();

private:
    /// Initialize all shaders.
    /// @param context Pointer to the device context.
    static void InitAllShaders(ID3D11DeviceContext*& context);

    /// Shutdown all shaders.
    static void Shutdown();

    /// Update the context.
    /// @param context Pointer to the device context.
    static void UpdateContext(ID3D11DeviceContext*& context);

    /// Get the current context.
    /// @return Pointer to the device context.
    static ID3D11DeviceContext*& GetContext();

    /// Send the camera matrices to the shader.
    /// @param view The view matrix.
    /// @param proj The projection matrix.
    static void SendCamMatrices(const Matrix& view, const Matrix& proj);

    /// Send the 2D camera matrices to the shader.
    /// @param view The view matrix.
    /// @param proj The projection matrix.
    static void Send2DCamMatrices(const Matrix& view, const Matrix& proj);

    /// Send the light parameters to the shader.
    /// @param eyePos The eye position vector.
    static void SendLightParams(const Vect& eyePos);

    /// Send the screen size to the shader.
    /// @param width The screen width.
    /// @param height The screen height.
    static void SendScreenSize(const unsigned int width, const unsigned int height);

public:
    /// Set the fog data.
    /// @param FogStart The start distance of the fog.
    /// @param FogRange The range of the fog.
    /// @param FogColor The color of the fog.
    static void SetFogData(const float FogStart, const float FogRange, const Vect& FogColor);

    /// Set the directional light parameters.
    /// @param ln The light number.
    /// @param pLight Pointer to the directional light.
    static void SetDirectionalLightParameters(LIGHTNUM ln, const DirectionalLight* pLight);

    /// Set the point light parameters.
    /// @param ln The light number.
    /// @param pLight Pointer to the point light.
    static void SetPointLightParameters(LIGHTNUM ln, const PointLight* pLight);

    /// Set the spot light parameters.
    /// @param ln The light number.
    /// @param pLight Pointer to the spot light.
    static void SetSpotLightParameters(LIGHTNUM ln, const SpotLight* pLight);

private:
    /// Send the color parameters to the shader.
    /// @param world The world matrix.
    /// @param col The color vector.
    /// @param scale The scale factor.
    static void SendColorParams(const Matrix& world, const Vect& col, const float scale = 1.0f);

    /// Send the color light parameters to the shader.
    /// @param world The world matrix.
    /// @param amb The ambient color vector.
    /// @param dif The diffuse color vector.
    /// @param sp The specular color vector.
    /// @param scale The scale factor.
    static void SendColorLightParams(const Matrix& world, const Vect& amb = Vect(.5f, .5f, .5f), const Vect& dif = Vect(.5f, .5f, .5f), const Vect& sp = Vect(.5f, .5f, .5f), const float scale = 1.0f);

    /// Send the texture parameters to the shader.
    /// @param world The world matrix.
    /// @param scale The scale factor.
    static void SendTextureParams(const Matrix& world, const float scale = 1.0f);

    /// Send the texture light parameters to the shader.
    /// @param world The world matrix.
    /// @param amb The ambient color vector.
    /// @param dif The diffuse color vector.
    /// @param sp The specular color vector.
    /// @param scale The scale factor.
    static void SendTextureLightParams(const Matrix& world, const Vect& amb = Vect(.5f, .5f, .5f), const Vect& dif = Vect(.5f, .5f, .5f), const Vect& sp = Vect(.5f, .5f, .5f), const float scale = 1.0f);

    /// Send the sprite parameters to the shader.
    /// @param pos The position matrix.
    /// @param texWidth The texture width.
    /// @param texHeight The texture height.
    /// @param pImgRect The image rectangle.
    static void SendSpriteParams(const Matrix& pos, float texWidth, float texHeight, const jAzulRect& pImgRect);

    /// Set the color shader to the context.
    static void SetColorToContext();

    /// Set the color light shader to the context.
    static void SetColorLightToContext();

    /// Set the texture shader to the context.
    static void SetTextureToContext();

    /// Set the texture light shader to the context.
    static void SetTextureLightToContext();

    /// Set the sprite shader to the context.
    static void SetSpriteToContext();

private:
    static ShaderContextManager& Instance();
    static ShaderContextManager* instance;

    static ID3D11DeviceContext* pCurrentContext;
    static ShaderColor* pShaderColor;
    static ShaderColorLight* pShaderColorLight;
    static ShaderTexture* pShaderTex;
    static ShaderTextureLight* pShaderTexLight;
    static ShaderSprite* pShaderSprite;
};

#endif // SHADERCONTEXTMANAGER_H
