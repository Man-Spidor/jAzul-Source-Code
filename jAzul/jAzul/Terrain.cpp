#include "Terrain.h"
#include "TerrainModel.h"
#include "GraphicsObject_TextureLight.h"

Terrain::~Terrain()
{
	delete this->pTerrainModel;
	delete this->pTerrainGO;
}

Terrain::Terrain(LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV) :
	pTerrainModel(new TerrainModel(heightmapFile, len, maxheight, ytrans, RepeatU, RepeatV)),
	pTerrainGO(new GraphicsObject_TextureLight(this->pTerrainModel->getModel()))
{
	assert(this->pTerrainModel);
	assert(this->pTerrainGO);
}

void Terrain::SetWorld(const Matrix& m)
{
	this->pTerrainGO->SetWorld(m);
}

void Terrain::SetTexture(Texture* pTexture)
{
	this->pTerrainGO->SetTexture(pTexture);
}

void Terrain::SetMaterial(const Vect& amb, const Vect& diff, const Vect& sp)
{
	this->pTerrainGO->SetMaterial(amb, diff, sp);
}

void Terrain::SetMaterial(const unsigned int meshNum, const Vect& amb, const Vect& diff, const Vect& sp)
{
	this->pTerrainGO->SetMaterial(meshNum, amb, diff, sp);
}

void Terrain::Render()
{
	this->pTerrainGO->Render();;
}
