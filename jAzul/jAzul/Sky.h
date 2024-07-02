#ifndef SKY_H
#define SKY_H

class Matrix;
class Texture;
class SkyBox;
class ShaderTexture;
class GraphicsObject_Texture;

struct ID3D11Device;

class Sky
{
public:
	Sky();
	Sky(const Sky& other) = default;
	Sky& operator=(const Sky& other) = default;
	Sky(Sky&& other) = default;
	Sky& operator=(Sky&& other) = default;
	~Sky();
	

	void SetWorld(const Matrix& m);
	void SetTexture(Texture* pTexture);

	void Render();

private:
	SkyBox* pSkyModel;
	GraphicsObject_Texture* pSkyGO;
};

#endif // SKY_H
