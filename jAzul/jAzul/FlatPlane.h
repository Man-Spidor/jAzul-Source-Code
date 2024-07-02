#ifndef _FlatPlane
#define _FlatPlane

#include "Model.h"

/// Represents a flat plane model.
/// 
/// This class provides functionality to create and manage a flat plane model with specified size and texture repetition.
class FlatPlane : public Model
{
public:
    FlatPlane(const FlatPlane&) = delete; // Copy constructor
    FlatPlane(Model&&) = delete;          // Move constructor
    FlatPlane& operator=(const FlatPlane&) & = delete; // Copy assignment operator
    FlatPlane& operator=(FlatPlane&&) & = delete;      // Move assignment operator
    ~FlatPlane() = default;               // Destructor

    /// Constructor to initialize the flat plane model with specified size and texture repetition.
    /// @param size The size of the flat plane.
    /// @param hrep The horizontal repetition of the texture.
    /// @param vrep The vertical repetition of the texture.
    FlatPlane(float size, float hrep, float vrep);
};

#endif // _FlatPlane
