#ifndef DRAWCMDPOOL_H
#define DRAWCMDPOOL_H

#include <stack>

class DrawCommand;
class DrawColorCmd;
class DrawColorLightCmd;
class DrawTextureCmd;
class DrawTextureLightCmd;
class DrawAlphaCmd;
class DrawWFCmd;
class DrawSpriteCmd;

class DrawCmdPool
{
public:
	DrawCmdPool() = default;
	DrawCmdPool(const DrawCmdPool& other) = default;
	DrawCmdPool& operator=(const DrawCmdPool& other) = default;
	DrawCmdPool(DrawCmdPool&& other) = default;
	DrawCmdPool& operator=(DrawCmdPool&& other) = default;
	~DrawCmdPool();

	DrawWFCmd* GetWFCmd();
	DrawColorCmd* GetColorCmd();
	DrawColorLightCmd* GetColorLightCmd();
	DrawTextureCmd* GetTextureCmd();
	DrawTextureLightCmd* GetTextureLightCmd();
	DrawAlphaCmd* GetTextureAlphaCmd();
	DrawSpriteCmd* GetSpriteCmd();

	void ReturnCmd(DrawWFCmd*);
	void ReturnCmd(DrawColorCmd*);
	void ReturnCmd(DrawColorLightCmd*);
	void ReturnCmd(DrawTextureCmd*);
	void ReturnCmd(DrawTextureLightCmd*);
	void ReturnCmd(DrawAlphaCmd*);
	void ReturnCmd(DrawSpriteCmd*);

private:
	using CmdPool = std::stack<DrawCommand*>;
	CmdPool ColorPool;
	CmdPool ColorLightPool;
	CmdPool AlphaPool;
	CmdPool SpritePool;
	CmdPool TexturePool;
	CmdPool TextureLightPool;
	CmdPool WireframePool;
};

#endif // DRAWCMDPOOL_H
