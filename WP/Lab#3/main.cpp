#include <windows.h>
#include <windowsx.h>

#define IDB_TOOLS_GROUP 100
#define IDB_PENCIL_TOOL 101

#define IDB_ERASER_TOOL 102
#define IDB_RECTANGLE_TOOL 103
#define IDB_LINE_TOOL 104
#define IDB_ELLIPSE_TOOL 105
#define IDB_FILL_CHECK 106
#define IDB_BORDER_WIDTH 107
#define IDB_BEZIER_TOOL 109
#define HK_DRAW_ELLIPSE 500
#define HK_RED_COLOR    501

LPSTR szClassName = "Simple Paint";
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
HINSTANCE hInst;

void updateColorControls(HDC, COLORREF, int, int);
int getFromInput(HWND);
POINT getCurrentPointPosition(int, int, RECT, int);

COLORREF fillColor = RGB(255, 255, 255);
COLORREF borderColor = RGB(0, 0, 0);
COLORREF colorSelect(HWND hwnd, COLORREF color)
{
    COLORREF g_rgbCustom[16] = {0};
    CHOOSECOLOR cc = {sizeof(CHOOSECOLOR)};

    cc.Flags = CC_RGBINIT | CC_SOLIDCOLOR;
    cc.hwndOwner = hwnd;
    cc.rgbResult = color;
    cc.lpCustColors = g_rgbCustom;

    if(ChooseColor(&cc))
    {
        color = cc.rgbResult;
    }
    //InvalidateRect(hwnd, NULL,FALSE);
    return color;
}

