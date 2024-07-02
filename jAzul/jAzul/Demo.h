#ifndef DEMO_H
#define DEMO_H

// New includes for demo
#include "Vect.h"
#include "Matrix.h"
#include "PerspectiveCamera.h"

class Sky;
class Model;
class Walls;
class Floor;
class SkyBox;
class Terrain;
class Texture;
class FlatPlane;
class GraphicsObject_Color;
class GraphicsObject_Sprite;
class GraphicsObject_Texture;
class GraphicsObject_Wireframe;
class GraphicsObject_ColorLight;
class GraphicsObject_TextureLight;

struct DirectionalLight;
struct PointLight;
struct SpotLight;

class Demo
{
public:
	Demo() = default;
	Demo(const Demo& other) = default;
	Demo& operator=(const Demo& other) = default;
	Demo(Demo&& other) = default;
	Demo& operator=(Demo&& other) = default;
	~Demo();

	void Initialize();

	void Update();
	void Draw();

	Camera* getCam();
	Camera* getCam2D();

private:
	// Demo specific additions
	PerspectiveCamera mCam;
	PerspectiveCamera Cam2D;

	// Add any Textures, Graphics Objects, and Shaders here:
	// Matrices
	Matrix BusStopPos;
	Matrix BusSignPos;
	Matrix StreetSignPos;
	Matrix LampPostPos1;
	Matrix LampPostPos2;
	Matrix TreeOrient;

	// Textures:
	Texture* pBusSignTex;
	Texture* pBusStopTex;
	Texture* pGlassTex;
	Texture* pStreetSignTex;
	Texture* pTerrainTex;
	Texture* pBusStopFloorTex;
	Texture* pSkyBoxTex;
	Texture* pLampPostTex;
	Texture* pTreeTex1;
	Texture* pStitchTex;

	// Models:
	Model* pBusStopModel;
	Model* pBusSignModel;
	Model* pStreeSignModel;
	Model* pLampPostModel1;
	Model* pTreeModel;
	Model* pCube;
	Model* pSphere;
	Model* pPyramid;
	Model* pUnitSquare;
	Model* pUnitBSphere;

	// GraphicObject_Color:
	GraphicsObject_Color*		 pColorGO;
	GraphicsObject_Texture*		 pTexGO;
	GraphicsObject_TextureLight* pBusStopGO;
	GraphicsObject_TextureLight* pBusSignGO;
	GraphicsObject_TextureLight* pStreetSignGO;
	GraphicsObject_TextureLight* pLampPostGO1;
	GraphicsObject_TextureLight* pLampPostGO2;
	GraphicsObject_TextureLight* pTreeGO1;
	GraphicsObject_TextureLight* pTreeGO2;
	GraphicsObject_Sprite* pStitchGO;
	GraphicsObject_Wireframe* pBSphere;

	// "GameObjects"
	Terrain* pTerrain;
	Floor* pBusStopFloor;
	Sky* pSky;

	// Lights
	DirectionalLight* pDirLight;
	PointLight* pPointLight;
	SpotLight** pSpotLight;

	// Etc.
	float TreeScale;
	Vect FogColor;

};

#endif // DEMO_H
