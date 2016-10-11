#pragma once
class SRectangle : public Shape
{
public:
	SRectangle(int, COLORREF, int, int, POINT*);
	~SRectangle();
	void Paint(HDC);
};