#include "stdafx.h"

	SLine::SLine(COLORREF color, int width, COLORREF brushColor): Shape(color, width, brushColor)
	{
		
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