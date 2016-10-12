#pragma once
class SPen : public Shape
{
public:
	SPen(COLORREF, int, COLORREF);
	~SPen();
	void Paint(HDC);
};
