#include "stdafx.h"
SEllipse::SEllipse( COLORREF color, int width,COLORREF brushColor) : Shape(color, width, brushColor)
{
	
}

SEllipse::~SEllipse()
{

}

void SEllipse::Paint(HDC hdc)
{
	SelectObject(hdc, brush);
	Ellipse(hdc, points[0].x, points[0].y, points[1].x, points[1].y);
}