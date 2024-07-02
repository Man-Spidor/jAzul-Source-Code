#include "ShaderTexture.h"
#include "d3dUtil.h"
#include "FogParamData.h"

ShaderTexture::ShaderTexture(ID3D11Device* device)
	: ShaderBase(device, L"../Assets/Shaders/Texture.hlsl")
{
	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);
	this->CreateInputLayout(layout, numElements);

	HRESULT hr;

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

	// Color buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_World);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBuffWorld);
	assert(SUCCEEDED(hr));

	// fog param
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(FogData);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBuffFog);
	assert(SUCCEEDED(hr));
}

ShaderTexture::~ShaderTexture()
{
	ReleaseAndDeleteCOMobject(mpBuffWorld);
	ReleaseAndDeleteCOMobject(mpBufferCamMatrices);
	ReleaseAndDeleteCOMobject(mpBuffFog);
}

void ShaderTexture::SetToContext(ID3D11DeviceContext* devcon)
{	
	ShaderBase::SaveContextPtr(devcon);
	ShaderBase::SetToContext_VS_PS_InputLayout();

	devcon->VSSetConstantBuffers(0, 1, &mpBufferCamMatrices);
	devcon->VSSetConstantBuffers(1, 1, &mpBuffWorld);
	devcon->VSSetConstantBuffers(2, 1, &mpBuffFog);

	devcon->PSSetConstantBuffers(0, 1, &mpBufferCamMatrices);
	devcon->PSSetConstantBuffers(1, 1, &mpBuffWorld);
	devcon->PSSetConstantBuffers(2, 1, &mpBuffFog);
}

void ShaderTexture::SendCamMatrices(const Matrix& view, const Matrix& proj)
{
	CamMatrices	mCamMatrices;
	mCamMatrices.eyePos = this->eyePos;
	mCamMatrices.View = view;
	mCamMatrices.Projection = proj;

	this->GetContext()->UpdateSubresource(mpBufferCamMatrices, 0, nullptr, &mCamMatrices, 0, 0);
}

void ShaderTexture::SendWorld(const Matrix& world)
{
	Data_World w;
	w.World = world;
	w.WorldInv = world.getInv();

	this->GetContext()->UpdateSubresource(mpBuffWorld, 0, nullptr, &w, 0, 0);
}

void ShaderTexture::SendFogData()
{
	this->GetContext()->UpdateSubresource(mpBuffFog, 0, nullptr, &this->fogData, 0, 0);
}

void ShaderTexture::SetFogData(const float FogStart, const float FogRange, const Vect& FogColor)
{
	fogData.FogStart = FogStart;
	fogData.FogRange = FogRange;
	fogData.FogColor = FogColor;
	this->GetContext()->UpdateSubresource(mpBuffFog, 0, nullptr, &this->fogData, 0, 0);
}

void ShaderTexture::SetEyePos(const Vect& _eyePos)
{
	this->eyePos = _eyePos;
}

void ShaderTexture::SetFogScale(const float scale)
{
	fogData.FogStart /= scale;
	fogData.FogRange /= scale;
	this->GetContext()->UpdateSubresource(mpBuffFog, 0, nullptr, &this->fogData, 0, 0);
}
