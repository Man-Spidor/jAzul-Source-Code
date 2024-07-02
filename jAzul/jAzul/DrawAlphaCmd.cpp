#include "DrawAlphaCmd.h"

#include "GraphicsAttorney.h"
#include "GraphicsObject_TextureAlpha.h"

DrawAlphaCmd::DrawAlphaCmd() :
	pGO(nullptr)
{
}

void DrawAlphaCmd::SetGO(GraphicsObject_TextureAlpha* _pGO)
{
	this->pGO = _pGO;
}

void DrawAlphaCmd::Execute()
{
	this->pGO->SetWorld(this->world);
	GraphicsAttorney::GraphicsObject::Draw(this->pGO);
}
