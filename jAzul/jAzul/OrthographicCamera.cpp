#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera() :
	Camera(),
	left(0.0f),
	right(0.0f),
	top(0.0f),
	bottom(0.0f),
	zNear(0.0f),
	zFar(0.0f)
{
}

void OrthographicCamera::setOrthographic(const float xMin, const float xMax, const float yMin, const float yMax, const float zMin, const float zMax)
{
	this->left = xMin;
	this->right = xMax;
	this->bottom = yMin;
	this->top = yMax;
	this->nearDist = zMin;
	this->farDist = zMax;
}

void OrthographicCamera::privUpdateProjectionMatrix(void)
{
	this->projMatrix[m0] = 2.0f / (this->right - this->left);
	this->projMatrix[m1] = 0.0f;
	this->projMatrix[m2] = 0.0f;
	this->projMatrix[m3] = 0.0f;

	this->projMatrix[m4] = 0.0f;
	this->projMatrix[m5] = 2.0f / (this->top - this->bottom);
	this->projMatrix[m6] = 0.0f;
	this->projMatrix[m7] = 0.0f;

	this->projMatrix[m8] = 0.0f;
	this->projMatrix[m9] = 0.0f;
	this->projMatrix[m10] = - 2.0f / (this->farDist - this->nearDist);
	this->projMatrix[m11] = 0.0f;

	this->projMatrix[m12] = -(this->right + this->left) / (this->right - this->left);
	this->projMatrix[m13] = -(this->top + this->bottom) / (this->top - this->bottom);
	this->projMatrix[m14] = -(this->farDist + this->nearDist) / (this->farDist - this->bottom);
	this->projMatrix[m15] = 1.0f;

	// Converting from OpenGL-style NDC of [-1,1] to DX's [0,1].  See note: https://anteru.net/blog/2011/12/27/1830/
	// (Note: NDCConvert should be precomputed once and stored for reuse)
	Matrix B(TRANS, 0, 0, 1.0f);
	Matrix S(SCALE, 1, 1, 0.5f);
	Matrix NDCConvert = B * S;

	projMatrix = projMatrix * NDCConvert;
}
