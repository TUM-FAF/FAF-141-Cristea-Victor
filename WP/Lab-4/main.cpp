#include "obj.h"

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

static Objects *objects[100];
char szClassName[ ] = "Animation";

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);

    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;

    wincl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);

    if (!RegisterClassEx (&wincl))
        return 0;

    hwnd = CreateWindowEx (
           0,
           szClassName,
           "Laboratory work nr.4",
           WS_OVERLAPPEDWINDOW,
           CW_USEDEFAULT,
           CW_USEDEFAULT,
           900,
           775,
           HWND_DESKTOP,
           NULL,
           hThisInstance,
           NULL
           );

    ShowWindow (hwnd, nCmdShow);

    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HDC hdc,hdcMem;
    static PAINTSTRUCT ps;
    static RECT rect;
    static HBRUSH hBrush;
    static HBITMAP hbmMem;

    static HANDLE hOld;

    static int timerSpeed = 1,nrObj = 0;
    static RECT area = {0, 0, 1600, 1200};

    switch (message)
    {
        case WM_CREATE:
        {
          hdc = GetDC(hwnd);
          GetClientRect(hwnd,&rect);

          hdcMem = CreateCompatibleDC(hdc);
          hbmMem = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
          hOld = SelectObject(hdcMem,hbmMem);

          SetTimer(hwnd, ID_TIMER, timerSpeed, NULL);
        break;
        }

        case WM_SIZE:
        {
            SelectObject(hdcMem, hOld);
            DeleteObject(hbmMem);
            DeleteDC(hdcMem);

            hdc = GetDC(hwnd);
            GetClientRect(hwnd, &rect);

            hdcMem = CreateCompatibleDC(hdc);
            hbmMem = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
            hOld = SelectObject(hdcMem, hbmMem);
        break;
        }

        case WM_LBUTTONDOWN:
        {
            POINT coord;
            coord.x = LOWORD(lParam);
            coord.y = HIWORD(lParam);

            objects[nrObj] = new Circle(coord,2 + coord.x%5);
            objects[nrObj] -> Color(RGB(coord.x%255, coord.x%125+coord.y%125, coord.y%255));

            nrObj++;
        break;
        }

         case WM_KEYDOWN:
         {
            switch(wParam)
            {
                case VK_DOWN:
                {
                    timerSpeed+=30;
                break;
                }

                case VK_UP:
                {
                    timerSpeed-=30;

                        if (timerSpeed < 0)
                        {
                            timerSpeed = 1;
                        }
                 break;
                }

                default: return DefWindowProc (hwnd, message, wParam, lParam);
            break;
            }

            KillTimer(hwnd,ID_TIMER);
            SetTimer(hwnd,ID_TIMER,timerSpeed,NULL);
        break;
        }

        case WM_MOUSEWHEEL:
        {
            if((short)HIWORD(wParam)<0)
            {
                timerSpeed+=10;
            }
            else
            {
                timerSpeed-=10;
                if (timerSpeed<0)
                {
                    timerSpeed=1;
                }
            }
            KillTimer(hwnd,ID_TIMER);
            SetTimer(hwnd,ID_TIMER,timerSpeed,NULL);
        break;
        }

        case WM_PAINT:
        {
            hdc = BeginPaint(hwnd,&ps);
            GetClientRect(hwnd,&rect);

            for(int i = 0; i<nrObj-1; i++)
            {
                for(int j = i+1; j < nrObj; j++)
                {
                    Interaction(*objects[i],*objects[j]);
                }
            }

            FillRect(hdcMem, &rect,(HBRUSH)GetStockObject(WHITE_BRUSH));

            for(int i = 0; i < nrObj; i++)
            {
                objects[i] -> Move(hdcMem, rect, hBrush);
            }

            BitBlt(hdc, 0, 0, rect.right, rect.bottom, hdcMem, 0, 0, SRCCOPY);

            EndPaint(hwnd,&ps);

        break;
        }

        case WM_TIMER:
        {
            InvalidateRect(hwnd,NULL,FALSE);
        break;
        }

        case WM_DESTROY:
        {
            SelectObject(hdcMem,hOld);
            DeleteObject(hbmMem);
            DeleteDC(hdcMem);
            KillTimer(hwnd,ID_TIMER);

            PostQuitMessage (0);
        break;
        }

        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}
Objects::Objects(POINT center, const int &speed)
 {

    this -> center = center;
    this -> xSpeed = speed;
    this -> ySpeed = speed;
    clr = RGB(0,255,0);

}

bool Objects::Accelerate(const int& dX, const int& dY)
{
    xSpeed = dX;
    ySpeed = dY;
    return TRUE;
}

bool Objects::Color(const COLORREF &clr)
{
    this -> clr = clr;
    return TRUE;
}
bool Objects::Shape(Objects &ob)
{

    return TRUE;
}

bool Circle::Move(const HDC &hdc, const RECT& rect, HBRUSH &hBrush)
{
    hBrush = CreateSolidBrush(clr);
    SelectObject(hdc, hBrush);

    Collision(rect);

    center.x += xSpeed; center.y -= ySpeed;

    if(counter>0)
    {
        Rectangle(hdc, center.x-25, center.y-25, center.x+25, center.y+25 );
        SelectObject(hdc, GetStockObject(WHITE_BRUSH));
        DeleteObject(hBrush);
        return TRUE;
    }

    Ellipse(hdc, center.x-25, center.y-25, center.x+25, center.y+25 );
    SelectObject(hdc, GetStockObject(WHITE_BRUSH));
    DeleteObject(hBrush);
    return TRUE;

}

bool Objects::Collision(const RECT &rect)
{
    if(center.x+25 > rect.right-1)
    {
        xSpeed =- abs(xSpeed);
        counter=1;
    }
    if(center.x-25 < rect.left+1)
    {
        xSpeed = abs(xSpeed);
        counter=1;
    }
    if(center.y+25 > rect.bottom-1)
    {
        ySpeed = abs(ySpeed);
    }
    if(center.y-25 < rect.top+1)
    {
        ySpeed = -abs(ySpeed);
    }
    return TRUE;
}

bool Interaction(Objects &alfa, Objects &beta) {

    float distance;
    POINT totalSpeed;

    distance = sqrt( pow(alfa.center.x-beta.center.x,2) + pow(alfa.center.y-beta.center.y,2) );

    if ( distance < 53 )
    {
    totalSpeed.x = (abs(alfa.xSpeed) + abs(beta.xSpeed))/2;
    totalSpeed.y = (abs(alfa.ySpeed) + abs(beta.ySpeed))/2;

    alfa.Accelerate(-alfa.xSpeed*totalSpeed.x/abs(alfa.xSpeed), -alfa.ySpeed*totalSpeed.y/abs(alfa.ySpeed));
    beta.Accelerate(-beta.xSpeed*totalSpeed.x/abs(beta.xSpeed), -beta.ySpeed*totalSpeed.y/abs(beta.ySpeed));

    alfa.Color(RGB(0,0,255));
    }

    return TRUE;
}
