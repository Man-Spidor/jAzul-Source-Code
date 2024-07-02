#include "DrawCmdPool.h"

#include "DrawColorCmd.h"
#include "DrawColorLightCmd.h"
#include "DrawTextureCmd.h"
#include "DrawTextureLightCmd.h"
#include "DrawAlphaCmd.h"
#include "DrawWFCmd.h"
#include "DrawSpriteCmd.h"

DrawCmdPool::~DrawCmdPool()
{
    while (!this->WireframePool.empty()) {
        delete this->WireframePool.top();
        this->WireframePool.pop();
    }

    while (!this->ColorPool.empty()) {
        delete this->ColorPool.top();
        this->ColorPool.pop();
    }

    while (!this->ColorLightPool.empty()) {
        delete this->ColorLightPool.top();
        this->ColorLightPool.pop();
    }

    while (!this->TexturePool.empty()) {
        delete this->TexturePool.top();
        this->TexturePool.pop();
    }

    while (!this->TextureLightPool.empty()) {
        delete this->TextureLightPool.top();
        this->TextureLightPool.pop();
    }

    while (!this->AlphaPool.empty()) {
        delete this->AlphaPool.top();
        this->AlphaPool.pop();
    }

    while (!this->SpritePool.empty()) {
        delete this->SpritePool.top();
        this->SpritePool.pop();
    }
}

DrawWFCmd* DrawCmdPool::GetWFCmd()
{
    DrawWFCmd* pCmd;
    if (this->WireframePool.empty())
        pCmd = new DrawWFCmd();
    
    else {
        pCmd = (DrawWFCmd*) this->WireframePool.top();
        this->WireframePool.pop();
    }

    return pCmd;
}

DrawColorCmd* DrawCmdPool::GetColorCmd()
{
    DrawColorCmd* pCmd;
    if (this->ColorPool.empty())
        pCmd = new DrawColorCmd();

    else {
        pCmd = (DrawColorCmd*) this->ColorPool.top();
        this->ColorPool.pop();
    }

    return pCmd;
}

DrawColorLightCmd* DrawCmdPool::GetColorLightCmd()
{
    DrawColorLightCmd* pCmd;
    if (this->ColorLightPool.empty())
        pCmd = new DrawColorLightCmd();

    else {
        pCmd = (DrawColorLightCmd*) this->ColorLightPool.top();
        this->ColorLightPool.pop();
    }

    return pCmd;
}

DrawTextureCmd* DrawCmdPool::GetTextureCmd()
{
    DrawTextureCmd* pCmd;
    if (this->TexturePool.empty())
        pCmd = new DrawTextureCmd();

    else {
        pCmd = (DrawTextureCmd*) this->TexturePool.top();
        this->TexturePool.pop();
    }

    return pCmd;
}

DrawTextureLightCmd* DrawCmdPool::GetTextureLightCmd()
{
    DrawTextureLightCmd* pCmd;
    if (this->TextureLightPool.empty())
        pCmd = new DrawTextureLightCmd();

    else {
        pCmd = (DrawTextureLightCmd*) this->TextureLightPool.top();
        this->TextureLightPool.pop();
    }

    return pCmd;
}

DrawAlphaCmd* DrawCmdPool::GetTextureAlphaCmd()
{
    DrawAlphaCmd* pCmd;
    if (this->AlphaPool.empty())
        pCmd = new DrawAlphaCmd();

    else {
        pCmd = (DrawAlphaCmd*) this->AlphaPool.top();
        this->AlphaPool.pop();
    }

    return pCmd;
}

DrawSpriteCmd* DrawCmdPool::GetSpriteCmd()
{
    DrawSpriteCmd* pCmd;
    if (this->SpritePool.empty())
        pCmd = new DrawSpriteCmd();

    else {
        pCmd = (DrawSpriteCmd*)this->SpritePool.top();
        this->SpritePool.pop();
    }

    return pCmd;
}

void DrawCmdPool::ReturnCmd(DrawWFCmd* pCmd)
{
    this->WireframePool.push(pCmd);
}

void DrawCmdPool::ReturnCmd(DrawColorCmd* pCmd)
{
    this->ColorPool.push(pCmd);
}

void DrawCmdPool::ReturnCmd(DrawColorLightCmd* pCmd)
{
    this->ColorLightPool.push(pCmd);
}

void DrawCmdPool::ReturnCmd(DrawTextureCmd* pCmd)
{
    this->TexturePool.push(pCmd);
}

void DrawCmdPool::ReturnCmd(DrawTextureLightCmd* pCmd)
{
    this->TextureLightPool.push(pCmd);
}

void DrawCmdPool::ReturnCmd(DrawAlphaCmd* pCmd)
{
    this->AlphaPool.push(pCmd);
}

void DrawCmdPool::ReturnCmd(DrawSpriteCmd* pCmd)
{
    this->SpritePool.push(pCmd);
}
