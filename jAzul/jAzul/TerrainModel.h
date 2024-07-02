#ifndef _TerrainModel
#define _TerrainModel

#include "Model.h"

/// Represents a cell in the terrain model.
/// 
/// This structure contains information about a terrain cell necessary for collision detection, 
/// including its vertices, bounding box, center, and diagonal vectors.
struct TerrainCell
{
public:
    TerrainCell() = default;
    TerrainCell(const TerrainCell& other) = default;
    TerrainCell& operator=(const TerrainCell& other) = default;
    TerrainCell(TerrainCell&& other) = default;
    TerrainCell& operator=(TerrainCell&& other) = default;
    ~TerrainCell() = default;

    Vect Min; ///< Minimum bounds of the cell.
    Vect Max; ///< Maximum bounds of the cell.
    Vect Center; ///< Center of the cell.
    Vect HalfDiagonal; ///< Half diagonal of the cell.
    Vect YAxis; ///< Y-axis vector.

    float YMag; ///< Y-axis magnitude.

    const StandardVertex* v0; ///< Pointer to the first vertex.
    const StandardVertex* v1; ///< Pointer to the second vertex.
    const StandardVertex* v2; ///< Pointer to the third vertex.
    const StandardVertex* v3; ///< Pointer to the fourth vertex.
    const Vect* XAxis; ///< X-axis vector.
    const Vect* ZAxis; ///< Z-axis vector.
    const float* CellWidth; ///< Width of the cell.
};

/// Represents a terrain model.
/// 
/// This class provides functionality to create, manage, and retrieve information about a terrain model using a greyscale heightmap texture.
class TerrainModel : public Model
{
public:
    TerrainModel() = delete;
    TerrainModel(const TerrainModel& other) = default;
    TerrainModel& operator=(const TerrainModel& other) = default;
    TerrainModel(TerrainModel&& other) = default;
    TerrainModel& operator=(TerrainModel&& other) = default;
    ~TerrainModel();

    /// Constructor to initialize the terrain model with heightmap data.
    /// @param heightmapFile The heightmap file.
    /// @param len The length of the terrain.
    /// @param maxheight The maximum height of the terrain.
    /// @param ytrans The Y-axis translation.
    /// @param RepeatU The U-axis texture repetition.
    /// @param RepeatV The V-axis texture repetition.
    TerrainModel(LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV);

    /// Get the side length of the terrain.
    /// @return The side length of the terrain.
    const int GetSideLen() const;

    /// Get the minimum bounds of a specific cell.
    /// @param i The row index.
    /// @param j The column index.
    /// @return The minimum bounds vector.
    const Vect& GetMin(int i, int j) const;

    /// Get the maximum bounds of a specific cell.
    /// @param i The row index.
    /// @param j The column index.
    /// @return The maximum bounds vector.
    const Vect& GetMax(int i, int j) const;

    /// Get the list of terrain cells.
    /// @return Pointer to the terrain cell list.
    const TerrainCell* GetCellList() const;

    /// Get the width of each cell.
    /// @return The width of each cell.
    const float GetCellWidth() const;

private:
    /// Check the minimum and maximum bounds of a terrain cell.
    /// @param pCell Reference to the terrain cell.
    /// @param Vert Reference to the vertex.
    void CheckMinMax(TerrainCell& pCell, const StandardVertex& Vert);

    /// Get the index of a texel in the heightmap.
    /// @param pixel_width The width of the heightmap in pixels.
    /// @param x The x-coordinate.
    /// @param y The y-coordinate.
    /// @return The texel index.
    const unsigned int TexelIndex(unsigned int pixel_width, const int x, const int y);

private:
    Vect cell_axes[2]; ///< Array of cell xz axis vectors.
    TerrainCell* pCellList; ///< Pointer to the terrain cell list.
    float cell_width; ///< Width of each cell.
    unsigned int numCells; ///< Number of cells.
    unsigned int side; ///< Side length of the terrain.
};

#endif // _TerrainModel
