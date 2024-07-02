#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "LightData.h"

/// @brief Represents a point light source.
/// 
/// This structure contains information about a point light, including its lighting parameters, position, attenuation, and range.
/// 
/// This is the structure used by the shaders to send light information to the GPU
struct PointLight
{
    PointLight() = default; ///< Default constructor.
    PointLight(const PointLight& other) = default; ///< Copy constructor.
    PointLight& operator=(const PointLight& other) = default; ///< Copy assignment operator.
    PointLight(PointLight&& other) = default; ///< Move constructor.
    PointLight& operator=(PointLight&& other) = default; ///< Move assignment operator.
    ~PointLight() = default; ///< Destructor.

    LightData Light; ///< Lighting parameters (ambient, diffuse, specular).
    Vect Position; ///< Position of the point light.
    Vect Attenuation; ///< Attenuation factors (constant, linear, quadratic).
    float Range = 0.0f; ///< Range of the point light.
};

#endif // POINTLIGHT_H
