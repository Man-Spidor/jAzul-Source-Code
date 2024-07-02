#include "Sky.h"
#include "SkyBox.h"
#include "GraphicsObject_Texture.h"

Sky::~Sky()
{
	delete this->pSkyModel;
	delete this->pSkyGO;
}

Sky::Sky() :
	pSkyModel(new SkyBox()),
	pSkyGO(new GraphicsObject_Texture(this->pSkyModel->getModel()))
{
	assert(this->pSkyModel);
	assert(this->pSkyGO);
}

void Sky::SetWorld(const Matrix& m)
{
	this->pSkyGO->SetWorld(m);
}

void Sky::SetTexture(Texture* pTexture)
{
	this->pSkyGO->SetTexture(pTexture);
}

void Sky::Render()
{
	this->pSkyGO->Render();
}
