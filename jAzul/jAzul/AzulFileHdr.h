#ifndef AZUL_FILE_HDR_H
#define AZUL_FILE_HDR_H

#include <string.h>
#include "MathEngine.h"

#define OBJECT_NAME_SIZE 32

/// Represents the header information of an Azul file.
/// 
/// This structure contains information about an Azul file, including object name,
/// vertex buffer details, triangle list details, texture names, and bounding volumes.
struct AzulFileHdr
{
    /// Default constructor. Initializes all members to zero.
    AzulFileHdr()
    {
        memset(this, 0x0, sizeof(AzulFileHdr));
    }

    /// Destructor.
    ~AzulFileHdr()
    {
        // Do nothing
    }

    char objName[OBJECT_NAME_SIZE]; ///< Object name.

    int numVerts; ///< Number of vertices.
    int vertBufferOffset; ///< Offset to the vertex buffer.

    int numTriangles; ///< Number of triangles.
    int triangleListBufferOffset; ///< Offset to the triangle list buffer.

    int numTextures; ///< Number of textures.
    int textureNamesOffset; ///< Offset to the texture names list.
    int textureNamesInBytes; ///< Size of the texture names list in bytes.

    Vect center; ///< Center of the bounding sphere.
    float radius; ///< Radius of the bounding sphere.

    Vect minPointAABB; ///< Minimum point of the axis-aligned bounding box.
    Vect maxPointAABB; ///< Maximum point of the axis-aligned bounding box.
};

#endif // AZUL_FILE_HDR_H
