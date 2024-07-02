#include "ModelTools.h"
//#include "Enum.h"
//#include <math.h>
#include "Matrix.h"
#include <assert.h>
#include "Model.h"
#include "d3dUtil.h"


/// Creates the unit box centered at the origin
void ModelTools::CreateUnitBox(StandardVertex *&pVerts, unsigned int& nverts, TriangleByIndex *&pTriList, unsigned int& ntri)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 1, 0, 0, 0, 1);
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0, 0, 0, 0, 1);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0, 1, 0, 0, 1);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 1, 1, 0, 0, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0, 0, 0, 0, -1);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 1, 0, 0, 0, -1);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 1, 1, 0, 0, -1);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0, 1, 0, 0, -1);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 1, 0, 0);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0, 0, 1, 0, 0);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0, 1, 1, 0, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 1, 0, -1, 0, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, -1, 0, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, -1, 0, 0);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 1, 1, -1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 0, 1, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, 0, 1, 0);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0, 1, 0, 1, 0);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 1, 1, 0, 1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1, 0, 0, -1, 0);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 0, 0, 0, -1, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, 0, -1, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 0, -1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}

void ModelTools::CreateUnitPyramid(StandardVertex*& pVerts, unsigned int& nverts, TriangleByIndex*& pTriList, unsigned int& ntri)
{
	nverts = 5;
	pVerts = new StandardVertex[nverts];
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];

	pVerts[0].set(0.0f, 1.0f, 0.0f);
	pVerts[1].set(-1.0f, -1.0f, -1.0f);
	pVerts[2].set(+1.0f, -1.0f, -1.0f);
	pVerts[3].set(+1.0f, -1.0f, +1.0f);
	pVerts[4].set(-1.0f, -1.0f, +1.0f);


	pTriList[0].set(0, 2, 1); // back face
	pTriList[1].set(0, 4, 3); // front face
	pTriList[2].set(0, 3, 2); // left face
	pTriList[3].set(0, 1, 4); // right face
	pTriList[4].set(1, 2, 3); // bottom faces
	pTriList[5].set(1, 3, 4);
}

void ModelTools::CreateUnitPyramidRepTexture(StandardVertex*& pVerts, unsigned int& nverts, TriangleByIndex*& pTriList, unsigned int& ntri)
{
	nverts = 13;
	pVerts = new StandardVertex[nverts];
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];

	pVerts[0].set(0.0f, 1.0f, 0.0f, 0.5f, 0.0f);		// top vertex
	pVerts[1].set(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f);		// back right vertex
	pVerts[2].set(+1.0f, -1.0f, -1.0f, 0.0f, 1.0f);		// back left vertex
	pTriList[0].set(0, 2, 1); // back face

	pVerts[3].set(+1.0f, -1.0f, +1.0f, 1.0f, 1.0f);		// front left vertex
	pVerts[4].set(-1.0f, -1.0f, +1.0f, 0.0f, 1.0f);		// front right vertex
	pTriList[1].set(0, 4, 3); // front face

	pVerts[5].set(+1.0f, -1.0f, -1.0f, 1.0f, 1.0f);	// back right vertex
	pVerts[6].set(+1.0f, -1.0f, +1.0f, 0.0f, 1.0f);	// front right vertex
	pTriList[2].set(0, 6, 5); // left face

	pVerts[7].set(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f);		// back left vertex
	pVerts[8].set(-1.0f, -1.0f, +1.0f, 1.0f, 1.0f);		// front left vertex
	pTriList[3].set(0, 7, 8); // right face

	pVerts[9].set(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f);		// back left vertex
	pVerts[10].set(+1.0f, -1.0f, -1.0f, 1.0f, 1.0f);	// back right vertex
	pVerts[11].set(+1.0f, -1.0f, +1.0f, 1.0f, 0.0f);	// front right vertex
	pVerts[12].set(-1.0f, -1.0f, +1.0f, 0.0f, 0.0f);	// front left vertex
	pTriList[4].set(9, 10, 11); // bottom faces
	pTriList[5].set(9, 11, 12);
}

