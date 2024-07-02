#include "ShaderSprite.h"

#include "jAzulRect.h"

#include <d3d11.h>
#include "d3dUtil.h"

ShaderSprite::~ShaderSprite()
{
	ReleaseAndDeleteCOMobject(mpBuffWorld);
	ReleaseAndDeleteCOMobject(mpBufferCamMatrices);
}

ShaderSprite::ShaderSprite(ID3D11Device* device)
	: ShaderBase(device, L"../Assets/Shaders/Sprite.hlsl")
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

	// World buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_World);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBuffWorld);
	assert(SUCCEEDED(hr));
}

void ShaderSprite::SetToContext(ID3D11DeviceContext* devcon)
{
	ShaderBase::SaveContextPtr(devcon);
	ShaderBase::SetToContext_VS_PS_InputLayout();

	devcon->VSSetConstantBuffers(0, 1, &mpBufferCamMatrices);
	devcon->VSSetConstantBuffers(1, 1, &mpBuffWorld);

	devcon->PSSetConstantBuffers(0, 1, &mpBufferCamMatrices);
	devcon->PSSetConstantBuffers(1, 1, &mpBuffWorld);
}

void ShaderSprite::SetScreenSize(const unsigned int width, const unsigned int height)
{
	this->ScreenOffset = Matrix(TRANS, Vect(-0.5f * static_cast<float>(width), 0.5f * static_cast<float>(height), 0.0f, 1.0f));
}

void ShaderSprite::SendCamMatrices(const Matrix& view, const Matrix& proj)
{
	CamMatrices	mCamMatrices;
	mCamMatrices.View = view;
	mCamMatrices.Projection = proj;

	this->GetContext()->UpdateSubresource(mpBufferCamMatrices, 0, nullptr, &mCamMatrices, 0, 0);
}

void ShaderSprite::SendWorld(const Matrix& Pos, float texWidth, float texHeight, const jAzulRect& imgRect)
{
	Data_World w;
	w.World = Pos * this->ScreenOffset;

	w.texW = texWidth;
	w.texH = texHeight;

	w.imgW = imgRect.w;
	w.imgH = imgRect.h;
	w.imgX = imgRect.x;
	w.imgY = imgRect.y;		

	this->GetContext()->UpdateSubresource(mpBuffWorld, 0, nullptr, &w, 0, 0);
}
