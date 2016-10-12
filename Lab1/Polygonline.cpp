#include "stdafx.h"

SPolygonline::SPolygonline(COLORREF color, int width, COLORREF brushColor) : Shape(color, width, brushColor)
{
	
}

SPolygonline::~SPolygonline()
{

}

void SPolygonline::Paint(HDC hdc)
{
	SelectObject(hdc, brush);
	MoveToEx(hdc, points[0].x, points[0].y, NULL);
	LineTo(hdc, points[1].x, points[1].y);
}