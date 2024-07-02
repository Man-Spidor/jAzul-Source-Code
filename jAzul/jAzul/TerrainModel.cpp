#include "TerrainModel.h"
#include "d3dUtil.h"
#include "DirectXTex.h"
#include "GraphicsAttorney.h"

TerrainModel::~TerrainModel()
{
    delete[] this->pCellList;
}

TerrainModel::TerrainModel(LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV)
{
    this->mDevice = GraphicsAttorney::Device::GetDevice();
    assert(this->mDevice);

    DirectX::ScratchImage scrtTex;
    HRESULT hr = LoadFromTGAFile(heightmapFile, nullptr, scrtTex);
    assert(SUCCEEDED(hr));

    const DirectX::Image* hgtmap = scrtTex.GetImage(0, 0, 0);
    assert(hgtmap->height == hgtmap->width);

    this->side = hgtmap->height;    // the image should be square
    int pixel_width = 4;          // 4 bytes RGBA per pixel

    // Calculate step sizes
    float xStepSize = len / (side - 1);
    float zStepSize = len / (side - 1);

    this->numVerts = side * side;
    this->pStdVerts = new StandardVertex[numVerts];

    this->numTris = 2 * (side - 1) * (side - 1);
    this->pTriList = new TriangleByIndex[numTris];

    this->numCells = this->numTris / 2;
    this->pCellList = new TerrainCell[numCells];
    this->cell_width = len / side;
    this->cell_axes[0] = Vect(this->cell_width, 0.0f, 0.0f, 0.0f);
    this->cell_axes[1] = Vect(0.0f, this->cell_width, 0.0f, 0.0f);

    // Generate vertices and adjust height based on the heightmap
    for (unsigned int z = 0; z < side; ++z) {
        for (unsigned int x = 0; x < side; ++x) {
            int index = z * side + x;
            
            float height = static_cast<float>(hgtmap->pixels[this->TexelIndex(pixel_width, x, z)]);
            float normalized_height = (height + ytrans) * (maxheight / 255.0f); // Normalize and scale height
            if (normalized_height > maxheight)
                normalized_height = maxheight;

            float u = static_cast<float>(x) / (side - 1); // Calculate u coordinate
            float v = static_cast<float>(z) / (side - 1); // Calculate v coordinate

            pStdVerts[index].set(x * xStepSize - len / 2.0f, normalized_height, z * zStepSize - len / 2.0f, u * RepeatU, v * RepeatV);
        }
    }

    // Calculate normals
    for (unsigned int z = 0; z < side; ++z) {
        for (unsigned int x = 0; x < side; ++x) {
            Vect normal(0, 0, 0);
            int index = z * side + x;

            if (x > 0 && x < side - 1 && z > 0 && z < side - 1) {
                Vect left(pStdVerts[z * side + (x - 1)].x, pStdVerts[z * side + (x - 1)].y, pStdVerts[z * side + (x - 1)].z);
                Vect right(pStdVerts[z * side + (x + 1)].x, pStdVerts[z * side + (x + 1)].y, pStdVerts[z * side + (x + 1)].z);
                Vect down(pStdVerts[(z - 1) * side + x].x, pStdVerts[(z - 1) * side + x].y, pStdVerts[(z - 1) * side + x].z);
                Vect up(pStdVerts[(z + 1) * side + x].x, pStdVerts[(z + 1) * side + x].y, pStdVerts[(z + 1) * side + x].z);

                Vect dx = right - left;
                Vect dz = up - down;

                normal = dz.cross(dx);
                normal.norm();
            }
            else {
                normal = Vect(0, 1, 0); // Default normal for edges and corners
            }

            // Set vertex normal
            pStdVerts[index].nx = normal.X();
            pStdVerts[index].ny = normal.Y();
            pStdVerts[index].nz = normal.Z();
        }
    }

    // Generate triangle indices
    unsigned int triIndex = 0;
    for (unsigned int z = 0; z < side - 1; ++z) {
        for (unsigned int x = 0; x < side - 1; ++x) {
            unsigned int i0 = z * side + x;
            unsigned int i1 = i0 + 1;
            unsigned int i2 = (z + 1) * side + x;
            unsigned int i3 = i2 + 1;

            // First triangle
            pTriList[triIndex++].set(i0, i2, i1);
            // Second triangle
            pTriList[triIndex++].set(i1, i2, i3);
        }
    }

    for (unsigned int i = 0; i < (side - 1); i++) {
        for (unsigned int j = 0; j < (side - 1); j++) {
            const unsigned int i0 = (i * side) + j;
            const unsigned int i1 = i0 + 1;
            const unsigned int i2 = ((i + 1) * side) + j;
            const unsigned int i3 = i2 + 1;

            const unsigned int cellIndex = i * (side - 1) + j;
            
            // Set The Verts
            this->pCellList[cellIndex].v0 = &this->pStdVerts[i0];
            this->pCellList[cellIndex].v1 = &this->pStdVerts[i1];
            this->pCellList[cellIndex].v2 = &this->pStdVerts[i2];
            this->pCellList[cellIndex].v3 = &this->pStdVerts[i3];
            
            // Find and set the Min/Max
            this->pCellList[cellIndex].Min.X() = this->pStdVerts[i0].x;
            this->pCellList[cellIndex].Min.Y() = this->pStdVerts[i0].y;
            this->pCellList[cellIndex].Min.Z() = this->pStdVerts[i0].z;
            this->pCellList[cellIndex].Max = this->pCellList[cellIndex].Min;
            this->CheckMinMax(this->pCellList[cellIndex], this->pStdVerts[i1]);
            this->CheckMinMax(this->pCellList[cellIndex], this->pStdVerts[i2]);
            this->CheckMinMax(this->pCellList[cellIndex], this->pStdVerts[i3]);

            // Set The CellWidth and Axes
            this->pCellList[cellIndex].CellWidth = &this->cell_width;
            this->pCellList[cellIndex].XAxis = &this->cell_axes[0];
            this->pCellList[cellIndex].ZAxis = &this->cell_axes[1];
            this->pCellList[cellIndex].YAxis = Vect(0.0f, fabsf(this->pCellList[cellIndex].Max.Y() - this->pCellList[cellIndex].Min.Y()), 0.0f);
            this->pCellList[cellIndex].YMag = this->pCellList[cellIndex].YAxis.mag();

            // Calculate the center
            this->pCellList[cellIndex].Center = 0.5f * (this->pCellList[cellIndex].Max + this->pCellList[cellIndex].Min);

            // Calculate the half diagonal
            this->pCellList[cellIndex].HalfDiagonal = this->pCellList[cellIndex].Max - this->pCellList[cellIndex].Center;
        }
    }

    this->privRemoveVertDupes();
    this->privCalcColData();
    this->privLoadDataToGPU();
}

