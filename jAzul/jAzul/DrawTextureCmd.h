#ifndef DRAWTEXTURECMD_H
#define DRAWTEXTURECMD_H

#include "DrawCommand.h"

class GraphicsObject_Texture;

class DrawTextureCmd : public DrawCommand
{
public:
	DrawTextureCmd();
	DrawTextureCmd(const DrawTextureCmd& other) = delete;
	DrawTextureCmd& operator=(const DrawTextureCmd& other) = delete;
	DrawTextureCmd(DrawTextureCmd&& other) = delete;
	DrawTextureCmd& operator=(DrawTextureCmd&& other) = delete;
	virtual ~DrawTextureCmd() = default;

	void SetGO(GraphicsObject_Texture* _pGO);

	virtual void Execute() override;

private:
	GraphicsObject_Texture* pGO;
};

#endif // DRAWTEXTURECMD_H
