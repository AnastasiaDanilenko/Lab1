#pragma once
class SText
{
public:
	SText(COLORREF, int, COLORREF);
	~SText();
	void Paint(HDC);
private:
	COLORREF textColor, brushColor;
	LOGFONT font;
	HFONT hFont;
	POINTS* points;
	std::string str;
	int count = 0;
};