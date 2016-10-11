#pragma once
class SText : public Shape
{
public:
	SText(int, COLORREF, int, int, POINT*);
	~SText();
	void Paint(HDC);
};