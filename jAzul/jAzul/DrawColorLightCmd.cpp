#include "DrawColorLightCmd.h"

#include "GraphicsAttorney.h"
#include "GraphicObject_ColorLight.h"

DrawColorLightCmd::DrawColorLightCmd() :
	pGO(nullptr)
{
}

void DrawColorLightCmd::SetGO(GraphicsObject_ColorLight* _pGO)
{
	this->pGO = _pGO;
}

void DrawColorLightCmd::Execute()
{
	this->pGO->SetWorld(this->world);
	GraphicsAttorney::GraphicsObject::Draw(this->pGO);
}