void ModelTools::CreateUnitSphere(int vslice, int hslice, StandardVertex*& pVerts, unsigned int& nverts, TriangleByIndex*& pTriList, unsigned int& ntri)
{
	nverts = (vslice + 1) * (hslice + 1) * 1;
	pVerts = new StandardVertex[nverts];

	ntri = vslice * hslice * 2;
	pTriList = new TriangleByIndex[ntri];

	// Generate sphere vertices using matrix rotations
	const float pi = 2 * static_cast<float>(acos(0.0));
	int index = 0;
	for (int i = 0; i <= hslice; ++i) {
		float phi = static_cast<float>(i) / static_cast<float>(hslice) * static_cast<float>(pi);
		for (int j = 0; j <= vslice; ++j) {
			float theta = static_cast<float>(j) / static_cast<float>(vslice) * 2.0f * static_cast<float>(pi);

			// Generate a unit vector
			Vect unitVector(1.0f, 0.0f, 0.0f);

			// Rotate the vector using matrix operations
			Matrix RotZ(ROT_Z, theta);
			Matrix RotY(ROT_Y, phi);
			unitVector = unitVector * RotZ * RotY;

			float u = static_cast<float>(j) / static_cast<float>(vslice);
			float v = static_cast<float>(i) / static_cast<float>(hslice);

			// Set the vertex position
			pVerts[index].set(unitVector.X(), unitVector.Y(), unitVector.Z(), u, v, unitVector.X(), unitVector.Y(), unitVector.Z());

			++index;
		}
	}
	index = 0;
	const int TopFrontQuarter = vslice / 4;
	const int BotFrontQuarter = vslice - TopFrontQuarter;

	for (int i = 0; i < hslice; i++) {
		for (int j = 0; j < vslice; j++) {
			int v0 = i * (vslice + 1) + j;           // Bottom Left
			int v1 = v0 + 1;                          // Top Left
			int v2 = (i + 1) * (vslice + 1) + j;      // Bottom Right
			int v3 = v2 + 1;                          // Top Right

			// Front half of circle is drawn differently than back hald
			if (j < TopFrontQuarter || j >= BotFrontQuarter) {
				pTriList[index].set(v0, v2, v1);
				index++;
				pTriList[index].set(v1, v2, v3);
				index++;
			}
			else {
				pTriList[index].set(v2, v0, v1);
				index++;
				pTriList[index].set(v2, v1, v3);
				index++;
			}
		}
	}
}

void ModelTools::CreateUnitSquare(StandardVertex*& pVerts, unsigned int& nverts, TriangleByIndex*& pTriList, unsigned int& ntri)
{
	nverts = 4;
	pVerts = new StandardVertex[nverts];
	ntri = 2;
	pTriList = new TriangleByIndex[ntri];

	pVerts[0].set(-1.0f, -1.0f, 0.0f, 0.0f, 1.0f);	  // 0
	pVerts[1].set(-1.0f, 1.0f, 0.0f, 0.0f, 0.0f);	  // 1
	pVerts[2].set(1.0f, 1.0f, 0.0f, 1.0f, 0.0f);	  // 2
	pVerts[3].set(1.0f, -1.0f, 0.0f, 1.0f, 1.0f);	  // 3

	pTriList[0].set(0, 2, 1);
	pTriList[1].set(0, 3, 2);
}

void ModelTools::GetModelMin(Vect& Min, const Vect* pVertList, const unsigned int vertCount)
{
	Min = pVertList[0];
	for (unsigned int i = 1; i < vertCount; ++i) {
		if (pVertList[i].X() < Min.X())
			Min.X() = pVertList[i].X();
		if (pVertList[i].Y() < Min.Y())
			Min.Y() = pVertList[i].Y();
		if (pVertList[i].Z() < Min.Z())
			Min.Z() = pVertList[i].Z();
	}
}

void ModelTools::GetModelMax(Vect& Max, const Vect* pVertList, const unsigned int vertCount)
{
	Max = pVertList[0];
	for (unsigned int i = 1; i < vertCount; ++i) {
		if (pVertList[i].X() > Max.X())
			Max.X() = pVertList[i].X();
		if (pVertList[i].Y() > Max.Y())
			Max.Y() = pVertList[i].Y();
		if (pVertList[i].Z() > Max.Z())
			Max.Z() = pVertList[i].Z();
	}
}

void ModelTools::GetModelCenterAndRadius(Vect& Center, float& Radius, const Vect& Min, const Vect& Max)
{
	Center = 0.5f * (Max + Min);

	Radius = (Max - Center).mag();
}
