#include "GraphicsObject_TextureLight.h"

#include "Model.h"
#include "Texture.h"
#include "LightParamData.h"

#include "GraphicsAttorney.h"

GraphicsObject_TextureLight::~GraphicsObject_TextureLight()
{
	delete[] this->MeshColors;
	delete[] this->MeshTextures;
}

GraphicsObject_TextureLight::GraphicsObject_TextureLight(Model* mod) :
	GraphicsObject_Base(mod),
	MeshColors(nullptr),
	MeshTextures(nullptr),
	scale(1.0f)
{
	int n = this->pModel->GetMeshCount();
	MeshColors = new Material[n];
	for (int i = 0; i < n; i++) {
		Vect amb, diff, sp;
		MeshColors[i].lightData = LightData(amb, diff, sp);
		MeshColors[i].scale = this->scale;
	}

	this->MeshTextures = new Texture*[n];
	for (int i = 0; i < this->pModel->GetMeshCount(); i++) {
		this->MeshTextures[i] = nullptr;
	}
}

void GraphicsObject_TextureLight::SetScale(const float _scale)
{
	this->scale = _scale;
	for (int i = 0; i < this->pModel->GetMeshCount(); i++) {
		MeshColors[i].scale = this->scale;
	}
}

void GraphicsObject_TextureLight::SetTexture(Texture* pTexture)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++) {
		this->MeshTextures[i] = pTexture;
	}
}

void GraphicsObject_TextureLight::SetTexture(const unsigned int meshnum, Texture* pTexture)
{
	this->MeshTextures[meshnum] = pTexture;
}

void GraphicsObject_TextureLight::SetMaterial(const Vect& amb, const Vect& diff, const Vect& sp)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++) {
		MeshColors[i].lightData.Ambient = amb;
		MeshColors[i].lightData.Diffuse = diff;
		MeshColors[i].lightData.Specular = sp;
		MeshColors[i].scale = this->scale;
	}
}

void GraphicsObject_TextureLight::SetMaterial(const unsigned int meshNum, const Vect& amb, const Vect& diff, const Vect& sp)
{
	MeshColors[meshNum].lightData.Ambient = amb;
	MeshColors[meshNum].lightData.Diffuse = diff;
	MeshColors[meshNum].lightData.Specular = sp;
	MeshColors[meshNum].scale = this->scale;
}

void GraphicsObject_TextureLight::SetWorld(const Matrix& m)
{
	this->world = m;
}

void GraphicsObject_TextureLight::Render()
{
	GraphicsAttorney::Draw::DrawGO(this);
}

void GraphicsObject_TextureLight::Draw()
{
	this->pModel->SetToContext(GraphicsAttorney::Shader::GetContext());

	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
	{
		this->MeshTextures[i]->SetToContext(GraphicsAttorney::Shader::GetContext());
		GraphicsAttorney::Shader::SendTextureLightParams(world, MeshColors[i].lightData.Ambient, MeshColors[i].lightData.Diffuse, MeshColors[i].lightData.Specular, this->scale);

		this->pModel->RenderMesh(GraphicsAttorney::Shader::GetContext(), i);
	}
}
