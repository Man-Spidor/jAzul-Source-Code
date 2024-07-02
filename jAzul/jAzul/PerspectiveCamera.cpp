#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera() :
    Camera(),
    fovy(0), 
    aspectRatio(0) 
{
}

void PerspectiveCamera::setPerspective(const float FieldOfView_Degs, const float AspectRatio, const float NearDist, const float FarDist)
{
	this->aspectRatio = AspectRatio;
	this->fovy = FieldOfView_Degs;
	this->nearDist = NearDist;
	this->farDist = FarDist;
}

void PerspectiveCamera::privUpdateProjectionMatrix(void)
{
	float d = 1 / tanf(fovy / 2);

	this->projMatrix[m0] = d / aspectRatio;
	this->projMatrix[m1] = 0.0f;
	this->projMatrix[m2] = 0.0f;
	this->projMatrix[m3] = 0.0f;

	this->projMatrix[m4] = 0.0f;
	this->projMatrix[m5] = d;
	this->projMatrix[m6] = 0.0f;
	this->projMatrix[m7] = 0.0f;

	this->projMatrix[m8] = 0.0f;
	this->projMatrix[m9] = 0.0f;
	this->projMatrix[m10] = -(this->farDist + this->nearDist) / (this->farDist - this->nearDist);
	this->projMatrix[m11] = -1.0f;

	this->projMatrix[m12] = 0.0f;
	this->projMatrix[m13] = 0.0f;
	this->projMatrix[m14] = (-2.0f * this->farDist * this->nearDist) / (this->farDist - this->nearDist);
	this->projMatrix[m15] = 0.0f;

	// Converting from OpenGL-style NDC of [-1,1] to DX's [0,1].  See note: https://anteru.net/blog/2011/12/27/1830/
	// (Note: NDCConvert should be precomputed once and stored for reuse)
	Matrix B(TRANS, 0, 0, 1.0f);
	Matrix S(SCALE, 1, 1, 0.5f);
	Matrix NDCConvert = B * S;

	projMatrix = projMatrix * NDCConvert;
}
