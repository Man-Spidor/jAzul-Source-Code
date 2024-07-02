#include "GraphicsObject_Texture.h"

#include "Model.h"
#include "Texture.h"

#include "GraphicsAttorney.h"

GraphicsObject_Texture::~GraphicsObject_Texture()
{
	delete[] this->MeshTextures;
}

GraphicsObject_Texture::GraphicsObject_Texture(Model* _pModel) :
	GraphicsObject_Base(_pModel),
	MeshTextures(nullptr),
	scale(1.0f)
{
	const unsigned int n = this->pModel->GetMeshCount();
	this->MeshTextures = new Texture*[n];
	for (int i = 0; i < this->pModel->GetMeshCount(); i++) {
		this->MeshTextures[i] = nullptr;
	}
}

void GraphicsObject_Texture::SetScale(const float _scale)
{
	this->scale = _scale;
}

void GraphicsObject_Texture::SetTexture(Texture* _pTexture)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++) {
		this->MeshTextures[i] = _pTexture;
	}
}

void GraphicsObject_Texture::SetTexture(const unsigned int meshnum, Texture* _pTexture)
{
	this->MeshTextures[meshnum] = _pTexture;
}

void GraphicsObject_Texture::SetWorld(const Matrix& m)
{
	this->world  = m;
}

void GraphicsObject_Texture::Render()
{
	GraphicsAttorney::Draw::DrawGO(this);
}

void GraphicsObject_Texture::Draw()
{
	GraphicsAttorney::Shader::SendTextureParams(world);
	this->pModel->SetToContext(GraphicsAttorney::Shader::GetContext());

	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
	{
		this->MeshTextures[i]->SetToContext(GraphicsAttorney::Shader::GetContext());

		this->pModel->RenderMesh(GraphicsAttorney::Shader::GetContext(), i);
	}
}
