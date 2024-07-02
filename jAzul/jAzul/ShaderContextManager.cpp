#include "ShaderContextManager.h"

#include "ShaderColor.h"
#include "ShaderColorLight.h"
#include "ShaderTexture.h"
#include "ShaderTextureLight.h"
#include "ShaderSprite.h"

#include "GraphicsAttorney.h"

ShaderContextManager* ShaderContextManager::instance = nullptr;

ID3D11DeviceContext* ShaderContextManager::pCurrentContext = nullptr; 
ShaderColor* ShaderContextManager::pShaderColor = nullptr;
ShaderColorLight* ShaderContextManager::pShaderColorLight = nullptr;
ShaderTexture* ShaderContextManager::pShaderTex = nullptr;
ShaderTextureLight* ShaderContextManager::pShaderTexLight = nullptr;
ShaderSprite* ShaderContextManager::pShaderSprite = nullptr;

ShaderContextManager::~ShaderContextManager()
{
}

void ShaderContextManager::InitAllShaders(ID3D11DeviceContext*& context)
{
	pCurrentContext = context;
	ID3D11Device* pDevice = GraphicsAttorney::Device::GetDevice();

	pShaderColor = new ShaderColor(pDevice);
	pShaderColor->SetToContext(pCurrentContext);
	pShaderColorLight = new ShaderColorLight(pDevice);
	pShaderColorLight->SetToContext(pCurrentContext);
	pShaderTex = new ShaderTexture(pDevice);
	pShaderTex->SetToContext(pCurrentContext);
	pShaderTexLight = new ShaderTextureLight(pDevice);
	pShaderTexLight->SetToContext(pCurrentContext);
	pShaderSprite = new ShaderSprite(pDevice);
	pShaderSprite->SetToContext(pCurrentContext);
}

void ShaderContextManager::Shutdown()
{
	delete pShaderColor;
	delete pShaderColorLight;
	delete pShaderTex;
	delete pShaderTexLight;
	delete pShaderSprite;

	delete instance;
}

void ShaderContextManager::UpdateContext(ID3D11DeviceContext*& context)
{
	pCurrentContext = context;
}

ID3D11DeviceContext*& ShaderContextManager::GetContext()
{
	return pCurrentContext;
}

void ShaderContextManager::SendCamMatrices(const Matrix& view, const Matrix& proj)
{
	if (pShaderColor)
		pShaderColor->SendCamMatrices(view, proj);

	if (pShaderColorLight)
		pShaderColorLight->SendCamMatrices(view, proj);

	if (pShaderTex)
		pShaderTex->SendCamMatrices(view, proj);

	if (pShaderTexLight)
		pShaderTexLight->SendCamMatrices(view, proj);
}

void ShaderContextManager::Send2DCamMatrices(const Matrix& view, const Matrix& proj)
{
	if (pShaderSprite)
		pShaderSprite->SendCamMatrices(view, proj);
}

void ShaderContextManager::SendLightParams(const Vect& eyePos)
{
	if (pShaderColorLight)
		pShaderColorLight->SendLightParameters(eyePos);

	if (pShaderTex)
		pShaderTex->SetEyePos(eyePos);

	if (pShaderTexLight)
		pShaderTexLight->SendLightParameters(eyePos);	
}

void ShaderContextManager::SendScreenSize(const unsigned int width, const unsigned int height)
{
	pShaderSprite->SetScreenSize(width, height);
}

void ShaderContextManager::SetFogData(const float FogStart, const float FogRange, const Vect& FogColor)
{
	if (pShaderColorLight) {
		pShaderColorLight->SetFogData(FogStart, FogRange, FogColor);
		pShaderColorLight->SendFogData();
	}

	if (pShaderTex) {
		pShaderTex->SetFogData(FogStart, FogRange, FogColor);
		pShaderTex->SendFogData();
	}

	if (pShaderTexLight) {
		pShaderTexLight->SetFogData(FogStart, FogRange, FogColor);
		pShaderTexLight->SendFogData();
	}
}

