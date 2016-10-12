#pragma once
class SPolygonline : public Shape
{
public:
	SPolygonline(COLORREF, int, COLORREF);
	~SPolygonline();
	void Paint(HDC);
};