const int TerrainModel::GetSideLen() const
{
    return this->side;
}

const Vect& TerrainModel::GetMin(int i, int j) const
{
    return this->pCellList[j * (this->side - 1) + i].Min;
}

const Vect& TerrainModel::GetMax(int i, int j) const
{
    return this->pCellList[j * (this->side - 1) + i].Max;
}

const TerrainCell* TerrainModel::GetCellList() const
{
    return this->pCellList;
}

const float TerrainModel::GetCellWidth() const
{
    return this->cell_width;
}

void TerrainModel::CheckMinMax(TerrainCell& pCell, const StandardVertex& Vert)
{
    if (pCell.Min.X() > Vert.x)
        pCell.Min.X() = Vert.x;

    else if (pCell.Max.X() < Vert.x)
        pCell.Max.X() = Vert.x;

    if (pCell.Min.Y() > Vert.y)
        pCell.Min.Y() = Vert.y;

    else if (pCell.Max.Y() < Vert.y)
        pCell.Max.Y() = Vert.y;

    if (pCell.Min.Z() > Vert.z)
        pCell.Min.Z() = Vert.z;

    else if (pCell.Max.Z() < Vert.z)
        pCell.Max.Z() = Vert.z;
}

const unsigned int TerrainModel::TexelIndex(unsigned int pixel_width, const int x, const int y)
{
    return static_cast<unsigned int>((y * this->side + x) * pixel_width);
}
