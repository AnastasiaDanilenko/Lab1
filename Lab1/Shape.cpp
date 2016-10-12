#include "stdafx.h"



	Shape::Shape()
	{

	}

	void Shape::SetCoordinates(POINT* newPoints)
	{
		points = newPoints;
	}

	Shape::Shape(COLORREF color, int width, COLORREF brushColor)
	{
		width = width;
		pen = CreatePen(PS_SOLID, width, color);
		if (brushColor == 0)
			brush = (HBRUSH)GetStockObject(NULL_BRUSH);
		else
			brush = CreateSolidBrush(brushColor);
	}

	Shape::~Shape()
	{
		DeleteObject(brush);
		DeleteObject(pen);
	}