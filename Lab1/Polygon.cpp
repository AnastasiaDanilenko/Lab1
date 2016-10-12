#include "stdafx.h"
SPolygon::SPolygon(COLORREF color, int width, COLORREF brushColor) : Shape(color, width, brushColor)
{
	
}

SPolygon::~SPolygon()
{

}

void SPolygon::Paint(HDC hdc)
{
	SelectObject(hdc, brush);
	SelectObject(hdc, pen);
	Polygon(hdc, points, amount);
}