#ifndef MODEL_H
#define MODEL_H

#include <d3d11.h>
#include "Vect.h"
#include "Matrix.h"

class MeshSeparator;

/// Represents a standard vertex.
/// 
/// This structure contains information about a vertex, including position, texture coordinates, 
/// normal vectors, color, and mesh number.
struct StandardVertex : public Align16
{
    float x;    ///< X-coordinate of the vertex.
    float y;    ///< Y-coordinate of the vertex.
    float z;    ///< Z-coordinate of the vertex.

    float u;    ///< U-coordinate for texture mapping.
    float v;    ///< V-coordinate for texture mapping.

    unsigned int meshnum; ///< Mesh number for texture trickery.

    float nx;   ///< X-component of the normal vector.
    float ny;   ///< Y-component of the normal vector.
    float nz;   ///< Z-component of the normal vector.

    float r;    ///< Red component of the vertex color.
    float g;    ///< Green component of the vertex color.
    float b;    ///< Blue component of the vertex color.

    /// Set the vertex data.
    /// @param _x X-coordinate of the vertex.
    /// @param _y Y-coordinate of the vertex.
    /// @param _z Z-coordinate of the vertex.
    /// @param _u U-coordinate for texture mapping.
    /// @param _v V-coordinate for texture mapping.
    /// @param _nx X-component of the normal vector.
    /// @param _ny Y-component of the normal vector.
    /// @param _nz Z-component of the normal vector.
    /// @param _meshnum Mesh number for texture trickery.
    /// @param _r Red component of the vertex color.
    /// @param _g Green component of the vertex color.
    /// @param _b Blue component of the vertex color.
    void set(float _x, float _y, float _z, float _u = 0.0f, float _v = 0.0f, float _nx = 0.0f, float _ny = 0.0f, float _nz = 0.0f, unsigned int _meshnum = 0, float _r = 1.0f, float _g = 1.0f, float _b = 1.0f)
    {
        x = _x;
        y = _y;
        z = _z;
        u = _u;
        v = _v;
        nx = _nx;
        ny = _ny;
        nz = _nz;
        meshnum = _meshnum;
        r = _r;
        g = _g;
        b = _b;
    }

    /// Comparison operator for sorting vertices.
    /// @param other The other vertex to compare with.
    /// @return True if this vertex is less than the other vertex, false otherwise.
    bool operator<(const StandardVertex& other) const
    {
        // Compare based on x, y, and z values
        if (x != other.x)
            return x < other.x;
        if (y != other.y)
            return y < other.y;
        return z < other.z;
    }
};

/// Represents a triangle in the mesh of the model, by index.
/// 
/// This structure contains information about a triangle, including the indices of its vertices.
struct TriangleByIndex : public Align16
{
    unsigned int v0; ///< Index of the first vertex.
    unsigned int v1; ///< Index of the second vertex.
    unsigned int v2; ///< Index of the third vertex.

    /// Set the indices of the triangle.
    /// @param _v0 Index of the first vertex.
    /// @param _v1 Index of the second vertex.
    /// @param _v2 Index of the third vertex.
    void set(int _v0, int _v1, int _v2)
    {
        v0 = _v0;
        v1 = _v1;
        v2 = _v2;
    }
};

/// Manages a 3D model.
/// 
/// This class provides functionality to load, render, and manipulate 3D models.
class Model : public Align16
{
public:
    Model(const Model&) = delete;				// Copy constructor
    Model(Model&&) = delete;                    // Move constructor
    Model& operator=(const Model&) & = delete;  // Copy assignment operator
    Model& operator=(Model&&) & = delete;       // Move assignment operator

    enum PreMadeModels {
        UnitBox,
        UnitPyramid,
        UnitSphere,
        UnitSquareXY
    };

protected:
    Model();

public:
    /// Constructor to initialize the model with vertex and triangle data.
    /// @param pVerts Pointer to the vertex data.
    /// @param nverts Number of vertices.
    /// @param ptlist Pointer to the triangle data.
    /// @param ntri Number of triangles.
    Model(StandardVertex* pVerts, unsigned int nverts, TriangleByIndex* ptlist, int ntri);

    /// Constructor to initialize a pre-made model.
    /// @param pm The pre-made model type.
    Model(PreMadeModels pm);

    /// Constructor to load a model from a file.
    /// @param _modelName The name of the model file.
    Model(const char* const _modelName);

    /// Destructor.
    virtual ~Model();

    /// Set the model to the context.
    /// @param context Pointer to the device context.
    void SetToContext(ID3D11DeviceContext* context);

    /// Render the model.
    /// @param context Pointer to the device context.
    void Render(ID3D11DeviceContext* context);

    /// Render a specific mesh of the model.
    /// @param context Pointer to the device context.
    /// @param meshnum The mesh number.
    void RenderMesh(ID3D11DeviceContext* context, int meshnum);

    /// Get the number of meshes in the model.
    /// @return The number of meshes.
    int GetMeshCount();

    /// Check if the mesh number is valid.
    /// @param i The mesh number.
    /// @return True if the mesh number is valid, false otherwise.
    bool ValidMeshNum(int i);

    /// Get the center of the model.
    /// @return The center vector.
    const Vect& GetCenter() const;

    /// Get the radius of the model's bounding sphere.
    /// @return The radius.
    const float GetRadius() const;

    /// Get the minimum point of the model.
    /// @return The minimum point vector.
    const Vect& GetModelMin() const;

    /// Get the maximum point of the model.
    /// @return The maximum point vector.
    const Vect& GetModelMax() const;

    /// Get the vertex list of the model.
    /// @return Pointer to the vertex list.
    const Vect* GetVertList() const;

    /// Get the number of vertices in the model.
    /// @return The number of vertices.
    const unsigned int GetVertCount() const;

protected:
    /// Load data to the GPU.
    void privLoadDataToGPU();

    /// Load data from a file.
    /// @param _modelName The name of the model file.
    /// @param pVerts Reference to store the vertex data.
    /// @param nverts Reference to store the number of vertices.
    /// @param ptlist Reference to store the triangle data.
    /// @param ntri Reference to store the number of triangles.
    void privLoadDataFromFile(const char* const _modelName, StandardVertex*& pVerts, unsigned int& nverts, TriangleByIndex*& ptlist, unsigned int& ntri);

    /// Calculate the collision data.
    void privCalcColData();

    /// Remove duplicate vertices.
    void privRemoveVertDupes();

protected:
    TriangleByIndex* pTriList; ///< Pointer to the triangle list.
    StandardVertex* pStdVerts; ///< Pointer to the standard vertices.
    Vect* pVertList; ///< Pointer to the vertex list.

    MeshSeparator* meshes; ///< Pointer to the mesh separator.

    ID3D11Device* mDevice; ///< Pointer to the device.
    ID3D11Buffer* mpVertexBuffer; ///< Pointer to the vertex buffer.
    ID3D11Buffer* mpIndexBuffer; ///< Pointer to the index buffer.

    Vect* modelMin; ///< Pointer to the minimum point of the model.
    Vect* modelMax; ///< Pointer to the maximum point of the model.

    Vect* center; ///< Pointer to the center of the model.

    unsigned int numVertsNoDupes; ///< Number of vertices without duplicates.
    unsigned int numVerts; ///< Number of vertices.
    unsigned int numTris; ///< Number of triangles.

    float radius; ///< Radius of the model's bounding sphere.
};

#endif // MODEL_H
