#pragma once
class SRectangle : public Shape
{
public:
	SRectangle(COLORREF, int, COLORREF);
	~SRectangle();
	void Paint(HDC);
};