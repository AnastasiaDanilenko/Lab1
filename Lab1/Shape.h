#pragma once
class Shape
{
	public:
		virtual void Paint(HDC) = 0;
		Shape();
		Shape(COLORREF, int, COLORREF);
		~Shape();
		void SetCoordinates(POINT*);
	protected:
		POINT* points;
		int amount;
		HBRUSH brush;
		HPEN pen;
		int weight;
};
