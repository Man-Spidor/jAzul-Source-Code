#ifndef SAMPLERMANAGER_H
#define SAMPLERMANAGER_H

#include <map>
#include <d3d11.h>

class SamplerManager
{
public:
	SamplerManager();
	SamplerManager(const SamplerManager& other) = default;
	SamplerManager& operator=(const SamplerManager& other) = default;
	SamplerManager(SamplerManager&& other) = default;
	SamplerManager& operator=(SamplerManager&& other) = default;
	~SamplerManager();

	static void Initialize();
	static void Terminate();

	// static void Load(const char const * Key, const D3D11_SAMPLER_DESC& samplerDesc);
	// static void Load(const char const* Key, D3D11_FILTER filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR, UINT isotropic_level = 4, D3D11_TEXTURE_ADDRESS_MODE = D3D11_TEXTURE_ADDRESS_WRAP);
	// 
	// static ID3D11SamplerState* SetSamplerToContext(const char const * Key);
	// static ID3D11SamplerState* SetDefaultToContext();

private:
	static SamplerManager* instance;
	static SamplerManager& Instance();

	using SamplerMap = std::map<const char* const, ID3D11SamplerState*>;
	SamplerMap samplerMap;


	ID3D11SamplerState* defaultSampler;
	ID3D11Device* d3dDev;
};

#endif // SAMPLERMANAGER_H
