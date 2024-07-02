#ifndef _ShaderBase
#define _ShaderBase

#include <d3dcommon.h>
#include "Matrix.h"
#include <string>

struct ID3D11Device;
struct ID3D11InputLayout;
struct ID3D11PixelShader;
struct ID3D11VertexShader;
struct ID3D11DeviceContext;

struct D3D11_INPUT_ELEMENT_DESC;

/// Base class for shader management.
/// 
/// This class provides the basic functionality for shaders, including compilation,
/// setting to context, and managing shader resources.
class ShaderBase : public Align16
{
public:
    ShaderBase(const ShaderBase&) = delete; // Copy constructor
    ShaderBase(ShaderBase&&) = delete; // Move constructor
    ShaderBase& operator=(const ShaderBase&) & = delete; // Copy assignment operator
    ShaderBase& operator=(ShaderBase&&) & = delete; // Move assignment operator
    ShaderBase() = delete;
    virtual ~ShaderBase();

    /// Set the shader to the context.
    /// @param devcon Pointer to the device context.
    virtual void SetToContext(ID3D11DeviceContext* devcon) = 0;

    /// Get the device context.
    /// @return Pointer to the device context.
    ID3D11DeviceContext* GetContext();

protected:
    ID3D11Device* GetDevice();

    ShaderBase(ID3D11Device* device, WCHAR* filename, LPCSTR vsModel = "vs_4_0", LPCSTR psModel = "ps_4_0");
    void CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* layoutdesc, UINT size);
    void SaveContextPtr(ID3D11DeviceContext* devcon);
    void SetToContext_VS_PS_InputLayout();

private:
    ID3D11Device* mDevice; ///< Pointer to the DirectX device.
    ID3D11DeviceContext* mContext; ///< Pointer to the DirectX device context.

    ID3D11VertexShader* mpVertexShader; ///< Pointer to the vertex shader.
    ID3D11PixelShader* mpPixelShader; ///< Pointer to the pixel shader.
    ID3D11InputLayout* mpVertexLayout; ///< Pointer to the input layout.

    ID3DBlob* pVSBlob; ///< Pointer to the vertex shader blob.
    ID3DBlob* pPSBlob; ///< Pointer to the pixel shader blob.

    HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
    void privBuildShaders(WCHAR* filename, LPCSTR vsModel, LPCSTR psModel);
};

#endif // _ShaderBase
