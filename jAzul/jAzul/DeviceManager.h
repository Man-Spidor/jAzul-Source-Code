#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

struct ID3D11Device;

/// Manages the DirectX device.
/// 
/// This singleton class provides functionality to set and retrieve the DirectX device used for rendering.
class DeviceManager
{
    friend class GraphicsAttorney;

public:
    /// Default constructor.
    DeviceManager() = default;

    /// Copy constructor.
    /// @param other The other DeviceManager to copy from.
    DeviceManager(const DeviceManager& other) = default;

    /// Copy assignment operator.
    /// @param other The other DeviceManager to copy from.
    /// @return A reference to this DeviceManager.
    DeviceManager& operator=(const DeviceManager& other) = default;

    /// Move constructor.
    /// @param other The other DeviceManager to move from.
    DeviceManager(DeviceManager&& other) = default;

    /// Move assignment operator.
    /// @param other The other DeviceManager to move from.
    /// @return A reference to this DeviceManager.
    DeviceManager& operator=(DeviceManager&& other) = default;

    /// Destructor.
    ~DeviceManager() = default;

private:
    /// Set the DirectX device.
    /// @param _md3dDevice Pointer to the DirectX device.
    static void SetDevice(ID3D11Device* _md3dDevice);

    /// Get the DirectX device.
    /// @return Pointer to the DirectX device.
    static ID3D11Device* GetDevice();

    static ID3D11Device* md3dDevice; ///< Pointer to the DirectX device.
};

#endif // DEVICEMANAGER_H
