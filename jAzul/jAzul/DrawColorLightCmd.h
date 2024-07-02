#ifndef DRAWCOLORLIGHTCMD_H
#define DRAWCOLORLIGHTCMD_H

#include "DrawCommand.h"

class GraphicsObject_ColorLight;

class DrawColorLightCmd : public DrawCommand
{
public:
	DrawColorLightCmd();
	DrawColorLightCmd(const DrawColorLightCmd& other) = delete;
	DrawColorLightCmd& operator=(const DrawColorLightCmd& other) = delete;
	DrawColorLightCmd(DrawColorLightCmd&& other) = delete;
	DrawColorLightCmd& operator=(DrawColorLightCmd&& other) = delete;
	~DrawColorLightCmd() = default;

	void SetGO(GraphicsObject_ColorLight* _pGO);

	virtual void Execute() override;

private:
	GraphicsObject_ColorLight* pGO;
};

#endif // DRAWCOLORLIGHTCMD_H
