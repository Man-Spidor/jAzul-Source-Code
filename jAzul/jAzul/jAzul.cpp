#include "jAzul.h"

#include "d3dUtil.h"

#include "ShaderContextManager.h"
#include "DrawManager.h"
#include "GraphicsAttorney.h"

jAzul::jAzul() :
	BackgroundColor(Vect(61.0f / 255.0f, 68.0f / 255.0f, 86.f / 255.0f)),
	md3dDevice(nullptr),
	md3dImmediateContext(nullptr),
	mSwapChain(nullptr),
	mRenderTargetView(nullptr),
	mpDepthStencilView(nullptr),
	mSolidRasterizerState(nullptr),
	mWireFrameRasterizerState(nullptr),
	currCam(nullptr),
	currCam2D(nullptr),
	width(0),
	height(0),
	SyncInterval(0)         // 1 for sync to monitor refresh rate, 0 for no sync
{

}

jAzul::~jAzul()
{
	GraphicsAttorney::Shader::Shutdown();
	GraphicsAttorney::Draw::Shutdown();

	ReleaseAndDeleteCOMobject(mSolidRasterizerState);
	ReleaseAndDeleteCOMobject(mWireFrameRasterizerState);

	ReleaseAndDeleteCOMobject(mRenderTargetView);
	ReleaseAndDeleteCOMobject(mpDepthStencilView);
	ReleaseAndDeleteCOMobject(mSwapChain);
	ReleaseAndDeleteCOMobject(md3dImmediateContext);

	// Must be done BEFORE the device is released
	ReportLiveDXObjects();		// See http://masterkenth.com/directx-leak-debugging/

	ReleaseAndDeleteCOMobject(md3dDevice);
}

bool jAzul::Initialize(HWND hwnd, int _width, int _height)
{
	if (!InitializeDirectX(hwnd, _width, _height))
		return false;

	this->width = _width;
	this->height = _height;

	GraphicsAttorney::Device::SetDevice(this->md3dDevice);
	GraphicsAttorney::Shader::InitAllShaders(this->md3dImmediateContext);
	GraphicsAttorney::Shader::SendScreenSize(this->width, this->height);

	return true;
}

