#include "Demo.h"

#include "Sky.h"
#include "Model.h"
#include "Floor.h"
#include "DirectXTex.h"
#include "Texture.h"
#include "FlatPlane.h"
#include "Terrain.h"
#include "GraphicObject_Color.h"
#include "GraphicsObject_Sprite.h"
#include "GraphicsObject_Texture.h"
#include "GraphicsObject_Wireframe.h"
#include "GraphicsObject_TextureLight.h"
#include "GraphicObject_ColorLight.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "jAzulRect.h"
#include "Image.h"

#include "ShaderContextManager.h"
#include "d3dUtil.h"
#include "Engine.h"

Demo::~Demo()
{
	// Textures:
	delete this->pBusSignTex;
	delete this->pBusStopTex;
	delete this->pGlassTex;
	delete this->pStreetSignTex;
	delete this->pTerrainTex;
	delete this->pBusStopFloorTex;
	delete this->pSkyBoxTex;
	delete this->pLampPostTex;
	delete this->pTreeTex1;

	// Models:
	delete this->pBusStopModel;
	delete this->pBusSignModel;
	delete this->pStreeSignModel;
	delete this->pLampPostModel1;
	delete this->pTreeModel;
	delete this->pCube;
	delete this->pUnitSquare;

	// GraphicObject_Color:
	delete this->pBusStopGO;
	delete this->pBusSignGO;
	delete this->pStreetSignGO;
	delete this->pLampPostGO1;
	delete this->pLampPostGO2;
	delete this->pTreeGO1;
	delete this->pTreeGO2;
	delete this->pTexGO;
	delete this->pColorGO;

	// "GameObjects"
	delete this->pTerrain;
	delete this->pBusStopFloor;
	delete this->pSky;

	// Sprite stuff
	delete this->pStitchTex;

	// Lights
	delete this->pDirLight;
	delete this->pPointLight;
	delete this->pSpotLight[0];
	delete this->pSpotLight[1];
	delete this->pSpotLight[2];
	delete this->pSpotLight[3];
	delete[] this->pSpotLight;
}

