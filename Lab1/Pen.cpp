#include "stdafx.h"
SPen::SPen(COLORREF color, int width, COLORREF brushColor) : Shape(color, width, color)
{
	
}

SPen::~SPen()
{

}

void SPen::Paint(HDC hdc)
{
	SelectObject(hdc,pen);
	Polyline(hdc, points, amount);
}