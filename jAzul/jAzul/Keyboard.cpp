#include "Keyboard.h"

bool Keyboard::keyStates[KeyStatesLength];

Keyboard::Keyboard() :
	keyBuffer(),
	charBuffer()
{
	for (int i = 0; i < KeyStatesLength; i++) {
		this->keyStates[i] = false;
	}
}

bool Keyboard::GetKeyState(const char c)
{
	return keyStates[int(c)];
}

bool Keyboard::GetKeyState(JAZUL_KEY key)
{
	return keyStates[(int) key];
}

bool Keyboard::KeyBufferIsEmpty()
{
	return this->keyBuffer.empty();
}

bool Keyboard::CharBufferIsEmpty()
{
	return this->charBuffer.empty();
}

KeyboardEvent Keyboard::ReadKey()
{
	if (!this->keyBuffer.empty()) {
		KeyboardEvent e = this->keyBuffer.front(); //Get first Keyboard Event from queue
		this->keyBuffer.pop(); //Remove first item from queue
		return e; //Returns keyboard event
	}
	return KeyboardEvent();
}

unsigned char Keyboard::ReadChar()
{
	if (!this->charBuffer.empty()) {
		unsigned char e = this->charBuffer.front(); //Get first char from queue
		this->charBuffer.pop(); //Remove first char from queue
		return e; //Returns char
	}
	return 0;
}

void Keyboard::OnKeyPressed(const unsigned char key)
{
	this->keyStates[key] = true;
	this->keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Press, key));
}

void Keyboard::OnKeyReleased(const unsigned char key)
{
	this->keyStates[key] = false;
	this->keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Release, key));
}

void Keyboard::OnChar(const unsigned char key)
{
	charBuffer.push(key);
}