// Redirecting child messages to parent window
WNDPROC GroupBoxProc;
LONG CALLBACK GroupRelay(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if(msg == WM_COMMAND || msg == WM_NOTIFY){
        return SendMessage(GetParent(hwnd), msg, wParam, lParam);
    }

    return CallWindowProc(GroupBoxProc, hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
    WNDCLASSEX wnd;
    MSG msg;
    HWND hwnd;
    hInst = hInstance;

    /* The Window Structure */
    wnd.hInstance = hInst;
    wnd.lpszClassName = szClassName;
    wnd.lpfnWndProc = WindowProcedure;
    wnd.style = CS_HREDRAW | CS_VREDRAW;
    wnd.cbSize = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Default icon
    wnd.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // Default icon
    wnd.hCursor = LoadCursor(NULL, IDC_ARROW); // Default arrow mouse cursor
    wnd.lpszMenuName = NULL; // No menu
    wnd.cbClsExtra = 0; // No extra bytes after the window class
    wnd.cbWndExtra = 0; // structure or the window instance

    wnd.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);

    if(!RegisterClassEx(&wnd)) // Register the WNDCLASSEX
    {
        MessageBox(NULL, "This Program Requires Windows NT", "Error", MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        (DWORD)NULL,
        szClassName,
        "Laboratory work nr.3", // Window title
        WS_OVERLAPPED | WS_BORDER | WS_SYSMENU, // Basic window style
        CW_USEDEFAULT, CW_USEDEFAULT, // Set starting point to default value
        705, 380, // Set all the dimensions to default value
        NULL, //no parent window
        NULL, //no menu
        hInst,
        NULL); //no parameters to pass

    ShowWindow(hwnd, iCmdShow); //display the window on the screen
    UpdateWindow(hwnd); //make sure the window is updated correctly

    while(GetMessage(&msg, NULL, 0, 0)) //message loop
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HWND hwndToolsGroup;
    static HWND hwndPencilTool;
    static HWND hwndEllipseTool;
    static HWND hwndLineTool;
    static HWND hwndEraserTool;
    static HWND hwndFillCheck;
    static HWND hwndBorderWidth;
    static HWND hwndEraserWidth;
    static HWND hwndRectangleTool;
    static HWND hwndConfigGroup;
    static HWND hwndBezierTool;
    RECT rect ;
    int screenW;
    int screenH;
    PAINTSTRUCT ps;
    HDC hdc = GetDC(hwnd);
    int xMouse, yMouse;

    // Color preview rectangles
    int xFillPreview = 115;
    int yFillPreview = 200;
    int xStrokePreview = 115;
    int yStrokePreview = 250;



    HDC hdcMem;
    BITMAP bitmap;
    HBITMAP hbmpDesignerImage = NULL;
    hbmpDesignerImage = (HBITMAP)LoadImage(hInst, "example.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(hbmpDesignerImage, sizeof(bitmap), &bitmap);

    static RECT drawingArea = {170, 17, 680, 340};
    static RECT fillColorRect = {xFillPreview, yFillPreview, xFillPreview + 25, yFillPreview + 20};
    static RECT borderColorRect = {xStrokePreview, yStrokePreview, xStrokePreview + 25, yStrokePreview + 20};
    static RECT gradientRect = {25, 300, 140, 330};
    static RECT tempRect;

    // Drawing stuff
    HBRUSH hBrush;
    static POINT pointPen;
    POINT point;
    HPEN linePen;
    int width;

    static BOOL lineStarted;
    static POINT line;
    static BOOL rectangleStarted;
    static RECT rectangle;
    static BOOL ellipseStarted;
    static RECT ellipse;
    static int bezierStage = 0;
    static POINT bezierPoints[4];

    HPEN borderPen;
    HBRUSH fillBrush;

    switch(msg)
    {
        case WM_CREATE:
            screenW = GetSystemMetrics(SM_CXSCREEN);
            screenH = GetSystemMetrics(SM_CYSCREEN);
            GetWindowRect(hwnd, &rect);
            SetWindowPos(
                    hwnd, 0,
                    (screenW - rect.right)/2,
                    (screenH - rect.bottom)/2,
                    0, 0, SWP_NOZORDER|SWP_NOSIZE);

            // Drawing tools group
            hwndToolsGroup = CreateWindowEx(
                0,
                "Button",
                "Instruments",
                WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
                15, 10,
                140, 140,
                hwnd,
                (HMENU)IDB_TOOLS_GROUP,
                hInst,
                NULL);

            // Pen tool
            hwndPencilTool = CreateWindowEx(
                0,
                "Button",
                "Pen",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                10, 15,
                110, 20,
                hwndToolsGroup,
                (HMENU)IDB_PENCIL_TOOL,
                hInst,
                NULL);
            Button_SetCheck(hwndPencilTool, BST_CHECKED);

            // Ellipse tool
            hwndEllipseTool = CreateWindowEx(
                0,
                "Button",
                "Ellipse",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                10, 35,
                110, 20,
                hwndToolsGroup,
                (HMENU)IDB_ELLIPSE_TOOL,
                hInst,
                NULL);

            // Rectangle tool
            hwndRectangleTool = CreateWindowEx(
                0,
                "Button",
                "Rectangle",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                10, 55,
                110, 20,
                hwndToolsGroup,
                (HMENU)IDB_RECTANGLE_TOOL,
                hInst,
                NULL);

            // Line tool
            hwndLineTool = CreateWindowEx(
                0,
                "Button",
                "Line",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                10, 75,
                110, 20,
                hwndToolsGroup,
                (HMENU)IDB_LINE_TOOL,
                hInst,
                NULL);

            // Bezier tool
            hwndBezierTool = CreateWindowEx(
                0,
                "Button",
                "Bezier curve",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                10, 95,
                110, 20,
                hwndToolsGroup,
                (HMENU)IDB_ERASER_TOOL,
                hInst,
                NULL);

            // Eraser tool
            hwndEraserTool = CreateWindowEx(
                0,
                "Button",
                "Eraser",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                10, 115,
                110, 20,
                hwndToolsGroup,
                (HMENU)IDB_ERASER_TOOL,
                hInst,
                NULL);

            // options group
            hwndConfigGroup = CreateWindowEx(
                0,
                "Button",
                "Options",
                WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
                15, 160,
                140, 180,
                hwnd,
                (HMENU)IDB_TOOLS_GROUP,
                hInst,
                NULL);

            // Fill checkbox
            hwndFillCheck = CreateWindowEx(
                0,
                "Button",
                "Fill with grad.",
                WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
                10, 15,
                120, 20,
                hwndConfigGroup,
                (HMENU)IDB_FILL_CHECK,
                hInst,
                NULL);

            // Fill with label
            CreateWindowEx(
                0,
                "Static",
                "Fill with",
                WS_VISIBLE | WS_CHILD | SS_LEFT,
                10, 40,
                90, 20,
                hwndConfigGroup,
                (HMENU)0,
                hInst,
                NULL);

            // Border width label
            CreateWindowEx(
                0,
                "Static",
                "Border width",
                WS_VISIBLE | WS_CHILD | SS_LEFT,
                10, 65,
                100, 20,
                hwndConfigGroup,
                (HMENU)0,
                hInst,
                NULL);

            // Border width input
            hwndBorderWidth = CreateWindowEx(
                0,
                "Edit",
                "5",
                WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,
                100, 65,
                25, 20,
                hwndConfigGroup,
                (HMENU)0,
                hInst,
                NULL);

            // Border color label
            CreateWindowEx(
                0,
                "Static",
                "Border color",
                WS_VISIBLE | WS_CHILD | SS_LEFT,
                10, 90,
                90, 20,
                hwndConfigGroup,
                (HMENU)0,
                hInst,
                NULL);

            // Eraser width label
            CreateWindowEx(
                0,
                "Static",
                "Eraser width",
                WS_VISIBLE | WS_CHILD | SS_LEFT,
                10, 115,
                100, 20,
                hwndConfigGroup,
                (HMENU)0,
                hInst,
                NULL);

            // Eraser width input
            hwndEraserWidth = CreateWindowEx(
                0,
                "Edit",
                "5",
                WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,
                100, 115,
                25, 20,
                hwndConfigGroup,
                (HMENU)0,
                hInst,
                NULL);


            RegisterHotKey(hwnd, HK_DRAW_ELLIPSE, MOD_CONTROL, 0x45); //CTRL+E
            RegisterHotKey(hwnd, HK_RED_COLOR, MOD_CONTROL, 0x44); // CTRL+D

            // Redirecting child messages to parent window
            GroupBoxProc = reinterpret_cast<WNDPROC>(GetWindowLongPtr(hwndConfigGroup, GWLP_WNDPROC));
            SetWindowLongPtr(hwndConfigGroup, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(GroupRelay));

            GroupBoxProc = reinterpret_cast<WNDPROC>(GetWindowLongPtr(hwndToolsGroup, GWLP_WNDPROC));
            SetWindowLongPtr(hwndToolsGroup, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(GroupRelay));
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                default:
                    DefWindowProc(hwnd, WM_COMMAND, wParam, lParam);
                    break;
            }
            break;

        case WM_PAINT:

            hdc = BeginPaint(hwnd, &ps);

            // Fill color preview rectangle
            updateColorControls(hdc, fillColor, xFillPreview, yFillPreview);

            // Stroke color preview rectangle
            updateColorControls(hdc, borderColor, xStrokePreview, yStrokePreview);

            // Draw image
            hdcMem = CreateCompatibleDC(hdc);
            SelectObject(hdcMem, hbmpDesignerImage);
            BitBlt(hdc, 15, 340, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
            DeleteDC(hdcMem);

            // Blank draw area
            SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(0,0,0)));
            SelectObject(hdc, (HBRUSH)GetStockObject(WHITE_BRUSH));
            Rectangle(hdc, drawingArea.left, drawingArea.top, drawingArea.right, drawingArea.bottom);

            /*/
            Load the bitmap from the resource
            bmpExercising = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_EXERCISING));
            // Create a memory device compatible with the above DC variable
            MemDCExercising = CreateCompatibleDC(hDC);
            // Select the new bitmap
            SelectObject(MemDCExercising, bmpExercising);

            // Copy the bits from the memory DC into the current dc
            BitBlt(hDC, 10, 10, 450, 400, MemDCExercising, 0, 0, SRCCOPY);
            */



            EndPaint(hwnd, &ps);
            break;

        case WM_LBUTTONDOWN:
            xMouse = GET_X_LPARAM(lParam);
            yMouse = GET_Y_LPARAM(lParam);

            if(xMouse >= fillColorRect.left && xMouse <= fillColorRect.right)
            {
                if(yMouse >= fillColorRect.top && yMouse <= fillColorRect.bottom)
                {
                    fillColor = colorSelect(hwnd, fillColor);
                    updateColorControls(hdc, fillColor, xFillPreview, yFillPreview);
                }
                else if(yMouse >= borderColorRect.top && yMouse <= borderColorRect.bottom)
                {
                    borderColor = colorSelect(hwnd, borderColor);
                    updateColorControls(hdc, borderColor, xFillPreview, yFillPreview);
                }
                return 0;
            }

            if( (xMouse > drawingArea.left) && (xMouse < drawingArea.right) &&
                (yMouse > drawingArea.top) && (yMouse < drawingArea.bottom) )
            {
                width = getFromInput(hwndBorderWidth);
                point = getCurrentPointPosition(xMouse, yMouse, drawingArea, width);
                xMouse = point.x;
                yMouse = point.y;

                // If Pencil tool is selected, setting startpoint
                if((wParam == MK_LBUTTON) && (Button_GetCheck(hwndPencilTool) == BST_CHECKED))
                {
                    pointPen.x = xMouse;
                    pointPen.y = yMouse;
                }

                // Line
                if((wParam == MK_LBUTTON) && (Button_GetCheck(hwndLineTool) == BST_CHECKED))
                {
                    line.x = xMouse;
                    line.y = yMouse;
                    lineStarted = true;
                }

                // Rectangle
                if((wParam == MK_LBUTTON) && (Button_GetCheck(hwndRectangleTool) == BST_CHECKED))
                {
                    rectangle.left = xMouse;
                    rectangle.top = yMouse;
                    rectangleStarted = true;
                }

                // Ellipse
                if((wParam == MK_LBUTTON) && (Button_GetCheck(hwndEllipseTool) == BST_CHECKED))
                {
                    ellipse.left = xMouse;
                    ellipse.top = yMouse;
                    ellipseStarted = true;
                }

                // Bezierceg
                if((wParam == MK_LBUTTON) && (Button_GetCheck(hwndBezierTool) == BST_CHECKED))
                {
                    if(bezierStage == 0)
                    {
                        bezierPoints[0] = point;
                        bezierStage = 1;
                    }
                    else
                    {
                        bezierPoints[2] = point;
                        bezierStage = 3;
                    }
                }
            }
            break;

        case WM_LBUTTONUP:
            xMouse = GET_X_LPARAM(lParam);
            yMouse = GET_Y_LPARAM(lParam);
            width = getFromInput(hwndBorderWidth);
            point = getCurrentPointPosition(xMouse, yMouse, drawingArea, width);
            xMouse = point.x;
            yMouse = point.y;

            borderPen = CreatePen(PS_SOLID, width, borderColor);
            if(Button_GetCheck(hwndFillCheck) == BST_CHECKED)
                fillBrush = CreateSolidBrush(fillColor);
            else
                fillBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

            if(lineStarted)
            {
                SelectObject(hdc, borderPen);
                MoveToEx(hdc, xMouse, yMouse, NULL);
                LineTo(hdc, line.x, line.y);
                DeleteObject(borderPen);
                lineStarted = false;
            }

            if(rectangleStarted)
            {
                SelectObject(hdc, borderPen);
                SelectObject(hdc, fillBrush);
                Rectangle(hdc, rectangle.left, rectangle.top, xMouse, yMouse);

                DeleteObject(borderPen);
                DeleteObject(fillBrush);

                rectangleStarted = false;
            }

            if(ellipseStarted)
            {
                SelectObject(hdc, borderPen);
                SelectObject(hdc, fillBrush);

                Ellipse(hdc, ellipse.left, ellipse.top, xMouse, yMouse);
                DeleteObject(borderPen);
                DeleteObject(fillBrush);

                ellipseStarted = false;
            }

            if(bezierStage == 1)
            {
                bezierPoints[1] = point;
                bezierStage = 2;
            }

            if(bezierStage == 3)
            {
                bezierPoints[3] = point;
                bezierStage = 0;
                SelectObject(hdc, borderPen);
                PolyBezier(hdc, bezierPoints, 4);
                DeleteObject(borderPen);
            }
            break;

        case WM_MOUSEMOVE:
            xMouse = GET_X_LPARAM(lParam);
            yMouse = GET_Y_LPARAM(lParam);
            if( (xMouse > drawingArea.left) && (xMouse < drawingArea.right) &&
                (yMouse > drawingArea.top) && (yMouse < drawingArea.bottom) )
            {
                 // If Pen tool is selected
                if((wParam == MK_LBUTTON) && (Button_GetCheck(hwndPencilTool) == BST_CHECKED))
                {
                    width = getFromInput(hwndBorderWidth);
                    point = getCurrentPointPosition(xMouse, yMouse, drawingArea, width);
                    xMouse = point.x;
                    yMouse = point.y;
                    linePen = CreatePen(PS_SOLID, width, borderColor);
                    SelectObject(hdc, linePen);
                    MoveToEx(hdc, xMouse, yMouse, NULL);
                    LineTo(hdc, pointPen.x, pointPen.y);
                    DeleteObject(linePen);
                    pointPen.x = xMouse;
                    pointPen.y = yMouse;
                }

                // If Eraser tool is selected
                if((wParam == MK_LBUTTON) && (Button_GetCheck(hwndEraserTool) == BST_CHECKED))
                {
                    width = getFromInput(hwndEraserWidth);
                    point = getCurrentPointPosition(xMouse, yMouse, drawingArea, width);
                    xMouse = point.x;
                    yMouse = point.y;
                    rect.left = point.x - (width / 2);
                    rect.right = point.x + (width / 2);
                    rect.top = point.y - (width / 2);
                    rect.bottom = point.y + (width / 2);
                    InvalidateRect(hwnd, &rect, FALSE);
                    SendMessage(hwnd, WM_PAINT, 0, 0);
                    //ValidateRect(hwnd, &rect);
                }
            }

            break;

            case WM_CTLCOLORSTATIC:
                if(GetDlgItem(hwnd, IDB_TOOLS_GROUP) == (HWND)lParam)
                {
                    HDC hDC = (HDC)wParam;
                    SetBkColor(hDC, GetSysColor(COLOR_WINDOW));
                    SetTextColor(hDC, RGB(0, 0, 0xFF));
                    SetBkMode(hDC, TRANSPARENT);
                    return (INT_PTR)CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
                }

                break;

        case WM_HOTKEY:
        {
            switch(wParam)
            {
                case HK_DRAW_ELLIPSE:

                    Button_SetCheck(hwndPencilTool, BST_UNCHECKED);
                    Button_SetCheck(hwndLineTool, BST_UNCHECKED);
                    Button_SetCheck(hwndBezierTool, BST_UNCHECKED);
                    Button_SetCheck(hwndRectangleTool, BST_UNCHECKED);
                    Button_SetCheck(hwndEraserTool, BST_UNCHECKED);
                    Button_SetCheck(hwndEllipseTool, BST_CHECKED);
                    break;

                case HK_RED_COLOR:
                    Button_SetCheck(hwndFillCheck, BST_CHECKED);
                    fillColor = RGB(255,0,0);
                    updateColorControls(hdc, fillColor, xFillPreview, yFillPreview);
                    break;
                default:
                    break;
            }
            break;
        }
        /**/
        case WM_KEYDOWN:   // keyboard input
        {
            switch(wParam)
            {
                case KEY_S:
				     isDrawing = FALSE;
				break;
                case KEY_P:  // LeftSHIFT + P
                {
                    if (GetAsyncKeyState(VK_LSHIFT))
                    {
                     SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(ID_PEN, 0), 0);
                     Button_SetCheck(HwndPen, BST_UNCHECKED);
                    }
                break;
                }

                case KEY_B:  // LeftSHIFT + B
                {
                    if (GetAsyncKeyState(VK_LSHIFT))
                    {
                     SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(ID_BLUE, 0), 0);
                    }
                break;
                }
                case KEY_G:  // LeftSHIFT + G
                {
                    if (GetAsyncKeyState(VK_LSHIFT))
                    {
                     SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(ID_GREEN, 0), 0);
                    }
                break;
                }
                case KEY_R:  // LeftSHIFT + R
                {
                    if (GetAsyncKeyState(VK_LSHIFT))
                    {
                     SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(ID_RED, 0), 0);
                    }
                break;
                }
                case KEY_C:   // LShift + C
                {
                    if (GetAsyncKeyState(VK_LSHIFT))
                    {

                SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(ID_CLEAR, 0), 0);
                    }
                 break;
                }

                default: return DefWindowProc (hwnd, message, wParam, lParam);
            break;   // end of switch statement
            }
        break;
        */
         case WM_CLOSE:
            if(MessageBox(hwnd, "Are you sure you want to exit?", "Paint", MB_YESNO) == IDYES)
                DestroyWindow(hwnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void updateColorControls(HDC hdc, COLORREF rgb, int xLeft, int yTop)
{
    HBRUSH hBrush = CreateSolidBrush(rgb);
    HPEN hPen = CreatePen(PS_INSIDEFRAME, 2, RGB(10, 40, 140));

    SelectObject(hdc, hBrush);
    SelectObject(hdc, hPen);

    Rectangle(hdc, xLeft, yTop, xLeft + 25, yTop + 20);

    hBrush = CreateSolidBrush(RGB(10, 40, 140));
    SelectObject(hdc, hBrush);

    Rectangle(hdc, xLeft+18, yTop+13, xLeft + 25, yTop + 20);

    DeleteObject(hPen);
    DeleteObject(hBrush);

}
int getFromInput(HWND input)
{
    int result, len;
    len = SendMessage(input, WM_GETTEXTLENGTH, 0, 0);

    char * temp = (char *)malloc(len + 1);
    SendMessage(input, WM_GETTEXT, len + 1, (LPARAM)temp);
    result = atoi(temp);
    free(temp);
    return result;
}

POINT getCurrentPointPosition(int xMouse, int yMouse, RECT limit, int width)
{
    POINT result;
    width = width / 2 + 1;

    if(xMouse + width > limit.right)
        result.x = limit.right - width;
    else if(xMouse - width < limit.left)
        result.x = limit.left + width;
    else
        result.x = xMouse;

    if(yMouse - width < limit.top)
        result.y = limit.top + width;
    else if(yMouse + width > limit.bottom)
        result.y = limit.bottom - width;
    else
        result.y = yMouse;

    return result;
}
// fill with gradient
void fillWithGradient(HDC hdc, HBRUSH hBrush, RECT tempRect, RECT gradientRect, int colorNr)
{
    for(int i = 0; i < (gradientRect.right - gradientRect.left); i++) {
        int color;
        color = i * 255 / (gradientRect.right - gradientRect.left);
        tempRect.left  = gradientRect.left  + i;
        tempRect.right = gradientRect.left + i + 1;
        if (colorNr == 0)
            hBrush = CreateSolidBrush(RGB(color, 0, 0));
        else if (colorNr == 1)
            hBrush = CreateSolidBrush(RGB(0, color, 0));
        else
            hBrush = CreateSolidBrush(RGB(0, 0, color));
        FillRect(hdc, &tempRect, hBrush);
        DeleteObject(hBrush);
    }
