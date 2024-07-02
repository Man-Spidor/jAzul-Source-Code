#ifndef DRAWCOMMAND_H
#define DRAWCOMMAND_H

#include "Matrix.h"

class DrawCommand
{
public:
	DrawCommand() = default;
	DrawCommand(const DrawCommand& other) = default;
	DrawCommand& operator=(const DrawCommand& other) = default;
	DrawCommand(DrawCommand&& other) = default;
	DrawCommand& operator=(DrawCommand&& other) = default;
	virtual ~DrawCommand() = default;

	void SetWorld(const Matrix& world);

	virtual void Execute() = 0;

protected:
	Matrix world;
};

#endif // DRAWCOMMAND_H
