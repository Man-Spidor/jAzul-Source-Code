#include "jAzulRect.h"

jAzulRect::jAzulRect() :
	x(0.0f),
	y(0.0f),
	w(0.0f),
	h(0.0f)
{
}

jAzulRect::jAzulRect(const float _x, const float _y, const float _w, const float _h) :
	x(_x),
	y(_y),
	w(_w),
	h(_h)
{
}

bool jAzulRect::operator==(const jAzulRect& other) const
{
	return	(this->x == other.x) && 
			(this->y == other.y) && 
			(this->w == other.w) && 
			(this->h == other.h);
}

bool jAzulRect::operator!=(const jAzulRect& other) const
{
	return !(*this == other);
}

bool jAzulRect::Contains(float px, float py) const
{
	return (px >= x && px <= x + w && py >= y && py <= y + h);
}

float jAzulRect::Area() const
{
	return w * h;
}

float jAzulRect::Perimeter() const
{
	return 2 * (w + h);
}
