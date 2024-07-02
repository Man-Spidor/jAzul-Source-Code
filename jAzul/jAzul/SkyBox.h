#ifndef SKYBOX_H
#define SKYBOX_H

#include "Model.h"

struct ID3D11Device;

/// Represents a skybox model.
/// 
/// This class provides functionality to create and manage a skybox model with a specified scale.
class SkyBox : public Model
{
public:
    SkyBox() = delete; ///< Default constructor (deleted).
    SkyBox(const SkyBox& other) = default; ///< Copy constructor.
    SkyBox& operator=(const SkyBox& other) = default; ///< Copy assignment operator.
    SkyBox(SkyBox&& other) = default; ///< Move constructor.
    SkyBox& operator=(SkyBox&& other) = default; ///< Move assignment operator.
    ~SkyBox() = default; ///< Destructor.

    /// Constructor to initialize the skybox model with a specified scale.
    /// @param scale The scale of the skybox.
    SkyBox(const float scale);
};

#endif // SKYBOX_H
