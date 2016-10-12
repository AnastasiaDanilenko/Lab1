#include "stdafx.h"
SRectangle::SRectangle(COLORREF color, int width, COLORREF brushColor) : Shape(color, width, brushColor)
{
	
}

SRectangle::~SRectangle()
{

}

void SRectangle::Paint(HDC hdc)
{
	SelectObject(hdc, brush);
	Rectangle(hdc, points[0].x, points[0].y, points[1].x, points[1].y);
}