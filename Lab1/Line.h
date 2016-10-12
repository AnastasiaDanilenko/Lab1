#pragma once
class SLine : public Shape
{
	public:
		SLine(COLORREF, int, COLORREF);
		~SLine();
		void Paint(HDC);
};
