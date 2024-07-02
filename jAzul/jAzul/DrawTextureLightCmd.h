#ifndef DRAWTEXTURELIGHTCMD_H
#define DRAWTEXTURELIGHTCMD_H

#include "DrawCommand.h"

class GraphicsObject_TextureLight;

class DrawTextureLightCmd : public DrawCommand
{
public:
	DrawTextureLightCmd();
	DrawTextureLightCmd(const DrawTextureLightCmd& other) = delete;
	DrawTextureLightCmd& operator=(const DrawTextureLightCmd& other) = delete;
	DrawTextureLightCmd(DrawTextureLightCmd&& other) = delete;
	DrawTextureLightCmd& operator=(DrawTextureLightCmd&& other) = delete;
	virtual ~DrawTextureLightCmd() = default;

	void SetGO(GraphicsObject_TextureLight* _pGO);
	
	virtual void Execute() override;

private:
	GraphicsObject_TextureLight* pGO;
};

#endif // DRAWTEXTURELIGHTCMD_H
