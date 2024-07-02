#include "GraphicsObject_Wireframe.h"
#include "Model.h"

#include "GraphicsAttorney.h"

GraphicsObject_Wireframe::~GraphicsObject_Wireframe()
{
	delete[] MeshColors;
}

GraphicsObject_Wireframe::GraphicsObject_Wireframe(Model* pModel) :
	GraphicsObject_Base(pModel),
	MeshColors(nullptr)
{
	const unsigned int n = this->pModel->GetMeshCount();
	MeshColors = new Vect[n];
	for (unsigned int i = 0; i < n; i++)
		MeshColors[i] = Vect(0, 0, 0);
}

void GraphicsObject_Wireframe::SetColor(const Vect& col)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
		MeshColors[i] = col;
}

const Vect& GraphicsObject_Wireframe::GetColor() const
{
	return *this->MeshColors;
}

void GraphicsObject_Wireframe::SetWorld(const Matrix& m)
{
	this->world = m;
}

void GraphicsObject_Wireframe::Render()
{
	GraphicsAttorney::Draw::DrawGO(this);
}

void GraphicsObject_Wireframe::Draw()
{
	this->pModel->SetToContext(GraphicsAttorney::Shader::GetContext());

	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
	{
		GraphicsAttorney::Shader::SendColorParams(this->world, this->MeshColors[i]);

		this->pModel->RenderMesh(GraphicsAttorney::Shader::GetContext(), i);
	}
}
