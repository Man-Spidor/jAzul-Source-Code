#ifndef FLOOR_H
#define FLOOR_H

class Vect;
class Matrix;
class Texture;
class FlatPlane;
class ShaderTextureLight;
class GraphicsObject_TextureLight;

class Floor
{
public:
	Floor() = delete;
	Floor(const Floor& other) = default;
	Floor& operator=(const Floor& other) = default;
	Floor(Floor&& other) = default;
	Floor& operator=(Floor&& other) = default;
	~Floor();

	Floor(float size, float hrep, float vrep);

	void SetWorld(const Matrix& m);
	void SetTexture(Texture* pTexture);

	void SetMaterial(const Vect& amb, const Vect& diff, const Vect& sp);
	void SetMaterial(const unsigned int meshNum, const Vect& amb, const Vect& diff, const Vect& sp);

	void Render();

private:
	FlatPlane* pPlaneModel;
	GraphicsObject_TextureLight* pPlaneGO;
};

#endif // FLOOR_H
