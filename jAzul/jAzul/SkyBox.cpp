#include "SkyBox.h"

#include "GraphicsAttorney.h"

SkyBox::SkyBox(const float scale)
{
	this->mDevice = GraphicsAttorney::Device::GetDevice();
	assert(this->mDevice);

	this->numVerts = 20;
	this->pStdVerts = new StandardVertex[this->numVerts];

	this->numTris = 12;
	this->pTriList = new TriangleByIndex[this->numTris];

	pStdVerts[0].set(-scale * 1.0f, -scale * 1.0f, +scale * 1.0f, 0.25f, 2.0f / 3.0f);	// front bottom right	
	pStdVerts[1].set(-scale * 1.0f, +scale * 1.0f, +scale * 1.0f, 0.25f, 1.0f / 3.0f);	// front top right		
	pStdVerts[2].set(+scale * 1.0f, +scale * 1.0f, +scale * 1.0f, 0.0f, 1.0f / 3.0f);	// front top left
	pStdVerts[3].set(+scale * 1.0f, -scale * 1.0f, +scale * 1.0f, 0.0f, 2.0f / 3.0f);	// front bottom left
	pStdVerts[4].set(-scale * 1.0f, -scale * 1.0f, -scale * 1.0f, scale * 1.0f, 2.0f / 3.0f);	// back bottom left		
	pStdVerts[5].set(-scale * 1.0f, +scale * 1.0f, -scale * 1.0f, scale * 1.0f, 1.0f / 3.0f);	// back top left		
	pStdVerts[6].set(+scale * 1.0f, +scale * 1.0f, -scale * 1.0f, 0.75f, 1.0f / 3.0f);	// back top right
	pStdVerts[7].set(+scale * 1.0f, -scale * 1.0f, -scale * 1.0f, 0.75f, 2.0f / 3.0f);	// back bottom right
	pStdVerts[8].set(+scale * 1.0f, +scale * 1.0f, +scale * 1.0f, 1.0f, 1.0f / 3.0f);	// front top left
	pStdVerts[9].set(+scale * 1.0f, -scale * 1.0f, +scale * 1.0f, 1.0f, 2.0f / 3.0f);	// front bottom left	
	pStdVerts[10].set(+scale * 1.0f, +scale * 1.0f, +scale * 1.0f, 0.25f, 0.0f);		// TOP Top right		
	pStdVerts[11].set(+scale * 1.0f, +scale * 1.0f, -scale * 1.0f, scale * 1.0f, 0.0f);		// TOP Top right	
	pStdVerts[12].set(+scale * 1.0f, -scale * 1.0f, +scale * 1.0f, 0.25f, 1.0f);		// front bottom right	
	pStdVerts[13].set(+scale * 1.0f, -scale * 1.0f, -scale * 1.0f, scale * 1.0f, 1.0f);		// back bottom right

	// front face
	pTriList[0].set(0, 1, 2);
	pTriList[1].set(0, 2, 3);
	// left face
	pTriList[2].set(4, 5, 0);
	pTriList[3].set(5, 1, 0);
	// back face
	pTriList[4].set(6, 5, 4);
	pTriList[5].set(7, 6, 4);
	// right face
	pTriList[6].set(6, 9, 8);
	pTriList[7].set(6, 7, 9);
	// top face
	pTriList[8].set(1, 5, 10);
	pTriList[9].set(5, 11, 10);
	// bottom face
	pTriList[10].set(4, 0, 12);
	pTriList[11].set(13, 4, 12);

	this->privRemoveVertDupes();
	this->privCalcColData();
	this->privLoadDataToGPU();
}
