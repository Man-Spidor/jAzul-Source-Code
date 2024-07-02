#include "GraphicsObject_Sprite.h"

#include "Image.h"
#include "Model.h"
#include "Texture.h"
#include "jAzulRect.h"

#include "GraphicsAttorney.h"

GraphicsObject_Sprite::GraphicsObject_Sprite(Model* pMod, Image* _pImage, jAzulRect* _pRect) :
	GraphicsObject_Base(pMod),
	pImage(_pImage),
	pRect(_pRect)
{
}

Image& GraphicsObject_Sprite::GetImage() const
{
	return *this->pImage;
}

void GraphicsObject_Sprite::SetWorld(const Matrix& w)
{
	this->world = w;
}

void GraphicsObject_Sprite::Render()
{
	GraphicsAttorney::Draw::DrawGO(this);
}

void GraphicsObject_Sprite::Draw()
{
	// this->world.M12() += this->pImage->pRect->w;
	// this->world.M13() -= this->pImage->pRect->h;
	GraphicsAttorney::Shader::SendSpriteParams(	this->world,
												this->pImage->pText->getWidth(), 
												this->pImage->pText->getHeight(),
												*this->pImage->pRect);
	
	this->pModel->SetToContext(GraphicsAttorney::Shader::GetContext());
	this->pImage->pText->SetToContext(GraphicsAttorney::Shader::GetContext());

	this->pModel->Render(GraphicsAttorney::Shader::GetContext());
}
