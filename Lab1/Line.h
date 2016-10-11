#pragma once
class SLine : public Shape
{
	public:
		SLine(int, COLORREF, int, int, POINT*);
		~SLine();
		void Paint(HDC);
};
