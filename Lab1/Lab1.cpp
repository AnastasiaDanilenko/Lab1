// Lab1.cpp: определяет точку входа для приложения.
//
#include "stdafx.h"
#include "Lab1.h"

#define MAX_LOADSTRING 100

HANDLE res;
// Глобальные переменные:
const int clientRectTop = GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CXMENUSIZE);
HIMAGELIST ImageList = NULL;
Shape* currentShape = NULL;
int shapeId = 0;
POINTS start;
COLORREF currentColorPen;
COLORREF currentColorBrush;
POINTS end;
int weight;
HDC g_hdc;
bool drawing;
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
// Отправить объявления функций, включенных в этот модуль кода:
INT_PTR CALLBACK	WeightChangeDialog(HWND, UINT, WPARAM, LPARAM);
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB1));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0) > 0)
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   if (!hWnd)
   {
      return FALSE;
   }
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

HWND CreateToolbarFromResource(HWND hWndParent)
{
	// Declare and initialize local constants.
	const int ImageListID = 0;
	const int numButtons = 10;
	int bitmapSize = 16;

	const DWORD buttonStyles = BTNS_AUTOSIZE;

	// Create the toolbar.
	HWND hWndToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL,
		WS_CHILD | TBSTYLE_WRAPABLE, 0, 0, 0, 0,
		hWndParent, NULL, hInst, NULL);
	if (hWndToolbar == NULL)
		return NULL;

	// Create the image list.
	ImageList = ImageList_Create(bitmapSize, bitmapSize,   // Dimensions of individual bitmaps.
		ILC_COLOR16 | ILC_MASK,   // Ensures transparent background.
		numButtons, 0);

	for (int i = 0; i < 7; i++)
		ImageList_AddIcon(ImageList, LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1 + i)));

	// Set the image list.
	SendMessage(hWndToolbar, TB_SETIMAGELIST, (WPARAM)ImageListID, (LPARAM)ImageList);

	// Load the button images.
	//SendMessage(hWndToolbar, TB_LOADIMAGES, (WPARAM)IDB_STD_SMALL_COLOR, (LPARAM)HINST_COMMCTRL);

	int iNew = SendMessage(hWndToolbar, TB_ADDSTRING,
		(WPARAM)hInst, (LPARAM)IDS_NEW);

	// Initialize button info.
	// IDM_NEW, IDM_OPEN, and IDM_SAVE are application-defined command constants.
	std::vector<std::wstring> buttons = {L"Карандаш", L"Линия",L"Прямоугольник", L"Эллипс", L"Полигон", L"Ломаная", L"Текст", L"Цвет",L"Толщина", L"Изменить цвет"  };
	TBBUTTON tbButtons[numButtons];
	for (int i = 0; i < numButtons; i++)
	{
		tbButtons[i].iBitmap = i;
		tbButtons[i].fsStyle = buttonStyles;
		tbButtons[i].fsState = TBSTATE_ENABLED;
		tbButtons[i].iString = (INT_PTR)buttons[i].data();
		tbButtons[i].idCommand = IDM_PEN + i;
	}

	// Add buttons.
	SendMessage(hWndToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	SendMessage(hWndToolbar, TB_ADDBUTTONS, (WPARAM)numButtons, (LPARAM)&tbButtons);

	// Resize the toolbar, and then show it.
	SendMessage(hWndToolbar, TB_AUTOSIZE, 0, 0);
	ShowWindow(hWndToolbar, TRUE);

	return hWndToolbar;
}

void AddPoints(LPARAM lparam)
{
	//points = (POINTS*)realloc(points, sizeof(POINT));
	
}

void InitializeVariables()
{
	start.x = -1;
	start.y = 0;
	end.x = -1;
	end.y = 0;
	currentColorPen = 0;
	currentColorBrush = 1;
	drawing = false;

	//points = NULL;
}