bool jAzul::InitializeDirectX(HWND hwnd, int _width, int _height)
{
	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// This is a *greatly* simplified process to create a DX device and context:
	// We force the use of DX11 feature level since that's what CDM labs are limited to.
	// For real-life applications would need to test what's the best feature level and act accordingly
	hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, nullptr, 0, D3D11_SDK_VERSION, &md3dDevice, nullptr, &md3dImmediateContext);
	assert(SUCCEEDED(hr));

	// Now we obtain the associated DXGIfactory1 with our device 
	// Many steps...
	IDXGIDevice* dxgiDevice = nullptr;
	hr = md3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
	assert(SUCCEEDED(hr));

	IDXGIAdapter* adapter = nullptr;
	hr = dxgiDevice->GetAdapter(&adapter);
	assert(SUCCEEDED(hr));

	IDXGIFactory1* dxgiFactory1 = nullptr;
	hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory1));
	assert(SUCCEEDED(hr));
	// See also note on weird stuff with factories and swap chains (1s and 2s)
	// https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

	// We are done with these now...
	ReleaseAndDeleteCOMobject(adapter);
	ReleaseAndDeleteCOMobject(dxgiDevice);

	// Controls MSAA option:
	// - 4x count level garanteed for all DX11 
	// - MUST be the same for depth buffer!
	// - We _need_ to work with the depth buffer because reasons... (see below)
	DXGI_SAMPLE_DESC sampDesc;
	sampDesc.Count = 1;
	sampDesc.Quality = static_cast<UINT>(D3D11_CENTER_MULTISAMPLE_PATTERN);  // MS: what's with the type mismtach?

	DXGI_MODE_DESC buffdesc;				// https://msdn.microsoft.com/en-us/library/windows/desktop/bb173064(v=vs.85).aspx
	ZeroMemory(&buffdesc, sizeof(buffdesc));
	buffdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	buffdesc.Width = _width;
	buffdesc.Height = _height;

	// Next we create a swap chain. 
	// Useful thread: http://stackoverflow.com/questions/27270504/directx-creating-the-swapchain
	// Note that this is for a DirectX 11.0: in a real app, we should test the feature levels and act accordingly

	DXGI_SWAP_CHAIN_DESC sd;				// See MSDN: https://msdn.microsoft.com/en-us/library/windows/desktop/bb173075(v=vs.85).aspx
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;						// Much confusion about this number... see http://www.gamedev.net/topic/633807-swap-chain-buffer-count/
	sd.BufferDesc = buffdesc;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hwnd;
	sd.SampleDesc = sampDesc;
	sd.Windowed = TRUE;

	hr = dxgiFactory1->CreateSwapChain(md3dDevice, &sd, &mSwapChain);
	assert(SUCCEEDED(hr));
	ReleaseAndDeleteCOMobject(dxgiFactory1);

	// Create a render target view		https://msdn.microsoft.com/en-us/library/windows/desktop/ff476582(v=vs.85).aspx
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	assert(SUCCEEDED(hr));;

	hr = md3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &mRenderTargetView);
	ReleaseAndDeleteCOMobject(pBackBuffer);
	assert(SUCCEEDED(hr));

	/**********************************************************/

	// First we fix what it means for triangles to be front facing.
	// Requires setting a whole new rasterizer state
	//*
	D3D11_RASTERIZER_DESC rd;
	rd.FillMode = D3D11_FILL_SOLID;  // Also: D3D11_FILL_WIREFRAME
	rd.CullMode = D3D11_CULL_BACK;
	rd.FrontCounterClockwise = true; // true for RH forward facing
	rd.DepthBias = 0;
	rd.SlopeScaledDepthBias = 0.0f;
	rd.DepthBiasClamp = 0.0f;
	rd.DepthClipEnable = true;
	rd.ScissorEnable = false;
	rd.MultisampleEnable = true;  // Does not in fact turn on/off multisample: https://msdn.microsoft.com/en-us/library/windows/desktop/ff476198(v=vs.85).aspx
	rd.AntialiasedLineEnable = true;

	md3dDevice->CreateRasterizerState(&rd, &this->mSolidRasterizerState);

	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_WIREFRAME;  // Also: D3D11_FILL_WIREFRAME
	rd.CullMode = D3D11_CULL_BACK;
	rd.FrontCounterClockwise = true; // true for RH forward facing
	rd.DepthBias = 0;
	rd.SlopeScaledDepthBias = 0.0f;
	rd.DepthBiasClamp = 0.0f;
	rd.DepthClipEnable = true;
	rd.ScissorEnable = false;
	rd.MultisampleEnable = true;  // Does not in fact turn on/off multisample: https://msdn.microsoft.com/en-us/library/windows/desktop/ff476198(v=vs.85).aspx
	rd.AntialiasedLineEnable = true;

	md3dDevice->CreateRasterizerState(&rd, &this->mWireFrameRasterizerState);
	
	this->EnableSolid();
	
	//*/

	// We must turn on the abilty to process depth during rendering.
	// Done through depth stencils (see https://msdn.microsoft.com/en-us/library/windows/desktop/bb205074(v=vs.85).aspx)
	// Below is a simplified version
	//*
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = _width;
	descDepth.Height = _height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc = sampDesc;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	ID3D11Texture2D* pDepthStencil;
	hr = md3dDevice->CreateTexture2D(&descDepth, NULL, &pDepthStencil);
	assert(SUCCEEDED(hr));

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	descDSV.Texture2D.MipSlice = 0;

	hr = md3dDevice->CreateDepthStencilView(pDepthStencil, &descDSV, &mpDepthStencilView);
	assert(SUCCEEDED(hr));
	ReleaseAndDeleteCOMobject(pDepthStencil);
	//*/

	/**********************************************************/

	// Enable Depth Stencil
	this->EnableDepthTest();
	
	ID3D11BlendState* d3dBlendState;
	D3D11_BLEND_DESC omDesc;

	ZeroMemory(&omDesc, sizeof(D3D11_BLEND_DESC));

	omDesc.RenderTarget[0].BlendEnable = true;
	omDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	omDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	omDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	omDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	omDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	omDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	omDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	if (FAILED(this->md3dDevice->CreateBlendState(&omDesc, &d3dBlendState)))
		return false;

	this->md3dImmediateContext->OMSetBlendState(d3dBlendState, 0, 0xffffffff);
	ReleaseAndDeleteCOMobject(d3dBlendState);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)_width;
	vp.Height = (FLOAT)_height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	md3dImmediateContext->RSSetViewports(1, &vp);

	return true;
}

