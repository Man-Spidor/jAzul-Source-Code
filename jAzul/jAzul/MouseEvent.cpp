#include "MouseEvent.h"

MouseEvent::MouseEvent() :
	type(EventType::Invalid),
	pos(-1, -1)
{
}

MouseEvent::MouseEvent(const EventType _type, const int x, const int y) :
	type(_type),
	pos(x, y)
{
}

const MouseEvent::EventType MouseEvent::GetType() const
{
	return this->type;
}

const MousePoint MouseEvent::GetPos() const
{
	return this->pos;
}

const bool MouseEvent::IsValid() const
{
	return type != MouseEvent::EventType::Invalid;
}

const int MouseEvent::GetPosX() const
{
	return pos.x;
}

const int MouseEvent::GetPosY() const
{
	return pos.y;
}
