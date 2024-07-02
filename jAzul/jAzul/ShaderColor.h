#ifndef _ShaderColor
#define _ShaderColor

#include "ShaderBase.h"
#include "Matrix.h"
#include "FogParamData.h"

struct ID3D11Buffer;
struct ID3D11Device;

/// Manages a color shader.
/// 
/// This class provides functionality to manage a color shader, including setting camera matrices,
/// sending world and color data, and setting the shader to the context.
class ShaderColor : public ShaderBase
{
public:
    ShaderColor(const ShaderColor&) = delete; // Copy constructor
    ShaderColor(ShaderColor&&) = default; // Move constructor
    ShaderColor& operator=(const ShaderColor&) & = default; // Copy assignment operator
    ShaderColor& operator=(ShaderColor&&) & = default; // Move assignment operator
    ~ShaderColor(); // Destructor

    ShaderColor(ID3D11Device* device);

    virtual void SetToContext(ID3D11DeviceContext* devcon) override;

    /// Send the camera matrices to the shader.
    /// @param view The view matrix.
    /// @param proj The projection matrix.
    void SendCamMatrices(const Matrix& view, const Matrix& proj);

    /// Send the world and color data to the shader.
    /// @param world The world matrix.
    /// @param col The color vector.
    void SendWorldColor(const Matrix& world, const Vect& col);

private:
    struct CamMatrices
    {
        Matrix View;
        Matrix Projection;
    };

    struct Data_WorldColor
    {
        Matrix World;
        Vect Color;
    };

    ID3D11Buffer* mpBufferCamMatrices;
    ID3D11Buffer* mpBuffWordColor;
};

#endif // _ShaderColor
