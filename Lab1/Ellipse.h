#pragma once
class SEllipse : public Shape
{
public:
	SEllipse(COLORREF, int, COLORREF);
	~SEllipse();
	void Paint(HDC);
};