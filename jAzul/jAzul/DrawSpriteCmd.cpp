#include "DrawSpriteCmd.h"

#include "GraphicsAttorney.h"
#include "GraphicsObject_Sprite.h"

DrawSpriteCmd::DrawSpriteCmd() :
	pGO(nullptr)
{
}

void DrawSpriteCmd::SetGO(GraphicsObject_Sprite* _pGO)
{
	this->pGO = _pGO;
}

void DrawSpriteCmd::Execute()
{
	this->pGO->SetWorld(this->world);
	GraphicsAttorney::GraphicsObject::Draw(this->pGO);
}
