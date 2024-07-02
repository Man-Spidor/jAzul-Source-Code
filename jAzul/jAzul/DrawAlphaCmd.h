#ifndef DRAWALPHACMD_H
#define DRAWALPHACMD_H

#include "DrawCommand.h"

class GraphicsObject_TextureAlpha;

class DrawAlphaCmd : public DrawCommand
{
public:
	DrawAlphaCmd();
	DrawAlphaCmd(const DrawAlphaCmd& other) = default;
	DrawAlphaCmd& operator=(const DrawAlphaCmd& other) = default;
	DrawAlphaCmd(DrawAlphaCmd&& other) = default;
	DrawAlphaCmd& operator=(DrawAlphaCmd&& other) = default;
	~DrawAlphaCmd() = default;

	void SetGO(GraphicsObject_TextureAlpha* _pGO);
	

	virtual void Execute() override;

private:
	GraphicsObject_TextureAlpha* pGO;
};

#endif // DRAWALPHACMD_H
