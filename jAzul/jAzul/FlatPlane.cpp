#include "FlatPlane.h"

#include "d3dUtil.h"

#include "GraphicsAttorney.h"

FlatPlane::FlatPlane(float size, float hrep, float vrep)
{
	this->mDevice = GraphicsAttorney::Device::GetDevice();

	this->numVerts = 4;
	this->pStdVerts = new StandardVertex[this->numVerts];

	this->numTris = 2;
	this->pTriList = new TriangleByIndex[this->numTris];

	float c = size / 2;

	this->pStdVerts[0].set(-c, 0, -c, hrep, vrep, 0, 1, 0);
	this->pStdVerts[1].set(-c, 0,  c, hrep, 0, 0, 1, 0);
	this->pStdVerts[2].set( c, 0,  c, 0, 0, 0, 1, 0);
	this->pStdVerts[3].set( c, 0, -c, 0, vrep, 0, 1, 0);
	
	this->pTriList[0].set(0, 1, 2);
	this->pTriList[1].set(0, 2, 3); 

	this->privRemoveVertDupes();
	this->privCalcColData();
	this->privLoadDataToGPU();
}