void ShaderContextManager::SetDirectionalLightParameters(LIGHTNUM ln, const DirectionalLight* pLight)
{
	if (pShaderColorLight)
		pShaderColorLight->SetDirectionalLightParameters(	ln, pLight->Direction, 
															pLight->Light.Ambient, 
															pLight->Light.Diffuse, 
															pLight->Light.Specular);

	if (pShaderTexLight)
		pShaderTexLight->SetDirectionalLightParameters(		ln, pLight->Direction, 
															pLight->Light.Ambient, 
															pLight->Light.Diffuse, 
															pLight->Light.Specular);
}

void ShaderContextManager::SetPointLightParameters(LIGHTNUM ln, const PointLight* pLight)
{
	if (pShaderColorLight)
		pShaderColorLight->SetPointLightParameters(	ln, pLight->Position, pLight->Range, pLight->Attenuation,
													pLight->Light.Ambient, 
													pLight->Light.Diffuse, 
													pLight->Light.Specular);

	if (pShaderTexLight)
		pShaderTexLight->SetPointLightParameters(	ln, pLight->Position, pLight->Range, pLight->Attenuation,
													pLight->Light.Ambient, 
													pLight->Light.Diffuse, 
													pLight->Light.Specular);
}

void ShaderContextManager::SetSpotLightParameters(LIGHTNUM ln, const SpotLight* pLight)
{
	if (pShaderColorLight)
		pShaderColorLight->SetSpotLightParameters(	ln, pLight->Position, pLight->Range, pLight->Attenuation, pLight->Direction, pLight->SpotExp,
													pLight->Light.Ambient, 
													pLight->Light.Diffuse, 
													pLight->Light.Specular);

	if (pShaderTexLight)
		pShaderTexLight->SetSpotLightParameters(	ln, pLight->Position, pLight->Range, pLight->Attenuation, pLight->Direction, pLight->SpotExp,
													pLight->Light.Ambient, 
													pLight->Light.Diffuse, 
													pLight->Light.Specular);
}

void ShaderContextManager::SendColorParams(const Matrix& world, const Vect& col, const float scale)
{
	assert(pShaderColor);
	UNREFERENCED_PARAMETER(scale);
	pShaderColor->SendWorldColor(world, col);
}

void ShaderContextManager::SendColorLightParams(const Matrix& world, const Vect& amb, const Vect& dif, const Vect& sp, const float scale)
{
	assert(pShaderColorLight);
	pShaderColorLight->SendWorldAndMaterial(world, amb, dif, sp, scale);
}

void ShaderContextManager::SendTextureParams(const Matrix& world, const float scale)
{
	assert(pShaderTex);
	UNREFERENCED_PARAMETER(scale);
	pShaderTex->SendWorld(world);
}

void ShaderContextManager::SendTextureLightParams(const Matrix& world, const Vect& amb, const Vect& dif, const Vect& sp, const float scale)
{
	assert(pShaderTexLight);
	pShaderTexLight->SendWorldAndMaterial(world, amb, dif, sp, scale);
}

void ShaderContextManager::SendSpriteParams(const Matrix& pos, float texWidth, float texHeight, const jAzulRect& pImgRect)
{
	pShaderSprite->SendWorld(pos,texWidth, texHeight, pImgRect);
}

void ShaderContextManager::SetColorToContext()
{
	pShaderColor->SetToContext(pCurrentContext);
}

void ShaderContextManager::SetColorLightToContext()
{
	pShaderColorLight->SetToContext(pCurrentContext);
}

void ShaderContextManager::SetTextureToContext()
{
	pShaderTex->SetToContext(pCurrentContext);
}

void ShaderContextManager::SetTextureLightToContext()
{
	pShaderTexLight->SetToContext(pCurrentContext);
}

void ShaderContextManager::SetSpriteToContext()
{
	pShaderSprite->SetToContext(pCurrentContext);
}

ShaderContextManager& ShaderContextManager::Instance()
{
	if (!instance) {
		instance = new ShaderContextManager();
	}
	return *instance;
}
