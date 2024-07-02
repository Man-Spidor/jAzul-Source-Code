// MeshSeparator

#ifndef _MeshSeparator
#define _MeshSeparator

#include <map>
#include <vector>

struct StandardVertex;
struct TriangleByIndex;

/// Separates a mesh into multiple sub-meshes.
/// 
/// This class provides functionality to separate a mesh into multiple sub-meshes based on vertex and triangle data.
class MeshSeparator
{
private:
    struct MeshIndexData
    {
        int offset; ///< Offset of the mesh in the index buffer.
        int numTri; ///< Number of triangles in the mesh.
    };

    MeshIndexData* meshdata; ///< Array of mesh index data.
    int meshcount; ///< Number of meshes.

public:
    MeshSeparator(const MeshSeparator&) = delete;				 // Copy constructor
    MeshSeparator(MeshSeparator&&) = default;                    // Move constructor
    MeshSeparator& operator=(const MeshSeparator&) & = default;  // Copy assignment operator
    MeshSeparator& operator=(MeshSeparator&&) & = default;       // Move assignment operator
    ~MeshSeparator();									         // Destructor

    MeshSeparator() = delete;

    /// Constructor to initialize the mesh separator with vertex and triangle data.
    /// @param pVerts Pointer to the vertex data.
    /// @param nverts Number of vertices.
    /// @param pTriList Reference to the triangle data.
    /// @param ntri Number of triangles.
    MeshSeparator(StandardVertex* pVerts, int nverts, TriangleByIndex*& pTriList, int ntri);

    /// Get the number of meshes.
    /// @return The number of meshes.
    int GetMeshCount();

    /// Get the triangle count and offset for a specific mesh.
    /// @param meshnum The mesh number.
    /// @param count Reference to store the triangle count.
    /// @param offset Reference to store the offset.
    void GetMeshTriCountAndOffset(int meshnum, int& count, int& offset);
};

#endif // _MeshSeparator
