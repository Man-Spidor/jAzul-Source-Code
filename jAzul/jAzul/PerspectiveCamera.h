#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "Camera.h"

/// Represents a perspective camera.
/// 
/// This class provides functionality for a perspective camera, including setting the perspective parameters.
class PerspectiveCamera : public Camera
{
public:
    /// Default constructor.
    PerspectiveCamera();

    /// Copy constructor.
    PerspectiveCamera(const PerspectiveCamera& other) = default;

    /// Copy assignment operator.
    PerspectiveCamera& operator=(const PerspectiveCamera& other) = default;

    /// Move constructor.
    PerspectiveCamera(PerspectiveCamera&& other) = default;

    /// Move assignment operator.
    PerspectiveCamera& operator=(PerspectiveCamera&& other) = default;

    /// Destructor.
    virtual ~PerspectiveCamera() = default;

    /// Set the perspective parameters.
    /// @param FieldOfView_Degs The field of view in degrees.
    /// @param AspectRatio The aspect ratio.
    /// @param NearDist The near distance.
    /// @param FarDist The far distance.
    void setPerspective(const float FieldOfView_Degs, const float AspectRatio, const float NearDist, const float FarDist);

    /// Get the field of view angle.
    /// @return The field of view angle in degrees.
    float getFieldOfView() const { return fovy; }

    /// Get the aspect ratio.
    /// @return The aspect ratio.
    float getAspectRatio() const { return aspectRatio; }

private:
    /// Update the projection matrix.
    virtual void privUpdateProjectionMatrix(void) override;

private:
    float fovy; ///< The field of view angle in degrees.
    float aspectRatio; ///< The aspect ratio.
};

#endif // PERSPECTIVECAMERA_H
