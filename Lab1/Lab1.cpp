// Lab1.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "Lab1.h"

#define MAX_LOADSTRING 100

HANDLE res;
// Глобальные переменные:

HIMAGELIST ImageList = NULL;
Shape* currentShape = NULL;
int shapeId = 0;
POINTS start;
POINTS end;
HDC g_hdc;
bool drawing;
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
// Отправить объявления функций, включенных в этот модуль кода:
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
	int bitmapSize = 128;

	const DWORD buttonStyles = BTNS_AUTOSIZE;

	// Create the toolbar.
	HWND hWndToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL,
		WS_CHILD | TBSTYLE_WRAPABLE, 0, 0, 0, 0,
		hWndParent, NULL, hInst, NULL);
	if (hWndToolbar == NULL)
		return NULL;

	// Create the image list.
	//ImageList = ImageList_Create(bitmapSize, bitmapSize,   // Dimensions of individual bitmaps.
		//ILC_COLOR16 | ILC_MASK,   // Ensures transparent background.
		//numButtons, 0);

	// Set the image list.
	SendMessage(hWndToolbar, TB_SETIMAGELIST,
		(WPARAM)ImageListID,
		(LPARAM)ImageList);

	// Load the button images.
	SendMessage(hWndToolbar, TB_LOADIMAGES,
		(WPARAM)IDB_STD_SMALL_COLOR,
		(LPARAM)HINST_COMMCTRL);

	int iNew = SendMessage(hWndToolbar, TB_ADDSTRING,
		(WPARAM)hInst, (LPARAM)IDS_NEW);

	// Initialize button info.
	// IDM_NEW, IDM_OPEN, and IDM_SAVE are application-defined command constants.
	std::vector<std::wstring> buttons = {L"Карандаш", L"Линия", L"Ломаная", L"Эллипс", L"Прямоугольник", L"Полигон", L"Цвет", L"Масштаб", L"Толщина", L"Текст"};
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



COLORREF CheckColor()
{
	return RGB(0,0,0,0);
}

int CheckWeight()
{
	return 1;
}

void AddPoints(LPARAM lparam)
{
	//points = (POINTS*)realloc(points, sizeof(POINT));
	
}

void InitializeVariables()
{
	start.x = -1;
	start.y = 0;
	end.x = 0;
	end.y = 0;
	drawing = false;
	//points = NULL;
}

Shape* GetShape()
{
	Shape* shape;
	switch (shapeId)
	{
		case IDM_ELLIPSE:
			shape = new SEllipse();
			break;
		case IDM_LINE:
			shape = new SLine();
			break;
		case IDM_RECTANGLE:
			shape = new SRectangle();
			break;
		case IDM_TEXT:
			shape = new SText();
			break;
		case IDM_POLYGON:
			shape = new SPolygon();
			break;
		case IDM_POLYGONLINE:
			shape = new SPolygonline();
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE: {
		CreateToolbarFromResource(hWnd);
		g_hdc = GetDC(hWnd);
		InitializeVariables();
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
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {

			break;
        }
	case WM_MOVE:
	{
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
					HDC hdc = GetDC(hWnd);
					currentShape->Paint(hdc);
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
