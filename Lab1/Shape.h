#pragma once
class Shape
{
	public:
		virtual void Paint(HDC) = 0;
		Shape();
		Shape(int, COLORREF, int, int, POINT*);
		~Shape();
		void SetCoordinates(POINT*);
	protected:
		POINT* points;
		HBRUSH brush;
		HPEN pen;
		int weight;
};
