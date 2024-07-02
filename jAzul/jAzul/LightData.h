#ifndef LIGHTDATA_H
#define LIGHTDATA_H

#include <Vect.h>

/// @brief Represents basic light data.
/// 
/// This structure contains information about the ambient, diffuse, and specular components of a light source.
struct LightData
{
    LightData() = default; ///< Default constructor.
    LightData(const LightData& other) = default; ///< Copy constructor.
    LightData& operator=(const LightData& other) = default; ///< Copy assignment operator.
    LightData(LightData&& other) = default; ///< Move constructor.
    LightData& operator=(LightData&& other) = default; ///< Move assignment operator.
    ~LightData() = default; ///< Destructor.

    /// @brief Parameterized constructor to initialize light data.
    /// @param _amb Ambient color.
    /// @param _diff Diffuse color.
    /// @param _sp Specular color.
    LightData(const Vect& _amb, const Vect& _diff, const Vect& _sp) :
        Ambient(_amb),
        Diffuse(_diff),
        Specular(_sp)
    {
    };

    Vect Ambient; ///< Ambient color component.
    Vect Diffuse; ///< Diffuse color component.
    Vect Specular; ///< Specular color component.
};

#endif // LIGHTDATA_H
