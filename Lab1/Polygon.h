#pragma once
class SPolygon : public Shape
{
public:
	SPolygon(COLORREF, int, COLORREF);
	~SPolygon();
	void Paint(HDC);
};