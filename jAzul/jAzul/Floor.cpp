#include "Floor.h"
#include "FlatPlane.h"
#include "GraphicsObject_TextureLight.h"

Floor::~Floor()
{
	delete this->pPlaneModel;
	delete this->pPlaneGO;
}

Floor::Floor(float size, float hrep, float vrep) :
	pPlaneModel(new FlatPlane(size, hrep, vrep)),
	pPlaneGO(new GraphicsObject_TextureLight(this->pPlaneModel->getModel()))
{
	assert(this->pPlaneModel);
	assert(this->pPlaneGO);
}

void Floor::SetWorld(const Matrix& m)
{
	this->pPlaneGO->SetWorld(m);
}

void Floor::SetTexture(Texture* pTexture)
{
	this->pPlaneGO->SetTexture(pTexture);
}

void Floor::SetMaterial(const Vect& amb, const Vect& diff, const Vect& sp)
{
	this->pPlaneGO->SetMaterial(amb, diff, sp);
}

void Floor::SetMaterial(const unsigned int meshNum, const Vect& amb, const Vect& diff, const Vect& sp)
{
	this->pPlaneGO->SetMaterial(meshNum, amb, diff, sp);
}

void Floor::Render()
{
	this->pPlaneGO->Render();
}