Shape* GetShape()
{
	Shape* shape = NULL;
	switch (shapeId)
	{
		case IDM_ELLIPSE:
			shape = new SEllipse(PS_DOT, 1, RGB(0, 255, 0));
			break;
		case IDM_LINE:
			shape = new SLine(PS_DOT, 1, RGB(0, 255, 0));
			break;
		case IDM_RECTANGLE:
			shape = new SRectangle(PS_DOT, 1, RGB(0, 255, 0));
			break;
		case IDM_PEN:
			shape = new SPen(PS_DOT, 1, RGB(0, 255, 0));
		case IDM_POLYGON:
			shape = new SPolygon(PS_DOT, 1, RGB(0, 255, 0));
			break;
		case IDM_POLYGONLINE:
			shape = new SPolygonline(PS_DOT, 1, RGB(0, 255, 0));
			break;
	}
	return shape;
}

void MakeArray()
{
	POINT* sm = (POINT*)malloc(sizeof(POINT*));
	sm[0].x = start.x;
	sm[1].x = end.x;
	sm[0].y = start.y;
	sm[1].y = end.y;
	currentShape->SetCoordinates(sm);
}

void Drawing(HWND hWnd)
{
	RECT windowRect;
	GetClientRect(hWnd, &windowRect);
	HDC hdc = GetDC(hWnd);
	HDC hdc2 = CreateCompatibleDC(hdc);
	int windowWidth = windowRect.right - windowRect.left;//!
	int windowHeight = windowRect.bottom - windowRect.top;//!
	HBITMAP hbm = CreateCompatibleBitmap(hdc, windowWidth, windowHeight);
	HANDLE hold = SelectObject(hdc2, hbm);
	FillRect(hdc2, &windowRect, WHITE_BRUSH);
	SetDCPenColor(hdc2, 0);
	SetDCBrushColor(hdc2, 0);
	currentShape->Paint(hdc2);
	int newClientRectTop = clientRectTop;
	BitBlt(hdc, 0, newClientRectTop + 1, windowWidth, windowHeight - newClientRectTop - 1, hdc2, 0, newClientRectTop + 1, SRCCOPY);
	SelectObject(hdc2, hold);
	ReleaseDC(hWnd, hdc);
	DeleteObject(hbm);
	DeleteDC(hdc2);
	ValidateRect(hWnd, &windowRect);
}

CHOOSECOLOR chooseColor[2];

void InitChooseColorStruct(HWND hWnd)
{
	static COLORREF acrCustColor[16];
	for (int i = 0; i < 2; i++)
	{
		ZeroMemory(&chooseColor[i], sizeof(CHOOSECOLOR));
		chooseColor[i].lStructSize = sizeof(CHOOSECOLOR);
		chooseColor[i].hwndOwner = hWnd;
		chooseColor[i].Flags = CC_RGBINIT;
		chooseColor[i].lpCustColors = (LPDWORD)acrCustColor;
	}
	chooseColor[0].rgbResult = currentColorBrush;
	chooseColor[1].rgbResult = currentColorPen;
}

//standard choose color dialog
int ChooseColorProc(CHOOSECOLOR chooseColor)
{
	if (ChooseColor(&chooseColor))
		return chooseColor.rgbResult;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE: {
		CreateToolbarFromResource(hWnd);
		g_hdc = GetDC(hWnd);
		InitializeVariables();
		InitChooseColorStruct(hWnd);
		return 0;
	}
	case WM_GETMINMAXINFO:
	{
		MINMAXINFO *minMax = reinterpret_cast<MINMAXINFO*>(lParam);
		minMax->ptMinTrackSize.x = 650;
		minMax->ptMinTrackSize.y = 450;
		minMax->ptMaxTrackSize.x = 1000;
		minMax->ptMaxTrackSize.y = 750;
		break;
	}
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
			case IDM_LINE:
			case IDM_ELLIPSE:
			case IDM_POLYGON:
			case IDM_RECTANGLE:
			case IDM_PEN:
			case IDM_TEXT:
			case IDM_POLYGONLINE:
			{
				shapeId = wmId;
				drawing = true;
				break;
			}
            case IDM_EXIT:
				SendMessage(hWnd, WM_DESTROY, 0, 0);
                break;
			case IDM_PAINTCAN:currentColorBrush = ChooseColorProc(chooseColor[0]);
				break;
			case IDM_CHOOSECOLOR:currentColorPen = ChooseColorProc(chooseColor[1]);
				break;
			case IDM_WEIGHT:DialogBox(hInst, MAKEINTRESOURCE(IDD_WEIGHTCHANGEBOX), hWnd, WeightChangeDialog);
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
		if (end.x != -1)
		{
			Drawing(hWnd);
		}
			break;
        }
	case WM_MOUSEMOVE:
	{
		if (start.x != -1)
		{
			end = MAKEPOINTS(lParam);
			currentShape = GetShape();
			MakeArray();
			InvalidateRect(hWnd, NULL, false);
		}
		break;
	}
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_LBUTTONDOWN:
	{
		if (drawing == true)
		{
			if (start.x == -1)
			{
				start = MAKEPOINTS(lParam);
			}
			else
			{
				if ((shapeId != 32772) && (shapeId != 32773))
				{
					end = MAKEPOINTS(lParam);
					currentShape = GetShape();
					MakeArray();
					InvalidateRect(hWnd, NULL, false);
					start.x = -1;
				}
			}
		}
			break;
		}
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

