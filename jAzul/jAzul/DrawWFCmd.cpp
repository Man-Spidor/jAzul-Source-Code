#include "DrawWFCmd.h"

#include "GraphicsObject_Wireframe.h"
#include "GraphicsAttorney.h"

DrawWFCmd::DrawWFCmd() :
	color(),
	pGO(nullptr)
{
}

void DrawWFCmd::SetGO(GraphicsObject_Wireframe* _pGO)
{
	this->pGO = _pGO;
	this->color = this->pGO->GetColor();
}

void DrawWFCmd::Execute()
{
	this->pGO->SetWorld(this->world);
	this->pGO->SetColor(this->color);
	GraphicsAttorney::GraphicsObject::Draw(this->pGO);
}
