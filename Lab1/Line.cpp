#include "stdafx.h"

	SLine::SLine(int type, COLORREF color, int fnstyle, int width, POINT* newpoints): Shape(type, color, fnstyle, width, points)
	{
		points = newpoints;
	}

	SLine::~SLine()
	{

	}

	void SLine::Paint(HDC hdc)
	{
		SelectObject(hdc, brush);
		MoveToEx(hdc, points[0].x, points[0].y, NULL);
		LineTo(hdc, points[1].x, points[1].y);
	}