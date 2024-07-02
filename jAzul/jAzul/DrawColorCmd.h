#ifndef DRAWCOLORCMD_H
#define DRAWCOLORCMD_H

#include "DrawCommand.h"

class GraphicsObject_Color;

class DrawColorCmd : public DrawCommand
{
public:
	DrawColorCmd();
	DrawColorCmd(const DrawColorCmd& other) = delete;
	DrawColorCmd& operator=(const DrawColorCmd& other) = delete;
	DrawColorCmd(DrawColorCmd&& other) = delete;
	DrawColorCmd& operator=(DrawColorCmd&& other) = delete;
	~DrawColorCmd() = default;

	void SetGO(GraphicsObject_Color* _pGO);

	virtual void Execute() override;

private:
	GraphicsObject_Color* pGO;
};

#endif // DRAWCOLORCMD_H
