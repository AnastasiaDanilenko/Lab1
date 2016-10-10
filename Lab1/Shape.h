#pragma once
class Shape
{
	public:
		void Paint();
		~Shape();
	protected:
		POINT* StartPoint;
		HBRUSH brush;
		HPEN pen;
};
