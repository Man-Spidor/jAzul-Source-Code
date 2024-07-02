#include "Mouse.h"

bool Mouse::leftDown; 
bool Mouse::rightDown; 
bool Mouse::middleDown;
MousePoint Mouse::pos = MousePoint(0, 0); 

Mouse::Mouse() :
	eventBuffer()
{
}

void Mouse::OnLeftPressed(int x, int y)
{
	this->leftDown = true;
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::LPress, x, y));
}

void Mouse::OnLeftReleased(int x, int y)
{
	this->leftDown = false;
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::LRelease, x, y));

}

void Mouse::OnRightPressed(int x, int y)
{
	this->rightDown = true;
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::RPress, x, y));
}

void Mouse::OnRightReleased(int x, int y)
{
	this->rightDown = false;
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::RRelease, x, y));
}

void Mouse::OnMiddlePressed(int x, int y)
{
	this->middleDown = true;
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::MPress, x, y));
}

void Mouse::OnMiddleReleased(int x, int y)
{
	this->middleDown = false;
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::MRelease, x, y));
}

void Mouse::OnWheelUp(int x, int y)
{
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelUp, x, y));
}

void Mouse::OnWheelDown(int x, int y)
{
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelDown, x, y));
}

void Mouse::OnMouseMove(int x, int y)
{
	this->pos.x = x;
	this->pos.y = y;
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::Move, x, y));
}

void Mouse::OnMouseMoveRaw(int x, int y)
{
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::RAW_MOVE, x, y));
}

bool Mouse::IsLeftDown() const
{
	return leftDown;
}

bool Mouse::IsRightDown() const
{
	return rightDown;
}

bool Mouse::IsMiddleDown() const
{
	return middleDown;
}

int Mouse::GetPosX() const
{
	return pos.x;
}

int Mouse::GetPosY() const
{
	return pos.y;
}

MousePoint Mouse::GetPos() const
{
	return pos;
}

bool Mouse::EventBufferIsEmpty()
{
	return this->eventBuffer.empty();
}

MouseEvent Mouse::ReadEvent()
{
	if (this->eventBuffer.empty())
	{
		return MouseEvent();
	}
	else
	{
		MouseEvent e = this->eventBuffer.front(); //Get first event from buffer
		this->eventBuffer.pop(); //Remove first event from buffer
		return e;
	}	
}
