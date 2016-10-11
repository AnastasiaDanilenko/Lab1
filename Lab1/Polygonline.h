#pragma once
class SPolygonline : public Shape
{
public:
	SPolygonline(int, COLORREF, int, int, POINT*);
	~SPolygonline();
	void Paint(HDC);
};
