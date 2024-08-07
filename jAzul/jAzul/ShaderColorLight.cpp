#include "ShaderColorLight.h"
#include "d3dUtil.h"
#include <d3d11.h>
#include <assert.h>
#include "FogParamData.h"

ShaderColorLight::ShaderColorLight(ID3D11Device* dev)
	: ShaderBase(dev, L"../Assets/Shaders/ColorLight.hlsl")
{
	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);
	this->CreateInputLayout(layout, numElements);

	HRESULT hr = S_OK;

	// View Projection buffer
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CamMatrices);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBufferCamMatrices);
	assert(SUCCEEDED(hr));

	// light param
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_LightParams);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBufferLightParams);
	assert(SUCCEEDED(hr));
	
	// Color buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_WorldAndMaterial);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBuffWordAndMaterial);
	assert(SUCCEEDED(hr));

	// fog param
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(FogData);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBufferFogParams);
	assert(SUCCEEDED(hr));

	// Zeroing the light data
	ZeroMemory(&FogParamData, sizeof(FogData));
	ZeroMemory(&DirLightData, sizeof(DirLightData));
	ZeroMemory(&PointLightData, sizeof(PointLightData));
	ZeroMemory(&SpotLightData, sizeof(SpotLightData));
}

ShaderColorLight::~ShaderColorLight()
{
	ReleaseAndDeleteCOMobject(mpBuffWordAndMaterial);
	ReleaseAndDeleteCOMobject(mpBufferLightParams);
	ReleaseAndDeleteCOMobject(mpBufferCamMatrices);
	ReleaseAndDeleteCOMobject(mpBufferFogParams);
}

void ShaderColorLight::SendCamMatrices(const Matrix& view, const Matrix& proj)
{
	CamMatrices	mCamMatrices;
	mCamMatrices.View = view;
	mCamMatrices.Projection = proj;

	this->GetContext()->UpdateSubresource(mpBufferCamMatrices, 0, nullptr, &mCamMatrices, 0, 0);
}

void ShaderColorLight::SetDirectionalLightParameters(LIGHTNUM ln, const Vect& dir, const Vect& amb, const Vect& dif, const Vect& sp)
{
	DirLightData[(unsigned int)ln].Light.Ambient = amb;
	DirLightData[(unsigned int)ln].Light.Diffuse = dif;
	DirLightData[(unsigned int)ln].Light.Specular = sp;
	DirLightData[(unsigned int)ln].Direction = dir;
}

void ShaderColorLight::SetPointLightParameters(LIGHTNUM ln, const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp)
{
	PointLightData[(unsigned int)ln].Light.Ambient = amb;
	PointLightData[(unsigned int)ln].Light.Diffuse = dif;
	PointLightData[(unsigned int)ln].Light.Specular = sp;
	PointLightData[(unsigned int)ln].Position = pos;
	PointLightData[(unsigned int)ln].Attenuation = att;
	PointLightData[(unsigned int)ln].Range = r;
}

void ShaderColorLight::SetSpotLightParameters(LIGHTNUM ln, const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp)
{
	SpotLightData[(unsigned int)ln].Light.Ambient = amb;
	SpotLightData[(unsigned int)ln].Light.Diffuse = dif;
	SpotLightData[(unsigned int)ln].Light.Specular = sp;
	SpotLightData[(unsigned int)ln].Position = pos;
	SpotLightData[(unsigned int)ln].Direction = dir;
	SpotLightData[(unsigned int)ln].Attenuation = att;
	SpotLightData[(unsigned int)ln].Range = r;
	SpotLightData[(unsigned int)ln].SpotExp = spotExp;
}

void ShaderColorLight::SendLightParameters( const Vect& eyepos)
{
	Data_LightParams dl;
	for (unsigned int i = 0; i < MAX_DIR_LIGHTS; i++) {
		dl.DirLight[i] = DirLightData[i];
	}

	for (unsigned int i = 0; i < MAX_POINT_LIGHTS; i++) {
		dl.PntLight[i] = PointLightData[i];
	}
	for (unsigned int i = 0; i < MAX_SPOT_LIGHTS; i++) {
		dl.SptLight[i] = SpotLightData[i];
	}

	dl.EyePosWorld = eyepos;

	this->GetContext()->UpdateSubresource(mpBufferLightParams, 0, nullptr, &dl, 0, 0);
}

void ShaderColorLight::SetFogData(const float FogStart, const float FogRange, const Vect& FogColor)
{
	this->FogParamData.FogStart = FogStart;
	this->FogParamData.FogRange = FogRange;
	this->FogParamData.FogColor = FogColor;
}

void ShaderColorLight::SetFogScale(const float scale)
{
	this->FogParamData.FogStart /= scale;
	this->FogParamData.FogRange /= scale;
}

void ShaderColorLight::SendWorldAndMaterial(const Matrix& world, const Vect& amb, const Vect& dif, const Vect& sp, const float scale)
{
	Data_WorldAndMaterial wm;
	wm.World = world;
	wm.WorldInv = world.getInv();
	wm.Mat.lightData.Ambient = amb;
	wm.Mat.lightData.Diffuse = dif;
	wm.Mat.lightData.Specular = sp;
	wm.Mat.scale = scale;

	this->GetContext()->UpdateSubresource(mpBuffWordAndMaterial, 0, nullptr, &wm, 0, 0);
}

void ShaderColorLight::SendFogData()
{
	this->GetContext()->UpdateSubresource(mpBufferFogParams, 0, nullptr, &FogParamData, 0, 0);
}

void ShaderColorLight::SetToContext(ID3D11DeviceContext* devcon)
{
	ShaderBase::SaveContextPtr(devcon);
	ShaderBase::SetToContext_VS_PS_InputLayout();

	devcon->VSSetConstantBuffers(0, 1, &mpBufferCamMatrices);
	devcon->VSSetConstantBuffers(1, 1, &mpBufferLightParams);
	devcon->VSSetConstantBuffers(2, 1, &mpBuffWordAndMaterial);
	devcon->VSSetConstantBuffers(3, 1, &mpBufferFogParams);

	devcon->PSSetConstantBuffers(0, 1, &mpBufferCamMatrices);
	devcon->PSSetConstantBuffers(1, 1, &mpBufferLightParams);
	devcon->PSSetConstantBuffers(2, 1, &mpBuffWordAndMaterial);
	devcon->PSSetConstantBuffers(3, 1, &mpBufferFogParams);
}