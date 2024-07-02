#ifndef DRAWSPRITECMD_H
#define DRAWSPRITECMD_H

#include "DrawCommand.h"

class GraphicsObject_Sprite;

class DrawSpriteCmd : public DrawCommand
{
public:
	DrawSpriteCmd();
	DrawSpriteCmd(const DrawSpriteCmd& other) = default;
	DrawSpriteCmd& operator=(const DrawSpriteCmd& other) = default;
	DrawSpriteCmd(DrawSpriteCmd&& other) = default;
	DrawSpriteCmd& operator=(DrawSpriteCmd&& other) = default;
	virtual ~DrawSpriteCmd() = default;

	void SetGO(GraphicsObject_Sprite* _pGO);

	virtual void Execute() override;

private:
	GraphicsObject_Sprite* pGO;
};

#endif // DRAWSPRITECMD_H
