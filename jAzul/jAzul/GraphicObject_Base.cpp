#include "GraphicObject_Base.h"

GraphicsObject_Base::GraphicsObject_Base(Model* _pModel) :
	pModel(_pModel)
{
}

void GraphicsObject_Base::SetModel(Model* mod)
{
	pModel = mod;
}

Model* GraphicsObject_Base::GetModel() const
{
	return this->pModel;
}

void GraphicsObject_Base::SetWorld(const Matrix& _world)
{
	this->world = _world;
}

const Matrix& GraphicsObject_Base::GetWorld() const
{
	return this->world;
}
