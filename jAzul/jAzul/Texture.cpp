#include "Texture.h"

#include "d3dUtil.h"
#include "DirectXTex.h"

#include "GraphicsAttorney.h"

#include "Sampler.h"

Texture::~Texture()
{
	ReleaseAndDeleteCOMobject(mpTextureRV);
}

Texture::Texture(LPCWSTR filepath, Sampler* pSampler, bool ComputeMip, size_t miplevel, DirectX::TEX_FILTER_FLAGS filterflags )
{
	ID3D11Device* d3dDev = GraphicsAttorney::Device::GetDevice();

	std::wstring fpath(filepath);
	std::wstring ext = fpath.substr(fpath.find_last_of(L".") + 1);

	DirectX::ScratchImage scrtTex;
	HRESULT hr = S_OK;
	if (ext == L"tga" || ext == L"TGA")
	{
		hr = LoadFromTGAFile(filepath, nullptr, scrtTex);
	} 
	else if (ext == L"dds" || ext == L"DDS")
	{
		hr = LoadFromDDSFile(filepath, DirectX::DDS_FLAGS_NONE, nullptr, scrtTex);
	}
	else
	{
		assert(false && "ERROR: Invalid file format");
	}
	assert(SUCCEEDED(hr));

	if (ComputeMip)
	{
		assert( scrtTex.GetImageCount() == 1 && "ERROR: File already contains MIP map." );
		DirectX::ScratchImage mipchain;
		hr = DirectX::GenerateMipMaps(*(scrtTex.GetImage(0, 0, 0)), filterflags, miplevel, mipchain);
		assert(SUCCEEDED(hr));

		CreateShaderResourceView(d3dDev, mipchain.GetImage(0, 0, 0), mipchain.GetImageCount(), mipchain.GetMetadata(), &mpTextureRV);
	}
	else
	{
		CreateShaderResourceView(d3dDev, scrtTex.GetImage(0, 0, 0), scrtTex.GetImageCount(), scrtTex.GetMetadata(), &mpTextureRV);
	}
		
	this->width	 =	static_cast<float>(scrtTex.GetMetadata().width);
	this->height =	static_cast<float>(scrtTex.GetMetadata().height);

	this->pSampler = pSampler;
}

void Texture::SetToContext(ID3D11DeviceContext* devcon, int texResSlot,  int sampSlot)
{
	devcon->PSSetShaderResources(texResSlot, 1, &mpTextureRV);
	this->pSampler->SetToContext(devcon, sampSlot);
}

float Texture::getWidth() const
{
	return this->width;
}

float Texture::getHeight() const
{
	return this->height;
}

