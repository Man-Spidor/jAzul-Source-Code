#include "Image.h"
#include "jAzulRect.h"

Image::Image() :
	pText(nullptr),
	pRect(nullptr)
{
}

Image::Image(Texture* _pText, jAzulRect* _pRect) :
	pText(_pText),
	pRect(_pRect)
{
}

Image::~Image()
{
	delete this->pRect;
}

void Image::Set(Texture* _pText, jAzulRect* _pRect)
{
	this->pText = _pText;
	delete this->pRect;
	this->pRect = _pRect;
}
