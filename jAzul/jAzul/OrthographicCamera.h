#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H

#include "Camera.h"

/// Represents an orthographic camera.
/// 
/// This class provides functionality for an orthographic camera, including setting the orthographic parameters.
class OrthographicCamera : public Camera
{
public:
    /// Default constructor.
    OrthographicCamera();

    /// Copy constructor.
    OrthographicCamera(const OrthographicCamera& other) = default;

    /// Copy assignment operator.
    OrthographicCamera& operator=(const OrthographicCamera& other) = default;

    /// Move constructor.
    OrthographicCamera(OrthographicCamera&& other) = default;

    /// Move assignment operator.
    OrthographicCamera& operator=(OrthographicCamera&& other) = default;

    /// Destructor.
    virtual ~OrthographicCamera() = default;

    /// Set the orthographic parameters.
    /// @param xMin The minimum x value.
    /// @param xMax The maximum x value.
    /// @param yMin The minimum y value.
    /// @param yMax The maximum y value.
    /// @param zMin The minimum z value.
    /// @param zMax The maximum z value.
    void setOrthographic(const float xMin, const float xMax, const float yMin, const float yMax, const float zMin, const float zMax);

    /// Get the orthographic width.
    /// @return The orthographic width.
    float getOrthographicWidth() const { return right - left; }

    /// Get the orthographic height.
    /// @return The orthographic height.
    float getOrthographicHeight() const { return top - bottom; }

private:
    /// Update the projection matrix.
    virtual void privUpdateProjectionMatrix(void) override;

private:
    float left; ///< The left value for the orthographic projection.
    float right; ///< The right value for the orthographic projection.
    float top; ///< The top value for the orthographic projection.
    float bottom; ///< The bottom value for the orthographic projection.
    float zNear; ///< The near value for the orthographic projection.
    float zFar; ///< The far value for the orthographic projection.
};

#endif // ORTHOGRAPHICCAMERA_H
