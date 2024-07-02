#include "DrawTextureLightCmd.h"

#include "GraphicsAttorney.h"
#include "GraphicsObject_TextureLight.h"

DrawTextureLightCmd::DrawTextureLightCmd() :
	pGO(nullptr)
{
}

void DrawTextureLightCmd::SetGO(GraphicsObject_TextureLight* _pGO)
{
	this->pGO = _pGO;
}

void DrawTextureLightCmd::Execute()
{
	this->pGO->SetWorld(this->world);
	GraphicsAttorney::GraphicsObject::Draw(this->pGO);
}
