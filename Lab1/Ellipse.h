#pragma once
class SEllipse : public Shape
{
public:
	SEllipse(int, COLORREF, int, int, POINT*);
	~SEllipse();
	void Paint(HDC);
};