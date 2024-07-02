#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "LightData.h"

/// @brief Represents a spot light source.
/// 
/// This structure contains information about a spot light, including its lighting parameters, position, attenuation, direction, and spot exponent.
/// 
/// This is the structure used by the shaders to send light information to the GPU
struct SpotLight
{
    SpotLight() = default; ///< Default constructor.
    SpotLight(const SpotLight& other) = default; ///< Copy constructor.
    SpotLight& operator=(const SpotLight& other) = default; ///< Copy assignment operator.
    SpotLight(SpotLight&& other) = default; ///< Move constructor.
    SpotLight& operator=(SpotLight&& other) = default; ///< Move assignment operator.
    ~SpotLight() = default; ///< Destructor.

    LightData Light; ///< Lighting parameters (ambient, diffuse, specular).
    Vect Position; ///< Position of the spot light.
    Vect Attenuation; ///< Attenuation factors (constant, linear, quadratic).
    Vect Direction; ///< Direction of the light.
    float SpotExp = 0.0f; ///< Spotlight exponent.
    float Range = 0.0f; ///< Range of the spot light.
};

#endif // SPOTLIGHT_H