HWND CreateTrackBar(HWND hwndDlg, HINSTANCE hInst)
{
	InitCommonControls();
	HWND hWndTrackBar = CreateWindowEx(0, TRACKBAR_CLASS, L"Trackbar Control", WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS | TBS_ENABLESELRANGE | TBS_TRANSPARENTBKGND, 10, 20, 200, 30, hwndDlg, NULL, hInst, NULL);
	if (hWndTrackBar == NULL)
		return NULL;
	SendMessage(hWndTrackBar, TBM_SETRANGE, 0, (LPARAM)MAKELONG(0, DEFAULT_TRACKBAR_MAXSIZE));
	SendMessage(hWndTrackBar, TBM_SETPAGESIZE, 0, (LPARAM)DEFAULT_TRACKBAR_PAGESIZE);                  // new page size 
	SendMessage(hWndTrackBar, TBM_SETSEL, (WPARAM)FALSE, (LPARAM)MAKELONG(0, DEFAULT_TRACKBAR_MAXSIZE)); // redraw flag
	SendMessage(hWndTrackBar, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)weight);                   // redraw flag
	SetFocus(hWndTrackBar);
	return hWndTrackBar;
}


INT_PTR CALLBACK WeightChangeDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	HWND hWndTrackBar = NULL;
	PAINTSTRUCT ps;
	static wchar_t currentPosString[64];
	static int currentPos = weight;
	switch (message)
	{
		//change current position of trackbar
	case WM_INITDIALOG:
		hWndTrackBar = CreateTrackBar(hDlg, hInst);
		if (currentPos != weight)
			currentPos = weight;
		InvalidateRect(hDlg, NULL, FALSE);
		break;
	case WM_HSCROLL:
		switch (LOWORD(wParam))
		{
		case TB_LINEUP:
			if (currentPos>0)
				currentPos -= 1;
			break;
		case TB_LINEDOWN:
			if (currentPos<DEFAULT_TRACKBAR_MAXSIZE)
				currentPos += 1;
			break;
		case TB_PAGEUP:
			if (currentPos >= 0)
				currentPos -= DEFAULT_TRACKBAR_PAGESIZE;
			break;
		case TB_PAGEDOWN:
			if (currentPos<DEFAULT_TRACKBAR_MAXSIZE)
				currentPos += DEFAULT_TRACKBAR_PAGESIZE;
			break;
		case TB_THUMBTRACK:
		case TB_THUMBPOSITION:currentPos = HIWORD(wParam);
			break;
		case TB_TOP:currentPos = 0;
			break;
		case TB_BOTTOM:currentPos = DEFAULT_TRACKBAR_MAXSIZE;
			break;
			break;
		}
		InvalidateRect(hDlg, NULL, FALSE);
		break;
		//display current position of trackbar
	case WM_PAINT:
	{
		HDC hdc = BeginPaint(hDlg, &ps);
		wsprintf(currentPosString, L" Толщина: %d  ", currentPos);
		TabbedTextOut(hdc, 65, 5, currentPosString, wcslen(currentPosString), 0, 0, 0);
		EndPaint(hDlg, &ps);
	}
	break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
			weight = currentPos;
		EndDialog(hDlg, LOWORD(wParam));
		return (INT_PTR)TRUE;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
