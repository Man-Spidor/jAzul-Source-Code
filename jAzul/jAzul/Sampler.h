#ifndef SAMPLER_H
#define SAMPLER_H

struct ID3D11SamplerState;
struct ID3D11DeviceContext;
struct D3D11_SAMPLER_DESC;

enum D3D11_FILTER;
enum D3D11_TEXTURE_ADDRESS_MODE;

class Sampler
{
public:
	Sampler();
	Sampler(const Sampler& other) = default;
	Sampler& operator=(const Sampler& other) = default;
	Sampler(Sampler&& other) = default;
	Sampler& operator=(Sampler&& other) = default;
	~Sampler();

	Sampler(const D3D11_SAMPLER_DESC& desc);
	Sampler(D3D11_FILTER filter, UINT isotropic_level, D3D11_TEXTURE_ADDRESS_MODE);

	void SetToContext(ID3D11DeviceContext* devcon, int sampSlot = 0);

private:
	ID3D11SamplerState* mpSampler;
};

#endif // SAMPLER_H
