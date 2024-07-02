#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include "DrawCmdPool.h"
#include <vector>

class GraphicsObject_Base;
class GraphicsObject_Wireframe;
class GraphicsObject_Color;
class GraphicsObject_ColorLight;
class GraphicsObject_Texture;
class GraphicsObject_TextureLight;
class GraphicsObject_TextureAlpha;
class GraphicsObject_Sprite;

class DrawManager
{
	friend class GraphicsAttorney;
private:
	DrawManager() = default;
	DrawManager(const DrawManager& other) = delete;
	DrawManager& operator=(const DrawManager& other) = delete;
	DrawManager(DrawManager&& other) = delete;
	DrawManager& operator=(DrawManager&& other) = delete;
	~DrawManager() = default;

private:
	static void Shutdown();

	static void DrawWF();
	static void Draw3D();
	static void Draw2D();

	static void DrawGO(GraphicsObject_Wireframe* pGO);
	static void DrawGO(GraphicsObject_Color* pGO);
	static void DrawGO(GraphicsObject_ColorLight* pGO);
	static void DrawGO(GraphicsObject_Texture* pGO);
	static void DrawGO(GraphicsObject_TextureLight* pGO);
	static void DrawGO(GraphicsObject_TextureAlpha* pGO);
	static void DrawGO(GraphicsObject_Sprite* pGO);

private:
	void privDrawWF();
	void privDraw3D();
	void privDraw2D();

	static DrawManager& Instance();
	static DrawManager* instance;

	DrawCmdPool cmdPool;

	using DrawList = std::stack<DrawCommand*>;
	DrawList pColorList;
	DrawList pColorLightList;
	DrawList pTextureList;
	DrawList pTextureLightList;
	DrawList pTextureAlphaList;
	DrawList pSpriteList;
	DrawList pWFList;
};

#endif // DRAWMANAGER_H
