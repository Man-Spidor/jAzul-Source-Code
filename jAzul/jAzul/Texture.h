#ifndef _Texture
#define _Texture

#include <string>
#include "DirectXTex.h"

class Sampler;

/// Manages a DirectX texture resource.
/// 
/// This class provides functionality to load and manage a DirectX texture resource,
/// including setting the texture to a context and retrieving its dimensions.
/// 
/// @warning This Texture class ONLY accepts .tga files.
class Texture
{
public:
    /// Copy constructor (deleted).
    Texture(const Texture&) = delete;

    /// Move constructor (deleted).
    Texture(Texture&&) = delete;

    /// Copy assignment operator (deleted).
    Texture& operator=(const Texture&) & = delete;

    /// Move assignment operator (deleted).
    Texture& operator=(Texture&&) & = delete;

    /// Destructor.
    ~Texture();

    /// Default constructor (deleted).
    Texture() = delete;

    /// Constructor to initialize the texture from a file path.
    /// @param filepath The file path to the texture.
    /// @param pSampler Pointer to the sampler.
    /// @param ComputeMip Whether to compute mip levels (default is false).
    /// @param miplevel The mip level (default is 0).
    /// @param filterflags The filter flags (default is DirectX::TEX_FILTER_LINEAR).
    Texture(LPCWSTR filepath, Sampler* pSampler, bool ComputeMip = false, size_t miplevel = 0, DirectX::TEX_FILTER_FLAGS filterflags = DirectX::TEX_FILTER_LINEAR);

    /// Set the texture and sampler to the specified context slots.
    /// @param devcon The DirectX device context.
    /// @param texResSlot The texture resource slot (default is 0).
    /// @param sampSlot The sampler slot (default is 0).
    void SetToContext(ID3D11DeviceContext* devcon, int texResSlot = 0, int sampSlot = 0);

    /// Get the width of the texture.
    /// @return The width of the texture.
    float getWidth() const;

    /// Get the height of the texture.
    /// @return The height of the texture.
    float getHeight() const;

private:
    ID3D11ShaderResourceView* mpTextureRV; ///< Pointer to the DirectX texture resource view.
    Sampler* pSampler; ///< Pointer to the sampler.

    float width; ///< The width of the texture.
    float height; ///< The height of the texture.
};

#endif _Texture
