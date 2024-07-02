#include "DrawTextureCmd.h"

#include "GraphicsObject_Texture.h"
#include "GraphicsAttorney.h"

DrawTextureCmd::DrawTextureCmd() :
	pGO(nullptr)
{
}

void DrawTextureCmd::SetGO(GraphicsObject_Texture* _pGO)
{
	this->pGO = _pGO;
}

void DrawTextureCmd::Execute()
{
	this->pGO->SetWorld(this->world);
	GraphicsAttorney::GraphicsObject::Draw(this->pGO);
}
