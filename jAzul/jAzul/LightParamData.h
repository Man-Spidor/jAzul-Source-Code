#ifndef LIGHTPARAMDATA_H
#define LIGHTPARAMDATA_H

#include <Matrix.h>
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "LightNum.h"
#include "LightData.h"

static const unsigned int MAX_DIR_LIGHTS = 2;
static const unsigned int MAX_POINT_LIGHTS = 16;
static const unsigned int MAX_SPOT_LIGHTS = 16;

/// @brief Represents a materials properties for lighting.
/// 
/// This structure contains information about the light data and the scale of the material.
struct Material
{
    LightData lightData; ///< Light data (ambient, diffuse, specular).
    float scale = 1.0f; ///< Scale of the material.
};

/// @brief Represents world and material data for shaders.
/// 
/// This structure contains the world matrix, the inverse world matrix, and the material properties.
struct Data_WorldAndMaterial
{
    Matrix World; ///< World matrix.
    Matrix WorldInv; ///< Inverse world matrix.
    Material Mat; ///< Material properties.
};

/// @struct Data_LightParams
/// @brief Represents lighting parameters for shaders.
/// 
/// This structure contains information about the directional lights, point lights, spotlights, and the eye position in world space.
struct Data_LightParams
{
    DirectionalLight DirLight[MAX_DIR_LIGHTS]; ///< Array of directional lights.
    PointLight PntLight[MAX_POINT_LIGHTS]; ///< Array of point lights.
    SpotLight SptLight[MAX_SPOT_LIGHTS]; ///< Array of spotlights.
    Vect EyePosWorld; ///< Eye position in world space.
};

#endif // LIGHTPARAMDATA_H
