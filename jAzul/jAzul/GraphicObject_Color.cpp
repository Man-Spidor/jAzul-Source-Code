#include "GraphicObject_Color.h"

#include "Model.h"
#include "LightParamData.h"

#include "GraphicsAttorney.h"

GraphicsObject_Color::GraphicsObject_Color(Model* mod) :
	GraphicsObject_Base(mod),
	MeshColors(nullptr)
{
	const unsigned int n = this->pModel->GetMeshCount();
	MeshColors = new Vect[n];
	for (unsigned int i = 0; i < n; i++)
		MeshColors[i] = Vect(0, 0, 0);
}

GraphicsObject_Color::~GraphicsObject_Color()
{
	delete[] MeshColors;
}

void GraphicsObject_Color::SetColor(const Vect& col) 
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
		MeshColors[i] = col;
}

void GraphicsObject_Color::SetColor(const Vect& col, int meshnum)
{
	assert(pModel->ValidMeshNum(meshnum));
	MeshColors[meshnum] = col;
}

void GraphicsObject_Color::SetWorld(const Matrix& m) 
{ 
	world = m;
}

void GraphicsObject_Color::Render()
{
	GraphicsAttorney::Draw::DrawGO(this);
}

void GraphicsObject_Color::Draw()
{
	this->pModel->SetToContext(GraphicsAttorney::Shader::GetContext());

	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
	{
		GraphicsAttorney::Shader::SendColorParams(this->world, this->MeshColors[i]);

		this->pModel->RenderMesh(GraphicsAttorney::Shader::GetContext(), i);
	}
}
