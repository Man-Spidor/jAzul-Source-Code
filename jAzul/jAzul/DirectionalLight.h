#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "LightData.h"

/// @brief Represents a directional light source.
/// 
/// This structure contains information about a directional light, including its lighting parameters and direction.
/// 
/// This is the structure used by the shaders to send light information to the GPU
struct DirectionalLight
{
    DirectionalLight() = default; ///< Default constructor.
    DirectionalLight(const DirectionalLight& other) = default; ///< Copy constructor.
    DirectionalLight& operator=(const DirectionalLight& other) = default; ///< Copy assignment operator.
    DirectionalLight(DirectionalLight&& other) = default; ///< Move constructor.
    DirectionalLight& operator=(DirectionalLight&& other) = default; ///< Move assignment operator.
    ~DirectionalLight() = default; ///< Destructor.

    LightData Light; ///< Lighting parameters (ambient, diffuse, specular).
    Vect Direction; ///< Direction of the light.
};

#endif // DIRECTIONALLIGHT_H
