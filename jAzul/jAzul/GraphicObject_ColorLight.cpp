#include "GraphicObject_ColorLight.h"

#include "Model.h"
#include "d3dUtil.h"
#include "LightData.h"
#include "LightParamData.h"

#include "GraphicsAttorney.h"

void GraphicsObject_ColorLight::SetMaterial(const Vect& amb, const Vect& diff, const Vect& sp)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++) {
		MeshColors[i].lightData.Ambient = amb;
		MeshColors[i].lightData.Diffuse = diff;
		MeshColors[i].lightData.Specular = sp;
		MeshColors[i].scale = this->scale;
	}
}

void GraphicsObject_ColorLight::SetMaterial(const unsigned int meshNum, const Vect& amb, const Vect& diff, const Vect& sp)
{
	MeshColors[meshNum].lightData.Ambient = amb;
	MeshColors[meshNum].lightData.Diffuse = diff;
	MeshColors[meshNum].lightData.Specular = sp;
	MeshColors[meshNum].scale = this->scale;
}

GraphicsObject_ColorLight::~GraphicsObject_ColorLight()
{
	delete[] this->MeshColors;
}

void GraphicsObject_ColorLight::SetScale(const float _scale)
{
	this->scale = _scale;
}

void GraphicsObject_ColorLight::SetWorld(const Matrix& m)
{
	this->world = m;
}

void GraphicsObject_ColorLight::SetColor(const Vect& color)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++) {
		this->MeshColors[i].lightData.Ambient = 0.25f * color;
		this->MeshColors[i].lightData.Diffuse = 0.5f * color;
		this->MeshColors[i].lightData.Specular = 0.2f * color;
		this->MeshColors[i].scale = this->scale;
	}
}

void GraphicsObject_ColorLight::SetColor(const unsigned int meshNum, const Vect& color)
{
	MeshColors[meshNum].lightData.Ambient = 0.25f * color;
	MeshColors[meshNum].lightData.Diffuse = 0.5f * color;
	MeshColors[meshNum].lightData.Specular = 0.25f * color;
	MeshColors[meshNum].scale = this->scale;
}

void GraphicsObject_ColorLight::Render()
{
	GraphicsAttorney::Draw::DrawGO(this);
}

void GraphicsObject_ColorLight::Draw()
{
	this->pModel->SetToContext(GraphicsAttorney::Shader::GetContext());

	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
	{
		GraphicsAttorney::Shader::SendColorLightParams(world, MeshColors[i].lightData.Ambient, MeshColors[i].lightData.Diffuse, MeshColors[i].lightData.Specular);

		this->pModel->RenderMesh(GraphicsAttorney::Shader::GetContext(), i);
	}
}

GraphicsObject_ColorLight::GraphicsObject_ColorLight(Model* _pModel) :
	GraphicsObject_Base(_pModel),
	MeshColors(nullptr),
	scale(1.0f)
{	
	int n = this->pModel->GetMeshCount();
	MeshColors = new Material[n];
	for (int i = 0; i < n; i++) {
		Vect amb, diff, sp;
		MeshColors[i].lightData = LightData(amb, diff, sp);
		this->scale = 1.0f;
	}
}
