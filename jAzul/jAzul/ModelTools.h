// ModelTools
// Support tools to compute bounding volumes on models
// Ported/adapted from Keenan's FBX Converter code

#ifndef _ModelTools
#define _ModelTools

#include "Vect.h"

struct StandardVertex;
struct TriangleByIndex;

/// @class ModelTools
/// Provides tools to create and manipulate 3D models.
/// 
/// This class provides functionality to create unit geometric shapes, compute bounding volumes, and more.
class ModelTools
{
public:
    /// Create a unit box.
    /// @param pVerts Reference to store the vertex data.
    /// @param nverts Reference to store the number of vertices.
    /// @param pTriList Reference to store the triangle data.
    /// @param ntri Reference to store the number of triangles.
    static void CreateUnitBox(StandardVertex*& pVerts, unsigned int& nverts, TriangleByIndex*& pTriList, unsigned int& ntri);

    /// Create a unit pyramid.
    /// @param pVerts Reference to store the vertex data.
    /// @param nverts Reference to store the number of vertices.
    /// @param pTriList Reference to store the triangle data.
    /// @param ntri Reference to store the number of triangles.
    static void CreateUnitPyramid(StandardVertex*& pVerts, unsigned int& nverts, TriangleByIndex*& pTriList, unsigned int& ntri);

    /// Create a unit pyramid with repeated texture coordinates.
    /// @param pVerts Reference to store the vertex data.
    /// @param nverts Reference to store the number of vertices.
    /// @param pTriList Reference to store the triangle data.
    /// @param ntri Reference to store the number of triangles.
    static void CreateUnitPyramidRepTexture(StandardVertex*& pVerts, unsigned  int& nverts, TriangleByIndex*& pTriList, unsigned int& ntri);

    /// Create a unit sphere.
    /// @param vslice Number of vertical slices.
    /// @param hslice Number of horizontal slices.
    /// @param pVerts Reference to store the vertex data.
    /// @param nverts Reference to store the number of vertices.
    /// @param pTriList Reference to store the triangle data.
    /// @param ntri Reference to store the number of triangles.
    static void CreateUnitSphere(int vslice, int hslice, StandardVertex*& pVerts, unsigned int& nverts, TriangleByIndex*& pTriList, unsigned int& ntri);

    /// Create a unit square.
    /// @param pVerts Reference to store the vertex data.
    /// @param nverts Reference to store the number of vertices.
    /// @param pTriList Reference to store the triangle data.
    /// @param ntri Reference to store the number of triangles.
    static void CreateUnitSquare(StandardVertex*& pVerts, unsigned int& nverts, TriangleByIndex*& pTriList, unsigned int& ntri);

    /// Get the minimum point of the model.
    /// @param Min Reference to store the minimum point.
    /// @param pVertList Pointer to the vertex list.
    /// @param vertCount Number of vertices.
    static void GetModelMin(Vect& Min, const Vect* pVertList, const unsigned int vertCount);

    /// Get the maximum point of the model.
    /// @param Max Reference to store the maximum point.
    /// @param pVertList Pointer to the vertex list.
    /// @param vertCount Number of vertices.
    static void GetModelMax(Vect& Max, const Vect* pVertList, const unsigned int vertCount);

    /// Get the center and radius of the model's bounding sphere.
    /// @param Center Reference to store the center point.
    /// @param Radius Reference to store the radius.
    /// @param Min The minimum point of the model.
    /// @param Max The maximum point of the model.
    static void GetModelCenterAndRadius(Vect& Center, float& Radius, const Vect& Min, const Vect& Max);
};

#endif // _ModelTools