void Demo::Initialize()
{
//	ShaderContextManager::InitShader(ShaderType::COLOR);
//	ShaderContextManager::InitShader(ShaderType::COLOR_LIGHT);
//	ShaderContextManager::InitShader(ShaderType::TEXTURE);
//	ShaderContextManager::InitShader(ShaderType::TEXTURE_LIGHT);
//	ShaderContextManager::InitShader(ShaderType::SPRITE);
//
//	this->pUnitSquare = new Model(Model::UnitSqaureXY);
//	this->pStitchTex = new Texture(L"../Assets/Textures/Stitch.tga");
//
//	// Initialize everything here...
//	this->TreeScale = 0.025f;
//	this->FogColor = Vect(61.0f / 255.0f, 68.0f / 255.0f, 86.f / 255.0f);
//	// this->FogColor = Colors::Gray;
//	// this->FogColor = Colors::MidnightBlue;
//
//	this->BusStopPos = Matrix(ROT_X, -3.14159265558972f / 2.0f) * Matrix(TRANS, 0.0f, 31.0f, 0.0f);
//	this->BusSignPos =  Matrix(ROT_X, -3.14159265558972f / 2.0f) * Matrix(TRANS, 4.0f, 31.0f, 0.5f);
//	this->StreetSignPos = Matrix(ROT_X, -3.14159265558972f / 2.0f) * Matrix(TRANS, -3.0f, 29.0f, 0.5f);
//	this->LampPostPos1 = Matrix(ROT_X, -3.14159265558972f / 2.0f) * Matrix(ROT_Y, -3.14159265558972f / 2.0f) * Matrix(TRANS, -15.0f, 29.0f, 0.5f);
//	this->LampPostPos2 = Matrix(ROT_X, -3.14159265558972f / 2.0f) * Matrix(ROT_Y, -3.14159265558972f / 2.0f) * Matrix(ROT_Z, 0.2f) * Matrix(TRANS, 15.0f, 29.0f, 0.5f);
//	this->TreeOrient = Matrix(SCALE, this->TreeScale, this->TreeScale, this->TreeScale) * Matrix(ROT_X, 3.14159265558972f );
//		
//	this->pBusSignTex = new Texture(L"../Assets/Textures/BusStop01.tga");
//	this->pBusStopTex = new Texture(L"../Assets/Textures/BusSign.tga");
//	this->pGlassTex = new Texture(L"../Assets/Textures/Glass.tga");
//	this->pStreetSignTex = new Texture(L"../Assets/Textures/BusStopSign.tga");
//	this->pTerrainTex = new Texture(L"../Assets/Textures/Grass.tga");
//	this->pBusStopFloorTex = new Texture(L"../Assets/Textures/Concrete.tga");
//	this->pSkyBoxTex = new Texture(L"../Assets/Textures/skybox_texture.tga");
//	this->pLampPostTex = new Texture(L"../Assets/Textures/Lamppost.tga");
//
//	this->pTreeTex1 = new Texture(L"../Assets/Textures/tree01_fall.tga", D3D11_FILTER_MIN_MAG_MIP_LINEAR, 4, false, 0, DirectX::TEX_FILTER_DEFAULT);
//
//	this->pBusStopModel = new Model("../Assets/Models/BusStop.azul");
//	this->pBusSignModel = new Model("../Assets/Models/BusSign.azul");
//	this->pStreeSignModel = new Model("../Assets/Models/StreetSign.azul");
//	this->pLampPostModel1 = new Model("../Assets/Models/LampPost1.azul");
//	this->pTreeModel = new Model("../Assets/Models/tree01.azul");
//	this->pCube = new Model(Model::UnitBox);
//	this->pUnitBSphere = new Model(Model::UnitSphere);
//
//	this->pBusStopGO = new GraphicsObject_TextureLight(this->pBusStopModel);
//	this->pBusStopGO->SetMaterial(Vect(0.050876f, 0.050876f, 0.050876f), Vect(0.8, 0.8, 0.8), Vect(0.8f, 0.8f, 0.8f, 15));
//	this->pBusStopGO->SetWorld(this->BusStopPos);
//	this->pBusStopGO->SetTexture(0, this->pBusStopTex);
//	this->pBusStopGO->SetTexture(1, this->pGlassTex);
//	this->pBusStopGO->SetTexture(2, this->pGlassTex);
//
//	this->pBusSignGO = new GraphicsObject_TextureLight(this->pBusSignModel);
//	this->pBusSignGO->SetMaterial(Vect(0.050876f, 0.050876f, 0.050876f), Vect(0.8, 0.8, 0.8), Vect(0.8f, 0.8f, 0.8f, 15));
//	this->pBusSignGO->SetWorld(this->BusSignPos);
//	this->pBusSignGO->SetTexture(this->pBusSignTex);
//
//	this->pStreetSignGO = new GraphicsObject_TextureLight(this->pStreeSignModel);
//	this->pStreetSignGO->SetMaterial(Vect(0.050876f, 0.050876f, 0.050876f), Vect(0.8, 0.8, 0.8), Vect(0.8f, 0.8f, 0.8f, 15));
//	this->pStreetSignGO->SetWorld(this->StreetSignPos);
//	this->pStreetSignGO->SetTexture(this->pStreetSignTex);
//
//	this->pLampPostGO1 = new GraphicsObject_TextureLight(this->pLampPostModel1);
//	this->pLampPostGO1->SetMaterial(Vect(0.050876f, 0.050876f, 0.050876f), Vect(0.8, 0.8, 0.8), Vect(0.8f, 0.8f, 0.8f, 15));
//	this->pLampPostGO1->SetWorld(this->LampPostPos1);
//	this->pLampPostGO1->SetTexture(this->pLampPostTex);
//
//	this->pLampPostGO2 = new GraphicsObject_TextureLight(this->pLampPostModel1);
//	this->pLampPostGO2->SetMaterial(Vect(0.050876f, 0.050876f, 0.050876f), Vect(0.8, 0.8, 0.8), Vect(0.8f, 0.8f, 0.8f, 15));
//	this->pLampPostGO2->SetWorld(this->LampPostPos2);
//	this->pLampPostGO2->SetTexture(this->pLampPostTex);
//		
//	this->pTreeGO1 = new GraphicsObject_TextureLight(this->pTreeModel);
//	this->pTreeGO1->SetMaterial(Colors::ForestGreen, Colors::ForestGreen, Vect(1, 1, 1));
//	this->pTreeGO1->SetWorld(this->TreeOrient * Matrix(TRANS, -10.0f, 35.0f, 0.0f));
//	this->pTreeGO1->SetTexture(this->pTreeTex1);
//	this->pTreeGO1->SetScale(this->TreeScale);
//
//	this->pTreeGO2 = new GraphicsObject_TextureLight(this->pTreeModel);
//	this->pTreeGO2->SetMaterial(Colors::ForestGreen, Colors::ForestGreen, Vect(1, 1, 1));
//	this->pTreeGO2->SetWorld(this->TreeOrient * Matrix(TRANS, -2.0f, 35.0f, -12.0f));
//	this->pTreeGO2->SetTexture(this->pTreeTex1);
//	this->pTreeGO2->SetScale(this->TreeScale);
//
//	this->pTerrain = new Terrain(L"../Assets/Textures/HeightmapIsland.tga", 2000, 300, 300, 10, 10);
//	this->pTerrain->SetWorld(Matrix(IDENTITY));
//	this->pTerrain->SetTexture(this->pTerrainTex);
//	this->pTerrain->SetMaterial(Colors::ForestGreen, Colors::ForestGreen, Vect(1, 1, 1));
//
//	this->pBusStopFloor = new Floor(10, 1, 1);
//	this->pBusStopFloor->SetWorld(Matrix(ROT_X, 3.14159265558972f / 2.0f) * this->BusStopPos * Matrix(TRANS, 0.0f, -1.8f, 0.0f));
//	this->pBusStopFloor->SetTexture(this->pBusStopFloorTex);
//	this->pBusStopFloor->SetMaterial(Vect(0.050876f, 0.050876f, 0.050876f), Vect(0.8, 0.8, 0.8), Vect(0.8f, 0.8f, 0.8f, 15));
//
//	this->pSky = new Sky();
//	this->pSky->SetWorld(Matrix(IDENTITY) * Matrix(SCALE, 2000.0f, 2000.0f, 2000.0f));
//	this->pSky->SetTexture(this->pSkyBoxTex);
//
//	this->pTexGO = new GraphicsObject_Texture(this->pUnitSquare);
//	this->pTexGO->SetWorld(Matrix(IDENTITY));
//	this->pTexGO->SetTexture(this->pStitchTex);
//
//	this->pColorGO = new GraphicsObject_Color(this->pUnitSquare);
//	this->pColorGO->SetWorld(Matrix(IDENTITY));
//	this->pColorGO->SetColor(Colors::Black);
//	
//	this->pBSphere = new GraphicsObject_Wireframe(this->pCube);
//	this->pBSphere->SetColor(Colors::GreenYellow);
//	this->pBSphere->SetWorld(this->BusStopPos);
//
//	this->pDirLight = new DirectionalLight();
//	this->pDirLight->Direction = Vect(0.0f, -1.0f, 0.0f).getNorm();
//	this->pDirLight->Light.Ambient = .25 * Vect(1, 1, 1);
//	this->pDirLight->Light.Diffuse = .25 * Vect(1, 1, 1);
//	this->pDirLight->Light.Specular = Vect(1, 1, 1);
//
//	this->pPointLight = new PointLight();
//	this->pPointLight->Position = this->BusStopPos.get(ROW_3) + Vect(0, 2, 0);
//	this->pPointLight->Range = 5.0f;
//	this->pPointLight->Attenuation = .1 * Vect(0, 1, 0);
//	this->pPointLight->Light.Ambient = .25 * Vect(1, 1, 1);
//	this->pPointLight->Light.Diffuse = .25 * Vect(1, 1, 1);
//	this->pPointLight->Light.Specular = Vect(1, 1, 1);
//
//	this->pSpotLight = new SpotLight*[4];
//
//	this->pSpotLight[0] = new SpotLight();
//	this->pSpotLight[0]->Position = this->LampPostPos1.get(ROW_3) + Vect(2.0f, 10.0f, 0.0f);
//	this->pSpotLight[0]->Range = 4000.0f;
//	this->pSpotLight[0]->Attenuation = .1 * Vect(0, 1, 0);
//	this->pSpotLight[0]->Direction = Vect(0.0f, -1.0f, 0.0f);
//	this->pSpotLight[0]->SpotExp = 50.0f;
//	this->pSpotLight[0]->Light.Ambient = .25 * Vect(1, 1, 1);
//	this->pSpotLight[0]->Light.Diffuse = .25 * Vect(1, 1, 1);
//	this->pSpotLight[0]->Light.Specular = Vect(1, 1, 1);
//
//	this->pSpotLight[1] = new SpotLight();
//	this->pSpotLight[1]->Position = this->LampPostPos1.get(ROW_3) + Vect(-2.0f, 10.0f, 0.0f);
//	this->pSpotLight[1]->Range = 4000.0f;
//	this->pSpotLight[1]->Attenuation = .1 * Vect(0, 1, 0);
//	this->pSpotLight[1]->Direction = Vect(0.0f, -1.0f, 0.0f);
//	this->pSpotLight[1]->SpotExp = 50.0f;
//	this->pSpotLight[1]->Light.Ambient = .25 * Vect(1, 1, 1);
//	this->pSpotLight[1]->Light.Diffuse = .25 * Vect(1, 1, 1);
//	this->pSpotLight[1]->Light.Specular = Vect(1, 1, 1);
//
//	this->pSpotLight[2] = new SpotLight();
//	this->pSpotLight[2]->Position = this->LampPostPos2.get(ROW_3) + Vect(-4.0f, 10.0f, 0.0f);
//	this->pSpotLight[2]->Range = 4000.0f;
//	this->pSpotLight[2]->Attenuation = .1 * Vect(0, 1, 0);
//	this->pSpotLight[2]->Direction = Vect(0.0f, -1.0f, 0.0f);
//	this->pSpotLight[2]->SpotExp = 50.0f;
//	this->pSpotLight[2]->Light.Ambient = .25 * Vect(1, 1, 1);
//	this->pSpotLight[2]->Light.Diffuse = .25 * Vect(1, 1, 1);
//	this->pSpotLight[2]->Light.Specular = Vect(1, 1, 1);
//
//	this->pSpotLight[3] = new SpotLight();
//	this->pSpotLight[3]->Position = this->LampPostPos2.get(ROW_3) + Vect(0.0f, 10.0f, 0.0f);
//	this->pSpotLight[3]->Range = 4000.0f;
//	this->pSpotLight[3]->Attenuation = .1 * Vect(0, 1, 0);
//	this->pSpotLight[3]->Direction = Vect(0.0f, -1.0f, 0.0f);
//	this->pSpotLight[3]->SpotExp = 50.0f;
//	this->pSpotLight[3]->Light.Ambient = .25f * Vect(1, 1, 1);
//	this->pSpotLight[3]->Light.Diffuse = .25f * Vect(1, 1, 1);
//	this->pSpotLight[3]->Light.Specular = Vect(1, 1, 1);
//
//	ShaderContextManager::SetFogData(10.0f, 35.0f, this->FogColor);
//
//	ShaderContextManager::SetDirectionalLightParameters(LIGHTNUM::LIGHT_1, this->pDirLight);
//	ShaderContextManager::SetPointLightParameters(LIGHTNUM::LIGHT_1, this->pPointLight);
//	ShaderContextManager::SetSpotLightParameters(LIGHTNUM::LIGHT_1, this->pSpotLight[0]);
//	ShaderContextManager::SetSpotLightParameters(LIGHTNUM::LIGHT_2, this->pSpotLight[1]);
//	ShaderContextManager::SetSpotLightParameters(LIGHTNUM::LIGHT_3, this->pSpotLight[2]);
//	ShaderContextManager::SetSpotLightParameters(LIGHTNUM::LIGHT_4, this->pSpotLight[3]);
//
//	// Initialize the projection matrix
//	mCam.setPerspective( 3.14159/3, (float)Engine::GetWidth() / (float)Engine::GetHeight(), 1.0f, 3000.0f);
//	mCam.setOrientAndPosition(Vect(0.0f, 1.0f, 0.0f), Vect(0.9f, 0.0f, 1.0f), Vect(20.0f, 32.0f, 15.0f));
//	mCam.TiltUpDown(3.14159f / 3.0f);
//	
//	this->Cam2D.setPerspective(3.14159 / 3, (float)Engine::GetWidth() / (float)Engine::GetHeight(), 1.0f, 3000.0f);
//	this->Cam2D.setOrientAndPosition(Vect(0, 1, 0), Vect(0, 0, 1), Vect(0, 3, -5));
//
//	// SPRITE TESTS HAPPENING HERE:
//	jAzulRect* pRect = new jAzulRect(0.0f, 0.0f, this->pStitchTex->getWidth(), this->pStitchTex->getHeight());
//	Image* pImage = new Image();
//	pImage->Set(this->pStitchTex, pRect);
//	
//	this->pStitchGO = new GraphicsObject_Sprite(this->pUnitSquare, pImage, new jAzulRect(150.0f, 500.0f, 100.0f, 100.0f));
//	this->pStitchGO->SetWorld(Matrix(IDENTITY));
//	
//	this->Cam2D.updateCamera();
}

