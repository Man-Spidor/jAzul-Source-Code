#include "SamplerManager.h"
#include "GraphicsAttorney.h"
#include "d3dUtil.h"

SamplerManager* SamplerManager::instance = nullptr;

SamplerManager::SamplerManager() :
	samplerMap(),
	defaultSampler(nullptr),
	d3dDev(GraphicsAttorney::Device::GetDevice())
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
	HRESULT hr = d3dDev->CreateSamplerState(&sampDesc, &this->defaultSampler);
	assert(SUCCEEDED(hr));
}

SamplerManager::~SamplerManager()
{
	while (!this->samplerMap.empty()) {
		ReleaseAndDeleteCOMobject(this->samplerMap.begin()->second);
		this->samplerMap.erase(this->samplerMap.begin());
	}
}

void SamplerManager::Initialize()
{
	instance = new SamplerManager();
}

void SamplerManager::Terminate()
{
	delete instance;
}

//void SamplerManager::Load(const char const* Key, const D3D11_SAMPLER_DESC& samplerDesc)
//{
//	UNREFERENCED_PARAMETER()
//	// this->samplerMap[Key];
//	// HRESULT hr = this->d3dDev->CreateSamplerState(&samplerDesc, &);
//	// assert(SUCCEEDED(hr));
//}
//
//void SamplerManager::Load(const char const* Key, D3D11_FILTER filter, UINT isotropic_level, D3D11_TEXTURE_ADDRESS_MODE)
//{
//}

SamplerManager& SamplerManager::Instance()
{
	assert(instance);

	return *instance;
}
