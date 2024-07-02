#include "DeviceManager.h"

ID3D11Device* DeviceManager::md3dDevice = nullptr;

void DeviceManager::SetDevice(ID3D11Device* _md3dDevice)
{
	md3dDevice = _md3dDevice;
}

ID3D11Device* DeviceManager::GetDevice()
{
	return md3dDevice;
}

