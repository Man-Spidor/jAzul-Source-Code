#ifndef PHONGADS_H
#define PHONGADS_H

#include "Vect.h"

struct PhongADS
{
	PhongADS() = default;
	PhongADS(const PhongADS& other) = default;
	PhongADS& operator=(const PhongADS& other) = default;
	PhongADS(PhongADS&& other) = default;
	PhongADS& operator=(PhongADS&& other) = default;
	~PhongADS() = default;

	Vect Ambient;
	Vect Diffuse;
	Vect Specular;
};

#endif // PHONGADS_H