#include "stdafx.h"



	Shape::Shape()
	{

	}

	void Shape::SetCoordinates(POINT* newPoints)
	{
		points = newPoints;
	}

	Shape::Shape(int type, COLORREF color, int fnstyle, int width, POINT* newPoints)
	{
		width = width;
		points = newPoints;
		if (type == 0)
		{
			pen = CreatePen(fnstyle, width, color);
		}
		else
		{
			if (fnstyle == 0)
				brush = CreateSolidBrush(color);
			else
				brush = CreateHatchBrush(fnstyle, color);
		}
	}

	Shape::~Shape()
	{
		DeleteObject(brush);
		DeleteObject(pen);
	}