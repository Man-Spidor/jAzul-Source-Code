#ifndef GRAPHICSATTORNEY_H
#define GRAPHICSATTORNEY_H

#include "DrawManager.h"
#include "DeviceManager.h"
#include "GraphicObject_Base.h"
#include "ShaderContextManager.h"

class GraphicsAttorney
{
	friend class ShaderContextManager;
	friend class SamplerManager;
	friend class jAzul;
	friend class Model;
	friend class FlatPlane;
	friend class TerrainModel;
	friend class SkyBox;
	friend class Texture;
	friend class Sampler;

	friend class GraphicsObject_Wireframe;
	friend class GraphicsObject_Color;
	friend class GraphicsObject_ColorLight;
	friend class GraphicsObject_Texture;
	friend class GraphicsObject_TextureLight;
	friend class GraphicsObject_TextureAlpha;
	friend class GraphicsObject_Sprite;

	friend class DrawManager;

	class Device
	{
		friend class ShaderContextManager;
		friend class SamplerManager;
		friend class jAzul;
		friend class Model;
		friend class FlatPlane;
		friend class SkyBox;
		friend class TerrainModel;
		friend class Texture;
		friend class Sampler;

		static void SetDevice(ID3D11Device* _md3dDevice) { DeviceManager::SetDevice(_md3dDevice); };
		static ID3D11Device* GetDevice() { return DeviceManager::GetDevice(); };
	};

	friend class DrawColorCmd;
	friend class DrawColorLightCmd;
	friend class DrawTextureCmd;
	friend class DrawTextureLightCmd;
	friend class DrawAlphaCmd;
	friend class DrawWFCmd;
	friend class DrawSpriteCmd;

	class GraphicsObject
	{
		friend class DrawAlphaCmd;
		friend class DrawWFCmd;
		friend class DrawSpriteCmd;
		friend class DrawColorCmd;
		friend class DrawColorLightCmd;
		friend class DrawTextureCmd;
		friend class DrawTextureLightCmd;
		static void Draw(GraphicsObject_Base* pGO) { pGO->Draw(); };
	};

	class Shader
	{
		friend class jAzul;
		
		friend class DrawManager;

		friend class GraphicsObject_Wireframe;
		friend class GraphicsObject_Color;
		friend class GraphicsObject_ColorLight;
		friend class GraphicsObject_Texture;
		friend class GraphicsObject_TextureLight;
		friend class GraphicsObject_TextureAlpha;
		friend class GraphicsObject_Sprite;

		static void InitAllShaders(ID3D11DeviceContext*& context) { ShaderContextManager::InitAllShaders(context); };
		static void Shutdown() { ShaderContextManager::Shutdown(); };

		static void UpdateContext(ID3D11DeviceContext*& context) { ShaderContextManager::UpdateContext(context); };
		static ID3D11DeviceContext*& GetContext() { return ShaderContextManager::GetContext(); };

		static void SendCamMatrices(const Matrix& view, const Matrix& proj) { ShaderContextManager::SendCamMatrices(view, proj); };
		static void Send2DCamMatrices(const Matrix& view, const Matrix& proj) { ShaderContextManager::Send2DCamMatrices(view, proj); };
		static void SendLightParams(const Vect& eyePos) { ShaderContextManager::SendLightParams(eyePos); };
		static void SendScreenSize(const unsigned int width, const unsigned int height) { ShaderContextManager::SendScreenSize(width, height); };

		static void SendColorParams(const Matrix& world, const Vect& col, const float scale = 1.0f) { ShaderContextManager::SendColorParams(world, col, scale); };
		static void SendColorLightParams(const Matrix& world, const Vect& amb = Vect(.5f, .5f, .5f), const Vect& dif = Vect(.5f, .5f, .5f), const Vect& sp = Vect(.5f, .5f, .5f), const float scale = 1.0f) { ShaderContextManager::SendColorLightParams(world, amb, dif, sp, scale); };
		static void SendTextureParams(const Matrix& world, const float scale = 1.0f) { ShaderContextManager::SendTextureParams(world, scale); };
		static void SendTextureLightParams(const Matrix& world, const Vect& amb = Vect(.5f, .5f, .5f), const Vect& dif = Vect(.5f, .5f, .5f), const Vect& sp = Vect(.5f, .5f, .5f), const float scale = 1.0f) { ShaderContextManager::SendTextureLightParams(world, amb, dif, sp, scale); };
		static void SendSpriteParams(const Matrix& pos, float texWidth, float texHeight, const jAzulRect& pImgRect) { ShaderContextManager::SendSpriteParams(pos, texWidth, texHeight, pImgRect); };

		static void SetColorToContext() { ShaderContextManager::SetColorToContext(); };
		static void SetColorLightToContext() { ShaderContextManager::SetColorLightToContext(); };
		static void SetTextureToContext() { ShaderContextManager::SetTextureToContext(); };
		static void SetTextureLightToContext() { ShaderContextManager::SetTextureLightToContext(); };
		static void SetSpriteToContext() { ShaderContextManager::SetSpriteToContext(); };
	};

	class Draw
	{
		friend class jAzul;
		friend class GraphicsObject_Wireframe;
		friend class GraphicsObject_Color;
		friend class GraphicsObject_ColorLight;
		friend class GraphicsObject_Texture;
		friend class GraphicsObject_TextureLight;
		friend class GraphicsObject_TextureAlpha;
		friend class GraphicsObject_Sprite;

		static void Shutdown() { DrawManager::Shutdown(); };

		static void DrawWF() { DrawManager::DrawWF(); };
		static void Draw3D() { DrawManager::Draw3D(); };
		static void Draw2D() { DrawManager::Draw2D(); };

		static void DrawGO(GraphicsObject_Wireframe* pGO) { DrawManager::DrawGO(pGO); };
		static void DrawGO(GraphicsObject_Color* pGO) { DrawManager::DrawGO(pGO); };
		static void DrawGO(GraphicsObject_ColorLight* pGO) { DrawManager::DrawGO(pGO); };
		static void DrawGO(GraphicsObject_Texture* pGO) { DrawManager::DrawGO(pGO); };
		static void DrawGO(GraphicsObject_TextureLight* pGO) { DrawManager::DrawGO(pGO); };
		static void DrawGO(GraphicsObject_TextureAlpha* pGO) { DrawManager::DrawGO(pGO); };
		static void DrawGO(GraphicsObject_Sprite* pGO) { DrawManager::DrawGO(pGO); };
	};
};

#endif // GRAPHICSATTORNEY_H