void Demo::Update()
{
	float camSpeed = 0.25f;
	if (Keyboard::GetKeyState('W'))
	{
		mCam.TranslateFwdBack(camSpeed);
	}
	else if (Keyboard::GetKeyState('S'))
	{
		mCam.TranslateFwdBack(-camSpeed);
	}

	if (Keyboard::GetKeyState('A'))
	{
		mCam.TranslateLeftRight(-camSpeed);
	}
	else if (Keyboard::GetKeyState('D'))
	{
		mCam.TranslateLeftRight(camSpeed);
	}

	float rotSpeed = 0.025f;
	if (GetKeyState(VK_LEFT) & 0x08000)
	{
		mCam.TurnLeftRight(rotSpeed);
	}
	else if (GetKeyState(VK_RIGHT) & 0x08000)
	{
		mCam.TurnLeftRight(-rotSpeed);
	}

	if (GetKeyState(VK_UP) & 0x08000)
	{
		mCam.TiltUpDown(rotSpeed);
	}
	else if (GetKeyState(VK_DOWN) & 0x08000)
	{
		mCam.TiltUpDown(-rotSpeed);
	}

	mCam.updateCamera();
}

void Demo::Draw()
{
	// this->pSky->Render();
	this->pTreeGO1->Render();
	this->pTreeGO2->Render();

	this->pTexGO->Render();
	this->pBusStopGO->Render();

	this->pLampPostGO1->Render();
	this->pLampPostGO2->Render();

	this->pTerrain->Render();

	this->pBusSignGO->Render();
	this->pStreetSignGO->Render();
	this->pBusStopFloor->Render();

	this->pColorGO->Render();

	// this->pStitchGO->Render();

	this->pBSphere->Render();
}

Camera* Demo::getCam() 
{
	return &this->mCam;
}

Camera* Demo::getCam2D()
{
	return &this->Cam2D;
}
