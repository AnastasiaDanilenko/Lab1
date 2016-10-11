#pragma once
class SPolygon : public Shape
{
public:
	SPolygon(int, COLORREF, int, int, POINT*);
	~SPolygon();
	void Paint(HDC);
};