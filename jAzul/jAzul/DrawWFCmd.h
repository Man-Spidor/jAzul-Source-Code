#ifndef DRAWWFCMD_H
#define DRAWWFCMD_H

#include "DrawCommand.h"

class GraphicsObject_Wireframe;

class DrawWFCmd : public DrawCommand
{
public:
	DrawWFCmd();
	DrawWFCmd(const DrawWFCmd& other) = default;
	DrawWFCmd& operator=(const DrawWFCmd& other) = default;
	DrawWFCmd(DrawWFCmd&& other) = default;
	DrawWFCmd& operator=(DrawWFCmd&& other) = default;
	virtual ~DrawWFCmd() = default;

	void SetGO(GraphicsObject_Wireframe* _pGO);

	virtual void Execute() override;

private:
	Vect color;
	GraphicsObject_Wireframe* pGO;
};

#endif // DRAWWFCMD_H
