#include "stdafx.h"
#include "Text.h"
SText::SText(COLORREF color, int weight, COLORREF brushColor)
{
	textColor = color;
	this->brushColor = brushColor;
	font.lfHeight = 16;
	font.lfWidth = 0;
	font.lfWeight = weight;
	font.lfItalic = 0;
	font.lfUnderline = 0;
	font.lfStrikeOut = 0;
	font.lfCharSet = RUSSIAN_CHARSET | DEFAULT_CHARSET;
	font.lfOutPrecision = 0;// Устанавливает точность вывода
	font.lfClipPrecision = 0;// Устанавливает точность отсечения
	font.lfQuality = 0;// Устанавливает качество вывода
	font.lfPitchAndFamily = 0;// Устанавливает ширину символов и семейство шрифта
	//strcpy_s(font.lfFaceName, "VERDANA");
	hFont = CreateFontIndirect(&font);
}

SText::~SText()
{
	
}

void SText::Paint(HDC hdc)
{
	if (points[0].x == 0 && points[0].y == 0)
		points[0].x = points[0].y = 20;
	SelectObject(hdc, hFont);
	SetTextColor(hdc, textColor);
	SetBkColor(hdc, brushColor);
	//TabbedTextOut(hdc, points[0].x, points[0].y, str.data(), str.size(), 0, 0, 0);
}