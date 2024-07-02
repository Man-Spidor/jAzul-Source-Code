#ifndef CAMERA_H
#define CAMERA_H

#include "Vect.h"
#include "Matrix.h"

/// Base class for camera management.
/// 
/// This class provides the basic functionality for a camera, including setting orientation and position,
/// updating the camera, and retrieving the view and projection matrices.
class Camera
{
public:
    /// Default constructor.
    Camera();

    /// Copy constructor.
    Camera(const Camera& other) = default;

    /// Copy assignment operator.
    Camera& operator=(const Camera& other) = default;

    /// Move constructor.
    Camera(Camera&& other) = default;

    /// Move assignment operator.
    Camera& operator=(Camera&& other) = default;

    /// Destructor.
    virtual ~Camera() = default;

    /// Set the orientation and position of the camera.
    /// @param Up_vect The up vector.
    /// @param inLookAt_pt The look-at point.
    /// @param pos_pt The position point.
    void setOrientAndPosition(const Vect& Up_vect, const Vect& inLookAt_pt, const Vect& pos_pt);

    /// Update the camera system.
    virtual void updateCamera(void);

    /// Get the view matrix for rendering.
    /// @return Reference to the view matrix.
    Matrix& getViewMatrix();

    /// Get the projection matrix for rendering.
    /// @return Reference to the projection matrix.
    Matrix& getProjMatrix();

    /// Accessors for camera properties.
    void getPos(Vect& outPos) const;
    void getDir(Vect& outDir) const;
    void getUp(Vect& outUp) const;
    void getLookAt(Vect& outLookAt) const;
    void getRight(Vect& outRight) const;

    /// Translate the camera left or right.
    /// @param delta The translation amount.
    void TranslateLeftRight(float delta);

    /// Translate the camera forward or backward.
    /// @param delta The translation amount.
    void TranslateFwdBack(float delta);

    /// Tilt the camera up or down.
    /// @param ang The tilt angle in degrees.
    void TiltUpDown(float ang);

    /// Turn the camera left or right.
    /// @param ang The turn angle in degrees.
    void TurnLeftRight(float ang);

protected:
    /// Update the projection matrix (virtual).
    virtual void privUpdateProjectionMatrix(void) = 0;

    /// Update the view matrix.
    virtual void privUpdateViewMatrix(void);

protected:
    Matrix projMatrix; ///< The projection matrix.
    Matrix viewMatrix; ///< The view matrix.

    Vect vUp; ///< The up vector.
    Vect vDir; ///< The direction vector.
    Vect vRight; ///< The right vector.
    Vect vPos; ///< The position vector.
    Vect vLookAt; ///< The look-at vector.

    float nearDist; ///< The near distance for the frustum.
    float farDist; ///< The far distance for the frustum.
};

#endif // CAMERA_H
