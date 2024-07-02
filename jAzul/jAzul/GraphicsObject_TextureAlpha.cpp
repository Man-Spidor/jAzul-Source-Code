#include "GraphicsObject_TextureAlpha.h"

#include "GraphicsAttorney.h"

GraphicsObject_TextureAlpha::GraphicsObject_TextureAlpha(Model* mod) :
	GraphicsObject_TextureLight(mod)
{
}

void GraphicsObject_TextureAlpha::Render()
{
	GraphicsAttorney::Draw::DrawGO(this);
}
