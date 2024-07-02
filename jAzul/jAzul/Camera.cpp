#include "Camera.h"
#include <assert.h>
#include <math.h>

Camera::Camera() : 	
	projMatrix(), 
	viewMatrix(),
	vUp(), 
	vDir(), 
	vRight(),  
	vPos(),	
	vLookAt(),
	nearDist(0), farDist(0) 
{
}

void Camera::setOrientAndPosition(const Vect &inUp, const Vect &inLookAt, const Vect &inPos)
{
	// Remember the up, dir and right are unit length, and are perpendicular.
	// Treat lookAt as king, find Right vect, then correct Up to insure perpendiculare.
	// Make sure that all vectors are unit vectors.

	this->vLookAt = inLookAt;
	this->vDir = -(inLookAt - inPos); // Right-Hand camera: vDir is flipped
	this->vDir.norm();   

	// Clean up the vectors (Right hand rule)
	this->vRight = inUp.cross(this->vDir);
	this->vRight.norm();

	this->vUp = this->vDir.cross(this->vRight);
	this->vUp.norm();

	this->vPos = inPos;
};

void Camera::privUpdateViewMatrix(void)
{
	// This functions assumes the your vUp, vRight, vDir are still unit
	// And perpendicular to each other

	// Set for DX Right-handed space
	this->viewMatrix[m0] = this->vRight[x];
	this->viewMatrix[m1] = this->vUp[x];
	this->viewMatrix[m2] = this->vDir[x];
	this->viewMatrix[m3] = 0.0f;

	this->viewMatrix[m4] = this->vRight[y];
	this->viewMatrix[m5] = this->vUp[y];
	this->viewMatrix[m6] = this->vDir[y];
	this->viewMatrix[m7] = 0.0f;

	this->viewMatrix[m8] = this->vRight[z];
	this->viewMatrix[m9] = this->vUp[z];
	this->viewMatrix[m10] = this->vDir[z];
	this->viewMatrix[m11] = 0.0f;

	// Apply R^t( -Pos ). Use dot-product with the basis vectors
	this->viewMatrix[m12] = -vPos.dot(vRight);
	this->viewMatrix[m13] = -vPos.dot(vUp);
	this->viewMatrix[m14] = -vPos.dot(vDir);
	this->viewMatrix[m15] = 1.0f;
};


// Update everything (make sure it's consistent)
void Camera::updateCamera(void)
{
	// update the projection matrix
	this->privUpdateProjectionMatrix();

	// update the view matrix
	this->privUpdateViewMatrix();
}

Matrix & Camera::getViewMatrix(void)
{
	return this->viewMatrix;
}

Matrix & Camera::getProjMatrix(void)
{
	return this->projMatrix;
}

void Camera::getPos(Vect &outPos) const
{
	outPos = this->vPos;
}

void  Camera::getDir(Vect &outDir) const
{
	outDir = this->vDir;
}

void  Camera::getUp(Vect &outUp) const
{
	outUp = this->vUp;
}

void Camera::getLookAt(Vect &outLookAt) const
{
	outLookAt = this->vLookAt;
}

void Camera::getRight(Vect &outRight) const
{
	outRight = this->vRight;
}

void Camera::TranslateLeftRight(float delta)
{
	vPos += vRight * delta;
}

void Camera::TranslateFwdBack(float delta)
{
	vPos -= vDir * delta;
}

void Camera::TiltUpDown(float ang)
{
	Matrix Rot = Matrix(ROT_AXIS_ANGLE, vRight, ang);
	vDir = vDir * Rot;
	vUp = vUp * Rot;
	setOrientAndPosition(vUp, vPos - vDir, vPos);
}

void Camera::TurnLeftRight(float ang)
{
	Matrix Rot = Matrix(ROT_Y, ang);
	vDir = vDir * Rot;
	vUp = vUp * Rot;
	setOrientAndPosition(vUp, vPos - vDir, vPos);
}

