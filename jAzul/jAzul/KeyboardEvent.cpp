#include "KeyboardEvent.h"

KeyboardEvent::KeyboardEvent() :
	type(EventType::Invalid),
	key()
{
}

KeyboardEvent::KeyboardEvent(const EventType _type, const unsigned char _key) :
	type(_type),
	key(_key)
{
}

const bool KeyboardEvent::isPress() const
{
	return this->type == EventType::Press;
}

const bool KeyboardEvent::isRelease() const
{
	return this->type == EventType::Release;
}

const bool KeyboardEvent::isValid() const
{
	return this->type != EventType::Invalid;
}

const unsigned char KeyboardEvent::GetKeyCode() const
{
	return this->key;
}
