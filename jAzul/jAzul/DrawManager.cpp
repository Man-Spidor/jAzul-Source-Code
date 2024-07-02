#include "DrawManager.h"

#include "GraphicObject_Color.h"
#include "GraphicsObject_Sprite.h"
#include "GraphicsObject_Texture.h"
#include "GraphicsObject_Wireframe.h"
#include "GraphicObject_ColorLight.h"
#include "GraphicsObject_TextureLight.h"
#include "GraphicsObject_TextureAlpha.h"

#include "DrawColorCmd.h"
#include "DrawColorLightCmd.h"
#include "DrawTextureCmd.h"
#include "DrawTextureLightCmd.h"
#include "DrawAlphaCmd.h"
#include "DrawWFCmd.h"
#include "DrawSpriteCmd.h"

#include "GraphicsAttorney.h"

DrawManager* DrawManager::instance = nullptr;

void DrawManager::Shutdown()
{
	delete instance;
}

void DrawManager::DrawWF()
{
	Instance().privDrawWF();
}

void DrawManager::Draw3D()
{
	Instance().privDraw3D();
}

void DrawManager::Draw2D()
{
	Instance().privDraw2D();
}

void DrawManager::DrawGO(GraphicsObject_Wireframe* pGO)
{
	DrawWFCmd* pCmd = Instance().cmdPool.GetWFCmd();

	pCmd->SetWorld(pGO->GetWorld());
	pCmd->SetGO(pGO);

	Instance().pWFList.push(pCmd);
}

void DrawManager::DrawGO(GraphicsObject_Color* pGO)
{
	DrawColorCmd* pCmd = Instance().cmdPool.GetColorCmd();

	pCmd->SetWorld(pGO->GetWorld());
	pCmd->SetGO(pGO);

	Instance().pColorList.push(pCmd);
}

void DrawManager::DrawGO(GraphicsObject_ColorLight* pGO)
{
	DrawColorLightCmd* pCmd = Instance().cmdPool.GetColorLightCmd();

	pCmd->SetWorld(pGO->GetWorld());
	pCmd->SetGO(pGO);

	Instance().pColorLightList.push(pCmd);
}

void DrawManager::DrawGO(GraphicsObject_Texture* pGO)
{
	DrawTextureCmd* pCmd = Instance().cmdPool.GetTextureCmd();

	pCmd->SetWorld(pGO->GetWorld());
	pCmd->SetGO(pGO);

	Instance().pTextureList.push(pCmd);
}

void DrawManager::DrawGO(GraphicsObject_TextureLight* pGO)
{
	DrawTextureLightCmd* pCmd = Instance().cmdPool.GetTextureLightCmd();

	pCmd->SetWorld(pGO->GetWorld());
	pCmd->SetGO(pGO);

	Instance().pTextureLightList.push(pCmd);
}

void DrawManager::DrawGO(GraphicsObject_TextureAlpha* pGO)
{
	DrawAlphaCmd* pCmd = Instance().cmdPool.GetTextureAlphaCmd();

	pCmd->SetWorld(pGO->GetWorld());
	pCmd->SetGO(pGO);

	Instance().pTextureAlphaList.push(pCmd);
}

void DrawManager::DrawGO(GraphicsObject_Sprite* pGO)
{
	DrawSpriteCmd* pCmd = Instance().cmdPool.GetSpriteCmd();

	pCmd->SetWorld(pGO->GetWorld());
	pCmd->SetGO(pGO);

	Instance().pSpriteList.push(pCmd);
}

void DrawManager::privDrawWF()
{
	if (!this->pWFList.empty()) {
		GraphicsAttorney::Shader::SetColorToContext();
		while (!this->pWFList.empty()) {
			this->pWFList.top()->Execute();
			this->cmdPool.ReturnCmd((DrawWFCmd*) this->pWFList.top());
			this->pWFList.pop();
		}
	}
}

void DrawManager::privDraw3D()
{
	if (!this->pColorList.empty()) {
		GraphicsAttorney::Shader::SetColorToContext();
		while (!this->pColorList.empty()) {
			this->pColorList.top()->Execute();
			this->cmdPool.ReturnCmd((DrawColorCmd*)this->pColorList.top());
			this->pColorList.pop();
		}
	}

	if (!this->pColorLightList.empty()) {
		GraphicsAttorney::Shader::SetColorLightToContext();
		while (!this->pColorLightList.empty()) {
			this->pColorLightList.top()->Execute();
			this->cmdPool.ReturnCmd((DrawColorLightCmd*)this->pColorLightList.top());
			this->pColorLightList.pop();
		}
	}

	if (!this->pTextureList.empty()) {
		GraphicsAttorney::Shader::SetTextureToContext();
		while (!this->pTextureList.empty()) {
			this->pTextureList.top()->Execute();
			this->cmdPool.ReturnCmd((DrawTextureCmd*)this->pTextureList.top());
			this->pTextureList.pop();
		}
	}

	if (!this->pTextureLightList.empty() || !this->pTextureAlphaList.empty()) {
		GraphicsAttorney::Shader::SetTextureLightToContext();
		while (!this->pTextureLightList.empty()) {
			this->pTextureLightList.top()->Execute();
			this->cmdPool.ReturnCmd((DrawTextureLightCmd*)this->pTextureLightList.top());
			this->pTextureLightList.pop();
		}

		while (!this->pTextureAlphaList.empty()) {
			this->pTextureAlphaList.top()->Execute();
			this->cmdPool.ReturnCmd((DrawAlphaCmd*)this->pTextureAlphaList.top());
			this->pTextureAlphaList.pop();
		}
	}
}

void DrawManager::privDraw2D()
{
	if (!this->pSpriteList.empty()) {
		GraphicsAttorney::Shader::SetSpriteToContext();
		while (!this->pSpriteList.empty()) {
			this->pSpriteList.top()->Execute();
			this->cmdPool.ReturnCmd((DrawSpriteCmd*)this->pSpriteList.top());
			this->pSpriteList.pop();
		}
	}
}

DrawManager& DrawManager::Instance()
{
	if (!instance)
		instance = new DrawManager();

	return *instance;
}
