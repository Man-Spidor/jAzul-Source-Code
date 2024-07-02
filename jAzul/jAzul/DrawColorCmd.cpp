#include "DrawColorCmd.h"

#include "GraphicsAttorney.h"
#include "GraphicObject_Color.h"

DrawColorCmd::DrawColorCmd() :
	pGO(nullptr)
{
}

void DrawColorCmd::SetGO(GraphicsObject_Color* _pGO)
{
	this->pGO = _pGO;
}

void DrawColorCmd::Execute()
{
	this->pGO->SetWorld(this->world);
	GraphicsAttorney::GraphicsObject::Draw(this->pGO);
}