void jAzul::ReportLiveDXObjects()
{
#ifdef _DEBUG
	HRESULT hr = S_OK;

	// Now we set up the Debug interface, to be queried on shutdown
	ID3D11Debug* debugDev;
	hr = md3dDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&debugDev));

	debugDev->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	ReleaseAndDeleteCOMobject(debugDev);
#endif
}

void jAzul::RenderFrame()
{
	if (this->currCam) {
		this->md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, VasA(BackgroundColor));
		this->md3dImmediateContext->ClearDepthStencilView(mpDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

		Vect eyePos;
		currCam->getPos(eyePos);

		GraphicsAttorney::Shader::SendLightParams(eyePos);
		GraphicsAttorney::Shader::SendCamMatrices(currCam->getViewMatrix(), currCam->getProjMatrix());
		GraphicsAttorney::Shader::Send2DCamMatrices(this->currCam2D->getViewMatrix(), this->currCam2D->getProjMatrix());
		
		this->EnableWireFrame();
		GraphicsAttorney::Draw::DrawWF();
		this->EnableSolid();

		GraphicsAttorney::Draw::Draw3D();

		this->DisableDepthTest();
		GraphicsAttorney::Draw::Draw2D();
		this->EnableDepthTest();

		// Switches the display to show the now-finished back-buffer
		mSwapChain->Present(SyncInterval, 0);
	}
}

void jAzul::EnableDepthTest()
{
	this->md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, this->mpDepthStencilView);  // to use without depth stencil
}

void jAzul::DisableDepthTest()
{
	this->md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, nullptr);  // to use without depth stencil
}

void jAzul::EnableSolid()
{
	this->md3dImmediateContext->RSSetState(this->mSolidRasterizerState);
}

void jAzul::EnableWireFrame()
{
	this->md3dImmediateContext->RSSetState(this->mWireFrameRasterizerState);
}

void jAzul::SetCurrCam(Camera* cam)
{
	this->currCam = cam;
}

void jAzul::SetCurrCam2D(Camera* cam)
{
	this->currCam2D = cam; 
}

void jAzul::SetWidth(const int _width)
{
	this->width = _width;
}

void jAzul::SetHeight(const int _height)
{
	this->height = _height;
}

const int jAzul::GetWidth() const
{
	return this->width;
}

const int jAzul::GetHeight() const
{
	return this->height;
}

void jAzul::SetBackgroundColor(const float R, const float G, const float B, const float A)
{
	this->BackgroundColor.X() = R;
	this->BackgroundColor.Y() = G;
	this->BackgroundColor.Z() = B;
	this->BackgroundColor.W() = A;
}

void jAzul::SetBackgroundColor(const Vect& color)
{
	this->BackgroundColor = color;
}

void jAzul::EnableASync()
{
	this->SyncInterval = 1;
}

void jAzul::DisableASync()
{
	this->SyncInterval = 0;
}
