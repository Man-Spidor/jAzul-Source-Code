#ifndef TERRAIN_H
#define TERRAIN_H

class Vect;
class Matrix;
class Texture;
class TerrainModel;
class ShaderTextureLight;
class GraphicsObject_TextureLight;

class Terrain
{
public:
	Terrain() = delete;
	Terrain(const Terrain& other) = default;
	Terrain& operator=(const Terrain& other) = default;
	Terrain(Terrain&& other) = default;
	Terrain& operator=(Terrain&& other) = default;
	~Terrain();

	Terrain(LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV);

	void SetWorld(const Matrix& m);
	void SetTexture(Texture* pTexture);

	void SetMaterial(const Vect& amb, const Vect& diff, const Vect& sp);
	void SetMaterial(const unsigned int meshNum, const Vect& amb, const Vect& diff, const Vect& sp);

	void Render();

private:
	TerrainModel* pTerrainModel;
	GraphicsObject_TextureLight* pTerrainGO;
};

#endif // TERRAIN_H
