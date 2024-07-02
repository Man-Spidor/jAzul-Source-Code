// DXApp
// Andre Berthiaume, June 2016
// Note: DX 11 SDK https://www.microsoft.com/en-us/download/details.aspx?id=6812
// Note on weird stuff with swap chain (1s and 2s) https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

#ifndef _DXApp
#define _DXApp

#include <d3d11.h>
#include "d3dUtil.h"
#include "GameTimer.h"
#include <string>

#include "Vect.h"
#include "Matrix.h"
#include "Camera.h"

class Demo;

class DXApp : public Align16
{
private:
	DXApp() = delete;
	DXApp(const DXApp& other) = delete;
	DXApp& operator=(const DXApp& other) = delete;
	DXApp(DXApp&& other) = delete;
	DXApp& operator=(DXApp&& other) = delete;

	// Main window handle
	HWND      mhMainWnd;

	Vect BackgroundColor;
	int SyncInterval = 0;  // 1 for sync to monitor refresh rate, 0 for no sync

	// DX application elements
	ID3D11Device* md3dDevice;					// Connects to the graphics card
	ID3D11DeviceContext* md3dImmediateContext;	// Settings for the GPU to use
	IDXGISwapChain* mSwapChain;					// image buffers used for rendering
	ID3D11RenderTargetView* mRenderTargetView;	// Where to send rendring operations (typically: points to one of the swap buffers)
	ID3D11DepthStencilView* mpDepthStencilView; // Needed to force depth-buffer operations

	GameTimer mTimer;
	std::string mMainWndCaption;
	int mClientWidth;
	int mClientHeight;

public:
	static void InitDirect3D();
	static void InitDemo();

private:
	void UpdateScene();
	void DrawScene();
	void CalculateFrameStats();

	// Debug utility
	void ReportLiveDXObjects();

	DXApp(HWND hwnd);
	virtual ~DXApp();

public:
	static void InitDXApp(HWND hwnd);
	static void ShutdownDXApp();

	static void SetCurrCam(Camera* cam);

	static ID3D11Device* getDevice();
	static ID3D11DeviceContext* getContext();

	static float GetWidth();
	static float GetHeight();

	static void FrameTick();

	// overrides for handling mouse input.
	static void OnMouseDown(WPARAM btnState, int xval, int yval);
	static void OnMouseUp(WPARAM btnState, int xval, int yval);
	static void OnMouseMove(WPARAM btnState, int xval, int yval);
	static void OnMouseWheel(short delta);

private:
	static DXApp& Instance();
	static DXApp* instance;

	void privInitDirect3D();
	void privInitDemo();

	Camera* currCam;
	Demo* pDemo;
};

#endif _DXApp