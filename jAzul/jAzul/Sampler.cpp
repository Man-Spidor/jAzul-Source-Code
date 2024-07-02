#include "Sampler.h"
#include "GraphicsAttorney.h"

#include <d3d11.h>
#include "d3dUtil.h"

Sampler::Sampler()
{
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.MaxAnisotropy = 4;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	HRESULT hr = GraphicsAttorney::Device::GetDevice()->CreateSamplerState(&sampDesc, &mpSampler);
	assert(SUCCEEDED(hr));
}

Sampler::Sampler(const D3D11_SAMPLER_DESC& desc)
{
	HRESULT hr = GraphicsAttorney::Device::GetDevice()->CreateSamplerState(&desc, &mpSampler);
	assert(SUCCEEDED(hr));
}

Sampler::Sampler(D3D11_FILTER filter, UINT isotropic_level, D3D11_TEXTURE_ADDRESS_MODE address_mode)
{
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = filter;
	sampDesc.MaxAnisotropy = isotropic_level;
	sampDesc.AddressU = address_mode;
	sampDesc.AddressV = address_mode;
	sampDesc.AddressW = address_mode;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	HRESULT hr = GraphicsAttorney::Device::GetDevice()->CreateSamplerState(&sampDesc, &mpSampler);
	assert(SUCCEEDED(hr));
}

void Sampler::SetToContext(ID3D11DeviceContext* devcon, int sampSlot)
{
	devcon->PSSetSamplers(sampSlot, 1, &mpSampler);
}

Sampler::~Sampler()
{
	ReleaseAndDeleteCOMobject(mpSampler);
}
