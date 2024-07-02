#ifndef GRAPHICOBJECT_COLORLIGHT_H
#define GRAPHICOBJECT_COLORLIGHT_H

#include "GraphicObject_Base.h"

struct Material;

class GraphicsObject_ColorLight : public GraphicsObject_Base
{
public:
	GraphicsObject_ColorLight() = delete;
	GraphicsObject_ColorLight(const GraphicsObject_ColorLight& other) = default;
	GraphicsObject_ColorLight& operator=(const GraphicsObject_ColorLight& other) = default;
	GraphicsObject_ColorLight(GraphicsObject_ColorLight&& other) = default;
	GraphicsObject_ColorLight& operator=(GraphicsObject_ColorLight&& other) = default;
	virtual ~GraphicsObject_ColorLight();

	void SetScale(const float scale);
	void SetWorld(const Matrix& m);
	void SetColor(const Vect& color);
	void SetColor(const unsigned int meshnum, const Vect& color);
	void SetMaterial(const Vect& amb, const Vect& diff, const Vect& sp);
	void SetMaterial(const unsigned int meshNum, const Vect& amb, const Vect& diff, const Vect& sp);
	virtual void Render() override;
	virtual void Draw() override;

	GraphicsObject_ColorLight(Model* mod);

private:
	Material* MeshColors;
	float scale;
};

#endif // GRAPHICOBJECT_COLORLIGHT_H
